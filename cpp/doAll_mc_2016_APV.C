{
    gROOT->ProcessLine(".L analyze_bjets.C+");
    std::string FILEDIR = "/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/230214_tt_bkg_Cutbased";


    // Category TTV
    TChain *chTTV = new TChain("Events");
    std::string sample_strTTV("2016_APV_TTV");
    chTTV->Add((FILEDIR + "/2016_APV/TTH_HToNonBB*4.root").data());
    chTTV->Add((FILEDIR + "/2016_APV/TTW_lnu*6.root").data());
    chTTV->Add((FILEDIR + "/2016_APV/TTZ_2l2nu_M_10*12.root").data());
    ScanChain(chTTV, sample_strTTV, "outputs/plots", "outputs/mc");


    // Category TT_lnu
    TChain *chTT_lnu = new TChain("Events");
    std::string sample_strTT_lnu("2016_APV_TT_lnu");
    chTT_lnu->Add((FILEDIR + "/2016_APV/TT_lnu_nlo*265.root").data());
    ScanChain(chTT_lnu, sample_strTT_lnu, "outputs/plots", "outputs/mc");


    // Category TT_2l2nu
    TChain *chTT_2l2nu = new TChain("Events");
    std::string sample_strTT_2l2nu("2016_APV_TT_2l2nu");
    chTT_2l2nu->Add((FILEDIR + "/2016_APV/TT_2l2nu*76.root").data());
    ScanChain(chTT_2l2nu, sample_strTT_2l2nu, "outputs/plots", "outputs/mc");


    // Category ST_tW
    TChain *chST_tW = new TChain("Events");
    std::string sample_strST_tW("2016_APV_ST_tW");
    chST_tW->Add((FILEDIR + "/2016_APV/ST_tW_antitop_5f_NoFullyHadronicDecays*6.root").data());
    chST_tW->Add((FILEDIR + "/2016_APV/ST_tW_top_5f_NoFullyHadronicDecays*6.root").data());
    ScanChain(chST_tW, sample_strST_tW, "outputs/plots", "outputs/mc");


    // Category WW
    TChain *chWW = new TChain("Events");
    std::string sample_strWW("2016_APV_WW");
    chWW->Add((FILEDIR + "/2016_APV/qqWW_2l2nu*6.root").data());
    ScanChain(chWW, sample_strWW, "outputs/plots", "outputs/mc");


    // Category Others
    TChain *chOthers = new TChain("Events");
    std::string sample_strOthers("2016_APV_Others");
    chOthers->Add((FILEDIR + "/2016_APV/DY_2l_M_10to50*14.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/DY_2l_M_50*127.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/GGH_ZZTo4L_POWHEG*2.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTGJets*3.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTHH*1.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTTJ*1.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTTW*1.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTWH*1.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTWW*1.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTWZ*1.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTZH*1.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/TTZZ*1.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WJets_lnu_0j*145.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WJets_lnu_1j*218.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WJets_lnu_2j*122.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WWG*2.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WWW_4f*1.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WWW_4f_ext*9.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WZG*2.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WZZ*1.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/WZZ_ext*9.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/ZZZ*1.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/ZZZ_ext*8.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/qqWG_lnu_lo*14.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/qqWG_lnu_nlo_01j*83.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/qqWZ_3lnu_MG*15.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/qqWZ_3lnu_POWHEG*2.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/qqZG_ll_01j*41.root").data());
    chOthers->Add((FILEDIR + "/2016_APV/qqZZ_4l*68.root").data());
    ScanChain(chOthers, sample_strOthers, "outputs/plots", "outputs/mc");


}
