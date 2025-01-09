#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TAxis.h>
#include "../include/MyBranch.C"

float getDR(float eta1, float phi1, float eta2, float phi2) {
    float pi = TMath::Pi();
    float dPhi = fmin(fabs(phi2 - phi1), 2.0 * pi - fabs(phi2 - phi1));
    float DR = sqrt(pow(dPhi, 2) + pow(eta2 - eta1, 2));
    return DR;
}
void custom_x_labels() {
    // Open the ROOT file and get the tree
    TFile *file = TFile::Open("DYJetsToLLM50_2018_tight.root");
    TTree *tree = (TTree*)file->Get("Events");
	MyBranch(tree);
    // Create a histogram


    // Custom X-axis labels
    const char* labels[] = {"eee", "eem", "eet",
							  "eme", "emm", "emt",
							  "ete", "etm", "ett",
							  "mme", "mmm", "mmt",
							  "mte", "mtm", "mtt",
							  "tte", "ttm", "ttt"};
    int nBins = sizeof(labels)/sizeof(labels[0]); // Number of bins
    TH1F *hist = new TH1F("hist", "Z->l^{+}l^{-}(Good) + tight fake ", nBins, 22, 22+nBins);
    for (int i = 1; i <= nBins; ++i) {
        hist->GetXaxis()->SetBinLabel(i, labels[i - 1]);
    }
    // Fill the histogram from the tree
    //tree->SetBranchAddress("cat", &cat);

    for (int i = 0; i < tree->GetEntries(); ++i) {
        tree->GetEntry(i);
        //if ((cat==22 or cat ==31 or cat==37) and pt_3 <38) continue;//extra ele
        //if ((cat==23 or cat ==32 or cat==38) and pt_3 <30) continue;//extra mu
        if (getDR(eta_1, phi_1, eta_3, phi_3) < 0.3 or getDR(eta_2, phi_2, eta_3, phi_3) < 0.3) continue;
        //cout<<cat;
        hist->Fill(cat); // Fill corresponding bin
    }

    // Draw the histogram
    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600);
    hist->Draw("hist text");
}
