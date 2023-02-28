{
    gROOT->ProcessLine(".L analyze_bjets_C.so");
    const char* env_FILEDIR = std::getenv("FILEDIR");
    std::string FILEDIR = env_FILEDIR != nullptr ? env_FILEDIR : "SPECIFY/FILEDIR/AS/ENV/VARIABLE";
    std::cout << "getting files from " << FILEDIR << endl;


    // Category TTV
    TChain *chTTV = new TChain("SkimTree");
    std::string sample_strTTV("2016_APV_TTV");
    chTTV->Add((FILEDIR + "/2016_APV/TTH_HToNonBB*.root").data());
    chTTV->Add((FILEDIR + "/2016_APV/TTW_lnu*.root").data());
    chTTV->Add((FILEDIR + "/2016_APV/TTZ_2l2nu_M_10*.root").data());
    ScanChain(chTTV, sample_strTTV, "outputs/plots", "outputs/mc");


    // Category TT_lnu
    TChain *chTT_lnu = new TChain("SkimTree");
    std::string sample_strTT_lnu("2016_APV_TT_lnu");
    chTT_lnu->Add((FILEDIR + "/2016_APV/TT_lnu_nlo*.root").data());
    ScanChain(chTT_lnu, sample_strTT_lnu, "outputs/plots", "outputs/mc");


    // Category TT_2l2nu
    TChain *chTT_2l2nu = new TChain("SkimTree");
    std::string sample_strTT_2l2nu("2016_APV_TT_2l2nu");
    chTT_2l2nu->Add((FILEDIR + "/2016_APV/TT_2l2nu*.root").data());
    ScanChain(chTT_2l2nu, sample_strTT_2l2nu, "outputs/plots", "outputs/mc");


    // Category ST_tW
    TChain *chST_tW = new TChain("SkimTree");
    std::string sample_strST_tW("2016_APV_ST_tW");
    chST_tW->Add((FILEDIR + "/2016_APV/ST_tW_antitop_5f_NoFullyHadronicDecays*.root").data());
    chST_tW->Add((FILEDIR + "/2016_APV/ST_tW_top_5f_NoFullyHadronicDecays*.root").data());
    ScanChain(chST_tW, sample_strST_tW, "outputs/plots", "outputs/mc");


    // Category WW
    TChain *chWW = new TChain("SkimTree");
    std::string sample_strWW("2016_APV_WW");
    chWW->Add((FILEDIR + "/2016_APV/qqWW_2l2nu*.root").data());
    ScanChain(chWW, sample_strWW, "outputs/plots", "outputs/mc");


    // Category Others
    TChain *chOthers = new TChain("SkimTree");
    std::string sample_strOthers("2016_APV_Others");
    chOthers->Add((FILEDIR + "/2016_APV/DY_2l_M_10to50*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/DY_2l_M_50*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/GGH_ZZTo4L_POWHEG*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTGJets*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTHH*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTTJ*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTTW*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTWH*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTWW*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTWZ*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTZH*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTZZ*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WJets_lnu_0j*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WJets_lnu_1j*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WJets_lnu_2j*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WWG*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WWW_4f*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WWW_4f_ext*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WZG*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WZZ*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WZZ_ext*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/ZZZ*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/ZZZ_ext*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/qqWG_lnu_lo*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/qqWG_lnu_nlo_01j*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/qqWZ_3lnu_MG*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/qqWZ_3lnu_POWHEG*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/qqZG_ll_01j*.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/qqZZ_4l*.root").data());
    ScanChain(chOthers, sample_strOthers, "outputs/plots", "outputs/mc");


}
