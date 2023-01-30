#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"
#include "TCanvas.h"
#include "TPad.h"
#include "THStack.h"
#include "TStyle.h"
#include "TLine.h"
#include "TLegend.h"
#include "TRatioPlot.h"
#include "TLatex.h"
#include "TLorentzVector.h"

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

#define H1(name,nbins,low,high) TH1F *h_##name = new TH1F(#name,#name,nbins,low,high);
#define H1vec(name,nbins,low,high) \
  std::vector<TH1F *> h_##name ; \
  for (unsigned int i=0; i<3; i++){ \
    /* name the categories lt2 eq2 gt2 */ \
    std::string catname = #name; \
    if (catname == "nbjet") { if (i>0) break;} \
    else {\
      if (i==0) catname += "_nb_lt2"; \
      else if (i==1) catname += "_nb_eq2"; \
      else if (i==2) catname += "_nb_gt2"; \
    }\
    h_##name.push_back(new TH1F(catname.c_str(),catname.c_str(),nbins,low,high)); \
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

string getHistogramName(string hname){
    //std::cout << "getHistogramName" << endl;
    // get the sample name from the root file name
    // remove the path and the .root extension
    string hname_latex = "";
    if(hname.find("njet") != string::npos){
        hname_latex = "n_{jet}";
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
    else if(hname.find("m_ll") != string::npos){
        hname_latex = "m_{ll} [GeV]";
    }
    else {
        std::cout << "hname not recognized" << endl;
        std::cout << hname << endl;
    }

    return hname_latex;
}

void plotVariable(std::vector<TH1F*> const& h_vars, string sample_str, string plotDir) {
    //std::cout << "Plot Variable" << endl;
    for (auto const& h_var: h_vars){
      TCanvas *varPlot = new TCanvas(h_var->GetName(), "", 1000,800);
      varPlot->cd();
      //h_var->GetXaxis()->SetTitle(varName.c_str());
      //h_var->GetYaxis()->SetTitle("Events");
      h_var->Draw();
      varPlot->SetLogy();
  
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

void makeRatioPlot(THStack* hs, TH1F* h_data, string hname, string plotDir) {
  //std::cout << "Make Ratio Plot" << endl;
  // create a canvas to draw the plot on
  TString canvasname = hname + "_ratio";
  PlottingHelpers::PlotCanvas plot(canvasname, 512, 512, 1, 2, 0.25, 0.08, 0.2, 0.0875, 0., 0.1, 0.3);
  plot.addCMSLogo(kPreliminary, 13, 0, 0);
  cout << "Preparing canvas " << canvasname << "..." << endl;

  // draw the histogram stack in the top pad
  plot.getInsidePanels()[0][1]->cd();
  hs->SetMaximum(hs->GetMaximum() * 1.1);
  hs->SetMinimum(0.0);
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
  TH1F* h_mc = (TH1F*)hs->GetStack()->Last();

  // create a legend
  TLegend *legend = new TLegend(0.7, 0.7, 0.95, 0.90);
  legend->SetBorderSize(0);
  legend->SetTextFont(43);
  legend->SetTextSize(plot.getStdPixelSize_XYLabel());
  legend->SetLineColor(1);
  legend->SetLineStyle(1);
  legend->SetLineWidth(1);
  legend->SetFillColor(0);
  legend->SetFillStyle(0);
  legend->AddEntry(h_data, "Observed", "ep");
  //legend->AddEntry(h_mc, "MC", "f");


  // TODO: fill in the MC components in legend
  TList *histos = hs->GetHists();
  TIter next(histos);
  TH1 *histo;
  while ((histo = (TH1*)next())) {
      legend->AddEntry(histo, histo->GetXaxis()->GetTitle(), "f");
  }

  // TODO: compute the size of the legend based on the number of entries
  // ymin = ymax - (entry_size)*n_entries

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
  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(plot.getStdPixelSize_CMSLogoExtras());
  tex->DrawLatex(0.15, 0.85, "Channel: e#mu");

  string hname_latex = getHistogramName(hname);

  // make a ratio plot in the bottom pad
  plot.getInsidePanels()[0][0]->cd();
  TH1F* h_ratio = (TH1F*)h_data->Clone("h_ratio");
  h_ratio->SetTitle("");
  h_ratio->Divide(h_mc);
  h_ratio->SetMarkerStyle(20);
  h_ratio->SetMarkerSize(1.2);
  h_ratio->SetLineWidth(2);
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.0);
  h_ratio->SetMaximum(2.0);

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
  ytitle->DrawLatexNDC(0.5, 1.-0.5/1.4, "Events / bin");
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

  // draw the cut string on the canvas
  tex->SetTextSize(plot.getStdPixelSize_CMSLogoExtras());
  tex->DrawLatex(0.15, 0.75, cut_string.c_str());

  // save the plot to file
  //std::cout << plotDir << "/" << canvasname << endl;
 
  plot.save(plotDir, "png"); 
  plot.save(plotDir, "pdf"); 
}
 

int ScanChain(TChain *ch, string sample_str, string plotDir, string rootDir) {
    //std::cout << "ScanChain" << std::endl;
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

    //std::cout << "Making histograms" << std::endl;
    int const njet_nbin = 7;
    H1vec(njet,njet_nbin,0,njet_nbin);

    int const nbjet_nbin = 7;
    H1vec(nbjet,nbjet_nbin,0,nbjet_nbin);
//    std::cout << "2" << endl;

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

    // set up branches
    //std::cout << "Setting up branches" << std::endl;

    float event_wgt;
    ch->SetBranchAddress("event_wgt", &event_wgt);

    float event_wgt_triggers_dilepton_matched;
    ch->SetBranchAddress("event_wgt_triggers_dilepton_matched", &event_wgt_triggers_dilepton_matched);

    float event_wgt_SFs_btagging;
    ch->SetBranchAddress("event_wgt_SFs_btagging", &event_wgt_SFs_btagging);

    unsigned int njet;
    ch->SetBranchAddress("nak4jets_tight_pt25", &njet);
    //std::cout << "3" << endl;

    unsigned int nbjet;
    ch->SetBranchAddress("nak4jets_tight_pt25_btagged", &nbjet);
    //std::cout << "4" << endl;

    float PFMET_pt_final;
    ch->SetBranchAddress("pTmiss", &PFMET_pt_final);

    std::vector<float> *jet_pt = 0;
    ch->SetBranchAddress("ak4jets_pt", &jet_pt);

    std::vector<bool> *jet_is_btagged = 0;
    ch->SetBranchAddress("ak4jets_is_btagged", &jet_is_btagged);

    // add lepton variables pt, eta, phi, m
    std::vector<float> *lep_pt = 0;
    ch->SetBranchAddress("leptons_pt", &lep_pt);

    std::vector<float> *lep_eta = 0;
    ch->SetBranchAddress("leptons_eta", &lep_eta);

    std::vector<float> *lep_phi = 0;
    ch->SetBranchAddress("leptons_phi", &lep_phi);

    std::vector<float> *lep_mass = 0;
    ch->SetBranchAddress("leptons_mass", &lep_mass);

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
      //std::cout << "5" << endl;
      TLorentzVector lep1;
      lep1.SetPtEtaPhiM(lep_pt->at(0), lep_eta->at(0), lep_phi->at(0), lep_mass->at(0));
      TLorentzVector lep2;
      lep2.SetPtEtaPhiM(lep_pt->at(1), lep_eta->at(1), lep_phi->at(1), lep_mass->at(1));
      TLorentzVector dilep = lep1 + lep2;
    
      // Fill histograms
      //std::cout << "Filling histograms" << endl;
      if (PFMET_pt_final > 50.) h_nbjet.front()->Fill(nbjet, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);
      for (unsigned int i_bjet = 0; i_bjet < 3; i_bjet++){
        //std::cout << "Filling histograms: " << i_bjet << endl;
        // lt2 eq2 gt2 
        if ((i_bjet == 0) && (nbjet >= 2)) continue;
        if ((i_bjet == 1) && (nbjet != 2)) continue;
        if ((i_bjet == 2) && (nbjet <= 2)) continue;

        if (PFMET_pt_final > 50.) {
          h_njet.at(i_bjet)->Fill(njet_ct, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);
          h_lep1_pt.at(i_bjet)->Fill(lep_pt->at(0), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);
          h_lep1_eta.at(i_bjet)->Fill(lep_eta->at(0), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);
          h_lep1_phi.at(i_bjet)->Fill(lep_phi->at(0), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);
          h_lep2_pt.at(i_bjet)->Fill(lep_pt->at(1), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);
          h_lep2_eta.at(i_bjet)->Fill(lep_eta->at(1), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);
          h_lep2_phi.at(i_bjet)->Fill(lep_phi->at(1), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);
      
          // dilepton hists
          h_m_ll.at(i_bjet)->Fill(dilep.M(), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);
          h_pt_ll.at(i_bjet)->Fill(dilep.Pt(), event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);
          h_m_lb.at(i_bjet)->Fill(min_mlb, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);
          h_m_bb.at(i_bjet)->Fill(min_mbb, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);
        }
        h_met.at(i_bjet)->Fill(PFMET_pt_final, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);
        h_Ht.at(i_bjet)->Fill(Ht, event_wgt * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging);
      }
    }

    //std::cout << "rebinning histograms" << endl;
    std::vector<std::vector<TH1F *> *> histograms {&h_nbjet, &h_njet, &h_met, &h_Ht, &h_lep1_pt, &h_lep1_eta, &h_lep1_phi, &h_lep2_pt, &h_lep2_eta, &h_lep2_phi};
    
    for (int i = 0; i < histograms.size(); i++) {
        for (auto& histogram : *histograms.at(i)) {
          int nbin = histogram->GetNbinsX();
          histogram->SetBinContent(nbin, histogram->GetBinContent(nbin + 1) + histogram->GetBinContent(nbin));
          histogram->SetBinError(nbin, std::sqrt(std::pow(histogram->GetBinError(nbin + 1), 2) + std::pow(histogram->GetBinError(nbin), 2)));
        }
    }

    bar.finish();

    // save histograms as png, pdf, and root files
    plotVariable(h_njet, sample_str, plotDir);
    plotVariable(h_nbjet, sample_str, plotDir);
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

    //std::cout << "20" << endl;
    // save histograms to root file
    string outfile_name = rootDir + "/hists_";
    outfile_name += sample_str;
    outfile_name += ".root";
//    std::cout << "21" << endl;

    TFile* f = new TFile(outfile_name.data(), "RECREATE");

#define WRITE_HISTOGRAMS \
   WRITE_HISTOGRAM(h_nbjet)\
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
   WRITE_HISTOGRAM(h_m_bb)

//#define WRITE_HISTOGRAM(name) for (auto& h: name) std::cout << "will write " << h->GetName() << std::endl;
//WRITE_HISTOGRAMS
//#undef WRITE_HISTOGRAM 

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
    std::cout << "get hist name: ";
    string hname_latex = getHistogramName(hname);
    std::cout << hname_latex << endl;

    // separate data and Others
    TH1F* h_data = NULL;
    string entry_data;
    TH1F* h_Others = NULL;
    string entry_Others;
    vector<TH1F*> hists;
    vector<string> legend_entries;
    for(int i = 0; i < rootFiles.size(); i++){
        TFile* f = new TFile(rootFiles[i].data());
        std::cout << "file " << f->GetName() << endl;
        std::cout << "get " << hname << endl;
        TH1F* h = (TH1F*)f->Get(hname.data());
        if (h) std::cout << "got " << hname << endl;
        else std::cout << "failed " << hname << endl;
    

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

    
        std::cout << "adding hist to hists " << hname << endl;
        hists.push_back(h);
        legend_entries.push_back(entry);
        std::cout << "added hist to hists " << hname << endl;
    }

    // sort the hists by integral
    // smallest integral on top
    // keep track of the indices of the sorted histograms
    // by using a vector of pairs
    std::cout << "creating hist pairs" << endl;
    vector<pair<int, TH1F*> > hists_sorted;
    for(int i = 0; i < hists.size(); i++){
        hists_sorted.emplace_back(i, hists[i]);
    }
    std::cout << "created hist pairs" << endl;
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
    std::cout << "create canvas" << endl;
    TCanvas *c = new TCanvas(hname.data(),"", 1000,800);
    c->cd();
    THStack *hs = new THStack(hname.data(),"");
    TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
    std::cout << "creates canvas and stack" << endl;

    // add the Others histogram first
    if (h_Others) { 
        std::cout << "stack Others hist" << endl;
        std::cout << "size of hists " << hists_sorted.size() << endl;
        
        h_Others->SetFillColor(colors[hists_sorted.size()%colors.size()]);
        h_Others->SetLineColor(colors[hists_sorted.size()%colors.size()]+2);
        h_Others->SetLineWidth(1);
        h_Others->SetFillStyle(3001);
        h_Others->GetXaxis()->SetTitle("");
        hs->Add(h_Others);
    }

    for(int i = 0; i < hists_sorted.size(); i++){
        // there may be more hists than colors
        // so use the modulo operator to cycle through the colors
        // set line color slightly lighter than fill color
        std::cout << "stack hist" << hists_sorted[i].second->GetName() << endl;
        hists_sorted[i].second->SetFillColor(colors[i%colors.size()]);
        hists_sorted[i].second->SetLineColor(colors[i%colors.size()]+2);
        hists_sorted[i].second->SetLineWidth(1);
        hists_sorted[i].second->SetFillStyle(3001);
        hists_sorted[i].second->GetXaxis()->SetTitle("");
        hs->Add(hists_sorted[i].second);
        std::cout << "stacked hist" << hists_sorted[i].second->GetName() << endl;
    }


    // compute the min and max for hs
    hs->SetMinimum(1e-1);
    hs->SetMaximum(3e5);
    hs->Draw("hist");
    //hs->GetXaxis()->SetTitle(hname_latex.data());
    //hs->GetYaxis()->SetTitle("Events");

    // fill the legend in reverse order
    leg->AddEntry(h_data, "data", "lep");
    for(int i = hists_sorted.size() - 1; i >= 0; i--){
        leg->AddEntry(hists_sorted[i].second, legend_entries[hists_sorted[i].first].data(), "f");
    }
    // then Others
    leg->AddEntry(h_Others, "Others", "f");


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
