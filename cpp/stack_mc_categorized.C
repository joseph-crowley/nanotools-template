{
gROOT->ProcessLine(".L analyze_bjets.C+");


std::string plotDir("/home/users/crowley/public_html/test");
vector<string> rootFiles;
rootFiles.push_back("outputs/mc/output_Others.root");
rootFiles.push_back("outputs/mc/output_WW.root");
rootFiles.push_back("outputs/mc/output_ST_tW.root");
rootFiles.push_back("outputs/mc/output_TTV.root");
rootFiles.push_back("outputs/mc/output_TT_lnu.root");
rootFiles.push_back("outputs/mc/output_TT_2l2nu.root");

stackHists("njet", rootFiles, plotDir.data());
stackHists("Ht", rootFiles, plotDir.data());
stackHists("met", rootFiles, plotDir.data());


}
