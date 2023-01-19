{
// set up output
gROOT->ProcessLine(".L directory_tools.C+");
std::string dirName = directory_tools();
std::cout << "Output directory: " << dirName << endl;

// load the script
gROOT->ProcessLine(".x loadLib.C");
gROOT->ProcessLine(".L analyze_bjets.C+");

vector<string> rootFiles;
rootFiles.push_back("outputs/mc/hists_TT_2l2nu.root");
rootFiles.push_back("outputs/mc/hists_TT_lnu.root");
rootFiles.push_back("outputs/mc/hists_TTV.root");
rootFiles.push_back("outputs/mc/hists_ST_tW.root");
rootFiles.push_back("outputs/mc/hists_WW.root");
rootFiles.push_back("outputs/mc/hists_Others.root");
//rootFiles.push_back("outputs/data/hists_Data_Run2.root");

stackHists("nbjet", rootFiles, dirName);
stackHists("njet_nb_lt2", rootFiles, dirName);
stackHists("njet_nb_eq2", rootFiles, dirName);
stackHists("njet_nb_gt2", rootFiles, dirName);
stackHists("met_nb_lt2", rootFiles, dirName);
stackHists("met_nb_eq2", rootFiles, dirName);
stackHists("met_nb_gt2", rootFiles, dirName);
stackHists("Ht_nb_lt2", rootFiles, dirName);
stackHists("Ht_nb_eq2", rootFiles, dirName);
stackHists("Ht_nb_gt2", rootFiles, dirName);
stackHists("lep1_pt_nb_lt2", rootFiles, dirName);
stackHists("lep1_pt_nb_eq2", rootFiles, dirName);
stackHists("lep1_pt_nb_gt2", rootFiles, dirName);
stackHists("lep1_eta_nb_lt2", rootFiles, dirName);
stackHists("lep1_eta_nb_eq2", rootFiles, dirName);
stackHists("lep1_eta_nb_gt2", rootFiles, dirName);
stackHists("lep1_phi_nb_lt2", rootFiles, dirName);
stackHists("lep1_phi_nb_eq2", rootFiles, dirName);
stackHists("lep1_phi_nb_gt2", rootFiles, dirName);
stackHists("lep2_pt_nb_lt2", rootFiles, dirName);
stackHists("lep2_pt_nb_eq2", rootFiles, dirName);
stackHists("lep2_pt_nb_gt2", rootFiles, dirName);
stackHists("lep2_eta_nb_lt2", rootFiles, dirName);
stackHists("lep2_eta_nb_eq2", rootFiles, dirName);
stackHists("lep2_eta_nb_gt2", rootFiles, dirName);
stackHists("lep2_phi_nb_lt2", rootFiles, dirName);
stackHists("lep2_phi_nb_eq2", rootFiles, dirName);
stackHists("lep2_phi_nb_gt2", rootFiles, dirName);
stackHists("pt_ll_nb_lt2", rootFiles, dirName);
stackHists("pt_ll_nb_eq2", rootFiles, dirName);
stackHists("pt_ll_nb_gt2", rootFiles, dirName);
stackHists("m_ll_nb_lt2", rootFiles, dirName);
stackHists("m_ll_nb_eq2", rootFiles, dirName);
stackHists("m_ll_nb_gt2", rootFiles, dirName);
stackHists("m_lb_nb_lt2", rootFiles, dirName);
stackHists("m_lb_nb_eq2", rootFiles, dirName);
stackHists("m_lb_nb_gt2", rootFiles, dirName);
stackHists("m_bb_nb_lt2", rootFiles, dirName);
stackHists("m_bb_nb_eq2", rootFiles, dirName);
stackHists("m_bb_nb_gt2", rootFiles, dirName);

}
