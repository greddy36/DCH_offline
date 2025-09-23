//To apply various kinematics selections right after online analysis.
#include "TMath.h"
#include <cmath>
#include <vector>
#include "TF1.h"
#include "TFile.h"
#include <TDirectory.h>
#include "include/Xsections.C"


void skim_trees(const char* ext = ".root"){
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
		//if (fname.find("ttZ") > fname.length() and fname.find("ZH") > fname.length()) continue;
		if (XSec(filename[j])==1) continue; 
		cout<<fname<<endl;
		
		std::string root_dir[] = {"0tau/","1tau/","2tau/","3tau/"/*,"3lep0tau/","3lep1tau/","3lep2tau/"*/};
		const char* o_name = "hist_mll";
		char *oname = gSystem->ConcatFileName(o_name, fname.c_str());
		TFile* ofile = new TFile(oname, "RECREATE"); 
		for (auto & dir_name : root_dir){
			std::string tree_name = dir_name + "Events";
			TTree *tree = (TTree*)ifile->Get(tree_name.c_str());
			for (float w = 0; w <= 1.1; w +=0.1){
				//cout<<w<<endl;
				std::ostringstream oss;
				oss << "h_" << std::fixed << std::setprecision(1) << w ;
				std::string histName = oss.str();

				std::ostringstream expr;
				expr << "(" << w << ")*mll1 + (" << (1 - w) << ")*mll2";

				TH1F* h = new TH1F(histName.c_str(), (expr.str()+";"+expr.str()+" [GeV]; Events").c_str(), 1000, 0, 2000);
				tree->Draw((expr.str() + ">>" + histName).c_str(), "evtwt");		
				TDirectory* tauDir = ofile->mkdir(dir_name.c_str());
				tauDir->cd();
				h->Write();
				delete h;
			}
			delete tree;
		}
		ofile->Close(); ifile->Close();
	}
	gSystem->FreeDirectory(dirp);
}

