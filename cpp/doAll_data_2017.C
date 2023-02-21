{
    gROOT->ProcessLine(".L analyze_bjets.C+");
    std::string FILEDIR = "/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/230209_tt_bkg_Cutbased";


    // Category Data_2017
    TChain *chData_2017 = new TChain("Events");
    std::string sample_strData_2017("Data_2017");
    chData_2017->Add((FILEDIR + "/2017F/Run2017F*110.root").data());
    chData_2017->Add((FILEDIR + "/2017B/Run2017B*83.root").data());
    chData_2017->Add((FILEDIR + "/2017C/Run2017C*145.root").data());
    chData_2017->Add((FILEDIR + "/2017D/Run2017D*68.root").data());
    chData_2017->Add((FILEDIR + "/2017E/Run2017E*51.root").data());
    ScanChain(chData_2017, sample_strData_2017, "outputs_WPL_bpt40_jpt25/plots", "outputs_WPL_bpt40_jpt25/data");


}
