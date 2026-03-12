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

void processPairs( const char* cat_name, vector<pair<int, int>>& Z_pair, vector<pair<int, int>>& Zv_pair, vector<pair<int, int>>& H_pair, vector<pair<int,int>>& opp_pair) {//global function to process pairs
	int len = strlen(cat_name);
	for (int m = 1; m <= len; ++m) {
		for (int n = m + 1; n <= len; ++n) {
			string pair_name = pairFunc(m, n, cat_name, 20);
			if (pair_name == "Zwindow") Z_pair.push_back({m,n});
			else if (pair_name == "Zv") Zv_pair.push_back({m,n});
			else if (pair_name == "ZttPair") Zv_pair.push_back({m,n});
			else if (pair_name == "oppPair") opp_pair.push_back({m,n});
			else if (pair_name == "DCH") H_pair.push_back({m,n});
			else continue;
		}
	}
}

void FillHists(TDirectory* rootDir, std::map< std::string, double > hist_variable_map, double evtwt_nom, std::map<std::string, TH1D*> h_mll1, std::map<std::string, TH1D*> h_mll2, std::map<std::string, TH1D*> h_mDCH1, std::map<std::string, TH1D*> h_mDCH2, std::map<std::string, TH1D*> h_ll1_pt, std::map<std::string, TH1D*> h_ST, std::map<std::string, TH1D*> h_mZ1, std::map<std::string, TH1D*> h_mZ2, std::map<std::string, TH1D*> h_mZ3, std::map<std::string, TH1D*> h_mZ4, std::map<std::string, TH1D*> h_mT1, std::map<std::string, TH1D*> h_mT2, std::map<std::string, TH1D*> h_mTtot1, std::map<std::string, TH1D*> h_mTtot2, std::map<std::string, TH1D*> h_mT1_opp, std::map<std::string, TH1D*> h_mT2_opp, std::map<std::string, TH1D*> h_mT3_opp, std::map<std::string, TH1D*> h_mT4_opp, std::map<std::string, TH1D*> h_mTtot1_opp, std::map<std::string, TH1D*> h_mTtot2_opp, std::map<std::string, TH1D*> h_mTtot3_opp, std::map<std::string, TH1D*> h_mTtot4_opp, std::map<std::string, TH1D*> h_met, std::map<std::string, TH1D*> h_pT1, std::map<std::string, TH1D*> h_pT2, std::map<std::string, TH1D*> h_pT3, std::map<std::string, TH1D*> h_pT4, std::map<std::string, TH1D*> h_dR1, std::map<std::string, TH1D*> h_dR2, std::map<std::string, TH1D*> h_dR3, std::map<std::string, TH1D*> h_dR4, std::map<std::string, TH1D*> h_dRll, std::map<std::string, TH1D*> h_dRll2, std::map<std::string, TH1D*> h_dR1_met, std::map<std::string, TH1D*> h_dR2_met, std::map<std::string, TH1D*> h_dPhiZ_met, std::map<std::string, TH1D*> h_dPhiW_met, std::map<std::string, TH1D*> h_W_mt, std::map<std::string, TH1D*> h_cat, std::map<std::string, TH1D*> h_gencat){
	rootDir->cd();
	const char* dirName = rootDir->GetName();
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
	h_dPhiZ_met[dirName]->Fill(hist_variable_map["dPhiZ_met"], evtwt_nom);
	h_dPhiW_met[dirName]->Fill(hist_variable_map["dPhiW_met"], evtwt_nom);
	h_W_mt[dirName]->Fill(hist_variable_map["W_mt"], evtwt_nom);
	h_cat[dirName]->Fill(hist_variable_map["cat"],evtwt_nom);
	h_gencat[dirName]->Fill(hist_variable_map["gen_cat"], evtwt_nom);
}


void WriteHists(TDirectory* rootDir, std::map<std::string, std::map<std::string, TH1D*> h_mll1, std::map<std::string, TH1D*> h_mll2, std::map<std::string, TH1D*> h_mDCH1, std::map<std::string, TH1D*> h_mDCH2, std::map<std::string, TH1D*> h_ll1_pt, std::map<std::string, TH1D*> h_ST, std::map<std::string, TH1D*> h_mZ1, std::map<std::string, TH1D*> h_mZ2, std::map<std::string, TH1D*> h_mZ3, std::map<std::string, TH1D*> h_mZ4, std::map<std::string, TH1D*> h_mT1, std::map<std::string, TH1D*> h_mT2, std::map<std::string, TH1D*> h_mTtot1, std::map<std::string, TH1D*> h_mTtot2, std::map<std::string, TH1D*> h_mT1_opp, std::map<std::string, TH1D*> h_mT2_opp, std::map<std::string, TH1D*> h_mT3_opp, std::map<std::string, TH1D*> h_mT4_opp, std::map<std::string, TH1D*> h_mTtot1_opp, std::map<std::string, TH1D*> h_mTtot2_opp, std::map<std::string, TH1D*> h_mTtot3_opp, std::map<std::string, TH1D*> h_mTtot4_opp, std::map<std::string, TH1D*> h_met, std::map<std::string, TH1D*> h_pT1, std::map<std::string, TH1D*> h_pT2, std::map<std::string, TH1D*> h_pT3, std::map<std::string, TH1D*> h_pT4, std::map<std::string, TH1D*> h_dR1, std::map<std::string, TH1D*> h_dR2, std::map<std::string, TH1D*> h_dR3, std::map<std::string, TH1D*> h_dR4, std::map<std::string, TH1D*> h_dRll, std::map<std::string, TH1D*> h_dRll2, std::map<std::string, TH1D*> h_dR1_met, std::map<std::string, TH1D*> h_dR2_met, std::map<std::string, TH1D*> h_dR_HH, std::map<std::string, TH1D*> h_dPhiW_met, std::map<std::string, TH1D*> h_W_mt, std::map<std::string, TH1D*> h_cat, std::map<std::string, TH1D*> h_gencat){
	rootDir->cd();
	const char* dirName = rootDir->GetName();
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
	h_dR_HH[dirName]->Write();
	h_dPhiW_met[dirName]->Write();
	h_W_mt[dirName]->Write();
	h_cat[dirName]->Write();
	h_gencat[dirName]->Write();
}

void DCH_presel(const char* ext = ".root"){
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
	
	std::string selection = "CR";

	double mDCH = 500, mZ = 91.2, lumi_2016 = 35900, lumi_2017 = 41500, lumi_2018 = 58900.0;//in pb^-1
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		std::string fname = filename[j];
		if (fname.find("_2016.") > fname.length()) continue;
		if (fname.find("ttZ") > fname.length() and fname.find("ZH") > fname.length()) continue;
		//if (XSec(filename[j])==1) continue; 
		cout<<filename[j]<<endl;
		
		TH1D* hNWEvts;
		double xs_weight = 1.0;
		if(XSec(filename[j])!=1){
			hNWEvts = (TH1D*)ifile->Get("hNWEvts");
			if (!hNWEvts) hNWEvts = (TH1D*)ifile->Get("hNEvts");
			xs_weight = lumi_2016*XSec(filename[j])/hNWEvts->Integral();
		}
		else hNWEvts = (TH1D*)ifile->Get("hNEvts");
		cout<<xs_weight<<endl;
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

		TTree *tree = (TTree*)ifile->Get("Events");
		MyBranch(tree);
						
		double xmin = 0, xmax = mDCH+1000; int binw = 100; int nbins = (xmax-xmin)/binw;
		
		std::map<std::string, TH1D*> cutflow, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat;
		
		for(auto rootDirName: {"0tau","1tau","2tau","3tau","3lep0tau","3lep1tau","3lep2tau"}){
			
			cutflow[rootDirName] = new TH1D("cutflow", "cutflow", 6, 0, 6);
			cutflow[rootDirName]->Sumw2();
			h_mll1[rootDirName] = new TH1D("h_mll1", "mll_1", nbins, xmin, xmax);
			h_mll1[rootDirName]->Sumw2();
			h_mll2[rootDirName] = new TH1D("h_mll2", "mll_2", nbins, xmin, xmax);
			h_mll2[rootDirName]->Sumw2();
			h_mDCH1[rootDirName] = new TH1D("h_mDCH1", "mDCH1", nbins, xmin, xmax);
			h_mDCH1[rootDirName]->Sumw2();
			h_mDCH2[rootDirName] = new TH1D("h_mDCH2", "mDCH2", nbins, xmin, xmax);
			h_mDCH2[rootDirName]->Sumw2();
			h_ll1_pt[rootDirName] = new TH1D("h_ll1_pt", "Leading pair pT", nbins, xmin, xmax);
			h_ll1_pt[rootDirName]->Sumw2();
			h_ST[rootDirName] = new TH1D("h_ST", "ST", 100, 0, mDCH+500);
			h_ST[rootDirName]->Sumw2();
			h_mZ1[rootDirName] = new TH1D("h_mZ1", "|M1_{l+l-}-mZ|", 50, 0, mDCH+1500);
			h_mZ1[rootDirName]->Sumw2();
			h_mZ2[rootDirName] = new TH1D("h_mZ2", "|M2_{l+l-}-mZ|", 50, 0, mDCH+1500);
			h_mZ2[rootDirName]->Sumw2();
			h_mZ3[rootDirName] = new TH1D("h_mZ3", "|M3_{l+l-}-mZ|", 50, 0, mDCH+1500);
			h_mZ3[rootDirName]->Sumw2();
			h_mZ4[rootDirName] = new TH1D("h_mZ4", "|M4_{l+l-}-mZ|", 50, 0, mDCH+1500);
			h_mZ4[rootDirName]->Sumw2();
			h_mT1[rootDirName] = new TH1D("h_mT1", "M_T of first ll pair and MET", 50, 0, mDCH+1500);
			h_mT1[rootDirName]->Sumw2();
			h_mT2[rootDirName] = new TH1D("h_mT2", "M_T of second ll pair and MET", 50, 0, mDCH+1500);
			h_mT2[rootDirName]->Sumw2();
			h_mTtot1[rootDirName] = new TH1D("h_mTtot1", "M_Ttot of first ll pair and MET", 50, 0, mDCH+1500);
			h_mTtot1[rootDirName]->Sumw2();
			h_mTtot2[rootDirName] = new TH1D("h_mTtot2", "M_Ttot of second ll pair and MET", 50, 0, mDCH+1500);
			h_mTtot2[rootDirName]->Sumw2();
			h_mT1_opp[rootDirName] = new TH1D("h_mT1_opp", "M_T of first l+l- pair and MET", 50, 0, mDCH+1500);
			h_mT1_opp[rootDirName]->Sumw2();
			h_mT2_opp[rootDirName] = new TH1D("h_mT2_opp", "M_T of second l+l- pair and MET", 50, 0, mDCH+1500);
			h_mT2_opp[rootDirName]->Sumw2();
			h_mT3_opp[rootDirName] = new TH1D("h_mT3_opp", "M_T of third l+l- pair and MET", 50, 0, mDCH+1500);
			h_mT3_opp[rootDirName]->Sumw2();
			h_mT4_opp[rootDirName] = new TH1D("h_mT4_opp", "M_T of fourth l+l- pair and MET", 50, 0, mDCH+1500);
			h_mT4_opp[rootDirName]->Sumw2();
			h_mTtot1_opp[rootDirName] = new TH1D("h_mTtot1_opp", "M_Ttot of first l+l- pair and MET", 50, 0, mDCH+1500);
			h_mTtot1_opp[rootDirName]->Sumw2();
			h_mTtot2_opp[rootDirName] = new TH1D("h_mTtot2_opp", "M_Ttot of second l+l- pair and MET", 50, 0, mDCH+1500);
			h_mTtot2_opp[rootDirName]->Sumw2();
			h_mTtot3_opp[rootDirName] = new TH1D("h_mTtot3_opp", "M_Ttot of third l+l- pair and MET", 50, 0, mDCH+1500);
			h_mTtot3_opp[rootDirName]->Sumw2();
			h_mTtot4_opp[rootDirName] = new TH1D("h_mTtot4_opp", "M_Ttot of fourth l+l- pair and MET", 50, 0, mDCH+1500);
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
			h_dR4[rootDirName] = new TH1D("h_dR4", "dR between 4th(+-) leptons ", 50, 0, 5);
			h_dR4[rootDirName]->Sumw2();
			h_dRll[rootDirName] = new TH1D("h_dRll", "dR between 1st pair", 50, 0, 5);
			h_dRll[rootDirName]->Sumw2();
			h_dRll2[rootDirName] = new TH1D("h_dRll2", "dR between 2nd pair", 50, 0, 5);
			h_dRll2[rootDirName]->Sumw2();
			h_dR1_met[rootDirName] = new TH1D("h_dR1_met", "dR between 1st pair and MET ", 50, 0, 5);
			h_dR1_met[rootDirName]->Sumw2();
			h_dR2_met[rootDirName] = new TH1D("h_dR2_met", "dR between 2nd pair and MET ", 50, 0, 5);				
			h_dR2_met[rootDirName]->Sumw2();
			h_dPhiZ_met[rootDirName] = new TH1D("h_dPhiZ_met", "dPhi between (+-) pair and MET ", 50, -4, 4);
			h_dPhiZ_met[rootDirName]->Sumw2();
			h_dPhiW_met[rootDirName] = new TH1D("h_dPhiW_met", "dPhi between 3rd lepton and MET ", 50, -4, 4);				
			h_dPhiW_met[rootDirName]->Sumw2();
			h_W_mt[rootDirName] = new TH1D("h_W_mt", "W transverse mass", 50, 0, mDCH+1500);				
			h_W_mt[rootDirName]->Sumw2();
			h_cat[rootDirName] = new TH1D("h_cat", "cat", 46,0,46);
			h_cat[rootDirName]->Sumw2();
			h_gencat[rootDirName] = new TH1D("h_gencat", "gen cat", 22,0,22);
			h_gencat[rootDirName]->Sumw2();
		}
		
		TH1D* h_Xmass_0t = new TH1D("h_Xmass_0t", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_1t = new TH1D("h_Xmass_1t", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_2t = new TH1D("h_Xmass_2t", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_3t = new TH1D("h_Xmass_3t", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_0t3l = new TH1D("h_Xmass_0t3l", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_1t3l = new TH1D("h_Xmass_1t3l", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_2t3l = new TH1D("h_Xmass_2t3l", "mDCH1", nbins, xmin, xmax);
		for (int i =0; i < tree->GetEntries(); i++){
			tree->GetEntry(i);
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
			
			/*void processPairs( const char* cat_name, vector<pair<int, int>>& Z_pair, vector<pair<int, int>>& Zv_pair, vector<pair<int, int>>& H_pair) {//global function to process pairs
				int len = strlen(cat_name);
				for (int m = 1; m <= len; ++m) {
					for (int n = m + 1; n <= len; ++n) {
						string pair_name = pairFunc(m, n, cat_name, 20);
						if (pair_name == "Zwindow") Z_pair.push_back({m,n});
						else if (pair_name == "Zv") Zv_pair.push_back({m,n});
						else if (pair_name == "DCH") H_pair.push_back({m,n});
						else continue;
					}
				}
			}	*/		
			evtwt_nom *= xs_weight;
			TLorentzVector MET; MET.SetPtEtaPhiM(met, 0, metphi, 0);
//=======================Histograms without any cuts=============================
			if (selection == "none"){
				vector<pair<int, int>> SFopp_pair, opp_pair, H_pair;
				processPairs(cat_name, SFopp_pair, SFopp_pair, H_pair, opp_pair); 
				if (SFopp_pair.size() < 1) continue; 
				//cout<< SFopp_pair.size()<<endl;
				double mll1 = (LepV(H_pair[0].first)+LepV(H_pair[0].second)).M();
				double mZ1 = (LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second)).M();
				double mZ2 = (LepV(SFopp_pair[1].first)+LepV(SFopp_pair[1].second)).M();
				double dRll = deltaR(LepV(H_pair[0].first),LepV(H_pair[0].second));
				double mll2 = (LepV(H_pair[1].first)+LepV(H_pair[1].second)).M();
				double mZ3 = (LepV(SFopp_pair[2].first)+LepV(SFopp_pair[2].second)).M();
				double mZ4 = (LepV(SFopp_pair[3].first)+LepV(SFopp_pair[3].second)).M();	
				double dRll2 = deltaR(LepV(H_pair[1].first),LepV(H_pair[1].second));
				double mT1 = calculateMT(LepV(H_pair[0].first)+LepV(H_pair[0].second),MET);
				double mT2 = calculateMT(LepV(H_pair[1].first)+LepV(H_pair[1].second),MET);
				double mTtot1 = calculateMTtot(LepV(H_pair[0].first),LepV(H_pair[0].second));
				double mTtot2 = calculateMTtot(LepV(H_pair[1].first),LepV(H_pair[1].second));
				double mT1_opp = calculateMT(LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second),MET);
				double mT2_opp = calculateMT(LepV(SFopp_pair[1].first)+LepV(SFopp_pair[1].second),MET);
				double mT3_opp = calculateMT(LepV(SFopp_pair[2].first)+LepV(SFopp_pair[2].second),MET);
				double mT4_opp = calculateMT(LepV(SFopp_pair[3].first)+LepV(SFopp_pair[3].second),MET);
				double mTtot1_opp = calculateMTtot(LepV(SFopp_pair[0].first),LepV(SFopp_pair[0].second));
				double mTtot2_opp = calculateMTtot(LepV(SFopp_pair[1].first),LepV(SFopp_pair[1].second));
				double mTtot3_opp = calculateMTtot(LepV(SFopp_pair[2].first),LepV(SFopp_pair[2].second));
				double mTtot4_opp = calculateMTtot(LepV(SFopp_pair[3].first),LepV(SFopp_pair[3].second));
				int W_lep_idx =remaining_idx(SFopp_pair, cat_name);
				
				std::map< std::string, double > hist_variable_map = {
																{"cutflow", 0}, 
																{"mll1", mll1},
																{"mll2", mll2},
																{"mDCH1", mll1},
																{"mDCH2", mll2},
																{"ll1_pt", (LepV(H_pair[0].first)+LepV(H_pair[0].second)).Pt()},
																{"ST", st},
																{"mZ1", mZ1},
																{"mZ2", mZ2},
																{"mZ3", mZ3},
																{"mZ4", mZ4},
																{"mT1", mT1},
																{"mT2", mT2},
																{"mTtot1", mTtot1},
																{"mTtot2", mTtot2},
																{"mT1_opp", mT1_opp},
																{"mT2_opp", mT2_opp},
																{"mT3_opp", mT3_opp},
																{"mT4_opp", mT4_opp},
																{"mTtot1_opp", mTtot1_opp},
																{"mTtot2_opp", mTtot2_opp},
																{"mTtot3_opp", mTtot3_opp},
																{"mTtot4_opp", mTtot4_opp},
																{"met", met},
																{"pT1", leptons[0].pt},
																{"pT2", leptons[1].pt},
																{"pT3", leptons[2].pt},
																{"pT4", leptons[3].pt},
																{"dR1", deltaR(LepV(SFopp_pair[0].first),LepV(SFopp_pair[0].second))},
																{"dR2", deltaR(LepV(SFopp_pair[1].first),LepV(SFopp_pair[1].second))}, 
																{"dR3", deltaR(LepV(SFopp_pair[2].first),LepV(SFopp_pair[2].second))},
																{"dR4", deltaR(LepV(SFopp_pair[3].first),LepV(SFopp_pair[3].second))},
																{"dRll", dRll},
																{"dRll2", dRll2},
																{"dR1_met", deltaR((LepV(H_pair[0].first)+LepV(H_pair[0].second)), MET)},
																{"dR2_met", deltaR((LepV(H_pair[1].first)+LepV(H_pair[1].second)), MET)},
																{"dPhiZ_met", deltaPhi((LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second)), MET)},
																{"dPhiW_met", deltaPhi(LepV(W_lep_idx), MET)},
																{"W_mt", calculateMT(LepV(W_lep_idx), MET)},
																{"cat", cat},
																{"gen_cat", gen_cat}
					};
				if (cat <=21){//4-lep
					if (Ntau == 0){ 
						FillHists(tau0Dir, hist_variable_map, evtwt_nom, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
						//cout<<calculateMTtot(LepV(H_pair[0].first)+LepV(H_pair[0].second),LepV(H_pair[1].first)+LepV(H_pair[1].second))<<endl;
					
					}	
					else if (Ntau == 1){
						FillHists(tau1Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if (Ntau == 2){
						FillHists(tau2Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if (Ntau == 3){
						FillHists(tau3Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					
				}//4-lep	
				else if(cat >= 22 and cat <=39){//3-lep
					if(Ntau == 0){
						cout<<calculateMT(LepV(W_lep_idx), MET)<<"\t"<<W_lep_idx<<endl;
						FillHists(lep3tau0Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if(Ntau == 1){
						FillHists(lep3tau1Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if(Ntau == 2){
						FillHists(lep3tau2Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}			
				}//3-lep
			}//no selections
//===========================Histograms with CR cuts=============================
			if (selection == "CR"){				
				vector<pair<int, int>> SFopp_pair, opp_pair, H_pair;
				processPairs(cat_name, SFopp_pair, SFopp_pair, H_pair, opp_pair); 
				if (SFopp_pair.size() < 1) continue; 
				//if (met <40)continue; if (strlen(cat_name)!=3) continue;
				
				//if (SFopp_pair.size() < 2) continue;//for ZZ CR test 
				//cout<< SFopp_pair.size()<<endl;
				double mll1 = (LepV(H_pair[0].first)+LepV(H_pair[0].second)).M();
				double mZ1 = (LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second)).M();
				double mZ2 = (LepV(SFopp_pair[1].first)+LepV(SFopp_pair[1].second)).M();
				double dRll = deltaR(LepV(H_pair[0].first),LepV(H_pair[0].second));
				double mll2 = (LepV(H_pair[1].first)+LepV(H_pair[1].second)).M();
				double mZ3 = (LepV(SFopp_pair[2].first)+LepV(SFopp_pair[2].second)).M();
				double mZ4 = (LepV(SFopp_pair[3].first)+LepV(SFopp_pair[3].second)).M();	
				double dRll2 = deltaR(LepV(H_pair[1].first),LepV(H_pair[1].second));
				double mT1 = calculateMT(LepV(H_pair[0].first)+LepV(H_pair[0].second),MET);
				double mT2 = calculateMT(LepV(H_pair[1].first)+LepV(H_pair[1].second),MET);
				double mTtot1 = calculateMTtot(LepV(H_pair[0].first),LepV(H_pair[0].second));
				double mTtot2 = calculateMTtot(LepV(H_pair[1].first),LepV(H_pair[1].second));
				double mT1_opp = calculateMT(LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second),MET);
				double mT2_opp = calculateMT(LepV(SFopp_pair[1].first)+LepV(SFopp_pair[1].second),MET);
				double mT3_opp = calculateMT(LepV(SFopp_pair[2].first)+LepV(SFopp_pair[2].second),MET);
				double mT4_opp = calculateMT(LepV(SFopp_pair[3].first)+LepV(SFopp_pair[3].second),MET);
				double mTtot1_opp = calculateMTtot(LepV(SFopp_pair[0].first),LepV(SFopp_pair[0].second));
				double mTtot2_opp = calculateMTtot(LepV(SFopp_pair[1].first),LepV(SFopp_pair[1].second));
				double mTtot3_opp = calculateMTtot(LepV(SFopp_pair[2].first),LepV(SFopp_pair[2].second));
				double mTtot4_opp = calculateMTtot(LepV(SFopp_pair[3].first),LepV(SFopp_pair[3].second));
				int W_lep_idx =remaining_idx(SFopp_pair, cat_name);
				
				std::map< std::string, double > hist_variable_map = {
																{"cutflow", 0}, 
																{"mll1", mll1},
																{"mll2", mll2},
																{"mDCH1", mll1},
																{"mDCH2", mll2},
																{"ll1_pt", (LepV(H_pair[0].first)+LepV(H_pair[0].second)).Pt()},
																{"ST", st},
																{"mZ1", mZ1},
																{"mZ2", mZ2},
																{"mZ3", mZ3},
																{"mZ4", mZ4},
																{"mT1", mT1},
																{"mT2", mT2},
																{"mTtot1", mTtot1},
																{"mTtot2", mTtot2},
																{"mT1_opp", mT1_opp},
																{"mT2_opp", mT2_opp},
																{"mT3_opp", mT3_opp},
																{"mT4_opp", mT4_opp},
																{"mTtot1_opp", mTtot1_opp},
																{"mTtot2_opp", mTtot2_opp},
																{"mTtot3_opp", mTtot3_opp},
																{"mTtot4_opp", mTtot4_opp},
																{"met", met},
																{"pT1", leptons[0].pt},
																{"pT2", leptons[1].pt},
																{"pT3", leptons[2].pt},
																{"pT4", leptons[3].pt},
																{"dR1", deltaR(LepV(SFopp_pair[0].first),LepV(SFopp_pair[0].second))},
																{"dR2", deltaR(LepV(SFopp_pair[1].first),LepV(SFopp_pair[1].second))}, 
																{"dR3", deltaR(LepV(SFopp_pair[2].first),LepV(SFopp_pair[2].second))},
																{"dR4", deltaR(LepV(SFopp_pair[3].first),LepV(SFopp_pair[3].second))},
																{"dRll", dRll},
																{"dRll2", dRll2},
																{"dR1_met", deltaR((LepV(H_pair[0].first)+LepV(H_pair[0].second)), MET)},
																{"dR2_met", deltaR((LepV(H_pair[1].first)+LepV(H_pair[1].second)), MET)},
																{"dPhiZ_met", deltaPhi((LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second)), MET)},
																{"dPhiW_met", deltaPhi(LepV(W_lep_idx), MET)}, 
																{"W_mt", calculateMT(LepV(W_lep_idx), MET)},
																{"cat", cat},
																{"gen_cat", gen_cat}
					};
				if (cat <=21){//4-lep
					//if (abs(mZ1-mZ) > 10 and abs(mZ2-mZ) > 10 and abs(mZ3-mZ) > 10 and abs(mZ4-mZ) > 10) continue;
					if (Ntau == 0){ 
						if (abs(mZ1-mZ) > 10 and abs(mZ2-mZ) > 10 and abs(mZ3-mZ) > 10 and abs(mZ4-mZ) > 10) continue;
						FillHists(tau0Dir, hist_variable_map, evtwt_nom, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );			
					}	
					else if (Ntau == 1){
						if (abs(mZ1-mZ) > 10 and abs(mZ2-mZ) > 10 and abs(mZ3-mZ) > 10 and abs(mZ4-mZ) > 10) continue;
						FillHists(tau1Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if (Ntau == 2){
						if (abs(mZ1-mZ) > 10 and abs(mZ2-mZ) > 10 and abs(mZ3-mZ) > 10 and abs(mZ4-mZ) > 10) continue;
						FillHists(tau2Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if (Ntau == 3){
						FillHists(tau3Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					
				}//4-lep	
				else if(cat >= 22 and cat <=39){//3-lep
					//if (abs(mZ1-mZ) > 10 and abs(mZ2-mZ) > 10) continue;
					if(Ntau == 0){
						if (abs(mZ1-mZ) > 10 and abs(mZ2-mZ) > 10) continue;
						FillHists(lep3tau0Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if(Ntau == 1){
						if (abs(mZ1-mZ) > 10 and abs(mZ2-mZ) > 10) continue;
						FillHists(lep3tau1Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if(Ntau == 2){
						FillHists(lep3tau2Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}			
				}//3-lep
			}//CR
//===========================Histograms with VR cuts=============================
			if (selection == "VR"){	
				vector<pair<int, int>> SFopp_pair, opp_pair, H_pair;
				processPairs(cat_name, SFopp_pair, SFopp_pair, H_pair, opp_pair);
				if (SFopp_pair.size() < 1) continue; 
				//cout<< SFopp_pair.size()<<endl;
				double mll1 = (LepV(H_pair[0].first)+LepV(H_pair[0].second)).M();
				double mZ1 = (LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second)).M();
				double mZ2 = (LepV(SFopp_pair[1].first)+LepV(SFopp_pair[1].second)).M();
				double dRll = deltaR(LepV(H_pair[0].first),LepV(H_pair[0].second));
				double mll2 = (LepV(H_pair[1].first)+LepV(H_pair[1].second)).M();
				double mZ3 = (LepV(SFopp_pair[2].first)+LepV(SFopp_pair[2].second)).M();
				double mZ4 = (LepV(SFopp_pair[3].first)+LepV(SFopp_pair[3].second)).M();	
				double dRll2 = deltaR(LepV(H_pair[1].first),LepV(H_pair[1].second));
				double mT1 = calculateMT(LepV(H_pair[0].first)+LepV(H_pair[0].second), MET);
				double mT2 = calculateMT(LepV(H_pair[1].first)+LepV(H_pair[1].second), MET);
				double mTtot1 = calculateMTtot(LepV(H_pair[0].first),LepV(H_pair[0].second));
				double mTtot2 = calculateMTtot(LepV(H_pair[1].first),LepV(H_pair[1].second));
				double mT1_opp = calculateMT(LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second),MET);
				double mT2_opp = calculateMT(LepV(SFopp_pair[1].first)+LepV(SFopp_pair[1].second),MET);
				double mT3_opp = calculateMT(LepV(SFopp_pair[2].first)+LepV(SFopp_pair[2].second),MET);
				double mT4_opp = calculateMT(LepV(SFopp_pair[3].first)+LepV(SFopp_pair[3].second),MET);
				double mTtot1_opp = calculateMTtot(LepV(SFopp_pair[0].first),LepV(SFopp_pair[0].second));
				double mTtot2_opp = calculateMTtot(LepV(SFopp_pair[1].first),LepV(SFopp_pair[1].second));
				double mTtot3_opp = calculateMTtot(LepV(SFopp_pair[2].first),LepV(SFopp_pair[2].second));
				double mTtot4_opp = calculateMTtot(LepV(SFopp_pair[3].first),LepV(SFopp_pair[3].second));
				int W_lep_idx =remaining_idx(SFopp_pair, cat_name);
				
				std::map< std::string, double > hist_variable_map = {
																{"cutflow", 0}, 
																{"mll1", mll1},
																{"mll2", mll2},
																{"mDCH1", mll1},
																{"mDCH2", mll2},
																{"ll1_pt", (LepV(H_pair[0].first)+LepV(H_pair[0].second)).Pt()},
																{"ST", st},
																{"mZ1", mZ1},
																{"mZ2", mZ2},
																{"mZ3", mZ3},
																{"mZ4", mZ4},
																{"mT1", mT1},
																{"mT2", mT2},
																{"mTtot1", mTtot1},
																{"mTtot2", mTtot2},
																{"mT1_opp", mT1_opp},
																{"mT2_opp", mT2_opp},
																{"mT3_opp", mT3_opp},
																{"mT4_opp", mT4_opp},
																{"mTtot1_opp", mTtot1_opp},
																{"mTtot2_opp", mTtot2_opp},
																{"mTtot3_opp", mTtot3_opp},
																{"mTtot4_opp", mTtot4_opp},
																{"met", met},
																{"pT1", leptons[0].pt},
																{"pT2", leptons[1].pt},
																{"pT3", leptons[2].pt},
																{"pT4", leptons[3].pt},
																{"dR1", deltaR(LepV(SFopp_pair[0].first),LepV(SFopp_pair[0].second))},
																{"dR2", deltaR(LepV(SFopp_pair[1].first),LepV(SFopp_pair[1].second))}, 
																{"dR3", deltaR(LepV(SFopp_pair[2].first),LepV(SFopp_pair[2].second))},
																{"dR4", deltaR(LepV(SFopp_pair[3].first),LepV(SFopp_pair[3].second))},
																{"dRll", dRll},
																{"dRll2", dRll2},
																{"dR1_met", deltaR((LepV(H_pair[0].first)+LepV(H_pair[0].second)), MET)},
																{"dR2_met", deltaR((LepV(H_pair[1].first)+LepV(H_pair[1].second)), MET)},
																{"dPhiZ_met", deltaPhi((LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second)), MET)},
																{"dPhiW_met", deltaPhi(LepV(W_lep_idx), MET)}, 
																{"W_mt", calculateMT(LepV(W_lep_idx), MET)},
																{"cat", cat},
																{"gen_cat", gen_cat}
					};
				if (cat <=21){//4-lep
					//if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10 or abs(mZ3-mZ) < 10 or abs(mZ4-mZ) < 10) continue;
					if (Ntau == 0){ 
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10 or abs(mZ3-mZ) < 10 or abs(mZ4-mZ) < 10) continue;
						if (st > 400){ continue;}
						FillHists(tau0Dir, hist_variable_map, evtwt_nom, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
						
					}	
					else if (Ntau == 1){
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10 or abs(mZ3-mZ) < 10 or abs(mZ4-mZ) < 10) continue;
						if (st > 400){ continue;}
						FillHists(tau1Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if (Ntau == 2){
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10 or abs(mZ3-mZ) < 10 or abs(mZ4-mZ) < 10) continue;
						if (st > 400){ continue;}
						FillHists(tau2Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if (Ntau == 3){
						if (st > 100){ continue;}
						FillHists(tau3Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					
				}//4-lep	
				else if(cat >= 22 and cat <=39){//3-lep
					//if (abs(mZ1-mZ) > 10 and abs(mZ2-mZ) > 10) continue;
					if(Ntau == 0){
						if (st > 300){ continue;}
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10) continue;
						FillHists(lep3tau0Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if(Ntau == 1){
						if (st > 200){ continue;}
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10) continue;
						FillHists(lep3tau1Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if(Ntau == 2){
						if (st > 100){ continue;}
						FillHists(lep3tau2Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}			
				}//3-lep
			}//VR
//==============================================================================
			if (selection == "Pre"){	
				vector<pair<int, int>> SFopp_pair, opp_pair, H_pair;
				processPairs(cat_name, SFopp_pair, SFopp_pair, H_pair, opp_pair);
				if (SFopp_pair.size() < 1) continue; 
				//cout<< SFopp_pair.size()<<endl;
				double mll1 = (LepV(H_pair[0].first)+LepV(H_pair[0].second)).M();
				double mZ1 = (LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second)).M();
				double mZ2 = (LepV(SFopp_pair[1].first)+LepV(SFopp_pair[1].second)).M();
				double dRll = deltaR(LepV(H_pair[0].first),LepV(H_pair[0].second));
				double mll2 = (LepV(H_pair[1].first)+LepV(H_pair[1].second)).M();
				double mZ3 = (LepV(SFopp_pair[2].first)+LepV(SFopp_pair[2].second)).M();
				double mZ4 = (LepV(SFopp_pair[3].first)+LepV(SFopp_pair[3].second)).M();	
				double dRll2 = deltaR(LepV(H_pair[1].first),LepV(H_pair[1].second));
				double mT1 = calculateMT(LepV(H_pair[0].first)+LepV(H_pair[0].second),MET);
				double mT2 = calculateMT(LepV(H_pair[1].first)+LepV(H_pair[1].second),MET);
				double mTtot1 = calculateMTtot(LepV(H_pair[0].first),LepV(H_pair[0].second));
				double mTtot2 = calculateMTtot(LepV(H_pair[1].first),LepV(H_pair[1].second));
				double mT1_opp = calculateMT(LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second),MET);
				double mT2_opp = calculateMT(LepV(SFopp_pair[1].first)+LepV(SFopp_pair[1].second),MET);
				double mT3_opp = calculateMT(LepV(SFopp_pair[2].first)+LepV(SFopp_pair[2].second),MET);
				double mT4_opp = calculateMT(LepV(SFopp_pair[3].first)+LepV(SFopp_pair[3].second),MET);
				double mTtot1_opp = calculateMTtot(LepV(SFopp_pair[0].first),LepV(SFopp_pair[0].second));
				double mTtot2_opp = calculateMTtot(LepV(SFopp_pair[1].first),LepV(SFopp_pair[1].second));
				double mTtot3_opp = calculateMTtot(LepV(SFopp_pair[2].first),LepV(SFopp_pair[2].second));
				double mTtot4_opp = calculateMTtot(LepV(SFopp_pair[3].first),LepV(SFopp_pair[3].second));
				int W_lep_idx =remaining_idx(SFopp_pair, cat_name);
				
				std::map< std::string, double > hist_variable_map = {
																{"cutflow", 0}, 
																{"mll1", mll1},
																{"mll2", mll2},
																{"mDCH1", mll1},
																{"mDCH2", mll2},
																{"ll1_pt", (LepV(H_pair[0].first)+LepV(H_pair[0].second)).Pt()},
																{"ST", st},
																{"mZ1", mZ1},
																{"mZ2", mZ2},
																{"mZ3", mZ3},
																{"mZ4", mZ4},
																{"mT1", mT1},
																{"mT2", mT2},
																{"mTtot1", mTtot1},
																{"mTtot2", mTtot2},
																{"mT1_opp", mT1_opp},
																{"mT2_opp", mT2_opp},
																{"mT3_opp", mT3_opp},
																{"mT4_opp", mT4_opp},
																{"mTtot1_opp", mTtot1_opp},
																{"mTtot2_opp", mTtot2_opp},
																{"mTtot3_opp", mTtot3_opp},
																{"mTtot4_opp", mTtot4_opp},
																{"met", met},
																{"pT1", leptons[0].pt},
																{"pT2", leptons[1].pt},
																{"pT3", leptons[2].pt},
																{"pT4", leptons[3].pt},
																{"dR1", deltaR(LepV(SFopp_pair[0].first),LepV(SFopp_pair[0].second))},
																{"dR2", deltaR(LepV(SFopp_pair[1].first),LepV(SFopp_pair[1].second))}, 
																{"dR3", deltaR(LepV(SFopp_pair[2].first),LepV(SFopp_pair[2].second))},
																{"dR4", deltaR(LepV(SFopp_pair[3].first),LepV(SFopp_pair[3].second))},
																{"dRll", dRll},
																{"dRll2", dRll2},
																{"dR1_met", deltaR((LepV(H_pair[0].first)+LepV(H_pair[0].second)), MET)},
																{"dR2_met", deltaR((LepV(H_pair[1].first)+LepV(H_pair[1].second)), MET)},
																{"dPhiZ_met", deltaPhi((LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second)), MET)},
																{"dPhiW_met", deltaPhi(LepV(W_lep_idx), MET)},
																{"W_mt", calculateMT(LepV(W_lep_idx), MET)},
																{"cat", cat},
																{"gen_cat", gen_cat}
					};
				if (cat <=21){//4-lep
					if (Ntau == 0){ 
						if (st < 400){ continue;}
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10 or abs(mZ3-mZ) < 10 or abs(mZ4-mZ) < 10) continue;
						FillHists(tau0Dir, hist_variable_map, evtwt_nom, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
						
					}	
					else if (Ntau == 1){
						if (st < 400){ continue;}
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10 or abs(mZ3-mZ) < 10 or abs(mZ4-mZ) < 10) continue;
						FillHists(tau1Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if (Ntau == 2){
						if (st < 400){ continue;}
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10 or abs(mZ3-mZ) < 10 or abs(mZ4-mZ) < 10) continue;
						FillHists(tau2Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if (Ntau == 3){
						if (st < 100){ continue;}
						FillHists(tau3Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					
				}//4-lep	
				else if(cat >= 22 and cat <=39){//3-lep
					if(Ntau == 0){
						if (st < 300){ continue;}
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10) continue;
						FillHists(lep3tau0Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if(Ntau == 1){
						if (st < 200){ continue;}
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10) continue;
						FillHists(lep3tau1Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if(Ntau == 2){
						if (st < 100){ continue;}
						FillHists(lep3tau2Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}			
				}//3-lep
			}//MY SLECTIONS
//===================================================================================
			if(selection == "test"){//######My selections##########	
				vector<pair<int, int>> opp_pair, H_pair;
				processPairs(cat_name, opp_pair, opp_pair, H_pair, opp_pair);
				double mll1 = (LepV(H_pair[0].first)+LepV(H_pair[0].second)).M();
				double mll2 = (LepV(H_pair[1].first)+LepV(H_pair[1].second)).M();
				double mZ1 = (LepV(opp_pair[0].first)+LepV(opp_pair[0].second)).M();
				double mZ2 = (LepV(opp_pair[1].first)+LepV(opp_pair[1].second)).M();
				double mZ3 = (LepV(opp_pair[2].first)+LepV(opp_pair[2].second)).M();
				double mZ4 = (LepV(opp_pair[3].first)+LepV(opp_pair[3].second)).M();
				double dRll = deltaR(LepV(H_pair[0].first),LepV(H_pair[0].second));
				double dRll2 = deltaR(LepV(H_pair[1].first),LepV(H_pair[1].second));
				double mT1 = calculateMT(LepV(H_pair[0].first)+LepV(H_pair[0].second),MET);
				double mT2 = calculateMT(LepV(H_pair[1].first)+LepV(H_pair[1].second),MET);
				double mTtot1 = calculateMTtot(LepV(H_pair[0].first),LepV(H_pair[0].second));
				double mTtot2 = calculateMTtot(LepV(H_pair[1].first),LepV(H_pair[1].second));
				double mT1_opp = calculateMT(LepV(opp_pair[0].first)+LepV(opp_pair[0].second),MET);
				double mT2_opp = calculateMT(LepV(opp_pair[1].first)+LepV(opp_pair[1].second),MET);
				double mT3_opp = calculateMT(LepV(opp_pair[2].first)+LepV(opp_pair[2].second),MET);
				double mT4_opp = calculateMT(LepV(opp_pair[3].first)+LepV(opp_pair[3].second),MET);
				double mTtot1_opp = calculateMTtot(LepV(opp_pair[0].first),LepV(opp_pair[0].second));
				double mTtot2_opp = calculateMTtot(LepV(opp_pair[1].first),LepV(opp_pair[1].second));
				double mTtot3_opp = calculateMTtot(LepV(opp_pair[2].first),LepV(opp_pair[2].second));
				double mTtot4_opp = calculateMTtot(LepV(opp_pair[3].first),LepV(opp_pair[3].second));
				std::map< std::string, double > hist_variable_map = {
																{"cutflow", 0}, 
																{"mll1", mll1},
																{"mll2", mll2},
																{"mDCH1", mll1},
																{"mDCH2", mll2},
																{"ll1_pt", (LepV(H_pair[0].first)+LepV(H_pair[0].second)).Pt()},
																{"ST", st},
																{"mZ1", mZ1},
																{"mZ2", mZ2},
																{"mZ3", mZ3},
																{"mZ4", mZ4},
																{"mT1", mT1},
																{"mT2", mT2},
																{"mTtot1", mTtot1},
																{"mTtot2", mTtot2},
																{"mT1_opp", mT1_opp},
																{"mT2_opp", mT2_opp},
																{"mT3_opp", mT3_opp},
																{"mT4_opp", mT4_opp},
																{"mTtot1_opp", mTtot1_opp},
																{"mTtot2_opp", mTtot2_opp},
																{"mTtot3_opp", mTtot3_opp},
																{"mTtot4_opp", mTtot4_opp},
																{"met", met},
																{"pT1", leptons[0].pt},
																{"pT2", leptons[1].pt},
																{"pT3", leptons[2].pt},
																{"pT4", leptons[3].pt},
																{"dR1", deltaR(LepV(SFopp_pair[0].first),LepV(SFopp_pair[0].second))},
																{"dR2", deltaR(LepV(SFopp_pair[1].first),LepV(SFopp_pair[1].second))}, 
																{"dR3", deltaR(LepV(SFopp_pair[2].first),LepV(SFopp_pair[2].second))},
																{"dR4", deltaR(LepV(SFopp_pair[3].first),LepV(SFopp_pair[3].second))},
																{"dRll", dRll},
																{"dRll2", dRll2},
																{"dR1_met", deltaR((LepV(H_pair[0].first)+LepV(H_pair[0].second)), MET)},
																{"dR2_met", deltaR((LepV(H_pair[1].first)+LepV(H_pair[1].second)), MET)},
																{"dPhiZ_met", deltaPhi((LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second)), MET)},
																{"dPhiW_met", deltaPhi(LepV(W_lep_idx), MET)},
																{"W_mt", calculateMT(LepV(W_lep_idx), MET)},
																{"cat", cat},
																{"gen_cat", gen_cat}
					};
				if (cat <=21){//4-lep
					if (Ntau == 0){
						if (st < 700){ continue;}//ST
						if (dRll > 4 or dRll2 > 4){ continue;}
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10 or abs(mZ3-mZ) < 10 or abs(mZ4-mZ) < 10){ continue;}
						if (mll1 < 400 and mll2 < 400 ){ continue;}  
						//if ((mll1+mll2)/2 < 400 ){ continue;}  
						FillHists(tau0Dir, hist_variable_map, evtwt_nom, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}	
					else if (Ntau == 1){
						if (st < 600){ continue;}//ST
						if (dRll > 3.6 or dRll2 > 3.6){ continue;}
						if (abs(mZ1-mZ) < 25 or abs(mZ2-mZ) < 25 or abs(mZ3-mZ) < 25 or abs(mZ4-mZ) < 25){ continue;}
						if (mll1 < 250 and mll2 < 250 ){ continue;}  
						//if ((mll1+mll2)/2 < 400 ){ continue;}  
						FillHists(tau1Dir, hist_variable_map, evtwt_nom, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if (Ntau == 2){
						if (st < 600){ continue;}//ST
						if (dRll > 3.9 or dRll2 > 3.9){ continue;}
						if (abs(mZ1-mZ) < 85 or abs(mZ2-mZ) < 85 or abs(mZ3-mZ) < 85 or abs(mZ4-mZ) < 85){ continue;}
						if (mll1 < 150 and mll2 < 150 ){ continue;}  
						//if ((mll1+mll2)/2 < 400 ){ continue;}  
						FillHists(tau2Dir, hist_variable_map, evtwt_nom, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					if (Ntau > 2){
						if (st < 450){ continue;}//ST
						if (dRll > 3.9 or dRll2 > 3.9){ continue;}
						if (abs(mZ1-mZ) < 5 or abs(mZ2-mZ) < 5 or abs(mZ3-mZ) < 5 or abs(mZ4-mZ) < 5){ continue;}
						if (mll1 < 100 and mll2 < 100 ){ continue;}  
						//if ((mll1+mll2)/2 < 400 ){ continue;}  
						FillHists(tau3Dir, hist_variable_map, evtwt_nom, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
				}//4-lep	
				else if(cat >= 22 and cat <=39 and Ntau !=3 ){//3-lep	
					//if (abs(mZ1-mZ) > 10 and abs(mZ2-mZ) > 10) continue;
					if(Ntau == 0){
						if (st < 300){ continue;}
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10) continue;
						FillHists(lep3tau0Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if(Ntau == 1){
						if (st < 200){ continue;}
						if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10) continue;
						FillHists(lep3tau1Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}
					else if(Ntau == 2){
						if (st < 100){ continue;}
						FillHists(lep3tau2Dir, hist_variable_map, evtwt_nom,h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dPhiZ_met, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
					}			
				}	
				}//3-lep
			}//MyPreseltest
			
		}//evt loop
		
		/*h_Xmass_0t->Write();
		h_Xmass_1t->Write();
		h_Xmass_2t->Write();
		h_Xmass_3t->Write();
		h_Xmass_0t3l->Write();
		h_Xmass_1t3l->Write();
		h_Xmass_2t3l->Write();*/
		
		
		WriteHists(tau0Dir, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dR_HH, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
		WriteHists(tau1Dir, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dR_HH, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
		WriteHists(tau2Dir, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dR_HH, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
		WriteHists(tau3Dir, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dR_HH, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
		WriteHists(lep3tau0Dir, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dR_HH, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
		WriteHists(lep3tau1Dir, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dR_HH, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
		WriteHists(lep3tau2Dir, h_mll1, h_mll2, h_mDCH1, h_mDCH2, h_ll1_pt, h_ST, h_mZ1, h_mZ2, h_mZ3, h_mZ4, h_mT1, h_mT2, h_mTtot1, h_mTtot2,h_mT1_opp, h_mT2_opp, h_mT3_opp, h_mT4_opp, h_mTtot1_opp, h_mTtot2_opp,h_mTtot3_opp, h_mTtot4_opp, h_met, h_pT1, h_pT2, h_pT3, h_pT4, h_dR1, h_dR2, h_dR3, h_dR4, h_dRll, h_dRll2, h_dR1_met, h_dR2_met, h_dR_HH, h_dPhiW_met, h_W_mt, h_cat, h_gencat );
		//cout<< j <<"\t"<< oname <<endl;
		//printf("%s %f\t %f\n ", oname,  h_Xmass_0t->Integral(), h_Xmass_3lep->Integral());
		delete tree;
	}
	gSystem->FreeDirectory(dirp);
}

