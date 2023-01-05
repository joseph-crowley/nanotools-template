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
#include "TLine.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TLorentzVector.h"

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

string getHistogramName(string hname){
    // get the sample name from the root file name
    // remove the path and the .root extension
    string hname_latex = "";
    if(hname == "njet"){
        hname_latex = "n_{jet}";
    }  
    else if(hname == "met"){
        hname_latex = "p_{T}^{miss} [GeV]";
    }
    else if(hname == "Ht"){
        hname_latex = "H_{T} [GeV]";
    }
    else if(hname == "lep1_pt" || hname == "lep2_pt" ||
            hname == "lep1_eta" || hname == "lep2_eta" ||
            hname == "lep1_phi" || hname == "lep2_phi"){
            
        if(hname.find("pt") != string::npos){
            hname_latex = "p_{T}";
            hname_latex += "^{l";
            hname_latex += hname[3];
            hname_latex += "} [GeV]";
        }
        else if(hname.find("eta") != string::npos){
            hname_latex = "#eta";
            hname_latex += "^{l";
            hname_latex += hname[3];
            hname_latex += "}";
        }
        else if(hname.find("phi") != string::npos){
            hname_latex = "#phi";
            hname_latex += "^{l";
            hname_latex += hname[3];
            hname_latex += "}";
        }
    }
    else if(hname == "m_bb"){
        hname_latex = "m_{bb} [GeV]";
    }
    else if(hname == "m_lb"){
        hname_latex = "m_{lb} [GeV]";
    }
    else if(hname == "m_ll"){
        hname_latex = "m_{ll} [GeV]";
    }
    else {
        std::cout << "hname not recognized" << endl;
    }

    return hname_latex;
}

void plotVariable(string varName, TH1F* h_var, string sample_str, string plotDir) {
  TCanvas *varPlot = new TCanvas(varName.c_str(), varName.c_str(), 1000,800);
  varPlot->cd();
  h_var->GetXaxis()->SetTitle(varName.c_str());
  h_var->GetYaxis()->SetTitle("Events");
  h_var->Draw();
  varPlot->SetLogy();
  
  string varPlotName = plotDir + "/" + varName + "_";
  varPlotName += sample_str;
  varPlotName += ".pdf";
  varPlot->SaveAs(varPlotName.data());

  varPlotName = plotDir + "/" + varName + "_";
  varPlotName += sample_str;
  varPlotName += ".png";
  varPlot->SaveAs(varPlotName.data());
}

void makeRatioPlot(THStack* hs, TH1F* h_data, string hname, string plotDir) {
  // make a ratio plot of the data/MC in the bottom pad
  // and a stacked histogram with data overlayed on the top pad

  // create a canvas to draw the plot on
  TCanvas *c = new TCanvas("c", "c", 800, 800);

  // divide the canvas into two pads
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.5, 1, 1.0);
  pad1->SetTopMargin(0.05);
  pad1->SetBottomMargin(0.05);
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.0, 1, 0.5);
  pad2->SetTopMargin(0.05);
  pad2->SetBottomMargin(0.3);

  // draw the histogram stack in the top pad
  pad1->Draw();
  pad1->cd();
  hs->SetMaximum(hs->GetMaximum() * 1.1);
  hs->SetMinimum(0.0);
  hs->Draw("hist");
  h_data->Draw("e1p same");

  // draw the CMS logo
  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->DrawLatex(0.15, 0.96, "CMS Preliminary");
  tex->DrawLatex(0.7, 0.96, "#sqrt{s} = 13 TeV");

  // draw the integrated luminosity
  tex->SetTextSize(0.03);
  tex->DrawLatex(0.7, 0.88, Form("N_{events} = %.0f", h_data->Integral()));

  // get the last histogram in the stack (i.e. the MC histogram)
  TH1F* h_mc = (TH1F*)hs->GetStack()->Last();

  // create a legend
  TLegend *legend = new TLegend(0.7, 0.8, 0.9, 0.9);
  legend->SetFillColor(0);
  legend->SetLineColor(0);
  legend->AddEntry(h_data, "Data", "ep");
  legend->AddEntry(h_mc, "MC", "f");
  legend->Draw();

  // make the cut string
  vector<string> cuts;
  cuts.push_back("N_{jets} p_{T} #geq 40");
  cuts.push_back("N_{b-jets} = 2 (Medium WP)");
  cuts.push_back("N_{lep} = 2");
  cuts.push_back("p_{T}^{Miss} #geq 50");
  string cut_string = "Cut: ";
  for (int i = 0; i < cuts.size(); i++) {
    cut_string += cuts[i];
    if (i != cuts.size() - 1) cut_string += ", ";
  }

  // draw the channel
  tex->SetTextSize(0.03);
  tex->DrawLatex(0.15, 0.85, "Channel: e#mu");

  string hname_latex = getHistogramName(hname);

  // make a ratio plot
  pad2->Draw();
  pad2->cd();
  TH1F* h_ratio = (TH1F*)h_data->Clone("h_ratio");
  h_ratio->Divide(h_mc);
  h_ratio->SetMarkerStyle(20);
  h_ratio->SetMarkerSize(1.2);
  h_ratio->SetLineWidth(2);
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.0);
  h_ratio->SetMaximum(2.0);
  h_ratio->GetXaxis()->SetTitle(hname_latex.data());
  h_ratio->GetYaxis()->SetTitle("Data/MC");
  h_ratio->Draw("e1p");

  // draw the ratio plot axis labels
  tex->SetTextSize(0.03);
  tex->SetTextAlign(32);
  tex->DrawLatex(0.9, 0.5, cut_string.data());
  tex->SetTextAlign(12);
  tex->DrawLatex(0.15, 0.5, hname_latex.data());

  // save the plot to a file
  c->SaveAs((plotDir + hname + ".png").data());
  c->SaveAs((plotDir + hname + ".pdf").data());

  // clean up
  delete c;
  delete tex;
  delete legend;
  delete h_ratio;

  return;
}

int ScanChain(TChain *ch, string sample_str, string plotDir, string rootDir) {
    int nEventsChain = ch->GetEntries();
    TFile *currentFile = 0;
    TObjArray *listOfFiles = ch->GetListOfFiles();
    TIter fileIter(listOfFiles);
    tqdm bar;

    // remove stats box
    gStyle->SetOptStat(0);

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

    // leading lepton histograms
    int const lep1_pt_nbin = 100;
    int const lep1_eta_nbin = 50;
    int const lep1_phi_nbin = 32;
    H1(lep1_pt,lep1_pt_nbin,0,1000);
    H1(lep1_eta,lep1_eta_nbin,-2.5,2.5);
    H1(lep1_phi,lep1_phi_nbin,-3.2,3.2);

    // subleading lepton histograms
    int const lep2_pt_nbin = 100;
    int const lep2_eta_nbin = 50;
    int const lep2_phi_nbin = 32;
    H1(lep2_pt,lep2_pt_nbin,0,1000);
    H1(lep2_eta,lep2_eta_nbin,-2.5,2.5);
    H1(lep2_phi,lep2_phi_nbin,-3.2,3.2);
    
    // dilepton histograms

    int const pt_ll_nbin = 100;
    H1(pt_ll,pt_ll_nbin,0,1000);

    // invariant mass histograms
    int const m_ll_nbin = 40;
    int const m_lb_nbin = 40;
    int const m_bb_nbin = 40;
    H1(m_ll,m_ll_nbin,0,1000);
    H1(m_lb,m_lb_nbin,0,1000);
    H1(m_bb,m_bb_nbin,0,1000);

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

    // add lepton variables pt, eta, phi, m
    std::vector<float> *lep_pt = 0;
    ch->SetBranchAddress("lep_pt", &lep_pt);

    std::vector<float> *lep_eta = 0;
    ch->SetBranchAddress("lep_eta", &lep_eta);

    std::vector<float> *lep_phi = 0;
    ch->SetBranchAddress("lep_phi", &lep_phi);

    std::vector<float> *lep_mass = 0;
    ch->SetBranchAddress("lep_mass", &lep_mass);

    float min_mbb;
    ch->SetBranchAddress("min_mbb", &min_mbb);

    float min_mlb;
    ch->SetBranchAddress("min_mlb", &min_mlb);

    // Event loop
    // Declare variables outside of the event loop
    Long64_t nEventsTotal = 0;
    
    // Event loop
    for (Long64_t event = 0; event < ch->GetEntries(); ++event) {
      ch->GetEntry(event);
    
      // progress bar
      nEventsTotal++;
      bar.progress(nEventsTotal, nEventsChain);
    
      // Calculate variables needed for filling histograms
      int njet_ct = 0;
      float Ht = 0;
      for (unsigned int i = 0; i < njet; i++) {
        auto const& is_btagged = jet_is_btagged->at(i);
        auto const& pt = jet_pt->at(i);
        float const pt_threshold = (is_btagged ? 25. : 40.);
        if (pt > pt_threshold) Ht += pt;
        if (!is_btagged) njet_ct++;
      }
      TLorentzVector lep1;
      lep1.SetPtEtaPhiM(lep_pt->at(0), lep_eta->at(0), lep_phi->at(0), lep_mass->at(0));
      TLorentzVector lep2;
      lep2.SetPtEtaPhiM(lep_pt->at(1), lep_eta->at(1), lep_phi->at(1), lep_mass->at(1));
      TLorentzVector dilep = lep1 + lep2;
    
      // Fill histograms
      if (PFMET_pt_final > 50.) {
        h_njet->Fill(njet_ct, event_wgt * event_weight_triggers_dilepton_matched);
        h_lep1_pt->Fill(lep_pt->at(0), event_wgt * event_weight_triggers_dilepton_matched);
        h_lep1_eta->Fill(lep_eta->at(0), event_wgt * event_weight_triggers_dilepton_matched);
        h_lep1_phi->Fill(lep_phi->at(0), event_wgt * event_weight_triggers_dilepton_matched);
        h_lep2_pt->Fill(lep_pt->at(1), event_wgt * event_weight_triggers_dilepton_matched);
        h_lep2_eta->Fill(lep_eta->at(1), event_wgt * event_weight_triggers_dilepton_matched);
        h_lep2_phi->Fill(lep_phi->at(1), event_wgt * event_weight_triggers_dilepton_matched);
    
        // dilepton hists
        h_m_ll->Fill(dilep.M(), event_wgt * event_weight_triggers_dilepton_matched);
        h_pt_ll->Fill(dilep.Pt(), event_wgt * event_weight_triggers_dilepton_matched);
        h_m_lb->Fill(min_mlb, event_wgt * event_weight_triggers_dilepton_matched);
        h_m_bb->Fill(min_mbb, event_wgt * event_weight_triggers_dilepton_matched);
    }
    h_met->Fill(PFMET_pt_final, event_wgt * event_weight_triggers_dilepton_matched);
    h_Ht->Fill(Ht, event_wgt * event_weight_triggers_dilepton_matched);
    }

//    std::cout << "13" << endl;

    const int num_histograms = 9;
    TH1F* histograms[num_histograms] = {h_njet, h_met, h_Ht, h_lep1_pt, h_lep1_eta, h_lep1_phi, h_lep2_pt, h_lep2_eta, h_lep2_phi};
    int nbins[num_histograms] = {njet_nbin, met_nbin, Ht_nbin, lep1_pt_nbin, lep1_eta_nbin, lep1_phi_nbin, lep2_pt_nbin, lep2_eta_nbin, lep2_phi_nbin};
    
    for (int i = 0; i < num_histograms; i++) {
      TH1F* histogram = histograms[i];
      int nbin = nbins[i];
      histogram->SetBinContent(nbin, histogram->GetBinContent(nbin + 1) + histogram->GetBinContent(nbin));
      histogram->SetBinError(nbin, std::sqrt(std::pow(histogram->GetBinError(nbin + 1), 2) + std::pow(histogram->GetBinError(nbin), 2)));
    }


//    std::cout << "15" << endl;

    bar.finish();
//    std::cout << "16" << endl;

    // save histograms as png, pdf, and root files
    plotVariable("njet", h_njet, sample_str, plotDir);
    plotVariable("p_{T}^{miss}", h_met, sample_str, plotDir);
    plotVariable("H_{T}", h_Ht, sample_str, plotDir);
    plotVariable("p_{T}^{lep1}", h_lep1_pt, sample_str, plotDir);
    plotVariable("#eta^{lep1}", h_lep1_eta, sample_str, plotDir);
    plotVariable("#phi^{lep1}", h_lep1_phi, sample_str, plotDir);
    plotVariable("p_{T}^{lep2}", h_lep2_pt, sample_str, plotDir);
    plotVariable("#eta^{lep2}", h_lep2_eta, sample_str, plotDir);
    plotVariable("#phi^{lep2}", h_lep2_phi, sample_str, plotDir);
    plotVariable("p_{T}^{ll}", h_pt_ll, sample_str, plotDir);
    plotVariable("M_{ll}", h_m_ll, sample_str, plotDir);
    plotVariable("M_{lb}", h_m_lb, sample_str, plotDir);
    plotVariable("M_{bb}", h_m_bb, sample_str, plotDir);

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
    h_lep1_pt->Write();
    h_lep1_eta->Write();
    h_lep1_phi->Write();
    h_lep2_pt->Write();
    h_lep2_eta->Write();
    h_lep2_phi->Write();

    h_pt_ll->Write();
    h_m_ll->Write();
    h_m_lb->Write();
    h_m_bb->Write();

    f->Write();
    f->Close();

    // clean up memory
    delete f;
    delete h_njet;
    delete h_met;
    delete h_Ht;
    delete h_lep1_pt;
    delete h_lep1_eta;
    delete h_lep1_phi;
    delete h_lep2_pt;
    delete h_lep2_eta;
    delete h_lep2_phi;
    delete h_pt_ll;
    delete h_m_ll;
    delete h_m_lb;
    delete h_m_bb;

    return 0;
}

// define a compareHists function for comparing the histograms 
// from different samples by integrating over the bins
// and making a plot
// takes a two <pair<int, TH1F*> > as input 
bool compareHists(pair<int, TH1F*> p1, pair<int, TH1F*> p2){
    // get the histograms
    TH1F* h1 = p1.second;
    TH1F* h2 = p2.second;
    
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

    // get the histogram name in latex format
    string hname_latex = getHistogramName(hname);

    // create a vector of histograms and legend entries
    // separate data and Others
    TH1F* h_data = NULL;
    string entry_data;
    TH1F* h_Others = NULL;
    string entry_Others;
    vector<TH1F*> hists;
    vector<string> legend_entries;
    for(int i = 0; i < rootFiles.size(); i++){
        TFile* f = new TFile(rootFiles[i].data());
        TH1F* h = (TH1F*)f->Get(hname.data());

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
        // for Others
        if (rootFiles[i].find("Others") != string::npos){
            string entry = rootFiles[i];
            entry.erase(0, entry.find_last_of("/")+1);
            entry.erase(entry.find_last_of("."), entry.size());
            h_Others = h;
            entry_Others = entry;
            continue;
        }

        // for MC
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

        hists.push_back(h);
        legend_entries.push_back(entry);
    }

    // sort the hists by integral
    // smallest integral on top
    // keep track of the indices of the sorted histograms
    // by using a vector of pairs
    vector<pair<int, TH1F*> > hists_sorted;
    for(int i = 0; i < hists.size(); i++){
        hists_sorted.push_back(make_pair(i, hists[i]));
    }
    sort(hists_sorted.begin(), hists_sorted.end(), compareHists);

    // create a vector of colors hopefully larger than the number of histograms
    vector<int> colors;
    colors.push_back(kRed);
    colors.push_back(kViolet);
    colors.push_back(kGreen);
    colors.push_back(kOrange);
    colors.push_back(kMagenta);
    colors.push_back(kCyan);

    // stack the histograms and make a plot
    TCanvas *c = new TCanvas(hname.data(),hname.data(), 1000,800);
    c->cd();
    THStack *hs = new THStack(hname.data(),hname.data());
    TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);

    // add the Others histogram first
    h_Others->SetFillColor(colors[hists_sorted.size()%colors.size()]);
    h_Others->SetLineColor(colors[hists_sorted.size()%colors.size()]+2);
    h_Others->SetLineWidth(1);
    h_Others->SetFillStyle(3001);
    hs->Add(h_Others);

    for(int i = 0; i < hists_sorted.size(); i++){
        // there may be more hists than colors
        // so use the modulo operator to cycle through the colors
        // set line color slightly lighter than fill color
        hists_sorted[i].second->SetFillColor(colors[i%colors.size()]);
        hists_sorted[i].second->SetLineColor(colors[i%colors.size()]+2);
        hists_sorted[i].second->SetLineWidth(1);
        hists_sorted[i].second->SetFillStyle(3001);
        hs->Add(hists_sorted[i].second);
    }


    // compute the min and max for hs
    hs->SetMinimum(1e-1);
    hs->SetMaximum(3e5);
    hs->Draw("hist");
    hs->GetXaxis()->SetTitle(hname_latex.data());
    hs->GetYaxis()->SetTitle("Events");

    // fill the legend in reverse order
    for(int i = hists_sorted.size() - 1; i >= 0; i--){
        leg->AddEntry(hists_sorted[i].second, legend_entries[hists_sorted[i].first].data(), "f");
    }
    // then Others
    leg->AddEntry(h_Others, "Others", "f");

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

    makeRatioPlot(hs, h_data, hname, plotDir);

    // clean up memory
    delete c;
    delete f;
    delete hs;
    delete leg;
    for(int i = 0; i < hists.size(); i++){
        delete hists[i];
    }
    hists.clear();
    hists_sorted.clear();
    legend_entries.clear();
    colors.clear();

    return 0;
}
