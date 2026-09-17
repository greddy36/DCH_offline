
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TKey.h>
#include <TClass.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
	"",//nominal
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


void makeMissingHist(TFile* fout){
    fout->cd();
    for (const string& Ch : fullChList) {
		for (const string& Syst : fullSystList) {
		for (const string& var : {"mll1","mll2","mDCH1","mDCH2","mH1","mH2"}){
		for (const string& delta : {"Up","Down"}){
			string histname = "h_"+var+"_"+Ch;//nominal
			if (Syst != "") histname += "_"+Syst+delta;			
		    if (fout->Get(histname.c_str())) continue;//skips already existing hists 
		    cout << "Creating empty histogram: " << histname << endl;
		    double xmin = 0, xmax = 2000;//if you change this you gotta change in the main function too!
		    TH1D* h = new TH1D(histname.c_str(), histname.c_str(), 100, xmin, xmax);
		    h->Sumw2();
		    h->Write();
		    delete h;
		}}}
	}
}

void treeTohist(string inputFile = "masstree_DYJetsToLLM50_2016postVFP.root",
               string outputFile = "hist_DYJetsToLLM50_2016postVFP.root")
{
    TFile *fin = TFile::Open(inputFile.c_str(), "READ");
    if (!fin || fin->IsZombie()) {
        cerr << "ERROR: Cannot open " << inputFile << endl;
        return;
    }

    TFile *fout = TFile::Open(outputFile.c_str(), "RECREATE");

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

        // Only process trees called Events_<channel>...
        if (treeName.find("Events_") != 0) {
            delete obj;
            continue;
        }

        // Remove "Events_"
        string name = treeName.substr(7);

        // Split channel and systematic
        // Example:
        //   3tau             -> channel=3tau, systematic=""
        //   3tau_JESUp       -> channel=3tau, systematic=JESUp
        //
        // If your channel names contain "_" this should be adjusted.

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

        cout << "Processing tree: " << treeName << "  channel=" << channel << "  systematic=" << systematic << endl;

        // Loop over branches
        TObjArray *branches = tree->GetListOfBranches();

        for (int i = 0; i < branches->GetEntries(); i++) {

            TBranch *branch = (TBranch*)branches->At(i);
            string branchName = branch->GetName();
			if (branchName =="evtwt" or branchName =="region")continue;
            // --------------------------------------------------
            // Get branch information
            // --------------------------------------------------

            TLeaf *leaf = branch->GetLeaf(branchName.c_str());

            if (!leaf) {
                cerr << "WARNING: Cannot find leaf for "
                     << branchName << endl;
                continue;
            }

            // Only handle numerical branches
            string type = leaf->GetTypeName();

            if (type != "Float_t" &&
                type != "Double_t" &&
                type != "Int_t" &&
                type != "UInt_t" &&
                type != "Long64_t" &&
                type != "ULong64_t") {

                cout << "Skipping non-numerical branch: "
                     << branchName << " (" << type << ")" << endl;
                continue;
            }

            // --------------------------------------------------
            // Determine histogram range automatically
            // --------------------------------------------------

            double xmin = 0;
            double xmax = 0;

            tree->Draw(
                Form("%s>>htemp(100)", branchName.c_str()),
                "",
                "goff"
            );

            TH1 *htemp = (TH1*)gDirectory->Get("htemp");

            if (!htemp || htemp->GetEntries() == 0) {
                cout << "Skipping empty branch: "
                     << branchName << endl;

                if (htemp)
                    delete htemp;

                continue;
            }
			if (branchName.find("mll")!=std::string::npos or branchName.find("m")!=std::string::npos){
				xmin = 0; xmax = 2000;
			}
            //xmin = htemp->GetXaxis()->GetXmin();
            //xmax = htemp->GetXaxis()->GetXmax();

            // Avoid zero-width histogram
            if (xmin == xmax) {
                xmin -= 0.5;
                xmax += 0.5;
            }

            delete htemp;

            string histName = "h_" + branchName + "_" + channel;

            if (!systematic.empty())
                histName += "_" + systematic;

            TH1D *hist = new TH1D(// Make histogram
                histName.c_str(),
                histName.c_str(),
                100,
                xmin,
                xmax
            );

            hist->Sumw2();
			//Fill the histogram
            tree->Draw(
                Form("%s>>%s", branchName.c_str(), histName.c_str()),
                "evtwt",//weigh the hist
                "goff"
            );

            fout->cd();
            hist->Write();

            delete hist;
        }
        delete obj;
    } 
    makeMissingHist(fout);
    fout->Close();
    fin->Close();

    cout << "\nDone. Histograms written to "
         << outputFile << endl;
}
