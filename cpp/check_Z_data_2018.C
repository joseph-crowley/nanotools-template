{
    gROOT->ProcessLine(".L check_Z_C.so");
    const char* env_FILEDIR = std::getenv("FILEDIR");
    std::string FILEDIR = env_FILEDIR != nullptr ? env_FILEDIR : "SPECIFY/FILEDIR/AS/ENV/VARIABLE";
    std::cout << "getting files from " << FILEDIR << endl;


    // Category Data_2018
    TChain *chData_2018 = new TChain("SkimTree");
    std::string sample_strData_2018("Data_2018");
    chData_2018->Add((FILEDIR + "/2018D/Run2018D*.root").data());
    chData_2018->Add((FILEDIR + "/2018A/Run2018A*.root").data());
    chData_2018->Add((FILEDIR + "/2018B/Run2018B*.root").data());
    chData_2018->Add((FILEDIR + "/2018C/Run2018C*.root").data());
    ScanChain(chData_2018, sample_strData_2018, "outputs/plots", "outputs/data");


}
