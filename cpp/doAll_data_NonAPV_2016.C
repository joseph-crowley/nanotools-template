{
    gROOT->ProcessLine(".L analyze_bjets.C+");
    std::string FILEDIR = "/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/230209_tt_bkg_Cutbased";


    // Category Data_2016
    TChain *chData_2016 = new TChain("Events");
    std::string sample_strData_2016("Data_2016_NonAPV");
    chData_2016->Add((FILEDIR + "/2016G/Run2016G*.root").data());
    chData_2016->Add((FILEDIR + "/2016F_NonAPV/Run2016F*.root").data());
    chData_2016->Add((FILEDIR + "/2016H/Run2016H*86.root").data());
    ScanChain(chData_2016, sample_strData_2016, "outputs_WPL_bpt40_jpt25/plots", "outputs_WPL_bpt40_jpt25/data");


}
