#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>

void CreateHist(TTree* tree, const char* variable, const char* title, const char* xTitle, const char* yTitle, int bins, double xmin, double xmax) {
    // Create a canvas
    TCanvas* canvas = new TCanvas("canvas", "Histogram Canvas", 800, 600);
	double branch;
	tree->SetBranchAddress(variable, &branch)
    // Create a histogram
    TH1F* histogram = new TH1F("histogram", title, bins, xmin, xmax);

    // Draw the variable from the tree into the histogram
    tree->Draw(Form("%s >> histogram", variable));

}
