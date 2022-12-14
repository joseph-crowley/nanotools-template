{
gROOT->ProcessLine(".L analyze_bjets.C+");


std::string plotDir("/home/users/crowley/public_html/test");
vector<string> rootFiles;
rootFiles.push_back("outputs/mc/hists_Others.root");
rootFiles.push_back("outputs/mc/hists_WW.root");
rootFiles.push_back("outputs/mc/hists_ST_tW.root");
rootFiles.push_back("outputs/mc/hists_TTV.root");
rootFiles.push_back("outputs/mc/hists_TT_lnu.root");
rootFiles.push_back("outputs/mc/hists_TT_2l2nu.root");
rootFiles.push_back("outputs/data/hists_Data_Run2.root");

stackHists("njet", rootFiles, plotDir.data());
stackHists("met", rootFiles, plotDir.data());
stackHists("Ht", rootFiles, plotDir.data());
stackHists("lep1_pt", rootFiles, plotDir.data());
stackHists("lep1_eta", rootFiles, plotDir.data());
stackHists("lep1_phi", rootFiles, plotDir.data());
stackHists("lep2_pt", rootFiles, plotDir.data());
stackHists("lep2_eta", rootFiles, plotDir.data());
stackHists("lep2_phi", rootFiles, plotDir.data());

}
