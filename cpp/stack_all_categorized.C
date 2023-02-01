{
// set up output
 gROOT->ProcessLine(".L directory_tools.C+");
 std::string dirName = directory_tools();
 std::cout << "Output directory: " << dirName << endl;

 // load the script
 gROOT->ProcessLine(".x loadLib.C");
 gROOT->ProcessLine(".L analyze_bjets.C+");

 // set up a directive to stack all the hists
#define STACK_HISTS \
 STACK_HIST("nbjet")\
 STACK_HIST("njet_nb_lt2")\
 STACK_HIST("njet_nb_eq2")\
 STACK_HIST("njet_nb_gt2")\
 STACK_HIST("met_nb_lt2")\
 STACK_HIST("met_nb_eq2")\
 STACK_HIST("met_nb_gt2")\
 STACK_HIST("Ht_nb_lt2")\
 STACK_HIST("Ht_nb_eq2")\
 STACK_HIST("Ht_nb_gt2")\
 STACK_HIST("lep1_pt_nb_lt2")\
 STACK_HIST("lep1_pt_nb_eq2")\
 STACK_HIST("lep1_pt_nb_gt2")\
 STACK_HIST("lep1_eta_nb_lt2")\
 STACK_HIST("lep1_eta_nb_eq2")\
 STACK_HIST("lep1_eta_nb_gt2")\
 STACK_HIST("lep1_phi_nb_lt2")\
 STACK_HIST("lep1_phi_nb_eq2")\
 STACK_HIST("lep1_phi_nb_gt2")\
 STACK_HIST("lep2_pt_nb_lt2")\
 STACK_HIST("lep2_pt_nb_eq2")\
 STACK_HIST("lep2_pt_nb_gt2")\
 STACK_HIST("lep2_eta_nb_lt2")\
 STACK_HIST("lep2_eta_nb_eq2")\
 STACK_HIST("lep2_eta_nb_gt2")\
 STACK_HIST("lep2_phi_nb_lt2")\
 STACK_HIST("lep2_phi_nb_eq2")\
 STACK_HIST("lep2_phi_nb_gt2")\
 STACK_HIST("pt_ll_nb_lt2")\
 STACK_HIST("pt_ll_nb_eq2")\
 STACK_HIST("pt_ll_nb_gt2")\
 STACK_HIST("m_ll_nb_lt2")\
 STACK_HIST("m_ll_nb_eq2")\
 STACK_HIST("m_ll_nb_gt2")\
 STACK_HIST("m_lb_nb_lt2")\
 STACK_HIST("m_lb_nb_eq2")\
 STACK_HIST("m_lb_nb_gt2")\
 STACK_HIST("m_bb_nb_lt2")\
 STACK_HIST("m_bb_nb_eq2")\
 STACK_HIST("m_bb_nb_gt2")

// vector<string> rootFiles_2016;
// rootFiles_2016.push_back("outputs/mc/hists_2016_NonAPV_Others.root");
// rootFiles_2016.push_back("outputs/mc/hists_2016_NonAPV_ST_tW.root");     
// rootFiles_2016.push_back("outputs/mc/hists_2016_NonAPV_TTV.root");       
// rootFiles_2016.push_back("outputs/mc/hists_2016_NonAPV_TT_2l2nu.root");  
// rootFiles_2016.push_back("outputs/mc/hists_2016_NonAPV_TT_lnu.root");    
// rootFiles_2016.push_back("outputs/mc/hists_2016_NonAPV_WW.root");        
// rootFiles_2016.push_back("outputs/data/hists_Data_2016.root");
//
//#define STACK_HIST(name) stackHists(name, rootFiles_2016, dirName);
//STACK_HISTS
//#undef STACK_HIST 

 vector<string> rootFiles_2017;
 rootFiles_2017.push_back("outputs/mc/hists_2017_WW.root");
 rootFiles_2017.push_back("outputs/mc/hists_2017_TT_lnu.root");
 rootFiles_2017.push_back("outputs/mc/hists_2017_Others.root");           
 rootFiles_2017.push_back("outputs/mc/hists_2017_ST_tW.root");            
 rootFiles_2017.push_back("outputs/mc/hists_2017_TTV.root");              
 rootFiles_2017.push_back("outputs/mc/hists_2017_TT_2l2nu.root");
 rootFiles_2017.push_back("outputs/data/hists_Data_2017.root");

#define STACK_HIST(name) stackHists(name, rootFiles_2017, dirName);
STACK_HISTS
#undef STACK_HIST 

// vector<string> rootFiles_2018;
// rootFiles_2018.push_back("outputs/mc/hists_2018_TTV.root");
// rootFiles_2018.push_back("outputs/mc/hists_2018_Others.root");
// rootFiles_2018.push_back("outputs/mc/hists_2018_ST_tW.root");
// rootFiles_2018.push_back("outputs/mc/hists_2018_TT_2l2nu.root");
// rootFiles_2018.push_back("outputs/mc/hists_2018_TT_lnu.root");
// rootFiles_2018.push_back("outputs/mc/hists_2018_WW.root");
// rootFiles_2018.push_back("outputs/data/hists_Data_2018.root");
//
//#define STACK_HIST(name) stackHists(name, rootFiles_2018, dirName);
//STACK_HISTS
//#undef STACK_HIST 


#undef STACK_HISTS
}

