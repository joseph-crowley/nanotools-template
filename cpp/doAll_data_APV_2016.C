{
    gROOT->ProcessLine(".L analyze_bjets.C+");
    std::string FILEDIR = "/ceph/cms/store/group/tttt/Worker/usarica/output/Analysis_TTJetRadiation/2023_01_13_tt_bkg_Data";


    // Category Data_2016
    TChain *chData_2016 = new TChain("Events");
    std::string sample_strData_2016("Data_2016_APV");
    chData_2016->Add((FILEDIR + "/2016B/Run2016B*.root").data());
    chData_2016->Add((FILEDIR + "/2016C/Run2016C*.root").data());
    chData_2016->Add((FILEDIR + "/2016D/Run2016D*.root").data());
    chData_2016->Add((FILEDIR + "/2016E/Run2016E*.root").data());
    chData_2016->Add((FILEDIR + "/2016F_APV/Run2016F_APV*25.root").data());
    ScanChain(chData_2016, sample_strData_2016, "outputs/plots", "outputs/data");


}
