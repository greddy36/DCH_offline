//To apply various kinematics selections right after online analysis.
#include "TMath.h"
#include <cmath>
#include <vector>
#include "TF1.h"
#include "TFile.h"
#include <TDirectory.h>
#include "include/MyBranch.C"//branch definitons
#include "include/Kinematics.C"//Kine fns
#include "include/MET_split.C"
#include "include/Xsections.C"
#include "rjm_guru.C"
#include "rjm_final.C"
#include "rjm_test.C"
void processPairs( const char* cat_name, vector<pair<int, int>>& Z_pair, vector<pair<int, int>>& Zv_pair, vector<pair<int, int>>& SS_pair, vector<pair<int,int>>& OSOF_pair) {//global function to process pairs
	int len = strlen(cat_name);
	for (int m = 1; m <= len; ++m) {
		for (int n = m + 1; n <= len; ++n) {
			string pair_name = pairFunc(m, n, cat_name, 20);
			if (pair_name == "Zwindow") Z_pair.push_back({m,n});
			else if (pair_name == "Zv") Zv_pair.push_back({m,n});
			else if (pair_name == "ZttPair") Zv_pair.push_back({m,n});
			else if (pair_name == "OSOFpair") OSOF_pair.push_back({m,n});
			else if (pair_name == "SSpair") SS_pair.push_back({m,n});
			else continue;
		}
	}
}

void n_minus_one_cutflow(const std::string& excludeCut,
                         std::map<std::string, TH1D*>& cutflowHists,
                         const std::string& channel,
                         const std::map<std::string, bool>& cutbools)
{
    const std::vector<std::string> cutNames = {"M_ll1","M_ll1+M_ll2 >= 500","ST", "dRll", "dRlplm"};

    // Safety check
    if (cutflowHists.find(channel) == cutflowHists.end()) {
        std::cerr << "Warning: Channel '" << channel << "' not found in cutflow map!" << std::endl;
        return;
        
    }

    bool pass = true;
    for (const auto& cut : cutNames) {
        if (cut == excludeCut) continue;
        auto it = cutbools.find(cut);
        if (it == cutbools.end() || !it->second) {
            pass = false;
            break;
        }
    }

    if (pass) {
        int bin = cutflowHists[channel]->GetXaxis()->FindBin(excludeCut.c_str());
        cutflowHists[channel]->AddBinContent(bin);
    }
}



void FillHists(TDirectory* rootDir, std::map<std::string, TTree*> trim_tree, std::map< std::string, double > hist_variable_map, double evtwt_nom, 
				std::map<std::string, TH1D*> cutflow, std::map<std::string, TH1D*> h_mll1, std::map<std::string, TH1D*> h_mll2, std::map<std::string, TH1D*> h_mDCH1, std::map<std::string, TH1D*> h_mDCH2, std::map<std::string, TH1D*> h_ll1_pt, std::map<std::string, TH1D*> h_ST, std::map<std::string, TH1D*> h_mZ1, std::map<std::string, TH1D*> h_mZ2, std::map<std::string, TH1D*> h_mZ3, std::map<std::string, TH1D*> h_mZ4, std::map<std::string, TH1D*> h_mT1, std::map<std::string, TH1D*> h_mT2, std::map<std::string, TH1D*> h_mTtot1, std::map<std::string, TH1D*> h_mTtot2, std::map<std::string, TH1D*> h_mT1_opp, std::map<std::string, TH1D*> h_mT2_opp, std::map<std::string, TH1D*> h_mT3_opp, std::map<std::string, TH1D*> h_mT4_opp, std::map<std::string, TH1D*> h_mTtot1_opp, std::map<std::string, TH1D*> h_mTtot2_opp, std::map<std::string, TH1D*> h_mTtot3_opp, std::map<std::string, TH1D*> h_mTtot4_opp, std::map<std::string, TH1D*> h_met, std::map<std::string, TH1D*> h_pT1, std::map<std::string, TH1D*> h_pT2, std::map<std::string, TH1D*> h_pT3, std::map<std::string, TH1D*> h_pT4, std::map<std::string, TH1D*> h_dR1, std::map<std::string, TH1D*> h_dR2, std::map<std::string, TH1D*> h_dR3, std::map<std::string, TH1D*> h_dR4, std::map<std::string, TH1D*> h_dRll, std::map<std::string, TH1D*> h_dRll2, std::map<std::string, TH1D*> h_dR1_met, std::map<std::string, TH1D*> h_dR2_met, std::map<std::string, TH1D*> h_max_dR_lplm, std::map<std::string, TH1D*> h_max_dR_ll,  std::map<std::string, TH1D*> h_dPhiW_met, std::map<std::string, TH1D*> h_W_mt, std::map<std::string, TH1D*> h_cat, std::map<std::string, TH1D*> h_gencat){
	rootDir->cd();
	const char* dirName = rootDir->GetName();
	trim_tree[dirName]->Fill();
	cutflow[dirName]->Fill(hist_variable_map["cutflow"], evtwt_nom);
	h_mll1[dirName]->Fill(hist_variable_map["mll1"], evtwt_nom);
	h_mll2[dirName]->Fill(hist_variable_map["mll2"], evtwt_nom);
	h_mDCH1[dirName]->Fill(hist_variable_map["mDCH1"], evtwt_nom);
	h_mDCH2[dirName]->Fill(hist_variable_map["mDCH2"], evtwt_nom);
	h_mZ1[dirName]->Fill(hist_variable_map["mZ1"], evtwt_nom);
	h_mZ2[dirName]->Fill(hist_variable_map["mZ2"], evtwt_nom);
	h_mZ3[dirName]->Fill(hist_variable_map["mZ3"], evtwt_nom);
	h_mZ4[dirName]->Fill(hist_variable_map["mZ4"], evtwt_nom);
	h_mT1[dirName]->Fill(hist_variable_map["mT1"], evtwt_nom);
	h_mT2[dirName]->Fill(hist_variable_map["mT2"], evtwt_nom);
	h_mTtot1[dirName]->Fill(hist_variable_map["mTtot1"], evtwt_nom);
	h_mTtot2[dirName]->Fill(hist_variable_map["mTtot2"], evtwt_nom);
	h_mT1_opp[dirName]->Fill(hist_variable_map["mT1_opp"], evtwt_nom);
	h_mT2_opp[dirName]->Fill(hist_variable_map["mT2_opp"], evtwt_nom);
	h_mT3_opp[dirName]->Fill(hist_variable_map["mT3_opp"], evtwt_nom);
	h_mT4_opp[dirName]->Fill(hist_variable_map["mT4_opp"], evtwt_nom);
	h_mTtot1_opp[dirName]->Fill(hist_variable_map["mTtot1_opp"], evtwt_nom);
	h_mTtot2_opp[dirName]->Fill(hist_variable_map["mTtot2_opp"], evtwt_nom);
	h_mTtot3_opp[dirName]->Fill(hist_variable_map["mTtot3_opp"], evtwt_nom);
	h_mTtot4_opp[dirName]->Fill(hist_variable_map["mTtot4_opp"], evtwt_nom);
	h_ll1_pt[dirName]->Fill(hist_variable_map["ll1_pt"], evtwt_nom);//need to sort the pt order!!
	h_ST[dirName]->Fill(hist_variable_map["ST"], evtwt_nom);
	h_met[dirName]->Fill(hist_variable_map["met"], evtwt_nom);
	h_pT1[dirName]->Fill(hist_variable_map["pT1"], evtwt_nom);
	h_pT2[dirName]->Fill(hist_variable_map["pT2"], evtwt_nom);
	h_pT3[dirName]->Fill(hist_variable_map["pT3"], evtwt_nom);
	h_pT4[dirName]->Fill(hist_variable_map["pT4"], evtwt_nom);
	h_dR1[dirName]->Fill(hist_variable_map["dR1"], evtwt_nom);
	h_dR2[dirName]->Fill(hist_variable_map["dR2"], evtwt_nom);
	h_dR3[dirName]->Fill(hist_variable_map["dR3"], evtwt_nom);
	h_dR4[dirName]->Fill(hist_variable_map["dR4"], evtwt_nom);
	h_dRll[dirName]->Fill(hist_variable_map["dRll"], evtwt_nom);
	h_dRll2[dirName]->Fill(hist_variable_map["dRll2"], evtwt_nom);
	h_dR1_met[dirName]->Fill(hist_variable_map["dR1_met"], evtwt_nom);
	h_dR2_met[dirName]->Fill(hist_variable_map["dR2_met"], evtwt_nom);
	h_max_dR_lplm[dirName]->Fill(hist_variable_map["max_dR_lplm"], evtwt_nom);
	h_max_dR_ll[dirName]->Fill(hist_variable_map["max_dR_ll"], evtwt_nom);
	h_dPhiW_met[dirName]->Fill(hist_variable_map["dPhiW_met"], evtwt_nom);
	h_W_mt[dirName]->Fill(hist_variable_map["W_mt"], evtwt_nom);
	h_cat[dirName]->Fill(hist_variable_map["cat"],evtwt_nom);
	h_gencat[dirName]->Fill(hist_variable_map["gen_cat"], evtwt_nom);
}

void WriteHists(TDirectory* rootDir, std::map<std::string, TTree*> trim_tree, std::map<std::string, TH1D*> cutflow, std::map<std::string, TH1D*> h_mll1, std::map<std::string, TH1D*> h_mll2, std::map<std::string, TH1D*> h_mDCH1, std::map<std::string, TH1D*> h_mDCH2, std::map<std::string, TH1D*> h_ll1_pt, std::map<std::string, TH1D*> h_ST, std::map<std::string, TH1D*> h_mZ1, std::map<std::string, TH1D*> h_mZ2, std::map<std::string, TH1D*> h_mZ3, std::map<std::string, TH1D*> h_mZ4, std::map<std::string, TH1D*> h_mT1, std::map<std::string, TH1D*> h_mT2, std::map<std::string, TH1D*> h_mTtot1, std::map<std::string, TH1D*> h_mTtot2, std::map<std::string, TH1D*> h_mT1_opp, std::map<std::string, TH1D*> h_mT2_opp, std::map<std::string, TH1D*> h_mT3_opp, std::map<std::string, TH1D*> h_mT4_opp, std::map<std::string, TH1D*> h_mTtot1_opp, std::map<std::string, TH1D*> h_mTtot2_opp, std::map<std::string, TH1D*> h_mTtot3_opp, std::map<std::string, TH1D*> h_mTtot4_opp, std::map<std::string, TH1D*> h_met, std::map<std::string, TH1D*> h_pT1, std::map<std::string, TH1D*> h_pT2, std::map<std::string, TH1D*> h_pT3, std::map<std::string, TH1D*> h_pT4, std::map<std::string, TH1D*> h_dR1, std::map<std::string, TH1D*> h_dR2, std::map<std::string, TH1D*> h_dR3, std::map<std::string, TH1D*> h_dR4, std::map<std::string, TH1D*> h_dRll, std::map<std::string, TH1D*> h_dRll2, std::map<std::string, TH1D*> h_dR1_met, std::map<std::string, TH1D*> h_dR2_met, std::map<std::string, TH1D*> h_max_dR_lplm, std::map<std::string, TH1D*> h_max_dR_ll, std::map<std::string, TH1D*> h_dPhiW_met, std::map<std::string, TH1D*> h_W_mt, std::map<std::string, TH1D*> h_cat, std::map<std::string, TH1D*> h_gencat){
	rootDir->cd();
	const char* dirName = rootDir->GetName();
	trim_tree[dirName]->Write();
	cutflow[dirName]->Write();
	h_mll1[dirName]->Write();
	h_mll2[dirName]->Write();
	h_mDCH1[dirName]->Write();
	h_mDCH2[dirName]->Write();
	h_mZ1[dirName]->Write();
	h_mZ2[dirName]->Write();
	h_mZ3[dirName]->Write();
	h_mZ4[dirName]->Write();
	h_mT1[dirName]->Write();
	h_mT2[dirName]->Write();
	h_mTtot1[dirName]->Write();
	h_mTtot2[dirName]->Write();
	h_mT1_opp[dirName]->Write();
	h_mT2_opp[dirName]->Write();
	h_mT3_opp[dirName]->Write();
	h_mT4_opp[dirName]->Write();
	h_mTtot1_opp[dirName]->Write();
	h_mTtot2_opp[dirName]->Write();
	h_mTtot3_opp[dirName]->Write();
	h_mTtot4_opp[dirName]->Write();
	h_ll1_pt[dirName]->Write();
	h_ST[dirName]->Write();
	h_met[dirName]->Write();
	h_pT1[dirName]->Write();
	h_pT2[dirName]->Write();
	h_pT3[dirName]->Write();
	h_pT4[dirName]->Write();
	h_dR1[dirName]->Write();
	h_dR2[dirName]->Write();
	h_dR3[dirName]->Write();
	h_dR4[dirName]->Write();
	h_dRll[dirName]->Write();
	h_dRll2[dirName]->Write();
	h_dR1_met[dirName]->Write();
	h_dR2_met[dirName]->Write();
	h_max_dR_lplm[dirName]->Write();
	h_max_dR_ll[dirName]->Write();
	h_dPhiW_met[dirName]->Write();
	h_W_mt[dirName]->Write();
	h_cat[dirName]->Write();
	h_gencat[dirName]->Write();
}

void DCH_presel_tree(const char* ext = ".root"){
	const char* inDir = ".";
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
	
	std::string selection = "Pre";

	double mDCH = 500, mZ = 91.2;
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		std::string fname = filename[j];
		if (fname.find("skim_500_test") > fname.length()) continue;
		if (XSec(filename[j])==1) continue; 
		cout<<filename[j]<<endl;
		
		const char* o_name;
		if (selection =="none") o_name = "hist";
		else if (selection =="Pre") o_name = "hist_MY";
		else if (selection =="APre") o_name = "hist_APre";
		else if (selection =="CR") o_name = "hist_CR";
		else if (selection =="VR") o_name = "hist_VR";
		else if (selection =="test") o_name = "hist_test";
		else cout<< "SELECTION NOT DEFINED!!!"<<endl;
		char *oname = gSystem->ConcatFileName(o_name, filename[j]);
		TFile* ofile = new TFile(oname, "RECREATE"); 
		TDirectory* tau0Dir = ofile->mkdir("0tau");
		TDirectory* tau1Dir = ofile->mkdir("1tau");
		TDirectory* tau2Dir = ofile->mkdir("2tau");
		TDirectory* tau3Dir = ofile->mkdir("3tau");
		TDirectory* lep3tau0Dir = ofile->mkdir("3lep0tau");
		TDirectory* lep3tau1Dir = ofile->mkdir("3lep1tau");
		TDirectory* lep3tau2Dir = ofile->mkdir("3lep2tau");


		TH1D* hNWEvts;
		if(XSec(fname)!=1){
			hNWEvts = (TH1D*)ifile->Get("hNWEvts")->Clone("hNWEvts");
			if (!hNWEvts) hNWEvts = (TH1D*)ifile->Get("hNEvts")->Clone("hNWEvts");
		}
		hNWEvts->Write();
		
		TTree *tree = (TTree*)ifile->Get("Events");
		MyBranch(tree);
		
		std::map<std::string, TTree*> trimmed_tree;
    
		double xmin = 0, xmax = mDCH+1000; int binw = 10; int nbins = (xmax-xmin)/binw;
		
		std::map<std::string, TH1D*> cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat;
		double mll_1, mll_2, dR_1, dR_2, evtwt;
		for(auto rootDirName: {"0tau","1tau","2tau","3tau","3lep0tau","3lep1tau","3lep2tau"}){
			trimmed_tree[rootDirName] = new TTree("Events", "trees");
			trimmed_tree[rootDirName]->Branch("mll1", &mll_1);
			trimmed_tree[rootDirName]->Branch("mll2", &mll_2);
			trimmed_tree[rootDirName]->Branch("dR1", &dR_1);
			trimmed_tree[rootDirName]->Branch("dR2", &dR_2);
			trimmed_tree[rootDirName]->Branch("evtwt", &evtwt);
			
			cutflow[rootDirName] = new TH1D("cutflow", "cutflow", 7, 0, 7);
			cutflow[rootDirName]->Sumw2();
			h_mll1[rootDirName] = new TH1D("h_mll1", "mll_1", nbins, xmin, 2*xmax);
			h_mll1[rootDirName]->Sumw2();
			h_mll2[rootDirName] = new TH1D("h_mll2", "mll_2", nbins, xmin, 2*xmax);
			h_mll2[rootDirName]->Sumw2();
			h_mDCH1[rootDirName] = new TH1D("h_mDCH1", "mDCH1", nbins, xmin, 2*xmax);
			h_mDCH1[rootDirName]->Sumw2();
			h_mDCH2[rootDirName] = new TH1D("h_mDCH2", "mDCH2", nbins, xmin, 2*xmax);
			h_mDCH2[rootDirName]->Sumw2();
			h_ll1_pt[rootDirName] = new TH1D("h_ll1_pt", "Leading pair pT", nbins, xmin, xmax);
			h_ll1_pt[rootDirName]->Sumw2();
			h_ST[rootDirName] = new TH1D("h_ST", "ST", 100, 0, mDCH+500);
			h_ST[rootDirName]->Sumw2();
			h_mZ1[rootDirName] = new TH1D("h_mZ1", "|M1_{l+l-}-mZ|", nbins, xmin, 2*xmax);
			h_mZ1[rootDirName]->Sumw2();
			h_mZ2[rootDirName] = new TH1D("h_mZ2", "|M2_{l+l-}-mZ|", nbins, xmin, 2*xmax);
			h_mZ2[rootDirName]->Sumw2();
			h_mZ3[rootDirName] = new TH1D("h_mZ3", "|M3_{l+l-}-mZ|", nbins, xmin, 2*xmax);
			h_mZ3[rootDirName]->Sumw2();
			h_mZ4[rootDirName] = new TH1D("h_mZ4", "|M4_{l+l-}-mZ|", nbins, xmin, 2*xmax);
			h_mZ4[rootDirName]->Sumw2();
			h_mT1[rootDirName] = new TH1D("h_mT1", "mDCH1 with cov MET", nbins, xmin, 2*xmax);
			h_mT1[rootDirName]->Sumw2();
			h_mT2[rootDirName] = new TH1D("h_mT2", "mDCH2 with cov MET", nbins, xmin, 2*xmax);
			h_mT2[rootDirName]->Sumw2();
			h_mTtot1[rootDirName] = new TH1D("h_mTtot1", "mDCH1 with simple MET split", nbins, xmin, 2*xmax);
			h_mTtot1[rootDirName]->Sumw2();
			h_mTtot2[rootDirName] = new TH1D("h_mTtot2", "mDCH2 with simple MET split", nbins, xmin, 2*xmax);
			h_mTtot2[rootDirName]->Sumw2();
			h_mT1_opp[rootDirName] = new TH1D("h_mT1_opp", "mll1 with Gen #nu", nbins, xmin, 2*xmax);
			h_mT1_opp[rootDirName]->Sumw2();
			h_mT2_opp[rootDirName] = new TH1D("h_mT2_opp", "mll2 with Gen #nu", nbins, xmin, 2*xmax);
			h_mT2_opp[rootDirName]->Sumw2();
			h_mT3_opp[rootDirName] = new TH1D("h_mT3_opp", "M_T of third l+l- pair and MET", nbins, xmin, 2*xmax);
			h_mT3_opp[rootDirName]->Sumw2();
			h_mT4_opp[rootDirName] = new TH1D("h_mT4_opp", "M_T of fourth l+l- pair and MET", nbins, xmin, 2*xmax);
			h_mT4_opp[rootDirName]->Sumw2();
			h_mTtot1_opp[rootDirName] = new TH1D("h_mTtot1_opp", "M_Ttot of first l+l- pair and MET", nbins, xmin, 2*xmax);
			h_mTtot1_opp[rootDirName]->Sumw2();
			h_mTtot2_opp[rootDirName] = new TH1D("h_mTtot2_opp", "M_Ttot of second l+l- pair and MET", nbins, xmin, 2*xmax);
			h_mTtot2_opp[rootDirName]->Sumw2();
			h_mTtot3_opp[rootDirName] = new TH1D("h_mTtot3_opp", "M_Ttot of third l+l- pair and MET", nbins, xmin, 2*xmax);
			h_mTtot3_opp[rootDirName]->Sumw2();
			h_mTtot4_opp[rootDirName] = new TH1D("h_mTtot4_opp", "M_Ttot of fourth l+l- pair and MET", nbins, xmin, 2*xmax);
			h_mTtot4_opp[rootDirName]->Sumw2();
			
			h_met[rootDirName] = new TH1D("h_met", "MET", 100, 0, mDCH+500);
			h_met[rootDirName]->Sumw2();
			h_pT1[rootDirName] = new TH1D("h_pT1", "Leading pT", 100, 0, mDCH+1500);
			h_pT1[rootDirName]->Sumw2();
			h_pT2[rootDirName] = new TH1D("h_pT2", "Sub-leading pT", 100, 0, mDCH+1500);
			h_pT2[rootDirName]->Sumw2();
			h_pT3[rootDirName] = new TH1D("h_pT3", "3rd pT", 100, 0, mDCH+1500);
			h_pT3[rootDirName]->Sumw2();
			h_pT4[rootDirName] = new TH1D("h_pT4", "4th pT", 100, 0, mDCH+1500);
			h_pT4[rootDirName]->Sumw2();
			h_dR1[rootDirName] = new TH1D("h_dR1", "dR between 1st(+-) leptons ", 50, 0, 5);
			h_dR1[rootDirName]->Sumw2();
			h_dR2[rootDirName] = new TH1D("h_dR2", "dR between 2nd(+-) leptons ", 50, 0, 5);
			h_dR2[rootDirName]->Sumw2();
			h_dR3[rootDirName] = new TH1D("h_dR3", "dR between 3rd(+-) leptons ", 50, 0, 5);
			h_dR3[rootDirName]->Sumw2();
			//h_dR4[rootDirName] = new TH1D("h_dR4", "dR between 4th(+-) leptons ", 50, 0, 5);
			h_dR4[rootDirName] = new TH1D("h_dR4", "d#phi between two #nu in Higgs ", 50, 0, 5);
			h_dR4[rootDirName]->Sumw2();
			h_dRll[rootDirName] = new TH1D("h_dRll", "dR between 1st pair", 50, 0, 5);
			h_dRll[rootDirName]->Sumw2();
			h_dRll2[rootDirName] = new TH1D("h_dRll2", "dR between 2nd pair", 50, 0, 5);
			h_dRll2[rootDirName]->Sumw2();
			h_dR1_met[rootDirName] = new TH1D("h_dR1_met", "dR between 1st pair and MET ", 50, 0, 5);
			h_dR1_met[rootDirName]->Sumw2();
			h_dR2_met[rootDirName] = new TH1D("h_dR2_met", "dR between 2nd pair and MET ", 50, 0, 5);	
			h_dR2_met[rootDirName]->Sumw2();
			h_max_dR_lplm[rootDirName] = new TH1D("h_max_dR_lplm", "min of dR between 1st and 2nd l+ l- pairs", 50, 0, 5);
			h_max_dR_lplm[rootDirName]->Sumw2();
			h_max_dR_ll[rootDirName] = new TH1D("h_max_dR_ll", "dPhi between DCH pairs", 50, 0, 5);
			h_max_dR_ll[rootDirName]->Sumw2();
			h_dPhiW_met[rootDirName] = new TH1D("h_dPhiW_met", "dPhi between 3rd lepton and MET ", 50, -4, 4);				
			h_dPhiW_met[rootDirName]->Sumw2();
			h_W_mt[rootDirName] = new TH1D("h_W_mt", "W transverse mass", nbins, xmin, 2*xmax);				
			h_W_mt[rootDirName]->Sumw2();
			h_cat[rootDirName] = new TH1D("h_cat", "cat", 46,0,46);
			h_cat[rootDirName]->Sumw2();
			h_gencat[rootDirName] = new TH1D("h_gencat", "gen cat", 22,0,22);
			h_gencat[rootDirName]->Sumw2();
		}
		
		TCanvas *c1 = new TCanvas("c1","",900,800);
    	c1->Divide(1,2);
		TH1D* h_dR_Lnu = new TH1D("h_dR_Lnu", "dR(l,#nu)", 50, 0, 0.5);
		TH1D* h_nudphi = new TH1D("h_nudphi", "#nu dPhi", 50, 0, 4);
		TH1D* h_nuMETdphi = new TH1D("h_nuMETdphi", "d#Phi_{#nu,MET}", 50, 0, 4);
		TH1D* h_chi2 = new TH1D("h_chi2", "best Chi2", 50, 0, 0.005);
		TH1D* h_visPz = new TH1D("h_visPz", "Sum of pT", 100, 0, 1500);
		TH1D* h_nuPz = new TH1D("h_nuPz", "Sum of pT", 100, 0, 1500);
		TH1D* h_Xmass_0t = new TH1D("h_Xmass_0t", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_1t = new TH1D("h_Xmass_1t", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_2t = new TH1D("h_Xmass_2t", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_3t = new TH1D("h_Xmass_3t", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_0t3l = new TH1D("h_Xmass_0t3l", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_1t3l = new TH1D("h_Xmass_1t3l", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_2t3l = new TH1D("h_Xmass_2t3l", "mDCH1", nbins, xmin, xmax);
		for (int ievt=0; ievt< tree->GetEntries(); ievt++){
			tree->GetEntry(ievt);
			//ERA checking for 2018
			/*if (XSec(filename[j])==1){
				//if (run < 315252 or run > 316995) continue; //A
				//if (run < 316998 or run > 319312) continue; //B
				//if (run < 319313 or run > 320393) continue; //C
				if (run < 320394 or run > 325273) continue; //D
			}*/
			string cat_string = numberToCat(cat);
			char* cat_name = const_cast<char*>(cat_string.c_str());
			int Nlep = cat_lepCount(cat_name,'e','m'); 
			int Ntau = strlen(cat_name)-Nlep; 	
			if (cat <= 21  and q_1+q_2+q_3+q_4 != 0) continue; 
			if (cat > 21  and abs(q_1+q_2+q_3) != 1) continue;
			if (strlen(cat_name)<=2) continue; 
			
			/*if (fname.find("HppM") < fname.length()){
				std::string Gencat_str = numberToCat(gen_cat);
				if (Gencat_str.substr(0,2) == "tt"  )
					brWeight = brWeight*6;
				else if ( Gencat_str.substr(0,2) == "ee" || Gencat_str.substr(0,2) == "mm" || Gencat_str.substr(0,2) == "em" || Gencat_str.substr(0,2) == "mt" || Gencat_str.substr(0,2) == "et")
					brWeight = brWeight*0;
				if (Gencat_str.substr(2,2) == "tt" )
					brWeight = brWeight*6;
				else if ( Gencat_str.substr(2,2) == "ee" || Gencat_str.substr(2,2) == "mm" || Gencat_str.substr(2,2) == "em" || Gencat_str.substr(2,2) == "mt" || Gencat_str.substr(2,2) == "et")
					brWeight = brWeight*0;
			
				//if (Gencat_str.substr(0,2) == Gencat_str.substr(2,2))
					//brWeight = brWeight*2;
				//cout<<brWeight<<"\t"<<Gencat_str<<endl;
			}*/
	
			double evtwt_nom = brWeight*Generator_weight;
			if (fname.find("_2018.") < fname.length()){//HEM veto
				if (XSec(filename[j])==1 and run >= 319077 and applyHEMveto(cat_string) == "yes") continue;
				if (XSec(filename[j])!=1 and applyHEMveto(cat_string) == "yes") evtwt_nom *= 0.35;
			}
			applyTauES(cat_string);
			
			/*if (XSec(filename[j])!=1){
				evtwt_nom *= L1PreFiringWeight_Nom*weightPUtruejson;
				if(strlen(cat_name)<3){
					evtwt_nom *= IDSF_1*IDSF_2*ISOSF_1*ISOSF_2*TauVsEleIDSF_1*TauVsEleIDSF_2*TauVsMuIDSF_1*TauVsMuIDSF_2*TauVsJetIDSF_1*TauVsJetIDSF_2;
					if (isTrig_1 >=1)
						evtwt_nom *= TrigSF_1;
					else if (isTrig_1 == -1)
						evtwt_nom *= TrigSF_2;
					//cout<<evtwt_nom<<endl;
				}
				else if (strlen(cat_name)==3)
					evtwt_nom *= IDSF_1*IDSF_2*IDSF_3*ISOSF_1*ISOSF_2*ISOSF_3*TauVsEleIDSF_1*TauVsEleIDSF_2*TauVsEleIDSF_3*TauVsMuIDSF_1*TauVsMuIDSF_2*TauVsMuIDSF_3*TauVsJetIDSF_1*TauVsJetIDSF_2*TauVsJetIDSF_3;
				else evtwt_nom *= IDSF_1*IDSF_2*IDSF_3*IDSF_4*ISOSF_1*ISOSF_2*ISOSF_3*ISOSF_4*TauVsEleIDSF_1*TauVsEleIDSF_2*TauVsEleIDSF_3*TauVsEleIDSF_4*TauVsMuIDSF_1*TauVsMuIDSF_2*TauVsMuIDSF_3*TauVsMuIDSF_4*TauVsJetIDSF_1*TauVsJetIDSF_2*TauVsJetIDSF_3*TauVsJetIDSF_4;
				if(strlen(cat_name)>=3){
					if (isTrig_1 >=1 and isTrig_2 == 0)
						evtwt_nom *= TrigSF_1;
					else if (isTrig_1 == -1 and isTrig_2 == 0)
						evtwt_nom *= TrigSF_2;
					//else if (isTrig_1 == 2 and)
					//	evtwt_nom *= TrigSF_1*TrigSF_2;
					else if (isTrig_2 >= 1 and isTrig_1 == 0)
						evtwt_nom *= TrigSF_3;
					else if (isTrig_2 == -1 and isTrig_1 == 0)
						evtwt_nom *= TrigSF_4;
					else if (isTrig_1 == 2 and isTrig_2 == 2)
						evtwt_nom *= TrigSF_1;
					//cout<<evtwt_nom<<endl;
				}
			}*/
			
			if (XSec(filename[j])!=1){
				evtwt_nom *= L1PreFiringWeight_Nom*weightPUtruejson;
				
				if(strlen(cat_name)<3){
					evtwt_nom *= IDSF_1*IDSF_2*ISOSF_1*ISOSF_2*TauVsEleIDSF_1*TauVsEleIDSF_2*TauVsMuIDSF_1*TauVsMuIDSF_2*TauVsJetIDSF_1*TauVsJetIDSF_2;
					if (TrigSF_1 !=1)
						evtwt_nom *= TrigSF_1;
					else if (TrigSF_2 !=1)
						evtwt_nom *= TrigSF_2;
					//cout<<evtwt_nom<<endl;
				}
				else if (strlen(cat_name)==3)
					evtwt_nom *= IDSF_1*IDSF_2*IDSF_3*ISOSF_1*ISOSF_2*ISOSF_3*TauVsEleIDSF_1*TauVsEleIDSF_2*TauVsEleIDSF_3*TauVsMuIDSF_1*TauVsMuIDSF_2*TauVsMuIDSF_3*TauVsJetIDSF_1*TauVsJetIDSF_2*TauVsJetIDSF_3;
				else evtwt_nom *= IDSF_1*IDSF_2*IDSF_3*IDSF_4*ISOSF_1*ISOSF_2*ISOSF_3*ISOSF_4*TauVsEleIDSF_1*TauVsEleIDSF_2*TauVsEleIDSF_3*TauVsEleIDSF_4*TauVsMuIDSF_1*TauVsMuIDSF_2*TauVsMuIDSF_3*TauVsMuIDSF_4*TauVsJetIDSF_1*TauVsJetIDSF_2*TauVsJetIDSF_3*TauVsJetIDSF_4;
				if(strlen(cat_name)>=3){
					if (TrigSF_1 !=1)
						evtwt_nom *= TrigSF_1;
					else if (TrigSF_2 !=1)
						evtwt_nom *= TrigSF_2;
					else if (TrigSF_3 !=1)
						evtwt_nom *= TrigSF_3;
					else if (TrigSF_4 !=1)
						evtwt_nom *= TrigSF_4;
				}
			}
			
			bool foundDup = false;
			std::vector<Lepton> leptons = {
				Lepton(pt_1, eta_1, phi_1, m_1, q_1, d0_1, dZ_1, iso_1),
				Lepton(pt_2, eta_2, phi_2, m_2, q_2, d0_2, dZ_2, iso_2),
				Lepton(pt_3, eta_3, phi_3, m_3, q_3, d0_3, dZ_3, iso_3),
				Lepton(pt_4, eta_4, phi_4, m_4, q_4, d0_4, dZ_4, iso_4),
			};
			
			for (int w = 0; w < strlen(cat_name) && !foundDup; ++w) {
				for (int x = w + 1; x < strlen(cat_name); ++x) {
					if (isDuplicate(leptons[w], leptons[x])){
					foundDup = true;
					//cout<<"DUUUUUp"<<endl;
					break;
					}
				}
			}
			if (foundDup == true ) continue;
			
			//Sort the lepton variables in descending order based on pt
			/*std::sort(leptons.begin(), leptons.end(), [](const Lepton& a, const Lepton& b) 
				return a.pt > b.pt;
			});*/
			
			double st = 0;
			if (strlen(cat_name)==4) st = pt_1+pt_2+pt_3+pt_4;
			else if (strlen(cat_name)==3) st = pt_1+pt_2+pt_3;
			
			/*void processPairs( const char* cat_name, vector<pair<int, int>>& Z_pair, vector<pair<int, int>>& Zv_pair, vector<pair<int, int>>& SS_pair) {//global function to process pairs
				int len = strlen(cat_name);
				for (int m = 1; m <= len; ++m) {
					for (int n = m + 1; n <= len; ++n) {
						string pair_name = pairFunc(m, n, cat_name, 20);
						if (pair_name == "Zwindow") Z_pair.push_back({m,n});
						else if (pair_name == "Zv") Zv_pair.push_back({m,n});
						else if (pair_name == "DCH") SS_pair.push_back({m,n});
						else continue;
					}
				}
			}	*/		
			TLorentzVector MET; MET.SetPtEtaPhiM(met, 0, metphi, 0);
//==============================================================================
			if (selection == "Pre"){	
				vector<pair<int, int>> OSSF_pair, OSOF_pair, SS_pair;
				processPairs(cat_name, OSSF_pair, OSSF_pair, SS_pair, OSOF_pair);
				if (OSSF_pair.size() < 1) continue; 
				
				//cout<< OSSF_pair.size()<<endl;
				int H1_idx1 = SS_pair[0].first, H1_idx2 = SS_pair[0].second, H2_idx1 = SS_pair[1].first, H2_idx2 = SS_pair[1].second; 
				if ((LepV(SS_pair[0].first)+LepV(SS_pair[0].second)).M() <= (LepV(SS_pair[1].first)+LepV(SS_pair[1].second)).M()){
					H1_idx1 = SS_pair[1].first;
					H1_idx2 = SS_pair[1].second;
					H2_idx1 = SS_pair[0].first;
					H2_idx2 = SS_pair[0].second;
				}
				double mll1 = (LepV(H1_idx1)+LepV(H1_idx2)).M();
				double mll2 = (LepV(H2_idx1)+LepV(H2_idx2)).M();
				double mll1_nu = (LepV(H1_idx1)+LepV(H1_idx2)+NuV(H1_idx1)+NuV(H1_idx2)).M();
				double mll2_nu = (LepV(H2_idx1)+LepV(H2_idx2)+NuV(H2_idx1)+NuV(H2_idx2)).M();
				double mZ1 = (LepV(OSSF_pair[0].first)+LepV(OSSF_pair[0].second)).M();
				double mZ2 = (LepV(OSSF_pair[1].first)+LepV(OSSF_pair[1].second)).M();
				double dRll = deltaR(LepV(H1_idx1),LepV(H1_idx2));
				//double dRll = deltaPhi(LepV(H1_idx1),LepV(H1_idx2));
				double mZ3 = (LepV(OSSF_pair[2].first)+LepV(OSSF_pair[2].second)).M();
				double mZ4 = (LepV(OSSF_pair[3].first)+LepV(OSSF_pair[3].second)).M();	
				double dRll2 = deltaR(LepV(H2_idx1),LepV(H2_idx2));
				//double dRll2 = min(deltaPhi(LepV(H1_idx1),LepV(H1_idx2)),deltaPhi(LepV(H2_idx1),LepV(H2_idx2)));
				double dR1 = deltaR(LepV(OSSF_pair[0].first),LepV(OSSF_pair[0].second));
				double dR2 = deltaR(LepV(OSSF_pair[1].first),LepV(OSSF_pair[1].second));
				double dR3 = deltaR(LepV(OSSF_pair[2].first),LepV(OSSF_pair[2].second));
				//double dR4 = deltaR(LepV(OSSF_pair[3].first),LepV(OSSF_pair[3].second));
				double dR4 = deltaPhi(LepV(H1_idx2),LepV(H2_idx2));
				double mT1 = calculateMT(LepV(H1_idx1)+LepV(H1_idx2),MET);
				double mT2 = calculateMT(LepV(H2_idx1)+LepV(H2_idx2),MET);
				double mTtot1 = calculateMTtot(LepV(H1_idx1),LepV(H1_idx2));
				double mTtot2 = calculateMTtot(LepV(H2_idx1),LepV(H2_idx2));
				//double mT1_opp = calculateMT(LepV(OSSF_pair[0].first)+LepV(OSSF_pair[0].second),MET);
				//double mT2_opp = calculateMT(LepV(OSSF_pair[1].first)+LepV(OSSF_pair[1].second),MET);
				double mT3_opp = calculateMT(LepV(OSSF_pair[2].first)+LepV(OSSF_pair[2].second),MET);
				double mT4_opp = calculateMT(LepV(OSSF_pair[3].first)+LepV(OSSF_pair[3].second),MET);
				double mTtot1_opp = calculateMTtot(LepV(OSSF_pair[0].first),LepV(OSSF_pair[0].second));
				double mTtot2_opp = calculateMTtot(LepV(OSSF_pair[1].first),LepV(OSSF_pair[1].second));
				double mTtot3_opp = calculateMTtot(LepV(OSSF_pair[2].first),LepV(OSSF_pair[2].second));
				double mTtot4_opp = calculateMTtot(LepV(OSSF_pair[3].first),LepV(OSSF_pair[3].second));
				int W_lep_idx =remaining_idx(OSSF_pair, cat_name);

				double max_dR_ll = 0;
				if (cat <=21){//4-lep
					max_dR_ll = max(dRll,dRll2);
				}
				else if(cat >= 22 and cat <=39){//3-lep
					max_dR_ll = dRll;
				}
				
				/*std::pair<double, double> DCH_mass =  ComputeDCHMasses( 
																LepV(H1_idx1), 
																LepV(H1_idx2),
																LepV(H2_idx1), 
																LepV(H2_idx2),
																MET
																);
				
				
				InputData ev;//for RJM
				ev.l1 = LepV(H1_idx1);
				ev.l2 = LepV(H1_idx2);
				ev.l3 = LepV(H2_idx1);
				ev.l4 = LepV(H2_idx2);
				ev.MET.Set(met*cos(metphi), met*sin(metphi));
				std::pair<double, double> mass_DCH = ReconstructMass(ev);*/

				if (cat > 21) continue;
				std::string Gencat_str = numberToCat(gen_cat);
				if (cat_lepCount(Gencat_str,'t','g')!=3) continue;
				//if (Ntau !=2 ) continue;
				
				std::array<TLorentzVector,4> L;
				L[0] = LepV(H1_idx1);
				L[1] = LepV(H1_idx2);
				L[2] = LepV(H2_idx1);
				L[3] = LepV(H2_idx2);
				TVector2 met_xy(MET.X(), MET.Y());
				//cout<<"mll "<<mll1 <<"\t"<<mll2<<endl;
				
				mat2 metcov;
				metcov[0][0] = metcov00; metcov[0][1] = metcov01;
    			metcov[1][0] = metcov10; metcov[1][1] = metcov11; 
    			
				std::string realcat = "";
				realcat.push_back(cat_string[H1_idx1-1]);
				realcat.push_back(cat_string[H1_idx2-1]);
				realcat.push_back(cat_string[H2_idx1-1]);
				realcat.push_back(cat_string[H2_idx2-1]);
				//auto [nlegs0, Mdch01, Mdch02] = get_legs(L, MET);
				
				auto [nlegs0, Mdch01, Mdch02, bestdPhi, bestChi2, isOpp] = get_legs_comb(realcat, L, MET, metcov,true);
				
				//if (!isOpp) continue; 
				/*if (!(Mdch01 < 400 or Mdch01 > 550)) continue;
				if (!(Mdch02 < 400 or Mdch02 > 550)) continue;*/
				
				//get_legs_comb(realcat, L, MET, metcov,true);//this is running again to print out alphas etc
				h_nudphi->Fill(bestdPhi);
				h_chi2->Fill(bestChi2);
				h_visPz->Fill((LepV(H1_idx1)+LepV(H1_idx2)+LepV(H2_idx1)+LepV(H2_idx2)).Pz());
				//double boost = (LepV(1)+LepV(2)+LepV(3)+LepV(4)).Pz()/(LepV(1)+LepV(2)+LepV(3)+LepV(4)).E();
				double min_dPhi_nuMET = 999;
				TLorentzVector numer;
				for(int i : {H1_idx1, H1_idx2, H2_idx1, H2_idx2}){numer += LepV(i);
					if(NuV(i).Pt()){
						h_dR_Lnu->Fill(deltaR(LepV(i), NuV(i)));
						//cout<<"Lep: ";print4Vec(LepV(i));
						cout<<"Nu: ";print4Vec(NuV(i));
						if (min_dPhi_nuMET > deltaPhi(NuV(i),MET)) min_dPhi_nuMET = deltaPhi(NuV(i),MET);
					}
				}
				h_nuMETdphi->Fill(min_dPhi_nuMET);
				double boost = numer.Pz()/numer.E();
				TLorentzVector totNu = (LepV(1)+LepV(2)+LepV(3)+LepV(4));
				totNu.Boost(0.0,0.0,-boost);
				//h_nuPz->Fill((LepV(H1_idx1)+LepV(H1_idx2)+NuV(H1_idx1)+NuV(H1_idx2)).DeltaPhi((LepV(H2_idx1)+LepV(H2_idx2)+NuV(H2_idx1)+NuV(H2_idx2))));
				h_nuPz->Fill(totNu.Pz());
				cout<<"Total Nu pT: "<<(NuV(1)+NuV(2)+NuV(3)+NuV(4)).Pt()<<endl;
				cout<<"Total Nu pz/E: "<<(NuV(1)+NuV(2)+NuV(3)+NuV(4)).Pz()/(NuV(1)+NuV(2)+NuV(3)+NuV(4)).E()<<endl;
				print4Vec(MET);
				cout<<"Event#: "<<evt<< "\t isOpp: "<<isOpp<<"\t"<<Gencat_str<<"\t"<<realcat<<"\t mll1_nu: "<<mll1_nu<<"\t mll2_nu: "<<mll2_nu<<endl<<endl;
				auto [nlegs, Mdch1, Mdch2] = get_legs_tau(realcat, L, MET);
				//if (nlegs !=1)continue;
				
				double Mdch001 = Mdch01, Mdch002 = Mdch02;
				if (abs(Mdch1-Mdch2) < abs(Mdch01-Mdch02)) {
					Mdch001 = Mdch1; Mdch002 = Mdch2;
				} 
				//auto res = reconstruct(L, met_xy);
				 // Try collinear
				/*auto res_col = run_reco_event(L, met_xy, "collinear");
				std::cout << "--- collinear policy ---\n";
				for (int i=0;i<4;++i) std::cout << "alpha["<<i<<"]="<<res_col.alpha[i] << "  ";
				std::cout << "\nresidual MET ref = " << res_col.residual << " GeV\n";
				std::cout << "MH1="<<res_col.MH1<<"  MH2="<<res_col.MH2<<"\n";

				// Try equal rapidity
				auto res_yr = run_reco_event(L, met_xy, "equal_rapidity");
				std::cout << "\n--- equal_rapidity policy ---\n";
				for (int i=0;i<4;++i) std::cout << "alpha["<<i<<"]="<<res_yr.alpha[i] << "  ";
				std::cout << "\nMH1="<<res_yr.MH1<<"  MH2="<<res_yr.MH2<<"\n";
				*/
				// Try fit-based pz adjustment
				//if (Ntau < 2  ) continue;
				auto res_fit = run_reco_event(L, met_xy, "fit", true);
				/*TVector3 met_vec = MET.Vect();
				auto res_fit = run_reco_event(L, met_vec, "fit", true);*/
				//std::cout << "\n--- fit policy ---\n";
				/*if (res_fit.alpha[0]+res_fit.alpha[1]+res_fit.alpha[2]+res_fit.alpha[3] >0.1){
					cout<<cat_name<<"\t"<< numberToCat(gen_cat)<<"\t"<<met<<endl;
					for (int i=0;i<4;++i) std::cout << "alpha["<<i<<"]="<<res_fit.alpha[i] << "  ";
					//std::cout << "\nresidual MET ref = " << res_fit.residual << " GeV";
					std::cout << "\nMll1="<<mll1<<"  Mll2="<<mll2<<endl;
					std::cout << "MH1 ="<<res_fit.MH1<<"  MH2 ="<<res_fit.MH2<<endl<<endl;
				}*/
				
				
				
				std::map< std::string, double > hist_variable_map = {
																{"cutflow", 0}, 
																{"mll1", mll1},
																{"mll2", mll2},
																{"mDCH1", res_fit.MH1},
																{"mDCH2", res_fit.MH2},
																{"ll1_pt", (LepV(H1_idx1)+LepV(H1_idx2)).Pt()},
																{"ST", st},
																{"mZ1", mZ1},
																{"mZ2", mZ2},
																{"mZ3", mZ3},
																{"mZ4", mZ4},
																{"mT1",Mdch01},
																{"mT2",Mdch02},
																{"mTtot1", Mdch1},
																{"mTtot2", Mdch2},
																{"mT1_opp", mll1_nu},
																{"mT2_opp", mll2_nu},
																{"mT3_opp", sqrt(abs(0.5*(mll1-mll2)*(mll1-mll2)+(1-0.5)*(mll1+mll2)*(mll1+mll2)-50000))*0.707},
																{"mT4_opp", sqrt(abs(0.6*(mll1-mll2)*(mll1-mll2)+(1-0.6)*(mll1+mll2)*(mll1+mll2)-50000))*0.707},
																{"mTtot1_opp", sqrt(abs(0.7*(mll1-mll2)*(mll1-mll2)+(1-0.7)*(mll1+mll2)*(mll1+mll2)-50000))*0.707},
																{"mTtot2_opp", sqrt(abs(0.8*(mll1-mll2)*(mll1-mll2)+(1-0.8)*(mll1+mll2)*(mll1+mll2)-50000))*0.707},
																{"mTtot3_opp", sqrt(abs(0.9*(mll1-mll2)*(mll1-mll2)+(1-0.9)*(mll1+mll2)*(mll1+mll2)-50000))*0.707},
																{"mTtot4_opp", sqrt(abs(1.0*(mll1-mll2)*(mll1-mll2)+(1-1.0)*(mll1+mll2)*(mll1+mll2)-50000))*0.707},
																{"met", met},
																{"pT1", leptons[0].pt},
																{"pT2", leptons[1].pt},
																{"pT3", leptons[2].pt},
																{"pT4", leptons[3].pt},
																{"dR1", dR1},
																{"dR2", dR2}, 
																{"dR3", dR3},
																{"dR4", dR4},
																{"dRll", dRll},
																{"dRll2", dRll2},
																{"dR1_met", deltaR((LepV(H1_idx1)+LepV(H1_idx2)), MET)},
																{"dR2_met", deltaR((LepV(H2_idx1)+LepV(H2_idx2)), MET)},
																{"max_dR_lplm", max(dR1,dR2)},
																{"max_dR_ll", max_dR_ll},
																{"dPhiW_met", deltaPhi(LepV(W_lep_idx), MET)},
																{"W_mt", calculateMT(LepV(W_lep_idx), MET)},
																{"cat", catToNumber(realcat)},
																{"gen_cat", gen_cat}
					};
					//mll_1 = mll1; mll_2 = mll2; dR_1 = dR1; dR_2 = dR2; evtwt = evtwt_nom;
					mll_1 = Mdch01; mll_2 = Mdch02; dR_1 = deltaPhi(LepV(H1_idx1),LepV(H1_idx2)); dR_2 = deltaPhi(LepV(H1_idx2),LepV(H2_idx2));; evtwt = evtwt_nom;
				if (cat <=21){//4-lep
					if (Ntau == 0){ 
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10 or abs(mZ3-mZ) < 10 or abs(mZ4-mZ) < 10) continue;
						std::map<std::string, bool> cutbools = {
							{"ST", (st >= 360)},
							{"dRll", true},
							{"M_ll1", true},
							{"M_ll1+M_ll2 >= 500", true},
							{"dRlplm", true}
						};
						bool pass = true;
						for (const auto& cutName : {"ST", "dRll", "M_ll1", "M_ll1+M_ll2 >= 500", "dRlplm"}) {
							n_minus_one_cutflow(cutName, cutflow, "0tau", cutbools); 
							pass = pass and cutbools[cutName];
						}
						if (!pass) continue;
						//trimmed_tree->Fill();
 						FillHists(tau0Dir, trimmed_tree, hist_variable_map, evtwt_nom, cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat );
						
					}	
					else if (Ntau == 1){
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10 or abs(mZ3-mZ) < 10 or abs(mZ4-mZ) < 10) continue;
						std::map<std::string, bool> cutbools = {
							{"ST", (st >= 340)},
							{"dRll", true},
							{"M_ll1", true},
							{"M_ll1+M_ll2 >= 500", true},
							{"dRlplm", true}
						};
						
						bool pass = true;
						for (const auto& cutName : {"ST", "dRll", "M_ll1", "M_ll1+M_ll2 >= 500", "dRlplm"}) {
							n_minus_one_cutflow(cutName, cutflow, "1tau", cutbools); 
							pass = pass and cutbools[cutName];
						}
						if (!pass) continue;
						
						
						FillHists(tau1Dir, trimmed_tree, hist_variable_map, evtwt_nom,cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if (Ntau == 2){
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10 or abs(mZ3-mZ) < 10 or abs(mZ4-mZ) < 10) continue;
						std::map<std::string, bool> cutbools = {
							{"ST", (st >= 340)},
							{"dRll", true},
							{"M_ll1", true},
							{"M_ll1+M_ll2 >= 500", true},
							{"dRlplm", true}
						};
						
						bool pass = true;
						for (const auto& cutName : {"ST", "dRll", "M_ll1", "M_ll1+M_ll2 >= 500", "dRlplm"}) {
							n_minus_one_cutflow(cutName, cutflow, "2tau", cutbools); 
							pass = pass and cutbools[cutName];
						}
						if (!pass) continue;
						
						
						FillHists(tau2Dir, trimmed_tree, hist_variable_map, evtwt_nom,cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if (Ntau == 3){
						std::map<std::string, bool> cutbools = {
							{"ST", (st >= 320)},
							{"dRll", true},
							{"M_ll1", true},
							{"M_ll1+M_ll2 >= 500", true},
							{"dRlplm", true}
						};
						
						bool pass = true;
						for (const auto& cutName : {"ST", "dRll", "M_ll1", "M_ll1+M_ll2 >= 500", "dRlplm"}) {
							n_minus_one_cutflow(cutName, cutflow, "3tau", cutbools); 
							pass = pass and cutbools[cutName];
						}
						if (!pass) continue;
						
						
						FillHists(tau3Dir, trimmed_tree, hist_variable_map, evtwt_nom,cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					
				}//4-lep	
				else if(cat >= 22 and cat <=39){//3-lep
					if(Ntau == 0){	
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10) continue;
						std::map<std::string, bool> cutbools = {
							{"ST", (st >= 200)},
							{"dRll", true},
							{"M_ll1", true},
							{"M_ll1+M_ll2 >= 500", (mll1+mll2 >=250)},
							{"dRlplm", true}
						};
						
						bool pass = true;
						for (const auto& cutName : {"ST", "dRll", "M_ll1", "M_ll1+M_ll2 >= 500", "dRlplm"}) {
							n_minus_one_cutflow(cutName, cutflow, "3lep0tau", cutbools); 
							pass = pass and cutbools[cutName];
						}
						if (!pass) continue;
						
			
						FillHists(lep3tau0Dir, trimmed_tree, hist_variable_map, evtwt_nom,cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if(Ntau == 1){
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10) continue;
						std::map<std::string, bool> cutbools = {
							{"ST", (st >= 200)},
							{"dRll", true},
							{"M_ll1", true},
							{"M_ll1+M_ll2 >= 500", true},
							{"dRlplm", true}
						};
						
						bool pass = true;
						for (const auto& cutName : {"ST", "dRll", "M_ll1", "M_ll1+M_ll2 >= 500", "dRlplm"}) {
							n_minus_one_cutflow(cutName, cutflow, "3lep1tau", cutbools); 
							pass = pass and cutbools[cutName];
						}
						if (!pass) continue;

						
						FillHists(lep3tau1Dir, trimmed_tree, hist_variable_map, evtwt_nom,cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if(Ntau == 2){
						std::map<std::string, bool> cutbools = {
							{"ST", (st >= 200)},
							{"dRll", true},
							{"M_ll1", true},
							{"M_ll1+M_ll2 >= 500", true},
							{"dRlplm", true}
						};
						
						bool pass = true;
						for (const auto& cutName : {"ST", "dRll", "M_ll1", "M_ll1+M_ll2 >= 500", "dRlplm"}) {
							n_minus_one_cutflow(cutName, cutflow, "3lep2tau", cutbools); 
							pass = pass and cutbools[cutName];
						}
						if (!pass) continue;
						
						
						FillHists(lep3tau2Dir, trimmed_tree, hist_variable_map, evtwt_nom,cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}			
				}//3-lep
			}//MY SLECTIONS
		}//ievtloop
		h_dR_Lnu->Write();
		WriteHists(tau0Dir, trimmed_tree, cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat );
		WriteHists(tau1Dir, trimmed_tree, cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat );
		WriteHists(tau2Dir, trimmed_tree, cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat );
		WriteHists(tau3Dir, trimmed_tree, cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat );
		WriteHists(lep3tau0Dir, trimmed_tree, cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat );
		WriteHists(lep3tau1Dir, trimmed_tree, cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat );
		WriteHists(lep3tau2Dir, trimmed_tree, cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_max_dR_lplm, h_max_dR_ll,  h_dPhiW_met, h_W_mt, h_cat, h_gencat );
		
		h_nudphi->Draw();
		h_nuMETdphi->Draw();
		gStyle->SetOptStat(0);
		c1->cd(1);  h_nuPz->SetLineColor(kRed);h_nuPz->Draw();
    	c1->cd(2); h_visPz->SetLineColor(kBlue);h_visPz->Draw("same");
    	 TLegend* leg1 = new TLegend(0.55, 0.7, 0.88, 0.88);
    	 leg1->AddEntry(h_nuPz, "Pz vis in boosted frame", "l");
    	 leg1->AddEntry(h_visPz, "Pz", "l");
    	 leg1->Draw();
		//trimmed_tree->Write();
		//cout<< j <<"\t"<< oname <<endl;
		//printf("%s %f\t %f\n ", oname,  h_Xmass_0t->Integral(), h_Xmass_3lep->Integral());
		delete tree;
	}
	gSystem->FreeDirectory(dirp);
}

