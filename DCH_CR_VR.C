//To apply various kinematics selections right after online analysis.
#include "TMath.h"
#include <cmath>
#include <vector>
#include "TH1D.h"
#include "TF1.h"
#include "TFile.h"
#include "include/MyBranch_FR_new.C"//#include "include/MyBranch.C"//branch definitons
#include "include/Kinematics.C"//Kine fns
//#include "include/MET_split.C"
#include "include/Xsections.C"


// Histogram creation utility to avoid code duplication
void createHistograms(std::map<std::string, TH1D*>& histograms,
                      const std::string& prefix,
                      const std::string& label,
                      int bins, double low, double high) {
    for (const std::string& channel : {"VR_0tau","VR_1tau","VR_2tau","VR_3tau","VR_3lep0tau","VR_3lep1tau","VR_3lep2tau",
	 "CR_0tau","CR_1tau","CR_2tau","CR_3tau","CR_3lep0tau","CR_3lep1tau","CR_3lep2tau",
	 "SR_0tau","SR_1tau","SR_2tau","SR_3tau","SR_3lep0tau","SR_3lep1tau","SR_3lep2tau",
	 "DYCR_0tau","DYCR_1tau","DYveto_0tau","DYveto_1tau",
	 "ee", "em", "mm", "eee", "eem", "eet", "emt", "mme", "mmm", "mmt",
	 "tte", "ttm", "eeee", "eeem", "eemm", "mmem", "mmmm", "eeet", "eemt",
	 "eett", "emmt", "ttem", "ttet", "mmmt", "mmtt", "ttmt", "v_ee", "v_em", "v_mm", "v_eee", "v_eem", "v_eet", "v_emt", "v_mme", "v_mmm", "v_mmt",
	 "v_tte", "v_ttm", "v_eeee", "v_eeem", "v_eemm", "v_mmem", "v_mmmm", "v_eeet", "v_eemt",
	 "v_eett", "v_emmt", "v_ttem", "v_ttet", "v_mmmt", "v_mmtt", "v_ttmt"}) {
        std::string hist_name = prefix + "_" + channel;
        std::string hist_label = label + " " + channel;
        
        histograms[channel] = new TH1D(hist_name.c_str(), hist_label.c_str(), bins, low, high);
        histograms[channel]->Sumw2(); // for proper error propagation
    }
}

void fillHistograms(const std::string& channel,
					std::map<std::string, TH1D*>& h_mZ1, 
					std::map<std::string, TH1D*>& h_mZ2,
					std::map<std::string, TH1D*>& h_mH1, 
					std::map<std::string, TH1D*>& h_mH2,
					std::map<std::string, TH1D*>& h_met,
					std::map<std::string, TH1D*>& h_LT, 
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
					double met,
					vector<pair<int, int>> OSSF_pair,
					vector<pair<int, int>> SS_pair,
                    double evtwt_nom) {
    h_met[channel]->Fill(met, evtwt_nom);
    h_LT[channel]->Fill(LepV(1).Pt()+LepV(2).Pt()+LepV(3).Pt()+LepV(4).Pt(), evtwt_nom);
	if (OSSF_pair.size()>0) {
		h_mZ1[channel]->Fill((LepV(OSSF_pair[0].first)+LepV(OSSF_pair[0].second)).M(), evtwt_nom);
		h_pt1[channel]->Fill(LepV(OSSF_pair[0].first).Pt(), evtwt_nom);
		h_pt2[channel]->Fill(LepV(OSSF_pair[0].second).Pt(), evtwt_nom);
		h_eta1[channel]->Fill(LepV(OSSF_pair[0].first).Eta(), evtwt_nom);
		h_eta2[channel]->Fill(LepV(OSSF_pair[0].second).Eta(), evtwt_nom);
		h_phi1[channel]->Fill(LepV(OSSF_pair[0].first).Phi(), evtwt_nom);
		h_phi2[channel]->Fill(LepV(OSSF_pair[0].second).Phi(), evtwt_nom);
    }
    if (OSSF_pair.size()>1) {
    	h_mZ2[channel]->Fill((LepV(OSSF_pair[1].first)+LepV(OSSF_pair[1].second)).M(), evtwt_nom);
    	h_pt3[channel]->Fill(LepV(OSSF_pair[1].first).Pt(), evtwt_nom);
    	h_pt4[channel]->Fill(LepV(OSSF_pair[1].second).Pt(), evtwt_nom);
    	h_eta3[channel]->Fill(LepV(OSSF_pair[1].first).Eta(), evtwt_nom);
		h_eta4[channel]->Fill(LepV(OSSF_pair[1].second).Eta(), evtwt_nom);
		h_phi3[channel]->Fill(LepV(OSSF_pair[1].first).Phi(), evtwt_nom);
		h_phi4[channel]->Fill(LepV(OSSF_pair[1].second).Phi(), evtwt_nom);
   	}
    if (SS_pair.size()>0) h_mH1[channel]->Fill((LepV(SS_pair[0].first)+LepV(SS_pair[0].second)).M(), evtwt_nom);
	if (SS_pair.size()>1) h_mH2[channel]->Fill((LepV(SS_pair[1].first)+LepV(SS_pair[1].second)).M(), evtwt_nom); 
    
}


void scaleAndWriteHistograms(std::map<std::string, TH1D*>& histograms, double xs_weight) {
    for (const std::string& channel : {"VR_0tau","VR_1tau","VR_2tau","VR_3tau","VR_3lep0tau","VR_3lep1tau","VR_3lep2tau",
	 "CR_0tau","CR_1tau","CR_2tau","CR_3tau","CR_3lep0tau","CR_3lep1tau","CR_3lep2tau",
	 "SR_0tau","SR_1tau","SR_2tau","SR_3tau","SR_3lep0tau","SR_3lep1tau","SR_3lep2tau",
	 "DYCR_0tau","DYCR_1tau","DYveto_0tau","DYveto_1tau",
	 "ee", "em", "mm", "eee", "eem", "eet", "emt", "mme", "mmm", "mmt",
	 "tte", "ttm", "eeee", "eeem", "eemm", "mmem", "mmmm", "eeet", "eemt",
	 "eett", "emmt", "ttem", "ttet", "mmmt", "mmtt", "ttmt", "v_ee", "v_em", "v_mm", "v_eee", "v_eem", "v_eet", "v_emt", "v_mme", "v_mmm", "v_mmt",
	 "v_tte", "v_ttm", "v_eeee", "v_eeem", "v_eemm", "v_mmem", "v_mmmm", "v_eeet", "v_eemt",
	 "v_eett", "v_emmt", "v_ttem", "v_ttet", "v_mmmt", "v_mmtt", "v_ttmt"}) {
        histograms[channel]->Scale(xs_weight);
        histograms[channel]->Write();
    }
}

void DCH_CR_VR(const char* ext = "root"){
	const char* inDir = ".";
	char* dir = gSystem->ExpandPathName(inDir);
	void* dirp = gSystem->OpenDirectory(dir);
	const char* entry;
	const char* filename[400];
	TString str; Int_t nfiles = 0;
	while((entry = (char*)gSystem->GetDirEntry(dirp))){
	  	str = entry;
	  	if(str.EndsWith(ext)){
			filename[nfiles++] = gSystem->ConcatFileName(dir, entry);
	  	}
	}
	gROOT->Reset();
	
	std::string selection = "test";

	double mDCH = 500.0, mZ = 91.2, lumi_2016 = 35900, lumi_2017 = 45000, lumi_2018 = 58900.0; //139000;
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		cout<<filename[j]<<endl;
		TFile *ifile = new TFile(filename[j],"READ");
		std::string fname = filename[j];
		if (fname.find("_2018.") > fname.length()) continue;
		//if (fname.find("EGa") > fname.length()) continue;
		//if (fname.find("ZZTo4L_2018") > fname.length()) continue;
		//if (XSec(filename[j])==1) continue; 
		
		//cout<<XSec(filename[j])<<endl;
		const char* o_name;
		TString base = gSystem->BaseName(fname.c_str());
		if (selection =="none") o_name = "hist";
		else if (selection =="Pre") o_name = "hist_MY";
		else if (selection =="APre") o_name = "hist_APre";
		else if (selection =="CR") o_name = "hist_CR";
		else if (selection =="VR") o_name = "hist_VR";
		else if (selection =="test") o_name = "hist_test_nopair_noFR";
		else cout<< "SELECTION NOT DEFINED!!!"<<endl;
		gSystem->mkdir(o_name, kTRUE);
		char *oname = gSystem->ConcatFileName(o_name, base);
		TFile* ofile = new TFile(oname, "RECREATE"); 
		
		TH1D* hNWEvts;
		if(XSec(fname)!=1) hNWEvts = (TH1D*)ifile->Get("hNWEvts")->Clone("hNWEvts");	
		if (!hNWEvts) hNWEvts = (TH1D*)ifile->Get("hNEvts")->Clone("hNWEvts");
		hNWEvts->Write();

		double xs_weight = 1.0;
		
		TTree *tree = (TTree*)ifile->Get("Events");
		MyBranch(tree);
		
		// Compact histogram creation
       std::map<std::string, TH1D*> h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4 ;
        
        createHistograms(h_mZ1, "h_mZ1", "mZ1", 5000,0,500);
        createHistograms(h_mZ2, "h_mZ2", "mZ2", 5000,0,500);
        createHistograms(h_mH1, "h_mH1", "mll1", 1000,0,1000);
        createHistograms(h_mH2, "h_mH2", "mll2", 1000,0,1000);
        createHistograms(h_met, "h_met", "MET", 100,0,500);
        createHistograms(h_LT, "h_LT", "LT", 1000,0,1000);
        createHistograms(h_pt1, "h_pt1", "pT1", 1000,0,500);
        createHistograms(h_eta1, "h_eta1", "Eta1", 1000, -3, 3);
        createHistograms(h_phi1, "h_phi1", "Phi1", 1000, -4, 4);
        createHistograms(h_pt2, "h_pt2", "pT2", 1000,0,250);
        createHistograms(h_eta2, "h_eta2", "Eta2", 1000, -3, 3);
        createHistograms(h_phi2, "h_phi2", "Phi2", 1000, -4, 4);
        createHistograms(h_pt3, "h_pt3", "pT3", 1000,0,250);
        createHistograms(h_eta3, "h_eta3", "Eta3", 1000, -3, 3);
        createHistograms(h_phi3, "h_phi3", "Phi3", 1000, -4, 4);
        createHistograms(h_pt4, "h_pt4", "pT4", 1000,0,250);
        createHistograms(h_eta4, "h_eta4", "Eta4", 1000, -3, 3);
        createHistograms(h_phi4, "h_phi4", "Phi4", 1000, -4, 4);
        
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
			else if (cat <= 39 and cat > 21 and abs(q_1+q_2+q_3) == 3) continue; 
			
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
			applyTauES(cat_string);
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
						/*if(Ntau != 0 or cat <= 39) continue;
						if (fname.find("2016") < fname.length()) {
							if (cat_string[1] == 'e') {
								if (pt_2 < 29) continue;
							} else {
								if (pt_2 < 26) continue;
							}
						}

						if (fname.find("2017") < fname.length()) {
							if (cat_string[1] == 'e') {
								if (pt_2 < 37) continue;
							} else {
								if (pt_2 < 29) continue;
							}
						}

						if (fname.find("2018") < fname.length()) {
							if (cat_string[1] == 'e') {
								if (pt_2 < 34) continue;
							} else {
								if (pt_2 < 26) continue;
							}
						}*/
			if (XSec(filename[j])!=1){
				evtwt_nom *= L1PreFiringWeight_Nom*weightPUtruejson;
				
				if(strlen(cat_name)<3){
					evtwt_nom *= IDSF_1*IDSF_2*ISOSF_1*ISOSF_2*TauVsEleIDSF_1*TauVsEleIDSF_2*TauVsMuIDSF_1*TauVsMuIDSF_2*TauVsJetIDSF_1*TauVsJetIDSF_2;
					if (TrigSF_1 !=1)
						evtwt_nom *= TrigSF_1;
					else if (TrigSF_2 !=1){
						evtwt_nom *= TrigSF_2;
					//cout<<evtwt_nom<<endl;
					}
					
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
				
				
				TLorentzVector MET;
				MET.SetPtEtaPhiM(met, 0, metphi, 0);
				double LT = LepV(1).Pt()+LepV(2).Pt()+LepV(3).Pt()+LepV(4).Pt();

				vector<pair<int, int>> Z_pair, Zv_pair, Ztt_pair, SS_pair;
				processPairs(cat_name, Z_pair, Zv_pair, Ztt_pair, SS_pair, Ztt_pair);//were putiing OSDF pairs in Ztt container for now.
				Zv_pair = removeOverlap(Zv_pair, strlen(cat_name));

				//don't remove duplicates in Zttpair yet as we'd lose et and mt too!
				//===============ordering leading pairs=====================
				std::sort(SS_pair.begin(), SS_pair.end(),[&](const std::pair<int,int>& a, const std::pair<int,int>& b){
					double pt_a = (LepV(a.first)  + LepV(a.second)).Pt();
					double pt_b = (LepV(b.first)  + LepV(b.second)).Pt();
					return pt_a > pt_b; // descending order of pt
				});
				
				std::sort(Z_pair.begin(), Z_pair.end(),[&](const std::pair<int,int>& a, const std::pair<int,int>& b){
					double pt_a = (LepV(a.first)  + LepV(a.second)).Pt();
					double pt_b = (LepV(b.first)  + LepV(b.second)).Pt();
					return pt_a > pt_b; // descending order of pt
				});
				
				std::sort(Zv_pair.begin(), Zv_pair.end(),[&](const std::pair<int,int>& a, const std::pair<int,int>& b){
					double pt_a = (LepV(a.first)  + LepV(a.second)).Pt();
					double pt_b = (LepV(b.first)  + LepV(b.second)).Pt();
					return pt_a > pt_b; // descending order of pt
				});
				std::sort(Ztt_pair.begin(), Ztt_pair.end(),[&](const std::pair<int,int>& a, const std::pair<int,int>& b){
					double pt_a = (LepV(a.first)  + LepV(a.second)).Pt();
					double pt_b = (LepV(b.first)  + LepV(b.second)).Pt();
					return pt_a > pt_b; // descending order of pt
				});				
				//===========================================================
				vector<pair<int, int>> OS_pair, OSSF_pair;
				OSSF_pair.insert(OSSF_pair.end(), Z_pair.begin(), Z_pair.end());
				OSSF_pair.insert(OSSF_pair.end(), Zv_pair.begin(), Zv_pair.end());
				OSSF_pair = removeOverlap(OSSF_pair, strlen(cat_name));

				OS_pair.insert(OS_pair.end(), OSSF_pair.begin(), OSSF_pair.end());
				OS_pair.insert(OS_pair.end(), Ztt_pair.begin(), Ztt_pair.end());
				OS_pair = removeOverlap(OS_pair, strlen(cat_name));

				std::unordered_set<std::string> histCh = {"VR_0tau","VR_1tau","VR_2tau","VR_3tau","VR_3lep0tau","VR_3lep1tau","VR_3lep2tau",
	 "CR_0tau","CR_1tau","CR_2tau","CR_3tau","CR_3lep0tau","CR_3lep1tau","CR_3lep2tau",
	 "SR_0tau","SR_1tau","SR_2tau","SR_3tau","SR_3lep0tau","SR_3lep1tau","SR_3lep2tau",
	 "DYCR_0tau","DYCR_1tau","DYveto_0tau","DYveto_1tau",
	 "ee", "em", "mm", "eee", "eem", "eet", "emt", "mme", "mmm", "mmt",
	 "tte", "ttm", "eeee", "eeem", "eemm", "mmem", "mmmm", "eeet", "eemt",
	 "eett", "emmt", "ttem", "ttet", "mmmt", "mmtt", "ttmt", "v_ee", "v_em", "v_mm", "v_eee", "v_eem", "v_eet", "v_emt", "v_mme", "v_mmm", "v_mmt",
	 "v_tte", "v_ttm", "v_eeee", "v_eeem", "v_eemm", "v_mmem", "v_mmmm", "v_eeet", "v_eemt",
	 "v_eett", "v_emmt", "v_ttem", "v_ttet", "v_mmmt", "v_mmtt", "v_ttmt"};//makes lookup faster!!
				

				std::string channel = classifyTauRegion(cat_name, LT, OS_pair);	
				//if (channel == "CR_2tau") cout<<cat_name<<"\t"<< OS_pair.size() <<"\t"<< OSSF_pair.size() <<"\t"<< Z_pair.size() <<"\t"<< Ztt_pair.size() <<endl;
				if(!histCh.count(channel)) continue;
				fillHistograms(channel, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OS_pair, SS_pair, evtwt_nom);//fills all the tau channels
				
				/*if( cat_string =="emt" ) fillHistograms(cat_string, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OSSF_pair, SS_pair, evtwt_nom);
				else if( cat_string =="ett" and q_2 == -q_3) fillHistograms(cat_string, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OSSF_pair, SS_pair, evtwt_nom);
				else if( cat_string =="mtt" and q_2 == -q_3) fillHistograms(cat_string, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OSSF_pair, SS_pair, evtwt_nom);*/
				
				std::string channel1 = classifyLepRegion(cat_name, OS_pair);
				if (channel1=="mmee") channel1 = "eemm";
				if (channel1=="mmee") channel1 = "eemm";
				
				if(!histCh.count(channel1)) continue;
				
				if (Z_pair.size() == 1){//fills DY and WZ CRs
					if (strlen(cat_name)==3 and !(met>=40)) continue; //for WZ CR
					fillHistograms(channel1, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OS_pair, SS_pair, evtwt_nom);
				}
				if(Z_pair.size() ==2){//fills ZZ CR.
					fillHistograms(channel1, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OS_pair, SS_pair, evtwt_nom);
				}
				else if (Zv_pair.size() > 0 and Z_pair.size()==0){//fills Veto Regions
					channel1 = "v_"+channel1;
					fillHistograms(channel1, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OS_pair, SS_pair, evtwt_nom);
				}
			}//selections loop
		}//evt loop 
		//hNWEvts->Write();
		scaleAndWriteHistograms(h_mZ1, xs_weight);
		scaleAndWriteHistograms(h_mH1, xs_weight);
		scaleAndWriteHistograms(h_mZ2, xs_weight);
		scaleAndWriteHistograms(h_mH2, xs_weight);
		scaleAndWriteHistograms(h_met, xs_weight);
		scaleAndWriteHistograms(h_LT, xs_weight);
		scaleAndWriteHistograms(h_pt1, xs_weight);
		scaleAndWriteHistograms(h_pt2, xs_weight);
		scaleAndWriteHistograms(h_pt3, xs_weight);
		scaleAndWriteHistograms(h_pt4, xs_weight);
		scaleAndWriteHistograms(h_eta1, xs_weight);
		scaleAndWriteHistograms(h_eta2, xs_weight);
		scaleAndWriteHistograms(h_eta3, xs_weight);
		scaleAndWriteHistograms(h_eta4, xs_weight);
		scaleAndWriteHistograms(h_phi1, xs_weight);
		scaleAndWriteHistograms(h_phi2, xs_weight);
		scaleAndWriteHistograms(h_phi3, xs_weight);
		scaleAndWriteHistograms(h_phi4, xs_weight);
		delete tree;
	}
	gSystem->FreeDirectory(dirp);
}


