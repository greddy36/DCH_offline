#include "TMath.h"
#include <cmath>
#include <vector>
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TMatrix.h"
#include "include/MyBranch.C"
#include "include/cat.h"
void MET_incl_new() {
TCanvas *can= new TCanvas("can","can",700,500);gStyle->SetOptStat(0); 
TLegend *leg = new TLegend(0.7, 0.7, .9, .9);
	TFile *ifile = new TFile("HppM500_2018.root","READ");
	TTree *tree = (TTree*)ifile->Get("Events");
	MyBranch(tree);
	TFile* ofile = new TFile("MET_exercise.root", "RECREATE");
	TH1F* h_mll = new TH1F("h_mll", "mll", 100, 0, 3000);
	TH1F* h_mll2 = new TH1F("h_mll2", "mll2", 100, 0, 3000);
	TH1F* h_mDCH1 = new TH1F("h_mDCH1", "mDCH1", 100, 0, 3000);
	TH1F* h_mDCH2 = new TH1F("h_mDCH2", "mDCH2", 100, 0, 3000);
	for (int i =0; i < tree->GetEntries(); i++){
		tree->GetEntry(i);
		const char *cat_name = numberToCat(cat);
		int lep_count = cat_lepCount(cat_name,'e','m'); 
		if (strlen(cat_name) != 4) continue;
		if (lep_count >2) continue;
		//if (cat !=1) continue; 
		TLorentzVector Lep1, Lep2, Lep3, Lep4, MET, Vis1, Vis2; //TLV for CMS frame particles
		MET.SetPtEtaPhiM(met, 0, metphi, 0);
		Lep1.SetPtEtaPhiM(pt_1, eta_1, phi_1, m_1_tr);//need to save m1
		Lep2.SetPtEtaPhiM(pt_2, eta_2, phi_2, m_2_tr);
		Lep3.SetPtEtaPhiM(pt_3, eta_3, phi_3, m_3);
		Lep4.SetPtEtaPhiM(pt_4, eta_4, phi_4, m_4);	
		Vis1 = Lep1+Lep2;
		Vis2 = Lep3+Lep4;
		TLorentzVector vis_total = Vis1+Vis2; 
		//cout<<MET.Pt()<<endl;

		cout<<"Vis1 Pt: "<<Vis1.Pt()<< "\t" <<"Vis1 Eta: "<<Vis1.Eta()<<"\t" <<"Vis1 Phi: "<<Vis1.Phi()<<"\t" <<"Vis1 M: "<<Vis1.M()<<endl;		
		cout<<"Vis2 Pt: "<<Vis2.Pt()<< "\t" <<"Vis2 Eta: "<<Vis2.Eta()<<"\t" <<"Vis2 Phi: "<<Vis2.Phi()<<"\t" <<"Vis2 M: "<<Vis2.M()<<endl;
		
		TLorentzVector neutr_leg1, neutr_leg2;
		
		double ptleg1 = MET.Pt()*0.5;//assumption 1
		//constraint 1: ptleg1+ptleg2 = MET by vector addition
		double A=1, B = 2*ptleg1*TMath::Cos(Vis1.Phi()-Vis2.Phi()), C = ptleg1*ptleg1 - MET.Pt()*MET.Pt(); 
		double ptleg2 = (-B + TMath::Sqrt( B*B-4*A*C ))/(2*A);
		if (ptleg2 < 0){
			ptleg2 = (-B - TMath::Sqrt( B*B-4*A*C ))/(2*A);
		}
		
		float MDCH = (mll+mll2)/2;
		double mleg2 = abs(MDCH-mll2);//assumption 2 
		//constraint 2: mDCH1 = mDCH2 
		double Eleg2 = TMath::Sqrt(mleg2*mleg2 + ptleg2*ptleg2*TMath::CosH(Vis2.Eta())*TMath::CosH(Vis2.Eta()));//E = sqrt(m^2+Pt^2*Cosh^2(eta))
		double J = (Eleg2+Vis2.E()), K = (ptleg2+Vis2.Pt())*TMath::CosH(Vis2.Eta()), L = (ptleg1+Vis1.Pt())*TMath::CosH(Vis1.Eta()); 
		double Eleg1 = -Vis1.E()+TMath::Sqrt(J*J - K*K + L*L);
		if (Eleg1 < 0){
			Eleg1 = -Vis1.E()-TMath::Sqrt(J*J - K*K + L*L);
		}
		
		neutr_leg1.SetPtEtaPhiE(ptleg1, Vis1.Eta(), Vis1.Phi(), Eleg1);
		neutr_leg2.SetPtEtaPhiE(ptleg2, Vis2.Eta(), Vis2.Phi(), Eleg2);	
			
			
		if(neutr_leg1.M() < 0 || neutr_leg1.E() < 0){//for only one leg 
			ptleg1 = 0; ptleg2 = MET.Pt(); 
			Eleg1 = 0;
			mleg2 = abs(mll-mll2);
			Eleg2 = TMath::Sqrt(mleg2*mleg2 + ptleg2*ptleg2*TMath::CosH(Vis2.Eta())*TMath::CosH(Vis2.Eta()));
			neutr_leg1.SetPtEtaPhiE(ptleg1, Vis1.Eta(), Vis1.Phi(), Eleg1);
			neutr_leg2.SetPtEtaPhiE(ptleg2, Vis2.Eta(), Vis2.Phi(), Eleg2);	
			cout<<"HAHAHA"<<endl;
		}
		
		//##########################################
		//cout<<met<<"\t"<< (neutr_leg1+neutr_leg2).Pt()<<endl;
		cout<< "Nu1 Pt: "<< (neutr_leg1).Pt() <<"\t"<< " Eta: " << (neutr_leg1).Eta() <<"\t" <<" Phi: "<<(neutr_leg1).Phi()<<"\t" <<" M: "<<(neutr_leg1).M()<< endl;
		cout<< "Nu2 Pt: "<< (neutr_leg2).Pt() <<"\t"<< " Eta: " << (neutr_leg2).Eta() <<"\t" <<" Phi: "<<(neutr_leg2).Phi()<<"\t" <<" M: "<<(neutr_leg2).M()<< endl<<endl;
		
		
		h_mll->Fill(mll); h_mll2->Fill(mll2);
		h_mDCH1->Fill((Vis1+neutr_leg1).M());
		h_mDCH2->Fill((Vis2+neutr_leg2).M());
	}
	h_mll->Write();
	h_mll2->Write();
	h_mDCH1->Write();
	h_mDCH2->Write();
	h_mll->SetLineColor(4);h_mll2->SetLineColor(4);h_mDCH1->SetLineColor(2);h_mDCH2->SetLineColor(2);
	h_mll->SetLineWidth(2);h_mll2->SetLineWidth(2);h_mDCH1->SetLineWidth(2);h_mDCH2->SetLineWidth(2);
	
	leg->AddEntry(h_mll2, "Vis. Only");
	leg->AddEntry(h_mDCH2, "Vis. + split MET"); 
	if (h_mll2->GetMaximum() > h_mDCH2->GetMaximum()){
    	h_mll2->Draw();h_mll2->SetTitle("mDCH2");
    	h_mDCH2->Draw("SAME");
    }
    else{
    	h_mDCH2->Draw();h_mDCH2->SetTitle("mDCH2");
    	h_mll2->Draw("SAME");
    }
	leg->Draw();
	can->SaveAs("3mll2.png");
	leg->Clear();
	
	leg->AddEntry(h_mll, "Vis. Only");
	leg->AddEntry(h_mDCH1, "Vis. + split MET"); 
	if (h_mll->GetMaximum() > h_mDCH1->GetMaximum()){
    	h_mll->Draw();h_mll->SetTitle("mDCH1");
    	h_mDCH1->Draw("SAME");
    }
    else{
    	h_mDCH1->Draw();h_mDCH1->SetTitle("mDCH1");
    	h_mll->Draw("SAME");
    }
	leg->Draw();
	can->SaveAs("3mll.png");	
		
}

