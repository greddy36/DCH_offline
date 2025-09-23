//Makes 2D hist from trees
#include "TMath.h"
#include <cmath>
#include <vector>
#include "TF1.h"
#include "TFile.h"
#include <TDirectory.h>
#include "include/Xsections.C"


void Signal_2Dfit(const char* ext = ".root"){
	const char* inDir = "hist_MY/";
	char* dir = gSystem->ExpandPathName(inDir);
	void* dirp = gSystem->OpenDirectory(dir);
	const char* entry;
	const char* filename[300];
	TString str; Int_t nfiles = 0;
	while((entry = (char*)gSystem->GetDirEntry(dirp))){
	  	str = entry;
	  	if(str.EndsWith(ext)){
			filename[nfiles++] = gSystem->ConcatFileName(dir, entry);
	  	}
	}
	gROOT->Reset();

	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		std::string fname = filename[j];
		std::string prefix = inDir;
		size_t pos = fname.find(prefix);
		if (pos != std::string::npos) {
		    fname.erase(pos, prefix.length());
		}
		if (fname.find("nuisance") < fname.length()) continue;
		if (fname.find("HppM5") > fname.length()) continue;
		if (XSec(filename[j])==1) continue; 
		cout<<fname<<endl;
		
		std::string root_dir[] = {"0tau/","1tau/","2tau/","3tau/"/*,"3lep0tau/","3lep1tau/","3lep2tau/"*/};
		const char* o_name = "hist_2D";
		char *oname = gSystem->ConcatFileName(o_name, fname.c_str());
		TFile* ofile = new TFile(oname, "RECREATE"); 
		for (auto & dir_name : root_dir){
			TCanvas* c = new TCanvas("c", "2D Fit", 800, 600);
			std::string tree_name = dir_name + "Events";
			TTree *tree = (TTree*)ifile->Get(tree_name.c_str());

			TH2F* h2 = new TH2F("h2", "mll1 vs mll2; mll1 [GeV]; mll2 [GeV]", 100, 0, 2000, 100, 0, 2000);
			std::ostringstream expr;
			expr << "evtwt*" <<applyXSec(ifile);
			tree->Draw("mll2:mll1 >> h2", (expr.str()).c_str(), "COLZ");
			TF2* f2 = new TF2("f2", "[0]*(x - y - [2])*(x - y - [2]) +[1]*(x + y - [3])*(x + y - [3]) - [4]*[4]", 0, 500, 0, 500);
			f2->SetParameters(0.3, 1.0, 100, 500, 5000);  // x0, y0, c
			//h2->Fit("f2", "R");  // R = fit only in specified range
			f2->SetLineColor(kRed);
			f2->SetLineWidth(2);
			TDirectory* tauDir = ofile->mkdir(dir_name.c_str());
			tauDir->cd();
			f2->Draw("same");
			h2->Write();
			//f2->Write();
			delete tree; delete h2; delete f2;
		}
		ofile->Close(); ifile->Close();
	}
	gSystem->FreeDirectory(dirp);
}
