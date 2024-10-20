#include <TCanvas.h>
#include <THStack.h>
#include <TLegend.h>
#include <TH1F.h>
#include <TFile.h>
#include <TLine.h>
#include <TPad.h>

void makeStackedPlot() {
    // Open the ROOT file containing histograms
    TFile *file = TFile::Open("histograms.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Retrieve histograms for backgrounds and data
    TH1F *h_bkg1 = (TH1F*)file->Get("bkg1");
    TH1F *h_bkg2 = (TH1F*)file->Get("bkg2");
    TH1F *h_data = (TH1F*)file->Get("data");

    // Check if histograms were loaded successfully
    if (!h_bkg1 || !h_bkg2 || !h_data) {
        std::cerr << "Error loading histograms!" << std::endl;
        file->Close();
        return;
    }

    // Create a stacked histogram for the backgrounds
    THStack *hs = new THStack("hs", "Stacked Backgrounds");
    h_bkg1->SetFillColor(kRed); // Set colors for visual distinction
    h_bkg2->SetFillColor(kBlue);

    hs->Add(h_bkg1);
    hs->Add(h_bkg2);

    // Create a histogram for the total background (sum of all background histograms)
    TH1F *h_bkg_total = (TH1F*)h_bkg1->Clone("h_bkg_total");
    h_bkg_total->Add(h_bkg2);

    // Create a canvas with two pads: one for the stacked plot, one for the ratio
    TCanvas *c = new TCanvas("c", "Stacked Plot with Data/MC Ratio", 800, 800);
    c->Divide(1, 2);
    
    // Adjust the upper pad (stacked plot)
    TPad *pad1 = (TPad*)c->cd(1);
    pad1->SetPad(0, 0.3, 1, 1);
    pad1->SetBottomMargin(0.02); // Remove bottom margin to reduce gap
    
    hs->Draw("HIST"); // Draw the stacked backgrounds
    h_data->SetMarkerStyle(20);
    h_data->Draw("E SAME"); // Draw data points on top of the stack
    
    // Add a legend
    TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg->AddEntry(h_data, "Data", "lep");
    leg->AddEntry(h_bkg1, "Background 1", "f");
    leg->AddEntry(h_bkg2, "Background 2", "f");
    leg->Draw();

    // Adjust the lower pad (ratio plot)
    TPad *pad2 = (TPad*)c->cd(2);
    pad2->SetPad(0, 0, 1, 0.3);
    pad2->SetTopMargin(0.05);
    pad2->SetBottomMargin(0.3);

    // Create the Data/MC ratio plot
    TH1F *h_ratio = (TH1F*)h_data->Clone("h_ratio");
    h_ratio->Divide(h_bkg_total);
    h_ratio->SetLineColor(kBlack);
    h_ratio->SetMarkerStyle(20);
    h_ratio->SetTitle(""); // Remove the title for the ratio plot
    h_ratio->GetYaxis()->SetTitle("Data/MC");
    h_ratio->GetYaxis()->SetNdivisions(505);
    h_ratio->GetYaxis()->SetTitleSize(0.07);
    h_ratio->GetYaxis()->SetTitleOffset(0.5);
    h_ratio->GetYaxis()->SetLabelSize(0.07);
    h_ratio->GetXaxis()->SetTitleSize(0.1);
    h_ratio->GetXaxis()->SetLabelSize(0.1);
    
    h_ratio->Draw("E");

    // Draw a line at y=1 for reference
    TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
    line->SetLineColor(kRed);
    line->SetLineStyle(2);
    line->Draw();

    // Save the canvas to a file
    c->SaveAs("stacked_plot_with_ratio.png");

    // Clean up
    file->Close();
    delete file;
}
