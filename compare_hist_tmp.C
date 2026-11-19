#include <TFile.h>
#include <TDirectory.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TString.h>
#include <iostream>

void compare_hist_tmp(const char* filename = "2nu_standalone/hist_MY/skim_500_test_old.root", const char* filename_bkg = "2nu_standalone/hist_MY/ZZTo4L_2018_old.root" ) {    
// Open file
    TFile* f = TFile::Open(filename, "READ");
	TFile* f_bkg = TFile::Open(filename_bkg, "READ");

    // Directory names
    const char* dirs[] = {"0tau", "1tau", "2tau", "3tau"};

    // Loop over directories
    for (const char* dir : dirs) {
        TDirectory* d = (TDirectory*)f->Get(dir);
		TDirectory* d_bkg = (TDirectory*)f_bkg->Get(dir);
        // Get histograms
        TH1* h_mll1  = (TH1*)d->Get("h_mll1");
        TH1* h_mDCH1 = (TH1*)d->Get("h_mDCH1");
        TH1* h_mT1 = (TH1*)d->Get("h_mT1");
        
        TH1* h_mll1_bkg  = (TH1*)d_bkg->Get("h_mll1");
        TH1* h_mDCH1_bkg = (TH1*)d_bkg->Get("h_mDCH1");
        TH1* h_mT1_bkg = (TH1*)d_bkg->Get("h_mT1");
        
  		TH1* h_mll2  = (TH1*)d->Get("h_mll2");
        TH1* h_mDCH2 = (TH1*)d->Get("h_mDCH2");
        TH1* h_mT2 = (TH1*)d->Get("h_mT2");
        
        TH1* h_mll2_bkg  = (TH1*)d_bkg->Get("h_mll2");
        TH1* h_mDCH2_bkg = (TH1*)d_bkg->Get("h_mDCH2");
        TH1* h_mT2_bkg = (TH1*)d_bkg->Get("h_mT2");
  		
        // Style them
        h_mll1->SetLineColor(kRed);
        h_mll1->SetLineWidth(2);
        h_mDCH1->SetLineColor(kGreen);
        h_mDCH1->SetLineWidth(2);
        h_mT1->SetLineColor(kBlue);
        h_mT1->SetLineWidth(2);
        h_mll1_bkg->SetFillColor(kRed);
        h_mll1_bkg->SetFillStyle(3000);
        h_mDCH1_bkg->SetFillColor(kGreen);
        h_mDCH1_bkg->SetFillStyle(3009);
        h_mT1_bkg->SetFillColor(kBlue);
        h_mT1_bkg->SetFillStyle(3006);
        
        h_mll2->SetLineColor(kRed);
        h_mll2->SetLineWidth(2);
        h_mDCH2->SetLineColor(kGreen);
        h_mDCH2->SetLineWidth(2);
        h_mT2->SetLineColor(kBlue);
        h_mT2->SetLineWidth(2);
        h_mll2_bkg->SetFillColor(kRed);
        h_mll2_bkg->SetFillStyle(3000);
        h_mDCH2_bkg->SetFillColor(kGreen);
        h_mDCH2_bkg->SetFillStyle(3009);
        h_mT2_bkg->SetFillColor(kBlue);
        h_mT2_bkg->SetFillStyle(3006);
        
        // Scale signal
        for (auto hist : {h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_mT1, h_mT2}){
        	hist->Scale(h_mll1_bkg->Integral() / hist->Integral());
        }
        
		h_mll1->SetTitle("Leading SS pair");
		h_mll1->GetXaxis()->SetRangeUser(0, 1000);
		float pad_max1 = max({h_mll1->GetMaximum(), h_mDCH1->GetMaximum(),h_mT1->GetMaximum()});
        h_mll1->SetMaximum(1.1*pad_max1);
        
        h_mll2->SetTitle("Sub-leading SS pair");
		h_mll2->GetXaxis()->SetRangeUser(0, 1000);
		float pad_max2 = max({h_mll2->GetMaximum(), h_mDCH2->GetMaximum(),h_mT2->GetMaximum()});
        h_mll2->SetMaximum(1.1*pad_max2);
        
        // Create canvas
        TCanvas *c = new TCanvas(Form("c_%s", dir), dir, 1600, 600);
        c->Divide(2,1);
		gStyle->SetOptStat(0);
		c->cd(1);
        // Draw
        h_mll1->Draw("HIST"); 
        h_mDCH1->Draw("HIST SAME");
        h_mT1->Draw("HIST SAME");
        h_mll1_bkg->Draw("HIST SAME"); 
        h_mDCH1_bkg->Draw("HIST SAME");
        h_mT1_bkg->Draw("HIST SAME");
        
       
        TLegend* leg1 = new TLegend(0.55, 0.7, 0.88, 0.88);
        leg1->AddEntry(h_mll1, "m_{ll_{1}}", "l");
        leg1->AddEntry(h_mDCH1, "m_{H_{a}} with #nu-algorithm", "l");
        leg1->AddEntry(h_mT1, "m_{H_{a}} new", "l");
        leg1->Draw();
        c->cd(2);
        // Draw
        h_mll2->Draw("HIST"); 
        h_mDCH2->Draw("HIST SAME");
        h_mT2->Draw("HIST SAME");
        h_mll2_bkg->Draw("HIST SAME"); 
        h_mDCH2_bkg->Draw("HIST SAME");
        h_mT2_bkg->Draw("HIST SAME");
        
        TLegend* leg2 = new TLegend(0.55, 0.7, 0.88, 0.88);
        leg2->AddEntry(h_mll2, "m_{ll_{2}}", "l");
        leg2->AddEntry(h_mDCH2, "m_{H_{b}} with #nu-algorithm", "l");
        leg2->AddEntry(h_mT2, "m_{H_{b}} new", "l");
        leg2->Draw();

        // Save as png
        TString outname = Form("%s_tmp.png", dir);
        c->SaveAs(outname);

        delete c;
    }

    f->Close();
}
