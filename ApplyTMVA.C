#include <TMVA/Reader.h>
#include "include/Xsections.C"

void ApplyTMVA(const char* ext = ".root"){
	const char* inDir = "hist_MY";
	char* dir = gSystem->ExpandPathName(inDir);
	void* dirp = gSystem->OpenDirectory(dir);
	const char* entry;
	const char* filename[100];
	TString str; Int_t nfiles = 0;
	while((entry = (char*)gSystem->GetDirEntry(dirp))){
	  	str = entry;
	  	if(str.EndsWith(ext)){
			filename[nfiles++] = gSystem->ConcatFileName(dir, entry);
	  	}
	}
	gROOT->Reset();
	
	std::vector<std::pair<TString, TString>> samples;
	for(int j = 0; j < nfiles; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		std::string fname = filename[j];
		if (fname.find("nuisance") < fname.length()) continue;
		//if (fname.find("DY") < fname.length()) continue;
		if (fname.find("_201") > fname.length()) continue;
		if (XSec(filename[j])==1) continue;
		
		std::string oname = "mva_"+fname;
		samples.push_back(std::make_pair(fname, oname));
	}
    // TMVA Reader
    TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

    double mll1, mll2, dR1, dR2, evtwt;
    float mll_1, mll_2, dR_1, dR_2, evtwt_nom;
    reader->AddVariable("mll1", &mll_1);
    reader->AddVariable("mll2", &mll_2);
    reader->AddVariable("dR1", &dR_1);
    reader->AddVariable("dR2", &dR_2);
    reader->BookMVA("BDT", "dataset/weights/TMVAClassification_BDT.weights.xml");


    for (auto [inname, outname] : samples) {
        TFile* fin = TFile::Open(inname);
        TFile* fout = new TFile(outname, "RECREATE");
        TH1D* hNWEvts = (TH1D*)fin->Get("hNWEvts");
        hNWEvts->Write();
	    TDirectory* tau0Dir = fout->mkdir("0tau");
		TDirectory* tau1Dir = fout->mkdir("1tau");
		TDirectory* tau2Dir = fout->mkdir("2tau");
		TDirectory* tau3Dir = fout->mkdir("3tau");
		TDirectory* lep3tau0Dir = fout->mkdir("3lep0tau");
		TDirectory* lep3tau1Dir = fout->mkdir("3lep1tau");
		TDirectory* lep3tau2Dir = fout->mkdir("3lep2tau"); 
		
		for(auto rootDirName: {"0tau","1tau","2tau","3tau","3lep0tau","3lep1tau","3lep2tau"}){
			std::string treeName = rootDirName;
			TDirectory *dir = (TDirectory*)fin->Get(rootDirName);
			TTree* tin = (TTree*)dir->Get("Events");
			
		    tin->SetBranchAddress("mll1", &mll1);
		    tin->SetBranchAddress("mll2", &mll2);
		    tin->SetBranchAddress("dR1", &dR1);
		    tin->SetBranchAddress("dR2", &dR2);
		    tin->SetBranchAddress("evtwt", &evtwt);
		    TDirectory* odir = (TDirectory*)fout->Get(rootDirName);
    		odir->cd();
		    TTree* tout = tin->CloneTree(0);

		    float mvaScore;
		    TBranch* b_mva = tout->Branch("mvaScore", &mvaScore, "mvaScore/F");

		    for (Long64_t i = 0; i < tin->GetEntries(); ++i) {
		        tin->GetEntry(i);
		        mll_1 = mll1;
		   		mll_2 = mll2;
		   		dR_1 = dR1;
		   		dR_2 = dR2;
		   		evtwt_nom = evtwt*applyXSec(fin);
		        mvaScore = reader->EvaluateMVA("BDT");
		        tout->Fill();
		    }
		    
		    tout->Write();
		}
		
	    fout->Close();
		fin->Close();

        std::cout << "===> Saved MVA-applied tree to " << outname << std::endl;
    }
}
