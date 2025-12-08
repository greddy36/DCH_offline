#include <TFile.h>
#include <TDirectory.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TString.h>
#include <iostream>

void compare_hist(const char* filename = "hist_MY/skim_500_2018.root") {
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
        TH1* h_mll1  = (TH1*)d->Get("h_mll2");
        TH1* h_mH1 = (TH1*)d->Get("h_mTtot2");
        TH1* h_mH01 = (TH1*)d->Get("h_mT2");
        
  		/*h_mll1->Add((TH1*)d->Get("h_mll2"));
  		h_mH1->Add((TH1*)d->Get("h_mTtot2"));
  		h_mH01->Add((TH1*)d->Get("h_mT2"));*/
  		
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
        
		h_mll1->SetTitle("M500");
		h_mll1->GetXaxis()->SetRangeUser(0, 1500);
		float pad_max = max({h_mll1->GetMaximum(), h_mH1->GetMaximum(), h_mH01->GetMaximum()});
        h_mll1->SetMaximum(1.1*pad_max);
        
        // Create canvas
        TCanvas* c = new TCanvas(Form("c_%s", dir), dir, 800, 600);
		gStyle->SetOptStat(0);
        // Draw
        h_mll1->Draw("HIST"); 
        h_mH1->Draw("HIST SAME");
        h_mH01->Draw("HIST SAME");
        // Legend
        TLegend* leg = new TLegend(0.55, 0.7, 0.88, 0.88);
        leg->AddEntry(h_mll1, "m_{ll_{2}}", "l");
        leg->AddEntry(h_mH1, "m_{H_{b}} with #nu for #tau_{h} only", "l");
        leg->AddEntry(h_mH01, "m_{H_{b}} with MET_{cov}", "l");
        leg->Draw();

        // Save as png
        TString outname = Form("%s.png", dir);
        c->SaveAs(outname);

        delete c;
    }

    f->Close();
}
