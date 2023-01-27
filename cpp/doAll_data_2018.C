{
    gROOT->ProcessLine(".L analyze_bjets.C+");
    std::string FILEDIR = "/ceph/cms/store/group/tttt/Worker/usarica/output/Analysis_TTJetRadiation/2023_01_13_tt_bkg_Data";


    // Category Data_2018
    TChain *chData_2018 = new TChain("Events");
    std::string sample_strData_2018("Data_2018");
    chData_2018->Add((FILEDIR + "/2018D/Run2018D*252.root").data());
    chData_2018->Add((FILEDIR + "/2018A/Run2018A*117.root").data());
    chData_2018->Add((FILEDIR + "/2018B/Run2018B*44.root").data());
    chData_2018->Add((FILEDIR + "/2018C/Run2018C*65.root").data());
    ScanChain(chData_2018, sample_strData_2018, "outputs/plots", "outputs/data");


}
