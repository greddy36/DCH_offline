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
	else if(fname.find("HppM") < fname.length()) return 0.001;//Signal
	else if(fname.find("EGamma") < fname.length()) return 1;//Data
	else if(fname.find("Muon") < fname.length()) return 1;//Data
	else if(fname.find("Tau") < fname.length()) return 1;//Data
	else{
		std::cout<<"DON'T KNOW X-SEC FOR FILE "<<fname<<endl;
		return 0;
	}
}

void DCH_test(const char* ext = ".root"){
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

	float mDCH = 500, mZ = 91.2, lumi_2018 = 139000;
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		TH1D* hnevts = (TH1D*)ifile->Get("hNEvts");
		float weight = 1;
		if(XSec(filename[j])!=1) weight = lumi_2018*XSec(filename[j])/hnevts->Integral();
		
		std::string fname = filename[j];
		//if (fname.find("DYJets") > fname.length()) continue;
		
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
		

		TH1F* h_mZ1 = new TH1F("h_mZ1", "mZ (e+e- & e)", 50, 0, 500);
		TH1F* h_mZ2 = new TH1F("h_mZ2", "mZ (e+e- & m)", 50, 0, 500);
		TH1F* h_mZ3 = new TH1F("h_mZ3", "mZ (m+m- & e)", 50, 0, 500);
		TH1F* h_mZ4 = new TH1F("h_mZ4", "mZ (m+m- & m)", 50, 0, 500);
		TH1F* h_mZv1 = new TH1F("h_mZv1", "Z-veto (e+e- & e)", 50, 0, 500);
		TH1F* h_mZv2 = new TH1F("h_mZv2", "Z-veto (e+e- & m)", 50, 0, 500);
		TH1F* h_mZv3 = new TH1F("h_mZv3", "Z-veto (m+m- & e)", 50, 0, 500);
		TH1F* h_mZv4 = new TH1F("h_mZv4", "Z-veto (m+m- & m)", 50, 0, 500);	

		TH1F* h_mH1 = new TH1F("h_mH1", "mll (e+e- & e)", 50, 0, 500);
		TH1F* h_mH2 = new TH1F("h_mH2", "mll (e+e- & m)", 50, 0, 500);
		TH1F* h_mH3 = new TH1F("h_mH3", "mll (m+m- & e)", 50, 0, 500);
		TH1F* h_mH4 = new TH1F("h_mH4", "mll (m+m- & m)", 50, 0, 500);
		TH1F* h_mHv1 = new TH1F("h_mHv1", "mll in Z-veto (e+e- & e)", 50, 0, 500);
		TH1F* h_mHv2 = new TH1F("h_mHv2", "mll in Z-veto (e+e- & m)", 50, 0, 500);
		TH1F* h_mHv3 = new TH1F("h_mHv3", "mll in Z-veto (m+m- & e)", 50, 0, 500);
		TH1F* h_mHv4 = new TH1F("h_mHv4", "mll in Z-veto (m+m- & m)", 50, 0, 500);	

		TH1F* h_pt1_1 = new TH1F("h_pt1_1", "pt1 (e+e- & e)", 50, 0, 500);
		TH1F* h_pt1_2 = new TH1F("h_pt1_2", "pt1 (e+e- & m)", 50, 0, 500);
		TH1F* h_pt1_3 = new TH1F("h_pt1_3", "pt1 (m+m- & e)", 50, 0, 500);
		TH1F* h_pt1_4 = new TH1F("h_pt1_4", "pt1 (m+m- & m)", 50, 0, 500);
		TH1F* h_pt1_v1 = new TH1F("h_pt1_v1", "pt1 in Z-veto (e+e- & e)", 50, 0, 500);
		TH1F* h_pt1_v2 = new TH1F("h_pt1_v2", "pt1 in Z-veto (e+e- & m)", 50, 0, 500);
		TH1F* h_pt1_v3 = new TH1F("h_pt1_v3", "pt1 in Z-veto (m+m- & e)", 50, 0, 500);
		TH1F* h_pt1_v4 = new TH1F("h_pt1_v4", "pt1 in Z-veto (m+m- & m)", 50, 0, 500);
	
		TH1F* h_pt2_1 = new TH1F("h_pt2_1", "pt2 (e+e- & e)", 50, 0, 500);
		TH1F* h_pt2_2 = new TH1F("h_pt2_2", "pt2 (e+e- & m)", 50, 0, 500);
		TH1F* h_pt2_3 = new TH1F("h_pt2_3", "pt2 (m+m- & e)", 50, 0, 500);
		TH1F* h_pt2_4 = new TH1F("h_pt2_4", "pt2 (m+m- & m)", 50, 0, 500);
		TH1F* h_pt2_v1 = new TH1F("h_pt2_v1", "pt2 in Z-veto (e+e- & e)", 50, 0, 500);
		TH1F* h_pt2_v2 = new TH1F("h_pt2_v2", "pt2 in Z-veto (e+e- & m)", 50, 0, 500);
		TH1F* h_pt2_v3 = new TH1F("h_pt2_v3", "pt2 in Z-veto (m+m- & e)", 50, 0, 500);
		TH1F* h_pt2_v4 = new TH1F("h_pt2_v4", "pt2 in Z-veto (m+m- & m)", 50, 0, 500);		

	
		TH1F* h_pt3_1 = new TH1F("h_pt3_1", "pt3 (e+e- & e)", 50, 0, 500);
		TH1F* h_pt3_2 = new TH1F("h_pt3_2", "pt3 (e+e- & m)", 50, 0, 500);
		TH1F* h_pt3_3 = new TH1F("h_pt3_3", "pt3 (m+m- & e)", 50, 0, 500);
		TH1F* h_pt3_4 = new TH1F("h_pt3_4", "pt3 (m+m- & m)", 50, 0, 500);
		TH1F* h_pt3_v1 = new TH1F("h_pt3_v1", "pt3 in Z-veto (e+e- & e)", 50, 0, 500);
		TH1F* h_pt3_v2 = new TH1F("h_pt3_v2", "pt3 in Z-veto (e+e- & m)", 50, 0, 500);
		TH1F* h_pt3_v3 = new TH1F("h_pt3_v3", "pt3 in Z-veto (m+m- & e)", 50, 0, 500);
		TH1F* h_pt3_v4 = new TH1F("h_pt3_v4", "pt3 in Z-veto (m+m- & m)", 50, 0, 500);	

		TH1F* h_met1 = new TH1F("h_met1", "met (e+e- & e)", 50, 0, 500);
		TH1F* h_met2 = new TH1F("h_met2", "met (e+e- & m)", 50, 0, 500);
		TH1F* h_met3 = new TH1F("h_met3", "met (m+m- & e)", 50, 0, 500);
		TH1F* h_met4 = new TH1F("h_met4", "met (m+m- & m)", 50, 0, 500);
		TH1F* h_metv1 = new TH1F("h_metv1", "met in Z-veto (e+e- & e)", 50, 0, 500);
		TH1F* h_metv2 = new TH1F("h_metv2", "met in Z-veto (e+e- & m)", 50, 0, 500);
		TH1F* h_metv3 = new TH1F("h_metv3", "met in Z-veto (m+m- & e)", 50, 0, 500);
		TH1F* h_metv4 = new TH1F("h_metv4", "met in Z-veto (m+m- & m)", 50, 0, 500);	
		
		TH1F* h_MT1 = new TH1F("h_MT1", "MT (e+e- & e)", 50, 0, 500);
		TH1F* h_MT2 = new TH1F("h_MT2", "MT (e+e- & m)", 50, 0, 500);
		TH1F* h_MT3 = new TH1F("h_MT3", "MT (m+m- & e)", 50, 0, 500);
		TH1F* h_MT4 = new TH1F("h_MT4", "MT (m+m- & m)", 50, 0, 500);
		TH1F* h_MTv1 = new TH1F("h_MTv1", "MT in Z-veto (e+e- & e)", 50, 0, 500);
		TH1F* h_MTv2 = new TH1F("h_MTv2", "MT in Z-veto (e+e- & m)", 50, 0, 500);
		TH1F* h_MTv3 = new TH1F("h_MTv3", "MT in Z-veto (m+m- & e)", 50, 0, 500);
		TH1F* h_MTv4 = new TH1F("h_MTv4", "MT in Z-veto (m+m- & m)", 50, 0, 500);			
		for (int i =0; i < tree->GetEntries(); i++){
			tree->GetEntry(i);			
			float *lep_pt, *tau_pt;
			const char *cat_name = numberToCat(cat);
			int Nlep = cat_lepCount(cat_name,'e','m'); 
			int Ntau = strlen(cat_name)-Nlep;  
			
			if (cat <= 21) continue;
			
			float mll_1, mll_2;
			if ((LepV(1)+LepV(2)).Pt() > (LepV(3)+LepV(4)).Pt()){
				mll_1 = mll;
				mll_2 = mll2;	
			}
			else{
				mll_1 = mll2;
				mll_2 = mll;
			}
			
			if(selection == "test"){//My tests
				TLorentzVector *Zcands = ZCandMaker(cat_name, LepV(1), LepV(2), LepV(3), LepV(4), 20);	
				TLorentzVector L1 = Zcands[0], L2 = Zcands[1], L3 = Zcands[2], L4 = Zcands[3];
				if (cat_name == "eee" and (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20)){ 
					h_mZ1->Fill((L1+L2).M());
					h_mH1->Fill(mll_1);
					h_pt1_1->Fill(L1.Pt());
					h_pt2_1->Fill(L2.Pt());
					h_pt3_1->Fill(L3.Pt());
					h_met1->Fill(met);
					h_MT1->Fill(met+L3.Mt());
				}
				else if (cat_name == "eme" and (abs((LepV(1)+LepV(3)).M()-mZ) < 20)){ 
					h_mZ2->Fill((L1+L2).M());
					h_mH2->Fill(mll_1);
					h_pt1_2->Fill(L1.Pt());
					h_pt2_2->Fill(L2.Pt());
					h_pt3_2->Fill(L3.Pt());
					h_met2->Fill(met);
					h_MT2->Fill(met+L3.Mt());
				}
				else if (cat_name == "emm" and (abs((LepV(2)+LepV(3)).M()-mZ) < 20)){ 
					h_mZ3->Fill((L1+L2).M());
					h_mH3->Fill(mll_1);
					h_pt1_3->Fill(L1.Pt());
					h_pt2_3->Fill(L2.Pt());
					h_pt3_3->Fill(L3.Pt());
					h_met3->Fill(met);
					h_MT3->Fill(met+L3.Mt());
				}
				else if( cat_name == "mmm" and (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20)){ 
					h_mZ4->Fill((L1+L2).M());
					h_mH4->Fill(mll_1);
					h_pt1_4->Fill(L1.Pt());
					h_pt2_4->Fill(L2.Pt());
					h_pt3_4->Fill(L3.Pt());
					h_met4->Fill(met);
					h_MT4->Fill(met+L3.Mt());
				}

				TLorentzVector *ZcandsV = ZVetoMaker(cat_name, LepV(1), LepV(2), LepV(3), LepV(4), 20);	
				L1 = ZcandsV[0], L2 = ZcandsV[1], L3 = ZcandsV[2], L4 = ZcandsV[3];
				
				if (cat_name == "eee" and (abs((LepV(1)+LepV(3)).M()-mZ) > 20 and abs((LepV(2)+LepV(3)).M()-mZ) > 20)){ 
					h_mZv1->Fill((L1+L2).M());
					h_mHv1->Fill(mll_1);
					h_pt1_v1->Fill(L1.Pt());
					h_pt2_v1->Fill(L2.Pt());
					h_pt3_v1->Fill(L3.Pt());
					h_metv1->Fill(met);
					h_MTv1->Fill(met+L3.Mt());
				}
				else if (cat_name == "eme" and (abs((LepV(1)+LepV(3)).M()-mZ) > 20)){  
					h_mZv2->Fill((L1+L2).M());
					h_mHv2->Fill(mll_1);
					h_pt1_v2->Fill(L1.Pt());
					h_pt2_v2->Fill(L2.Pt());
					h_pt3_v2->Fill(L3.Pt());
					h_metv2->Fill(met);
					h_MTv2->Fill(met+L3.Mt());
				}
				else if (cat_name == "emm" and (abs((LepV(2)+LepV(3)).M()-mZ) > 20)){ 
					h_mZv3->Fill((L1+L2).M());
					h_mHv3->Fill(mll_1);
					h_pt1_v3->Fill(L1.Pt());
					h_pt2_v3->Fill(L2.Pt());
					h_pt3_v3->Fill(L3.Pt());
					h_metv3->Fill(met);
					h_MTv3->Fill(met+L3.Mt());
				}
				else if( cat_name == "mmm" and (abs((LepV(1)+LepV(3)).M()-mZ) > 20 and abs((LepV(2)+LepV(3)).M()-mZ) > 20)){ 
					h_mZv4->Fill((L1+L2).M());
					h_mHv4->Fill(mll_1);
					h_pt1_v4->Fill(L1.Pt());
					h_pt2_v4->Fill(L2.Pt());
					h_pt3_v4->Fill(L3.Pt());
					h_metv4->Fill(met);
					h_MTv4->Fill(met+L3.Mt());
				}
			}
			
		}//evt loop

		h_mZ1->Scale(weight);
		h_mZ2->Scale(weight);
		h_mZ3->Scale(weight);
		h_mZ4->Scale(weight);
		h_mZv1->Scale(weight);
		h_mZv2->Scale(weight);
		h_mZv3->Scale(weight);
		h_mZv4->Scale(weight);
		
		h_mH1->Scale(weight);
		h_mH2->Scale(weight);
		h_mH3->Scale(weight);
		h_mH4->Scale(weight);
		h_mHv1->Scale(weight);
		h_mHv2->Scale(weight);
		h_mHv3->Scale(weight);
		h_mHv4->Scale(weight);
		
		h_met1->Scale(weight);
		h_met2->Scale(weight);
		h_met3->Scale(weight);
		h_met4->Scale(weight);
		h_metv1->Scale(weight);
		h_metv2->Scale(weight);
		h_metv3->Scale(weight);
		h_metv4->Scale(weight);

		h_MT1->Scale(weight);
		h_MT2->Scale(weight);
		h_MT3->Scale(weight);
		h_MT4->Scale(weight);
		h_MTv1->Scale(weight);
		h_MTv2->Scale(weight);
		h_MTv3->Scale(weight);
		h_MTv4->Scale(weight);

		h_pt1_1->Scale(weight);
		h_pt2_1->Scale(weight);
		h_pt3_1->Scale(weight);
		h_pt1_v1->Scale(weight);
		h_pt2_v1->Scale(weight);
		h_pt3_v1->Scale(weight);
	
		h_pt1_2->Scale(weight);
		h_pt2_2->Scale(weight);
		h_pt3_2->Scale(weight);
		h_pt1_v2->Scale(weight);
		h_pt2_v2->Scale(weight);
		h_pt3_v2->Scale(weight);

		h_pt1_3->Scale(weight);
		h_pt2_3->Scale(weight);
		h_pt3_3->Scale(weight);
		h_pt1_v3->Scale(weight);
		h_pt2_v3->Scale(weight);
		h_pt3_v3->Scale(weight);

		h_pt1_4->Scale(weight);
		h_pt2_4->Scale(weight);
		h_pt3_4->Scale(weight);
		h_pt1_v4->Scale(weight);
		h_pt2_v4->Scale(weight);
		h_pt3_v4->Scale(weight);

		hnevts->Write();	
			
		h_mZ1->Write();
		h_mZ2->Write();
		h_mZ3->Write();
		h_mZ4->Write();
		h_mZv1->Write();
		h_mZv2->Write();
		h_mZv3->Write();
		h_mZv4->Write();
		
		h_mH1->Write();
		h_mH2->Write();
		h_mH3->Write();
		h_mH4->Write();
		h_mHv1->Write();
		h_mHv2->Write();
		h_mHv3->Write();
		h_mHv4->Write();
		
		h_met1->Write();
		h_met2->Write();
		h_met3->Write();
		h_met4->Write();
		h_metv1->Write();
		h_metv2->Write();
		h_metv3->Write();
		h_metv4->Write();

		h_MT1->Write();
		h_MT2->Write();
		h_MT3->Write();
		h_MT4->Write();
		h_MTv1->Write();
		h_MTv2->Write();
		h_MTv3->Write();
		h_MTv4->Write();

		h_pt1_1->Write();
		h_pt2_1->Write();
		h_pt3_1->Write();
		h_pt1_v1->Write();
		h_pt2_v1->Write();
		h_pt3_v1->Write();
	
		h_pt1_2->Write();
		h_pt2_2->Write();
		h_pt3_2->Write();
		h_pt1_v2->Write();
		h_pt2_v2->Write();
		h_pt3_v2->Write();

		h_pt1_3->Write();
		h_pt2_3->Write();
		h_pt3_3->Write();
		h_pt1_v3->Write();
		h_pt2_v3->Write();
		h_pt3_v3->Write();

		h_pt1_4->Write();
		h_pt2_4->Write();
		h_pt3_4->Write();
		h_pt1_v4->Write();
		h_pt2_v4->Write();
		h_pt3_v4->Write();
		//cout<< j <<"\t"<< oname <<endl;
		printf("%s %f\n", oname, XSec(filename[j])*lumi_2018/hnevts->Integral() );
		delete tree;
	}
	gSystem->FreeDirectory(dirp);
}

