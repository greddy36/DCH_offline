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
#include "include/Xsections.C"

// Histogram creation utility to avoid code duplication
void createHistograms(std::vector<TH1D*>& histograms, const std::string& prefix, const std::string& label, int bins, double low, double high) {
	int nCh = 17;
    for (int i = 0; i <= nCh; i++) {
        histograms.push_back(new TH1D(Form("%s%d", prefix.c_str(), i), Form("%s %d", label.c_str(), i), bins, low, high));
    }
}

void scaleAndWriteHistograms(std::vector<TH1D*>& histograms, double xs_weight) {
    int end = histograms.size(); 
    for (int i = 1; i < end; ++i) {
        histograms[i]->Scale(xs_weight);
        histograms[i]->Write();
    }
}

void DCH_test_nopair(const char* ext = "root"){
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

	double mDCH = 500.0, mZ = 91.2, lumi_2016 = 35900, lumi_2017 = 41500, lumi_2018 = 58900.0; //139000;
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		cout<<filename[j]<<endl;
		TFile *ifile = new TFile(filename[j],"READ");
		std::string fname = filename[j];
		if (fname.find("_2018.") > fname.length()) continue;
		if (fname.find("TTTo") > fname.length()) continue;
		//if (fname.find("EGam") < fname.length()) continue;
		if (XSec(filename[j])==1) continue; 

		
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
		else if (selection =="test") o_name = "hist_test_nopair";
		else cout<< "SELECTION NOT DEFINED!!!"<<endl;
		char *oname = gSystem->ConcatFileName(o_name, filename[j]);
		TFile* ofile = new TFile(oname, "RECREATE"); 
		TTree *tree = (TTree*)ifile->Get("Events");
		MyBranch(tree);
		
		// Compact histogram creation
        std::vector<TH1D*> h_mZ, h_mZv, h_mH, h_mHv, h_met, h_metv, h_pt1, h_pt2, h_pt3, h_pt4, h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1, h_eta2, h_eta3, h_eta4, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1, h_phi2, h_phi3, h_phi4, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMt, h_WMtv;
        createHistograms(h_mZ, "h_mZ", "mZ", 25, 0, 300);
        createHistograms(h_mZv, "h_mZv", "Z-veto", 25, 0, 300);
        createHistograms(h_mH, "h_mH", "mll", 25, 0, 300);
        createHistograms(h_mHv, "h_mHv", "mll in Z-veto", 25, 0, 300);
        createHistograms(h_met, "h_met", "MET", 25, 0, 300);
        createHistograms(h_metv, "h_metv", "MET in Z-veto", 25, 0, 300);
        createHistograms(h_pt1, "h_pt1", "pT1", 25, 0, 300);
        createHistograms(h_pt1v, "h_pt1v", "pT1 in Z-veto", 25, 0, 300);
        createHistograms(h_eta1, "h_eta1", "Eta1", 25, -3, 3);
        createHistograms(h_eta1v, "h_eta1v", "Eta1 in Z-veto", 25, -3, 3);
        createHistograms(h_phi1, "h_phi1", "Phi1", 25, -3.5, 3.5);
        createHistograms(h_phi1v, "h_phi1v", "Phi1 in Z-veto", 25, -3.5, 3.5);
        createHistograms(h_pt2, "h_pt2", "pT2", 25, 0, 300);
        createHistograms(h_pt2v, "h_pt2v", "pT2 in Z-veto", 25, 0, 300);
        createHistograms(h_eta2, "h_eta2", "Eta2", 25, -3, 3);
        createHistograms(h_eta2v, "h_eta2v", "Eta2 in Z-veto", 25, -3, 3);
        createHistograms(h_phi2, "h_phi2", "Phi2", 25, -3.5, 3.5);
        createHistograms(h_phi2v, "h_phi2v", "Phi2 in Z-veto", 25, -3.5, 3.5);
        createHistograms(h_pt3, "h_pt3", "pT3", 25, 0, 300);
        createHistograms(h_pt3v, "h_pt3v", "pT3 in Z-veto", 25, 0, 300);
        createHistograms(h_eta3, "h_eta3", "Eta3", 25, -3, 3);
        createHistograms(h_eta3v, "h_eta3v", "Eta3 in Z-veto", 25, -3, 3);
        createHistograms(h_phi3, "h_phi3", "Phi3", 25, -3.5, 3.5);
        createHistograms(h_phi3v, "h_phi3v", "Phi3 in Z-veto", 25, -3.5, 3.5);
        createHistograms(h_pt4, "h_pt4", "pT4", 25, 0, 300);
        createHistograms(h_pt4v, "h_pt4v", "pT4 in Z-veto", 25, 0, 300);
        createHistograms(h_eta4, "h_eta4", "Eta4", 25, -3, 3);
        createHistograms(h_eta4v, "h_eta4v", "Eta4 in Z-veto", 25, -3, 3);
        createHistograms(h_phi4, "h_phi4", "Phi4", 25, -3.5, 3.5);
        createHistograms(h_phi4v, "h_phi4v", "Phi4 in Z-veto", 25, -3.5, 3.5);
        createHistograms(h_dxy1, "h_dxy1", "dxy1", 25, -0.045, 0.045);
        createHistograms(h_dxy2, "h_dxy2", "dxy2", 25, -0.045, 0.045);
        createHistograms(h_dxy3, "h_dxy3", "dxy3", 25, -0.045, 0.045);
        createHistograms(h_dxy4, "h_dxy4", "dxy4", 25, -0.045, 0.045);
        createHistograms(h_dZ1, "h_dZ1", "dZ1", 25, -0.1, 0.1);
        createHistograms(h_dZ2, "h_dZ2", "dZ2", 25, -0.1, 0.1);
        createHistograms(h_dZ3, "h_dZ3", "dZ3", 25, -0.1, 0.1);
        createHistograms(h_dZ4, "h_dZ4", "dZ4", 25, -0.1, 0.1);
        createHistograms(h_iso1, "h_iso1", "iso1 in Z-veto", 25, 0, 0.25);
        createHistograms(h_iso2, "h_iso2", "iso2 in Z-veto", 25, 0, 0.25);
        createHistograms(h_iso3, "h_iso3", "iso3 in Z-veto", 25, 0, 0.25);
        createHistograms(h_iso4, "h_iso4", "iso4 in Z-veto", 25, 0, 0.25);
        createHistograms(h_dxy1v, "h_dxy1v", "dxy1 in Z-veto", 25, -0.045, 0.045);
        createHistograms(h_dxy2v, "h_dxy2v", "dxy2 in Z-veto", 25, -0.045, 0.045);
        createHistograms(h_dxy3v, "h_dxy3v", "dxy3 in Z-veto", 25, -0.045, 0.045);
        createHistograms(h_dxy4v, "h_dxy4v", "dxy4 in Z-veto", 25, -0.045, 0.045);
        createHistograms(h_dZ1v, "h_dZ1v", "dZ1 in Z-veto", 25, -0.1, 0.1);
        createHistograms(h_dZ2v, "h_dZ2v", "dZ2 in Z-veto", 25, -0.1, 0.1);
        createHistograms(h_dZ3v, "h_dZ3v", "dZ3 in Z-veto", 25, -0.1, 0.1);
        createHistograms(h_dZ4v, "h_dZ4v", "dZ4 in Z-veto", 25, -0.1, 0.1);
        createHistograms(h_iso1v, "h_iso1v", "iso1 in Z-veto", 25, 0, 0.25);
        createHistograms(h_iso2v, "h_iso2v", "iso2 in Z-veto", 25, 0, 0.25);
        createHistograms(h_iso3v, "h_iso3v", "iso3 in Z-veto", 25, 0, 0.25);
        createHistograms(h_iso4v, "h_iso4v", "iso4 in Z-veto", 25, 0, 0.25);
        createHistograms(h_12dR, "h_12dR", "dR_{1,2}", 25, -3.5,3.5);
        createHistograms(h_13dR, "h_13dR", "dR_{1,3}", 25, -3.5,3.5);
        createHistograms(h_14dR, "h_14dR", "dR_{1,4}", 25, -3.5,3.5);
        createHistograms(h_23dR, "h_23dR", "dR_{2,3}", 25, -3.5,3.5);
        createHistograms(h_24dR, "h_24dR", "dR_{2,4}", 25, -3.5,3.5);
        createHistograms(h_34dR, "h_34dR", "dR_{3,4}", 25, -3.5,3.5);
        createHistograms(h_12dRv, "h_12dRv", "dR_{1,2} in Z-veto", 25, -3.5,3.5);
        createHistograms(h_13dRv, "h_13dRv", "dR_{1,3} in Z-veto", 25, -3.5,3.5);
        createHistograms(h_14dRv, "h_14dRv", "dR_{1,4} in Z-veto", 25, -3.5,3.5);
        createHistograms(h_23dRv, "h_23dRv", "dR_{2,3} in Z-veto", 25, -3.5,3.5);
        createHistograms(h_24dRv, "h_24dRv", "dR_{2,4} in Z-veto", 25, -3.5,3.5);
        createHistograms(h_34dRv, "h_34dRv", "dR_{3,4} in Z-veto", 25, -3.5,3.5);
        createHistograms(h_WMt, "h_WMt", "WMt in Z-window", 25, 0,1000);
        createHistograms(h_WMtv, "h_WMtv", "WMt in Z-veto", 25, 0,1000);
        
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
			//else if (cat <= 39 and cat > 21 and abs(q_1+q_2+q_3) == 3) continue; 
			//if (Ntau != 0) continue;
			//if (Nlep == 0) continue;
			//if (cat_name != "mmt") continue;

			//cout<<"BEFORE"<<"\t"<<q_1<<"\t"<<q_2<<"\t"<<q_3<<"\t"<<q_4<<"\t"<<cat_name<<endl;			
			// (strlen(cat_name) == 3 and (abs(q_1+q_2+q_3)!=1 or abs(q_1) !=1 or abs(q_2) != 1 or abs(q_3)!=1))continue;
			// (strlen(cat_name) == 4 and (abs(q_1+q_2+q_3+q_4)!=0 or abs(q_1) !=1 or abs(q_2) != 1 or abs(q_3)!=1 or abs(q_4)!=1))continue;
			
			double evtwt_nom = brWeight*Generator_weight;
			if (fname.find("_2018.") < fname.length()){//HEM veto
				if (XSec(filename[j])==1 and run >= 319077 and applyHEMveto(cat_string) == "yes") continue;
				if (XSec(filename[j])!=1 and applyHEMveto(cat_string) == "yes") evtwt_nom *= 0.35;
			}
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
			
			 			
			//cout<<evtwt_nom<<endl;	
			
			if(selection == "test"){//My tests
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
				// Sort the lepton variables in descending order based on pt
				/*std::sort(leptons.begin(), leptons.end(), [](const Lepton& a, const Lepton& b) {
					return a.pt > b.pt;
				});*/
				/*std::vector<int> Zcands = ZCandMaker(cat_name, 20);	
				TLorentzVector L1 = LepV(Zcands[0]), L2 = LepV(Zcands[1]), L3 = LepV(Zcands[2]), L4 = LepV(Zcands[3]);
				int Q[] = {-99, -99, -99, -99};
				for(int iq = 0; iq <= 3; iq++){
					if (Zcands[iq] == 1) Q[iq] = q_1;
					else if (Zcands[iq] == 2) Q[iq] = q_2;
					else if (Zcands[iq] == 3) Q[iq] = q_3;
					else if (Zcands[iq] == 4) Q[iq] = q_4;
				}
				int q1=Q[0],q2=Q[1],q3=Q[2],q4=Q[3];
				double mll_1=-99, mll_2=-99, mllt_2=-99;
				if (q1==q3 and (L1+L3).Pt() >= (L2+L4).Pt()){
					mll_1 = (L1+L3).M();
					mllt_2 = (L2+L4).Mt();
				}
				else if (q1==q3 and (L2+L4).Pt() >= (L1+L3).Pt()){
					mll_1 = (L2+L4).M();
				}
				else if (q1==q4 and (L1+L4).Pt() >= (L2+L3).Pt()){
					mll_1 = (L1+L4).M();
					mllt_2 = (L2+L3).Mt();
				}
				else if (q1==q4 and (L2+L3).Pt() >= (L1+L4).Pt()){
					mll_1 = (L2+L3).M();
					mllt_2 = (L1+L4).Mt();
					mllt_2 = (L1+L3).Mt();
				}*/
				if( cat_string =="emt" ){ 
					h_WMt[8]->Fill(0.0, evtwt_nom);
					h_mZ[8]->Fill(0.0, evtwt_nom);
					h_mH[8]->Fill(0.0, evtwt_nom);
					h_met[8]->Fill(met, evtwt_nom);
					h_pt1[8]->Fill(leptons[0].pt, evtwt_nom);
					h_pt2[8]->Fill(leptons[1].pt, evtwt_nom);
					h_pt3[8]->Fill(leptons[2].pt, evtwt_nom);
					h_pt4[8]->Fill(leptons[3].pt, evtwt_nom);
					h_eta1[8]->Fill(leptons[0].eta, evtwt_nom);
					h_eta2[8]->Fill(leptons[1].eta, evtwt_nom);
					h_eta3[8]->Fill(leptons[2].eta, evtwt_nom);
					h_eta4[8]->Fill(leptons[3].eta, evtwt_nom);
					h_phi1[8]->Fill(leptons[0].phi, evtwt_nom);
					h_phi2[8]->Fill(leptons[1].phi, evtwt_nom);
					h_phi3[8]->Fill(leptons[2].phi, evtwt_nom);
					h_phi4[8]->Fill(leptons[3].phi, evtwt_nom);
					h_dxy1[8]->Fill(leptons[0].d0, evtwt_nom);
					h_dxy2[8]->Fill(leptons[1].d0, evtwt_nom);
					h_dxy3[8]->Fill(leptons[2].d0, evtwt_nom);
					h_dxy4[8]->Fill(leptons[3].d0, evtwt_nom);
					h_dZ1[8]->Fill(leptons[0].dZ, evtwt_nom);
					h_dZ2[8]->Fill(leptons[1].dZ, evtwt_nom);
					h_dZ3[8]->Fill(leptons[2].dZ, evtwt_nom);
					h_dZ4[8]->Fill(leptons[3].dZ, evtwt_nom);
					h_iso1[8]->Fill(leptons[0].iso, evtwt_nom);
					h_iso2[8]->Fill(leptons[1].iso, evtwt_nom);
					h_iso3[8]->Fill(leptons[2].iso, evtwt_nom);
					h_iso4[8]->Fill(leptons[3].iso, evtwt_nom);
					h_12dR[8]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_13dR[8]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_14dR[8]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_23dR[8]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_24dR[8]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_34dR[8]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
				}
				else if( cat_string =="ett" and q_2 == -q_3){ 
					h_WMt[16]->Fill(0.0, evtwt_nom);
					h_mZ[16]->Fill((LepV(1)+LepV(2)).M(), evtwt_nom);
					h_mH[16]->Fill(0.0, evtwt_nom);
					h_met[16]->Fill(met, evtwt_nom);
					h_pt1[16]->Fill(leptons[0].pt, evtwt_nom);
					h_pt2[16]->Fill(leptons[1].pt, evtwt_nom);
					h_pt3[16]->Fill(leptons[2].pt, evtwt_nom);
					h_pt4[16]->Fill(leptons[3].pt, evtwt_nom);
					h_eta1[16]->Fill(leptons[0].eta, evtwt_nom);
					h_eta2[16]->Fill(leptons[1].eta, evtwt_nom);
					h_eta3[16]->Fill(leptons[2].eta, evtwt_nom);
					h_eta4[16]->Fill(leptons[3].eta, evtwt_nom);
					h_phi1[16]->Fill(leptons[0].phi, evtwt_nom);
					h_phi2[16]->Fill(leptons[1].phi, evtwt_nom);
					h_phi3[16]->Fill(leptons[2].phi, evtwt_nom);
					h_phi4[16]->Fill(leptons[3].phi, evtwt_nom);
					h_dxy1[16]->Fill(leptons[0].d0, evtwt_nom);
					h_dxy2[16]->Fill(leptons[1].d0, evtwt_nom);
					h_dxy3[16]->Fill(leptons[2].d0, evtwt_nom);
					h_dxy4[16]->Fill(leptons[3].d0, evtwt_nom);
					h_dZ1[16]->Fill(leptons[0].dZ, evtwt_nom);
					h_dZ2[16]->Fill(leptons[1].dZ, evtwt_nom);
					h_dZ3[16]->Fill(leptons[2].dZ, evtwt_nom);
					h_dZ4[16]->Fill(leptons[3].dZ, evtwt_nom);
					h_iso1[16]->Fill(leptons[0].iso, evtwt_nom);
					h_iso2[16]->Fill(leptons[1].iso, evtwt_nom);
					h_iso3[16]->Fill(leptons[2].iso, evtwt_nom);
					h_iso4[16]->Fill(leptons[3].iso, evtwt_nom);
					h_12dR[16]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_13dR[16]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_14dR[16]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_23dR[16]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_24dR[16]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_34dR[16]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
				}
				else if( cat_string =="mtt" and q_2 == -q_3){ 
					h_WMt[17]->Fill(0.0, evtwt_nom);
					h_mZ[17]->Fill((LepV(1)+LepV(2)).M(), evtwt_nom);
					h_mH[17]->Fill(0.0, evtwt_nom);
					h_met[17]->Fill(met, evtwt_nom);
					h_pt1[17]->Fill(leptons[0].pt, evtwt_nom);
					h_pt2[17]->Fill(leptons[1].pt, evtwt_nom);
					h_pt3[17]->Fill(leptons[2].pt, evtwt_nom);
					h_pt4[17]->Fill(leptons[3].pt, evtwt_nom);
					h_eta1[17]->Fill(leptons[0].eta, evtwt_nom);
					h_eta2[17]->Fill(leptons[1].eta, evtwt_nom);
					h_eta3[17]->Fill(leptons[2].eta, evtwt_nom);
					h_eta4[17]->Fill(leptons[3].eta, evtwt_nom);
					h_phi1[17]->Fill(leptons[0].phi, evtwt_nom);
					h_phi2[17]->Fill(leptons[1].phi, evtwt_nom);
					h_phi3[17]->Fill(leptons[2].phi, evtwt_nom);
					h_phi4[17]->Fill(leptons[3].phi, evtwt_nom);
					h_dxy1[17]->Fill(leptons[0].d0, evtwt_nom);
					h_dxy2[17]->Fill(leptons[1].d0, evtwt_nom);
					h_dxy3[17]->Fill(leptons[2].d0, evtwt_nom);
					h_dxy4[17]->Fill(leptons[3].d0, evtwt_nom);
					h_dZ1[17]->Fill(leptons[0].dZ, evtwt_nom);
					h_dZ2[17]->Fill(leptons[1].dZ, evtwt_nom);
					h_dZ3[17]->Fill(leptons[2].dZ, evtwt_nom);
					h_dZ4[17]->Fill(leptons[3].dZ, evtwt_nom);
					h_iso1[17]->Fill(leptons[0].iso, evtwt_nom);
					h_iso2[17]->Fill(leptons[1].iso, evtwt_nom);
					h_iso3[17]->Fill(leptons[2].iso, evtwt_nom);
					h_iso4[17]->Fill(leptons[3].iso, evtwt_nom);
					h_12dR[17]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_13dR[17]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_14dR[17]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_23dR[17]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_24dR[17]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
					h_34dR[17]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
				}
				applyTauES(cat_string);
				TLorentzVector MET;
				MET.SetPtEtaPhiM(met, 0, metphi, 0);
				
				std::vector<double> mZ, mZv, mH; 
				std::vector<int> paired_idx; 
				std::set<int> all_idx;
				for(int m = 1; m <= strlen(cat_name); ++m){
					all_idx.insert(m);
					for(int n = m+1; n <= strlen(cat_name); ++n){
						string pair_name = pairFunc(m,n,cat_name,20);
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
				//std::sort(mH.begin(), mH.end(), [](double a, double b){return a > b;});
				double Wmt = 0;
				if (mZ.size() >0 ) {
					//std::sort(mZ.begin(), mZ.end(), [](double a, double b){return a > b;});				
					for(int idx : paired_idx){ all_idx.erase(idx);}
					for(int unpaired_idx : all_idx){Wmt = (LepV(unpaired_idx)+MET).Mt();}
					if (cat_string== "ee"){
						//cout<<mZ.size()<<"\t"<<mH.size()<<endl;
						h_WMt[11]->Fill(Wmt, evtwt_nom);
						h_mZ[11]->Fill(mZ[0], evtwt_nom);
						h_mH[11]->Fill(0.0, evtwt_nom);
						h_met[11]->Fill(met, evtwt_nom);
						h_pt1[11]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2[11]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3[11]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4[11]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1[11]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2[11]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3[11]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4[11]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1[11]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2[11]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3[11]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4[11]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1[11]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2[11]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3[11]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4[11]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1[11]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2[11]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3[11]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4[11]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1[11]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2[11]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3[11]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4[11]->Fill(leptons[3].iso, evtwt_nom);
						h_12dR[11]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dR[11]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dR[11]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dR[11]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dR[11]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dR[11]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if (cat_string== "em"){ 
						//cout<<cat_name<<"\t"<<abs((L1+L3).M()-mZ)<<endl;
						h_WMt[12]->Fill(Wmt, evtwt_nom);
						h_mZ[12]->Fill(mZ[0], evtwt_nom);
						h_mH[12]->Fill(0.0, evtwt_nom);
						h_met[12]->Fill(met, evtwt_nom);
						h_pt1[12]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2[12]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3[12]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4[12]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1[12]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2[12]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3[12]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4[12]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1[12]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2[12]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3[12]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4[12]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1[12]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2[12]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3[12]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4[12]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1[12]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2[12]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3[12]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4[12]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1[12]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2[12]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3[12]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4[12]->Fill(leptons[3].iso, evtwt_nom);
						h_12dR[12]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dR[12]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dR[12]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dR[12]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dR[12]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dR[12]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if (cat_string== "mm"){ 
						h_WMt[13]->Fill(Wmt, evtwt_nom);
						h_mZ[13]->Fill(mZ[0], evtwt_nom);
						h_mH[13]->Fill(0.0, evtwt_nom);
						h_met[13]->Fill(met, evtwt_nom);
						h_pt1[13]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2[13]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3[13]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4[13]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1[13]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2[13]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3[13]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4[13]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1[13]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2[13]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3[13]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4[13]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1[13]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2[13]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3[13]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4[13]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1[13]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2[13]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3[13]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4[13]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1[13]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2[13]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3[13]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4[13]->Fill(leptons[3].iso, evtwt_nom);
						h_12dR[13]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dR[13]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dR[13]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dR[13]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dR[13]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dR[13]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if (cat_string== "ete" or cat_string== "eet" or cat_string == "tee"){ 
						h_WMt[14]->Fill(Wmt, evtwt_nom);
						h_mZ[14]->Fill(mZ[0], evtwt_nom);
						h_mH[14]->Fill(mH[0], evtwt_nom);
						h_met[14]->Fill(met, evtwt_nom);
						h_pt1[14]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2[14]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3[14]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4[14]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1[14]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2[14]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3[14]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4[14]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1[14]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2[14]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3[14]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4[14]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1[14]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2[14]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3[14]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4[14]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1[14]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2[14]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3[14]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4[14]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1[14]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2[14]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3[14]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4[14]->Fill(leptons[3].iso, evtwt_nom);
						h_12dR[14]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dR[14]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dR[14]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dR[14]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dR[14]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dR[14]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if (cat_string== "mtm" or cat_string== "mmt" or cat_string == "tmm"){ 		
						h_WMt[15]->Fill(Wmt, evtwt_nom);
						h_mZ[15]->Fill(mZ[0], evtwt_nom);
						h_mH[15]->Fill(mH[0], evtwt_nom);
						h_met[15]->Fill(met, evtwt_nom);
						h_pt1[15]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2[15]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3[15]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4[15]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1[15]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2[15]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3[15]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4[15]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1[15]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2[15]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3[15]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4[15]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1[15]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2[15]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3[15]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4[15]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1[15]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2[15]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3[15]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4[15]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1[15]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2[15]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3[15]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4[15]->Fill(leptons[3].iso, evtwt_nom);
						h_12dR[15]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dR[15]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dR[15]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dR[15]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dR[15]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dR[15]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if (cat_string== "eee"){ 
						//cout<<cat_name<<"\t"<<mH.size()<<endl;
						h_WMt[1]->Fill(Wmt, evtwt_nom);
						h_mZ[1]->Fill(mZ[0], evtwt_nom);
						h_mH[1]->Fill(mH[0], evtwt_nom);
						h_met[1]->Fill(met, evtwt_nom);
						h_pt1[1]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2[1]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3[1]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4[1]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1[1]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2[1]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3[1]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4[1]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1[1]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2[1]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3[1]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4[1]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1[1]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2[1]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3[1]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4[1]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1[1]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2[1]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3[1]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4[1]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1[1]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2[1]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3[1]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4[1]->Fill(leptons[3].iso, evtwt_nom);
						h_12dR[1]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dR[1]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dR[1]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dR[1]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dR[1]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dR[1]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if (cat_string== "eme" or cat_string== "eem" or cat_string == "mee"){
						h_WMt[2]->Fill(Wmt, evtwt_nom);
						h_mZ[2]->Fill(mZ[0], evtwt_nom);
						h_mH[2]->Fill(mH[0], evtwt_nom);
						h_met[2]->Fill(met, evtwt_nom);
						h_pt1[2]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2[2]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3[2]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4[2]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1[2]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2[2]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3[2]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4[2]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1[2]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2[2]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3[2]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4[2]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1[2]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2[2]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3[2]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4[2]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1[2]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2[2]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3[2]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4[2]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1[2]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2[2]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3[2]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4[2]->Fill(leptons[3].iso, evtwt_nom);
						h_12dR[2]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dR[2]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dR[2]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dR[2]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dR[2]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dR[2]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if (cat_string== "emm" or cat_string== "mme" or cat_string == "mem"){ 
						h_WMt[3]->Fill(Wmt, evtwt_nom);
						h_mZ[3]->Fill(mZ[0], evtwt_nom);
						h_mH[3]->Fill(mH[0], evtwt_nom);
						h_met[3]->Fill(met, evtwt_nom);
						h_pt1[3]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2[3]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3[3]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4[3]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1[3]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2[3]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3[3]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4[3]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1[3]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2[3]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3[3]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4[3]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1[3]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2[3]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3[3]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4[3]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1[3]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2[3]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3[3]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4[3]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1[3]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2[3]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3[3]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4[3]->Fill(leptons[3].iso, evtwt_nom);
						h_12dR[3]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dR[3]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dR[3]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dR[3]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dR[3]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dR[3]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if( cat_string== "mmm" ){
						h_WMt[4]->Fill(Wmt, evtwt_nom); 
						h_mZ[4]->Fill(mZ[0], evtwt_nom);
						h_mH[4]->Fill(mH[0], evtwt_nom);
						h_met[4]->Fill(met, evtwt_nom);
						h_pt1[4]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2[4]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3[4]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4[4]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1[4]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2[4]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3[4]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4[4]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1[4]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2[4]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3[4]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4[4]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1[4]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2[4]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3[4]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4[4]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1[4]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2[4]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3[4]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4[4]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1[4]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2[4]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3[4]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4[4]->Fill(leptons[3].iso, evtwt_nom);
						h_12dR[4]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dR[4]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dR[4]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dR[4]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dR[4]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dR[4]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					//if(mZ.size()<2) continue;
					else if( cat_string== "eeee" ){ 
						h_WMt[5]->Fill(Wmt, evtwt_nom);
						h_mZ[5]->Fill(mZ[0], evtwt_nom);
						h_mH[5]->Fill(mH[0], evtwt_nom);
						h_met[5]->Fill(met, evtwt_nom);
						h_pt1[5]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2[5]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3[5]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4[5]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1[5]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2[5]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3[5]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4[5]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1[5]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2[5]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3[5]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4[5]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1[5]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2[5]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3[5]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4[5]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1[5]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2[5]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3[5]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4[5]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1[5]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2[5]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3[5]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4[5]->Fill(leptons[3].iso, evtwt_nom);
						h_12dR[5]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dR[5]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dR[5]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dR[5]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dR[5]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dR[5]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if( cat_lepCount(cat_name,'e','g') == 3 and cat_lepCount(cat_name,'m','g') == 1 ){ 
						h_WMt[6]->Fill(Wmt, evtwt_nom);
						h_mZ[6]->Fill(mZ[0], evtwt_nom);
						h_mH[6]->Fill(mH[0], evtwt_nom);
						h_met[6]->Fill(met, evtwt_nom);
						h_pt1[6]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2[6]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3[6]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4[6]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1[6]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2[6]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3[6]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4[6]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1[6]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2[6]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3[6]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4[6]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1[6]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2[6]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3[6]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4[6]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1[6]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2[6]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3[6]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4[6]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1[6]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2[6]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3[6]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4[6]->Fill(leptons[3].iso, evtwt_nom);
						h_12dR[6]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dR[6]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dR[6]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dR[6]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dR[6]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dR[6]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if( cat_lepCount(cat_name,'e','g') == 2 and cat_lepCount(cat_name,'m','g') == 2 ){ 
						h_WMt[7]->Fill(Wmt, evtwt_nom);
						h_mZ[7]->Fill(mZ[0], evtwt_nom);
						h_mH[7]->Fill(mH[0], evtwt_nom);
						h_met[7]->Fill(met, evtwt_nom);
						h_pt1[7]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2[7]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3[7]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4[7]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1[7]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2[7]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3[7]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4[7]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1[7]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2[7]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3[7]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4[7]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1[7]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2[7]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3[7]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4[7]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1[7]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2[7]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3[7]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4[7]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1[7]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2[7]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3[7]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4[7]->Fill(leptons[3].iso, evtwt_nom);
						h_12dR[7]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dR[7]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dR[7]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dR[7]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dR[7]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dR[7]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if( cat_lepCount(cat_name,'e','g') == 1 and cat_lepCount(cat_name,'m','g') == 3 ){ 
						h_WMt[9]->Fill(Wmt, evtwt_nom);
						h_mZ[9]->Fill(mZ[0], evtwt_nom);
						h_mH[9]->Fill(mH[0], evtwt_nom);
						h_met[9]->Fill(met, evtwt_nom);
						h_pt1[9]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2[9]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3[9]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4[9]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1[9]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2[9]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3[9]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4[9]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1[9]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2[9]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3[9]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4[9]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1[9]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2[9]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3[9]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4[9]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1[9]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2[9]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3[9]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4[9]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1[9]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2[9]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3[9]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4[9]->Fill(leptons[3].iso, evtwt_nom);
						h_12dR[9]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dR[9]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dR[9]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dR[9]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dR[9]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dR[9]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if( cat_string== "mmmm" ){ 
						h_WMt[10]->Fill(Wmt, evtwt_nom);
						h_mZ[10]->Fill(mZ[0], evtwt_nom);
						h_mH[10]->Fill(mH[0], evtwt_nom);
						h_met[10]->Fill(met, evtwt_nom);
						h_pt1[10]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2[10]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3[10]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4[10]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1[10]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2[10]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3[10]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4[10]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1[10]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2[10]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3[10]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4[10]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1[10]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2[10]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3[10]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4[10]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1[10]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2[10]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3[10]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4[10]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1[10]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2[10]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3[10]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4[10]->Fill(leptons[3].iso, evtwt_nom);
						h_12dR[10]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dR[10]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dR[10]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dR[10]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dR[10]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dR[10]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}	
				}
				/*std::vector<int> ZcandsV = ZVetoMaker(cat_name, 20);	
				L1 = LepV(ZcandsV[0]), L2 = LepV(ZcandsV[1]), L3 = LepV(ZcandsV[2]), L4 = LepV(ZcandsV[3]);
				for(int iq = 0; iq <= 3; iq++){
					if (ZcandsV[iq] == 1) Q[iq] = q_1;
					else if (ZcandsV[iq] == 2) Q[iq] = q_2;
					else if (ZcandsV[iq] == 3) Q[iq] = q_3;
					else if (ZcandsV[iq] == 4) Q[iq] = q_4;
				}
				q1=Q[0],q2=Q[1],q3=Q[2],q4=Q[3];
				mll_1=-99, mll_2=-99, mllt_2=-99;
				if (q1==q3 and (L1+L3).Pt() >= (L2+L4).Pt()){
					mll_1 = (L1+L3).M();
					mllt_2 = (L2+L4).Mt();
				}
				else if (q1==q3 and (L2+L4).Pt() >= (L1+L3).Pt()){
					mll_1 = (L2+L4).M();
					mllt_2 = (L1+L3).Mt();
				}
				else if (q1==q4 and (L1+L4).Pt() >= (L2+L3).Pt()){
					mll_1 = (L1+L4).M();
					mllt_2 = (L2+L3).Mt();
				}
				else if (q1==q4 and (L2+L3).Pt() >= (L1+L4).Pt()){
					mll_1 = (L2+L3).M();
					mllt_2 = (L1+L4).Mt();
				}*/
				else if (mZv.size() >0 and mZ.size()==0){ 
					//std::sort(mZv.begin(), mZv.end(), [](double a, double b){return a > b;});
					//cout<<"BLABLASBLAS "<<cat_string<<endl; 
					if (cat_string== "ee"){ 
						//cout<<mZ.size()<<"\t"<<mH.size()<<endl;
						h_WMtv[11]->Fill(Wmt, evtwt_nom);
						h_mZv[11]->Fill(mZv[0], evtwt_nom);
						h_mHv[11]->Fill(0.0, evtwt_nom);
						h_metv[11]->Fill(met, evtwt_nom);
						h_pt1v[11]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2v[11]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3v[11]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4v[11]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1v[11]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2v[11]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3v[11]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4v[11]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1v[11]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2v[11]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3v[11]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4v[11]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1v[11]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2v[11]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3v[11]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4v[11]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1v[11]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2v[11]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3v[11]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4v[11]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1v[11]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2v[11]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3v[11]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4v[11]->Fill(leptons[3].iso, evtwt_nom);
						h_12dRv[11]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dRv[11]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dRv[11]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dRv[11]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dRv[11]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dRv[11]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if (cat_string== "em"){ 
						//cout<<cat_name<<"\t"<<abs((L1+L3).M()-mZ)<<endl;
						h_WMtv[12]->Fill(Wmt, evtwt_nom);
						h_mZv[12]->Fill(mZv[0], evtwt_nom);
						h_mHv[12]->Fill(0.0, evtwt_nom);
						h_metv[12]->Fill(met, evtwt_nom);
						h_pt1v[12]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2v[12]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3v[12]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4v[12]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1v[12]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2v[12]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3v[12]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4v[12]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1v[12]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2v[12]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3v[12]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4v[12]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1v[12]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2v[12]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3v[12]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4v[12]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1v[12]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2v[12]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3v[12]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4v[12]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1v[12]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2v[12]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3v[12]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4v[12]->Fill(leptons[3].iso, evtwt_nom);
						h_12dRv[12]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dRv[12]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dRv[12]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dRv[12]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dRv[12]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dRv[12]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if (cat_string== "mm"){ 
						h_WMtv[13]->Fill(Wmt, evtwt_nom);
						h_mZv[13]->Fill(mZv[0], evtwt_nom);
						h_mHv[13]->Fill(0.0, evtwt_nom);
						h_metv[13]->Fill(met, evtwt_nom);
						h_pt1v[13]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2v[13]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3v[13]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4v[13]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1v[13]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2v[13]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3v[13]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4v[13]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1v[13]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2v[13]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3v[13]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4v[13]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1v[13]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2v[13]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3v[13]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4v[13]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1v[13]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2v[13]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3v[13]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4v[13]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1v[13]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2v[13]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3v[13]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4v[13]->Fill(leptons[3].iso, evtwt_nom);
						h_12dRv[13]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dRv[13]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dRv[13]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dRv[13]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dRv[13]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dRv[13]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if (cat_string== "ete" or cat_string== "eet" or cat_string == "tee"){ 
						h_WMtv[14]->Fill(Wmt, evtwt_nom);
						h_mZv[14]->Fill(mZv[0], evtwt_nom);
						h_mHv[14]->Fill(mH[0], evtwt_nom);
						h_metv[14]->Fill(met, evtwt_nom);
						h_pt1v[14]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2v[14]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3v[14]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4v[14]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1v[14]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2v[14]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3v[14]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4v[14]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1v[14]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2v[14]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3v[14]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4v[14]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1v[14]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2v[14]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3v[14]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4v[14]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1v[14]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2v[14]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3v[14]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4v[14]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1v[14]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2v[14]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3v[14]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4v[14]->Fill(leptons[3].iso, evtwt_nom);
						h_12dRv[14]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dRv[14]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dRv[14]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dRv[14]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dRv[14]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dRv[14]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if (cat_string== "mtm" or cat_string== "mmt" or cat_string == "tmm"){ 
						h_WMtv[15]->Fill(Wmt, evtwt_nom);
						h_mZv[15]->Fill(mZv[0], evtwt_nom);
						h_mHv[15]->Fill(mH[0], evtwt_nom);
						h_metv[15]->Fill(met, evtwt_nom);
						h_pt1v[15]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2v[15]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3v[15]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4v[15]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1v[15]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2v[15]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3v[15]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4v[15]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1v[15]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2v[15]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3v[15]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4v[15]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1v[15]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2v[15]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3v[15]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4v[15]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1v[15]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2v[15]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3v[15]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4v[15]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1v[15]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2v[15]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3v[15]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4v[15]->Fill(leptons[3].iso, evtwt_nom);
						h_12dRv[15]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dRv[15]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dRv[15]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dRv[15]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dRv[15]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dRv[15]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if (cat_string== "eee"){ 
						//cout<<cat_name<<"\t"<<mH.size()<<endl;
						h_WMtv[1]->Fill(Wmt, evtwt_nom);
						h_mZv[1]->Fill(mZv[0], evtwt_nom);
						h_mHv[1]->Fill(mH[0], evtwt_nom);
						h_metv[1]->Fill(met, evtwt_nom);
						h_pt1v[1]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2v[1]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3v[1]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4v[1]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1v[1]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2v[1]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3v[1]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4v[1]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1v[1]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2v[1]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3v[1]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4v[1]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1v[1]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2v[1]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3v[1]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4v[1]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1v[1]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2v[1]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3v[1]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4v[1]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1v[1]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2v[1]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3v[1]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4v[1]->Fill(leptons[3].iso, evtwt_nom);
						h_12dRv[1]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dRv[1]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dRv[1]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dRv[1]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dRv[1]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dRv[1]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if (cat_string== "eme" or cat_string== "eem" or cat_string == "mee"){
						h_WMtv[2]->Fill(Wmt, evtwt_nom);
						h_mZv[2]->Fill(mZv[0], evtwt_nom);
						h_mHv[2]->Fill(mH[0], evtwt_nom);
						h_metv[2]->Fill(met, evtwt_nom);
						h_pt1v[2]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2v[2]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3v[2]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4v[2]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1v[2]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2v[2]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3v[2]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4v[2]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1v[2]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2v[2]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3v[2]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4v[2]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1v[2]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2v[2]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3v[2]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4v[2]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1v[2]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2v[2]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3v[2]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4v[2]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1v[2]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2v[2]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3v[2]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4v[2]->Fill(leptons[3].iso, evtwt_nom);
						h_12dRv[2]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dRv[2]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dRv[2]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dRv[2]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dRv[2]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dRv[2]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if (cat_string== "emm" or cat_string== "mme" or cat_string == "mem"){ 	
						h_WMtv[3]->Fill(Wmt, evtwt_nom);
						h_mZv[3]->Fill(mZv[0], evtwt_nom);
						h_mHv[3]->Fill(mH[0], evtwt_nom);
						h_metv[3]->Fill(met, evtwt_nom);
						h_pt1v[3]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2v[3]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3v[3]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4v[3]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1v[3]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2v[3]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3v[3]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4v[3]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1v[3]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2v[3]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3v[3]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4v[3]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1v[3]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2v[3]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3v[3]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4v[3]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1v[3]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2v[3]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3v[3]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4v[3]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1v[3]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2v[3]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3v[3]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4v[3]->Fill(leptons[3].iso, evtwt_nom);
						h_12dRv[3]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dRv[3]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dRv[3]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dRv[3]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dRv[3]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dRv[3]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if( cat_string== "mmm" ){ 
						h_WMtv[4]->Fill(Wmt, evtwt_nom);
						h_mZv[4]->Fill(mZv[0], evtwt_nom);
						h_mHv[4]->Fill(mH[0], evtwt_nom);
						h_metv[4]->Fill(met, evtwt_nom);
						h_pt1v[4]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2v[4]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3v[4]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4v[4]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1v[4]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2v[4]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3v[4]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4v[4]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1v[4]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2v[4]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3v[4]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4v[4]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1v[4]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2v[4]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3v[4]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4v[4]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1v[4]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2v[4]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3v[4]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4v[4]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1v[4]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2v[4]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3v[4]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4v[4]->Fill(leptons[3].iso, evtwt_nom);
						h_12dRv[4]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dRv[4]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dRv[4]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dRv[4]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dRv[4]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dRv[4]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if( cat_string== "eeee" ){ 
						h_WMtv[5]->Fill(Wmt, evtwt_nom);
						h_mZv[5]->Fill(mZv[0], evtwt_nom);
						h_mHv[5]->Fill(mH[0], evtwt_nom);
						h_metv[5]->Fill(met, evtwt_nom);
						h_pt1v[5]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2v[5]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3v[5]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4v[5]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1v[5]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2v[5]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3v[5]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4v[5]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1v[5]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2v[5]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3v[5]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4v[5]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1v[5]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2v[5]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3v[5]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4v[5]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1v[5]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2v[5]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3v[5]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4v[5]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1v[5]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2v[5]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3v[5]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4v[5]->Fill(leptons[3].iso, evtwt_nom);
						h_12dRv[5]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dRv[5]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dRv[5]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dRv[5]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dRv[5]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dRv[5]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if( cat_lepCount(cat_name,'e','g') == 3 and cat_lepCount(cat_name,'m','g') == 1 ){ 
						h_WMtv[6]->Fill(Wmt, evtwt_nom);
						h_mZv[6]->Fill(mZv[0], evtwt_nom);
						h_mHv[6]->Fill(mH[0], evtwt_nom);
						h_metv[6]->Fill(met, evtwt_nom);
						h_pt1v[6]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2v[6]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3v[6]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4v[6]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1v[6]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2v[6]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3v[6]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4v[6]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1v[6]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2v[6]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3v[6]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4v[6]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1v[6]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2v[6]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3v[6]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4v[6]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1v[6]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2v[6]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3v[6]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4v[6]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1v[6]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2v[6]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3v[6]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4v[6]->Fill(leptons[3].iso, evtwt_nom);
						h_12dRv[6]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dRv[6]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dRv[6]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dRv[6]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dRv[6]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dRv[6]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if( cat_lepCount(cat_name,'e','g') == 2 and cat_lepCount(cat_name,'m','g') == 2 ){ 
						h_WMtv[7]->Fill(Wmt, evtwt_nom);
						h_mZv[7]->Fill(mZv[0], evtwt_nom);
						h_mHv[7]->Fill(mH[0], evtwt_nom);
						h_metv[7]->Fill(met, evtwt_nom);
						h_pt1v[7]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2v[7]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3v[7]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4v[7]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1v[7]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2v[7]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3v[7]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4v[7]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1v[7]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2v[7]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3v[7]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4v[7]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1v[7]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2v[7]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3v[7]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4v[7]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1v[7]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2v[7]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3v[7]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4v[7]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1v[7]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2v[7]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3v[7]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4v[7]->Fill(leptons[3].iso, evtwt_nom);
						h_12dRv[7]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dRv[7]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dRv[7]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dRv[7]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dRv[7]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dRv[7]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if( cat_lepCount(cat_name,'e','g') == 1 and cat_lepCount(cat_name,'m','g') == 3 ){ 
						h_WMtv[9]->Fill(Wmt, evtwt_nom);
						h_mZv[9]->Fill(mZv[0], evtwt_nom);
						h_mHv[9]->Fill(mH[0], evtwt_nom);
						h_metv[9]->Fill(met, evtwt_nom);
						h_pt1v[9]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2v[9]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3v[9]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4v[9]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1v[9]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2v[9]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3v[9]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4v[9]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1v[9]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2v[9]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3v[9]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4v[9]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1v[9]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2v[9]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3v[9]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4v[9]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1v[9]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2v[9]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3v[9]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4v[9]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1v[9]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2v[9]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3v[9]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4v[9]->Fill(leptons[3].iso, evtwt_nom);
						h_12dRv[9]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dRv[9]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dRv[9]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dRv[9]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dRv[9]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dRv[9]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
					else if( cat_string== "mmmm" ){ 
						h_WMtv[10]->Fill(Wmt, evtwt_nom);
						h_mZv[10]->Fill(mZv[0], evtwt_nom);
						h_mHv[10]->Fill(mH[0], evtwt_nom);
						h_metv[10]->Fill(met, evtwt_nom);
						h_pt1v[10]->Fill(leptons[0].pt, evtwt_nom);
						h_pt2v[10]->Fill(leptons[1].pt, evtwt_nom);
						h_pt3v[10]->Fill(leptons[2].pt, evtwt_nom);
						h_pt4v[10]->Fill(leptons[3].pt, evtwt_nom);
						h_eta1v[10]->Fill(leptons[0].eta, evtwt_nom);
						h_eta2v[10]->Fill(leptons[1].eta, evtwt_nom);
						h_eta3v[10]->Fill(leptons[2].eta, evtwt_nom);
						h_eta4v[10]->Fill(leptons[3].eta, evtwt_nom);
						h_phi1v[10]->Fill(leptons[0].phi, evtwt_nom);
						h_phi2v[10]->Fill(leptons[1].phi, evtwt_nom);
						h_phi3v[10]->Fill(leptons[2].phi, evtwt_nom);
						h_phi4v[10]->Fill(leptons[3].phi, evtwt_nom);
						h_dxy1v[10]->Fill(leptons[0].d0, evtwt_nom);
						h_dxy2v[10]->Fill(leptons[1].d0, evtwt_nom);
						h_dxy3v[10]->Fill(leptons[2].d0, evtwt_nom);
						h_dxy4v[10]->Fill(leptons[3].d0, evtwt_nom);
						h_dZ1v[10]->Fill(leptons[0].dZ, evtwt_nom);
						h_dZ2v[10]->Fill(leptons[1].dZ, evtwt_nom);
						h_dZ3v[10]->Fill(leptons[2].dZ, evtwt_nom);
						h_dZ4v[10]->Fill(leptons[3].dZ, evtwt_nom);
						h_iso1v[10]->Fill(leptons[0].iso, evtwt_nom);
						h_iso2v[10]->Fill(leptons[1].iso, evtwt_nom);
						h_iso3v[10]->Fill(leptons[2].iso, evtwt_nom);
						h_iso4v[10]->Fill(leptons[3].iso, evtwt_nom);
						h_12dRv[10]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_13dRv[10]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_14dRv[10]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_23dRv[10]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_24dRv[10]->Fill(getDR(leptons[0].eta,leptons[0].phi,leptons[1].eta,leptons[1].phi), evtwt_nom);
						h_34dRv[10]->Fill(getDR(leptons[2].eta,leptons[2].phi,leptons[3].eta,leptons[3].phi), evtwt_nom);
					}
				}
			}//selections loop
		}//evt loop 
		hnevts->Write();
		scaleAndWriteHistograms(h_WMt, xs_weight);
		scaleAndWriteHistograms(h_WMtv, xs_weight);
		scaleAndWriteHistograms(h_mZ, xs_weight);
		scaleAndWriteHistograms(h_mZv, xs_weight);
		scaleAndWriteHistograms(h_mH, xs_weight);
		scaleAndWriteHistograms(h_mHv, xs_weight);
		scaleAndWriteHistograms(h_met, xs_weight);
		scaleAndWriteHistograms(h_metv, xs_weight);
		scaleAndWriteHistograms(h_pt1, xs_weight);
		scaleAndWriteHistograms(h_pt2, xs_weight);
		scaleAndWriteHistograms(h_pt3, xs_weight);
		scaleAndWriteHistograms(h_pt4, xs_weight);
		scaleAndWriteHistograms(h_pt1v, xs_weight);
		scaleAndWriteHistograms(h_pt2v, xs_weight);
		scaleAndWriteHistograms(h_pt3v, xs_weight);
		scaleAndWriteHistograms(h_pt4v, xs_weight);
		scaleAndWriteHistograms(h_eta1, xs_weight);
		scaleAndWriteHistograms(h_eta2, xs_weight);
		scaleAndWriteHistograms(h_eta3, xs_weight);
		scaleAndWriteHistograms(h_eta4, xs_weight);
		scaleAndWriteHistograms(h_eta1v, xs_weight);
		scaleAndWriteHistograms(h_eta2v, xs_weight);
		scaleAndWriteHistograms(h_eta3v, xs_weight);
		scaleAndWriteHistograms(h_eta4v, xs_weight);
		scaleAndWriteHistograms(h_phi1, xs_weight);
		scaleAndWriteHistograms(h_phi2, xs_weight);
		scaleAndWriteHistograms(h_phi3, xs_weight);
		scaleAndWriteHistograms(h_phi4, xs_weight);
		scaleAndWriteHistograms(h_phi1v, xs_weight);
		scaleAndWriteHistograms(h_phi2v, xs_weight);
		scaleAndWriteHistograms(h_phi3v, xs_weight);
		scaleAndWriteHistograms(h_phi4v, xs_weight);
		scaleAndWriteHistograms(h_dxy1, xs_weight);
		scaleAndWriteHistograms(h_dxy2, xs_weight);
		scaleAndWriteHistograms(h_dxy3, xs_weight);
		scaleAndWriteHistograms(h_dxy4, xs_weight);
		scaleAndWriteHistograms(h_dZ1, xs_weight);
		scaleAndWriteHistograms(h_dZ2, xs_weight);
		scaleAndWriteHistograms(h_dZ3, xs_weight);
		scaleAndWriteHistograms(h_dZ4, xs_weight);
		scaleAndWriteHistograms(h_iso1, xs_weight);
		scaleAndWriteHistograms(h_iso2, xs_weight);
		scaleAndWriteHistograms(h_iso3, xs_weight);
		scaleAndWriteHistograms(h_iso4, xs_weight);
		scaleAndWriteHistograms(h_dxy1v, xs_weight);
		scaleAndWriteHistograms(h_dxy2v, xs_weight);
		scaleAndWriteHistograms(h_dxy3v, xs_weight);
		scaleAndWriteHistograms(h_dxy4v, xs_weight);
		scaleAndWriteHistograms(h_dZ1v, xs_weight);
		scaleAndWriteHistograms(h_dZ2v, xs_weight);
		scaleAndWriteHistograms(h_dZ3v, xs_weight);
		scaleAndWriteHistograms(h_dZ4v, xs_weight);
		scaleAndWriteHistograms(h_iso1v, xs_weight);
		scaleAndWriteHistograms(h_iso2v, xs_weight);
		scaleAndWriteHistograms(h_iso3v, xs_weight);
		scaleAndWriteHistograms(h_iso4v, xs_weight);
		scaleAndWriteHistograms(h_12dR, xs_weight);
		scaleAndWriteHistograms(h_13dR, xs_weight);
		scaleAndWriteHistograms(h_14dR, xs_weight);
		scaleAndWriteHistograms(h_23dR, xs_weight);
		scaleAndWriteHistograms(h_24dR, xs_weight);
		scaleAndWriteHistograms(h_34dR, xs_weight);
		scaleAndWriteHistograms(h_12dRv, xs_weight);
		scaleAndWriteHistograms(h_13dRv, xs_weight);
		scaleAndWriteHistograms(h_14dRv, xs_weight);
		scaleAndWriteHistograms(h_23dRv, xs_weight);
		scaleAndWriteHistograms(h_24dRv, xs_weight);
		scaleAndWriteHistograms(h_34dRv, xs_weight);
		//cout<< j <<"\t"<< oname <<endl;
		//printf("%s %f\t %f\n", oname, 		h_mZ[13]->Integral(), h_eta1[13]->Integral());
		delete tree;
	}
	gSystem->FreeDirectory(dirp);
}

