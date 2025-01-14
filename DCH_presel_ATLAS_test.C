//To apply various kinematics selections right after online analysis.
#include "TMath.h"
#include <cmath>
#include <vector>
#include "TH1D.h"
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
	else if(fname.find("WZ_") < fname.length()) return 0;//27.6;
	else if(fname.find("ZHToMuMu") < fname.length()) return 0.7891*0.000218;
	else if(fname.find("ZHToTauTau") < fname.length()) return 0.7891*0.0627;
	else if(fname.find("ZZTo2L2Nu") < fname.length()) return 1.325;
	else if(fname.find("ZZTo2Q2L") < fname.length()) return 3.22;
	else if(fname.find("ZZTo4L") < fname.length()) return 1.325;
	else if(fname.find("ZZZ_") < fname.length()) return 0.01398;
	else if(fname.find("GluGluZH_") < fname.length()) return 0.0616;
	else if(fname.find("DYJetsToLLM10to50") < fname.length()) return 18610;
	else if(fname.find("DYJetsToLLM50") < fname.length()) return 6077.22;
	else if(fname.find("ST_s-channel_") < fname.length()) return 3.74;
	else if(fname.find("ST_t-channel_antitop_") < fname.length()) return 69.09;
	else if(fname.find("ST_t-channel_top_") < fname.length()) return 115.3;
	else if(fname.find("ST_tW_antitop_") < fname.length()) return 35.85;
	else if(fname.find("ST_tW_top_") < fname.length()) return 35.85;
	else if(fname.find("HppM") < fname.length()) return 0.001;//Signal
	else if(fname.find("EGamma") < fname.length()) return 1;//Data
	else if(fname.find("Muon") < fname.length()) return 1;//Data
	else if(fname.find("Tau") < fname.length()) return 1;//Data
	else if(fname.find("Single") < fname.length()) return 1;//Data
	else{
		std::cout<<"DON'T KNOW X-SEC FOR FILE "<<fname<<endl;
		return 0;
	}
}

void DCH_presel_ATLAS_test(const char* ext = "2018.root"){
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
		//cout<<filename[j]<<endl;
		std::string fname = filename[j];
		//if (fname.find("_2018.") > fname.length()) continue;
		//if (fname.find("DY") > fname.length()) continue;
		//if (XSec(filename[j])!=1) continue; 
	
		TH1D* hnevts;
		double xs_weight = 1.0;
		if(XSec(filename[j])!=1){
			hnevts = (TH1D*)ifile->Get("hNWEvts");
			if (!hnevts) hnevts = (TH1D*)ifile->Get("hNEvts");
			xs_weight = lumi_2018*XSec(filename[j])/hnevts->Integral();
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
		//float xmin = 0, xmax = 3000; int binw = 100; int nbins = (xmax-xmin)/binw; 
		float xmin = 300, xmax = 2000; int nbins = 1; 
		int nbins3L = 4; float binEdges3L[5] = {299, 380, 530, 680, 1150};
						
		TH1D* h_cat = new TH1D("h_cat", "cat", 40,0,40);
		TH1D* h_gencat = new TH1D("h_gencat", "gen cat", 40,0,40);
		TH1D* h_Xmass_0t = new TH1D("h_Xmass_0t", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_1t = new TH1D("h_Xmass_1t", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_2t = new TH1D("h_Xmass_2t", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_34t = new TH1D("h_Xmass_34t", "mDCH1", nbins, xmin, xmax);
		TH1D* h_Xmass_3lep = new TH1D("h_Xmass_3lep", "mDCH1", nbins3L, binEdges3L);
		for (int i =0; i < tree->GetEntries(); i++){
			tree->GetEntry(i);			
			const char *cat_name = numberToCat(cat);
			int Nlep = cat_lepCount(cat_name,'e','m'); 
			int Ntau = strlen(cat_name)-Nlep;
			if (cat > 39) continue;//not processing 2-lep channels
			//if (Ntau != 0) continue;
			//if (Ntau != 1) continue;
			//if (Ntau != 2) continue;
			//if (Ntau > 3) continue;
			//if (Ntau != 4) continue;
						
			double evtwt_nom = brWeight*Generator_weight;
			if (XSec(filename[j])!=1){
				//evtwt_nom *= weight*L1PreFiringWeight_Nom*weightPUtruejson;
				if(strlen(cat_name)<3){
					evtwt_nom *= IDSF_1*IDSF_2*ISOSF_1*ISOSF_2*weightPUtruejson*L1PreFiringWeight_Nom;
					if (isTrig_1 >=1)
						evtwt_nom *= TrigSF_1;
					else if (isTrig_1 == -1)
						evtwt_nom *= TrigSF_2;
					//cout<<evtwt_nom<<endl;
				}
				else if (strlen(cat_name)==3)
					evtwt_nom *= IDSF_1*IDSF_2*IDSF_3*ISOSF_1*ISOSF_2*ISOSF_3*weightPUtruejson*L1PreFiringWeight_Nom;
				else evtwt_nom *= IDSF_1*IDSF_2*IDSF_3*IDSF_4*ISOSF_1*ISOSF_2*ISOSF_3*ISOSF_4*weightPUtruejson*L1PreFiringWeight_Nom;
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
			}

			bool foundDup = false;
			std::vector<Lepton> leptons = {
				Lepton(pt_1, eta_1, phi_1, m_1, q_1, d0_1, dZ_1, iso_1),
				Lepton(pt_2, eta_2, phi_2, m_2, q_2, d0_2, dZ_2, iso_2),
				Lepton(pt_3, eta_3, phi_3, m_3, q_3, d0_3, dZ_3, iso_3),
				Lepton(pt_4, eta_4, phi_4, m_4, q_4, d0_4, dZ_4, iso_4),
			};
			//cout<<cat_name<<"\t"<<leptons[0].d0<<"\t"<<"\t"<<leptons[1].d0<<"\t"<<leptons[2].d0<<"\t"<<leptons[3].d0<<endl;
			for (int w = 0; w < strlen(cat_name) && !foundDup; ++w) {
				for (int x = w + 1; x < strlen(cat_name); ++x) {
					if (isDuplicate(leptons[w], leptons[x])){
						foundDup = true;
						break;
					}
				}
			}
			if (foundDup == true ) continue;
			// Sort the lepton variables in descending order based on pt
			std::sort(leptons.begin(), leptons.end(), [](const Lepton& a, const Lepton& b) {
				return a.pt > b.pt;
			});
			
			std::vector<double> mZ, mZv, mH; double llPt=0, tmpPt=0;
			for(int m = 1; m <= strlen(cat_name); ++m){
				for(int n = m+1; n <= strlen(cat_name); ++n){
					string pair_name = pairFunc(m,n,cat_name,20);
					//the vector elements are inv massses of highest pt pairs because we sotred the lepton vector by pt.
					if(pair_name=="Zwindow") mZ.push_back((LepV(m)+LepV(n)).M());
					else if(pair_name=="Zv") mZv.push_back((LepV(m)+LepV(n)).M());
					else if(pair_name=="DCH"){
						mH.push_back((LepV(m)+LepV(n)).M());
						tmpPt = (LepV(m)+LepV(n)).Pt();
						if (tmpPt>llPt) llPt = tmpPt;
					}
					//else if(pair_name=="found nothing") cout<<"found nothing"<<endl;
					else continue;
				}
			}
//###################### ATLAS #########################
			//if (Ntau != 0) continue;
			if(selection == "APre"){//ATLAS Signal region
				if (mH[0] < 300)continue;
				//if ( cat <= 21 ){
				if (cat<= 21 and Ntau ==0){
					if (mZ.size() > 0)continue;
					if ( (mH[0]+mH[1])/2 < 300 ) continue;
					h_Xmass_0t->Fill(mH[0],evtwt_nom);
				}
				//else if ( cat >= 22 and Ntau !=3){
				//else if ( cat >= 22 and Ntau ==0){
				else if ((cat<=21 and Ntau ==1) or (cat>21 and Ntau ==0)){
					if (mZ.size()>0)continue;
					if ( llPt < 300)continue;
					h_Xmass_3lep->Fill(mH[0],evtwt_nom);

				}
				
				//=================test============
				else if (cat<= 21 and Ntau == 1){
					if (mZ.size() > 0)continue;
					if ( (mH[0]+mH[1])/2 < 300 ) continue;
					h_Xmass_1t->Fill(mH[0],evtwt_nom);
				}
				else if (cat<= 21 and Ntau >= 2 and Ntau !=4){
					if (mZ.size() > 0)continue;
					if ( (mH[0]+mH[1])/2 < 300 ) continue;
					h_Xmass_2t->Fill(mH[0],evtwt_nom);

				}//================test================
					
			}
			/*else if(selection == "CR"){//Atlas CR for Di-bosons
				if ( cat <= 21 ){
					if (mH[0] >= 200 or mH[0] < 100)continue;
					h_Xmass_0t->Fill(mH[0]);
					h_Xmass_1t->Fill(mH[0]);
					h_Xmass_2t->Fill(mH[0]);
				}
				else if ( cat >= 22){
					if (mH[0] < 300)continue;
					if (abs((LepV(1)+LepV(3)).M()-mZ) > 20 and abs((LepV(2)+LepV(3)).M()-mZ) > 20)continue;
					h_Xmass_3lep->Fill(mH[0]);
				}
			}
			else if(selection == "VR"){//Atlas VR
				if ( cat <= 21 ){
					if (mH[0] >= 300 or mH[0] < 200)continue;
					h_Xmass_0t->Fill(mH[0]);
					h_Xmass_1t->Fill(mH[0]);
					h_Xmass_2t->Fill(mH[0]);
				}
				else if ( cat >= 22){
					if (mH[0] >= 300 or mH[0] < 100)continue;
					if (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20)continue;
					h_Xmass_3lep->Fill(mH[0]);
				}
			}*/		
		}//evt loop
		h_Xmass_0t->Scale(xs_weight);
		h_Xmass_1t->Scale(xs_weight);
		h_Xmass_2t->Scale(xs_weight);
		h_Xmass_34t->Scale(xs_weight);
		h_Xmass_3lep->Scale(xs_weight);
		
		hnevts->Write();		
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

