{
    gROOT->ProcessLine(".L analyze_bjets_C.so");
    std::string FILEDIR = "/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/230223_tt_bkg_Cutbased";


    // Category Data_2017
    TChain *chData_2017 = new TChain("SkimTree");
    std::string sample_strData_2017("Data_2017");
    chData_2017->Add((FILEDIR + "/2017F/Run2017F*.root").data());
    chData_2017->Add((FILEDIR + "/2017B/Run2017B*.root").data());
    chData_2017->Add((FILEDIR + "/2017C/Run2017C*.root").data());
    chData_2017->Add((FILEDIR + "/2017D/Run2017D*.root").data());
    chData_2017->Add((FILEDIR + "/2017E/Run2017E*.root").data());
    ScanChain(chData_2017, sample_strData_2017, "outputs/plots", "outputs/data");


}
