{
    gROOT->ProcessLine(".L analyze_bjets.C+");
    std::string FILEDIR = "/ceph/cms/store/group/tttt/Worker/usarica/output/Analysis_TTJetRadiation/2023_01_13_tt_bkg_Data";

    // Category Data
    TChain *chData = new TChain("Events");
    std::string sample_strData("Data");
    chData->Add((FILEDIR + "/2016B/Run2016B*103.root").data());
    chData->Add((FILEDIR + "/2016C/Run2016C*37.root").data());
    chData->Add((FILEDIR + "/2016D/Run2016D*37.root").data());
    chData->Add((FILEDIR + "/2016E/Run2016E*28.root").data());
    chData->Add((FILEDIR + "/2016F_APV/Run2016F_APV*25.root").data());
    chData->Add((FILEDIR + "/2016F_NonAPV/Run2016F_NonAPV*7.root").data());
    chData->Add((FILEDIR + "/2016G/Run2016G*70.root").data());
    chData->Add((FILEDIR + "/2016H/Run2016H*86.root").data());
    chData->Add((FILEDIR + "/2017B/Run2017B*83.root").data());
    chData->Add((FILEDIR + "/2017C/Run2017C*145.root").data());
    chData->Add((FILEDIR + "/2017D/Run2017D*68.root").data());
    chData->Add((FILEDIR + "/2017E/Run2017E*51.root").data());
    chData->Add((FILEDIR + "/2017F/Run2017F*110.root").data());
    chData->Add((FILEDIR + "/2018A/Run2018A*117.root").data());
    chData->Add((FILEDIR + "/2018B/Run2018B*44.root").data());
    chData->Add((FILEDIR + "/2018C/Run2018C*65.root").data());
    ScanChain(chData, sample_strData, "outputs/plots", "outputs/data");


}
