#include <TFile.h>
#include <TDirectory.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TString.h>
#include <iostream>

void compare_hist(const char* filename = "hist_MY/HppM1300_2018.root") {
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
        TH1* h_mll1  = (TH1*)d->Get("h_mT1");
        TH1* h_mDCH1 = (TH1*)d->Get("h_mDCH1");
        if (!h_mll1 || !h_mDCH1) {
            std::cerr << "Warning: missing histograms in " << dir << std::endl;
            continue;
        }

        // Style them
        h_mll1->SetLineColor(kBlue);
        h_mll1->SetLineWidth(2);
        h_mDCH1->SetLineColor(kRed);
        h_mDCH1->SetLineWidth(2);
        h_mDCH1->SetTitle("M1300");

        // Create canvas
        TCanvas* c = new TCanvas(Form("c_%s", dir), dir, 800, 600);

        // Draw
        h_mDCH1->Draw("HIST");
        h_mll1->Draw("HIST SAME");

        // Legend
        TLegend* leg = new TLegend(0.65, 0.7, 0.88, 0.88);
        leg->AddEntry(h_mll1, "m_{H} simple", "l");
        leg->AddEntry(h_mDCH1, "m_{H} complex", "l");
        leg->Draw();

        // Save as png
        TString outname = Form("%s.png", dir);
        c->SaveAs(outname);

        delete c;
    }

    f->Close();
}
