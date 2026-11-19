
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


// ============================================================
// MAKE FLATTENED mll1 x mll2 HISTOGRAM
// ============================================================
//
// One event contributes to ONE 2D bin:
//
//        (mll1, mll2)
//
// which is then converted to one 1D bin.
//
// Example for 3 x 3:
//
//          mll2
//
//          1   2   3
//       1  1   2   3
//       2  4   5   6
//       3  7   8   9
//
// Flattened:
//
// 1 2 3 4 5 6 7 8 9
//
// ============================================================

void makeFlattenedmassHist(TTree* tree, TFile* fout)
{
    // ============================================================
    // Check required branches
    // ============================================================
    if (!tree->GetBranch("mll1") ||
        !tree->GetBranch("mll2") ||
        !tree->GetBranch("mDCH1") ||
        !tree->GetBranch("mDCH2") ||
        !tree->GetBranch("evtwt")) {

        cout << "Skipping flattened 2D histograms for "
             << tree->GetName()
             << " because one or more required branches are missing."
             << endl;

        return;
    }

    // ============================================================
    // Declare variables
    // ============================================================

    Double_t mll1  = 0;
    Double_t mll2  = 0;
    Double_t mDCH1 = 0;
    Double_t mDCH2 = 0;
    Double_t evtwt = 0;

    // ============================================================
    // Connect branches
    // ============================================================

    tree->SetBranchAddress("mll1",  &mll1);
    tree->SetBranchAddress("mll2",  &mll2);
    tree->SetBranchAddress("mDCH1", &mDCH1);
    tree->SetBranchAddress("mDCH2", &mDCH2);
    tree->SetBranchAddress("evtwt", &evtwt);

    // ============================================================
    // 2D binning
    // ============================================================

    int nBins = 20;

    double xmin = 0;
    double xmax = 2000;

    int nFlatBins = nBins * nBins;

    // ============================================================
    // Histogram names
    // ============================================================
	string treeName = tree->GetName();
    string suffix = treeName.substr(7); //name is like Events_blabla. we want the blabla part

    string mllHistName  = "h_mll12flat_"  + suffix;
    string mDCHHistName = "h_mDCH12flat_" + suffix;

    // ============================================================
    // Create flattened histograms
    // ============================================================

    TH1D* h_mll =
        new TH1D(
            mllHistName.c_str(),
            mllHistName.c_str(),
            nFlatBins,
            0,
            nFlatBins
        );

    TH1D* h_mDCH =
        new TH1D(
            mDCHHistName.c_str(),
            mDCHHistName.c_str(),
            nFlatBins,
            0,
            nFlatBins
        );

    h_mll->Sumw2();
    h_mDCH->Sumw2();

    // ============================================================
    // Loop over events
    // ============================================================

    Long64_t nEntries = tree->GetEntries();

    for (Long64_t i = 0; i < nEntries; i++) {

        tree->GetEntry(i);

        // --------------------------------------------------------
        // mll1 / mll2
        // --------------------------------------------------------

        if (mll1 >= xmin && mll1 < xmax &&
            mll2 >= xmin && mll2 < xmax) {

            int bin1 =
                int((mll1 - xmin) / (xmax - xmin) * nBins) + 1;

            int bin2 =
                int((mll2 - xmin) / (xmax - xmin) * nBins) + 1;

            int flatBin =
                (bin1 - 1) * nBins + bin2;

            h_mll->Fill(flatBin - 0.5, evtwt);
        }

        // --------------------------------------------------------
        // mDCH1 / mDCH2
        // --------------------------------------------------------

        if (mDCH1 >= xmin && mDCH1 < xmax &&
            mDCH2 >= xmin && mDCH2 < xmax) {

            int bin1 =
                int((mDCH1 - xmin) / (xmax - xmin) * nBins) + 1;

            int bin2 =
                int((mDCH2 - xmin) / (xmax - xmin) * nBins) + 1;

            int flatBin =
                (bin1 - 1) * nBins + bin2;

            h_mDCH->Fill(flatBin - 0.5, evtwt);
        }
    }

    // ============================================================
    // Write histograms
    // ============================================================

    fout->cd();
	if ( h_mll->Integral() < 0) {//ONLY TEMPORARY TO REMOVE INVALID NORM. CHECK WHY THE HIST IS NEGATIVE!!!!
		h_mll->Scale(0);
	}
	if ( h_mDCH->Integral() < 0) {//ONLY TEMPORARY TO REMOVE INVALID NORM. CHECK WHY THE HIST IS NEGATIVE!!!!
		h_mDCH->Scale(0);
	}
    h_mll->Write();
    h_mDCH->Write();

    delete h_mll;
    delete h_mDCH;
}

void makeMissingHist(TFile* fout){
    fout->cd();
    for (const string& Ch : fullChList) {
		for (const string& Syst : fullSystList) {
		for (const string& var : {"mll1","mll2","mDCH1","mDCH2","mH1","mH2","mll12flat","mDCH12flat"}){
		for (const string& delta : {"Up","Down"}){
			string histname = "h_"+var+"_"+Ch;//nominal
			if (Syst != "") histname += "_"+Syst+delta;			
		    if (fout->Get(histname.c_str())) continue;//skips already existing hists 
		    cout << "Creating empty histogram: " << histname << endl;
		    double xmin = 0, xmax = 2000; int nBins = 100;//if you change this you gotta change in the main function too!
		    if (var.find("flat")!=string::npos){ xmax = 400; nBins = 400;}//nFlatBins
		    TH1D* h = new TH1D(histname.c_str(), histname.c_str(), nBins, xmin, xmax);
		    h->Sumw2();
		    h->Write();
		    delete h;
		}}}
	}
}

void treeTohist(string inputFile = "../athar_offline/masstree_HppM1000_2018.root",
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
		
        // Remove "Events_" string
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
			if (branchName =="evtwt" or branchName =="region" or branchName =="cat" or branchName =="gencat" )continue;
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
            //tree->Draw(Form("%s>>%s", branchName.c_str(), histName.c_str()), "evtwt", "goff");

            tree->Draw(Form("%s>>%s", branchName.c_str(), histName.c_str()), "evtwt*(mDCH2>200)", "goff");
           
            fout->cd();

			if (hist && hist->Integral() < 0) {//ONLY TEMPORARY TO REMOVE INVALID NORM. CHECK WHY THE HIST IS NEGATIVE!!!!
				hist->Scale(0);
			}
			
            hist->Write();

            delete hist;
        }
        makeFlattenedmassHist(tree, fout);
        delete obj;
    } //While loop
    makeMissingHist(fout);
    fout->Close();
    fin->Close();

    cout << "\nDone. Histograms written to "
         << outputFile << endl;
}
