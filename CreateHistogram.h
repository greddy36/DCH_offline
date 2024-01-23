#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>

void CreateHistogram(TTree* tree, const char* variable, const char* title, const char* xTitle, const char* yTitle, int bins, double xmin, double xmax) {
    // Create a canvas
    TCanvas* canvas = new TCanvas("canvas", "Histogram Canvas", 800, 600);

    // Create a histogram
    TH1F* histogram = new TH1F("histogram", title, bins, xmin, xmax);

    // Draw the variable from the tree into the histogram
    tree->Draw(Form("%s >> histogram", variable));

    // Customize the histogram appearance
    histogram->GetXaxis()->SetTitle(xTitle);
    histogram->GetYaxis()->SetTitle(yTitle);
    histogram->SetLineColor(kBlue);  // Set line color to blue
    histogram->SetLineWidth(2);      // Set line width

    // Draw the histogram on the canvas
    histogram->Draw();

    // Save or display the canvas
    canvas->SaveAs("histogram.png");  // Save as an image file
    // canvas->Draw();  // Uncomment to display the canvas
}
