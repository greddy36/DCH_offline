#include <TFile.h>
#include <TH1.h>
#include <TKey.h>
#include <TDirectory.h>
#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <iostream>

void printLTRanges(TDirectory* dir)
{
    TIter next(dir->GetListOfKeys());
    while (auto key = (TKey*)next()) {
        // Read only the latest cycle.
        if (key->GetCycle() != dir->GetKey(key->GetName())->GetCycle())
            continue;

        TObject* obj = key->ReadObj();

        if (auto subdir = dynamic_cast<TDirectory*>(obj)) {
            printLTRanges(subdir);
        } else if (auto h = dynamic_cast<TH1*>(obj)) {
            if (TString(h->GetName()).Contains("h_LT")) {
                std::cout << dir->GetPath() << "/" << h->GetName()
                          << "  bins=" << h->GetNbinsX()
                          << "  xmin=" << h->GetXaxis()->GetXmin()
                          << "  xmax=" << h->GetXaxis()->GetXmax()
                          << '\n';
            }
        }

        delete obj;
    }
}

void check_LT_ranges(const char* directory = ".")
{
    TSystemDirectory folder("inputs", directory);
    TList* files = folder.GetListOfFiles();
    if (!files) return;

    TIter next(files);
    while (auto entry = (TSystemFile*)next()) {
        TString name = entry->GetName();
        if (entry->IsDirectory() || !name.EndsWith(".root")) continue;

        TFile* file = TFile::Open(TString(directory) + "/" + name);
        if (file && !file->IsZombie()) printLTRanges(file);
        delete file;
    }

    delete files;
}
