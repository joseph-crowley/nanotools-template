{
    // Data
    gROOT->ProcessLine(".x doAll_data_NonAPV_2016.C");
    gROOT->ProcessLine(".x doAll_data_APV_2016.C");
    gROOT->ProcessLine(".x doAll_data_2017.C");
    gROOT->ProcessLine(".x doAll_data_2018.C");

    // MC
    gROOT->ProcessLine(".x doAll_mc_2016_NonAPV.C");
    gROOT->ProcessLine(".x doAll_mc_2016_APV.C");
    gROOT->ProcessLine(".x doAll_mc_2017.C");
    gROOT->ProcessLine(".x doAll_mc_2018.C");

    // plotting
    gROOT->ProcessLine(".x stack_2016_NonAPV.C");
    gROOT->ProcessLine(".x stack_2016_APV.C");
    gROOT->ProcessLine(".x stack_2017.C");
    gROOT->ProcessLine(".x stack_2018.C");
    gROOT->ProcessLine(".x stack_17_18.C");
}
