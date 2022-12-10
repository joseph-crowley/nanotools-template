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
    int nEventsTotal = 0;
    int nEventsChain = ch->GetEntries();
    TFile *currentFile = 0;
    TObjArray *listOfFiles = ch->GetListOfFiles();
    TIter fileIter(listOfFiles);
    tqdm bar;

    // make weighted histograms of: 
    /* njet 
     * met
     * Ht for all jets, bjets, and non-bjets
    */

    std::cout << "1" << endl;
    int const njet_nbin = 7;
    H1(njet,njet_nbin,0,njet_nbin);
    std::cout << "2" << endl;

    //int const met_nbin = 100;
    //H1(met,met_nbin,0,1000);

    int const Ht_nbin = 100;
    H1(Ht,Ht_nbin,0,1000);

    // set up branches

    double event_wgt;
    ch->SetBranchAddress("event_wgt", &event_wgt);

    float event_weight_triggers_dilepton_matched;
    ch->SetBranchAddress("event_weight_triggers_dilepton_matched", &event_weight_triggers_dilepton_matched);

    unsigned int njet;
    ch->SetBranchAddress("njet", &njet);
    std::cout << "3" << endl;

    unsigned int nbjet;
    ch->SetBranchAddress("nbjet", &nbjet);
    std::cout << "4" << endl;

    double PFMET_pt_final;
    ch->SetBranchAddress("PFMET_pt_final", &PFMET_pt_final);
    std::cout << "5" << endl;

    std::vector<float> *jet_pt = 0;
    ch->SetBranchAddress("jet_pt", &jet_pt);
    std::cout << "6" << endl;

    std::vector<bool> *jet_is_btagged = 0;
    ch->SetBranchAddress("jet_is_btagged", &jet_is_btagged);
    std::cout << "7" << endl;

    // Event loop
    for (Long64_t event = 0; event < ch->GetEntries(); ++event){
    std::cout << "8" << endl;
            ch->GetEntry(event);
            std::cout << "9" << endl;

            // progress bar
            nEventsTotal++;
            bar.progress(nEventsTotal, nEventsChain);
	    
            std::cout << "10" << endl;
            // iterate over jets and count number of non-btagged jets with pt > 40 GeV
            // and calculate Ht
            int njet_ct = 0;
            float Ht = 0;
            for (unsigned int i = 0; i < njet; i++){
                if (!(jet_pt->at(i) > 40) || jet_is_btagged->at(i)) continue;
                njet_ct++;
                Ht += jet_pt->at(i);
            }


            std::cout << "11" << endl;

            // fill histograms
            h_njet->Fill(njet_ct, event_wgt * event_weight_triggers_dilepton_matched);
            std::cout << "12" << endl;
            //h_met->Fill(PFMET_pt_final, event_wgt * event_weight_triggers_dilepton_matched);
            h_Ht->Fill(Ht, event_wgt * event_weight_triggers_dilepton_matched);

    } // Event loop


    std::cout << "13" << endl;

    // move overflow contents to last bin
    h_njet->SetBinContent(njet_nbin, h_njet->GetBinContent(njet_nbin+1) + h_njet->GetBinContent(njet_nbin));
    h_njet->SetBinError(njet_nbin, std::sqrt(std::pow(h_njet->GetBinError(njet_nbin+1),2) + std::pow(h_njet->GetBinError(njet_nbin),2)));

    std::cout << "14" << endl;
    // set overflow bin to 0
    h_njet->SetBinContent(njet_nbin+1, 0);
    h_njet->SetBinError(njet_nbin+1, 0);
    std::cout << "15" << endl;

    bar.finish();
    std::cout << "16" << endl;

    // make plots
    
    string plotDir = "/home/users/crowley/public_html/tttt_jet_distribution_check_12_10/";
    // njet plot
    TCanvas *njetPlot = new TCanvas("njet","njet", 1000,800);
    njetPlot->cd();
    h_njet->GetXaxis()->SetTitle("n_{jet}");
    h_njet->GetYaxis()->SetTitle("Events");
    h_njet->Draw();
    njetPlot->SetLogy();
    std::cout << "17" << endl;

    string njetPlotName = plotDir + "njet_";
    njetPlotName += sample_str;
    njetPlotName += ".pdf";
    njetPlot->SaveAs(njetPlotName.data());
    std::cout << "18" << endl;
    
    njetPlotName = plotDir + "njet_";
    njetPlotName += sample_str;
    njetPlotName += ".png";
    njetPlot->SaveAs(njetPlotName.data());

    std::cout << "19" << endl;
    //// met plot
    //TCanvas *metPlot = new TCanvas("met","met", 1000,800);
    //metPlot->cd();
    //h_met->GetXaxis()->SetTitle("MET [GeV]");
    //h_met->GetYaxis()->SetTitle("Events");
    //h_met->Draw();
    //metPlot->SetLogy();

    //string metPlotName = "/home/users/crowley/public_html/tttt_jet_distribution_check/met_";
    //metPlotName += sample_str;
    //metPlotName += ".pdf";
    //metPlot->SaveAs(metPlotName.data());

    //metPlotName = "/home/users/crowley/public_html/tttt_jet_distribution_check/met_";
    //metPlotName += sample_str;
    //metPlotName += ".png";
    //metPlot->SaveAs(metPlotName.data());
    //    
    // Ht plot
    TCanvas *HtPlot = new TCanvas("Ht","Ht", 1000,800);
    HtPlot->cd();
    h_Ht->GetXaxis()->SetTitle("H_{T} [GeV]");
    h_Ht->GetYaxis()->SetTitle("Events");
    h_Ht->Draw();
    HtPlot->SetLogy();

    string HtPlotName = plotDir + "Ht_";
    HtPlotName += sample_str;
    HtPlotName += ".pdf";
    HtPlot->SaveAs(HtPlotName.data());

    HtPlotName = plotDir + "Ht_";
    HtPlotName += sample_str;
    HtPlotName += ".png";
    HtPlot->SaveAs(HtPlotName.data());

    std::cout << "20" << endl;
    // save histograms to root file
    string outfile_name = "output_";
    outfile_name += sample_str;
    outfile_name += ".root";
    std::cout << "21" << endl;

    TFile* f1 = new TFile(outfile_name.data(), "RECREATE");
    h_njet->Write();
    std::cout << "22" << endl;
    //h_met->Write();
    h_Ht->Write();

    f1->Write();
    f1->Close();
    return 0;
}
