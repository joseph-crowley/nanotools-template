{
    gROOT->ProcessLine(".L analyze_bjets_C.so");
    const char* env_FILEDIR = std::getenv("FILEDIR");
    std::string FILEDIR = env_FILEDIR != nullptr ? env_FILEDIR : "SPECIFY/FILEDIR/AS/ENV/VARIABLE";
    std::cout << "getting files from " << FILEDIR << endl;


    // Category Data_2016
    TChain *chData_2016 = new TChain("SkimTree");
    std::string sample_strData_2016("Data_2016_APV");
    chData_2016->Add((FILEDIR + "/2016B/Run2016B*.root").data());
    chData_2016->Add((FILEDIR + "/2016C/Run2016C*.root").data());
    chData_2016->Add((FILEDIR + "/2016D/Run2016D*.root").data());
    chData_2016->Add((FILEDIR + "/2016E/Run2016E*.root").data());
    chData_2016->Add((FILEDIR + "/2016F_APV/Run2016F_APV*.root").data());
    ScanChain(chData_2016, sample_strData_2016, "outputs/plots", "outputs/data");


}
