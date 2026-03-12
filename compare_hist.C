#include <TFile.h>
#include <TDirectory.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TString.h>
#include <iostream>

void compare_hist(const char* filename = "hist_MY/skim_500_test.root") {
    // Open file
    TFile* f = TFile::Open(filename, "READ");
    if (!f || f->IsZombie()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return;
    }

    // Directory names
    const char* dirs[] = {"0tau", "1tau", "2tau", "3tau"};

    // Loop over directories
    for (const char* dir : dirs) {
        TDirectory* d = (TDirectory*)f->Get(dir);
        if (!d) {
            std::cerr << "Warning: directory " << dir << " not found!" << std::endl;
            continue;
        }

        // Get histograms
        TH1* h_mll1  = (TH1*)d->Get("h_mll1");
        TH1* h_mH1 = (TH1*)d->Get("h_mT1_opp");
        TH1* h_mH01 = (TH1*)d->Get("h_mT1");
        
  		TH1* h_mll2  = (TH1*)d->Get("h_mll2");
        TH1* h_mH2 = (TH1*)d->Get("h_mT2_opp");
        TH1* h_mH02 = (TH1*)d->Get("h_mT2");
  		
        if (!h_mll1 || !h_mH1 || !h_mH01) {
            std::cerr << "Warning: missing histograms in " << dir << std::endl;
            continue;
        }

        // Style them
        h_mll1->SetLineColor(kRed);
        h_mll1->SetLineWidth(2);
        h_mH1->SetLineColor(kGreen);
        h_mH1->SetLineWidth(2);
        h_mH01->SetLineColor(kBlue);
        h_mH01->SetLineWidth(2);
        
        h_mll2->SetLineColor(kRed);
        h_mll2->SetLineWidth(2);
        h_mH2->SetLineColor(kGreen);
        h_mH2->SetLineWidth(2);
        h_mH02->SetLineColor(kBlue);
        h_mH02->SetLineWidth(2);
        
		h_mll1->SetTitle("M500");
		h_mll1->GetXaxis()->SetRangeUser(0, 1500);
		float pad_max1 = max({h_mll1->GetMaximum(), h_mH1->GetMaximum(), h_mH01->GetMaximum()});
        h_mll1->SetMaximum(1.1*pad_max1);
        
        h_mll2->SetTitle("M500");
		h_mll2->GetXaxis()->SetRangeUser(0, 1500);
		float pad_max2 = max({h_mll2->GetMaximum(), h_mH2->GetMaximum(), h_mH02->GetMaximum()});
        h_mll2->SetMaximum(1.1*pad_max2);
        
        // Create canvas
        TCanvas *c = new TCanvas(Form("c_%s", dir), dir, 1600, 600);
        c->Divide(2,1);
		gStyle->SetOptStat(0);
		c->cd(1);
        // Draw
        h_mll1->Draw("HIST"); 
        //h_mH1->Draw("HIST SAME");
        h_mH01->Draw("HIST SAME");
       
        TLegend* leg1 = new TLegend(0.55, 0.7, 0.88, 0.88);
        leg1->AddEntry(h_mll1, "m_{ll_{1}}", "l");
        //leg1->AddEntry(h_mH1, "m_{H_{a}} with true #nu", "l");
        leg1->AddEntry(h_mH01, "m_{H_{a}} with MET_{cov}", "l");
        leg1->Draw();
        c->cd(2);
        // Draw
        h_mll2->Draw("HIST"); 
        //h_mH2->Draw("HIST SAME");
        h_mH02->Draw("HIST SAME");
        
        TLegend* leg2 = new TLegend(0.55, 0.7, 0.88, 0.88);
        leg2->AddEntry(h_mll2, "m_{ll_{2}}", "l");
        //leg2->AddEntry(h_mH2, "m_{H_{b}} with true #nu", "l");
        leg2->AddEntry(h_mH02, "m_{H_{b}} with MET_{cov}", "l");
        leg2->Draw();

        // Save as png
        TString outname = Form("%s.png", dir);
        c->SaveAs(outname);

        delete c;
    }

    f->Close();
}
