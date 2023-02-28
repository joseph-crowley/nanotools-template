{
    gROOT->ProcessLine(".L analyze_bjets_C.so");
    const char* env_FILEDIR = std::getenv("FILEDIR");
    std::string FILEDIR = env_FILEDIR != nullptr ? env_FILEDIR : "SPECIFY/FILEDIR/AS/ENV/VARIABLE";
    std::cout << "getting files from " << FILEDIR << endl;


    // Category Data_2016
    TChain *chData_2016 = new TChain("SkimTree");
    std::string sample_strData_2016("Data_2016_NonAPV");
    chData_2016->Add((FILEDIR + "/2016G/Run2016G*.root").data());
    chData_2016->Add((FILEDIR + "/2016F_NonAPV/Run2016F*.root").data());
    chData_2016->Add((FILEDIR + "/2016H/Run2016H*.root").data());
    ScanChain(chData_2016, sample_strData_2016, "outputs/plots", "outputs/data");


}
