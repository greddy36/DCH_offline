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

void DCH(const char* ext = ".root"){
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
        createHistograms(h_mH, "h_mH", "mll", 25, 0, 1000);
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
        createHistograms(h_dxy1, "h_dxy1", "dxy1", 25, -0.2, 0.2);
        createHistograms(h_dxy2, "h_dxy2", "dxy2", 25, -0.2, 0.2);
        createHistograms(h_dxy3, "h_dxy3", "dxy3", 25, -0.2, 0.2);
        createHistograms(h_dxy4, "h_dxy4", "dxy4", 25, -0.2, 0.2);
        createHistograms(h_dZ1, "h_dZ1", "dZ1", 25, -0.1, 0.1);
        createHistograms(h_dZ2, "h_dZ2", "dZ2", 25, -0.1, 0.1);
        createHistograms(h_dZ3, "h_dZ3", "dZ3", 25, -0.1, 0.1);
        createHistograms(h_dZ4, "h_dZ4", "dZ4", 25, -0.1, 0.1);
        createHistograms(h_iso1, "h_iso1", "iso1 in Z-veto", 25, 0, 0.5);
        createHistograms(h_iso2, "h_iso2", "iso2 in Z-veto", 25, 0, 0.5);
        createHistograms(h_iso3, "h_iso3", "iso3 in Z-veto", 25, 0, 0.5);
        createHistograms(h_iso4, "h_iso4", "iso4 in Z-veto", 25, 0, 0.5);
        createHistograms(h_dxy1v, "h_dxy1v", "dxy1 in Z-veto", 25, -0.2, 0.2);
        createHistograms(h_dxy2v, "h_dxy2v", "dxy2 in Z-veto", 25, -0.2, 0.2);
        createHistograms(h_dxy3v, "h_dxy3v", "dxy3 in Z-veto", 25, -0.2, 0.2);
        createHistograms(h_dxy4v, "h_dxy4v", "dxy4 in Z-veto", 25, -0.2, 0.2);
        createHistograms(h_dZ1v, "h_dZ1v", "dZ1 in Z-veto", 25, -0.1, 0.1);
        createHistograms(h_dZ2v, "h_dZ2v", "dZ2 in Z-veto", 25, -0.1, 0.1);
        createHistograms(h_dZ3v, "h_dZ3v", "dZ3 in Z-veto", 25, -0.1, 0.1);
        createHistograms(h_dZ4v, "h_dZ4v", "dZ4 in Z-veto", 25, -0.1, 0.1);
        createHistograms(h_iso1v, "h_iso1v", "iso1 in Z-veto", 25, 0, 0.5);
        createHistograms(h_iso2v, "h_iso2v", "iso2 in Z-veto", 25, 0, 0.5);
        createHistograms(h_iso3v, "h_iso3v", "iso3 in Z-veto", 25, 0, 0.5);
        createHistograms(h_iso4v, "h_iso4v", "iso4 in Z-veto", 25, 0, 0.5);
        
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
				//if (foundDup == true) continue;
				
				if(Ntau == 0) h_mH[1]->Fill(mll_1, brWeight*evtwt_nom);
				if(Ntau == 1) h_mH[2]->Fill(mll_1, brWeight*evtwt_nom);
				if(Ntau >= 2) h_mH[3]->Fill(mll_1, brWeight*evtwt_nom);
			}
		}//evt loop 
		hnevts->Write();	
		
		scaleAndWriteHistograms(h_mH, xs_weight);
		
		printf("%s %f\n", oname, XSec(filename[j])*lumi_2018/hnevts->Integral() );
		delete tree;
	}
	gSystem->FreeDirectory(dirp);
}

