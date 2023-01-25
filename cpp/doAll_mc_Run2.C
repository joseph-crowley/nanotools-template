{
    gROOT->ProcessLine(".L analyze_bjets.C+");
    std::string FILEDIR = "/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_TTJetRadiation/2023_01_13_tt_bkg_MC";

    // Category Others
    TChain *chOthers = new TChain("Events");
    std::string sample_strOthers("Others");
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
    chOthers->Add((FILEDIR + "/2016_NonAPV/DY_2l_M_10to50*11.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/DY_2l_M_50*94.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WJets_lnu_0j*157.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WJets_lnu_1j*212.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WJets_lnu_2j*120.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WWW_4f_ext*7.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/WZZ_ext*8.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/ZZZ_ext*7.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqWG_lnu_lo*5.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqWG_lnu_nlo_01j*87.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqWZ_3lnu_MG*17.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqZG_ll_01j*53.root").data());
    chOthers->Add((FILEDIR + "/2016_NonAPV/qqZZ_4l*72.root").data());
    chOthers->Add((FILEDIR + "/2017/DY_2l_M_10to50*40.root").data());
    chOthers->Add((FILEDIR + "/2017/DY_2l_M_50*282.root").data());
    chOthers->Add((FILEDIR + "/2017/TTGJets*7.root").data());
    chOthers->Add((FILEDIR + "/2017/TTWW*2.root").data());
    chOthers->Add((FILEDIR + "/2017/WJets_lnu_0j*172.root").data());
    chOthers->Add((FILEDIR + "/2017/WJets_lnu_1j*224.root").data());
    chOthers->Add((FILEDIR + "/2017/WJets_lnu_2j*133.root").data());
    chOthers->Add((FILEDIR + "/2017/WWG*4.root").data());
    chOthers->Add((FILEDIR + "/2017/WWW_4f_ext*16.root").data());
    chOthers->Add((FILEDIR + "/2017/WZG*3.root").data());
    chOthers->Add((FILEDIR + "/2017/WZZ_ext*16.root").data());
    chOthers->Add((FILEDIR + "/2017/ZZZ_ext*14.root").data());
    chOthers->Add((FILEDIR + "/2017/qqWG_lnu_lo*16.root").data());
    chOthers->Add((FILEDIR + "/2017/qqWG_lnu_nlo_01j*94.root").data());
    chOthers->Add((FILEDIR + "/2017/qqWZ_3lnu_POWHEG*4.root").data());
    chOthers->Add((FILEDIR + "/2017/qqZZ_4l*140.root").data());
    chOthers->Add((FILEDIR + "/2018/DY_2l_M_10to50*57.root").data());
    chOthers->Add((FILEDIR + "/2018/DY_2l_M_50*283.root").data());
    chOthers->Add((FILEDIR + "/2018/TTGJets*8.root").data());
    chOthers->Add((FILEDIR + "/2018/TTGJets_ext*11.root").data());
    chOthers->Add((FILEDIR + "/2018/WJets_lnu_0j*175.root").data());
    chOthers->Add((FILEDIR + "/2018/WJets_lnu_1j*232.root").data());
    chOthers->Add((FILEDIR + "/2018/WJets_lnu_2j*131.root").data());
    chOthers->Add((FILEDIR + "/2018/WWG*5.root").data());
    chOthers->Add((FILEDIR + "/2018/WZG*4.root").data());
    chOthers->Add((FILEDIR + "/2018/qqWG_lnu_lo*15.root").data());
    chOthers->Add((FILEDIR + "/2018/qqWG_lnu_nlo_01j*96.root").data());
    chOthers->Add((FILEDIR + "/2018/qqWZ_3lnu_MG*16.root").data());
    chOthers->Add((FILEDIR + "/2018/qqZZ_4l*139.root").data());
    ScanChain(chOthers, sample_strOthers, "outputs/plots", "outputs/mc");



    // Category ST_tW
    TChain *chST_tW = new TChain("Events");
    std::string sample_strST_tW("ST_tW");
    chST_tW->Add((FILEDIR + "/2016_APV/ST_tW_antitop_5f_NoFullyHadronicDecays*6.root").data());
    chST_tW->Add((FILEDIR + "/2016_APV/ST_tW_top_5f_NoFullyHadronicDecays*6.root").data());
    chST_tW->Add((FILEDIR + "/2016_NonAPV/ST_tW_antitop_5f_NoFullyHadronicDecays*7.root").data());
    chST_tW->Add((FILEDIR + "/2016_NonAPV/ST_tW_top_5f_NoFullyHadronicDecays*7.root").data());
    chST_tW->Add((FILEDIR + "/2017/ST_tW_antitop_5f_NoFullyHadronicDecays*16.root").data());
    chST_tW->Add((FILEDIR + "/2017/ST_tW_top_5f_NoFullyHadronicDecays*16.root").data());
    chST_tW->Add((FILEDIR + "/2018/ST_tW_antitop_5f_NoFullyHadronicDecays*20.root").data());
    chST_tW->Add((FILEDIR + "/2018/ST_tW_top_5f_NoFullyHadronicDecays*21.root").data());
    ScanChain(chST_tW, sample_strST_tW, "outputs/plots", "outputs/mc");



    // Category TTV
    TChain *chTTV = new TChain("Events");
    std::string sample_strTTV("TTV");
    chTTV->Add((FILEDIR + "/2016_APV/TTH_HToNonBB*4.root").data());
    chTTV->Add((FILEDIR + "/2016_APV/TTW_lnu*6.root").data());
    chTTV->Add((FILEDIR + "/2016_APV/TTZ_2l2nu_M_10*12.root").data());
    chTTV->Add((FILEDIR + "/2016_NonAPV/TTH_HToNonBB*5.root").data());
    chTTV->Add((FILEDIR + "/2016_NonAPV/TTW_lnu*7.root").data());
    chTTV->Add((FILEDIR + "/2016_NonAPV/TTZ_2l2nu_M_10*13.root").data());
    chTTV->Add((FILEDIR + "/2017/TTH_HToNonBB*11.root").data());
    chTTV->Add((FILEDIR + "/2017/TTW_lnu*15.root").data());
    chTTV->Add((FILEDIR + "/2017/TTZ_2l2nu_M_10*29.root").data());
    chTTV->Add((FILEDIR + "/2018/TTH_HToNonBB*15.root").data());
    chTTV->Add((FILEDIR + "/2018/TTW_lnu*21.root").data());
    chTTV->Add((FILEDIR + "/2018/TTZ_2l2nu_M_10*40.root").data());
    ScanChain(chTTV, sample_strTTV, "outputs/plots", "outputs/mc");



    // Category TT_2l2nu
    TChain *chTT_2l2nu = new TChain("Events");
    std::string sample_strTT_2l2nu("TT_2l2nu");
    chTT_2l2nu->Add((FILEDIR + "/2016_APV/TT_2l2nu*76.root").data());
    chTT_2l2nu->Add((FILEDIR + "/2016_NonAPV/TT_2l2nu*88.root").data());
    chTT_2l2nu->Add((FILEDIR + "/2017/TT_2l2nu*214.root").data());
    chTT_2l2nu->Add((FILEDIR + "/2018/TT_2l2nu*291.root").data());
    ScanChain(chTT_2l2nu, sample_strTT_2l2nu, "outputs/plots", "outputs/mc");



    // Category TT_lnu
    TChain *chTT_lnu = new TChain("Events");
    std::string sample_strTT_lnu("TT_lnu");
    chTT_lnu->Add((FILEDIR + "/2016_APV/TT_lnu_nlo*265.root").data());
    chTT_lnu->Add((FILEDIR + "/2016_NonAPV/TT_lnu_nlo*290.root").data());
    chTT_lnu->Add((FILEDIR + "/2017/TT_lnu_nlo*693.root").data());
    chTT_lnu->Add((FILEDIR + "/2018/TT_lnu_nlo*953.root").data());
    ScanChain(chTT_lnu, sample_strTT_lnu, "outputs/plots", "outputs/mc");



    // Category WW
    TChain *chWW = new TChain("Events");
    std::string sample_strWW("WW");
    chWW->Add((FILEDIR + "/2016_APV/qqWW_2l2nu*6.root").data());
    chWW->Add((FILEDIR + "/2016_NonAPV/qqWW_2l2nu*5.root").data());
    chWW->Add((FILEDIR + "/2017/qqWW_2l2nu*12.root").data());
    chWW->Add((FILEDIR + "/2018/qqWW_2l2nu*17.root").data());
    ScanChain(chWW, sample_strWW, "outputs/plots", "outputs/mc");


}
