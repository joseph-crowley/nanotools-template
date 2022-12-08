{

    gROOT->ProcessLine(".L analyze_bjets.C+");
    TChain *ch = new TChain("Events");


    // **********************************************************************************
    // MC-Run2 
    // **********************************************************************************

    // TT_2l2nu
    TChain *chTT_2l2nu = new TChain("Events");
    std::string sample_strTT_2l2nu("TT_2l2nu");

    chTT_2l2nu->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/TT_2l2nu*.root");
    chTT_2l2nu->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/TT_2l2nu*.root");
    chTT_2l2nu->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/TT_2l2nu*.root");
    chTT_2l2nu->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/TT_2l2nu*.root");

    ScanChain(chTT_2l2nu, sample_strTT_2l2nu);

    // TT_lnu
    TChain *chTT_lnu = new TChain("Events");
    std::string sample_strTT_lnu("TT_lnu");

    chTT_lnu->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/TT_lnu*.root");
    chTT_lnu->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/TT_lnu*.root");
    chTT_lnu->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/TT_lnu*.root");
    chTT_lnu->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/TT_lnu*.root");

    ScanChain(chTT_lnu, sample_strTT_lnu);

    // TTV
    TChain *chTTV = new TChain("Events");
    std::string sample_strTTV("TTV");

    chTTV->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/TTZ*.root");
    chTTV->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/TTZ*.root");
    chTTV->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/TTZ*.root");
    chTTV->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/TTZ*.root");

    chTTV->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/TTW*.root");
    chTTV->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/TTW*.root");
    chTTV->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/TTW*.root");
    chTTV->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/TTW*.root");

    chTTV->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/TTH*.root");
    chTTV->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/TTH*.root");
    chTTV->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/TTH*.root");
    chTTV->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/TTH*.root");

    ScanChain(chTTV, sample_strTTV);

    // Single Top + tW 
    TChain *chST_tW = new TChain("Events");
    std::string sample_strST_tW("ST_tW");

    chST_tW->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/ST*.root");
    chST_tW->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/ST*.root");
    chST_tW->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/ST*.root");
    chST_tW->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/ST*.root");

    ScanChain(chST_tW, sample_strST_tW);

    // Others ()
    TChain *chOthers = new TChain("Events");
    std::string sample_strOthers("Others");

    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WJets_lnu_0j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WJets_lnu_1j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WJets_lnu_2j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WJets_lnu_0j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WJets_lnu_1j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WJets_lnu_2j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WJets_lnu_0j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WJets_lnu_1j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WJets_lnu_2j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WJets_lnu_0j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WJets_lnu_1j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WJets_lnu_2j*.root");

    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/qqWG_lnu_nlo_01j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/qqWG_lnu_nlo_01j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/qqWG_lnu_nlo_01j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/qqWG_lnu_nlo_01j*.root");

    // Added using python script, may want to take a closer look 
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/DY_2l_M_10to50*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/DY_2l_M_10to50*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/DY_2l_M_10to50*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/DY_2l_M_10to50*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/DY_2l_M_50*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/DY_2l_M_50*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/DY_2l_M_50*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/DY_2l_M_50*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/GGH_ZZTo4L_POWHEG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/GGH_ZZTo4L_POWHEG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/GGH_ZZTo4L_POWHEG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/GGH_ZZTo4L_POWHEG*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/TTGJets_ext*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/TTGJets_ext*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/TTGJets_ext*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/TTGJets_ext*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/TTG_2l2nu*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/TTG_2l2nu*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/TTG_2l2nu*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/TTG_2l2nu*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/TTG_lnu*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/TTG_lnu*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/TTG_lnu*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/TTG_lnu*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/TTJets*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/TTJets*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/TTJets*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/TTJets*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/TTTJ*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/TTTJ*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/TTTJ*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/TTTJ*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/TTTT*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/TTTT*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/TTTT*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/TTTT*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WJets_lnu_HT_100-200*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WJets_lnu_HT_100-200*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WJets_lnu_HT_100-200*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WJets_lnu_HT_100-200*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WJets_lnu_HT_1200-2500*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WJets_lnu_HT_1200-2500*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WJets_lnu_HT_1200-2500*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WJets_lnu_HT_1200-2500*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WJets_lnu_HT_200-400*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WJets_lnu_HT_200-400*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WJets_lnu_HT_200-400*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WJets_lnu_HT_200-400*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WJets_lnu_HT_2500-inf*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WJets_lnu_HT_2500-inf*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WJets_lnu_HT_2500-inf*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WJets_lnu_HT_2500-inf*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WJets_lnu_HT_400-600*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WJets_lnu_HT_400-600*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WJets_lnu_HT_400-600*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WJets_lnu_HT_400-600*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WJets_lnu_HT_600-800*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WJets_lnu_HT_600-800*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WJets_lnu_HT_600-800*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WJets_lnu_HT_600-800*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WJets_lnu_HT_70-100*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WJets_lnu_HT_70-100*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WJets_lnu_HT_70-100*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WJets_lnu_HT_70-100*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WJets_lnu_HT_800-1200*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WJets_lnu_HT_800-1200*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WJets_lnu_HT_800-1200*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WJets_lnu_HT_800-1200*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WJets_lnu_lo*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WJets_lnu_lo*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WJets_lnu_lo*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WJets_lnu_lo*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WWG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WWG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WWG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WWG*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WWW_4f_ext*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WWW_4f_ext*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WWW_4f_ext*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WWW_4f_ext*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WZG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WZG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WZG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WZG*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/WZZ_ext*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/WZZ_ext*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/WZZ_ext*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/WZZ_ext*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/ZZZ_ext*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/ZZZ_ext*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/ZZZ_ext*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/ZZZ_ext*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/qqWG_lnu_lo*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/qqWG_lnu_lo*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/qqWG_lnu_lo*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/qqWG_lnu_lo*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/qqWG_lnu_nlo_01j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/qqWG_lnu_nlo_01j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/qqWG_lnu_nlo_01j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/qqWG_lnu_nlo_01j*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/qqWW_2l2nu*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/qqWW_2l2nu*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/qqWW_2l2nu*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/qqWW_2l2nu*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/qqWZ_3lnu_MG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/qqWZ_3lnu_MG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/qqWZ_3lnu_MG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/qqWZ_3lnu_MG*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/qqWZ_3lnu_POWHEG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/qqWZ_3lnu_POWHEG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/qqWZ_3lnu_POWHEG*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/qqWZ_3lnu_POWHEG*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/qqWZ_3lnu_POWHEG_mll_0p1-inf*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/qqWZ_3lnu_POWHEG_mll_0p1-inf*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/qqWZ_3lnu_POWHEG_mll_0p1-inf*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/qqWZ_3lnu_POWHEG_mll_0p1-inf*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/qqZG_ll_01j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/qqZG_ll_01j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/qqZG_ll_01j*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/qqZG_ll_01j*.root");
    
    
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016NonAPV/qqZZ_4l*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2016APV/qqZZ_4l*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2017/qqZZ_4l*.root");
    chOthers->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg_MC/2018/qqZZ_4l*.root");

    ScanChain(chOthers, sample_strOthers);
  
}
