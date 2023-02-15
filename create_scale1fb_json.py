import os
import pandas as pd
import json

data_dir = '/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/230214_tt_bkg_Cutbased'

# Function to get the paths for a given dataset and period
def get_paths(short_name, period):
    if period == '2016':
        prefix = '2016_APV' if 'APV' in short_name else '2016_NonAPV'
    else:
        prefix = period

    pattern = f'{short_name}_*_of_*.root'
    path = os.path.join(data_dir, prefix, pattern)

    return [path]

# Load CSV file into a pandas DataFrame
df = pd.read_csv('samples.csv')

# Initialize an empty dictionary to hold the output
samples_dict = {}

# Iterate over each row in the DataFrame
for index, row in df.iterrows():
    # Extract the relevant information from the row
    dataset = row['dataset']
    short_name = row['short_name'].replace('_ext','')

    if "#" in dataset:
        continue

    if short_name not in samples_dict:
        samples_dict[short_name] = {}

    period = row['period']
    xsec = row['xsec']
    BR = row['BR']
    extra_arguments = row['extra_arguments']

    # Create a new dictionary for the period if it doesn't exist yet
    if period not in samples_dict[short_name]:
        samples_dict[short_name][period] = {'paths':[], 'metadata':{}}

    # Add the paths and metadata to the period dictionary
    samples_dict[short_name][period]['paths'].append(get_paths(short_name, period))
    samples_dict[short_name][period]['metadata'].update({'xs': xsec})

# Convert the dictionary to a JSON string and save it to a file
with open('samples.json', 'w') as f:
    json.dump(samples_dict, f, indent=4)

