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
	else if(fname.find("WZ_") < fname.length()) return 0;//return 27.6;
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
	else if(fname.find("HppM") < fname.length()) return 0.001;//Signal
	else if(fname.find("EGamma") < fname.length()) return 1;//Data
	else if(fname.find("Muon") < fname.length()) return 1;//Data
	else if(fname.find("Tau") < fname.length()) return 1;//Data
	else{
		std::cout<<"DON'T KNOW X-SEC FOR FILE "<<fname<<endl;
		return 0;
	}
}

void DCH_presel(const char* ext = "2018.root"){
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
	
	const char* selection = "APre";

	float mDCH = 500, mZ = 91.2, lumi_2018 = 139000;
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		TH1D* hnevts = (TH1D*)ifile->Get("hNEvts");
		float weight = 1;
		if(XSec(filename[j])!=1) weight = lumi_2018*XSec(filename[j])/hnevts->Integral();

		std::string fname = filename[j];
		//if (fname.find("HppM100") > fname.length()) continue;
		//cout<<filename[j]<<endl;
		
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
		float xmin = 0, xmax = 3000; int binw = 100; int nbins = (xmax-xmin)/binw; 
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
			float *lep_pt, *tau_pt;
			const char *cat_name = numberToCat(cat);
			int Nlep = cat_lepCount(cat_name,'e','m'); 
			int Ntau = strlen(cat_name)-Nlep;  
			//if (cat_name != "mmmm") continue;
			float brWeight = 1;
			if (fname.find("HppM") < fname.length()){
				std::string Gencat_str = numberToCat(gen_cat);
				if (Gencat_str.substr(0,2) == "ee" || Gencat_str.substr(0,2) == "mm" || Gencat_str.substr(0,2) == "tt")
					brWeight = brWeight*3/2;
				else if (Gencat_str.substr(0,2) == "em" || Gencat_str.substr(0,2) == "et" || Gencat_str.substr(0,2) == "mt")
					brWeight = brWeight*3/4;
				if (Gencat_str.substr(2,2) == "ee" || Gencat_str.substr(2,2) == "mm" || Gencat_str.substr(0,2) == "tt")
					brWeight = brWeight*3/2;
				else if (Gencat_str.substr(2,2) == "em" || Gencat_str.substr(2,2) == "et" || Gencat_str.substr(0,2) == "mt")
					brWeight = brWeight*3/4;
					
				//if (Gencat_str.substr(0,2) == Gencat_str.substr(2,2))
					//brWeight = brWeight*2;
				//cout<<brWeight<<"\t"<<Gencat_str<<endl;
			}
			
			//if (Ntau != 0) continue;
			//if (Ntau != 1) continue;
			//if (Ntau != 2) continue;
			//if (Ntau > 3) continue;
			//if (Ntau != 4) continue;
			double st = st;
			h_ST->Fill(st);
			
			/*h_mZ1->Fill(abs((LepV(1)+LepV(3)).M()));
			h_mZ2->Fill(abs((LepV(1)+LepV(4)).M()));
			h_mZ3->Fill(abs((LepV(2)+LepV(3)).M()));
			h_mZ4->Fill(abs((LepV(2)+LepV(4)).M()));
			h_met->Fill(met);*/
			//if (isTrig_1 ==0 and isTrig_2 ==0) continue;
			
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
			if(selection == "Pre"){//######My selections##########
				if (cat <=21){//4-lep
					if (Ntau == 0){
						if (st < 400){ continue;}//ST
						cutflow->Fill(1);
						//if (getDR(eta_1,phi_1, eta_2,phi_2) >4 or getDR(eta_3,phi_3, eta_4,phi_4) >4){ continue;}
						cutflow->Fill(2);
						if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(1)+LepV(4)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(4)).M()-mZ) < 10){ continue;}
						cutflow->Fill(3);
						//if (mll_1 <400 or mll_2 <400 ){ continue;}  
						if ((mll_1+mll_2)/2 <200 ){ continue;}  
						cutflow->Fill(4);
						h_Xmass_0t->Fill(mll_1,brWeight);
						//h_Xmass_0t->Fill(mll_2 + xmax/2);
					}	
					else if (Ntau == 1){
						if (st < 600){ continue;}//ST
						cutflow->Fill(1);		
						//if (getDR(eta_1,phi_1, eta_2,phi_2) >3.6 or getDR(eta_3,phi_3, eta_4,phi_4) >3.6){ continue;}
						cutflow->Fill(2);	
						if (abs((LepV(1)+LepV(3)).M()-mZ) < 25 or abs((LepV(1)+LepV(4)).M()-mZ) < 25 or abs((LepV(2)+LepV(3)).M()-mZ) < 25 or abs((LepV(2)+LepV(4)).M()-mZ) < 25){ continue;}
						cutflow->Fill(3);
						//if (mll_1 <250 or mll_2 <250 ){ continue;}
						if ((mll_1+mll_2)/2 <250 ){ continue;}
						cutflow->Fill(4);
						h_Xmass_1t->Fill(mll_1,brWeight);
						//h_Xmass_1t->Fill(mll_2 + xmax/2);
					}
					else if (Ntau >= 2 and Ntau !=4){
						if (st < 450){ continue;}//ST
						cutflow->Fill(1);
						//if (getDR(eta_1,phi_1, eta_2,phi_2) >3.9 or getDR(eta_3,phi_3, eta_4,phi_4) >3.9){ continue;} 
						cutflow->Fill(2);
						if (abs((LepV(1)+LepV(3)).M()-mZ) < 5 or abs((LepV(1)+LepV(4)).M()-mZ) < 5 or abs((LepV(2)+LepV(3)).M()-mZ) < 5 or abs((LepV(2)+LepV(4)).M()-mZ) < 5){ continue;}
						cutflow->Fill(3);
						//if (mll_1 <100 or mll_2 <100 ){ continue;}
						if ((mll_1+mll_2)/2 <100 ){ continue;}
						cutflow->Fill(4);
						h_Xmass_2t->Fill(mll_1,brWeight);
						//h_Xmass_2t->Fill(mll_2 + xmax/2);
					}
					/*if (Ntau > 2){
						if (st < 450){ continue;}//ST
						cutflow->Fill(1);
						if (getDR(eta_1,phi_1, eta_2,phi_2) >3.9 or getDR(eta_3,phi_3, eta_4,phi_4) >3.9){ continue;} 
						cutflow->Fill(2);
						if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(1)+LepV(4)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(4)).M()-mZ) < 10){ continue;}
						cutflow->Fill(3);
						//if (mll_1 <100 or mll_2 <100 ){ continue;}
						if ((mll_1+mll_2)/2 <100 ){ continue;}
						cutflow->Fill(4);
						h_Xmass_34t->Fill(mll_1,brWeight);
					}*/
				}//4-lep	
				else if(cat >= 22 and Ntau !=3 ){//3-lep	
					//if (Ntau == 0){//0tau for 3lep
						if (pt_1+pt_2+pt_3 < 525){ continue;}//ST
						cutflow->Fill(1);
						//if (getDR(eta_1,phi_1, eta_2,phi_2) >4){ continue;}
						cutflow->Fill(2);
						if (abs((LepV(1)+LepV(3)).M()-mZ) < 10 or abs((LepV(2)+LepV(3)).M()-mZ) < 10){ continue;}
						cutflow->Fill(3);
						if (mll_1 <400){ continue;}  
						cutflow->Fill(4);
						h_Xmass_3lep->Fill(mll_1,brWeight);
					//}			
				}//3-lep
			}//MyPresel
//###################### ATLAS #########################
			//if (Ntau != 0) continue;
			if(selection == "APre"){//ATLAS Signal region
				if (mll_1 < 300)continue;
				//if ( cat <= 21 ){
				if (cat<= 21 and Ntau ==0){
					if (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(1)+LepV(4)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(4)).M()-mZ) < 20)continue;
					if ( (mll_1+mll_2)/2 < 300 ) continue;
					h_Xmass_0t->Fill(mll_1,brWeight);

					h_ll1_pt_4L->Fill(LL1.Pt());
					h_mZ1->Fill(abs((LepV(1)+LepV(3)).M()));
					h_mZ2->Fill(abs((LepV(1)+LepV(4)).M()));
					h_mZ3->Fill(abs((LepV(2)+LepV(3)).M()));
					h_mZ4->Fill(abs((LepV(2)+LepV(4)).M()));
				}
				else if ( cat >= 22 and Ntau !=3){
				//else if ( cat >= 22 and Ntau ==0){
				//if ((cat<=21 and Ntau ==1) or (cat>=21 and Ntau ==0)){
					if (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20)continue;
					if (LL1.Pt() < 300)continue;
					h_Xmass_3lep->Fill(mll_1,brWeight);

					h_ll1_pt_3L->Fill(LL1.Pt());
					h_mZ1_3L->Fill(abs((LepV(1)+LepV(3)).M()));
					h_mZ2_3L->Fill(abs((LepV(2)+LepV(3)).M()));
				}
				
				//=================test============
				else if (cat<= 21 and Ntau == 1){
					if (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(1)+LepV(4)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(4)).M()-mZ) < 20)continue;
					if ( (mll_1+mll_2)/2 < 300 ) continue;
					h_Xmass_1t->Fill(mll_1,brWeight);
				}
				else if (cat<= 21 and Ntau >= 2 and Ntau !=4){
					if (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(1)+LepV(4)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(4)).M()-mZ) < 20)continue;
					if ( (mll_1+mll_2)/2 < 300 ) continue;
					h_Xmass_2t->Fill(mll_1,brWeight);

				}//================test================
					
			}
			else if(selection == "CR"){//Atlas CR for Di-bosons
				if ( cat <= 21 ){
					if (mll_1 >= 200 or mll_1 < 100)continue;
					h_Xmass_0t->Fill(mll_1);
					h_Xmass_1t->Fill(mll_1);
					h_Xmass_2t->Fill(mll_1);

					h_ll1_pt_4L->Fill(LL1.Pt());
					h_mZ1->Fill(abs((LepV(1)+LepV(3)).M()));
					h_mZ2->Fill(abs((LepV(1)+LepV(4)).M()));
					h_mZ3->Fill(abs((LepV(2)+LepV(3)).M()));
					h_mZ4->Fill(abs((LepV(2)+LepV(4)).M()));
				}
				else if ( cat >= 22){
					if (mll_1 < 300)continue;
					if (abs((LepV(1)+LepV(3)).M()-mZ) > 20 and abs((LepV(2)+LepV(3)).M()-mZ) > 20)continue;
					h_Xmass_3lep->Fill(mll_1);
					
					h_ll1_pt_3L->Fill(LL1.Pt());
					h_mZ1_3L->Fill(abs((LepV(1)+LepV(3)).M()));
					h_mZ2_3L->Fill(abs((LepV(2)+LepV(3)).M()));
				}
			}
			else if(selection == "VR"){//Atlas VR
				if ( cat <= 21 ){
					if (mll_1 >= 300 or mll_1 < 200)continue;
					h_Xmass_0t->Fill(mll_1);
					h_Xmass_1t->Fill(mll_1);
					h_Xmass_2t->Fill(mll_1);

					h_ll1_pt_4L->Fill(LL1.Pt());
					h_mZ1->Fill(abs((LepV(1)+LepV(3)).M()));
					h_mZ2->Fill(abs((LepV(1)+LepV(4)).M()));
					h_mZ3->Fill(abs((LepV(2)+LepV(3)).M()));
					h_mZ4->Fill(abs((LepV(2)+LepV(4)).M()));
					//cout<<i <<" "<<pt_4<<" "<<pt_3<<" "<<endl;
				}
				else if ( cat >= 22){
					if (mll_1 >= 300 or mll_1 < 100)continue;
					if (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20)continue;
					h_Xmass_3lep->Fill(mll_1);

					h_ll1_pt_3L->Fill(LL1.Pt());
					h_mZ1_3L->Fill(abs((LepV(1)+LepV(3)).M()));
					h_mZ2_3L->Fill(abs((LepV(2)+LepV(3)).M()));
				}
			}
			else if(selection == "test"){//My tests
				if (cat_name == "eee" and (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20)) h_Xmass_0t->Fill(mll_1);
				else if (cat_name == "eme" and abs((LepV(1)+LepV(3)).M()-mZ) < 20) h_Xmass_1t->Fill(mll_1);
				else if( cat_name == "mmm" and (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20)) h_Xmass_2t->Fill(mll_1);
				else if (cat_name == "emm" and abs((LepV(2)+LepV(3)).M()-mZ) < 20) h_Xmass_34t->Fill(mll_1);
				
				/*else if (cat_name == "eee" and (abs((LepV(1)+LepV(3)).M()-mZ) > 20 and abs((LepV(2)+LepV(3)).M()-mZ) > 20)) h_Xmass_2t->Fill(mll_1);
				else if (cat_name == "eme" and abs((LepV(1)+LepV(3)).M()-mZ) > 20) h_Xmass_2t->Fill(mll_1);
				else if( cat_name == "mmm" and (abs((LepV(1)+LepV(3)).M()-mZ) > 20 or abs((LepV(2)+LepV(3)).M()-mZ) > 20)) h_Xmass_34t->Fill(mll_1);
				else if (cat_name == "emm" and abs((LepV(2)+LepV(3)).M()-mZ) > 20) h_Xmass_34t->Fill(mll_1);*/
			}
			/*else{
				if ( cat <= 21 ){
					h_Xmass_0t->Fill(mll_1);
					h_Xmass_1t->Fill(mll_1);
					h_Xmass_2t->Fill(mll_1);
					h_ll1_pt_4L->Fill(LL1.Pt());
					h_mZ1->Fill(abs((LepV(1)+LepV(3)).M()));
					h_mZ2->Fill(abs((LepV(1)+LepV(4)).M()));
					h_mZ3->Fill(abs((LepV(2)+LepV(3)).M()));
					h_mZ4->Fill(abs((LepV(2)+LepV(4)).M()));
				}
				else if ( cat >= 22){
					h_Xmass_3lep->Fill(mll_1);
					h_ll1_pt_3L->Fill(LL1.Pt());
					h_mZ1_3L->Fill(abs((LepV(1)+LepV(3)).M()));
					h_mZ2_3L->Fill(abs((LepV(2)+LepV(3)).M()));
				}
			}*/
			
		}//evt loop
		cutflow->Scale(weight);
		h_mll_1->Scale(weight);
		h_mll_2->Scale(weight);
		h_mDCH1->Scale(weight);
		h_mDCH2->Scale(weight);
		h_ST->Scale(weight);
		h_ll1_pt_4L->Scale(weight);
		h_ll1_pt_3L->Scale(weight);
		h_mZ1->Scale(weight);
		h_mZ2->Scale(weight);
		h_mZ3->Scale(weight);
		h_mZ4->Scale(weight);
		h_mZ1_3L->Scale(weight);
		h_mZ2_3L->Scale(weight);
		h_mZ3_3L->Scale(weight);
		h_mZ4_3L->Scale(weight);
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
		/*cutflow->Write();
		h_mll_1->Write();
		h_mll_2->Write();
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
}

