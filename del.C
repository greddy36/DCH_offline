#include <TFile.h>
#include <TDirectory.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TString.h>
#include <TStyle.h>
#include <iostream>
#include <algorithm>

void del(const char* filename = "hist_MY/skim_500_test.root") {

    // Open file
    TFile* f = TFile::Open(filename, "READ");
    if (!f || f->IsZombie()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return;
    }

    const char* dirs[] = {/*"0tau", "1tau", "2tau", */"3tau"};

    // Combined histograms (start as null)
    TH1* h_mll1_all  = nullptr;
    TH1* h_mH01_all  = nullptr;
    TH1* h_mll2_all  = nullptr;
    TH1* h_mH02_all  = nullptr;

    // Loop over channels and sum
    for (const char* dir : dirs) {
        TDirectory* d = (TDirectory*)f->Get(dir);
        if (!d) {
            std::cerr << "Warning: directory " << dir << " not found!" << std::endl;
            continue;
        }

        TH1* h_mll1  = (TH1*)d->Get("h_mll1");
        TH1* h_mH01  = (TH1*)d->Get("h_mT1");
        TH1* h_mll2  = (TH1*)d->Get("h_mll2");
        TH1* h_mH02  = (TH1*)d->Get("h_mT2");

        if (!h_mll1 || !h_mH01 || !h_mll2 || !h_mH02) {
            std::cerr << "Warning: missing histograms in " << dir << std::endl;
            continue;
        }

        // First directory: clone, others: add
        if (!h_mll1_all) {
            h_mll1_all = (TH1*)h_mll1->Clone("h_mll1_all");
            h_mH01_all = (TH1*)h_mH01->Clone("h_mH01_all");
            h_mll2_all = (TH1*)h_mll2->Clone("h_mll2_all");
            h_mH02_all = (TH1*)h_mH02->Clone("h_mH02_all");

            h_mll1_all->SetDirectory(0);
            h_mH01_all->SetDirectory(0);
            h_mll2_all->SetDirectory(0);
            h_mH02_all->SetDirectory(0);
        } else {
            h_mll1_all->Add(h_mll1);
            h_mH01_all->Add(h_mH01);
            h_mll2_all->Add(h_mll2);
            h_mH02_all->Add(h_mH02);
        }
    }

    if (!h_mll1_all) {
        std::cerr << "No histograms were combined. Exiting." << std::endl;
        return;
    }

    // =======================
    // Styling
    // =======================
    gStyle->SetOptStat(0);

    h_mll1_all->SetLineColor(kRed);
    h_mll1_all->SetLineWidth(2);
    h_mH01_all->SetLineColor(kBlue);
    h_mH01_all->SetLineWidth(2);

    h_mll2_all->SetLineColor(kRed);
    h_mll2_all->SetLineWidth(2);
    h_mH02_all->SetLineColor(kBlue);
    h_mH02_all->SetLineWidth(2);

    h_mll1_all->SetTitle("Mass reco for leading SS pair (all #tau_{had} channels)");
    h_mll2_all->SetTitle("Mass reco for sub-leading SS pair (all #tau_{had} channels)");

	h_mll1_all->GetXaxis()->SetTitle("GeV");
    h_mll2_all->GetXaxis()->SetTitle("GeV");
    
    h_mll1_all->GetXaxis()->SetRangeUser(0, 1500);
    h_mll2_all->GetXaxis()->SetRangeUser(0, 1500);

    double pad_max1 = std::max(h_mll1_all->GetMaximum(), h_mH01_all->GetMaximum());
    double pad_max2 = std::max(h_mll2_all->GetMaximum(), h_mH02_all->GetMaximum());

    h_mll1_all->SetMaximum(1.1 * pad_max1);
    h_mll2_all->SetMaximum(1.1 * pad_max2);

    // =======================
    // Draw
    // =======================
    TCanvas* c = new TCanvas("c_combined", "All #tau_{had} channels", 1600, 600);
    c->Divide(2,1);

    // Left: mll1
    c->cd(1);
    h_mll1_all->Draw("HIST");
    h_mH01_all->Draw("HIST SAME");

    TLegend* leg1 = new TLegend(0.55, 0.7, 0.88, 0.88);
    leg1->AddEntry(h_mll1_all, "m_{ll_{1}}", "l");
    leg1->AddEntry(h_mH01_all, "m_{H_{a}} with MET_{cov}", "l");
    leg1->Draw();

    // Right: mll2
    c->cd(2);
    h_mll2_all->Draw("HIST");
    h_mH02_all->Draw("HIST SAME");

    TLegend* leg2 = new TLegend(0.55, 0.7, 0.88, 0.88);
    leg2->AddEntry(h_mll2_all, "m_{ll_{2}}", "l");
    leg2->AddEntry(h_mH02_all, "m_{H_{b}} with MET_{cov}", "l");
    leg2->Draw();

    // Save
    c->SaveAs("combined_channels.png");

    f->Close();
}

