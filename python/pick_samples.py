from collections import Counter
import json
import subprocess
import os
import shutil
import re
from pprint import pprint

# plotdir is where the plots go
# skimdir is where the skim is
# rootdir is where the output root files go
PLOTDIR = 'outputs/plots'
#SKIMDIR = "/ceph/cms/store/group/tttt/Worker/usarica/output/Analysis_TTJetRadiation/2023_01_13_tt_bkg_Data"
SKIMDIR = "/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/2023_01_13_tt_bkg_MC"
ROOTDIR = 'outputs/mc'
indent = 4*" "

def get_file_name_for_doAll(filename):
    pattern = r"(.*)_([0-9]+)_of_([0-9]+).*"
    match = re.match(pattern, filename)
    if match:
        return match.group(1) + "*" + match.group(3) + ".root"
    else:
        return filename

def get_samples_by_category(categories, files):
    # TODO: finish fixing this (output_dict not defined, etc)
    samples = {}
    for category in categories:
        samples.update({category:[]})
        for f in files:
            base_sample = "_".join(f.split('/')[-1].replace("_ext","").split("_of")[0].split("_")[:-1])
            cat = get_category(base_sample, sample_map)
            if cat == category:
                samples[cat].append(f)

        if not samples[category]:
            print(f'no samples for {category}')
            del samples[category]
    return samples

def create_file(contents, filename = "doAll_t.C", filepath = ""):
    if filepath:
        file_path = os.path.join(filepath, filename)
    else:
        file_path = filename
    try:
        if os.path.isfile(file_path):
            shutil.copy2(file_path, file_path+".bak")
            print(f'{file_path} already exists, a backup was created at {file_path}.bak and the original will be overwritten.')
        with open(file_path, "w") as file:
            file.write("{\n")
            file.write(indent + "gROOT->ProcessLine(\".L analyze_bjets.C+\");\n")
            file.write(indent + f'std::string FILEDIR = "{SKIMDIR}";\n')
            file.write("\n")
            file.write("{}\n".format(contents))
            file.write("}\n")
    except Exception as e:
        print(f"An error occurred: {e}")

def load_sample_map():
    with open('sample_map.json','r') as f:
        sample_map = json.load(f)
    sample_map_inv = {}
    for k,l in sample_map.items():
        for s in l:
            sample_map_inv[s] = k
    return sample_map, sample_map_inv

_, sample_map = load_sample_map()

def get_category(base_sample, sample_map):
    if 'Run20' in base_sample: return 'Data'
    if base_sample in sample_map.keys():
        return sample_map[base_sample]
    return 'Ignore'

def get_all_periods(skim_dir):
    cmd = f'ls {skim_dir}'
    periods = subprocess.check_output(cmd, shell=True).decode('ascii').split('\n')[:-1]
    return periods

def get_all_files(skim_dir, period: str = ''):
    if not period:
        periods = get_all_periods(skim_dir)
    else:
        periods = [period]

    files = []
    for p in periods:
        cmd = f'ls {skim_dir}/{p}'
        files += [f"{p}/{f}" for f in subprocess.check_output(cmd, shell=True).decode('ascii').split('\n')[:-1]]
    return files

def files_to_use(sample, files, period):
    sample_name = '_'.join(sample.split("/")[-1].split("_")[0:-3])
    return [f for f in files if f.startswith(f"{period}/{sample_name}")]

def create_output_dictionary(periods, categories):
    return {p:{category: "" for category in categories} for p in periods}

def generate_doall_script(samples_by_category, plot_directory, basedir, rootdir):
    categories = list(samples_by_category.keys())
    files = [ll for l in list(samples_by_category.values()) for ll in l]
    print(f'\n\n\n')
    print(f'generate_doall_script({categories}, {files[:2]}..., "{plot_directory}", "{basedir}", "{rootdir}")')
    out = ""
    chains = set()
    files_used = set()
    for category, files in samples_by_category.items():
        if category == 'Ignore':
            continue
        for sample in files:
            name_with_wildcard = get_file_name_for_doAll(sample.split("/")[-1])
            if name_with_wildcard in files_used: continue
            files_used.add(name_with_wildcard)
            period = sample.split('/')[0]
            if category not in chains:
                chains.add(category)
                out += "\n"
                out += indent + "// Category {}\n".format(category)
                out += indent + f'TChain *ch{category} = new TChain("Events");\n'
                out += indent + f'std::string sample_str{category}("{category}");\n'
            basestr = f'ch{category}->Add((FILEDIR + "'
            # add the wild card to reduce the output
            out += indent + f'{basestr}/{period}/{name_with_wildcard}").data());\n'
        out += indent + f'ScanChain(ch{category}, sample_str{category}, "{plot_directory}", "{rootdir}");\n\n'
    return ''.join(''.join(out))

def main():
    categories = set(sample_map.values())
    periods = get_all_periods(SKIMDIR)
    output_dict = create_output_dictionary(periods,categories)
    for period, categories_dict in output_dict.items():
        # generate a doAll script for the period with all categories
        files = get_all_files(SKIMDIR, period)
        samples_by_category = get_samples_by_category(categories, files)
        categories_used = list(samples_by_category.keys())
        output_dict[period] = generate_doall_script(samples_by_category, PLOTDIR, SKIMDIR, ROOTDIR)
   
    pprint(output_dict)


    for period, doall_str in output_dict.items():
         pprint(doall_str)
         create_file(doall_str, f'doAll_{period}.C')

if __name__ == "__main__":
    main()

