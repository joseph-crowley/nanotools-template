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
 gROOT->ProcessLine(".L check_Z_C.so");

 vector<string> rootFiles_2018;
 rootFiles_2018.push_back("outputs/data/hists_Data_2018.root");
 rootFiles_2018.push_back("outputs/mc/hists_all_mc.root");

 makeRatioPlot("h_nleptons_loose", rootFiles_2018, dirName);
 makeRatioPlot("h_nleptons_fakeable", rootFiles_2018, dirName);
 makeRatioPlot("h_nmuons_loose", rootFiles_2018, dirName);
 makeRatioPlot("h_nmuons_fakeable", rootFiles_2018, dirName);
 makeRatioPlot("h_nelectrons_loose", rootFiles_2018, dirName);
 makeRatioPlot("h_nelectrons_fakeable", rootFiles_2018, dirName);
 makeRatioPlot("h_mll_os", rootFiles_2018, dirName);
 makeRatioPlot("h_mll_os_ee", rootFiles_2018, dirName);
 makeRatioPlot("h_mll_os_mm", rootFiles_2018, dirName);
 makeRatioPlot("h_mll_os_em", rootFiles_2018, dirName);

}

