#include <TFile.h>
#include <TDirectory.h>
#include <TKey.h>
#include <TH1.h>
#include <TObject.h>

#include <iostream>
#include <regex>
#include <string>

bool isSignal(const std::string& name)
{
    static const std::regex pattern("_M([0-9]+)$");
    std::smatch match;

    if (!std::regex_search(name, match, pattern))
        return false;

    const int mass = std::stoi(match[1].str());
    return mass >= 500 && mass <= 1500;
}

void copyHistograms(TDirectory* source, TDirectory* destination,
                    bool signalsOnly)
{
    TIter next(source->GetListOfKeys());

    while (auto key = static_cast<TKey*>(next())) {
        // Avoid copying older versions of the same object.
        if (key->GetCycle() != source->GetKey(key->GetName())->GetCycle())
            continue;

        TObject* obj = key->ReadObj();
        if (!obj) continue;

        if (auto subdir = dynamic_cast<TDirectory*>(obj)) {
            TDirectory* outdir = destination->GetDirectory(key->GetName());
            if (!outdir)
                outdir = destination->mkdir(key->GetName());

            copyHistograms(subdir, outdir, signalsOnly);
        }
        else if (auto hist = dynamic_cast<TH1*>(obj)) {
            if (isSignal(key->GetName()) == signalsOnly) {
                destination->cd();
                hist->Write(key->GetName(), TObject::kOverwrite);
                std::cout << source->GetPath() << "/"
                          << key->GetName() << '\n';
            }
        }

        delete obj;
    }
}

void combine_sources()
{
    TFile first("combined_hist_onlyTau.root", "READ");
    TFile second("combined_hist_LTmet.root", "READ");

    if (first.IsZombie() || second.IsZombie()) {
        std::cerr << "Cannot open an input file.\n";
        return;
    }

    TFile output("combined_onlyTau.root", "RECREATE");
    if (output.IsZombie()) {
        std::cerr << "Cannot create combined_hist_noTau.root.\n";
        return;
    }

    copyHistograms(&first,  &output, true);  // Signals
    copyHistograms(&second, &output, false); // Everything else

    output.Close();
    std::cout << "Saved combined_noTau.root\n";
}
