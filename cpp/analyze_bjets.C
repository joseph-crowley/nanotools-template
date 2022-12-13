#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TStyle.h"
#include "TLegend.h"

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

int ScanChain(TChain *ch, string sample_str, string plotDir, string rootDir) {
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

//    std::cout << "1" << endl;
    int const njet_nbin = 7;
    H1(njet,njet_nbin,0,njet_nbin);
//    std::cout << "2" << endl;

    int const met_nbin = 40;
    H1(met,met_nbin,0,1000);

    int const Ht_nbin = 100;
    H1(Ht,Ht_nbin,0,1000);

    // set up branches

    double event_wgt;
    ch->SetBranchAddress("event_wgt", &event_wgt);

    float event_weight_triggers_dilepton_matched;
    ch->SetBranchAddress("event_weight_triggers_dilepton_matched", &event_weight_triggers_dilepton_matched);

    unsigned int njet;
    ch->SetBranchAddress("njet", &njet);
//    std::cout << "3" << endl;

    unsigned int nbjet;
    ch->SetBranchAddress("nbjet", &nbjet);
//    std::cout << "4" << endl;

    double PFMET_pt_final;
    ch->SetBranchAddress("PFMET_pt_final", &PFMET_pt_final);
//    std::cout << "5" << endl;

    std::vector<float> *jet_pt = 0;
    ch->SetBranchAddress("jet_pt", &jet_pt);
//    std::cout << "6" << endl;

    std::vector<bool> *jet_is_btagged = 0;
    ch->SetBranchAddress("jet_is_btagged", &jet_is_btagged);
//    std::cout << "7" << endl;

    // Event loop
    for (Long64_t event = 0; event < ch->GetEntries(); ++event){
//    std::cout << "8" << endl;
            ch->GetEntry(event);
//            std::cout << "9" << endl;

            // progress bar
            nEventsTotal++;
            bar.progress(nEventsTotal, nEventsChain);
	    
//            std::cout << "10" << endl;
            // iterate over jets and count number of non-btagged jets with pt > 40 GeV
            // and calculate Ht
            int njet_ct = 0;
            float Ht = 0;
            for (unsigned int i = 0; i < njet; i++){
                auto const& is_btagged = jet_is_btagged->at(i);
                auto const& pt = jet_pt->at(i);
                float const pt_threshold = (is_btagged ? 25. : 40.);
                if (pt>pt_threshold) Ht += pt;
                if (!is_btagged) njet_ct++;
            }

//            std::cout << "11" << endl;

            // fill histograms
            // keep the full MET dist, but only plot njet for MET>50GeV
            if (PFMET_pt_final>50.)
                h_njet->Fill(njet_ct, event_wgt * event_weight_triggers_dilepton_matched);
//            std::cout << "12" << endl;
            h_met->Fill(PFMET_pt_final, event_wgt * event_weight_triggers_dilepton_matched);
            h_Ht->Fill(Ht, event_wgt * event_weight_triggers_dilepton_matched);

    } // Event loop


//    std::cout << "13" << endl;

    // move overflow contents to last bin
    h_njet->SetBinContent(njet_nbin, h_njet->GetBinContent(njet_nbin+1) + h_njet->GetBinContent(njet_nbin));
    h_njet->SetBinError(njet_nbin, std::sqrt(std::pow(h_njet->GetBinError(njet_nbin+1),2) + std::pow(h_njet->GetBinError(njet_nbin),2)));
    h_met->SetBinContent(met_nbin, h_met->GetBinContent(met_nbin+1) + h_met->GetBinContent(met_nbin));
    h_met->SetBinError(met_nbin, std::sqrt(std::pow(h_met->GetBinError(met_nbin+1),2) + std::pow(h_met->GetBinError(met_nbin),2)));
    h_Ht->SetBinContent(Ht_nbin, h_Ht->GetBinContent(Ht_nbin+1) + h_Ht->GetBinContent(Ht_nbin));
    h_Ht->SetBinError(Ht_nbin, std::sqrt(std::pow(h_Ht->GetBinError(Ht_nbin+1),2) + std::pow(h_Ht->GetBinError(Ht_nbin),2)));

//    std::cout << "14" << endl;
    // set overflow bin to 0
    h_njet->SetBinContent(njet_nbin+1, 0);
    h_njet->SetBinError(njet_nbin+1, 0);
    h_Ht->SetBinContent(Ht_nbin+1, 0);
    h_Ht->SetBinError(Ht_nbin+1, 0);
    h_met->SetBinContent(met_nbin+1, 0);
    h_met->SetBinError(met_nbin+1, 0);
//    std::cout << "15" << endl;

    bar.finish();
//    std::cout << "16" << endl;

    // make plots
    
    // njet plot
    TCanvas *njetPlot = new TCanvas("njet","njet", 1000,800);
    njetPlot->cd();
    h_njet->GetXaxis()->SetTitle("n_{jet}");
    h_njet->GetYaxis()->SetTitle("Events");
    h_njet->Draw();
    njetPlot->SetLogy();
//    std::cout << "17" << endl;

    string njetPlotName = plotDir + "/njet_";
    njetPlotName += sample_str;
    njetPlotName += ".pdf";
    njetPlot->SaveAs(njetPlotName.data());
//    std::cout << "18" << endl;
    
    njetPlotName = plotDir + "/njet_";
    njetPlotName += sample_str;
    njetPlotName += ".png";
    njetPlot->SaveAs(njetPlotName.data());

//    std::cout << "19" << endl;
    // met plot
    TCanvas *metPlot = new TCanvas("p_{T}^{miss}","p_{T}^{miss}", 1000,800);
    metPlot->cd();
    h_met->GetXaxis()->SetTitle("p_{T}^{miss}");
    h_met->GetYaxis()->SetTitle("Events");
    h_met->Draw();
    metPlot->SetLogy();

    string metPlotName = plotDir + "/met_";
    metPlotName += sample_str;
    metPlotName += ".pdf";
    metPlot->SaveAs(metPlotName.data());

    metPlotName = plotDir + "/met_";
    metPlotName += sample_str;
    metPlotName += ".png";
    metPlot->SaveAs(metPlotName.data());
        
    // Ht plot
    TCanvas *HtPlot = new TCanvas("Ht","Ht", 1000,800);
    HtPlot->cd();
    h_Ht->GetXaxis()->SetTitle("H_{T} [GeV]");
    h_Ht->GetYaxis()->SetTitle("Events");
    h_Ht->Draw();
    HtPlot->SetLogy();

    string HtPlotName = plotDir + "/Ht_";
    HtPlotName += sample_str;
    HtPlotName += ".pdf";
    HtPlot->SaveAs(HtPlotName.data());

    HtPlotName = plotDir + "/Ht_";
    HtPlotName += sample_str;
    HtPlotName += ".png";
    HtPlot->SaveAs(HtPlotName.data());

//    std::cout << "20" << endl;
    // save histograms to root file
    string outfile_name = rootDir + "/hists_";
    outfile_name += sample_str;
    outfile_name += ".root";
//    std::cout << "21" << endl;

    TFile* f = new TFile(outfile_name.data(), "RECREATE");
    h_njet->Write();
//    std::cout << "22" << endl;
    h_met->Write();
    h_Ht->Write();

    f->Write();
    f->Close();
    return 0;
}

// define a compareHists function for comparing the histograms 
// from different samples by integrating over the bins
// and making a plot
bool compareHists(TH1D* h1, TH1D* h2){

    // get the number of bins
    int nbins = h1->GetNbinsX();
    // get the bin width
    double binwidth = h1->GetBinWidth(1);
    // get the bin contents
    double h1_integral = 0;
    double h2_integral = 0;
    for(int i = 1; i <= nbins; i++){
        h1_integral += h1->GetBinContent(i);
        h2_integral += h2->GetBinContent(i);
    }
    // get the bin errors
    double h1_error = 0;
    double h2_error = 0;
    for(int i = 1; i <= nbins; i++){
        h1_error += std::pow(h1->GetBinError(i),2);
        h2_error += std::pow(h2->GetBinError(i),2);
    }
    h1_error = std::sqrt(h1_error);
    h2_error = std::sqrt(h2_error);

    // get the bin contents and errors normalized to the bin width
    double h1_integral_norm = h1_integral/binwidth;
    double h2_integral_norm = h2_integral/binwidth;
    double h1_error_norm = h1_error/binwidth;
    double h2_error_norm = h2_error/binwidth;

    // compare the bin contents and errors to see if h1 < h2
    return (h1_integral_norm < h2_integral_norm);
}

// Create a macro to stack the histograms and make a plot
int stackHists(string hname, vector<string> rootFiles, string plotDir){
    // stack histogram hname from rootFiles, make a plot, save the plot,
    // save the stacked histograms to a root file

    // remove stats box
    gStyle->SetOptStat(0);

    // hname is of the form njet, met, Ht
    // replace this with n_{jet}, p_{T}^{miss}, H_{T}
    // and the number of bins and the range of the histogram
    int nbins = 0;
    double xmin = 0;
    double xmax = 0;
    string hname_latex = hname;
    if(hname == "njet"){
        hname_latex = "n_{jet}";
        nbins = 7;
        xmin = 0;
        xmax = 7;
    }  
    else if(hname == "met"){
        hname_latex = "p_{T}^{miss}";
        nbins = 40;
        xmin = 0;
        xmax = 1000;
    }
    else if(hname == "Ht"){
        hname_latex = "H_{T}";
        nbins = 100;
        xmin = 0;
        xmax = 2000;
    }
    else{
        cout << "hname not recognized" << endl;
        return 1;
    }

    // create a vector of histograms and legend entries
    TH1D* h_data = NULL;
    string entry_data;
    vector<TH1D*> hists;
    vector<string> legend_entries;
    for(int i = 0; i < rootFiles.size(); i++){
        TFile* f = new TFile(rootFiles[i].data());
        TH1D* h = (TH1D*)f->Get(hname.data());

        // create a vector of legend entries from the root file names
        
        // for data
        // remove the path and the .root extension
        if (rootFiles[i].find("data") != string::npos){
            string entry = rootFiles[i];
            entry.erase(0, entry.find_last_of("/")+1);
            entry.erase(entry.find_last_of("."), entry.size());
            h_data = h;
            entry_data = entry;
            continue;
        }

        // for MC
        hists.push_back(h);
        // remove the path and the .root extension
        // and remove 'hists_' or 'output_'
        string entry = rootFiles[i];
        entry.erase(0, entry.find_last_of("/")+1);
        entry.erase(entry.find_last_of("."), entry.size());
        if(entry.find("hists_") != string::npos){
            entry.erase(0, entry.find("hists_")+6);
        }
        else if(entry.find("output_") != string::npos){
            entry.erase(0, entry.find("output_")+7);
        }
        legend_entries.push_back(entry);
    }

    // sort the hists by integral
    // smallest integral on top
    //sort(hists.begin(), hists.end(), compareHists);
    
    // get the legend entries in the same order as the histograms
    // Note: this currently does not give the correct order, I think. 
    // TODO: ask ulascan about doing this correctly
    //vector<string> legend_entries_sorted;
    //for(int i = 0; i < hists.size(); i++){
    //    for(int j = 0; j < rootFiles.size(); j++){
    //        if(hists[i] == (TH1D*)TFile(rootFiles[j].data()).Get(hname.data())){
    //            legend_entries_sorted.push_back(legend_entries[j]);
    //        }
    //    }
    //}

    // create a vector of colors hopefully larger than the number of histograms
    vector<int> colors;
    colors.push_back(kRed);
    colors.push_back(kBlue);
    colors.push_back(kGreen);
    colors.push_back(kOrange);
    colors.push_back(kMagenta);
    colors.push_back(kCyan);
    colors.push_back(kYellow);
    colors.push_back(kGray);
    colors.push_back(kViolet);
    colors.push_back(kTeal);
    colors.push_back(kAzure);
    colors.push_back(kSpring);
    colors.push_back(kPink);

    // stack the histograms and make a plot
    TCanvas *c = new TCanvas(hname.data(),hname.data(), 1000,800);
    c->cd();
    THStack *hs = new THStack(hname.data(),hname.data());
    TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
    for(int i = 0; i < hists.size(); i++){
        // there may be more hists than colors
        // so use the modulo operator to cycle through the colors
        // set line color slightly lighter than fill color
        hists[i]->SetFillColor(colors[i%colors.size()]);
        hists[i]->SetLineColor(colors[i%colors.size()]+2);
        hists[i]->SetLineWidth(1);
        hists[i]->SetFillStyle(3001);
        hs->Add(hists[i]);
    }

    // compute the min and max for hs
    hs->SetMinimum(1e-1);
    hs->SetMaximum(3e5);
    hs->Draw("hist");
    hs->GetXaxis()->SetTitle(hname_latex.data());
    hs->GetYaxis()->SetTitle("Events");

    // fill the legend in reverse order
    for(int i = hists.size() - 1; i >= 0; i--){
        leg->AddEntry(hists[i], legend_entries[i].data(), "f");
    }
    // data last    
    leg->AddEntry(h_data, "data", "lep");

    // draw the data histogram
    h_data->SetMarkerStyle(20);
    h_data->SetMarkerSize(1.2);
    h_data->SetLineWidth(2);
    h_data->SetLineColor(kBlack);
    h_data->Draw("e1psame");

    leg->Draw();
    c->SetLogy();

    // save the plot
    string plotName = plotDir + "/";
    plotName += hname;
    plotName += "_stack.pdf";
    c->SaveAs(plotName.data());

    plotName = plotDir + "/";
    plotName += hname;
    plotName += "_stack.png";
    c->SaveAs(plotName.data());

    // save the stacked histograms to a root file
    string outfile_name = plotDir + "/";
    outfile_name += hname;
    outfile_name += "_stack.root";
    TFile* f = new TFile(outfile_name.data(), "RECREATE");
    hs->Write();
    f->Write();
    f->Close();
    return 0;
}