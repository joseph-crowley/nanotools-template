{
    gROOT->ProcessLine(".L analyze_bjets.C+");
    std::string FILEDIR = "/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/2023_01_13_tt_bkg_MC";


    // Category TT_lnu
    TChain *chTT_lnu = new TChain("Events");
    std::string sample_strTT_lnu("2016_TT_lnu");
    chTT_lnu->Add((FILEDIR + "/2016_NonAPV/TT_lnu_nlo*290.root").data());
    ScanChain(chTT_lnu, sample_strTT_lnu, "outputs/plots", "outputs/mc");


    // Category TTV
    TChain *chTTV = new TChain("Events");
    std::string sample_strTTV("2016_TTV");
    chTTV->Add((FILEDIR + "/2016_NonAPV/TTH_HToNonBB*5.root").data());
    chTTV->Add((FILEDIR + "/2016_NonAPV/TTW_lnu*7.root").data());
    chTTV->Add((FILEDIR + "/2016_NonAPV/TTZ_2l2nu_M_10*13.root").data());
    ScanChain(chTTV, sample_strTTV, "outputs/plots", "outputs/mc");


    // Category WW
    TChain *chWW = new TChain("Events");
    std::string sample_strWW("2016_WW");
    chWW->Add((FILEDIR + "/2016_NonAPV/qqWW_2l2nu*5.root").data());
    ScanChain(chWW, sample_strWW, "outputs/plots", "outputs/mc");


    // Category ST_tW
    TChain *chST_tW = new TChain("Events");
    std::string sample_strST_tW("2016_ST_tW");
    chST_tW->Add((FILEDIR + "/2016_NonAPV/ST_tW_antitop_5f_NoFullyHadronicDecays*7.root").data());
    chST_tW->Add((FILEDIR + "/2016_NonAPV/ST_tW_top_5f_NoFullyHadronicDecays*7.root").data());
    ScanChain(chST_tW, sample_strST_tW, "outputs/plots", "outputs/mc");


    // Category Others
    TChain *chOthers = new TChain("Events");
    std::string sample_strOthers("2016_Others");
    chOthers->Add((FILEDIR + "/2016_NonAPV/DY_2l_M_10to50*11.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/DY_2l_M_50*94.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/GGH_ZZTo4L_POWHEG*2.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTGJets*3.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTHH*1.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTTJ*1.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTTW*1.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTWH*1.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTWW*1.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTWZ*1.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTZH*1.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/TTZZ*1.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WJets_lnu_0j*157.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WJets_lnu_1j*212.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WJets_lnu_2j*120.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WWG*2.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WWW_4f*1.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WWW_4f_ext*7.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WZG*2.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WZZ*1.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WZZ_ext*8.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/ZZZ*1.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/ZZZ_ext*7.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqWG_lnu_lo*5.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqWG_lnu_nlo_01j*87.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqWZ_3lnu_MG*17.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqWZ_3lnu_POWHEG*2.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqZG_ll_01j*53.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqZZ_4l*72.root").data());
    ScanChain(chOthers, sample_strOthers, "outputs/plots", "outputs/mc");


    // Category TT_2l2nu
    TChain *chTT_2l2nu = new TChain("Events");
    std::string sample_strTT_2l2nu("2016_TT_2l2nu");
    chTT_2l2nu->Add((FILEDIR + "/2016_NonAPV/TT_2l2nu*88.root").data());
    ScanChain(chTT_2l2nu, sample_strTT_2l2nu, "outputs/plots", "outputs/mc");


}
