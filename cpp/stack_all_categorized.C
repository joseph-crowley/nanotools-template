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
rootFiles.push_back("outputs/data/hists_Data_Run2.root");

stackHists("njet", rootFiles, dirName);
//stackHists("met", rootFiles, dirName);
//stackHists("Ht", rootFiles, dirName);
//stackHists("lep1_pt", rootFiles, dirName);
//stackHists("lep2_pt", rootFiles, dirName);
////stackHists("lep1_eta", rootFiles, dirName);
////stackHists("lep1_phi", rootFiles, dirName);
////stackHists("lep2_eta", rootFiles, dirName);
////stackHists("lep2_phi", rootFiles, dirName);
//stackHists("pt_ll", rootFiles, dirName);
//stackHists("m_ll", rootFiles, dirName);
//stackHists("m_lb", rootFiles, dirName);
stackHists("m_bb", rootFiles, dirName);

}
