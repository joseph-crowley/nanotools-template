{
    gROOT->ProcessLine(".L analyze_bjets.C+");
    std::string FILEDIR = "/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/2023_01_13_tt_bkg_MC";


    // Category Others
    TChain *chOthers = new TChain("Events");
    std::string sample_strOthers("2018_Others");
    chOthers->Add((FILEDIR + "/2018/DY_2l_M_10to50*57.root").data());
    chOthers->Add((FILEDIR + "/2018/DY_2l_M_50*283.root").data());
    chOthers->Add((FILEDIR + "/2018/GGH_ZZTo4L_POWHEG*2.root").data());
    chOthers->Add((FILEDIR + "/2018/TTGJets*8.root").data());
    chOthers->Add((FILEDIR + "/2018/TTGJets_ext*11.root").data());
    chOthers->Add((FILEDIR + "/2018/TTHH*1.root").data());
    chOthers->Add((FILEDIR + "/2018/TTTJ*1.root").data());
    chOthers->Add((FILEDIR + "/2018/TTTW*1.root").data());
    chOthers->Add((FILEDIR + "/2018/TTWH*1.root").data());
    chOthers->Add((FILEDIR + "/2018/TTWW*2.root").data());
    chOthers->Add((FILEDIR + "/2018/TTWZ*1.root").data());
    chOthers->Add((FILEDIR + "/2018/TTZH*1.root").data());
    chOthers->Add((FILEDIR + "/2018/TTZZ*1.root").data());
    chOthers->Add((FILEDIR + "/2018/WJets_lnu_0j*175.root").data());
    chOthers->Add((FILEDIR + "/2018/WJets_lnu_1j*232.root").data());
    chOthers->Add((FILEDIR + "/2018/WJets_lnu_2j*131.root").data());
    chOthers->Add((FILEDIR + "/2018/WWG*5.root").data());
    chOthers->Add((FILEDIR + "/2018/WWW_4f*1.root").data());
    chOthers->Add((FILEDIR + "/2018/WWW_4f_ext*16.root").data());
    chOthers->Add((FILEDIR + "/2018/WZG*4.root").data());
    chOthers->Add((FILEDIR + "/2018/WZZ*1.root").data());
    chOthers->Add((FILEDIR + "/2018/WZZ_ext*16.root").data());
    chOthers->Add((FILEDIR + "/2018/ZZZ*1.root").data());
    chOthers->Add((FILEDIR + "/2018/ZZZ_ext*14.root").data());
    chOthers->Add((FILEDIR + "/2018/qqWG_lnu_lo*15.root").data());
    chOthers->Add((FILEDIR + "/2018/qqWG_lnu_nlo_01j*96.root").data());
    chOthers->Add((FILEDIR + "/2018/qqWZ_3lnu_MG*16.root").data());
    chOthers->Add((FILEDIR + "/2018/qqWZ_3lnu_POWHEG*4.root").data());
    chOthers->Add((FILEDIR + "/2018/qqZG_ll_01j*53.root").data());
    chOthers->Add((FILEDIR + "/2018/qqZZ_4l*139.root").data());
    ScanChain(chOthers, sample_strOthers, "outputs/plots", "outputs/mc");


    // Category TT_lnu
    TChain *chTT_lnu = new TChain("Events");
    std::string sample_strTT_lnu("2018_TT_lnu");
    chTT_lnu->Add((FILEDIR + "/2018/TT_lnu_nlo*953.root").data());
    ScanChain(chTT_lnu, sample_strTT_lnu, "outputs/plots", "outputs/mc");


    // Category WW
    TChain *chWW = new TChain("Events");
    std::string sample_strWW("2018_WW");
    chWW->Add((FILEDIR + "/2018/qqWW_2l2nu*17.root").data());
    ScanChain(chWW, sample_strWW, "outputs/plots", "outputs/mc");


    // Category ST_tW
    TChain *chST_tW = new TChain("Events");
    std::string sample_strST_tW("2018_ST_tW");
    chST_tW->Add((FILEDIR + "/2018/ST_tW_antitop_5f_NoFullyHadronicDecays*20.root").data());
    chST_tW->Add((FILEDIR + "/2018/ST_tW_top_5f_NoFullyHadronicDecays*21.root").data());
    ScanChain(chST_tW, sample_strST_tW, "outputs/plots", "outputs/mc");


    // Category TTV
    TChain *chTTV = new TChain("Events");
    std::string sample_strTTV("2018_TTV");
    chTTV->Add((FILEDIR + "/2018/TTH_HToNonBB*15.root").data());
    chTTV->Add((FILEDIR + "/2018/TTW_lnu*21.root").data());
    chTTV->Add((FILEDIR + "/2018/TTZ_2l2nu_M_10*40.root").data());
    ScanChain(chTTV, sample_strTTV, "outputs/plots", "outputs/mc");


    // Category TT_2l2nu
    TChain *chTT_2l2nu = new TChain("Events");
    std::string sample_strTT_2l2nu("2018_TT_2l2nu");
    chTT_2l2nu->Add((FILEDIR + "/2018/TT_2l2nu*291.root").data());
    ScanChain(chTT_2l2nu, sample_strTT_2l2nu, "outputs/plots", "outputs/mc");


}
