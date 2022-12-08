#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"
#include "TCanvas.h"

//#include "../NanoCORE/Nano.h"
//#include "../NanoCORE/Base.h"
//#include "../NanoCORE/SSSelections.cc"
//#include "../NanoCORE/MetSelections.cc"
#include "../NanoCORE/tqdm.h"

#include <iostream>
#include <iomanip>

#define SUM(vec) std::accumulate((vec).begin(), (vec).end(), 0);
#define SUM_GT(vec,num) std::accumulate((vec).begin(), (vec).end(), 0, [](float x,float y){return ((y > (num)) ? x+y : x); });
#define COUNT_GT(vec,num) std::count_if((vec).begin(), (vec).end(), [](float x) { return x > (num); });
#define COUNT_LT(vec,num) std::count_if((vec).begin(), (vec).end(), [](float x) { return x < (num); });

#define H1(name,nbins,low,high) TH1F *h_##name = new TH1F(#name,#name,nbins,low,high);

// #define DEBUG

struct debugger { template<typename T> debugger& operator , (const T& v) { cerr<<v<<" "; return *this; } } dbg;
#ifdef DEBUG
    #define debug(args...) do {cerr << #args << ": "; dbg,args; cerr << endl;} while(0)
#else
    #define debug(args...)
#endif

using namespace std;
//using namespace tas;

int ScanChain(TChain *ch, string sample_str) {

    string outfile_name = "output_";
    outfile_name += sample_str;
    outfile_name += ".root";

    TFile* f1 = new TFile(outfile_name.data(), "RECREATE");

    int const njet_nbin = 7;
    H1(njet,njet_nbin,0,njet_nbin);

    int nEventsTotal = 0;
    int nEventsChain = ch->GetEntries();
    TFile *currentFile = 0;
    TObjArray *listOfFiles = ch->GetListOfFiles();
    TIter fileIter(listOfFiles);
    tqdm bar;


    int event_wgt;
    ch->SetBranchAddress("event_wgt", &event_wgt);

    float event_weight_triggers_dilepton_matched;
    ch->SetBranchAddress("event_weight_triggers_dilepton_matched", &event_weight_triggers_dilepton_matched);

    int njet;
    ch->SetBranchAddress("njet", &njet);

    for (Long64_t event = 0; event < ch->GetEntries(); ++event){
            ch->GetEntry(event);

            nEventsTotal++;
            bar.progress(nEventsTotal, nEventsChain);

            //printf("%i\n", njet);
	    
            h_njet->Fill(njet-2, event_wgt + event_weight_triggers_dilepton_matched);

    } // Event loop



    // move overflow contents to last bin
    h_njet->SetBinContent(njet_nbin, h_njet->GetBinContent(njet_nbin+1) + h_njet->GetBinContent(njet_nbin));
    h_njet->SetBinError(njet_nbin, std::sqrt(std::pow(h_njet->GetBinError(njet_nbin+1),2) + std::pow(h_njet->GetBinError(njet_nbin),2)));

    // set overflow bin to 0
    h_njet->SetBinContent(njet_nbin+1, 0);
    h_njet->SetBinError(njet_nbin+1, 0);

    bar.finish();

    TCanvas *njetPlot = new TCanvas("njet","njet", 1000,800);
    njetPlot->cd();
    h_njet->GetXaxis()->SetTitle("n_{jet}");
    h_njet->GetYaxis()->SetTitle("Events");
    h_njet->Draw();
    njetPlot->SetLogy();

    string njetPlotName = "/home/users/crowley/public_html/tttt_jet_distribution_check/njet_";
    njetPlotName += sample_str;
    njetPlotName += ".pdf";
    njetPlot->SaveAs(njetPlotName.data());
    
    njetPlotName = "/home/users/crowley/public_html/tttt_jet_distribution_check/njet_";
    njetPlotName += sample_str;
    njetPlotName += ".png";
    njetPlot->SaveAs(njetPlotName.data());

    f1->Write();
    f1->Close();
    return 0;
}
