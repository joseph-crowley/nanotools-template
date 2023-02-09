{
    gROOT->ProcessLine(".L analyze_bjets.C+");
    std::string FILEDIR = "/ceph/cms/store/group/tttt/Worker/usarica/output/Analysis_TTJetRadiation/2023_01_13_tt_bkg_Data";


    // Category Data_2016
    TChain *chData_2016 = new TChain("Events");
    std::string sample_strData_2016("Data_2016_NonAPV");
    chData_2016->Add((FILEDIR + "/2016G/Run2016G*.root").data());
    chData_2016->Add((FILEDIR + "/2016F_NonAPV/Run2016F*.root").data());
    chData_2016->Add((FILEDIR + "/2016H/Run2016H*86.root").data());
    ScanChain(chData_2016, sample_strData_2016, "outputs/plots", "outputs/data");


}
