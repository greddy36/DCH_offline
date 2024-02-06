#include "TMath.h"
#include <cmath>
#include <vector>
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "include/MyBranch.C"//branch definitons
#include "include/Kinematics.h"//Kine fns
#include "include/cat.h"
	
void DCH_presel(const char* ext = ".root"){
	const char* inDir = ".";
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
	gROOT->Reset();
	float mDCH = 500, mZ = 91;
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < n; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		cout<<filename[j]<<endl;
		char *oname = gSystem->ConcatFileName("hist", filename[j]);
		TFile* ofile = new TFile(oname, "RECREATE");
		TTree *tree = (TTree*)ifile->Get("Events");
		MyBranch(tree);
		TH1F* cutflow = new TH1F("cutflow", "cutflow", 6, 0, 6);     
		TH1F* h_mll = new TH1F("h_mll", "mll", 1000, 0, mDCH+1500);
		TH1F* h_mll2 = new TH1F("h_mll2", "mll2", 1000, 0, mDCH+1500);
		TH1F* h_ST = new TH1F("h_ST", "ST", 1000, 0, mDCH+2000);
		TH1F* h_mZ1 = new TH1F("h_mZ1", "Z mass 1", 1000, 0, mDCH+1500);
		TH1F* h_mZ2 = new TH1F("h_mZ2", "Z mass 2", 1000, 0, mDCH+1500);
		TH1F* h_mZ3 = new TH1F("h_mZ3", "Z mass 3", 1000, 0, mDCH+1500);
		TH1F* h_mZ4 = new TH1F("h_mZ4", "Z mass 4", 1000, 0, mDCH+1500);
		TH1F* h_met = new TH1F("h_met", "MET", 1000, 0, mDCH+1500);
		TH1F* h_pT1 = new TH1F("h_pT1", "Leading pT", 1000, 0, mDCH+1500);
		TH1F* h_pT2 = new TH1F("h_pT2", "Sub-leading pT", 1000, 0, mDCH+1500);
		TH1F* h_pT3 = new TH1F("h_pT3", "3rd pT", 1000, 0, mDCH+1500);
		TH1F* h_pT4 = new TH1F("h_pT4", "4th pT", 1000, 0, mDCH+1500);
		TH1F* h_dR = new TH1F("h_dR", "dR (+-) leptons ", 1000, 0, 5);
		TH1F* h_dRll = new TH1F("h_dRll", "dR between 1st pair", 1000, 0, 5);
		TH1F* h_dRll2 = new TH1F("h_dRll2", "dR between 2nd pair", 1000, 0, 5);
		//TH1F* h_cat = new TH1F("h_cat", "cat", 22,0,22);
		TH1F* h_Xmass_0t = new TH1F("h_Xmass_0t", "mDCH1", 1000, 0, 3000);
		TH1F* h_Xmass_1t = new TH1F("h_Xmass_1t", "mDCH1", 1000, 0, 3000);
		TH1F* h_Xmass_2t = new TH1F("h_Xmass_2t", "mDCH1", 1000, 0, 3000);
		TH1F* h_Xmass_34t = new TH1F("h_Xmass_34t", "mDCH1", 1000, 0, 3000);
		for (int i =0; i < tree->GetEntries(); i++){
			tree->GetEntry(i);			
			float *lep_pt, *tau_pt;
			const char *cat_name = numberToCat(cat);
			int lep_count = cat_lepCount(cat_name,'e','m');

			//if (lep_count != 4) continue;// 0 tau
			//if (lep_count != 3) continue;// 1 tau
			//if (lep_count != 2) continue;// 2 tau
			//if (lep_count > 1) continue;// 3-4 tau
			//if (lep_count != 0) continue;// 4 tau
			
			h_ST->Fill(pt_1+pt_2+pt_3+pt_4);
			h_mll->Fill(mll);
			h_mll2->Fill(mll2);
			h_mZ1->Fill(abs((LepV(1)+LepV(3)).M()));
			h_mZ2->Fill(abs((LepV(1)+LepV(4)).M()));
			h_mZ3->Fill(abs((LepV(2)+LepV(3)).M()));
			h_mZ4->Fill(abs((LepV(2)+LepV(4)).M()));
			h_met->Fill(met);
			h_dR->Fill(getDR(eta_1,phi_1, eta_3,phi_3));h_dR->Fill(getDR(eta_1,phi_1, eta_4,phi_4));h_dR->Fill(getDR(eta_2,phi_2, eta_3,phi_3));h_dR->Fill(getDR(eta_2,phi_2, eta_4,phi_4));
			h_dRll->Fill(getDR(eta_1,phi_1, eta_2,phi_2));
			h_dRll2->Fill(getDR(eta_3,phi_3, eta_4,phi_4));			
			cutflow->Fill(0);
//################# Pre-Selection #########################################################			
	/*		 if(lep_count == 0){
				tau_pt  = SortPt(cat_name,"t");
				h_pT1->Fill(tau_pt[0]);
				h_pT2->Fill(tau_pt[1]);
				h_pT3->Fill(tau_pt[2]);
				h_pT4->Fill(tau_pt[3]);
				//if(tau_pt[0] < 40 or tau_pt[1]< 40){ continue;}
				cutflow->Fill(1);
			}  
			else{ 
				lep_pt  = SortPt(cat_name,"nottau");
				h_pT1->Fill(lep_pt[0]);
				h_pT2->Fill(lep_pt[1]);
				h_pT3->Fill(lep_pt[2]);
				h_pT4->Fill(lep_pt[3]);
				//if(lep_count == 1 and lep_pt[0] < 30){ continue;}
			   	//if(lep_count >= 2 and (lep_pt[0] < 30 or lep_pt[2]< 20)){ continue;}
			   	cutflow->Fill(1);
			}
			//if( getDR(eta_1,phi_1, eta_2,phi_2) < 0.02 or getDR(eta_1,phi_1, eta_3,phi_3) < 0.02 or getDR(eta_1,phi_1, eta_4,phi_4) < 0.02 or getDR(eta_2,phi_2, eta_3,phi_3) < 0.02 or getDR(eta_2,phi_2, eta_4,phi_4) < 0.02 or getDR(eta_3,phi_3, eta_4,phi_4) < 0.02 ){ continue;}
			cutflow->Fill(2);
//############## AN Mass-Based Selection ##################################################			
			//cutflow->Fill(1);cutflow->Fill(2);
			if (lep_count == 4){
				if (pt_1+pt_2+pt_3+pt_4 < 1.63*mDCH-270){ continue;}//ST
				cutflow->Fill(3);cutflow->Fill(4);
				if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(1)+LepV(4)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(4)).M()-mZ) < 10){ continue;}
				cutflow->Fill(5);
				if (mll <0.9*mDCH or mll >1.1*mDCH or mll2 <0.9*mDCH or mll2 >1.1*mDCH){ continue;}  
				cutflow->Fill(6);
			}	
			else if (lep_count == 3){
				if (pt_1+pt_2+pt_3+pt_4 < 1.30*mDCH-34){ continue;}//ST
				cutflow->Fill(3);		
				if (getDR(eta_1,phi_1, eta_2,phi_2) >3.3 or getDR(eta_3,phi_3, eta_4,phi_4) >3.3){ continue;}
				cutflow->Fill(4);	
				if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(1)+LepV(4)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(4)).M()-mZ) < 10){ continue;}
				cutflow->Fill(5);
				if (mll <0.4*mDCH or mll >1.1*mDCH or mll2 <0.4*mDCH or mll2 >1.1*mDCH){ continue;}
				cutflow->Fill(6);
			}
			else if (lep_count == 2){
				if (pt_1+pt_2+pt_3+pt_4 < 0.56*mDCH+194){ continue;}//ST
				cutflow->Fill(3);
				if (getDR(eta_1,phi_1, eta_2,phi_2) >2.5 or getDR(eta_3,phi_3, eta_4,phi_4) >2.5){ continue;} 
				cutflow->Fill(4);
				if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(1)+LepV(4)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(4)).M()-mZ) < 10){ continue;}
				cutflow->Fill(5);
				if (mll <0.3*mDCH or mll >1.1*mDCH or mll2 <0.3*mDCH or mll2 >1.1*mDCH){ continue;}
				cutflow->Fill(6);
			}*/
//##################################My selection##########################################	
			if (lep_count == 4){
				if (pt_1+pt_2+pt_3+pt_4 < 700){ continue;}//ST
				cutflow->Fill(1);
				if (getDR(eta_1,phi_1, eta_2,phi_2) >4 or getDR(eta_3,phi_3, eta_4,phi_4) >4){ continue;}
				cutflow->Fill(2);
				if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(1)+LepV(4)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(4)).M()-mZ) < 10){ continue;}
				cutflow->Fill(3);
				if (mll <400  or mll2 <400 ){ continue;}  
				cutflow->Fill(4);
				h_Xmass_0t->Fill(mll);
			}	
			else if (lep_count == 3){
				if (pt_1+pt_2+pt_3+pt_4 < 600){ continue;}//ST
				cutflow->Fill(1);		
				if (getDR(eta_1,phi_1, eta_2,phi_2) >3.6 or getDR(eta_3,phi_3, eta_4,phi_4) >3.6){ continue;}
				cutflow->Fill(2);	
				if (abs((LepV(1)+LepV(3)).M()-mZ) < 25 or abs((LepV(1)+LepV(4)).M()-mZ) < 25 or abs((LepV(2)+LepV(3)).M()-mZ) < 25 or abs((LepV(2)+LepV(4)).M()-mZ) < 25){ continue;}
				cutflow->Fill(3);
				if (mll <250  or mll2 <250 ){ continue;}
				cutflow->Fill(4);
				h_Xmass_1t->Fill(mll);
			}
			else if (lep_count == 2){
				if (pt_1+pt_2+pt_3+pt_4 < 600){ continue;}//ST
				cutflow->Fill(1);
				if (getDR(eta_1,phi_1, eta_2,phi_2) >3.9 or getDR(eta_3,phi_3, eta_4,phi_4) >3.9){ continue;} 
				cutflow->Fill(2);
				if (abs((LepV(1)+LepV(3)).M()-mZ) < 85 or abs((LepV(1)+LepV(4)).M()-mZ) < 85 or abs((LepV(2)+LepV(3)).M()-mZ) < 85 or abs((LepV(2)+LepV(4)).M()-mZ) < 85){ continue;}
				cutflow->Fill(3);
				if (mll <150  or mll2 <150 ){ continue;}
				cutflow->Fill(4);
				h_Xmass_2t->Fill(mll);
			}
			if (lep_count < 2){
				if (pt_1+pt_2+pt_3+pt_4 < 450){ continue;}//ST
				cutflow->Fill(1);
				if (getDR(eta_1,phi_1, eta_2,phi_2) >3.9 or getDR(eta_3,phi_3, eta_4,phi_4) >3.9){ continue;} 
				cutflow->Fill(2);
				if (abs((LepV(1)+LepV(3)).M()-mZ) < 5 or abs((LepV(1)+LepV(4)).M()-mZ) < 5 or abs((LepV(2)+LepV(3)).M()-mZ) < 5 or abs((LepV(2)+LepV(4)).M()-mZ) < 5){ continue;}
				cutflow->Fill(3);
				if (mll <100 or mll2 <100 ){ continue;}
				cutflow->Fill(4);
				h_Xmass_34t->Fill(mll);
			}			
		}
		cutflow->Write();
		h_mll->Write();
		h_mll2->Write();
		h_ST->Write();
		h_mZ1->Write();
		h_mZ2->Write();
		h_mZ3->Write();
		h_mZ4->Write();
		h_met->Write();
		h_pT1->Write();
		h_pT2->Write();
		h_pT3->Write();
		h_pT4->Write(); 
		h_dR->Write();
		h_dRll->Write();
		h_dRll2->Write();
		h_Xmass_0t->Write();
		h_Xmass_1t->Write();
		h_Xmass_2t->Write();
		h_Xmass_34t->Write();
		//cout<< j <<"\t"<< oname <<endl;
		//printf("%s %f\n", oname, cutflow->GetBinContent(5));
		delete tree;
	}
	gSystem->FreeDirectory(dirp);
}