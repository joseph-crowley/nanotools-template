# NanoTools Template

just a scanchain definition, doall script, and the NanoCORE dependency. 

## To use the template:
Running from UAF:
```
git clone https://github.com/joseph-crowley/nanotools-template.git
cd /cvmfs/cms.cern.ch/slc7_amd64_gcc900/cms/cmssw/CMSSW_12_2_0/ ; cmsenv ; cd -
voms-proxy-init --rfc --voms cms -valid 192:00
cd nanotools-template/NanoCORE
make clean all 
cd ..
```

### note about using ivy:
```
eval $(./setup.sh env)
```

## Then run the example:
```
cd cpp
root -l -b -q doAll.C
```

This produces an output.root file with a tree with one branch: leading muon pt. 
