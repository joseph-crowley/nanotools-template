#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"
#include "TCanvas.h"
#include "TPad.h"
#include "THStack.h"
#include "TStyle.h"
#include "TText.h"
#include "TLine.h"
#include "TLegend.h"
#include "TRatioPlot.h"
#include "TLatex.h"
#include "TLorentzVector.h"

#include "lepton_sfs_el.h"
//#include "../NanoCORE/Nano.h"
//#include "../NanoCORE/Base.h"
//#include "../NanoCORE/SSSelections.cc"
//#include "../NanoCORE/MetSelections.cc"
#include "../NanoCORE/tqdm.h"
#include "PlottingHelpers.h"
using namespace PlottingHelpers;

#include <iostream>
#include <iomanip>

#define SUM(vec) std::accumulate((vec).begin(), (vec).end(), 0);
#define SUM_GT(vec,num) std::accumulate((vec).begin(), (vec).end(), 0, [](float x,float y){return ((y > (num)) ? x+y : x); });
#define COUNT_GT(vec,num) std::count_if((vec).begin(), (vec).end(), [](float x) { return x > (num); });
#define COUNT_LT(vec,num) std::count_if((vec).begin(), (vec).end(), [](float x) { return x < (num); });

#define H1(name,nbins,low,high) TH1D *h_##name = new TH1D(#name,#name,nbins,low,high);
#define H1vec(name,nbins,low,high) \
  std::vector<TH1D *> h_##name ; \
  for (unsigned int i=0; i<5; i++){ \
    /* name the categories lt2 eq2 gt2 eq1 eq0 */ \
    std::string catname = #name; \
    if (catname == "jetpt") { if (i>0) break;} \
    else if (catname == "nbjet" || catname == "bjetpt") { \
      if (i==0) catname += "_loose"; \
      else if (i==1) catname += "_medium"; \
      else if (i==2) catname += "_tight";} \
    else {\
      if (i==0) catname += "_nb_lt2"; \
      else if (i==1) catname += "_nb_eq2"; \
      else if (i==2) catname += "_nb_gt2"; \
      else if (i==3) catname += "_nb_eq1"; \
      else if (i==4) catname += "_nb_eq0"; \
    }\
    h_##name.push_back(new TH1D(catname.c_str(),catname.c_str(),nbins,low,high)); \
  }

// #define DEBUG

struct debugger { template<typename T> debugger& operator , (const T& v) { cerr<<v<<" "; return *this; } } dbg;
#ifdef DEBUG
    #define debug(args...) do {cerr << #args << ": "; dbg,args; cerr << endl;} while(0)
#else
    #define debug(args...)
#endif

using namespace std;
//using namespace tas;

bool isLinearScale(string hname){
    
    if (hname.find("PVs") != string::npos) return true;

    return false;
}

string getHistogramName(string hname){
    // get the sample name from the root file name
    // remove the path and the .root extension
    string hname_latex = "";
    if(hname.find("njet") != string::npos){
        hname_latex = "n_{jet}";
    }  
    else if(hname.find("nbjet") != string::npos){
        hname_latex = "n_{b}";
        hname_latex += " (";
        hname_latex += hname.substr(6);
        hname_latex += ")";
    }  
    else if(hname.find("bjetpt") != string::npos){
        hname_latex = "p_{T}^{b}";
        hname_latex += " (";
        hname_latex += hname.substr(7);
        hname_latex += ") [GeV]";
    }  
    else if(hname == "jetpt"){
        hname_latex = "p_{T}^{j}";
        hname_latex += " [GeV]";
    }  
    else if(hname == "nbjet"){
        hname_latex = "n_{b}";
    }  
    else if(hname.find("met") != string::npos){
        hname_latex = "p_{T}^{miss} [GeV]";
    }
    else if(hname.find("Ht") != string::npos){
        hname_latex = "H_{T} [GeV]";
    }
    else if(hname.find("lep1_pt") != string::npos || hname.find("lep2_pt") != string::npos ||
            hname.find("lep1_eta") != string::npos || hname.find("lep2_eta") != string::npos ||
            hname.find("lep1_phi") != string::npos || hname.find("lep2_phi") != string::npos){
            
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
    else if(hname.find("m_bb") != string::npos){
        hname_latex = "m_{bb} [GeV]";
    }
    else if(hname.find("m_lb") != string::npos){
        hname_latex = "m_{lb} [GeV]";
    }
    else if(hname.find("pt_ll") != string::npos){
        hname_latex = "p_{T}^{ll} [GeV]";
    }
    else if(hname.find("m_ll") != string::npos){
        hname_latex = "m_{ll} [GeV]";
    }
    else {
        std::cout << "hname not recognized" << endl;
        std::cout << hname << endl;
        return hname;
    }

    return hname_latex;
}

void addTextToMarkers(TH1D *hist) {
   for (int i = 1; i <= hist->GetNbinsX(); i++) {
      float value = hist->GetBinContent(i);
      if (value == 0) continue; // don't add text for empty bins
      TText *text = new TText(hist->GetBinCenter(i), 0.7, Form("%.2f", value));
      text->SetTextAlign(22);
      text->SetTextFont(42);
      text->SetTextSize(0.03);
      text->Draw();
   }
}

void plotVariable(std::vector<TH1D*> const& h_vars, string sample_str, string plotDir) {
    for (auto const& h_var: h_vars){
      TCanvas *varPlot = new TCanvas(h_var->GetName(), "", 1000,800);
      varPlot->cd();
      //h_var->GetXaxis()->SetTitle(h_var->GetName());
      //h_var->GetYaxis()->SetTitle("Events");
      h_var->Draw();
      if (!isLinearScale(h_var->GetName())) varPlot->SetLogy();
  
      string varPlotName = plotDir + "/" + h_var->GetName() + "_";
      varPlotName += sample_str;
      varPlotName += ".pdf";
      varPlot->SaveAs(varPlotName.data());

      varPlotName = plotDir + "/" + h_var->GetName() + "_";
      varPlotName += sample_str;
      varPlotName += ".png";
      varPlot->SaveAs(varPlotName.data());
    }
}


double getStackIntegral(THStack* stack)
{
   double total_integral = 0.0;
   TList* hist_list = stack->GetHists();
   TIter next(hist_list);
   TH1D* hist;
   while ((hist = (TH1D*)next())) {
      total_integral += hist->Integral();
   }
   return total_integral;
}


void makeRatioPlot(THStack* hs, TH1D* h_data, string hname, string plotDir, std::vector<pair<int, TH1D*> > hists_sorted, vector<string> legend_entries) {


  // get the integral of the stack
  double stack_integral = getStackIntegral(hs);
  std::cout << "stack integral" << " for " << hname << ": " << stack_integral << std::endl;
  
  

  // create a canvas to draw the plot on
  TString canvasname = hname + "_ratio";
  PlottingHelpers::PlotCanvas plot(canvasname, 512, 512, 1, 2, 0.25, 0.08, 0.2, 0.0875, 0., 0.1, 0.3);
  plot.addCMSLogo(kPreliminary, 13, 0, 0);

  float PLOT_MAX = std::max(hs->GetMaximum(), h_data->GetMaximum())*1.2;
  //float PLOT_MIN = std::max(0.8 * std::min(0.1, std::min(hs->GetMinimum(), h_data->GetMinimum())), 0.001);
  float PLOT_MIN = std::max(0.1, 0.75 * std::min(hs->GetMinimum(), h_data->GetMinimum()));

  // draw the histogram stack in the top pad
  plot.getInsidePanels()[0][1]->cd();
  if (!isLinearScale(hname)) plot.getInsidePanels()[0][1]->SetLogy();
  hs->SetMaximum(PLOT_MAX);
  hs->SetMinimum(PLOT_MIN);
  hs->Draw("hist");
  hs->GetXaxis()->SetTitleFont(PlotCanvas::getStdFont_XYTitle());
  hs->GetXaxis()->SetTitleSize(plot.getStdPixelSize_XYTitle());
  hs->GetXaxis()->SetLabelFont(PlotCanvas::getStdFont_XYLabel());
  hs->GetXaxis()->SetLabelSize(plot.getStdPixelSize_XYLabel());
  hs->GetXaxis()->SetLabelOffset(plot.getStdOffset_XLabel());
  hs->GetYaxis()->SetTitleFont(PlotCanvas::getStdFont_XYTitle());
  hs->GetYaxis()->SetTitleSize(plot.getStdPixelSize_XYTitle());
  hs->GetYaxis()->SetLabelFont(PlotCanvas::getStdFont_XYLabel());
  hs->GetYaxis()->SetLabelSize(plot.getStdPixelSize_XYLabel());
  hs->GetYaxis()->SetLabelOffset(plot.getStdOffset_YLabel());
  h_data->Draw("e1p same");

  // get the last histogram in the stack (i.e. the MC histogram)
  TH1D* h_mc = (TH1D*)hs->GetStack()->Last();

  // create a legend
  // fill the legend in reverse order
  TLegend *leg = new TLegend(0.7, 0.7, 0.95, 0.90);
  leg->AddEntry(h_data, "data", "lep");
  for(int i = hists_sorted.size() - 1; i >= 0; i--){
      leg->AddEntry(hists_sorted[i].second, legend_entries[hists_sorted[i].first].data(), "f");
  }
  leg->Draw();

  //legend->SetBorderSize(0);
  //legend->SetTextFont(43);
  //legend->SetTextSize(plot.getStdPixelSize_XYLabel());
  //legend->SetLineColor(1);
  //legend->SetLineStyle(1);
  //legend->SetLineWidth(1);
  //legend->SetFillColor(0);
  //legend->SetFillStyle(0);
  //legend->AddEntry(h_data, "Observed", "ep");
  //legend->AddEntry(h_mc, "MC", "f");
  //// TODO: fill in the MC components in legend
  //TList *histos = hs->GetHists();
  //TIter next(histos);
  //TH1 *histo;
  //while ((histo = (TH1*)next())) {
  //    legend->AddEntry(histo, histo->GetXaxis()->GetTitle(), "f");
  //}

  //leg->SetTextSize(plot.getStdPixelSize_XYLabel());

  // TODO: compute the size of the legend based on the number of entries
  // ymin = ymax - (entry_size)*n_entries


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
  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(plot.getStdPixelSize_CMSLogoExtras());
  tex->DrawLatex(0.15, 0.85, "Channel: e#mu");

  string hname_latex = getHistogramName(hname);

  // make a ratio plot in the bottom pad
  plot.getInsidePanels()[0][0]->cd();
  TH1D* h_ratio = (TH1D*)h_data->Clone("h_ratio");
  h_ratio->SetTitle("");
  h_ratio->Divide(h_mc);
  h_ratio->SetMarkerStyle(20);
  h_ratio->SetMarkerSize(1.2);
  h_ratio->SetLineWidth(2);
  h_ratio->SetLineColor(kBlack);
  //float RATIO_MAX = std::min(10., h_ratio->GetMaximum()*1.2);
  //float RATIO_MIN = std::min(0.5, h_ratio->GetMinimum()*0.8);
  float RATIO_MAX = 1.4;
  float RATIO_MIN = 0.6;
  h_ratio->SetMaximum(RATIO_MAX);
  h_ratio->SetMinimum(RATIO_MIN);

  // Add x and y titles
  TPad* pad_xtitle = plot.getBorderPanels().at(0); pad_xtitle->cd();
  TLatex* xtitle = new TLatex(); plot.addText(xtitle);
  xtitle->SetTextAlign(22);
  xtitle->SetTextFont(PlotCanvas::getStdFont_XYTitle());
  xtitle->SetTextSize(plot.getStdPixelSize_XYTitle());
  xtitle->DrawLatexNDC(0.5, 0.5, hname_latex.data());
  plot.getInsidePanels()[0][0]->cd();

  TPad* pad_ytitle = plot.getBorderPanels().at(1); pad_ytitle->cd();
  TLatex* ytitle = new TLatex(); plot.addText(ytitle);
  ytitle->SetTextAlign(22);
  ytitle->SetTextFont(PlotCanvas::getStdFont_XYTitle());
  ytitle->SetTextSize(plot.getStdPixelSize_XYTitle());
  ytitle->SetTextAngle(90);
  ytitle->DrawLatexNDC(0.5, 1.-0.5/1.4, "Events");
  ytitle->DrawLatexNDC(0.5, 0.15/1.4, "Ratio");
  plot.getInsidePanels()[0][0]->cd();
  
  hs->GetYaxis()->SetTitle("");
  hs->GetXaxis()->SetTitle("");

  h_ratio->GetYaxis()->SetTitle("");
  h_ratio->GetXaxis()->SetTitle("");
  h_ratio->GetYaxis()->SetNdivisions(505);

  h_ratio->GetXaxis()->SetTitleFont(PlotCanvas::getStdFont_XYTitle());
  h_ratio->GetXaxis()->SetTitleSize(plot.getStdPixelSize_XYTitle());
  h_ratio->GetXaxis()->SetLabelFont(PlotCanvas::getStdFont_XYLabel());
  h_ratio->GetXaxis()->SetLabelSize(plot.getStdPixelSize_XYLabel());
  h_ratio->GetXaxis()->SetLabelOffset(plot.getStdOffset_XLabel());
  h_ratio->GetYaxis()->SetTitleFont(PlotCanvas::getStdFont_XYTitle());
  h_ratio->GetYaxis()->SetTitleSize(plot.getStdPixelSize_XYTitle());
  h_ratio->GetYaxis()->SetLabelFont(PlotCanvas::getStdFont_XYLabel());
  h_ratio->GetYaxis()->SetLabelSize(plot.getStdPixelSize_XYLabel());
  h_ratio->GetYaxis()->SetLabelOffset(plot.getStdOffset_YLabel());

  // manual
  h_ratio->GetXaxis()->SetTitleOffset(2);
  h_ratio->Draw("e1p");
  //addTextToMarkers(h_ratio);

  // draw the cut string on the canvas
  tex->SetTextSize(plot.getStdPixelSize_CMSLogoExtras());
  tex->DrawLatex(0.15, 0.75, cut_string.c_str());

  // save the plot to file
 
  plot.save(plotDir, "png"); 
  plot.save(plotDir, "pdf"); 
}
 

int ScanChain(TChain *ch, string sample_str, string plotDir, string rootDir, int fake_category) {
    int nEventsChain = ch->GetEntries();
    TFile *currentFile = 0;
    TObjArray *listOfFiles = ch->GetListOfFiles();
    TIter fileIter(listOfFiles);
    tqdm bar;

    bool isData = false;
    isData = sample_str.find("Data") == std::string::npos ? false : true;

    // remove stats box
    gStyle->SetOptStat(0);

    // make weighted histograms of: 
    /* njet 
     * met
     * Ht for all jets, bjets, and non-bjets
    */
    
    const int NUM_NB_CATEGORIES = 5;
    const int BTAG_WP = 1; // 0 loose, 1 medium, 2 tight
    constexpr float pt_threshold_btagged = 25.;
    constexpr float pt_threshold_unbtagged = 25.;

    int const njet_nbin = 7;
    H1vec(njet,njet_nbin,0,njet_nbin);

    int const bjetpt_nbin = 100;
    H1vec(bjetpt,bjetpt_nbin,0,1000);

    int const jetpt_nbin = 100;
    H1vec(jetpt,jetpt_nbin,0,1000);

    int const nbjet_nbin = 7;
    H1vec(nbjet,nbjet_nbin,0,nbjet_nbin);

    int const met_nbin = 40;
    H1vec(met,met_nbin,0,1000);

    int const Ht_nbin = 100;
    H1vec(Ht,Ht_nbin,0,1000);

    // leading lepton histograms
    int const lep1_pt_nbin = 100;
    int const lep1_eta_nbin = 50;
    int const lep1_phi_nbin = 32;
    H1vec(lep1_pt,lep1_pt_nbin,0,1000);
    H1vec(lep1_eta,lep1_eta_nbin,-2.5,2.5);
    H1vec(lep1_phi,lep1_phi_nbin,-3.2,3.2);

    // subleading lepton histograms
    int const lep2_pt_nbin = 100;
    int const lep2_eta_nbin = 50;
    int const lep2_phi_nbin = 32;
    H1vec(lep2_pt,lep2_pt_nbin,0,1000);
    H1vec(lep2_eta,lep2_eta_nbin,-2.5,2.5);
    H1vec(lep2_phi,lep2_phi_nbin,-3.2,3.2);
    
    // dilepton histograms
    int const pt_ll_nbin = 100;
    H1vec(pt_ll,pt_ll_nbin,0,1000);

    // invariant mass histograms
    int const m_ll_nbin = 40;
    int const m_lb_nbin = 40;
    int const m_bb_nbin = 40;
    H1vec(m_ll,m_ll_nbin,0,1000);
    H1vec(m_lb,m_lb_nbin,0,1000);
    H1vec(m_bb,m_bb_nbin,0,1000);


    // Primary vertex histograms
    int const nPV_nbin = 50;
    H1vec(nPVs,nPV_nbin,0,50);

    int const nPV_good_nbin = 50;
    H1vec(nPVs_good,nPV_good_nbin,0,50);

    // fakeable and loose lepton histograms
    int const nleptons_loose_nbin = 5;
    int const nmuons_loose_nbin = 5;
    int const nelectrons_loose_nbin = 5;
    H1vec(nleptons_loose,nleptons_loose_nbin,0,5);
    H1vec(nmuons_loose,nmuons_loose_nbin,0,5);
    H1vec(nelectrons_loose,nelectrons_loose_nbin,0,5);

    int const nleptons_fakeable_nbin = 5;
    int const nelectrons_fakeable_nbin = 5;
    int const nmuons_fakeable_nbin = 5;
    H1vec(nleptons_fakeable,nleptons_fakeable_nbin,0,5);
    H1vec(nelectrons_fakeable,nelectrons_fakeable_nbin,0,5);
    H1vec(nmuons_fakeable,nmuons_fakeable_nbin,0,5);

    // set up branches

    float event_wgt;
    ch->SetBranchAddress("event_wgt", &event_wgt);

    // TODO: add a weighted category, PU or no PU
    float event_wgt_noPU;
    ch->SetBranchAddress("event_wgt_noPU", &event_wgt_noPU);

    // TODO: use this for the event weights (expect 5% effect in 16+17)
    float event_wgt_adjustment_L1Prefiring;
    ch->SetBranchAddress("event_wgt_adjustment_L1Prefiring", &event_wgt_adjustment_L1Prefiring);

    float event_wgt_triggers_dilepton_matched;
    ch->SetBranchAddress("event_wgt_triggers_dilepton_matched", &event_wgt_triggers_dilepton_matched);

    float event_wgt_xsecCORRECTION = 1.;
    //if (sample_str.find("TT_") != std::string::npos) event_wgt_xsecCORRECTION = 0.826;
    // tW xsec was using the wrong BR. needs the BR for "NoFullyHadronicDecays"
    //if (sample_str.find("ST_") != std::string::npos) event_wgt_xsecCORRECTION = 0.543;

    float event_wgt_SFs_btagging;
    ch->SetBranchAddress("event_wgt_SFs_btagging", &event_wgt_SFs_btagging);

    unsigned int njet;
    ch->SetBranchAddress("nak4jets_tight_pt25", &njet);

    float PFMET_pt_final;
    ch->SetBranchAddress("pTmiss", &PFMET_pt_final);

    std::vector<float> *jet_pt = 0;
    ch->SetBranchAddress("ak4jets_pt", &jet_pt);

    std::vector<unsigned char> *jet_is_btagged = 0;
    ch->SetBranchAddress("ak4jets_pass_btagging", &jet_is_btagged);

    std::vector<int> *jet_hadronFlavour = 0;
    ch->SetBranchAddress("ak4jets_hadronFlavour", &jet_hadronFlavour);

    // add lepton variables pt, eta, phi, m
    std::vector<float> *lep_pt = 0;
    ch->SetBranchAddress("leptons_pt", &lep_pt);

    std::vector<float> *lep_eta = 0;
    ch->SetBranchAddress("leptons_eta", &lep_eta);

    std::vector<float> *lep_phi = 0;
    ch->SetBranchAddress("leptons_phi", &lep_phi);

    std::vector<float> *lep_mass = 0;
    ch->SetBranchAddress("leptons_mass", &lep_mass);

    // leptons_pdgId
    std::vector<int> *lep_pdgId = 0;
    ch->SetBranchAddress("leptons_pdgId", &lep_pdgId);
    
    int nPVs;
    ch->SetBranchAddress("nPVs", &nPVs);

    int nPVs_good;
    ch->SetBranchAddress("nPVs_good", &nPVs_good);

    unsigned int nelectrons_fakeable;
    ch->SetBranchAddress("nelectrons_fakeable", &nelectrons_fakeable);

    unsigned int nelectrons_loose;
    ch->SetBranchAddress("nelectrons_loose", &nelectrons_loose);
    
    unsigned int nmuons_fakeable;
    ch->SetBranchAddress("nmuons_fakeable", &nmuons_fakeable);

    unsigned int nmuons_loose;
    ch->SetBranchAddress("nmuons_loose", &nmuons_loose);

    unsigned int nleptons_fakeable;
    ch->SetBranchAddress("nleptons_fakeable", &nleptons_fakeable);

    unsigned int nleptons_loose;
    ch->SetBranchAddress("nleptons_loose", &nleptons_loose);

    //TODO: calculate masses with b's, for L,M,T categories.
    float min_mbb_WPL;
    float min_mlb_WPL;
    float min_mbb_WPM;
    float min_mlb_WPM;
    float min_mbb_WPT;
    float min_mlb_WPT;

    // Event loop
    // Declare variables outside of the event loop
    Long64_t nEventsTotal = 0;

    // Event loop
    for (Long64_t event = 0; event < ch->GetEntries(); ++event) {
      ch->GetEntry(event);
      
      // progress bar
      nEventsTotal++;
      bar.progress(nEventsTotal, nEventsChain);

      // TODO: remove this from the processing
      if (isData) event_wgt_SFs_btagging = 1.;

      // Calculate lepton scale factors using the lepton SF headers lepton_sfs_el.h 
      // electronScaleFactor_RunABCD(float pt, float eta)
      // electronScaleFactorReco_RunABCD(float pt, float eta) 

      // do the calculation for the event by taking the product of the SFs for each lepton
      double event_wgt_SFs_leptons = 1.;
      if (!isData) {
          for (unsigned int i = 0; i < lep_pt->size(); i++) {
            if (std::abs(lep_pdgId->at(i)) == 11) {
              event_wgt_SFs_leptons *= electronScaleFactor_RunABCD(lep_pt->at(i), lep_eta->at(i));
              event_wgt_SFs_leptons *= electronScaleFactorReco_RunABCD(lep_pt->at(i), lep_eta->at(i));
            }
            //if (lep_pdgId->at(i) == 13) {
            //  event_wgt_SFs_leptons *= muonScaleFactor_RunABCD(lep_pt->at(i), lep_eta->at(i));
            //}
          }
      }

      // Calculate variables needed for filling histograms
      std::vector<unsigned int> nbjet_ct;
      nbjet_ct.push_back(0);
      nbjet_ct.push_back(0);
      nbjet_ct.push_back(0);
      unsigned int njet_ct = 0;
      unsigned int njet_ct_btagged_real = 0;
      unsigned int njet_ct_btagged_c = 0;
      unsigned int njet_ct_btagged_udsg = 0;
      float Ht = 0;
      for (unsigned int i = 0; i < njet; i++) {
        // is_btagged is an unsigned char 
        // defined by int(is_btagged_loose) + int(is_btagged_medium) + int(is_btagged_tight)
        auto is_btagged = jet_is_btagged->at(i);
        auto const& pt = jet_pt->at(i);
        float pt_threshold = (is_btagged ? pt_threshold_btagged : pt_threshold_unbtagged);
        if (is_btagged && pt < pt_threshold) is_btagged = 0;
        pt_threshold = (is_btagged ? pt_threshold_btagged : pt_threshold_unbtagged);
        if (pt > pt_threshold) {
            Ht += pt;
            
            if (PFMET_pt_final < 50.) continue;

            if (is_btagged == 0 ) h_jetpt.front()->Fill(pt, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
            if (is_btagged > 0) h_bjetpt.at(is_btagged - 1)->Fill(pt, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
            if (is_btagged == 0) njet_ct++;
            if (is_btagged >= 1) nbjet_ct.at(0)++; // loose
            if (is_btagged >= 2) nbjet_ct.at(1)++; // medium
            if (is_btagged >= 3) nbjet_ct.at(2)++; // tight

            // keep track of hadronFlavour (MC only)
            if (!isData) {
                if (is_btagged > BTAG_WP) {
                    if (std::abs(jet_hadronFlavour->at(i)) == 5) {
                        njet_ct_btagged_real++;
                    } else if (std::abs(jet_hadronFlavour->at(i)) == 4) {
                        njet_ct_btagged_c++;
                    } else {
                        njet_ct_btagged_udsg++;
                    }
                }
            }
        }
      }

      // only fill histograms for the fake_category
      switch (fake_category) {
        case 0: // all real b's
          if (njet_ct_btagged_real != nbjet_ct.at(BTAG_WP)) continue;
          break;
        case 1: // at least 1 c, no light jets
          if (njet_ct_btagged_c < 1 || njet_ct_btagged_udsg > 0) continue;
          break;
        case 2: // at least 1 c, at least 1 light jet
          if (njet_ct_btagged_c < 1 || njet_ct_btagged_udsg < 1) continue;
          break;
        case 3: // no c, at least 1 light jet
          if (njet_ct_btagged_c > 0 || njet_ct_btagged_udsg < 1) continue;
          break;
        default:
          if (!isData) continue;
          break;
      }

      TLorentzVector lep1;
      lep1.SetPtEtaPhiM(lep_pt->at(0), lep_eta->at(0), lep_phi->at(0), lep_mass->at(0));
      TLorentzVector lep2;
      lep2.SetPtEtaPhiM(lep_pt->at(1), lep_eta->at(1), lep_phi->at(1), lep_mass->at(1));
      TLorentzVector dilep = lep1 + lep2;

      // Fill histograms
      for (unsigned int i_bjet = 0; i_bjet < NUM_NB_CATEGORIES; i_bjet++){

        // there are 3 WPs and 5 NB categories, so no need to loop twice. i_bjet = loose, med, tight
        if (PFMET_pt_final > 50. && i_bjet < 3) h_nbjet.at(i_bjet)->Fill(nbjet_ct.at(i_bjet), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);

        // NB Categories: lt2 eq2 gt2 eq1 eq0
        switch (i_bjet) {
            case 0: // lt2
                if (nbjet_ct.at(BTAG_WP) >= 2) continue;
                break;
            case 1: // eq2
                if (nbjet_ct.at(BTAG_WP) != 2) continue;
                break;
            case 2: // gt2
                if (nbjet_ct.at(BTAG_WP) <= 2) continue;
                break;
            case 3: // eq1
                if (nbjet_ct.at(BTAG_WP) != 1) continue;
                break;
            case 4: // eq0
                if (nbjet_ct.at(BTAG_WP) != 0) continue;
                break;
            default:
                break;
        }


        if (PFMET_pt_final > 50.) {

          h_njet.at(i_bjet)->Fill(njet_ct, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
          
          // lepton hists
          h_lep1_pt.at(i_bjet)->Fill(lep_pt->at(0), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
          h_lep1_eta.at(i_bjet)->Fill(lep_eta->at(0), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
          h_lep1_phi.at(i_bjet)->Fill(lep_phi->at(0), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
          h_lep2_pt.at(i_bjet)->Fill(lep_pt->at(1), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
          h_lep2_eta.at(i_bjet)->Fill(lep_eta->at(1), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
          h_lep2_phi.at(i_bjet)->Fill(lep_phi->at(1), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
      
          // dilepton hists
          h_m_ll.at(i_bjet)->Fill(dilep.M(), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
          h_pt_ll.at(i_bjet)->Fill(dilep.Pt(), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
          //h_m_lb.at(i_bjet)->Fill(min_mlb, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
          //h_m_bb.at(i_bjet)->Fill(min_mbb, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);

          // Primary vertex hists 
            h_nPVs.at(i_bjet)->Fill(nPVs, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
            h_nPVs_good.at(i_bjet)->Fill(nPVs_good, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
          
          // fakeable and loose lepton hists
          // nleptons_fakeable, nleptons_loose 
            h_nleptons_fakeable.at(i_bjet)->Fill(nleptons_fakeable, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
            h_nleptons_loose.at(i_bjet)->Fill(nleptons_loose, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);

          // nelectrons_fakeable, nelectrons_loose 
            h_nelectrons_fakeable.at(i_bjet)->Fill(nelectrons_fakeable, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
            h_nelectrons_loose.at(i_bjet)->Fill(nelectrons_loose, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);

          // nmuons_fakeable, nmuons_loose 
            h_nmuons_fakeable.at(i_bjet)->Fill(nmuons_fakeable, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
            h_nmuons_loose.at(i_bjet)->Fill(nmuons_loose, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);

        }
        h_met.at(i_bjet)->Fill(PFMET_pt_final, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
        h_Ht.at(i_bjet)->Fill(Ht, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_xsecCORRECTION * event_wgt_SFs_leptons);
      }
    }


    // make a vector of vectors of histograms for all the histograms
    std::vector<std::vector<TH1D *> *> histograms {&h_bjetpt, &h_jetpt, &h_nbjet, &h_njet, &h_met, &h_Ht, &h_lep1_pt, &h_lep1_eta, &h_lep1_phi, &h_lep2_pt, &h_lep2_eta, &h_lep2_phi, &h_m_ll, &h_pt_ll, &h_nPVs, &h_nPVs_good, &h_nleptons_fakeable, &h_nleptons_loose, &h_nelectrons_fakeable, &h_nelectrons_loose, &h_nmuons_fakeable, &h_nmuons_loose};
    
    for (int i = 0; i < histograms.size(); i++) {
        for (auto& histogram : *histograms.at(i)) {
          int nbin = histogram->GetNbinsX();
          histogram->SetBinContent(nbin, histogram->GetBinContent(nbin + 1) + histogram->GetBinContent(nbin));
          histogram->SetBinError(nbin, std::sqrt(std::pow(histogram->GetBinError(nbin + 1), 2) + std::pow(histogram->GetBinError(nbin), 2)));
        }
    }

    bar.finish();

    // save histograms as png, pdf, and root files
    // for all histograms {&h_bjetpt, &h_jetpt, &h_nbjet, &h_njet, &h_met, &h_Ht, &h_lep1_pt, &h_lep1_eta, &h_lep1_phi, &h_lep2_pt, &h_lep2_eta, &h_lep2_phi, &h_m_ll, &h_pt_ll, &h_nPVs, &h_nPVs_good, &h_nleptons_fakeable, &h_nleptons_loose, &h_nelectrons_fakeable, &h_nelectrons_loose, &h_nmuons_fakeable, &h_nmuons_loose}
    plotVariable(h_njet, sample_str, plotDir);
    plotVariable(h_nbjet, sample_str, plotDir);
    plotVariable(h_jetpt, sample_str, plotDir);
    plotVariable(h_bjetpt, sample_str, plotDir);
    plotVariable(h_met, sample_str, plotDir);
    plotVariable(h_Ht, sample_str, plotDir);
    plotVariable(h_lep1_pt, sample_str, plotDir);
    plotVariable(h_lep1_eta, sample_str, plotDir);
    plotVariable(h_lep1_phi, sample_str, plotDir);
    plotVariable(h_lep2_pt, sample_str, plotDir);
    plotVariable(h_lep2_eta, sample_str, plotDir);
    plotVariable(h_lep2_phi, sample_str, plotDir);
    plotVariable(h_pt_ll, sample_str, plotDir);
    plotVariable(h_m_ll, sample_str, plotDir);
    plotVariable(h_m_lb, sample_str, plotDir);
    plotVariable(h_m_bb, sample_str, plotDir);
    plotVariable(h_nPVs, sample_str, plotDir);
    plotVariable(h_nPVs_good, sample_str, plotDir);
    plotVariable(h_nleptons_fakeable, sample_str, plotDir);
    plotVariable(h_nleptons_loose, sample_str, plotDir);
    plotVariable(h_nelectrons_fakeable, sample_str, plotDir);
    plotVariable(h_nelectrons_loose, sample_str, plotDir);
    plotVariable(h_nmuons_fakeable, sample_str, plotDir);
    plotVariable(h_nmuons_loose, sample_str, plotDir);

    // save histograms to root file
    string outfile_name = rootDir + "/hists_";
    outfile_name += sample_str;
    outfile_name += ".root";

    TFile* f = new TFile(outfile_name.data(), "RECREATE");

#define WRITE_HISTOGRAMS \
   WRITE_HISTOGRAM(h_nbjet)\
   WRITE_HISTOGRAM(h_bjetpt)\
   WRITE_HISTOGRAM(h_jetpt)\
   WRITE_HISTOGRAM(h_njet)\
   WRITE_HISTOGRAM(h_met)\
   WRITE_HISTOGRAM(h_Ht)\
   WRITE_HISTOGRAM(h_lep1_pt)\
   WRITE_HISTOGRAM(h_lep1_eta)\
   WRITE_HISTOGRAM(h_lep1_phi)\
   WRITE_HISTOGRAM(h_lep2_pt)\
   WRITE_HISTOGRAM(h_lep2_eta)\
   WRITE_HISTOGRAM(h_lep2_phi)\
   WRITE_HISTOGRAM(h_pt_ll)\
   WRITE_HISTOGRAM(h_m_ll)\
   WRITE_HISTOGRAM(h_m_lb)\
   WRITE_HISTOGRAM(h_m_bb)\
   WRITE_HISTOGRAM(h_nPVs)\
   WRITE_HISTOGRAM(h_nPVs_good)\
   WRITE_HISTOGRAM(h_nleptons_fakeable)\
   WRITE_HISTOGRAM(h_nleptons_loose)\
   WRITE_HISTOGRAM(h_nelectrons_fakeable)\
   WRITE_HISTOGRAM(h_nelectrons_loose)\
   WRITE_HISTOGRAM(h_nmuons_fakeable)\
   WRITE_HISTOGRAM(h_nmuons_loose)

#define WRITE_HISTOGRAM(name) for (auto& h: name) {f->WriteTObject(h); delete h;}
WRITE_HISTOGRAMS
#undef WRITE_HISTOGRAM 
#undef WRITE_HISTOGRAMS

    f->Close();

    return 0;
}

// define a compareHists function for comparing the histograms 
// from different samples by integrating over the bins
// and making a plot
// takes a two <pair<int, TH1D*> > as input 
bool compareHists(pair<int, TH1D*> p1, pair<int, TH1D*> p2){
    // get the histograms
    TH1D* h1 = p1.second;
    TH1D* h2 = p2.second;
    
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

    // separate data 
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
    vector<pair<int, TH1D*> > hists_sorted;
    for(int i = 0; i < hists.size(); i++){
        hists_sorted.emplace_back(i, hists[i]);
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
    TCanvas *c = new TCanvas(hname.data(),"", 1000,800);
    c->cd();
    THStack *hs = new THStack(hname.data(),"");
    TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);

    for(int i = 0; i < hists_sorted.size(); i++){
        // there may be more hists than colors
        // so use the modulo operator to cycle through the colors
        // set line color slightly lighter than fill color
        hists_sorted[i].second->SetFillColor(colors[i%colors.size()]);
        hists_sorted[i].second->SetLineColor(colors[i%colors.size()]+2);
        hists_sorted[i].second->SetLineWidth(1);
        hists_sorted[i].second->SetFillStyle(3001);
        hists_sorted[i].second->GetXaxis()->SetTitle("");
        hs->Add(hists_sorted[i].second);
    }


    // compute the min and max for hs
    float PLOT_MAX = std::max(hs->GetMaximum(), h_data->GetMaximum())*1.2;
    float PLOT_MIN = std::max(0.8 * std::min(0.1, std::min(hs->GetMinimum(), h_data->GetMinimum())), 0.001);
    hs->SetMinimum(PLOT_MIN);
    hs->SetMaximum(PLOT_MAX);
    hs->Draw("hist");
    hs->GetXaxis()->SetTitle(hname_latex.data());
    hs->GetYaxis()->SetTitle("Events");

    // fill the legend in reverse order
    leg->AddEntry(h_data, "data", "lep");
    for(int i = hists_sorted.size() - 1; i >= 0; i--){
        leg->AddEntry(hists_sorted[i].second, legend_entries[hists_sorted[i].first].data(), "f");
    }


    // draw the data histogram
    h_data->SetMarkerStyle(20);
    h_data->SetMarkerSize(1.2);
    h_data->SetLineWidth(2);
    h_data->SetLineColor(kBlack);
    h_data->Draw("e1psame");

    leg->Draw();
    if (!isLinearScale(hname)) c->SetLogy();



    // save the plot
    string plotName = plotDir + "/";
    plotName += hname;
    plotName += "_stack.pdf";
    //c->SaveAs(plotName.data());

    plotName = plotDir + "/";
    plotName += hname;
    plotName += "_stack.png";
    //c->SaveAs(plotName.data());

    // save the stacked histograms to a root file
    string outfile_name = plotDir + "/";
    outfile_name += hname;
    outfile_name += "_stack.root";
    TFile* f = new TFile(outfile_name.data(), "RECREATE");
    hs->Write();
    f->Write();
    f->Close();

    makeRatioPlot(hs, h_data, hname, plotDir, hists_sorted, legend_entries);

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

void check_fakes() { return; }

