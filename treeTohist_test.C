
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TKey.h>
#include <TClass.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


const char* numberToCat(int number){
    static const char* cat_names[] = {
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
          "ee","em","et","mm","mt","tt","e","m","t"};
 	// Check if the index is within the valid range
    if (number < 1 || number > sizeof(cat_names)) {
        return "Invalid";
    }
    // Return the corresponding cat name
    return cat_names[number - 1];
}

int cat_lepCount(string cat, char lep1, char lep2){//usully I count only e and m. 
    int count = 0;
    for (int i = 0; i<cat.length(); i++){
        if (cat[i] == lep1 or cat[i] == lep2 )
            count++;
    }
    return count;
}
// ============================================================
// Configuration
// ============================================================

vector<string> fullChList = {
    "0tau",
    "1tau",
    "2tau",
    "3tau",
    "3lep0tau",
    "3lep1tau",
    "3lep2tau"
};

vector<string> fullSystList = {
    "", // nominal
    "eIdIso",
    "eReco",
    "eTrig",
    "l1Prefire",
    "muId",
    "muIso",
    "muTrig",
    "roccor",
    "tauES",
    "tauVsEle",
    "tauVsJet",
    "tauVsMu",
    "xsec"
};


// ============================================================
// Create missing histograms
// ============================================================

void makeMissingHist(TFile* fout)
{
    fout->cd();

    for (const string& Ch : fullChList) {
        for (const string& Syst : fullSystList) {
            for (const string& var :
                 {"mll1","mll2","mDCH1","mDCH2","mH1","mH2"}) {

                for (const string& delta : {"Up","Down"}) {

                    string histname = "h_" + var + "_" + Ch;

                    if (Syst != "")
                        histname += "_" + Syst + delta;

                    if (fout->Get(histname.c_str()))
                        continue;

                    cout << "Creating empty histogram: "
                         << histname << endl;

                    double xmin = 0;
                    double xmax = 2000;
                    int nBins = 100;

                    TH1D* h = new TH1D(
                        histname.c_str(),
                        histname.c_str(),
                        nBins,
                        xmin,
                        xmax
                    );

                    h->Sumw2();
                    h->Write();

                    delete h;
                }
            }
        }
    }
}


// ============================================================
// Main
// ============================================================

void treeTohist_test(
    string inputFile =
        "../athar_offline/masstree_HppM1000_2018.root",

    string outputFile =
        "hist_DYJetsToLLM50_2016postVFP.root"
)
{
    TFile *fin = TFile::Open(inputFile.c_str(), "READ");

    if (!fin || fin->IsZombie()) {
        cerr << "ERROR: Cannot open "
             << inputFile << endl;
        return;
    }

    TFile *fout = TFile::Open(
        outputFile.c_str(),
        "RECREATE"
    );

    if (!fout || fout->IsZombie()) {
        cerr << "ERROR: Cannot create "
             << outputFile << endl;
        return;
    }


    // ========================================================
    // Loop over objects in input ROOT file
    // ========================================================

    TIter next(fin->GetListOfKeys());
    TKey *key;

    while ((key = (TKey*)next())) {

        TObject *obj = key->ReadObj();

        if (!obj->InheritsFrom(TTree::Class())) {
            delete obj;
            continue;
        }

        TTree *tree = (TTree*)obj;

        string treeName = tree->GetName();


        // ----------------------------------------------------
        // Only process Events_* trees
        // ----------------------------------------------------

        if (treeName.find("Events_") != 0) {
            delete obj;
            continue;
        }


        // ----------------------------------------------------
        // Determine channel and systematic
        // ----------------------------------------------------

        string name = treeName.substr(7);

        string channel;
        string systematic = "";

        size_t pos = name.find("_");

        if (pos == string::npos) {
            channel = name;
        }
        else {
            channel = name.substr(0, pos);
            systematic = name.substr(pos + 1);
        }

        cout << "Processing tree: "
             << treeName
             << "  channel=" << channel
             << "  systematic=" << systematic
             << endl;

		//if (channel == "1tau") channel = "3lep0tau";
        // ====================================================
        // Create histograms for this tree
        // ====================================================

        map<string, TH1D*> hist;

        for (const string& branchName :
             {"mll1","mll2","mDCH1","mDCH2","mH1","mH2"}) {

            string histName =
                "h_" + branchName + "_" + channel;

            if (!systematic.empty())
                histName += "_" + systematic;

            hist[branchName] = new TH1D(
                histName.c_str(),
                histName.c_str(),
                100,
                0,
                2000
            );

            hist[branchName]->Sumw2();
        }


        // ====================================================
        // Branch variables
        // ====================================================

        Double_t mll1;
        Double_t mll2;
        Double_t mDCH1;
        Double_t mDCH2;
        Double_t mH1;
        Double_t mH2;
		Int_t gencat;
        Double_t evtwt = 1.0;


        tree->SetBranchAddress("mll1",   &mll1);
        tree->SetBranchAddress("mll2",   &mll2);
        tree->SetBranchAddress("mDCH1",  &mDCH1);
        tree->SetBranchAddress("mDCH2",  &mDCH2);
        tree->SetBranchAddress("mH1",    &mH1);
        tree->SetBranchAddress("mH2",    &mH2);

        // Change this to the actual branch containing
        // your event weight.
        tree->SetBranchAddress("evtwt", &evtwt);
        tree->SetBranchAddress("gencat", &gencat);


        // ====================================================
        // EVENT LOOP
        // ====================================================

        Long64_t nEntries = tree->GetEntries();

        cout << "Number of events: "
             << nEntries << endl;

        for (Long64_t i = 0; i < nEntries; i++) {

            tree->GetEntry(i);


            // ------------------------------------------------
            // Calculate / modify event weight HERE
            // ------------------------------------------------

            double weight = evtwt;
	/*
            string cat_string = numberToCat(gencat);
            char* cat_name = const_cast<char*>(cat_string.c_str());
			int Nlep = cat_lepCount(cat_name,'e','m'); 
			int Ntau = strlen(cat_name)-Nlep;
			
			if (Ntau == 0) weight *= 0;
			else if (Ntau == 1) weight *= 0;
			else if (Ntau == 2) weight *= 0;
			else if (Ntau == 3) weight *= 0;
			else if (Ntau == 4) weight *= 36;
	*/		
            // ------------------------------------------------
            // Fill histograms
            // ------------------------------------------------
			
            hist["mll1"]->Fill(mll1, weight);
            hist["mll2"]->Fill(mll2, weight);
            hist["mDCH1"]->Fill(mDCH1, weight);
            hist["mDCH2"]->Fill(mDCH2, weight);
            hist["mH1"]->Fill(mH1, weight);
            hist["mH2"]->Fill(mH2, weight);
        }


        // ====================================================
        // Write histograms
        // ====================================================

        fout->cd();

        for (auto& item : hist) {

            TH1D* h = item.second;

            // Temporary protection against negative integral
            if (h->Integral() < 0) {
                cout << "WARNING: "
                     << h->GetName()
                     << " has negative integral. Setting to zero."
                     << endl;

                h->Scale(0);
            }

            h->Write();

            delete h;
        }


        delete obj;
    }


    // ========================================================
    // Create any missing histograms
    // ========================================================

    makeMissingHist(fout);


    // ========================================================
    // Close files
    // ========================================================

    fout->Close();
    fin->Close();

    cout << "\nDone. Histograms written to "
         << outputFile << endl;
}
