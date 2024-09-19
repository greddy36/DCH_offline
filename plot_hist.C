//THis is to print out all the input shape hists of HC input file
#include <iostream>
#include <TFile.h>
#include <TKey.h>
#include <TList.h>
#include <TCanvas.h>

void plotAllHistograms(const char* filename) {
    // Open the ROOT file
    TFile *file = new TFile(filename);
    
    // Check if the file is open successfully
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return;
    }

    // Create a canvas to display the histograms
    TCanvas *canvas = new TCanvas("canvas", "All Histograms", 800, 400);
    //canvas->Divide(2, 2);  // You can adjust the division based on the number of histograms

    // Get the list of keys in the file
    TList *keys = file->GetListOfKeys();

    // Loop over the keys and plot histograms
    int padIndex = 1;
    TIter next(keys);
    TKey *key;
    while ((key = dynamic_cast<TKey*>(next()))) {
    	std::string name = key->GetName();
		cout<<name<<endl;
    	if ( name.find("data") < name.length() ) continue;
        //if (key->IsA()->InheritsFrom("TH1F")) {
            // Retrieve and plot the histogram
            canvas->cd(padIndex);
            TH1 *histogram = dynamic_cast<TH1*>(key->ReadObj());
            cout<<name<< "\t" << histogram->Integral() <<endl;
            if (name.find("signal") < name.length()) histogram->SetTitle(const_cast<char*>(name.c_str()));
            else if (name.find("prompt") < name.length()) histogram->SetTitle(const_cast<char*>(name.c_str()));
            else if (name.find("fake") < name.length()) histogram->SetTitle(const_cast<char*>(name.c_str()));
            histogram->Draw("hist");
            name.append(".png");
            char* title = const_cast<char*>(name.c_str());//converting string to char
			canvas->SaveAs(title);
            padIndex++;
        //}
    }

    // Close the file
    file->Close();
}

void plot_hist() {
    // Replace "your_file.root" with the actual path to your ROOT file
    const char* filename = "hist_APre/nuisance_hist_test.root";

    // Call the function to plot all histograms in the file
    plotAllHistograms(filename);
}
