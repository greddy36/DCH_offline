//To apply various kinematics selections right after online analysis.
#include "TMath.h"
#include <cmath>
#include <vector>
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "include/MyBranch.C"//branch definitons
#include "include/Kinematics.C"//Kine fns
#include "include/MET_split.C"
#include "include/Xsections.c"
#include "StackHist_test.C"

void DCH_test_presel(const char* ext = "2016.root"){
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
	
	const char* selection = "test";

	double mDCH = 500, mZ = 91.2, lumi_2016 = 35900, lumi_2017 = 41500, lumi_2018 = 58900.0;
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		std::string fname = filename[j];
		if (fname.find("_2016.") > fname.length()) continue;
		//if (fname.find("SingleMu") > fname.length()) continue;
		//if (fname.find("EGam") < fname.length()) continue;
		//if (XSec(filename[j])==1) continue; 
		cout<<filename[j]<<endl;
		
		TH1D* hnevts;
		double xs_weight = 1.0;
		if(XSec(filename[j])!=1){
			hnevts = (TH1D*)ifile->Get("hNWEvts");
			if (!hnevts) hnevts = (TH1D*)ifile->Get("hNEvts");
			xs_weight = lumi_2016*XSec(filename[j])/hnevts->Integral();
		}
		else hnevts = (TH1D*)ifile->Get("hNEvts");
		
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
		TTree *tree = (TTree*)ifile->Get("Events");
		MyBranch(tree);
		
		double xmin = 0, xmax = 3000; int binw = 100; int nbins = (xmax-xmin)/binw; 
		TH1F* cutflow = new TH1F("cutflow", "cutflow", 6, 0, 6);     
		TH1F* h_mll_1 = new TH1F("h_mll_1", "mll_1", nbins, xmin, xmax);
		TH1F* h_mll_2 = new TH1F("h_mll_2", "mll_2", nbins, xmin, xmax);
		TH1F* h_mDCH1 = new TH1F("h_mDCH1", "mDCH1", nbins, xmin, xmax);
		TH1F* h_mDCH2 = new TH1F("h_mDCH2", "mDCH2", nbins, xmin, xmax);
		TH1F* h_ll1_pt_4L = new TH1F("h_ll1_pt_4L", "Leading pair pT 4L channel", nbins, xmin, xmax);
		TH1F* h_ll1_pt_3L = new TH1F("h_ll1_pt_3L", "Leading pair pT 3L channel", nbins, xmin, xmax);
		TH1F* h_mZ1_3L = new TH1F("h_mZ1_3L", "Z1 mass in 3L channel", 50, 0, mDCH);
		TH1F* h_mZ2_3L = new TH1F("h_mZ2_3L", "Z2 mass in 3L channel", 50, 0, mDCH);
		TH1F* h_mZ3_3L = new TH1F("h_mZ3_3L", "Z3 mass in 3L channel", 50, 0, mDCH);
		TH1F* h_mZ4_3L = new TH1F("h_mZ4_3L", "Z4 mass in 3L channel", 50, 0, mDCH);

		TH1F* h_ST = new TH1F("h_ST", "ST", 100, 0, mDCH+2000);
		TH1F* h_mZ1 = new TH1F("h_mZ1", "Z1 mass in 4L channel", 50, 0, mDCH);
		TH1F* h_mZ2 = new TH1F("h_mZ2", "Z2 mass in 4L channel", 50, 0, mDCH);
		TH1F* h_mZ3 = new TH1F("h_mZ3", "Z3 mass in 4L channel", 50, 0, mDCH);
		TH1F* h_mZ4 = new TH1F("h_mZ4", "Z4 mass in 4L channel", 50, 0, mDCH);
		TH1F* h_met = new TH1F("h_met", "MET", 100, 0, mDCH+1500);
		TH1F* h_pT1 = new TH1F("h_pT1", "Leading pT", 100, 0, mDCH+1500);
		TH1F* h_pT2 = new TH1F("h_pT2", "Sub-leading pT", 100, 0, mDCH+1500);
		TH1F* h_pT3 = new TH1F("h_pT3", "3rd pT", 100, 0, mDCH+1500);
		TH1F* h_pT4 = new TH1F("h_pT4", "4th pT", 100, 0, mDCH+1500);
		TH1F* h_dR = new TH1F("h_dR", "dR (+-) leptons ", 50, 0, 5);
		TH1F* h_dRll = new TH1F("h_dRll", "dR between 1st pair", 50, 0, 5);
		TH1F* h_dRll2 = new TH1F("h_dRll2", "dR between 2nd pair", 50, 0, 5);
		TH1F* h_dR1_met = new TH1F("h_dR1_met", "dR between 1st pair and MET ", 50, 0, 5);
		TH1F* h_dR2_met = new TH1F("h_dR2_met", "dR between 2nd pair and MET ", 50, 0, 5);				
		TH1F* h_cat = new TH1F("h_cat", "cat", 40,0,40);
		TH1F* h_gencat = new TH1F("h_gencat", "gen cat", 40,0,40);

		TH1F* h_Xmass_0t = new TH1F("h_Xmass_0t", "mDCH1", nbins, xmin, xmax);
		TH1F* h_Xmass_1t = new TH1F("h_Xmass_1t", "mDCH1", nbins, xmin, xmax);
		TH1F* h_Xmass_2t = new TH1F("h_Xmass_2t", "mDCH1", nbins, xmin, xmax);
		TH1F* h_Xmass_34t = new TH1F("h_Xmass_34t", "mDCH1", nbins, xmin, xmax);
		TH1F* h_Xmass_3lep = new TH1F("h_Xmass_3lep", "mDCH1", nbins, xmin, xmax);
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
			applyTauES(cat_string);
//===================================================================================
			if(selection == "test"){//######My selections##########
				double st = ST(cat_name);
				std::vector<double> mZ, mZv, mH; 
				std::vector<int> paired_idx; 
				std::set<int> all_idx;
				for(int m = 1; m <= strlen(cat_name); ++m){
					all_idx.insert(m);
					for(int n = m+1; n <= strlen(cat_name); ++n){
						string pair_name = pairFunc(m,n,cat_name,5);
						//the vector elements are inv massses of highest pt pairs because we sotred the lepton vector by pt.
						if(pair_name=="Zwindow"){
							mZ.push_back((LepV(m)+LepV(n)).M());
							paired_idx.push_back(m);
							paired_idx.push_back(n);
						}
						else if(pair_name=="Zv") mZv.push_back((LepV(m)+LepV(n)).M());
						else if(pair_name=="DCH") mH.push_back((LepV(m)+LepV(n)).M());
						//else if(pair_name=="found nothing") cout<<"found nothing"<<endl;
						else continue;
						//if ((pair_name=="Zv") and mZv[0] <= 10) cout<<cat_name<<"\t"<<leptons[0].eta<<"\t"<<"\t"<<leptons[1].eta<<"\t"<<leptons[2].eta<<"\t"<<leptons[3].eta<< "\t"<<getDR(leptons[m-1].eta,leptons[m-1].phi,leptons[n-1].eta,leptons[n-1].phi)<<endl;
					}
				}				

				if (mZ.size() >0 ) continue;
				if (cat <=21){//4-lep
					if (Ntau == 0){
						if (st < 700){ continue;}//ST
						cutflow->Fill(1);
						//if (getDR(eta_1,phi_1, eta_2,phi_2) >4 or getDR(eta_3,phi_3, eta_4,phi_4) >4){ continue;}
						cutflow-> Fill(2);
						//if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(1)+LepV(4)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(4)).M()-mZ) < 10){ continue;}
						cutflow->Fill(3);
						//if (mH[0] <400 or mH[1] <400 ){ continue;}  
						if ((mH[0]+mH[1])/2 <200 ){ continue;}  
						cutflow->Fill(4);
						h_Xmass_0t->Fill(mH[0],brWeight);
						//h_Xmass_0t->Fill(mH[1] + xmax/2);
					}	
					else if (Ntau == 1){
						if (st < 600){ continue;}//ST
						cutflow->Fill(1);		
						//if (getDR(eta_1,phi_1, eta_2,phi_2) >3.6 or getDR(eta_3,phi_3, eta_4,phi_4) >3.6){ continue;}
						cutflow->Fill(2);	
						//if (abs((LepV(1)+LepV(3)).M()-mZ) < 25 or abs((LepV(1)+LepV(4)).M()-mZ) < 25 or abs((LepV(2)+LepV(3)).M()-mZ) < 25 or abs((LepV(2)+LepV(4)).M()-mZ) < 25){ continue;}
						cutflow->Fill(3);
						//if (mH[0] <250 or mH[1] <250 ){ continue;}
						if ((mH[0]+mH[1])/2 <250 ){ continue;}
						cutflow->Fill(4);
						h_Xmass_1t->Fill(mH[0],brWeight);
						//h_Xmass_1t->Fill(mH[1] + xmax/2);
					}
					else if (Ntau >= 2 and Ntau !=4){
						if (st < 450){ continue;}//ST
						cutflow->Fill(1);
						//if (getDR(eta_1,phi_1, eta_2,phi_2) >3.9 or getDR(eta_3,phi_3, eta_4,phi_4) >3.9){ continue;} 
						cutflow->Fill(2);
						//if (abs((LepV(1)+LepV(3)).M()-mZ) < 5 or abs((LepV(1)+LepV(4)).M()-mZ) < 5 or abs((LepV(2)+LepV(3)).M()-mZ) < 5 or abs((LepV(2)+LepV(4)).M()-mZ) < 5){ continue;}
						cutflow->Fill(3);
						//if (mH[0] <100 or mH[1] <100 ){ continue;}
						if ((mH[0]+mH[1])/2 <100 ){ continue;}
						cutflow->Fill(4);
						h_Xmass_2t->Fill(mH[0],brWeight);
						//h_Xmass_2t->Fill(mH[1] + xmax/2);
					}
					/*if (Ntau > 2){
						if (st < 450){ continue;}//ST
						cutflow->Fill(1);
						if (getDR(eta_1,phi_1, eta_2,phi_2) >3.9 or getDR(eta_3,phi_3, eta_4,phi_4) >3.9){ continue;} 
						cutflow->Fill(2);
						if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(1)+LepV(4)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(4)).M()-mZ) < 10){ continue;}
						cutflow->Fill(3);
						//if (mH[0] <100 or mH[1] <100 ){ continue;}
						if ((mH[0]+mH[1])/2 <100 ){ continue;}
						cutflow->Fill(4);
						h_Xmass_34t->Fill(mH[0],brWeight);
					}*/
				}//4-lep	
				else if(cat >= 22 and Ntau !=3 ){//3-lep	
					//if (Ntau == 0){//0tau for 3lep
						if (pt_1+pt_2+pt_3 < 525){ continue;}//ST
						cutflow->Fill(1);
						//if (getDR(eta_1,phi_1, eta_2,phi_2) >4){ continue;}
						cutflow->Fill(2);
						//if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10){ continue;}
						cutflow->Fill(3);
						if (mH[0] <400){ continue;}  
						cutflow->Fill(4);
						h_Xmass_3lep->Fill(mH[0],brWeight);
					//}			
				}//3-lep
			}//MyPresel
			
		}//evt loop
		cutflow->Scale(xs_weight);
		h_mll_1->Scale(xs_weight);
		h_mll_2->Scale(xs_weight);
		h_mDCH1->Scale(xs_weight);
		h_mDCH2->Scale(xs_weight);
		h_ST->Scale(xs_weight);
		h_ll1_pt_4L->Scale(xs_weight);
		h_ll1_pt_3L->Scale(xs_weight);
		h_mZ1->Scale(xs_weight);
		h_mZ2->Scale(xs_weight);
		h_mZ3->Scale(xs_weight);
		h_mZ4->Scale(xs_weight);
		h_mZ1_3L->Scale(xs_weight);
		h_mZ2_3L->Scale(xs_weight);
		h_mZ3_3L->Scale(xs_weight);
		h_mZ4_3L->Scale(xs_weight);
		h_met->Scale(xs_weight);
		h_pT1->Scale(xs_weight);
		h_pT2->Scale(xs_weight);
		h_pT3->Scale(xs_weight);
		h_pT4->Scale(xs_weight); 
		h_dR->Scale(xs_weight);
		h_dRll->Scale(xs_weight);
		h_dRll2->Scale(xs_weight);
		h_dR1_met->Scale(xs_weight);
		h_dR2_met->Scale(xs_weight);
		h_Xmass_0t->Scale(xs_weight);
		h_Xmass_1t->Scale(xs_weight);
		h_Xmass_2t->Scale(xs_weight);
		h_Xmass_34t->Scale(xs_weight);
		h_Xmass_3lep->Scale(xs_weight);
		
		hnevts->Write();		
		/*cutflow->Write();
		h_mH[0]->Write();
		h_mH[1]->Write();
		h_mDCH1->Write();
		h_mDCH2->Write();
		h_ST->Write();
		h_ll1_pt_4L->Write();
		h_ll1_pt_3L->Write();
		h_mZ1->Write();
		h_mZ2->Write();
		h_mZ3->Write();
		h_mZ4->Write();
		h_mZ1_3L->Write();
		h_mZ2_3L->Write();
		h_mZ3_3L->Write();
		h_mZ4_3L->Write();
		h_met->Write();
		h_pT1->Write();
		h_pT2->Write();
		h_pT3->Write();
		h_pT4->Write(); 
		h_dR->Write();
		h_dRll->Write();
		h_dRll2->Write();
		h_dR1_met->Write();
		h_dR2_met->Write();*/
		h_Xmass_0t->Write();
		h_Xmass_1t->Write();
		h_Xmass_2t->Write();
		h_Xmass_34t->Write();
		h_Xmass_3lep->Write();
		h_gencat->Write();
		h_cat->Write();
		//cout<< j <<"\t"<< oname <<endl;
		printf("%s %f\t %f\n ", oname,  h_Xmass_0t->Integral(), h_Xmass_3lep->Integral());
		delete tree;
	}
	gSystem->FreeDirectory(dirp);
	StackHist_test();
}

