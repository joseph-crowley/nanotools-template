{

    gROOT->ProcessLine(".L analyze_bjets.C+");
    TChain *ch = new TChain("Events");

  //  // **********************************************************************************
  //  // Data-Run3 
  //  // **********************************************************************************
  //  
  //TChain *ch1 = new TChain("Events");

  //std::string sample_str1("data_Run3");
  ////ch1->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg/2022C/Run2022C_59_of_102.root");
  //ch1->Add("/ceph/cms/store/group/tttt/Worker/crowley/output/Analysis_FakeRates/221130_tt_bkg/2022C/*.root");
  //ScanChain(ch1, sample_str1);

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

    ScanChain(chOthers, sample_strOthers);
  
}
