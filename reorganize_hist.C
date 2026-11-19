#include <TFile.h>
#include <TDirectory.h>
#include <TH1.h>
#include <TKey.h>
#include <TClass.h>
#include <TROOT.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void reorganize_hist(string inputFile  = "hist_HppM1300_2016postVFP.root")
{//puts h_<var>_<ch>_<blabla> into <ch> directory as h_<var>_<blabla>
    string outputFolder = "hist_peter/";

    vector<string> channels = {
        "0tau",
        "1tau",
        "2tau",
        "3tau",
        "3lep0tau",
        "3lep1tau",
        "3lep2tau"
    };


    TFile* fin = TFile::Open(inputFile.c_str(), "READ");
    if (!fin || fin->IsZombie()) {
        cerr << "Cannot open input file" << endl;
        return;
    }
    string outputFile = outputFolder + "inputFile";
    TFile* fout = TFile::Open(outputFile.c_str(), "RECREATE");

    // Create channel directories
    for (const string& ch : channels)
        fout->mkdir(ch.c_str());

    TIter next(fin->GetListOfKeys());
    TKey* key;

    while ((key = (TKey*)next()))
    {
        TClass* cl = gROOT->GetClass(key->GetClassName());
        if (!cl || !cl->InheritsFrom(TH1::Class()))
            continue;

        TH1* h = (TH1*)key->ReadObj();
        string name = h->GetName();

        bool found = false;

        for (const string& ch : channels)
        {
            string pattern = "_" + ch;

            size_t pos = name.find(pattern);

            if (pos == string::npos)
                continue;

            // Ensure channel is a complete token
            size_t end = pos + pattern.size();

            if (end < name.size() && name[end] != '_')
                continue;

            // Remove channel from histogram name
            string newName = name;
            newName.erase(pos, pattern.size());

            TDirectory* dir = fout->GetDirectory(ch.c_str());
            dir->cd();

            h->SetName(newName.c_str());
            h->Write();

            cout << name << " -> "
                 << ch << "/" << newName << endl;

            found = true;
            break;
        }

        if (!found)
            cout << "Skipping: " << name << endl;

        delete h;
    }

    // No fout->Write() needed; histograms already written
    fout->Close();
    fin->Close();

    delete fout;
    delete fin;

    cout << "Done!" << endl;
}
