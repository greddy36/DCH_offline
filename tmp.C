#include <TFile.h>
#include <TH1.h>
#include <iostream>

int tmp() {
    // Paths to the ROOT files
    const char* file1Path = "tmp/ZZZ_2018.root";
    const char* file2Path = "ZZZ_2018.root";

    // Name of the histogram to copy
    const char* histName = "hNWEvts";

    // Open the first ROOT file in read mode
    TFile* file1 = TFile::Open(file1Path, "READ");
    if (!file1 || file1->IsZombie()) {
        std::cerr << "Error: Could not open file1!" << std::endl;
        return 1;
    }

    // Get the histogram from the first file
    TH1* hist = dynamic_cast<TH1*>(file1->Get(histName));
    if (!hist) {
        std::cerr << "Error: Histogram '" << histName << "' not found in file1!" << std::endl;
        file1->Close();
        return 1;
    }

    // Open the second ROOT file in update mode
    TFile* file2 = TFile::Open(file2Path, "UPDATE");
    if (!file2 || file2->IsZombie()) {
        std::cerr << "Error: Could not open file2!" << std::endl;
        file1->Close();
        return 1;
    }

    // Write the histogram into the second file
    file2->cd();
    hist->Write();  // Writes the histogram into the current directory of file2
    std::cout << "Histogram '" << histName << "' added to file2." << std::endl;

    // Close the files
    file1->Close();
    file2->Close();

    return 0;
}
