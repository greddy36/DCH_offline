#include <TFile.h>
#include <TH1.h>
#include <TKey.h>
#include <TString.h>
#include <iostream>
#include <map>

void combine_channels(const char* input = "combined_hist.root",
                      const char* output = "combined.root")
{
    TFile *fin = TFile::Open(input, "READ");
    TFile *fout = TFile::Open(output, "RECREATE");

    std::map<TString, TH1*> combined;

    TString channels[] = {
        "eeee", "eeem", "eeet", "eemm", "eemt", "eett",
        "emem", "emet", "emmm", "emmt", "emtt",
        "etet", "etmm", "etmt", "ettt",
        "mmmm", "mmmt", "mmtt",
        "mtmt", "mttt",
        "tttt",

        "eee", "eem", "eet",
        "eme", "emm", "emt",
        "ete", "etm", "ett",
        "mme", "mmm", "mmt",
        "mte", "mtm", "mtt",
        "tte", "ttm", "ttt",
    };

    TIter next(fin->GetListOfKeys());
    TKey *key;

    while ((key = (TKey*)next())) {

        TString name = key->GetName();

        if (!name.BeginsWith("h_LT_"))
            continue;

        TH1 *h = (TH1*)fin->Get(name);
        if (!h)
            continue;

        // Remove h_LT_<ch>_  -->  h_LT_
        TString newName = name;

        for (auto ch : channels) {
            TString pattern = "h_LT_" + ch + "_";

            if (newName.BeginsWith(pattern)) {
                newName.Replace(0, pattern.Length(), "h_LT_");
                break;
            }
        }

        // First histogram with this name
        if (combined.find(newName) == combined.end()) {
            combined[newName] = (TH1*)h->Clone(newName);
            combined[newName]->SetDirectory(nullptr);
        }
        // Add subsequent channels
        else {
            combined[newName]->Add(h);
        }
    }

    fout->cd();

    for (auto &it : combined)
        it.second->Write();

    fout->Close();
    fin->Close();

    std::cout << "Wrote " << combined.size()
              << " histograms to " << output << std::endl;
}