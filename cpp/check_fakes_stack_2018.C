{
// set up output
 gROOT->ProcessLine(".L directory_tools_C.so");
 std::string env_PLOTDIR = std::getenv("PLOTDIR");
 std::string PLOTDIR = env_PLOTDIR != nullptr ? env_PLOTDIR : "SPECIFY/PLOTDIR/AS/ENV/VARIABLE";
 std::string dirName = PLOTDIR + "_2018";
 directory_tools(dirName);
 std::cout << "Output directory: " << dirName << endl;

 // load the script
 gROOT->ProcessLine(".x loadLib.C");
 gROOT->ProcessLine(".L check_fakes_C.so");

 // set up a directive to stack all the hists
#define STACK_HISTS_BTAG_CATEGORIES \
 STACK_HIST("jetpt")\
 STACK_HIST("nbjet_loose")\
 STACK_HIST("nbjet_medium")\
 STACK_HIST("nbjet_tight")\
 STACK_HIST("bjetpt_loose")\
 STACK_HIST("bjetpt_medium")\
 STACK_HIST("bjetpt_tight")

#define STACK_HISTS_NB_CATEGORIES_LT2 \
 STACK_HIST("njet_nb_lt2")\
 STACK_HIST("m_ll_nb_lt2")\
 STACK_HIST("met_nb_lt2")\
 STACK_HIST("Ht_nb_lt2")\
 STACK_HIST("lep1_pt_nb_lt2")\
 STACK_HIST("lep1_eta_nb_lt2")\
 STACK_HIST("lep1_phi_nb_lt2")\
 STACK_HIST("lep2_pt_nb_lt2")\
 STACK_HIST("lep2_eta_nb_lt2")\
 STACK_HIST("lep2_phi_nb_lt2")\
 STACK_HIST("pt_ll_nb_lt2")\
 STACK_HIST("nPVs_nb_lt2")\
 STACK_HIST("nPVs_good_nb_lt2")\
 STACK_HIST("nleptons_fakeable_nb_lt2")\
 STACK_HIST("nleptons_loose_nb_lt2")\
 STACK_HIST("nelectrons_fakeable_nb_lt2")\
 STACK_HIST("nelectrons_loose_nb_lt2")\
 STACK_HIST("nmuons_fakeable_nb_lt2")\
 STACK_HIST("nmuons_loose_nb_lt2")\
 STACK_HIST("m_lb_nb_lt2") \
 STACK_HIST("m_bb_nb_lt2") \
 STACK_HIST("dR_bb_nb_lt2")


#define STACK_HISTS_NB_CATEGORIES_EQ0 \
 STACK_HIST("njet_nb_eq0")\
 STACK_HIST("m_ll_nb_eq0")\
 STACK_HIST("met_nb_eq0")\
 STACK_HIST("Ht_nb_eq0")\
 STACK_HIST("lep1_pt_nb_eq0")\
 STACK_HIST("lep1_eta_nb_eq0")\
 STACK_HIST("lep1_phi_nb_eq0")\
 STACK_HIST("lep2_pt_nb_eq0")\
 STACK_HIST("lep2_eta_nb_eq0")\
 STACK_HIST("lep2_phi_nb_eq0")\
 STACK_HIST("pt_ll_nb_eq0")\
 STACK_HIST("nPVs_nb_eq0")\
 STACK_HIST("nPVs_good_nb_eq0")\
 STACK_HIST("nleptons_fakeable_nb_eq0")\
 STACK_HIST("nleptons_loose_nb_eq0")\
 STACK_HIST("nelectrons_fakeable_nb_eq0")\
 STACK_HIST("nelectrons_loose_nb_eq0")\
 STACK_HIST("nmuons_fakeable_nb_eq0")\
 STACK_HIST("nmuons_loose_nb_eq0")\
 STACK_HIST("m_lb_nb_eq0") \
 STACK_HIST("m_bb_nb_eq0") \
 STACK_HIST("dR_bb_nb_eq0")

#define STACK_HISTS_NB_CATEGORIES_EQ1 \
 STACK_HIST("njet_nb_eq1")\
 STACK_HIST("m_ll_nb_eq1")\
 STACK_HIST("met_nb_eq1")\
 STACK_HIST("Ht_nb_eq1")\
 STACK_HIST("lep1_pt_nb_eq1")\
 STACK_HIST("lep1_eta_nb_eq1")\
 STACK_HIST("lep1_phi_nb_eq1")\
 STACK_HIST("lep2_pt_nb_eq1")\
 STACK_HIST("lep2_eta_nb_eq1")\
 STACK_HIST("lep2_phi_nb_eq1")\
 STACK_HIST("pt_ll_nb_eq1")\
 STACK_HIST("nPVs_nb_eq1")\
 STACK_HIST("nPVs_good_nb_eq1")\
 STACK_HIST("nleptons_fakeable_nb_eq1")\
 STACK_HIST("nleptons_loose_nb_eq1")\
 STACK_HIST("nelectrons_fakeable_nb_eq1")\
 STACK_HIST("nelectrons_loose_nb_eq1")\
 STACK_HIST("nmuons_fakeable_nb_eq1")\
 STACK_HIST("nmuons_loose_nb_eq1")\
 STACK_HIST("m_lb_nb_eq1") \
 STACK_HIST("m_bb_nb_eq1") \
 STACK_HIST("dR_bb_nb_eq1")

#define STACK_HISTS_NB_CATEGORIES_EQ2 \
 STACK_HIST("njet_nb_eq2")\
 STACK_HIST("m_ll_nb_eq2")\
 STACK_HIST("met_nb_eq2")\
 STACK_HIST("Ht_nb_eq2")\
 STACK_HIST("lep1_pt_nb_eq2")\
 STACK_HIST("lep1_eta_nb_eq2")\
 STACK_HIST("lep1_phi_nb_eq2")\
 STACK_HIST("lep2_pt_nb_eq2")\
 STACK_HIST("lep2_eta_nb_eq2")\
 STACK_HIST("lep2_phi_nb_eq2")\
 STACK_HIST("pt_ll_nb_eq2")\
 STACK_HIST("nPVs_nb_eq2")\
 STACK_HIST("nPVs_good_nb_eq2")\
 STACK_HIST("nleptons_fakeable_nb_eq2")\
 STACK_HIST("nleptons_loose_nb_eq2")\
 STACK_HIST("nelectrons_fakeable_nb_eq2")\
 STACK_HIST("nelectrons_loose_nb_eq2")\
 STACK_HIST("nmuons_fakeable_nb_eq2")\
 STACK_HIST("nmuons_loose_nb_eq2")\
 STACK_HIST("m_lb_nb_eq2") \
 STACK_HIST("m_bb_nb_eq2") \
 STACK_HIST("dR_bb_nb_eq2")


#define STACK_HISTS_NB_CATEGORIES_GT2 \
 STACK_HIST("njet_nb_gt2")\
 STACK_HIST("m_ll_nb_gt2")\
 STACK_HIST("met_nb_gt2")\
 STACK_HIST("Ht_nb_gt2")\
 STACK_HIST("lep1_pt_nb_gt2")\
 STACK_HIST("lep1_eta_nb_gt2")\
 STACK_HIST("lep1_phi_nb_gt2")\
 STACK_HIST("lep2_pt_nb_gt2")\
 STACK_HIST("lep2_eta_nb_gt2")\
 STACK_HIST("lep2_phi_nb_gt2")\
 STACK_HIST("pt_ll_nb_gt2")\
 STACK_HIST("nPVs_nb_gt2")\
 STACK_HIST("nPVs_good_nb_gt2")\
 STACK_HIST("nleptons_fakeable_nb_gt2")\
 STACK_HIST("nleptons_loose_nb_gt2")\
 STACK_HIST("nelectrons_fakeable_nb_gt2")\
 STACK_HIST("nelectrons_loose_nb_gt2")\
 STACK_HIST("nmuons_fakeable_nb_gt2")\
 STACK_HIST("nmuons_loose_nb_gt2")\
 STACK_HIST("m_lb_nb_gt2") \
 STACK_HIST("m_bb_nb_gt2") \
 STACK_HIST("dR_bb_nb_gt2")
 

 vector<string> rootFiles_2018;
 rootFiles_2018.push_back("outputs/mc/hists_all_real_b.root");
 rootFiles_2018.push_back("outputs/mc/hists_1c_1j.root");
 rootFiles_2018.push_back("outputs/mc/hists_1c_0j.root");
 rootFiles_2018.push_back("outputs/mc/hists_0c_1j.root");
 rootFiles_2018.push_back("outputs/data/hists_Data_2018.root");

#define STACK_HIST(name) stackHists(name, rootFiles_2018, dirName);
STACK_HISTS_BTAG_CATEGORIES
STACK_HISTS_NB_CATEGORIES_LT2
STACK_HISTS_NB_CATEGORIES_EQ0
STACK_HISTS_NB_CATEGORIES_EQ1
STACK_HISTS_NB_CATEGORIES_EQ2
STACK_HISTS_NB_CATEGORIES_GT2
#undef STACK_HIST 


#undef STACK_HISTS
}

