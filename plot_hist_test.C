#include <iostream>
#include <TFile.h>
#include <TKey.h>
#include <TList.h>
#include <TCanvas.h>
#include <TH1.h>
#include <THStack.h>
#include <TLegend.h>

void plotAllHistogramsStacked(const char* filename) {
    // Open the ROOT file
    TFile *file = new TFile(filename);
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return;
    }

    // Canvas setup
    TCanvas *canvas = new TCanvas("canvas", "Stacked Histograms", 800, 600);

    // THStack and legend
    THStack* stack = new THStack("stack", "Stacked Histograms");
    TLegend* legend = new TLegend(0.7, 0.6, 0.88, 0.88);

    // Get all keys in the file
    TList *keys = file->GetListOfKeys();
    TIter next(keys);
    TKey *key;

    int colorIndex = 2; // ROOT colors: start from 2 (kRed)

    while ((key = dynamic_cast<TKey*>(next()))) {
        std::string name = key->GetName();
        if (name.find("data") < name.length()) continue; // skip data

        // Get histogram object
        TH1* hist = dynamic_cast<TH1*>(key->ReadObj());
        if (!hist) continue;

        hist->SetDirectory(0); // Detach from file
        hist->SetLineColor(colorIndex);
        hist->SetFillColor(colorIndex);
        hist->SetTitle(name.c_str());

        // Add to stack and legend
        stack->Add(hist);
        legend->AddEntry(hist, name.c_str(), "f");

        std::cout << name << "\tIntegral = " << hist->Integral() << std::endl;

        colorIndex++;
        if (colorIndex == 5) colorIndex++; // skip yellow
    }

    // Draw and save
    stack->Draw("hist");
    stack->GetXaxis()->SetTitle("X-axis");
    stack->GetYaxis()->SetTitle("Events");
    legend->Draw();

    canvas->SaveAs("stacked_histograms.png");
    file->Close();
}

void plot_hist_test() {
    const char* filename = "hist_MY/nuisance_hist_test.root";
    plotAllHistogramsStacked(filename);
}
