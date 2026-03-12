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
void createHistograms(std::map<std::string, TH1D*>& histograms,
                      const std::string& prefix,
                      const std::string& label,
                      int bins, double low, double high) {
    for (const std::string& channel : {
        "ee", "em", "mm", "eee", "eem", "eet", "emt", "emm", "mmm", "mmt",
        "ett", "mtt", "eeee", "eeem", "eemm", "mmem", "mmmm", "eeet", "eemt",
        "eett", "emmt", "emtt", "ettt", "mmmt", "mmtt", "mttt"
    }) {
        std::string hist_name = prefix + "_" + channel;
        std::string hist_label = label + " " + channel;
        histograms[channel] = new TH1D(hist_name.c_str(), hist_label.c_str(), bins, low, high);
        histograms[channel]->Sumw2(); // for proper error propagation
    }
}

void fillHistograms(const std::string& cat_string,
					std::map<std::string, TH1D*>& h_mZ, 
					std::map<std::string, TH1D*>& h_mH, 
					std::map<std::string, TH1D*>& h_met, 
					std::map<std::string, TH1D*>& h_pt1, 
					std::map<std::string, TH1D*>& h_pt2,
					std::map<std::string, TH1D*>& h_pt3,
					std::map<std::string, TH1D*>& h_pt4,
					std::map<std::string, TH1D*>& h_eta1,
					std::map<std::string, TH1D*>& h_eta2,
					std::map<std::string, TH1D*>& h_eta3,
					std::map<std::string, TH1D*>& h_eta4,
					std::map<std::string, TH1D*>& h_phi1,
					std::map<std::string, TH1D*>& h_phi2,
					std::map<std::string, TH1D*>& h_phi3,
					std::map<std::string, TH1D*>& h_phi4,
					std::map<std::string, TH1D*>& h_dxy1,
					std::map<std::string, TH1D*>& h_dxy2,
					std::map<std::string, TH1D*>& h_dxy3,
					std::map<std::string, TH1D*>& h_dxy4,
					std::map<std::string, TH1D*>& h_dZ1,
					std::map<std::string, TH1D*>& h_dZ2,
					std::map<std::string, TH1D*>& h_dZ3,
					std::map<std::string, TH1D*>& h_dZ4,
					std::map<std::string, TH1D*>& h_iso1,
					std::map<std::string, TH1D*>& h_iso2,
					std::map<std::string, TH1D*>& h_iso3,
					std::map<std::string, TH1D*>& h_iso4,
					std::map<std::string, TH1D*>& h_12dR,
					std::map<std::string, TH1D*>& h_13dR,
					std::map<std::string, TH1D*>& h_14dR,
					std::map<std::string, TH1D*>& h_23dR,
					std::map<std::string, TH1D*>& h_24dR,
					std::map<std::string, TH1D*>& h_34dR,
					std::map<std::string, TH1D*>& h_WMt,
                    double Wmt, double met,
                    double mZ, double mH,
                    const std::vector<Lepton>& leptons,
                    double evtwt_nom) {
                    
    h_WMt[cat_string]->Fill(Wmt, evtwt_nom);
    h_mZ[cat_string]->Fill(mZ, evtwt_nom);
    h_mH[cat_string]->Fill(mH, evtwt_nom);
    h_met[cat_string]->Fill(met, evtwt_nom);

    h_pt1[cat_string]->Fill(leptons[0].pt, evtwt_nom);
    h_pt2[cat_string]->Fill(leptons[1].pt, evtwt_nom);
    h_pt3[cat_string]->Fill(leptons[2].pt, evtwt_nom);
    h_pt4[cat_string]->Fill(leptons[3].pt, evtwt_nom);

    h_eta1[cat_string]->Fill(leptons[0].eta, evtwt_nom);
    h_eta2[cat_string]->Fill(leptons[1].eta, evtwt_nom);
    h_eta3[cat_string]->Fill(leptons[2].eta, evtwt_nom);
    h_eta4[cat_string]->Fill(leptons[3].eta, evtwt_nom);

    h_phi1[cat_string]->Fill(leptons[0].phi, evtwt_nom);
    h_phi2[cat_string]->Fill(leptons[1].phi, evtwt_nom);
    h_phi3[cat_string]->Fill(leptons[2].phi, evtwt_nom);
    h_phi4[cat_string]->Fill(leptons[3].phi, evtwt_nom);

    h_dxy1[cat_string]->Fill(leptons[0].d0, evtwt_nom);
    h_dxy2[cat_string]->Fill(leptons[1].d0, evtwt_nom);
    h_dxy3[cat_string]->Fill(leptons[2].d0, evtwt_nom);
    h_dxy4[cat_string]->Fill(leptons[3].d0, evtwt_nom);

    h_dZ1[cat_string]->Fill(leptons[0].dZ, evtwt_nom);
    h_dZ2[cat_string]->Fill(leptons[1].dZ, evtwt_nom);
    h_dZ3[cat_string]->Fill(leptons[2].dZ, evtwt_nom);
    h_dZ4[cat_string]->Fill(leptons[3].dZ, evtwt_nom);

    h_iso1[cat_string]->Fill(leptons[0].iso, evtwt_nom);
    h_iso2[cat_string]->Fill(leptons[1].iso, evtwt_nom);
    h_iso3[cat_string]->Fill(leptons[2].iso, evtwt_nom);
    h_iso4[cat_string]->Fill(leptons[3].iso, evtwt_nom);

    h_12dR[cat_string]->Fill(getDR(leptons[0].eta, leptons[0].phi, leptons[1].eta, leptons[1].phi), evtwt_nom);
    h_13dR[cat_string]->Fill(getDR(leptons[0].eta, leptons[0].phi, leptons[2].eta, leptons[2].phi), evtwt_nom);
    h_14dR[cat_string]->Fill(getDR(leptons[0].eta, leptons[0].phi, leptons[3].eta, leptons[3].phi), evtwt_nom);
    h_23dR[cat_string]->Fill(getDR(leptons[1].eta, leptons[1].phi, leptons[2].eta, leptons[2].phi), evtwt_nom);
    h_24dR[cat_string]->Fill(getDR(leptons[1].eta, leptons[1].phi, leptons[3].eta, leptons[3].phi), evtwt_nom);
    h_34dR[cat_string]->Fill(getDR(leptons[2].eta, leptons[2].phi, leptons[3].eta, leptons[3].phi), evtwt_nom);
}


void scaleAndWriteHistograms(std::map<std::string, TH1D*>& histograms, double xs_weight) {
    for (const std::string& channel : {
        "ee", "em", "mm", "eee", "eem", "eet", "emt", "emm", "mmm", "mmt",
        "ett", "mtt", "eeee", "eeem", "eemm", "mmem", "mmmm", "eeet", "eemt",
        "eett", "emmt", "emtt", "ettt", "mmmt", "mmtt", "mttt"
    }) {
        histograms[channel]->Scale(xs_weight);
        histograms[channel]->Write();
    }
}

void test_simple(const char* ext = "root"){
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
	

	double mDCH = 500.0, mZ = 91.2, lumi_2016 = 35900, lumi_2017 = 41500, lumi_2018 = 58900.0; //139000;
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		std::string fname = filename[j];
		if (fname.find("_2018.") > fname.length()) continue;
		if (fname.find("Hpp") > fname.length()) continue;
		cout<<filename[j]<<endl;
		//if (XSec(filename[j])==1) continue; 
		
		//cout<<XSec(filename[j])<<endl;
		const char* o_name;
		o_name = "hist_test_nopair";
		
		char *oname = gSystem->ConcatFileName(o_name, filename[j]);
		TFile* ofile = new TFile(oname, "RECREATE"); 
		
		TH1D* hNWEvts;
		if(XSec(fname)!=1){
			hNWEvts = (TH1D*)ifile->Get("hNWEvts")->Clone("hNWEvts");
			if (!hNWEvts) hNWEvts = (TH1D*)ifile->Get("hNEvts")->Clone("hNWEvts");
		}

		hNWEvts->Write();
		double xs_weight = 1.0;
		
		TTree *tree = (TTree*)ifile->Get("Events");
		MyBranch(tree);
		
		// Compact histogram creation
       std::map<std::string, TH1D*> h_mZ, h_mZv, h_mH, h_mHv, h_met, h_metv, h_pt1, h_pt2, h_pt3, h_pt4, h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1, h_eta2, h_eta3, h_eta4, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1, h_phi2, h_phi3, h_phi4, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMt, h_WMtv;
        
        createHistograms(h_mZ, "h_mZ", "mZ", 100,0,1500);
        createHistograms(h_mZv, "h_mZv", "Z-veto", 100,0,1500);
        createHistograms(h_mH, "h_mH", "mll", 100,0,1500);
        createHistograms(h_mHv, "h_mHv", "mll in Z-veto", 100,0,1500);
        createHistograms(h_met, "h_met", "MET", 100,0,1500);
        createHistograms(h_metv, "h_metv", "MET in Z-veto", 100,0,1500);
        createHistograms(h_pt1, "h_pt1", "pT1", 100,0,1500);
        createHistograms(h_pt1v, "h_pt1v", "pT1 in Z-veto", 100,0,1500);
        createHistograms(h_eta1, "h_eta1", "Eta1", 25, -3, 3);
        createHistograms(h_eta1v, "h_eta1v", "Eta1 in Z-veto", 25, -3, 3);
        createHistograms(h_phi1, "h_phi1", "Phi1", 25, -3.5, 3.5);
        createHistograms(h_phi1v, "h_phi1v", "Phi1 in Z-veto", 25, -3.5, 3.5);
        createHistograms(h_pt2, "h_pt2", "pT2", 100,0,1500);
        createHistograms(h_pt2v, "h_pt2v", "pT2 in Z-veto", 100,0,1500);
        createHistograms(h_eta2, "h_eta2", "Eta2", 25, -3, 3);
        createHistograms(h_eta2v, "h_eta2v", "Eta2 in Z-veto", 25, -3, 3);
        createHistograms(h_phi2, "h_phi2", "Phi2", 25, -3.5, 3.5);
        createHistograms(h_phi2v, "h_phi2v", "Phi2 in Z-veto", 25, -3.5, 3.5);
        createHistograms(h_pt3, "h_pt3", "pT3", 100,0,1500);
        createHistograms(h_pt3v, "h_pt3v", "pT3 in Z-veto", 100,0,1500);
        createHistograms(h_eta3, "h_eta3", "Eta3", 25, -3, 3);
        createHistograms(h_eta3v, "h_eta3v", "Eta3 in Z-veto", 25, -3, 3);
        createHistograms(h_phi3, "h_phi3", "Phi3", 25, -3.5, 3.5);
        createHistograms(h_phi3v, "h_phi3v", "Phi3 in Z-veto", 25, -3.5, 3.5);
        createHistograms(h_pt4, "h_pt4", "pT4", 100,0,1500);
        createHistograms(h_pt4v, "h_pt4v", "pT4 in Z-veto", 100,0,1500);
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

			string cat_string = numberToCat(cat);
			char* cat_name = const_cast<char*>(cat_string.c_str());
			int Nlep = cat_lepCount(cat_name,'e','m'); 
			int Ntau = strlen(cat_name)-Nlep; 	
			if (cat <= 21  and q_1+q_2+q_3+q_4 != 0) continue;  

			double evtwt_nom = brWeight*Generator_weight;
						
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
				
			if( cat_string =="emt" ) fillHistograms(cat_string, h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, 0.0, met, 0.0, 0.0, leptons, evtwt_nom);
			else if( cat_string =="ett" and q_2 == -q_3) fillHistograms(cat_string, h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, 0.0, met, 0.0, 0.0, leptons, evtwt_nom);
			else if( cat_string =="mtt" and q_2 == -q_3) fillHistograms(cat_string, h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, 0.0, met, 0.0, 0.0, leptons, evtwt_nom);
				
			TLorentzVector MET;
			MET.SetPtEtaPhiM(met, 0, metphi, 0);
			
			if((Ntau == 1) and (gen_cat == 3 or gen_cat == 5 or gen_cat == 8 or gen_cat == 10 or gen_cat == 13 or gen_cat == 17)){
				cout<<deltaPhi(LepV(4), MET)*180/3.14<<endl;
			}
			
			std::vector<double> mZ, mZv, mH; 
			std::vector<int> Z_idx; 
			std::set<int> all_idx;
			for(int m = 1; m <= strlen(cat_name); ++m){
				all_idx.insert(m);
				for(int n = m+1; n <= strlen(cat_name); ++n){
					string pair_name = pairFunc(m,n,cat_name,20);
					//the vector elements are inv massses of highest pt pairs because we sotred the lepton vector by pt.
					if(pair_name=="Zwindow"){
						mZ.push_back((LepV(m)+LepV(n)).M());
						Z_idx.push_back(m);
						Z_idx.push_back(n);
					}
					else if(pair_name=="Zv") mZ.push_back((LepV(m)+LepV(n)).M());
					else if(pair_name=="DCH") mH.push_back((LepV(m)+LepV(n)).M());
					//else if(pair_name=="found nothing") cout<<"found nothing"<<endl;
					else continue;
				}
			}
			//std::sort(mH.begin(), mH.end(), [](double a, double b){return a > b;});
			double Wmt = 0;
			//if (mZ.size() >0 ) {
			if (cat > 39 and mH.size()>0) {
				//std::sort(mZ.begin(), mZ.end(), [](double a, double b){return a > b;});				
				//for(int idx : Z_idx){ all_idx.erase(idx);}
				//for(int unZ_idx : all_idx){Wmt = (LepV(unZ_idx)+MET).Mt();}
				if (cat_string== "ee") fillHistograms(cat_string, h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, 0, mH[0], leptons, evtwt_nom);
				else if (cat_string== "em") fillHistograms(cat_string, h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, 0, mH[0], leptons, evtwt_nom);
				else if (cat_string== "mm") fillHistograms(cat_string, h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, 0, mH[0], leptons, evtwt_nom); 
				else if (cat_string== "ete" or cat_string== "eet" or cat_string == "tee") fillHistograms("eet", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
				else if (cat_string== "mtm" or cat_string== "mmt" or cat_string == "tmm") fillHistograms("mmt", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom); 
				else if (cat_string== "eee") fillHistograms("eee", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
				else if (cat_string== "eme" or cat_string== "eem" or cat_string == "mee") fillHistograms("eem", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
				else if (cat_string== "emm" or cat_string== "mme" or cat_string == "mem") fillHistograms("emm", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
				else if( cat_string== "mmm" ) fillHistograms("mmm", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
					//if(mZ.size()<2) continue;
				else if( cat_string== "eeee" ) fillHistograms("eeee", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
				else if( cat_lepCount(cat_name,'e','g') == 3 and cat_lepCount(cat_name,'m','g') == 1 ) fillHistograms("eeem", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
				else if( cat_lepCount(cat_name,'e','g') == 2 and cat_lepCount(cat_name,'m','g') == 2 ) fillHistograms("eemm", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom); 
				else if( cat_lepCount(cat_name,'e','g') == 1 and cat_lepCount(cat_name,'m','g') == 3 ) fillHistograms("mmem", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
				else if( cat_string== "mmmm" ) fillHistograms("mmmm", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
				else if( cat_lepCount(cat_name,'e','g') == 3 and cat_lepCount(cat_name,'t','g') == 1 ) fillHistograms("eeet", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
				else if( cat_lepCount(cat_name,'e','g') == 2 and cat_lepCount(cat_name,'m','g') == 1 and cat_lepCount(cat_name,'t','g') == 1 ) fillHistograms("eemt", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
				else if( cat_lepCount(cat_name,'e','g') == 2 and cat_lepCount(cat_name,'t','g') == 2 ) fillHistograms("eett", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
				else if( cat_lepCount(cat_name,'e','g') == 1 and cat_lepCount(cat_name,'m','g') == 2 and cat_lepCount(cat_name,'t','g') == 1 ) fillHistograms("emmt", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'e','g') == 1 and cat_lepCount(cat_name,'m','g') == 1 and cat_lepCount(cat_name,'t','g') == 2 ) fillHistograms("emtt", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'e','g') == 1 and cat_lepCount(cat_name,'t','g') == 3 ) fillHistograms("ettt", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'m','g') == 3 and cat_lepCount(cat_name,'t','g') == 1 ) fillHistograms("mmmt", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'m','g') == 2 and cat_lepCount(cat_name,'t','g') == 2 ) fillHistograms("mmtt", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'m','g') == 1 and cat_lepCount(cat_name,'t','g') == 3 ) fillHistograms("mttt", h_mZ, h_mH, h_met,  h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_12dR, h_13dR, h_14dR, h_23dR, h_24dR, h_34dR, h_WMt, Wmt, met, mZ[0], mH[0], leptons, evtwt_nom);
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
					if (cat_string== "ee") fillHistograms(cat_string, h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], 0.0, leptons, evtwt_nom);
					else if (cat_string== "em") fillHistograms(cat_string, h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], 0.0, leptons, evtwt_nom);
					else if (cat_string== "mm") fillHistograms(cat_string, h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], 0.0, leptons, evtwt_nom); 
					else if (cat_string== "ete" or cat_string== "eet" or cat_string == "tee") fillHistograms("eet", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if (cat_string== "mtm" or cat_string== "mmt" or cat_string == "tmm") fillHistograms("mmt", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom); 
					else if (cat_string== "eee") fillHistograms("eee", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if (cat_string== "eme" or cat_string== "eem" or cat_string == "mee") fillHistograms("eem", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if (cat_string== "emm" or cat_string== "mme" or cat_string == "mem") fillHistograms("emm", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if( cat_string== "mmm" ) fillHistograms("mmm", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					//if(mZv.size()<2) continue;
					else if( cat_string== "eeee" ) fillHistograms("eeee", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'e','g') == 3 and cat_lepCount(cat_name,'m','g') == 1 ) fillHistograms("eeem", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'e','g') == 2 and cat_lepCount(cat_name,'m','g') == 2 ) fillHistograms("eemm", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom); 
					else if( cat_lepCount(cat_name,'e','g') == 1 and cat_lepCount(cat_name,'m','g') == 3 ) fillHistograms("mmem", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if( cat_string== "mmmm" ) fillHistograms("mmmm", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'e','g') == 3 and cat_lepCount(cat_name,'t','g') == 1 ) fillHistograms("eeet", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'e','g') == 2 and cat_lepCount(cat_name,'m','g') == 1 and cat_lepCount(cat_name,'t','g') == 1 ) fillHistograms("eemt", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'e','g') == 2 and cat_lepCount(cat_name,'t','g') == 2 ) fillHistograms("eett", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'e','g') == 1 and cat_lepCount(cat_name,'m','g') == 2 and cat_lepCount(cat_name,'t','g') == 1 ) fillHistograms("emmt", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'e','g') == 1 and cat_lepCount(cat_name,'m','g') == 1 and cat_lepCount(cat_name,'t','g') == 2 ) fillHistograms("emtt", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'e','g') == 1 and cat_lepCount(cat_name,'t','g') == 3 ) fillHistograms("ettt", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'m','g') == 3 and cat_lepCount(cat_name,'t','g') == 1 ) fillHistograms("mmmt", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'m','g') == 2 and cat_lepCount(cat_name,'t','g') == 2 ) fillHistograms("mmtt", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
					else if( cat_lepCount(cat_name,'m','g') == 1 and cat_lepCount(cat_name,'t','g') == 3 ) fillHistograms("mttt", h_mZv, h_mHv, h_metv,  h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v, h_12dRv, h_13dRv, h_14dRv, h_23dRv, h_24dRv, h_34dRv, h_WMtv, Wmt, met, mZv[0], mH[0], leptons, evtwt_nom);
				}
		}//evt loop 
		hNWEvts->Write();
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

