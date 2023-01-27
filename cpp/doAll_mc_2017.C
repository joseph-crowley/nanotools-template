{
    gROOT->ProcessLine(".L analyze_bjets.C+");
    std::string FILEDIR = "/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/2023_01_13_tt_bkg_MC";


    // Category Others
    TChain *chOthers = new TChain("Events");
    std::string sample_strOthers("2017_Others");
    chOthers->Add((FILEDIR + "/2017/DY_2l_M_10to50*40.root").data());
    chOthers->Add((FILEDIR + "/2017/DY_2l_M_50*282.root").data());
    chOthers->Add((FILEDIR + "/2017/GGH_ZZTo4L_POWHEG*2.root").data());
    chOthers->Add((FILEDIR + "/2017/TTGJets*7.root").data());
    chOthers->Add((FILEDIR + "/2017/TTHH*1.root").data());
    chOthers->Add((FILEDIR + "/2017/TTTJ*1.root").data());
    chOthers->Add((FILEDIR + "/2017/TTTW*1.root").data());
    chOthers->Add((FILEDIR + "/2017/TTWH*1.root").data());
    chOthers->Add((FILEDIR + "/2017/TTWW*2.root").data());
    chOthers->Add((FILEDIR + "/2017/TTWZ*1.root").data());
    chOthers->Add((FILEDIR + "/2017/TTZH*1.root").data());
    chOthers->Add((FILEDIR + "/2017/TTZZ*1.root").data());
    chOthers->Add((FILEDIR + "/2017/WJets_lnu_0j*172.root").data());
    chOthers->Add((FILEDIR + "/2017/WJets_lnu_1j*224.root").data());
    chOthers->Add((FILEDIR + "/2017/WJets_lnu_2j*133.root").data());
    chOthers->Add((FILEDIR + "/2017/WWG*4.root").data());
    chOthers->Add((FILEDIR + "/2017/WWW_4f*1.root").data());
    chOthers->Add((FILEDIR + "/2017/WWW_4f_ext*16.root").data());
    chOthers->Add((FILEDIR + "/2017/WZG*3.root").data());
    chOthers->Add((FILEDIR + "/2017/WZZ*1.root").data());
    chOthers->Add((FILEDIR + "/2017/WZZ_ext*16.root").data());
    chOthers->Add((FILEDIR + "/2017/ZZZ*1.root").data());
    chOthers->Add((FILEDIR + "/2017/ZZZ_ext*14.root").data());
    chOthers->Add((FILEDIR + "/2017/qqWG_lnu_lo*16.root").data());
    chOthers->Add((FILEDIR + "/2017/qqWG_lnu_nlo_01j*94.root").data());
    chOthers->Add((FILEDIR + "/2017/qqWZ_3lnu_MG*17.root").data());
    chOthers->Add((FILEDIR + "/2017/qqWZ_3lnu_POWHEG*4.root").data());
    chOthers->Add((FILEDIR + "/2017/qqZG_ll_01j*53.root").data());
    chOthers->Add((FILEDIR + "/2017/qqZZ_4l*140.root").data());
    ScanChain(chOthers, sample_strOthers, "outputs/plots", "outputs/mc");


    // Category TT_lnu
    TChain *chTT_lnu = new TChain("Events");
    std::string sample_strTT_lnu("2017_TT_lnu");
    chTT_lnu->Add((FILEDIR + "/2017/TT_lnu_nlo*693.root").data());
    ScanChain(chTT_lnu, sample_strTT_lnu, "outputs/plots", "outputs/mc");


    // Category WW
    TChain *chWW = new TChain("Events");
    std::string sample_strWW("2017_WW");
    chWW->Add((FILEDIR + "/2017/qqWW_2l2nu*12.root").data());
    ScanChain(chWW, sample_strWW, "outputs/plots", "outputs/mc");


    // Category ST_tW
    TChain *chST_tW = new TChain("Events");
    std::string sample_strST_tW("2017_ST_tW");
    chST_tW->Add((FILEDIR + "/2017/ST_tW_antitop_5f_NoFullyHadronicDecays*16.root").data());
    chST_tW->Add((FILEDIR + "/2017/ST_tW_top_5f_NoFullyHadronicDecays*16.root").data());
    ScanChain(chST_tW, sample_strST_tW, "outputs/plots", "outputs/mc");


    // Category TTV
    TChain *chTTV = new TChain("Events");
    std::string sample_strTTV("2017_TTV");
    chTTV->Add((FILEDIR + "/2017/TTH_HToNonBB*11.root").data());
    chTTV->Add((FILEDIR + "/2017/TTW_lnu*15.root").data());
    chTTV->Add((FILEDIR + "/2017/TTZ_2l2nu_M_10*29.root").data());
    ScanChain(chTTV, sample_strTTV, "outputs/plots", "outputs/mc");


    // Category TT_2l2nu
    TChain *chTT_2l2nu = new TChain("Events");
    std::string sample_strTT_2l2nu("2017_TT_2l2nu");
    chTT_2l2nu->Add((FILEDIR + "/2017/TT_2l2nu*214.root").data());
    ScanChain(chTT_2l2nu, sample_strTT_2l2nu, "outputs/plots", "outputs/mc");


}
