import ROOT as root
from ROOT import gROOT
import json

import helper_functions as hf

r.gSystem.Load('loopers/analyze_bjets.so')

samples_json = 'samples_MC_Run2.json'
with open(samples_json,'r') as f:
    samples = json.load(f)

for name,sample in samples:
    ch = root.TChain("Events")

    for file_ in hf.get_files(sample['2017']['paths']): ch.Add(file_)
    input(ch)

    root.ScanChain(ch, sample_str, "outputs/plots", "outputs/mc");
