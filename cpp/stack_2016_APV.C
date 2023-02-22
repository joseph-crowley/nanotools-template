{
// set up output
 gROOT->ProcessLine(".L directory_tools.C+");
 std::string dirName = "/home/users/crowley/public_html/tttt/2023_02_21_analyze_bjets_stacked_2016_APV";
 directory_tools(dirName);
 std::cout << "Output directory: " << dirName << endl;

 // load the script
 gROOT->ProcessLine(".x loadLib.C");
 gROOT->ProcessLine(".L analyze_bjets.C+");

 // set up a directive to stack all the hists
#define STACK_HISTS \
 STACK_HIST("jetpt")\
 STACK_HIST("nbjet_loose")\
 STACK_HIST("nbjet_medium")\
 STACK_HIST("nbjet_tight")\
 STACK_HIST("bjetpt_loose")\
 STACK_HIST("bjetpt_medium")\
 STACK_HIST("bjetpt_tight")\
 STACK_HIST("njet_nb_lt2")\
 STACK_HIST("njet_nb_eq2")\
 STACK_HIST("njet_nb_gt2")\
 //STACK_HIST("met_nb_lt2")\
 //STACK_HIST("met_nb_eq2")\
 //STACK_HIST("met_nb_gt2")\
 //STACK_HIST("Ht_nb_lt2")\
 //STACK_HIST("Ht_nb_eq2")\
 //STACK_HIST("Ht_nb_gt2")\
 //STACK_HIST("lep1_pt_nb_lt2")\
 //STACK_HIST("lep1_pt_nb_eq2")\
 //STACK_HIST("lep1_pt_nb_gt2")\
 //STACK_HIST("lep1_eta_nb_lt2")\
 //STACK_HIST("lep1_eta_nb_eq2")\
 //STACK_HIST("lep1_eta_nb_gt2")\
 //STACK_HIST("lep1_phi_nb_lt2")\
 //STACK_HIST("lep1_phi_nb_eq2")\
 //STACK_HIST("lep1_phi_nb_gt2")\
 //STACK_HIST("lep2_pt_nb_lt2")\
 //STACK_HIST("lep2_pt_nb_eq2")\
 //STACK_HIST("lep2_pt_nb_gt2")\
 //STACK_HIST("lep2_eta_nb_lt2")\
 //STACK_HIST("lep2_eta_nb_eq2")\
 //STACK_HIST("lep2_eta_nb_gt2")\
 //STACK_HIST("lep2_phi_nb_lt2")\
 //STACK_HIST("lep2_phi_nb_eq2")\
 //STACK_HIST("lep2_phi_nb_gt2")\
 //STACK_HIST("pt_ll_nb_lt2")\
 //STACK_HIST("pt_ll_nb_eq2")\
 //STACK_HIST("pt_ll_nb_gt2")\
 //STACK_HIST("m_ll_nb_lt2")\
 //STACK_HIST("m_ll_nb_eq2")\
 //STACK_HIST("m_ll_nb_gt2")
 //STACK_HIST("m_lb_nb_lt2")\
 //STACK_HIST("m_lb_nb_eq2")\
 //STACK_HIST("m_lb_nb_gt2")\
 //STACK_HIST("m_bb_nb_eq2")\
 //STACK_HIST("m_bb_nb_gt2")

// vector<string> rootFiles_17_18;
// rootFiles_17_18.push_back("outputs/mc/hists_17_18_Others.root");
// rootFiles_17_18.push_back("outputs/mc/hists_17_18_ST_tW.root");     
// rootFiles_17_18.push_back("outputs/mc/hists_17_18_TTV.root");       
// rootFiles_17_18.push_back("outputs/mc/hists_17_18_TT_2l2nu.root");  
// rootFiles_17_18.push_back("outputs/mc/hists_17_18_TT_lnu.root");    
// rootFiles_17_18.push_back("outputs/mc/hists_17_18_WW.root");        
// rootFiles_17_18.push_back("outputs/data/hists_17_18_Data.root");
//
//#define STACK_HIST(name) stackHists(name, rootFiles_17_18, dirName);
//STACK_HISTS
//#undef STACK_HIST 

// vector<string> rootFiles_All;
// rootFiles_All.push_back("outputs/mc/hists_All_Others.root");
// rootFiles_All.push_back("outputs/mc/hists_All_ST_tW.root");     
// rootFiles_All.push_back("outputs/mc/hists_All_TTV.root");       
// rootFiles_All.push_back("outputs/mc/hists_All_TT_2l2nu.root");  
// rootFiles_All.push_back("outputs/mc/hists_All_TT_lnu.root");    
// rootFiles_All.push_back("outputs/mc/hists_All_WW.root");        
// rootFiles_All.push_back("outputs/data/hists_All_Data.root");
//
//#define STACK_HIST(name) stackHists(name, rootFiles_All, dirName);
//STACK_HISTS
//#undef STACK_HIST 

 vector<string> rootFiles_2016_APV;
 rootFiles_2016_APV.push_back("outputs/mc/hists_2016_APV_Others.root");
 rootFiles_2016_APV.push_back("outputs/mc/hists_2016_APV_ST_tW.root");     
 rootFiles_2016_APV.push_back("outputs/mc/hists_2016_APV_TTV.root");       
 rootFiles_2016_APV.push_back("outputs/mc/hists_2016_APV_TT_2l2nu.root");  
 rootFiles_2016_APV.push_back("outputs/mc/hists_2016_APV_TT_lnu.root");    
 rootFiles_2016_APV.push_back("outputs/mc/hists_2016_APV_WW.root");        
 rootFiles_2016_APV.push_back("outputs/data/hists_Data_2016_APV.root");

#define STACK_HIST(name) stackHists(name, rootFiles_2016_APV, dirName);
STACK_HISTS
#undef STACK_HIST 

// vector<string> rootFiles_2016_NonAPV;
// rootFiles_2016_NonAPV.push_back("outputs/mc/hists_2016_NonAPV_Others.root");
// rootFiles_2016_NonAPV.push_back("outputs/mc/hists_2016_NonAPV_ST_tW.root");     
// rootFiles_2016_NonAPV.push_back("outputs/mc/hists_2016_NonAPV_TTV.root");       
// rootFiles_2016_NonAPV.push_back("outputs/mc/hists_2016_NonAPV_TT_2l2nu.root");  
// rootFiles_2016_NonAPV.push_back("outputs/mc/hists_2016_NonAPV_TT_lnu.root");    
// rootFiles_2016_NonAPV.push_back("outputs/mc/hists_2016_NonAPV_WW.root");        
// rootFiles_2016_NonAPV.push_back("outputs/data/hists_Data_2016_NonAPV.root");
//
//#define STACK_HIST(name) stackHists(name, rootFiles_2016_NonAPV, dirName);
//STACK_HISTS
//#undef STACK_HIST 

// vector<string> rootFiles_2017;
// rootFiles_2017.push_back("outputs/mc/hists_2017_WW.root");
// rootFiles_2017.push_back("outputs/mc/hists_2017_TT_lnu.root");
// rootFiles_2017.push_back("outputs/mc/hists_2017_Others.root");           
// rootFiles_2017.push_back("outputs/mc/hists_2017_ST_tW.root");            
// rootFiles_2017.push_back("outputs/mc/hists_2017_TTV.root");              
// rootFiles_2017.push_back("outputs/mc/hists_2017_TT_2l2nu.root");
// rootFiles_2017.push_back("outputs/data/hists_Data_2017.root");
//
//#define STACK_HIST(name) stackHists(name, rootFiles_2017, dirName);
//STACK_HISTS
//#undef STACK_HIST 

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

