from collections import Counter
import json
import subprocess
import os
import shutil
from pprint import pprint

# plotdir is where the plots go
# skimdir is where the skim is
# rootdir is where the output root files go
PLOTDIR = '../cpp/outputs/plots'
SKIMDIR = "/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/2023_01_13_tt_bkg_MC"
ROOTDIR = '../cpp/outputs/mc'

def create_file(dictionary, filename = "doAll_t.C", filepath = ""):
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
            file.write("    gROOT->ProcessLine(\".L analyze_bjets.C+\");\n")
            for category, string in sorted(dictionary.items()):
                file.write("\n")
                file.write("    // Category {}\n".format(category))
                file.write("{}\n".format(string))
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

def get_all_files(skim_dir):
    cmd = f'ls {skim_dir}'
    periods = subprocess.check_output(cmd, shell=True).decode('ascii').split('\n')[:-1]
    files = []
    for p in periods:
        cmd = f'ls {skim_dir}/{p}'
        files += [f"{p}/{f}" for f in subprocess.check_output(cmd, shell=True).decode('ascii').split('\n')[:-1]]
    return files

def files_to_use(sample, files, period):
    sample_name = '_'.join(sample.split("/")[-1].split("_")[0:-3])
    return [f for f in files if f.startswith(f"{period}/{sample_name}")]

def create_output_dictionary(categories):
    return {category: "" for category in categories}

def generate_doall_script(category, files, plot_directory, basedir, rootdir):
    if category == 'Ignore':
        return
    print(f'\n\n\n')
    print(f'generate_doall_script({category}, {files[:2]}, "{plot_directory}", "{basedir}", "{rootdir}")')
    out = ""
    indent = "    "
    chains = set()
    for sample in files:
        files_used = set()
        name_with_wildcard = "_".join(sample.split("_")[:-3] + ["*"] + sample.split("_")[-1:])
        if name_with_wildcard in files_used: continue
        files_used.add(name_with_wildcard)
        period = sample.split('/')[0]
        samp = '_'.join(sample.split("/")[-1].split("_")[0:-3])
        samp_noext = samp.replace("_ext","")
        if category not in chains:
            chains.add(category)
            out += indent + f'std::string FILEDIR = "{basedir}";\n'
            out += indent + f'TChain *ch{category} = new TChain("Events");\n'
            out += indent + f'std::string sample_str{category}("{samp}");\n'
        basestr = f'ch{category}->Add(FILEDIR + "'
        # add the wild card to reduce the output
        out += indent + f'{basestr}/{name_with_wildcard}");\n'
    out += indent + f'ScanChain(ch{category}, sample_str{category}, "{plot_directory}", "{rootdir}");\n\n'
    return ''.join(out)

def main():
    categories = set(sample_map.values())
    files = get_all_files(SKIMDIR)
    output_dict = create_output_dictionary(categories)
    samples = {}
    for category in categories:
        samples.update({category:[]})
        for f in files:
            base_sample = "_".join(f.split('/')[-1].replace("_ext","").split("_of")[0].split("_")[:-1])
            cat = get_category(base_sample, sample_map)
            if cat == category:
                samples[cat].append(f)
        output_dict[category] = generate_doall_script(category, samples[category], PLOTDIR, SKIMDIR, ROOTDIR)

    create_file(output_dict, filename = "doAll_test.C", filepath = ".")

if __name__ == "__main__":
    main()

