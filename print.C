#include "TMath.h"
#include <cmath>
#include <vector>
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "include/MyBranch.C"//branch definitons
#include "include/Kinematics.C"//Kine fns
#include "include/MET_split.C"

void print(const char* ext = "HppM600_2018.root"){ //gROOT->SetWebDisplay();
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
			
		TH1F* h_gen_cat = new TH1F("h_gen_cat", "2H-->(>=1t)-->Reco channels", 46,1,46);
		TCanvas* canvas = new TCanvas("canvas", "histograms", 900, 700);//600);
		TH1F* h_pt1 = new TH1F("h_pt1", "pT", 50,0,500);
		TH1F* h_pt2 = new TH1F("h_pt2", "pT", 50,0,500);
		TH1F* h_pt3 = new TH1F("h_pt3", "pT", 50,0,500);
		TH1F* h_pt4 = new TH1F("h_pt4", "pT", 50,0,500);
		TH1F* h_reco_cat = new TH1F("h_reco_cat", "2H-->(>=1t)-->Reco channels", 46,1,46);
		for(int j = 1; j <= 45; j++){
			h_gen_cat->GetXaxis()->SetBinLabel(j,numberToCat(j));
			h_reco_cat->GetXaxis()->SetBinLabel(j,numberToCat(j));
		} 
		for(Int_t j = 0; j <= tree->GetEntries(); j++){ 
			tree->GetEntry(j);
			
			std::string cat_name = numberToCat(gen_cat);
			if (cat_lepCount(cat_name,'t','g') < 1) continue;
			//if (gen_cat !=21) continue;
			
			//if (gen_cat == 21) {cout<< j <<"\t"<< numberToCat(gen_cat)<<"--->"<<numberToCat(cat)<<endl;}
			//if (Gencat_str.substr(0,2) == Gencat_str.substr(2,2))
				//brWeight = brWeight*2;
			//cout<<brWeight<<"\t"<<Gencat_str<<endl; 
			h_reco_cat->Fill(cat,brWeight);	
			h_gen_cat->Fill(gen_cat,brWeight);	
			std::vector<double> pt = SortPt();
			h_pt1->Fill(pt[0],brWeight);
			h_pt2->Fill(pt[1],brWeight);	
			h_pt3->Fill(pt[2],brWeight);	
			h_pt4->Fill(pt[3],brWeight);		
			//cout<<pt[0]<<"\t"<<pt[1]<<"\t"<<pt[2]<<"\t"<<pt[3]<<"\t"<<endl;
		}
		gStyle->SetOptStat(0);
		h_gen_cat->SetLineWidth(2);h_gen_cat->Draw("hist");
		h_reco_cat->SetLineColor(2);h_reco_cat->Draw("same hist");
		auto legend = new TLegend(0.8,0.8,0.9,0.9);
		//legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
		legend->AddEntry(h_gen_cat,"Gen","l");
		legend->AddEntry(h_reco_cat,"Reco","l");
		legend->Draw();
		//canvas->SetLogy();
		//canvas->SaveAs("genVreco.png");canvas->Clear();
		h_pt1->SetLineColor(2);h_pt1->SetLineWidth(2);
		h_pt2->SetLineColor(3);h_pt2->SetLineWidth(2);
		h_pt3->SetLineColor(4);h_pt3->SetLineWidth(2);
		h_pt4->SetLineColor(5);h_pt4->SetLineWidth(2);
		
		h_pt3->Draw("hist");
		//canvas->SaveAs("pt1.png");canvas->Clear();
		h_pt2->Draw("hist same");
		//canvas->SaveAs("pt2.png");canvas->Clear();
		h_pt1->Draw("hist same");
		//canvas->SaveAs("pt3.png");canvas->Clear();
		h_pt4->Draw("hist same");
		auto legend1 = new TLegend(0.7,0.7,0.9,0.9);
		legend1->AddEntry(h_pt1,"pT_{1}","l");
		legend1->AddEntry(h_pt2,"pT_{2}","l");
		legend1->AddEntry(h_pt3,"pT_{3}","l");
		legend1->AddEntry(h_pt4,"pT_{4}","l");
		legend1->Draw();
		canvas->SaveAs("pt4.png");canvas->Clear();
	}
  }
}
