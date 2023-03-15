// Check Z->ee, Z->mumu, Z->tautau, Z->qqbar, Z->llbar, Z->nunubar
// cut around Z mass with OSSF pairs
// check the flavor difference mumu vs ee vs tautau
#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
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
#include "lepton_sfs_mu.h"

#include <iostream>
#include <iomanip>

#include "PlottingHelpers.h"
using namespace PlottingHelpers;

int ScanChain(TChain *ch, string sample_str, string plotDir, string rootDir) {

    bool isData = false;
    isData = sample_str.find("Data") == std::string::npos ? false : true;
    
    // Set branch addresses and branch pointers
    float event_wgt;
    ch->SetBranchAddress("event_wgt", &event_wgt);

    float event_wgt_noPU;
    ch->SetBranchAddress("event_wgt_noPU", &event_wgt_noPU);

    float event_wgt_adjustment_L1Prefiring;
    ch->SetBranchAddress("event_wgt_adjustment_L1Prefiring", &event_wgt_adjustment_L1Prefiring);

    float event_wgt_triggers_dilepton_matched;
    ch->SetBranchAddress("event_wgt_triggers_dilepton_matched", &event_wgt_triggers_dilepton_matched);

    float event_wgt_SFs_btagging;
    ch->SetBranchAddress("event_wgt_SFs_btagging", &event_wgt_SFs_btagging);

    float PFMET_pt_final;
    ch->SetBranchAddress("pTmiss", &PFMET_pt_final);

    std::vector<float> *lep_pt = 0;
    ch->SetBranchAddress("leptons_pt", &lep_pt);

    std::vector<float> *lep_eta = 0;
    ch->SetBranchAddress("leptons_eta", &lep_eta);

    std::vector<float> *lep_phi = 0;
    ch->SetBranchAddress("leptons_phi", &lep_phi);

    std::vector<float> *lep_mass = 0;
    ch->SetBranchAddress("leptons_mass", &lep_mass);

    std::vector<int> *lep_pdgId = 0;
    ch->SetBranchAddress("leptons_pdgId", &lep_pdgId);

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

    // histograms
    TH1D *h_nleptons_loose = new TH1D("h_nleptons_loose", "h_nleptons_loose", 5, 0, 5);
    TH1D *h_nleptons_fakeable = new TH1D("h_nleptons_fakeable", "h_nleptons_fakeable", 5, 0, 5);
    TH1D *h_nmuons_loose = new TH1D("h_nmuons_loose", "h_nmuons_loose", 5, 0, 5);
    TH1D *h_nmuons_fakeable = new TH1D("h_nmuons_fakeable", "h_nmuons_fakeable", 5, 0, 5);
    TH1D *h_nelectrons_loose = new TH1D("h_nelectrons_loose", "h_nelectrons_loose", 5, 0, 5);
    TH1D *h_nelectrons_fakeable = new TH1D("h_nelectrons_fakeable", "h_nelectrons_fakeable", 5, 0, 5);
    TH1D *h_mll_os = new TH1D("h_mll_os", "h_mll_os", 70, 50, 140);
    TH1D *h_mll_os_ee = new TH1D("h_mll_os_ee", "h_mll_os_ee", 70, 50, 140);
    TH1D *h_mll_os_mm = new TH1D("h_mll_os_mm", "h_mll_os_mm", 70, 50, 140);
    TH1D *h_mll_os_em = new TH1D("h_mll_os_em", "h_mll_os_em", 70, 50, 140);

    // event loop
    Long64_t nentries = ch->GetEntries();
    std::cout << "nentries = " << nentries << endl;

    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        ch->GetEntry(jentry);

        // event weight
        // do the calculation for the event by taking the product of the SFs for each lepton
        double event_wgt_SFs_leptons = 1.;
        if (!isData) {
            for (unsigned int i = 0; i < lep_pt->size(); i++) {
              if (std::abs(lep_pdgId->at(i)) == 11) {
                event_wgt_SFs_leptons *= electronScaleFactor_RunABCD(lep_pt->at(i), lep_eta->at(i));
                event_wgt_SFs_leptons *= electronScaleFactorReco_RunABCD(lep_pt->at(i), lep_eta->at(i));
              }
              if (lep_pdgId->at(i) == 13) {
                event_wgt_SFs_leptons *= muonScaleFactor_RunABCD(lep_pt->at(i), lep_eta->at(i));
              }
            }
        }
        float event_weight = event_wgt * event_wgt_adjustment_L1Prefiring * event_wgt_triggers_dilepton_matched * event_wgt_SFs_btagging * event_wgt_SFs_leptons;

        // fill histograms
        h_nleptons_loose->Fill(nleptons_loose, event_weight);
        h_nleptons_fakeable->Fill(nleptons_fakeable, event_weight);
        h_nmuons_loose->Fill(nmuons_loose, event_weight);
        h_nmuons_fakeable->Fill(nmuons_fakeable, event_weight);
        h_nelectrons_loose->Fill(nelectrons_loose, event_weight);
        h_nelectrons_fakeable->Fill(nelectrons_fakeable, event_weight);

        // loop over leptons
        for (unsigned int ilep1 = 0; ilep1 < lep_pt->size(); ilep1++) {
            for (unsigned int ilep2 = ilep1+1; ilep2 < lep_pt->size(); ilep2++) {
                // opposite sign
                if (lep_pdgId->at(ilep1) * lep_pdgId->at(ilep2) < 0) {
                    TLorentzVector lep1;
                    lep1.SetPtEtaPhiM(lep_pt->at(ilep1), lep_eta->at(ilep1), lep_phi->at(ilep1), lep_mass->at(ilep1));
                    TLorentzVector lep2;
                    lep2.SetPtEtaPhiM(lep_pt->at(ilep2), lep_eta->at(ilep2), lep_phi->at(ilep2), lep_mass->at(ilep2));
                    TLorentzVector dilep = lep1 + lep2;

                    if (abs(dilep.M() - 91.2) > 30.) continue;
                    
                    h_mll_os->Fill(dilep.M(), event_weight);
                    if (abs(lep_pdgId->at(ilep1)) == 11 && abs(lep_pdgId->at(ilep2)) == 11) {
                        h_mll_os_ee->Fill(dilep.M(), event_weight);
                    }

                    if (abs(lep_pdgId->at(ilep1)) == 13 && abs(lep_pdgId->at(ilep2)) == 13) {
                        h_mll_os_mm->Fill(dilep.M(), event_weight);
                    }

                    if ((abs(lep_pdgId->at(ilep1)) == 11 && abs(lep_pdgId->at(ilep2)) == 13) || (abs(lep_pdgId->at(ilep1)) == 13 && abs(lep_pdgId->at(ilep2)) == 11)) {
                        h_mll_os_em->Fill(dilep.M(), event_weight);
                    }
                }

            }
        }
    }

    // rebin histograms
    int nbin = h_nleptons_loose->GetNbinsX();
    h_nleptons_loose->SetBinContent(nbin, h_nleptons_loose->GetBinContent(nbin + 1) + h_nleptons_loose->GetBinContent(nbin));
    h_nleptons_loose->SetBinError(nbin, std::sqrt(std::pow(h_nleptons_loose->GetBinError(nbin + 1), 2) + std::pow(h_nleptons_loose->GetBinError(nbin), 2)));
    nbin = h_nleptons_fakeable->GetNbinsX();
    h_nleptons_fakeable->SetBinContent(nbin, h_nleptons_fakeable->GetBinContent(nbin + 1) + h_nleptons_fakeable->GetBinContent(nbin));
    h_nleptons_fakeable->SetBinError(nbin, std::sqrt(std::pow(h_nleptons_fakeable->GetBinError(nbin + 1), 2) + std::pow(h_nleptons_fakeable->GetBinError(nbin), 2)));
    nbin = h_nmuons_fakeable->GetNbinsX();
    h_nmuons_fakeable->SetBinContent(nbin, h_nmuons_fakeable->GetBinContent(nbin + 1) + h_nmuons_fakeable->GetBinContent(nbin));
    h_nmuons_fakeable->SetBinError(nbin, std::sqrt(std::pow(h_nmuons_fakeable->GetBinError(nbin + 1), 2) + std::pow(h_nmuons_fakeable->GetBinError(nbin), 2)));

    nbin = h_nmuons_loose->GetNbinsX();
    h_nmuons_loose->SetBinContent(nbin, h_nmuons_loose->GetBinContent(nbin + 1) + h_nmuons_loose->GetBinContent(nbin));
    h_nmuons_loose->SetBinError(nbin, std::sqrt(std::pow(h_nmuons_loose->GetBinError(nbin + 1), 2) + std::pow(h_nmuons_loose->GetBinError(nbin), 2)));

    nbin = h_nelectrons_loose->GetNbinsX();
    h_nelectrons_loose->SetBinContent(nbin, h_nelectrons_loose->GetBinContent(nbin + 1) + h_nelectrons_loose->GetBinContent(nbin));
    h_nelectrons_loose->SetBinError(nbin, std::sqrt(std::pow(h_nelectrons_loose->GetBinError(nbin + 1), 2) + std::pow(h_nelectrons_loose->GetBinError(nbin), 2)));

    nbin = h_nelectrons_fakeable->GetNbinsX();
    h_nelectrons_fakeable->SetBinContent(nbin, h_nelectrons_fakeable->GetBinContent(nbin + 1) + h_nelectrons_fakeable->GetBinContent(nbin));
    h_nelectrons_fakeable->SetBinError(nbin, std::sqrt(std::pow(h_nelectrons_fakeable->GetBinError(nbin + 1), 2) + std::pow(h_nelectrons_fakeable->GetBinError(nbin), 2)));

    nbin = h_mll_os->GetNbinsX();
    h_mll_os->SetBinContent(nbin, h_mll_os->GetBinContent(nbin + 1) + h_mll_os->GetBinContent(nbin));
    h_mll_os->SetBinError(nbin, std::sqrt(std::pow(h_mll_os->GetBinError(nbin + 1), 2) + std::pow(h_mll_os->GetBinError(nbin), 2)));

    nbin = h_mll_os_ee->GetNbinsX();
    h_mll_os_ee->SetBinContent(nbin, h_mll_os_ee->GetBinContent(nbin + 1) + h_mll_os_ee->GetBinContent(nbin));
    h_mll_os_ee->SetBinError(nbin, std::sqrt(std::pow(h_mll_os_ee->GetBinError(nbin + 1), 2) + std::pow(h_mll_os_ee->GetBinError(nbin), 2)));

    nbin = h_mll_os_mm->GetNbinsX();
    h_mll_os_mm->SetBinContent(nbin, h_mll_os_mm->GetBinContent(nbin + 1) + h_mll_os_mm->GetBinContent(nbin));
    h_mll_os_mm->SetBinError(nbin, std::sqrt(std::pow(h_mll_os_mm->GetBinError(nbin + 1), 2) + std::pow(h_mll_os_mm->GetBinError(nbin), 2)));

    nbin = h_mll_os_em->GetNbinsX();
    h_mll_os_em->SetBinContent(nbin, h_mll_os_em->GetBinContent(nbin + 1) + h_mll_os_em->GetBinContent(nbin));
    h_mll_os_em->SetBinError(nbin, std::sqrt(std::pow(h_mll_os_em->GetBinError(nbin + 1), 2) + std::pow(h_mll_os_em->GetBinError(nbin), 2)));

    // save histograms
    string sample_type = "";
    if (isData) sample_type = "data";
    else sample_type = "mc";

    TFile *f_out = new TFile(("outputs/" + sample_type + "/" + "hists_" + sample_str + ".root").data(), "RECREATE");
    h_nleptons_loose->Write();
    h_nleptons_fakeable->Write();
    h_nmuons_loose->Write();
    h_nmuons_fakeable->Write();
    h_nelectrons_loose->Write();
    h_nelectrons_fakeable->Write();
    h_mll_os->Write();
    h_mll_os_ee->Write();
    h_mll_os_mm->Write();
    h_mll_os_em->Write();
    f_out->Close();

    return 0;
}


void plot_histograms(string sample_str, string plotDir) {
    TFile *f_in = new TFile(("outputs/hists_" + sample_str + ".root").data(), "READ");
    TH1D *h_nleptons_loose = (TH1D*)f_in->Get("h_nleptons_loose");
    TH1D *h_nleptons_fakeable = (TH1D*)f_in->Get("h_nleptons_fakeable");
    TH1D *h_nmuons_loose = (TH1D*)f_in->Get("h_nmuons_loose");
    TH1D *h_nmuons_fakeable = (TH1D*)f_in->Get("h_nmuons_fakeable");
    TH1D *h_nelectrons_loose = (TH1D*)f_in->Get("h_nelectrons_loose");
    TH1D *h_nelectrons_fakeable = (TH1D*)f_in->Get("h_nelectrons_fakeable");
    TH1D *h_mll_os = (TH1D*)f_in->Get("h_mll_os");
    TH1D *h_mll_os_ee = (TH1D*)f_in->Get("h_mll_os_ee");
    TH1D *h_mll_os_mm = (TH1D*)f_in->Get("h_mll_os_mm");
    TH1D *h_mll_os_em = (TH1D*)f_in->Get("h_mll_os_em");

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->SetLogy();
    h_nleptons_loose->Draw();
    c1->SaveAs((plotDir + "/nleptons_loose.png").data());
    c1->SaveAs((plotDir + "/nleptons_loose.pdf").data());

    c1->Clear();
    h_nleptons_fakeable->Draw();
    c1->SaveAs((plotDir + "/nleptons_fakeable.png").data());
    c1->SaveAs((plotDir + "/nleptons_fakeable.pdf").data());

    c1->Clear();
    h_nmuons_loose->Draw();
    c1->SaveAs((plotDir + "/nmuons_loose.png").data());
    c1->SaveAs((plotDir + "/nmuons_loose.pdf").data());

    c1->Clear();
    h_nmuons_fakeable->Draw();
    c1->SaveAs((plotDir + "/nmuons_fakeable.png").data());
    c1->SaveAs((plotDir + "/nmuons_fakeable.pdf").data());

    c1->Clear();
    h_nelectrons_loose->Draw();
    c1->SaveAs((plotDir + "/nelectrons_loose.png").data());
    c1->SaveAs((plotDir + "/nelectrons_loose.pdf").data());

    c1->Clear();
    h_nelectrons_fakeable->Draw();
    c1->SaveAs((plotDir + "/nelectrons_fakeable.png").data());
    c1->SaveAs((plotDir + "/nelectrons_fakeable.pdf").data());

    c1->Clear();
    h_mll_os->Draw();
    c1->SaveAs((plotDir + "/mll_os.png").data());
    c1->SaveAs((plotDir + "/mll_os.pdf").data());

    c1->Clear();
    h_mll_os_ee->Draw();
    c1->SaveAs((plotDir + "/mll_os_ee.png").data());
    c1->SaveAs((plotDir + "/mll_os_ee.pdf").data());

    c1->Clear();
    h_mll_os_mm->Draw();
    c1->SaveAs((plotDir + "/mll_os_mm.png").data());
    c1->SaveAs((plotDir + "/mll_os_mm.pdf").data());

    c1->Clear();
    h_mll_os_em->Draw();
    c1->SaveAs((plotDir + "/mll_os_em.png").data());
    c1->SaveAs((plotDir + "/mll_os_em.pdf").data());

    f_in->Close();
}

void makeRatioPlot(string hname, std::vector<string> rootfiles, string plotDir) {

    // get the histograms
    TFile *f_data = new TFile(rootfiles[0].data(), "READ");
    TH1D *h_data = (TH1D*)f_data->Get(hname.data());
    TFile *f_mc = new TFile(rootfiles[1].data(), "READ");
    TH1D *h_mc = (TH1D*)f_mc->Get(hname.data());

    // create a canvas to draw the plot on
    TString canvasname = hname + "_ratio";
    PlottingHelpers::PlotCanvas plot(canvasname, 512, 512, 1, 2, 0.25, 0.08, 0.2, 0.0875, 0., 0.1, 0.3);
    plot.addCMSLogo(kPreliminary, 13, 0, 0);

    float PLOT_MAX = std::max(h_mc->GetMaximum(), h_data->GetMaximum())*1.2;
    //float PLOT_MIN = std::max(0.8 * std::min(0.1, std::min(h_mc->GetMinimum(), h_data->GetMinimum())), 0.001);
    float PLOT_MIN;
    if (hname.find("os") == std::string::npos) PLOT_MIN = 10;
    if (hname.find("os") != std::string::npos) PLOT_MIN = 1000;

    // draw the histogram in the top pad
    plot.getInsidePanels()[0][1]->cd();
    plot.getInsidePanels()[0][1]->SetLogy();
    h_mc->SetMaximum(PLOT_MAX);
    h_mc->SetMinimum(PLOT_MIN);
    h_mc->Draw("hist");

    // set the histogram style
    h_mc->SetLineColor(kBlack);
    h_mc->SetFillColor(kGray);
    h_mc->SetFillStyle(3001);
    h_data->SetLineColor(kBlack);
    h_data->SetMarkerColor(kBlack);
    h_data->SetMarkerStyle(20);
    h_data->SetMarkerSize(1.0);

    h_mc->GetXaxis()->SetTitleFont(PlotCanvas::getStdFont_XYTitle());
    h_mc->GetXaxis()->SetTitleSize(plot.getStdPixelSize_XYTitle());
    h_mc->GetXaxis()->SetLabelFont(PlotCanvas::getStdFont_XYLabel());
    h_mc->GetXaxis()->SetLabelSize(plot.getStdPixelSize_XYLabel());
    h_mc->GetXaxis()->SetLabelOffset(plot.getStdOffset_XLabel());
    h_mc->GetYaxis()->SetTitleFont(PlotCanvas::getStdFont_XYTitle());
    h_mc->GetYaxis()->SetTitleSize(plot.getStdPixelSize_XYTitle());
    h_mc->GetYaxis()->SetLabelFont(PlotCanvas::getStdFont_XYLabel());
    h_mc->GetYaxis()->SetLabelSize(plot.getStdPixelSize_XYLabel());
    h_mc->GetYaxis()->SetLabelOffset(plot.getStdOffset_YLabel());
    h_data->Draw("e1p same");

    TLegend *leg = new TLegend(0.7, 0.7, 0.95, 0.90);
    leg->AddEntry(h_data, "data", "lep");
    leg->AddEntry(h_mc, "mc", "lep");
    leg->Draw();

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
    xtitle->DrawLatexNDC(0.5, 0.5, hname.data());
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
  
    h_mc->GetYaxis()->SetTitle("");
    h_mc->GetXaxis()->SetTitle("");

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

    // save the plot to file
    plot.save(plotDir, "png"); 
    plot.save(plotDir, "pdf"); 
}

int check_Z() {return 0;}
