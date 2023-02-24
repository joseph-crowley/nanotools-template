{
    gROOT->ProcessLine(".L analyze_bjets_C.so");
    std::string FILEDIR = "/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/230223_tt_bkg_Cutbased";


    // Category TT_lnu
    TChain *chTT_lnu = new TChain("SkimTree");
    std::string sample_strTT_lnu("2016_TT_lnu");
    chTT_lnu->Add((FILEDIR + "/2016_NonAPV/TT_lnu_nlo*.root").data());
    ScanChain(chTT_lnu, sample_strTT_lnu, "outputs/plots", "outputs/mc");


    // Category TTV
    TChain *chTTV = new TChain("SkimTree");
    std::string sample_strTTV("2016_TTV");
    chTTV->Add((FILEDIR + "/2016_NonAPV/TTH_HToNonBB*.root").data());
    chTTV->Add((FILEDIR + "/2016_NonAPV/TTW_lnu*.root").data());
    chTTV->Add((FILEDIR + "/2016_NonAPV/TTZ_2l2nu_M_10*.root").data());
    ScanChain(chTTV, sample_strTTV, "outputs/plots", "outputs/mc");


    // Category WW
    TChain *chWW = new TChain("SkimTree");
    std::string sample_strWW("2016_WW");
    chWW->Add((FILEDIR + "/2016_NonAPV/qqWW_2l2nu*.root").data());
    ScanChain(chWW, sample_strWW, "outputs/plots", "outputs/mc");


    // Category ST_tW
    TChain *chST_tW = new TChain("SkimTree");
    std::string sample_strST_tW("2016_ST_tW");
    chST_tW->Add((FILEDIR + "/2016_NonAPV/ST_tW_antitop_5f_NoFullyHadronicDecays*.root").data());
    chST_tW->Add((FILEDIR + "/2016_NonAPV/ST_tW_top_5f_NoFullyHadronicDecays*.root").data());
    ScanChain(chST_tW, sample_strST_tW, "outputs/plots", "outputs/mc");


    // Category Others
    TChain *chOthers = new TChain("SkimTree");
    std::string sample_strOthers("2016_Others");
    chOthers->Add((FILEDIR + "/2016_NonAPV/DY_2l_M_10to50*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/DY_2l_M_50*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/GGH_ZZTo4L_POWHEG*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTGJets*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTHH*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTTJ*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTTW*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTWH*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTWW*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTWZ*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTZH*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTZZ*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WJets_lnu_0j*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WJets_lnu_1j*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WJets_lnu_2j*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WWG*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WWW_4f_ext*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WZG*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WZZ_ext*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/ZZZ_ext*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqWG_lnu_lo*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqWG_lnu_nlo_01j*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqWZ_3lnu_MG*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqWZ_3lnu_POWHEG*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqZG_ll_01j*.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqZZ_4l*.root").data());
    ScanChain(chOthers, sample_strOthers, "outputs/plots", "outputs/mc");


    // Category TT_2l2nu
    TChain *chTT_2l2nu = new TChain("SkimTree");
    std::string sample_strTT_2l2nu("2016_TT_2l2nu");
    chTT_2l2nu->Add((FILEDIR + "/2016_NonAPV/TT_2l2nu*.root").data());
    ScanChain(chTT_2l2nu, sample_strTT_2l2nu, "outputs/plots", "outputs/mc");


}
