#include "TMath.h"
#include <cmath>
#include <vector>
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "include/MyBranch.C"//branch definitons
#include "include/Kinematics.C"//Kine fns
#include "include/MET_split.C"

float XSec(std::string fname){
	if(fname.find("ttHTo2L2Nu") < fname.length()) return 0.5418;
	else if(fname.find("ttHToEE") < fname.length()) return 0;
	else if(fname.find("ttHToMuMu") < fname.length()) return 0.5269*0.000218;
	else if(fname.find("ttHToTauTau") < fname.length()) return 0.5269*0.0627;
	else if(fname.find("ttWJets") < fname.length()) return 0.4611;
	else if(fname.find("ttZJets") < fname.length()) return 0.5407;
	else if(fname.find("WWTo2L2Nu") < fname.length()) return 12.178;
	else if(fname.find("WWW_") < fname.length()) return 0.2086;
	else if(fname.find("WW_") < fname.length()) return 75.8;
	else if(fname.find("WZTo2Q2L") < fname.length()) return 6.204;
	else if(fname.find("WZTo3LNu") < fname.length()) return 5.052;
	else if(fname.find("WZZ_") < fname.length()) return 0.05565;
	else if(fname.find("WZ_") < fname.length()) return 27.6;
	else if(fname.find("ZHToMuMu") < fname.length()) return 0.7891*0.000218;
	else if(fname.find("ZHToTauTau") < fname.length()) return 0.7891*0.0627;
	else if(fname.find("ZZTo2L2Nu") < fname.length()) return 1.325;
	else if(fname.find("ZZTo2Q2L") < fname.length()) return 3.22;
	else if(fname.find("ZZTo4L") < fname.length()) return 1.325;
	else if(fname.find("ZZZ_") < fname.length()) return 0.01398;
	else if(fname.find("GluGluZH_") < fname.length()) return 0.0616;
	else if(fname.find("DYJetsToLLM10to50") < fname.length()) return 18610;
	else if(fname.find("DYJetsToLLM50") < fname.length()) return 6225.42;
	else if(fname.find("ST_s-channel_") < fname.length()) return 3.74;
	else if(fname.find("ST_t-channel_antitop_") < fname.length()) return 69.09;
	else if(fname.find("ST_t-channel_top_") < fname.length()) return 115.3;
	else if(fname.find("ST_tW_antitop_") < fname.length()) return 35.85;
	else if(fname.find("ST_tW_top_") < fname.length()) return 35.85;
	else if(fname.find("HppM") < fname.length()) return 0.001;
	else{
		std::cout<<"DON'T KNOW X-SEC FOR FILE "<<fname<<endl;
		return 0;
	}
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
	float mDCH = 500, mZ = 91.2, lumi_2018 = 139000;
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		TH1D* hnevts = (TH1D*)ifile->Get("hNEvts");
		float weight = lumi_2018*XSec(filename[j])/hnevts->Integral();
		//cout<<filename[j]<<endl;
		char *oname = gSystem->ConcatFileName("hist_CR", filename[j]);
		TFile* ofile = new TFile(oname, "RECREATE"); 
		TTree *tree = (TTree*)ifile->Get("Events");
		MyBranch(tree);
		TH1F* cutflow = new TH1F("cutflow", "cutflow", 6, 0, 6);     
		TH1F* h_mll_1 = new TH1F("h_mll_1", "mll_1", 1000, 0, mDCH+1500);
		TH1F* h_mll_2 = new TH1F("h_mll_2", "mll_2", 1000, 0, mDCH+1500);
		TH1F* h_mDCH1 = new TH1F("h_mDCH1", "mDCH1", 1000, 0, mDCH+1500);
		TH1F* h_mDCH2 = new TH1F("h_mDCH2", "mDCH2", 1000, 0, mDCH+1500);
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
		TH1F* h_dR1_met = new TH1F("h_dR1_met", "dR between 1st pair and MET ", 1000, 0, 5);
		TH1F* h_dR2_met = new TH1F("h_dR2_met", "dR between 2nd pair and MET ", 1000, 0, 5);				
		TH1F* h_cat = new TH1F("h_cat", "cat", 40,0,40);
		int nbins = 3000; float xmin = 0, xmax = 3000;
		TH1F* h_Xmass_0t = new TH1F("h_Xmass_0t", "mDCH1", nbins, xmin, xmax);
		TH1F* h_Xmass_1t = new TH1F("h_Xmass_1t", "mDCH1", nbins, xmin, xmax);
		TH1F* h_Xmass_2t = new TH1F("h_Xmass_2t", "mDCH1", nbins, xmin, xmax);
		TH1F* h_Xmass_34t = new TH1F("h_Xmass_34t", "mDCH1", nbins, xmin, xmax);
		TH1F* h_Xmass_3lep = new TH1F("h_Xmass_3lep", "mDCH1", nbins, xmin, xmax);
		for (int i =0; i < tree->GetEntries(); i++){
			tree->GetEntry(i);			
			float *lep_pt, *tau_pt;
			const char *cat_name = numberToCat(cat);
			int Nlep = cat_lepCount(cat_name,'e','m'); 
			int Ntau = strlen(cat_name)-Nlep;  

			//if (Ntau != 0) continue;
			//if (Ntau != 1) continue;
			//if (Ntau != 2) continue;
			//if (Ntau > 3) continue;
			//if (Ntau != 4) continue;
			double st = st;
			h_ST->Fill(st);
			
			h_mZ1->Fill(abs((LepV(1)+LepV(3)).M()));
			h_mZ2->Fill(abs((LepV(1)+LepV(4)).M()));
			h_mZ3->Fill(abs((LepV(2)+LepV(3)).M()));
			h_mZ4->Fill(abs((LepV(2)+LepV(4)).M()));
			h_met->Fill(met);

			
			auto [nu_leg1, nu_leg2] = MET_split(LepV(1),LepV(2),LepV(3),LepV(4),met,metphi);
			double mll_1, mll_2, m_dch1, m_dch2;
			TLorentzVector LL1, LL2;
			if ((LepV(1)+LepV(2)).Pt() > (LepV(3)+LepV(4)).Pt()){
				mll_1 = mll;
				mll_2 = mll2;
				m_dch1 = (nu_leg1+LepV(1)+LepV(2)).M();
				m_dch2 = (nu_leg2+LepV(3)+LepV(4)).M();
				LL1 = LepV(1)+LepV(2);
				LL2 = LepV(3)+LepV(4);
			}
			else{
				mll_1 = mll2;
				mll_2 = mll;
				m_dch1 = (nu_leg2+LepV(3)+LepV(4)).M();
				m_dch2 = (nu_leg1+LepV(1)+LepV(2)).M();
				LL2 = LepV(1)+LepV(2);
				LL1 = LepV(3)+LepV(4);
			}
			h_mll_1->Fill(mll_1);
			h_mll_2->Fill(mll_2);
			h_mDCH1->Fill(m_dch1);
			h_mDCH2->Fill(m_dch2);
			
			h_dR->Fill(getDR(eta_1,phi_1, eta_3,phi_3));h_dR->Fill(getDR(eta_1,phi_1, eta_4,phi_4));h_dR->Fill(getDR(eta_2,phi_2, eta_3,phi_3));h_dR->Fill(getDR(eta_2,phi_2, eta_4,phi_4));
			h_dRll->Fill(getDR(eta_1,phi_1, eta_2,phi_2));
			h_dRll2->Fill(getDR(eta_3,phi_3, eta_4,phi_4));
			h_dR1_met->Fill(getDR(0, metphi, 0, (LepV(1)+LepV(2)).Phi()));	
			h_dR2_met->Fill(getDR(0, metphi, 0, (LepV(3)+LepV(4)).Phi()));		
			cutflow->Fill(0);
//################# Pre-Selection AN #####################################################			
	/*		 if(Ntau == 4){
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
				//if(Ntau == 3 and lep_pt[0] < 30){ continue;}
			   	//if(Ntau <= 2 and (lep_pt[0] < 30 or lep_pt[2]< 20)){ continue;}
			   	cutflow->Fill(1);	
			}
			//if( getDR(eta_1,phi_1, eta_2,phi_2) < 0.02 or getDR(eta_1,phi_1, eta_3,phi_3) < 0.02 or getDR(eta_1,phi_1, eta_4,phi_4) < 0.02 or getDR(eta_2,phi_2, eta_3,phi_3) < 0.02 or getDR(eta_2,phi_2, eta_4,phi_4) < 0.02 or getDR(eta_3,phi_3, eta_4,phi_4) < 0.02 ){ continue;}
			cutflow->Fill(2);
//############## AN Mass-Based Selection ##################################################			
			//cutflow->Fill(1);cutflow->Fill(2);
			if (Ntau == 0){
				if (st < 1.63*mDCH-270){ continue;}//ST
				cutflow->Fill(3);cutflow->Fill(4);
				if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(1)+LepV(4)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(4)).M()-mZ) < 10){ continue;}
				cutflow->Fill(5);
				if (mll_1 <0.9*mDCH or mll_1 >1.1*mDCH or mll_2 <0.9*mDCH or mll_2 >1.1*mDCH){ continue;}  
				cutflow->Fill(6);
			}	
			else if (Ntau == 1){
				if (st < 1.30*mDCH-34){ continue;}//ST
				cutflow->Fill(3);		
				if (getDR(eta_1,phi_1, eta_2,phi_2) >3.3 or getDR(eta_3,phi_3, eta_4,phi_4) >3.3){ continue;}
				cutflow->Fill(4);	
				if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(1)+LepV(4)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(4)).M()-mZ) < 10){ continue;}
				cutflow->Fill(5);
				if (mll_1 <0.4*mDCH or mll_1 >1.1*mDCH or mll_2 <0.4*mDCH or mll_2 >1.1*mDCH){ continue;}
				cutflow->Fill(6);
			}
			else if (Ntau == 2){
				if (st < 0.56*mDCH+194){ continue;}//ST
				cutflow->Fill(3);
				if (getDR(eta_1,phi_1, eta_2,phi_2) >2.5 or getDR(eta_3,phi_3, eta_4,phi_4) >2.5){ continue;} 
				cutflow->Fill(4);
				if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(1)+LepV(4)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(4)).M()-mZ) < 10){ continue;}
				cutflow->Fill(5);
				if (mll_1 <0.3*mDCH or mll_1 >1.1*mDCH or mll_2 <0.3*mDCH or mll_2 >1.1*mDCH){ continue;}
				cutflow->Fill(6);
			}*/
//===================================================================================
			bool doMyPresel = false, doAtlasPresel = false, doAtlasCR = true, doAtlasVR = false;
			if(doMyPresel){//######My selections##########
				if (cat <=21){//4-lep
					if (Ntau == 0){
						if (st < 700){ continue;}//ST
						cutflow->Fill(1);
						if (getDR(eta_1,phi_1, eta_2,phi_2) >4 or getDR(eta_3,phi_3, eta_4,phi_4) >4){ continue;}
						cutflow->Fill(2);
						if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(1)+LepV(4)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(4)).M()-mZ) < 10){ continue;}
						cutflow->Fill(3);
						if (mll_1 <400  or mll_2 <400 ){ continue;}  
						cutflow->Fill(4);
						h_Xmass_0t->Fill(mll_1);
						//h_Xmass_0t->Fill(mll_2 + xmax/2);
					}	
					else if (Ntau == 1){
						if (st < 600){ continue;}//ST
						cutflow->Fill(1);		
						if (getDR(eta_1,phi_1, eta_2,phi_2) >3.6 or getDR(eta_3,phi_3, eta_4,phi_4) >3.6){ continue;}
						cutflow->Fill(2);	
						if (abs((LepV(1)+LepV(3)).M()-mZ) < 25 or abs((LepV(1)+LepV(4)).M()-mZ) < 25 or abs((LepV(2)+LepV(3)).M()-mZ) < 25 or abs((LepV(2)+LepV(4)).M()-mZ) < 25){ continue;}
						cutflow->Fill(3);
						if (mll_1 <250  or mll_2 <250 ){ continue;}
						cutflow->Fill(4);
						h_Xmass_1t->Fill(mll_1);
						//h_Xmass_1t->Fill(mll_2 + xmax/2);
					}
					else if (Ntau >= 2){
						if (st < 450){ continue;}//ST
						cutflow->Fill(1);
						if (getDR(eta_1,phi_1, eta_2,phi_2) >3.9 or getDR(eta_3,phi_3, eta_4,phi_4) >3.9){ continue;} 
						cutflow->Fill(2);
						if (abs((LepV(1)+LepV(3)).M()-mZ) < 5 or abs((LepV(1)+LepV(4)).M()-mZ) < 5 or abs((LepV(2)+LepV(3)).M()-mZ) < 5 or abs((LepV(2)+LepV(4)).M()-mZ) < 5){ continue;}
						cutflow->Fill(3);
						if (mll_1 <100  or mll_2 <100 ){ continue;}
						cutflow->Fill(4);
						h_Xmass_2t->Fill(mll_1);
						//h_Xmass_2t->Fill(mll_2 + xmax/2);
					}
					/*if (Ntau > 2){
						if (st < 450){ continue;}//ST
						cutflow->Fill(1);
						if (getDR(eta_1,phi_1, eta_2,phi_2) >3.9 or getDR(eta_3,phi_3, eta_4,phi_4) >3.9){ continue;} 
						cutflow->Fill(2);
						if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(1)+LepV(4)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(4)).M()-mZ) < 10){ continue;}
						cutflow->Fill(3);
						if (mll_1 <100 or mll_2 <100 ){ continue;}
						cutflow->Fill(4);
						h_Xmass_34t->Fill(mll_1);
					}*/
				}//4-lep	
				else if(cat >= 22 ){//3-lep	
					if (Ntau == 0){//0tau for 3lep
						if (pt_1+pt_2+pt_3 < 525){ continue;}//ST
						cutflow->Fill(1);
						if (getDR(eta_1,phi_1, eta_2,phi_2) >4){ continue;}
						cutflow->Fill(2);
						if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10){ continue;}
						cutflow->Fill(3);
						if (mll_1 <400){ continue;}  
						cutflow->Fill(4);
						h_Xmass_3lep->Fill(mll_1);
					}			
				}//3-lep
			}//MyPresel
			if(not doMyPresel && doAtlasPresel){
				if (mll_1 < 300)continue;
				if (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(1)+LepV(4)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(4)).M()-mZ) < 20)continue;
				if ( cat <= 21 ){
					if ( (mll_1+mll_2)/2 < 300 ) continue;
					h_Xmass_0t->Fill(mll_1);
					h_Xmass_1t->Fill(mll_1);
					h_Xmass_2t->Fill(mll_1);
				}
				else if ( cat >= 22){
					if (LL1.Pt() < 300)continue;
					h_Xmass_3lep->Fill(mll_1);
				}				
			}//Atlas Presel
			if(not doMyPresel && doAtlasCR){
				if ( cat <= 21 ){
					if (mll_1 >= 200 or mll_1 < 100)continue;
					h_Xmass_0t->Fill(mll_1);
					h_Xmass_1t->Fill(mll_1);
					h_Xmass_2t->Fill(mll_1);
				}
				else if ( cat >= 22){
					if (mll_1 < 300)continue;
					if (abs((LepV(1)+LepV(3)).M()-mZ) > 20 and abs((LepV(1)+LepV(4)).M()-mZ) > 20 and abs((LepV(2)+LepV(3)).M()-mZ) > 20 and abs((LepV(2)+LepV(4)).M()-mZ) > 20)continue;
					h_Xmass_3lep->Fill(mll_1);
				}
			}//Atlas CR for Di-bosons
			if(not doMyPresel && doAtlasVR){
				if ( cat <= 21 ){
					if (mll_1 >= 300 or mll_1 < 200)continue;
					h_Xmass_0t->Fill(mll_1);
					h_Xmass_1t->Fill(mll_1);
					h_Xmass_2t->Fill(mll_1);
				}
				else if ( cat >= 22){
					if (mll_1 >= 300 or mll_1 < 100)continue;
					if (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(1)+LepV(4)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(4)).M()-mZ) < 20)continue;
					h_Xmass_3lep->Fill(mll_1);
				}
			}//Atlas VR
			
		}//evt loop
		cutflow->Scale(weight);
		h_mll_1->Scale(weight);
		h_mll_2->Scale(weight);
		h_mDCH1->Scale(weight);
		h_mDCH2->Scale(weight);
		h_ST->Scale(weight);
		h_mZ1->Scale(weight);
		h_mZ2->Scale(weight);
		h_mZ3->Scale(weight);
		h_mZ4->Scale(weight);
		h_met->Scale(weight);
		h_pT1->Scale(weight);
		h_pT2->Scale(weight);
		h_pT3->Scale(weight);
		h_pT4->Scale(weight); 
		h_dR->Scale(weight);
		h_dRll->Scale(weight);
		h_dRll2->Scale(weight);
		h_dR1_met->Scale(weight);
		h_dR2_met->Scale(weight);
		h_Xmass_0t->Scale(weight);
		h_Xmass_1t->Scale(weight);
		h_Xmass_2t->Scale(weight);
		h_Xmass_34t->Scale(weight);
		h_Xmass_3lep->Scale(weight);
		
		hnevts->Write();		
		cutflow->Write();
		h_mll_1->Write();
		h_mll_2->Write();
		h_mDCH1->Write();
		h_mDCH2->Write();
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
		h_dR1_met->Write();
		h_dR2_met->Write();
		h_Xmass_0t->Write();
		h_Xmass_1t->Write();
		h_Xmass_2t->Write();
		h_Xmass_34t->Write();
		h_Xmass_3lep->Write();
		//cout<< j <<"\t"<< oname <<endl;
		printf("%s %f\n", oname, hnevts->Integral() );
		delete tree;
	}
	gSystem->FreeDirectory(dirp);
}

