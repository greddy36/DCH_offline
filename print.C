#include "TMath.h"
#include <cmath>
#include <vector>
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "include/MyBranch.C"//branch definitons
#include "include/Kinematics.C"//Kine fns
#include "include/MET_split.C"

void print(const char* ext = "HppM1000_2018.root"){ //gROOT->SetWebDisplay();
  const char* inDir;
  for(Int_t k=1; k<=1;k++){
    if(k==1){inDir = ".";}
	char* dir = gSystem->ExpandPathName(inDir);
	void* dirp = gSystem->OpenDirectory(dir);
	const char* entry;
	const char* filename[100];
	TString str; Int_t n = 0;
		while((entry = (char*)gSystem->GetDirEntry(dirp))){
	  		str = entry;
	  		if(str.EndsWith(ext)){
				filename[n++] = gSystem->ConcatFileName(dir, entry);
	  		}
		}
	//Printf(" Selection: %s", "EvtWt*( nBTagMed_DeepFLV >=1  && ST>500 && DR_LepleadJet > 2.0  && HT_Full_pu > 500 && abs(DPHI_LepMet) < 1.0 && bVsW_ratio < 2 && (nVetoElectrons +  nVetoMuons) == 1 && LeadJet_btag >=1 && Lepton_pt > 40 && Lepton_eta < 2.1 && LeadJet_pt > 200 && abs(LeadJet_eta) < 2.4)");
	for (Int_t i = 0; i < n; i++){
		TFile *input_file = new TFile(filename[i]);
		TTree *tree = (TTree*)input_file->Get("Events");
		MyBranch(tree);
		//TH1D* nevts = (TH1D*)input_file->Get("hNEvts");
		/*double X = tree->GetEntries("cat <= 21 &&  mll<200 && mll>=100 && (isTrig_1 !=0 || isTrig_2 !=0)");
		double Y = tree->GetEntries("cat >= 22 &&  mll>=300 && (isTrig_1 !=0 || isTrig_2 !=0)");
		double M = tree->GetEntries("cat <= 21 &&  mll<200 && mll>=100");
		double N = tree->GetEntries("cat >= 22 &&  mll>=300");
		Printf("%s, %f\t, %f\n", filename[i],X,M);
		Printf("%s, %f\t, %f\n", filename[i],Y,N);*/
			
		TH1F* h_gen_cat = new TH1F("h_gen_cat", "Gen(>=1t) vs Reco (4L) democratic decays", 22,1,22);
		TH1F* h_reco_cat = new TH1F("h_reco_cat", "Gen vs Reco (4L) democratic decays", 22,1,22);
		for(int j = 1; j < 22; j++){
			h_gen_cat->GetXaxis()->SetBinLabel(j,numberToCat(j));
			h_reco_cat->GetXaxis()->SetBinLabel(j,numberToCat(j));
		} 
		cout<<tree->GetEntries();
		for(Int_t j = 0; j <= tree->GetEntries(); j++){ 
			tree->GetEntry(j);
			
			//if (cat >21) continue;
			
			//if (gen_cat == 21) {cout<< j <<"\t"<< numberToCat(gen_cat)<<"--->"<<numberToCat(cat)<<endl;}
			
			/*
			float brWeight = 1;
			std::string Gencat_str = numberToCat(gen_cat);
			if (Gencat_str.substr(3,1) != "t") continue;
			if (Gencat_str.substr(0,2) == "ee" || Gencat_str.substr(0,2) == "mm" || Gencat_str.substr(0,2) == "tt")
				brWeight = brWeight*3/2;
			else if (Gencat_str.substr(0,2) == "em" || Gencat_str.substr(0,2) == "et" || Gencat_str.substr(0,2) == "mt")
				brWeight = brWeight*3/4;
			if (Gencat_str.substr(2,2) == "ee" || Gencat_str.substr(2,2) == "mm" || Gencat_str.substr(0,2) == "tt")
				brWeight = brWeight*3/2;
			else if (Gencat_str.substr(2,2) == "em" || Gencat_str.substr(2,2) == "et" || Gencat_str.substr(0,2) == "mt")
				brWeight = brWeight*3/4;*/
					
			//if (Gencat_str.substr(0,2) == Gencat_str.substr(2,2))
				//brWeight = brWeight*2;
			//cout<<brWeight<<"\t"<<Gencat_str<<endl; 
						
			h_gen_cat->Fill(gen_cat,brWeight);
			h_reco_cat->Fill(cat,brWeight);			
			
		}
		cout <<h_gen_cat->Integral() << "\t"<<h_reco_cat->Integral()<<endl;
		gStyle->SetOptStat(0);
		h_gen_cat->SetLineWidth(2);h_gen_cat->Draw("hist");
		//h_reco_cat->SetLineColor(2);h_reco_cat->Draw("same hist");

		auto legend = new TLegend(0.8,0.8,0.9,0.9);
		//legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
		legend->AddEntry(h_gen_cat,"Gen","l");
		legend->AddEntry(h_reco_cat,"Reco","l");
		legend->Draw();
	}
  }
}
