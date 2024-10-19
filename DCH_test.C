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
	else if(fname.find("WZ_") < fname.length()) return 0;//27.6;
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
	else if(fname.find("Single") < fname.length()) return 1;//Data
	else{
		std::cout<<"DON'T KNOW X-SEC FOR FILE "<<fname<<endl;
		return 0;
	}
}


// Histogram creation utility to avoid code duplication
void createHistograms(std::vector<TH1F*>& histograms, const std::string& prefix, const std::string& label, int bins, float low, float high) {
    for (int i = 0; i <= 10; i++) {
        histograms.push_back(new TH1F(Form("%s%d", prefix.c_str(), i), Form("%s %d", label.c_str(), i), bins, low, high));
    }
}

void scaleAndWriteHistograms(std::vector<TH1F*>& histograms, float xs_weight, int start = 1, int end = -1) {
    if (end == -1) {
        end = histograms.size(); // Default to the end of the vector if no end index is specified
    }
    for (int i = start; i < end; ++i) {
        histograms[i]->Scale(xs_weight);
        histograms[i]->Write();
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

	float mDCH = 500, mZ = 91.2, lumi_2018 = 58900;//139000;
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		TH1D* hnevts = (TH1D*)ifile->Get("hNEvts");
		float xs_weight = 1;
		if(XSec(filename[j])!=1) xs_weight = lumi_2018*XSec(filename[j])/hnevts->Integral();
		
		std::string fname = filename[j];
		//if (fname.find("WZ") > fname.length()) continue;
		
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
		
		 // Compact histogram creation
        std::vector<TH1F*> h_mZ, h_mZv, h_mH, h_mHv, h_met, h_metv, h_pt1, h_pt2, h_pt3, h_pt4, h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1, h_eta2, h_eta3, h_eta4, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1, h_phi2, h_phi3, h_phi4, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v;
        createHistograms(h_mZ, "h_mZ", "mZ", 25, 0, 200);
        createHistograms(h_mZv, "h_mZv", "Z-veto", 25, 0, 300);
        createHistograms(h_mH, "h_mH", "mll", 25, 0, 300);
        createHistograms(h_mHv, "h_mHv", "mll in Z-veto", 25, 0, 300);
        createHistograms(h_met, "h_met", "MET", 25, 0, 300);
        createHistograms(h_metv, "h_metv", "MET in Z-veto", 25, 0, 300);
        createHistograms(h_pt1, "h_pt1", "pT1", 25, 0, 300);
        createHistograms(h_pt1v, "h_pt1v", "pT1 in Z-veto", 25, 0, 300);
        createHistograms(h_eta1, "h_eta1", "Eta1", 25, 0, 3);
        createHistograms(h_eta1v, "h_eta1v", "Eta1 in Z-veto", 25, 0, 3);
        createHistograms(h_phi1, "h_phi1", "Phi1", 25, -3.5, 3.5);
        createHistograms(h_phi1v, "h_phi1v", "Phi1 in Z-veto", 25, -3.5, 3.5);
        createHistograms(h_pt2, "h_pt2", "pT2", 25, 0, 300);
        createHistograms(h_pt2v, "h_pt2v", "pT2 in Z-veto", 25, 0, 300);
        createHistograms(h_eta2, "h_eta2", "Eta2", 25, 0, 3);
        createHistograms(h_eta2v, "h_eta2v", "Eta2 in Z-veto", 25, 0, 3);
        createHistograms(h_phi2, "h_phi2", "Phi2", 25, -3.5, 3.5);
        createHistograms(h_phi2v, "h_phi2v", "Phi2 in Z-veto", 25, -3.5, 3.5);
        createHistograms(h_pt3, "h_pt3", "pT3", 25, 0, 300);
        createHistograms(h_pt3v, "h_pt3v", "pT3 in Z-veto", 25, 0, 300);
        createHistograms(h_eta3, "h_eta3", "Eta3", 25, 0, 3);
        createHistograms(h_eta3v, "h_eta3v", "Eta3 in Z-veto", 25, 0, 3);
        createHistograms(h_phi3, "h_phi3", "Phi3", 25, -3.5, 3.5);
        createHistograms(h_phi3v, "h_phi4v", "Phi3 in Z-veto", 25, -3.5, 3.5);
        createHistograms(h_pt4, "h_pt4", "pT4", 25, 0, 300);
        createHistograms(h_pt4v, "h_pt4v", "pT4 in Z-veto", 25, 0, 300);
        createHistograms(h_eta4, "h_eta4", "Eta4", 25, 0, 3);
        createHistograms(h_eta4v, "h_eta4v", "Eta4 in Z-veto", 25, 0, 3);
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
        
		for (int i =0; i < tree->GetEntries(); i++){
			tree->GetEntry(i);			
			float *lep_pt, *tau_pt;
			const char *cat_name = numberToCat(cat);
			int Nlep = cat_lepCount(cat_name,'e','m'); 
			int Ntau = strlen(cat_name)-Nlep;  
			//if (cat <= 21) continue;
			/*float brWeight = 1;
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
			}*/
			
			float evtwt_nom = 1;
			if (XSec(filename[j])!=1){
				evtwt_nom = IDSF_1*IDSF_2*IDSF_3*IDSF_4*ISOSF_1*ISOSF_2*ISOSF_3*ISOSF_4*weightPUtruejson;
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
			}//cout<<LHEweight<< filename[j]<<endl;
									
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
				bool foundDup = false;
				Lepton lepton1 = {pt_1, eta_1, phi_1, m_1, q_1};
				Lepton lepton2 = {pt_2, eta_2, phi_2, m_2, q_2};
				Lepton lepton3 = {pt_3, eta_3, phi_3, m_3, q_3};
				Lepton lepton4 = {pt_4, eta_4, phi_4, m_4, q_4};
				Lepton leptons[4] = {lepton1, lepton2, lepton3, lepton4};//lepton array
				for (int w = 0; w < 4 && !foundDup; ++w) {
					for (int x = w + 1; x < 4; ++x) {
						if (isDuplicate(leptons[w], leptons[x])){
						foundDup = true;
						//cout<<leptons[w].eta <<"\t"<< leptons[w].phi<<endl;
						//cout<<leptons[x].eta <<"\t"<< leptons[x].phi<<endl;
						//cout<<endl;
						break;
						}
					}
				}
				if (foundDup == true) continue;
				
				TLorentzVector *Zcands = ZCandMaker_pair(cat_name, LepV(1), LepV(2), LepV(3), LepV(4), 20);	
				TLorentzVector L1 = Zcands[0], L2 = Zcands[1], L3 = Zcands[2], L4 = Zcands[3];
				if (cat_name == "eee" and (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20)){ 
					h_mZ[1]->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH[1]->Fill(mll_1, brWeight*evtwt_nom);
					h_met[1]->Fill(met, brWeight*evtwt_nom);
					h_pt1[1]->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2[1]->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3[1]->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_pt4[1]->Fill(L4.Pt(), brWeight*evtwt_nom);
					h_eta1[1]->Fill(L1.Eta(), brWeight*evtwt_nom);
					h_eta2[1]->Fill(L2.Eta(), brWeight*evtwt_nom);
					h_eta3[1]->Fill(L3.Eta(), brWeight*evtwt_nom);
					h_eta4[1]->Fill(L4.Eta(), brWeight*evtwt_nom);
					h_phi1[1]->Fill(L1.Phi(), brWeight*evtwt_nom);
					h_phi2[1]->Fill(L2.Phi(), brWeight*evtwt_nom);
					h_phi3[1]->Fill(L3.Phi(), brWeight*evtwt_nom);
					h_phi4[1]->Fill(L4.Phi(), brWeight*evtwt_nom);
					h_dxy1[1]->Fill(d0_1, brWeight*evtwt_nom);
					h_dxy2[1]->Fill(d0_2, brWeight*evtwt_nom);
					h_dxy3[1]->Fill(d0_3, brWeight*evtwt_nom);
					h_dxy4[1]->Fill(d0_4, brWeight*evtwt_nom);
					h_dZ1[1]->Fill(dZ_1, brWeight*evtwt_nom);
					h_dZ2[1]->Fill(dZ_2, brWeight*evtwt_nom);
					h_dZ3[1]->Fill(dZ_3, brWeight*evtwt_nom);
					h_dZ4[1]->Fill(dZ_4, brWeight*evtwt_nom);
					h_iso1[1]->Fill(iso_1, brWeight*evtwt_nom);
					h_iso2[1]->Fill(iso_2, brWeight*evtwt_nom);
					h_iso3[1]->Fill(iso_3, brWeight*evtwt_nom);
					h_iso4[1]->Fill(iso_4, brWeight*evtwt_nom);
				}
				else if (cat_name == "eme" and (abs((LepV(1)+LepV(3)).M()-mZ) < 20)){ 
					h_mZ[2]->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH[2]->Fill(mll_1, brWeight*evtwt_nom);
					h_met[2]->Fill(met, brWeight*evtwt_nom);
					h_pt1[2]->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2[2]->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3[2]->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_pt4[2]->Fill(L4.Pt(), brWeight*evtwt_nom);
					h_eta1[2]->Fill(L1.Eta(), brWeight*evtwt_nom);
					h_eta2[2]->Fill(L2.Eta(), brWeight*evtwt_nom);
					h_eta3[2]->Fill(L3.Eta(), brWeight*evtwt_nom);
					h_eta4[2]->Fill(L4.Eta(), brWeight*evtwt_nom);
					h_phi1[2]->Fill(L1.Phi(), brWeight*evtwt_nom);
					h_phi2[2]->Fill(L2.Phi(), brWeight*evtwt_nom);
					h_phi3[2]->Fill(L3.Phi(), brWeight*evtwt_nom);
					h_phi4[2]->Fill(L4.Phi(), brWeight*evtwt_nom);
					h_dxy1[2]->Fill(d0_1, brWeight*evtwt_nom);
					h_dxy2[2]->Fill(d0_2, brWeight*evtwt_nom);
					h_dxy3[2]->Fill(d0_3, brWeight*evtwt_nom);
					h_dxy4[2]->Fill(d0_4, brWeight*evtwt_nom);
					h_dZ1[2]->Fill(dZ_1, brWeight*evtwt_nom);
					h_dZ2[2]->Fill(dZ_2, brWeight*evtwt_nom);
					h_dZ3[2]->Fill(dZ_3, brWeight*evtwt_nom);
					h_dZ4[2]->Fill(dZ_4, brWeight*evtwt_nom);
					h_iso1[2]->Fill(iso_1, brWeight*evtwt_nom);
					h_iso2[2]->Fill(iso_2, brWeight*evtwt_nom);
					h_iso3[2]->Fill(iso_3, brWeight*evtwt_nom);
					h_iso4[2]->Fill(iso_4, brWeight*evtwt_nom);
				}
				else if (cat_name == "emm" and (abs((LepV(2)+LepV(3)).M()-mZ) < 20)){ 
					h_mZ[3]->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH[3]->Fill(mll_1, brWeight*evtwt_nom);
					h_met[3]->Fill(met, brWeight*evtwt_nom);
					h_pt1[3]->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2[3]->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3[3]->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_pt4[3]->Fill(L4.Pt(), brWeight*evtwt_nom);
					h_eta1[3]->Fill(L1.Eta(), brWeight*evtwt_nom);
					h_eta2[3]->Fill(L2.Eta(), brWeight*evtwt_nom);
					h_eta3[3]->Fill(L3.Eta(), brWeight*evtwt_nom);
					h_eta4[3]->Fill(L4.Eta(), brWeight*evtwt_nom);
					h_phi1[3]->Fill(L1.Phi(), brWeight*evtwt_nom);
					h_phi2[3]->Fill(L2.Phi(), brWeight*evtwt_nom);
					h_phi3[3]->Fill(L3.Phi(), brWeight*evtwt_nom);
					h_phi4[3]->Fill(L4.Phi(), brWeight*evtwt_nom);
					h_dxy1[3]->Fill(d0_1, brWeight*evtwt_nom);
					h_dxy2[3]->Fill(d0_2, brWeight*evtwt_nom);
					h_dxy3[3]->Fill(d0_3, brWeight*evtwt_nom);
					h_dxy4[3]->Fill(d0_4, brWeight*evtwt_nom);
					h_dZ1[3]->Fill(dZ_1, brWeight*evtwt_nom);
					h_dZ2[3]->Fill(dZ_2, brWeight*evtwt_nom);
					h_dZ3[3]->Fill(dZ_3, brWeight*evtwt_nom);
					h_dZ4[3]->Fill(dZ_4, brWeight*evtwt_nom);
					h_iso1[3]->Fill(iso_1, brWeight*evtwt_nom);
					h_iso2[3]->Fill(iso_2, brWeight*evtwt_nom);
					h_iso3[3]->Fill(iso_3, brWeight*evtwt_nom);
					h_iso4[3]->Fill(iso_4, brWeight*evtwt_nom);
				}
				else if( cat_name == "mmm" and (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20)){ 
					h_mZ[4]->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH[4]->Fill(mll_1, brWeight*evtwt_nom);
					h_met[4]->Fill(met, brWeight*evtwt_nom);
					h_pt1[4]->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2[4]->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3[4]->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_pt4[4]->Fill(L4.Pt(), brWeight*evtwt_nom);
					h_eta1[4]->Fill(L1.Eta(), brWeight*evtwt_nom);
					h_eta2[4]->Fill(L2.Eta(), brWeight*evtwt_nom);
					h_eta3[4]->Fill(L3.Eta(), brWeight*evtwt_nom);
					h_eta4[4]->Fill(L4.Eta(), brWeight*evtwt_nom);
					h_phi1[4]->Fill(L1.Phi(), brWeight*evtwt_nom);
					h_phi2[4]->Fill(L2.Phi(), brWeight*evtwt_nom);
					h_phi3[4]->Fill(L3.Phi(), brWeight*evtwt_nom);
					h_phi4[4]->Fill(L4.Phi(), brWeight*evtwt_nom);
					h_dxy1[4]->Fill(d0_1, brWeight*evtwt_nom);
					h_dxy2[4]->Fill(d0_2, brWeight*evtwt_nom);
					h_dxy3[4]->Fill(d0_3, brWeight*evtwt_nom);
					h_dxy4[4]->Fill(d0_4, brWeight*evtwt_nom);
					h_dZ1[4]->Fill(dZ_1, brWeight*evtwt_nom);
					h_dZ2[4]->Fill(dZ_2, brWeight*evtwt_nom);
					h_dZ3[4]->Fill(dZ_3, brWeight*evtwt_nom);
					h_dZ4[4]->Fill(dZ_4, brWeight*evtwt_nom);
					h_iso1[4]->Fill(iso_1, brWeight*evtwt_nom);
					h_iso2[4]->Fill(iso_2, brWeight*evtwt_nom);
					h_iso3[4]->Fill(iso_3, brWeight*evtwt_nom);
					h_iso4[4]->Fill(iso_4, brWeight*evtwt_nom);
				}
				else if( cat_name == "eeee" and (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20 or abs((LepV(1)+LepV(4)).M()-mZ) < 20 or abs((LepV(2)+LepV(4)).M()-mZ) < 20)){ 
					h_mZ[5]->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH[5]->Fill(mll_1, brWeight*evtwt_nom);
					h_met[5]->Fill(met, brWeight*evtwt_nom);
					h_pt1[5]->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2[5]->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3[5]->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_pt4[5]->Fill(L4.Pt(), brWeight*evtwt_nom);
					h_eta1[5]->Fill(L1.Eta(), brWeight*evtwt_nom);
					h_eta2[5]->Fill(L2.Eta(), brWeight*evtwt_nom);
					h_eta3[5]->Fill(L3.Eta(), brWeight*evtwt_nom);
					h_eta4[5]->Fill(L4.Eta(), brWeight*evtwt_nom);
					h_phi1[5]->Fill(L1.Phi(), brWeight*evtwt_nom);
					h_phi2[5]->Fill(L2.Phi(), brWeight*evtwt_nom);
					h_phi3[5]->Fill(L3.Phi(), brWeight*evtwt_nom);
					h_phi4[5]->Fill(L4.Phi(), brWeight*evtwt_nom);
					h_dxy1[5]->Fill(d0_1, brWeight*evtwt_nom);
					h_dxy2[5]->Fill(d0_2, brWeight*evtwt_nom);
					h_dxy3[5]->Fill(d0_3, brWeight*evtwt_nom);
					h_dxy4[5]->Fill(d0_4, brWeight*evtwt_nom);
					h_dZ1[5]->Fill(dZ_1, brWeight*evtwt_nom);
					h_dZ2[5]->Fill(dZ_2, brWeight*evtwt_nom);
					h_dZ3[5]->Fill(dZ_3, brWeight*evtwt_nom);
					h_dZ4[5]->Fill(dZ_4, brWeight*evtwt_nom);
					h_iso1[5]->Fill(iso_1, brWeight*evtwt_nom);
					h_iso2[5]->Fill(iso_2, brWeight*evtwt_nom);
					h_iso3[5]->Fill(iso_3, brWeight*evtwt_nom);
					h_iso4[5]->Fill(iso_4, brWeight*evtwt_nom);
				}
				else if( cat_name == "eeem" and (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20 )){ 
					h_mZ[6]->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH[6]->Fill(mll_1, brWeight*evtwt_nom);
					h_met[6]->Fill(met, brWeight*evtwt_nom);
					h_pt1[6]->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2[6]->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3[6]->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_pt4[6]->Fill(L4.Pt(), brWeight*evtwt_nom);
					h_eta1[6]->Fill(L1.Eta(), brWeight*evtwt_nom);
					h_eta2[6]->Fill(L2.Eta(), brWeight*evtwt_nom);
					h_eta3[6]->Fill(L3.Eta(), brWeight*evtwt_nom);
					h_eta4[6]->Fill(L4.Eta(), brWeight*evtwt_nom);
					h_phi1[6]->Fill(L1.Phi(), brWeight*evtwt_nom);
					h_phi2[6]->Fill(L2.Phi(), brWeight*evtwt_nom);
					h_phi3[6]->Fill(L3.Phi(), brWeight*evtwt_nom);
					h_phi4[6]->Fill(L4.Phi(), brWeight*evtwt_nom);
					h_dxy1[6]->Fill(d0_1, brWeight*evtwt_nom);
					h_dxy2[6]->Fill(d0_2, brWeight*evtwt_nom);
					h_dxy3[6]->Fill(d0_3, brWeight*evtwt_nom);
					h_dxy4[6]->Fill(d0_4, brWeight*evtwt_nom);
					h_dZ1[6]->Fill(dZ_1, brWeight*evtwt_nom);
					h_dZ2[6]->Fill(dZ_2, brWeight*evtwt_nom);
					h_dZ3[6]->Fill(dZ_3, brWeight*evtwt_nom);
					h_dZ4[6]->Fill(dZ_4, brWeight*evtwt_nom);
					h_iso1[6]->Fill(iso_1, brWeight*evtwt_nom);
					h_iso2[6]->Fill(iso_2, brWeight*evtwt_nom);
					h_iso3[6]->Fill(iso_3, brWeight*evtwt_nom);
					h_iso4[6]->Fill(iso_4, brWeight*evtwt_nom);
				}
				else if( cat_name == "eemm" and (abs((LepV(1)+LepV(3)).M()-mZ) < 20)){ 
					h_mZ[7]->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH[7]->Fill(mll_1, brWeight*evtwt_nom);
					h_met[7]->Fill(met, brWeight*evtwt_nom);
					h_pt1[7]->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2[7]->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3[7]->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_pt4[7]->Fill(L4.Pt(), brWeight*evtwt_nom);
					h_eta1[7]->Fill(L1.Eta(), brWeight*evtwt_nom);
					h_eta2[7]->Fill(L2.Eta(), brWeight*evtwt_nom);
					h_eta3[7]->Fill(L3.Eta(), brWeight*evtwt_nom);
					h_eta4[7]->Fill(L4.Eta(), brWeight*evtwt_nom);
					h_phi1[7]->Fill(L1.Phi(), brWeight*evtwt_nom);
					h_phi2[7]->Fill(L2.Phi(), brWeight*evtwt_nom);
					h_phi3[7]->Fill(L3.Phi(), brWeight*evtwt_nom);
					h_phi4[7]->Fill(L4.Phi(), brWeight*evtwt_nom);
					h_dxy1[7]->Fill(d0_1, brWeight*evtwt_nom);
					h_dxy2[7]->Fill(d0_2, brWeight*evtwt_nom);
					h_dxy3[7]->Fill(d0_3, brWeight*evtwt_nom);
					h_dxy4[7]->Fill(d0_4, brWeight*evtwt_nom);
					h_dZ1[7]->Fill(dZ_1, brWeight*evtwt_nom);
					h_dZ2[7]->Fill(dZ_2, brWeight*evtwt_nom);
					h_dZ3[7]->Fill(dZ_3, brWeight*evtwt_nom);
					h_dZ4[7]->Fill(dZ_4, brWeight*evtwt_nom);
					h_iso1[7]->Fill(iso_1, brWeight*evtwt_nom);
					h_iso2[7]->Fill(iso_2, brWeight*evtwt_nom);
					h_iso3[7]->Fill(iso_3, brWeight*evtwt_nom);
					h_iso4[7]->Fill(iso_4, brWeight*evtwt_nom);
				}
				else if( cat_name == "emem" and (abs((LepV(2)+LepV(4)).M()-mZ) < 20)){ 
					h_mZ[8]->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH[8]->Fill(mll_1, brWeight*evtwt_nom);
					h_met[8]->Fill(met, brWeight*evtwt_nom);
					h_pt1[8]->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2[8]->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3[8]->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_pt4[8]->Fill(L4.Pt(), brWeight*evtwt_nom);
					h_eta1[8]->Fill(L1.Eta(), brWeight*evtwt_nom);
					h_eta2[8]->Fill(L2.Eta(), brWeight*evtwt_nom);
					h_eta3[8]->Fill(L3.Eta(), brWeight*evtwt_nom);
					h_eta4[8]->Fill(L4.Eta(), brWeight*evtwt_nom);
					h_phi1[8]->Fill(L1.Phi(), brWeight*evtwt_nom);
					h_phi2[8]->Fill(L2.Phi(), brWeight*evtwt_nom);
					h_phi3[8]->Fill(L3.Phi(), brWeight*evtwt_nom);
					h_phi4[8]->Fill(L4.Phi(), brWeight*evtwt_nom);
					h_dxy1[8]->Fill(d0_1, brWeight*evtwt_nom);
					h_dxy2[8]->Fill(d0_2, brWeight*evtwt_nom);
					h_dxy3[8]->Fill(d0_3, brWeight*evtwt_nom);
					h_dxy4[8]->Fill(d0_4, brWeight*evtwt_nom);
					h_dZ1[8]->Fill(dZ_1, brWeight*evtwt_nom);
					h_dZ2[8]->Fill(dZ_2, brWeight*evtwt_nom);
					h_dZ3[8]->Fill(dZ_3, brWeight*evtwt_nom);
					h_dZ4[8]->Fill(dZ_4, brWeight*evtwt_nom);
					h_iso1[8]->Fill(iso_1, brWeight*evtwt_nom);
					h_iso2[8]->Fill(iso_2, brWeight*evtwt_nom);
					h_iso3[8]->Fill(iso_3, brWeight*evtwt_nom);
					h_iso4[8]->Fill(iso_4, brWeight*evtwt_nom);
				}
				else if( cat_name == "emmm" and (abs((LepV(2)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(4)).M()-mZ) < 20)){ 
					h_mZ[9]->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH[9]->Fill(mll_1, brWeight*evtwt_nom);
					h_met[9]->Fill(met, brWeight*evtwt_nom);
					h_pt1[9]->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2[9]->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3[9]->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_pt4[9]->Fill(L4.Pt(), brWeight*evtwt_nom);
					h_eta1[9]->Fill(L1.Eta(), brWeight*evtwt_nom);
					h_eta2[9]->Fill(L2.Eta(), brWeight*evtwt_nom);
					h_eta3[9]->Fill(L3.Eta(), brWeight*evtwt_nom);
					h_eta4[9]->Fill(L4.Eta(), brWeight*evtwt_nom);
					h_phi1[9]->Fill(L1.Phi(), brWeight*evtwt_nom);
					h_phi2[9]->Fill(L2.Phi(), brWeight*evtwt_nom);
					h_phi3[9]->Fill(L3.Phi(), brWeight*evtwt_nom);
					h_phi4[9]->Fill(L4.Phi(), brWeight*evtwt_nom);
					h_dxy1[9]->Fill(d0_1, brWeight*evtwt_nom);
					h_dxy2[9]->Fill(d0_2, brWeight*evtwt_nom);
					h_dxy3[9]->Fill(d0_3, brWeight*evtwt_nom);
					h_dxy4[9]->Fill(d0_4, brWeight*evtwt_nom);
					h_dZ1[9]->Fill(dZ_1, brWeight*evtwt_nom);
					h_dZ2[9]->Fill(dZ_2, brWeight*evtwt_nom);
					h_dZ3[9]->Fill(dZ_3, brWeight*evtwt_nom);
					h_dZ4[9]->Fill(dZ_4, brWeight*evtwt_nom);
					h_iso1[9]->Fill(iso_1, brWeight*evtwt_nom);
					h_iso2[9]->Fill(iso_2, brWeight*evtwt_nom);
					h_iso3[9]->Fill(iso_3, brWeight*evtwt_nom);
					h_iso4[9]->Fill(iso_4, brWeight*evtwt_nom);
				}
				else if( cat_name == "mmmm" and (abs((LepV(1)+LepV(3)).M()-mZ) < 20 or abs((LepV(2)+LepV(3)).M()-mZ) < 20 or abs((LepV(1)+LepV(4)).M()-mZ) < 20 or abs((LepV(2)+LepV(4)).M()-mZ) < 20)){ 
					h_mZ[10]->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH[10]->Fill(mll_1, brWeight*evtwt_nom);
					h_met[10]->Fill(met, brWeight*evtwt_nom);
					h_pt1[10]->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2[10]->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3[10]->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_pt4[10]->Fill(L4.Pt(), brWeight*evtwt_nom);
					h_eta1[10]->Fill(L1.Eta(), brWeight*evtwt_nom);
					h_eta2[10]->Fill(L2.Eta(), brWeight*evtwt_nom);
					h_eta3[10]->Fill(L3.Eta(), brWeight*evtwt_nom);
					h_eta4[10]->Fill(L4.Eta(), brWeight*evtwt_nom);
					h_phi1[10]->Fill(L1.Phi(), brWeight*evtwt_nom);
					h_phi2[10]->Fill(L2.Phi(), brWeight*evtwt_nom);
					h_phi3[10]->Fill(L3.Phi(), brWeight*evtwt_nom);
					h_phi4[10]->Fill(L4.Phi(), brWeight*evtwt_nom);
					h_dxy1[10]->Fill(d0_1, brWeight*evtwt_nom);
					h_dxy2[10]->Fill(d0_2, brWeight*evtwt_nom);
					h_dxy3[10]->Fill(d0_3, brWeight*evtwt_nom);
					h_dxy4[10]->Fill(d0_4, brWeight*evtwt_nom);
					h_dZ1[10]->Fill(dZ_1, brWeight*evtwt_nom);
					h_dZ2[10]->Fill(dZ_2, brWeight*evtwt_nom);
					h_dZ3[10]->Fill(dZ_3, brWeight*evtwt_nom);
					h_dZ4[10]->Fill(dZ_4, brWeight*evtwt_nom);
					h_iso1[10]->Fill(iso_1, brWeight*evtwt_nom);
					h_iso2[10]->Fill(iso_2, brWeight*evtwt_nom);
					h_iso3[10]->Fill(iso_3, brWeight*evtwt_nom);
					h_iso4[10]->Fill(iso_4, brWeight*evtwt_nom);
				}
				
				TLorentzVector *ZcandsV = ZVetoMaker_pair(cat_name, LepV(1), LepV(2), LepV(3), LepV(4), 20);	
				L1 = ZcandsV[0], L2 = ZcandsV[1], L3 = ZcandsV[2], L4 = ZcandsV[3];
				
				if (cat_name == "eee" and (abs((LepV(1)+LepV(3)).M()-mZ) > 20 and abs((LepV(2)+LepV(3)).M()-mZ) > 20)){ 
					h_mZv[1]->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mHv[1]->Fill(mll_1, brWeight*evtwt_nom);
					h_metv[1]->Fill(met, brWeight*evtwt_nom);
					h_pt1v[1]->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2v[1]->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3v[1]->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_pt4v[1]->Fill(L4.Pt(), brWeight*evtwt_nom);
					h_eta1v[1]->Fill(L1.Eta(), brWeight*evtwt_nom);
					h_eta2v[1]->Fill(L2.Eta(), brWeight*evtwt_nom);
					h_eta3v[1]->Fill(L3.Eta(), brWeight*evtwt_nom);
					h_eta4v[1]->Fill(L4.Eta(), brWeight*evtwt_nom);
					h_phi1v[1]->Fill(L1.Phi(), brWeight*evtwt_nom);
					h_phi2v[1]->Fill(L2.Phi(), brWeight*evtwt_nom);
					h_phi3v[1]->Fill(L3.Phi(), brWeight*evtwt_nom);
					h_phi4v[1]->Fill(L4.Phi(), brWeight*evtwt_nom);
					h_dxy1v[1]->Fill(d0_1, brWeight*evtwt_nom);
					h_dxy2v[1]->Fill(d0_2, brWeight*evtwt_nom);
					h_dxy3v[1]->Fill(d0_3, brWeight*evtwt_nom);
					h_dxy4v[1]->Fill(d0_4, brWeight*evtwt_nom);
					h_dZ1v[1]->Fill(dZ_1, brWeight*evtwt_nom);
					h_dZ2v[1]->Fill(dZ_2, brWeight*evtwt_nom);
					h_dZ3v[1]->Fill(dZ_3, brWeight*evtwt_nom);
					h_dZ4v[1]->Fill(dZ_4, brWeight*evtwt_nom);
					h_iso1v[1]->Fill(iso_1, brWeight*evtwt_nom);
					h_iso2v[1]->Fill(iso_2, brWeight*evtwt_nom);
					h_iso3v[1]->Fill(iso_3, brWeight*evtwt_nom);
					h_iso4v[1]->Fill(iso_4, brWeight*evtwt_nom);
				}
				else if (cat_name == "eme" and (abs((LepV(1)+LepV(3)).M()-mZ) > 20)){  
					h_mZv[2]->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mHv[2]->Fill(mll_1, brWeight*evtwt_nom);
					h_metv[2]->Fill(met, brWeight*evtwt_nom);
					h_pt1v[2]->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2v[2]->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3v[2]->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_pt4v[2]->Fill(L4.Pt(), brWeight*evtwt_nom);
					h_eta1v[2]->Fill(L1.Eta(), brWeight*evtwt_nom);
					h_eta2v[2]->Fill(L2.Eta(), brWeight*evtwt_nom);
					h_eta3v[2]->Fill(L3.Eta(), brWeight*evtwt_nom);
					h_eta4v[2]->Fill(L4.Eta(), brWeight*evtwt_nom);
					h_phi1v[2]->Fill(L1.Phi(), brWeight*evtwt_nom);
					h_phi2v[2]->Fill(L2.Phi(), brWeight*evtwt_nom);
					h_phi3v[2]->Fill(L3.Phi(), brWeight*evtwt_nom);
					h_phi4v[2]->Fill(L4.Phi(), brWeight*evtwt_nom);
					h_dxy1v[2]->Fill(d0_1, brWeight*evtwt_nom);
					h_dxy2v[2]->Fill(d0_2, brWeight*evtwt_nom);
					h_dxy3v[2]->Fill(d0_3, brWeight*evtwt_nom);
					h_dxy4v[2]->Fill(d0_4, brWeight*evtwt_nom);
					h_dZ1v[2]->Fill(dZ_1, brWeight*evtwt_nom);
					h_dZ2v[2]->Fill(dZ_2, brWeight*evtwt_nom);
					h_dZ3v[2]->Fill(dZ_3, brWeight*evtwt_nom);
					h_dZ4v[2]->Fill(dZ_4, brWeight*evtwt_nom);
					h_iso1v[2]->Fill(iso_1, brWeight*evtwt_nom);
					h_iso2v[2]->Fill(iso_2, brWeight*evtwt_nom);
					h_iso3v[2]->Fill(iso_3, brWeight*evtwt_nom);
					h_iso4v[2]->Fill(iso_4, brWeight*evtwt_nom);
				}
				else if (cat_name == "emm" and (abs((LepV(2)+LepV(3)).M()-mZ) > 20)){ 
					h_mZv[3]->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mHv[3]->Fill(mll_1, brWeight*evtwt_nom);
					h_metv[3]->Fill(met, brWeight*evtwt_nom);
					h_pt1v[3]->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2v[3]->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3v[3]->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_pt4v[3]->Fill(L4.Pt(), brWeight*evtwt_nom);
					h_eta1v[3]->Fill(L1.Eta(), brWeight*evtwt_nom);
					h_eta2v[3]->Fill(L2.Eta(), brWeight*evtwt_nom);
					h_eta3v[3]->Fill(L3.Eta(), brWeight*evtwt_nom);
					h_eta4v[3]->Fill(L4.Eta(), brWeight*evtwt_nom);
					h_phi1v[3]->Fill(L1.Phi(), brWeight*evtwt_nom);
					h_phi2v[3]->Fill(L2.Phi(), brWeight*evtwt_nom);
					h_phi3v[3]->Fill(L3.Phi(), brWeight*evtwt_nom);
					h_phi4v[3]->Fill(L4.Phi(), brWeight*evtwt_nom);
					h_dxy1v[3]->Fill(d0_1, brWeight*evtwt_nom);
					h_dxy2v[3]->Fill(d0_2, brWeight*evtwt_nom);
					h_dxy3v[3]->Fill(d0_3, brWeight*evtwt_nom);
					h_dxy4v[3]->Fill(d0_4, brWeight*evtwt_nom);
					h_dZ1v[3]->Fill(dZ_1, brWeight*evtwt_nom);
					h_dZ2v[3]->Fill(dZ_2, brWeight*evtwt_nom);
					h_dZ3v[3]->Fill(dZ_3, brWeight*evtwt_nom);
					h_dZ4v[3]->Fill(dZ_4, brWeight*evtwt_nom);
					h_iso1v[3]->Fill(iso_1, brWeight*evtwt_nom);
					h_iso2v[3]->Fill(iso_2, brWeight*evtwt_nom);
					h_iso3v[3]->Fill(iso_3, brWeight*evtwt_nom);
					h_iso4v[3]->Fill(iso_4, brWeight*evtwt_nom);
				}
				else if( cat_name == "mmm" and (abs((LepV(1)+LepV(3)).M()-mZ) > 20 and abs((LepV(2)+LepV(3)).M()-mZ) > 20)){ 
					h_mZv[4]->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mHv[4]->Fill(mll_1, brWeight*evtwt_nom);
					h_metv[4]->Fill(met, brWeight*evtwt_nom);
					h_pt1v[4]->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2v[4]->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3v[4]->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_pt4v[4]->Fill(L4.Pt(), brWeight*evtwt_nom);
					h_eta1v[4]->Fill(L1.Eta(), brWeight*evtwt_nom);
					h_eta2v[4]->Fill(L2.Eta(), brWeight*evtwt_nom);
					h_eta3v[4]->Fill(L3.Eta(), brWeight*evtwt_nom);
					h_eta4v[4]->Fill(L4.Eta(), brWeight*evtwt_nom);
					h_phi1v[4]->Fill(L1.Phi(), brWeight*evtwt_nom);
					h_phi2v[4]->Fill(L2.Phi(), brWeight*evtwt_nom);
					h_phi3v[4]->Fill(L3.Phi(), brWeight*evtwt_nom);
					h_dxy1v[4]->Fill(d0_1, brWeight*evtwt_nom);
					h_dxy2v[4]->Fill(d0_2, brWeight*evtwt_nom);
					h_dxy3v[4]->Fill(d0_3, brWeight*evtwt_nom);
					h_dxy4v[4]->Fill(d0_4, brWeight*evtwt_nom);
					h_dZ1v[4]->Fill(dZ_1, brWeight*evtwt_nom);
					h_dZ2v[4]->Fill(dZ_2, brWeight*evtwt_nom);
					h_dZ3v[4]->Fill(dZ_3, brWeight*evtwt_nom);
					h_dZ4v[4]->Fill(dZ_4, brWeight*evtwt_nom);
					h_iso1v[4]->Fill(iso_1, brWeight*evtwt_nom);
					h_iso2v[4]->Fill(iso_2, brWeight*evtwt_nom);
					h_iso3v[4]->Fill(iso_3, brWeight*evtwt_nom);
					h_iso4v[4]->Fill(iso_4, brWeight*evtwt_nom);
				}
			}
		}//evt loop 
		hnevts->Write();	

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
		//cout<< j <<"\t"<< oname <<endl;
		printf("%s %f\n", oname, XSec(filename[j])*lumi_2018/hnevts->Integral() );
		delete tree;
	}
	gSystem->FreeDirectory(dirp);
}

