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

# USE THESE SETTINGS FOR MONTE CARLO
tag = 'mc'
SKIMDIR = "/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/2023_01_13_tt_bkg_MC"

## USE THESE SETTINGS FOR DATA 
#tag = 'data'
#SKIMDIR = "/ceph/cms/store/group/tttt/Worker/usarica/output/Analysis_TTJetRadiation/2023_01_13_tt_bkg_Data"

years = ['APV_2016','NonAPV_2016' ,'2017','2018']
PLOTDIR = 'outputs/plots'
ROOTDIR = f'outputs/{tag}'
indent = 4*" "

def get_2016_era(period):
    APV = ['B','C','D','E','F_APV']
    NonAPV = ['G','H','F_NonAPV']
    APV_2016 = ['2016'+c for c in APV]
    NonAPV_2016 = ['2016'+c for c in NonAPV]
    if period in APV_2016:
        return "APV_2016X"
    if period in NonAPV_2016:
        return "NonAPV_2016X"
    return period

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
            if "Data" in category:
                base_sample = f.split('/')[-1].split('_')[0]
            else:
                base_sample = "_".join(f.split('/')[-1].replace("_ext","").split("_of")[0].split("_")[:-1])
            cat = get_category(base_sample, map_sample_to_category)
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
    with open(f'sample_map_{tag}.json','r') as f:
        sample_map = json.load(f)
    sample_map_inv = {}
    for k,l in sample_map.items():
        for s in l:
            sample_map_inv[s] = k
    return sample_map, sample_map_inv

map_category_to_sample, map_sample_to_category = load_sample_map()

def get_category(base_sample, map_sample_to_category):
    if 'Run20' in base_sample: 
        return "Data_" + base_sample[3:-1]
    if base_sample in map_sample_to_category.keys():
        return map_sample_to_category[base_sample]
    return 'Ignore'

def get_all_periods(skim_dir):
    cmd = f'ls {skim_dir}'
    periods = subprocess.check_output(cmd, shell=True).decode('ascii').split('\n')[:-1]
    return periods

def get_all_files(skim_dir, period = ''):
    if not isinstance(period,list): 
        if not period:
            periods = get_all_periods(skim_dir)
        else:
            periods = [period]
    else:
        periods = period

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

            #if "APV" in period:
            #    period_str = "2016"
            #else:
            #    period_str = period
            period_str = period

            if category not in chains:
                chains.add(category)
                out += "\n"
                out += indent + "// Category {}\n".format(category)
                out += indent + f'TChain *ch{category} = new TChain("Events");\n'
                if "Data" in category:
                    out += indent + f'std::string sample_str{category}("{category}");\n'
                else:
                    out += indent + f'std::string sample_str{category}("{period_str}_{category}");\n'
            basestr = f'ch{category}->Add((FILEDIR + "'
            # add the wild card to reduce the output
            out += indent + f'{basestr}/{period}/{name_with_wildcard}").data());\n'
        out += indent + f'ScanChain(ch{category}, sample_str{category}, "{plot_directory}", "{rootdir}");\n\n'
    return ''.join(''.join(out))

def main():
    categories = set(map_sample_to_category.values())
    if tag == "data":
        # TODO: make the periods = years for data
        #periods = years
        periods = get_all_periods(SKIMDIR)
    else: 
        periods = get_all_periods(SKIMDIR)
    output_dict = create_output_dictionary(periods,categories)
    for period, categories_dict in output_dict.items():
        # generate a doAll script for the period with all categories
        files = get_all_files(SKIMDIR, period)
        samples_by_category = get_samples_by_category(categories, files)
        periods_to_add = [i for category in samples_by_category.keys() for i in map_category_to_sample[category]]
        for p in periods_to_add:
            if p == period or p[:4] not in years: continue
            files = get_all_files(SKIMDIR, p)
            samples_to_add = get_samples_by_category(categories, files)

            # update samples_by_category to join on keys with samples_to_add
            for cat, fis in samples_to_add.items():
                if cat in samples_by_category:
                    samples_by_category[cat].extend(fis)
                else:
                    samples_by_category.update({cat:fis})

        #print(samples_by_category)

        output_dict[period] = generate_doall_script(samples_by_category, PLOTDIR, SKIMDIR, ROOTDIR)
   

    # join years for data (by this point all the periods will have info about the full year in data)
    joined_output_dict = {}
    periods_used = set()
    for p, doall_str in output_dict.items():
        # 2016 needs special treatment
        if "2016" in p:
            per = get_2016_era(p)
        else:
            per = p
        if per in joined_output_dict or per[:-1] not in years: continue
        joined_output_dict.update({per[:-1]: doall_str})
        periods_used.add(p)

    output_dict.update(joined_output_dict)
    for p in periods_used:
        del output_dict[p]

    for per, doall_str in output_dict.items():
        create_file(doall_str, f'doAll_{tag}_{per}.C')
    #pprint(output_dict)

if __name__ == "__main__":
    main()


