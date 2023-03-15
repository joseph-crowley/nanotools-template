{
    gROOT->ProcessLine(".L check_fakes_C.so");
    const char* env_FILEDIR = std::getenv("FILEDIRMC");
    std::string FILEDIR = env_FILEDIR != nullptr ? env_FILEDIR : "SPECIFY/FILEDIR/AS/ENV/VARIABLE";
    std::cout << "getting files from " << FILEDIR << endl;


    // Category TTV
    TChain *chTTV = new TChain("SkimTree");
    std::string sample_strTTV("2018_TTV");
    chTTV->Add((FILEDIR + "/2018/TTH_HToNonBB*.root").data());
    chTTV->Add((FILEDIR + "/2018/TTW_lnu*.root").data());
    chTTV->Add((FILEDIR + "/2018/TTZ_2l2nu_M_10*.root").data());


    // Category TT_lnu
    TChain *chTT_lnu = new TChain("SkimTree");
    std::string sample_strTT_lnu("2018_TT_lnu");
    chTT_lnu->Add((FILEDIR + "/2018/TT_lnu_nlo*.root").data());


    // Category TT_2l2nu
    TChain *chTT_2l2nu = new TChain("SkimTree");
    std::string sample_strTT_2l2nu("2018_TT_2l2nu");
    chTT_2l2nu->Add((FILEDIR + "/2018/TT_2l2nu*.root").data());


    // Category ST_tW
    TChain *chST_tW = new TChain("SkimTree");
    std::string sample_strST_tW("2018_ST_tW");
    chST_tW->Add((FILEDIR + "/2018/ST_tW_antitop_5f_NoFullyHadronicDecays*.root").data());
    chST_tW->Add((FILEDIR + "/2018/ST_tW_top_5f_NoFullyHadronicDecays*.root").data());


    // Category WW
    TChain *chWW = new TChain("SkimTree");
    std::string sample_strWW("2018_WW");
    chWW->Add((FILEDIR + "/2018/qqWW_2l2nu*.root").data());


    // Category Others
    TChain *chOthers = new TChain("SkimTree");
    std::string sample_strOthers("2018_Others");
    chOthers->Add((FILEDIR + "/2018/DY_2l_M_10to50*.root").data());
    chOthers->Add((FILEDIR + "/2018/DY_2l_M_50*.root").data());
    chOthers->Add((FILEDIR + "/2018/GGH_ZZTo4L_POWHEG*.root").data());
    chOthers->Add((FILEDIR + "/2018/TTGJets_ext*.root").data());
    chOthers->Add((FILEDIR + "/2018/TTHH*.root").data());
    chOthers->Add((FILEDIR + "/2018/TTTJ*.root").data());
    chOthers->Add((FILEDIR + "/2018/TTTW*.root").data());
    chOthers->Add((FILEDIR + "/2018/TTWH*.root").data());
    chOthers->Add((FILEDIR + "/2018/TTWW*.root").data());
    chOthers->Add((FILEDIR + "/2018/TTWZ*.root").data());
    chOthers->Add((FILEDIR + "/2018/TTZH*.root").data());
    chOthers->Add((FILEDIR + "/2018/TTZZ*.root").data());
    chOthers->Add((FILEDIR + "/2018/WJets_lnu_0j*.root").data());
    chOthers->Add((FILEDIR + "/2018/WJets_lnu_1j*.root").data());
    chOthers->Add((FILEDIR + "/2018/WJets_lnu_2j*.root").data());
    chOthers->Add((FILEDIR + "/2018/WWG*.root").data());
    chOthers->Add((FILEDIR + "/2018/WWW_4f_ext*.root").data());
    chOthers->Add((FILEDIR + "/2018/WZG*.root").data());
    chOthers->Add((FILEDIR + "/2018/WZZ_ext*.root").data());
    chOthers->Add((FILEDIR + "/2018/ZZZ_ext*.root").data());
    chOthers->Add((FILEDIR + "/2018/qqWG_lnu_lo*.root").data());
    chOthers->Add((FILEDIR + "/2018/qqWG_lnu_nlo_01j*.root").data());
    chOthers->Add((FILEDIR + "/2018/qqWZ_3lnu_MG*.root").data());
    chOthers->Add((FILEDIR + "/2018/qqWZ_3lnu_POWHEG*.root").data());
    chOthers->Add((FILEDIR + "/2018/qqZG_ll_01j*.root").data());
    chOthers->Add((FILEDIR + "/2018/qqZZ_4l*.root").data());

    
    // group everything by number of real b's instead
    TChain *chAll = new TChain("SkimTree");
    chAll->Add(chTTV);
    chAll->Add(chTT_lnu);
    chAll->Add(chTT_2l2nu);
    chAll->Add(chST_tW);
    chAll->Add(chWW);
    chAll->Add(chOthers);

    ScanChain(chAll, "all_real_b", "outputs/plots", "outputs/mc", 0);
    ScanChain(chAll, "1c_0j", "outputs/plots", "outputs/mc", 1);
    ScanChain(chAll, "1c_1j", "outputs/plots", "outputs/mc", 2);
    ScanChain(chAll, "0c_1j", "outputs/plots", "outputs/mc", 3);


}
