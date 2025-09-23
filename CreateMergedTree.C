#include <TFile.h>
#include <TTree.h>
#include <TDirectory.h>
#include "include/MyBranch.C"//branch definitons
#include "include/Kinematics.C"//Kine fns
#include "include/MET_split.C"
#include "include/Xsections.C"

void CreateMergedTree(const char* ext = ".root"){
    // Output
    TFile* fout = new TFile("mergedTMVA_input.root", "RECREATE");
	TDirectory* tau0Dir = fout->mkdir("0tau");
	TDirectory* tau1Dir = fout->mkdir("1tau");
	TDirectory* tau2Dir = fout->mkdir("2tau");
	TDirectory* tau3Dir = fout->mkdir("3tau");
	TDirectory* lep3tau0Dir = fout->mkdir("3lep0tau");
	TDirectory* lep3tau1Dir = fout->mkdir("3lep1tau");
	TDirectory* lep3tau2Dir = fout->mkdir("3lep2tau");
	
	const char* inDir = "hist_MY/";
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
	
	double mll1, mll2, dR1, dR2, evtwt;
    int classID;
    
    std::map<std::string, TTree*> newTree;
    for(auto rootDirName: {"0tau","1tau","2tau","3tau","3lep0tau","3lep1tau","3lep2tau"}){
		newTree[rootDirName] = new TTree("Events", "Merged Events");
		newTree[rootDirName]->Branch("mll1", &mll1);
		newTree[rootDirName]->Branch("mll2", &mll2);
		newTree[rootDirName]->Branch("dR1", &mll1);
		newTree[rootDirName]->Branch("dR2", &mll2);
		newTree[rootDirName]->Branch("evtwt", &evtwt);
		newTree[rootDirName]->Branch("classID", &classID);
	}
		
	for(int j = 0; j < nfiles; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		std::string fname = filename[j];
		if (fname.find("nuisance") < fname.length()) continue;
		//if (fname.find("DY") < fname.length()) continue;
		if (fname.find("_201") > fname.length()) continue;
		if (XSec(filename[j])==1) continue;
		
		if (fname.find("HppM500") < fname.length()) classID = 1;
		else if(fname.find("HppM") > fname.length()) classID = 0;
		else continue;
		cout<<filename[j]<<endl;

		double xs_wt = applyXSec(ifile);
		cout<<"BALSNASLAS ";
		for(auto rootDirName: {"0tau","1tau","2tau","3tau","3lep0tau","3lep1tau","3lep2tau"}){
			std::string treeName = rootDirName;
			treeName += "/Events";
			TTree *tree = (TTree*)ifile->Get(treeName.c_str());
			
			evtwt *= xs_wt;
			tree->SetBranchAddress("mll1",&mll1);
			tree->SetBranchAddress("mll2",&mll2);
			tree->SetBranchAddress("dR1",&dR1);
			tree->SetBranchAddress("dR2",&dR2);
			tree->SetBranchAddress("evtwt",&evtwt);
			
			Long64_t nentries = tree->GetEntries();
			
			for (Long64_t i = 0; i < nentries; ++i) {
				tree->GetEntry(i);
				newTree[rootDirName]->Fill();
			}
		}
	}
    fout->cd();
    for(auto rootDirName: {"0tau","1tau","2tau","3tau","3lep0tau","3lep1tau","3lep2tau"}){
    	TDirectory* dir = (TDirectory*)fout->Get(rootDirName);
    	dir->cd();
    	newTree[rootDirName]->Write();
    }
    fout->Close();

    std::cout << "===> Merged tree saved to merged_input.root" << std::endl;
}
