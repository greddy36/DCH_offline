//To apply various kinematics selections right after online analysis.
#include "TMath.h"
#include <cmath>
#include <vector>
#include "TH1D.h"
#include "TF1.h"
#include "TFile.h"
#include "include/MyBranch_FR_new.C"//branch definitons
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
 "ee", "em", "mm", "eee", "eem", "eet", "emt", "emm", "mmm", "mmt",
 "ett", "mtt", "eeee", "eeem", "eemm", "mmem", "mmmm", "eeet", "eemt",
 "eett", "emmt", "emtt", "ettt", "mmmt", "mmtt", "mttt", "v_ee", "v_em", "v_mm", "v_eee", "v_eem", "v_eet", "v_emt", "v_emm", "v_mmm", "v_mmt",
	 "v_ett", "v_mtt", "v_eeee", "v_eeem", "v_eemm", "v_mmem", "v_mmmm", "v_eeet", "v_eemt",
	 "v_eett", "v_emmt", "v_emtt", "v_ettt", "v_mmmt", "v_mmtt", "v_mttt"}) {
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
					std::map<std::string, TH1D*>& h_dRll,
					std::map<std::string, TH1D*>& h_mT,
					double met, double mT,
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
		h_dRll[channel]->Fill(deltaR(LepV(OSSF_pair[0].first),LepV(OSSF_pair[0].second)), evtwt_nom);
		h_mT[channel]->Fill(mT, evtwt_nom);
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
 "ee", "em", "mm", "eee", "eem", "eet", "emt", "emm", "mmm", "mmt",
 "ett", "mtt", "eeee", "eeem", "eemm", "mmem", "mmmm", "eeet", "eemt",
 "eett", "emmt", "emtt", "ettt", "mmmt", "mmtt", "mttt", "v_ee", "v_em", "v_mm", "v_eee", "v_eem", "v_eet", "v_emt", "v_emm", "v_mmm", "v_mmt",
	 "v_ett", "v_mtt", "v_eeee", "v_eeem", "v_eemm", "v_mmem", "v_mmmm", "v_eeet", "v_eemt",
	 "v_eett", "v_emmt", "v_emtt", "v_ettt", "v_mmmt", "v_mmtt", "v_mttt"}) {
        histograms[channel]->Scale(xs_weight);
        histograms[channel]->Write();
    }
}

class loadFR_Data2D{
public:
	loadFR_Data2D(const TString fileName, const std::string year, const std::string lepFlav){//loads FR histograms
		//TString fileName = "Data_fake_tau_rates.root";
		   
		TFile* frFile = TFile::Open(fileName);
		if (!frFile || frFile->IsZombie()) {
		    std::cerr << "ERROR: cannot open DATA 2D FR file "
		              << fileName << std::endl;
		    exit(1);
		}
		
		//TString hName = Form("Data_%s_fake_rates", year.c_str());
		TString hName = Form("Data_%s_%s_fake_rate", year.c_str(), lepFlav.c_str());

		TH2D* h_fr = (TH2D*)frFile->Get(hName);
		if (!h_fr) {
		    std::cerr << "ERROR: missing DATA 2D FR histogram for tau:\n" 
		    		  << hName << std::endl;
		    exit(1);
		}

		FR_hist = (TH2D*)h_fr->Clone(Form("%s_clone", hName.Data()));
		FR_hist->SetDirectory(0);
		frFile->Close();

		cout << "[FR][DATA 2D] loaded for "<< lepFlav<<"\t"<< hName <<endl;

	}
	/*~loadFR_Data2D() {
        delete FR_hist;
    }*/
    
	double getFR(double pt, double eta){
		if (!FR_hist) {
            std::cerr << "ERROR: FR_hist is null in getFR()" << std::endl;
            return 0.0;
        }
		double f = 1.0; 
		
		if (pt < 20) pt = 20.01;
		else if (pt > 200) pt = 199.9;
		
		if (abs(eta) > 2.5) eta = 2.45;
		
		const int bin2D = FR_hist->FindBin(pt, eta);
		f = FR_hist->GetBinContent(bin2D);
			
		return f;
	}
	
private:
    TH2* FR_hist = nullptr;//must be here, outside constructor/getFR
};


std::vector<std::vector<int>> generateStates(int nLoose, int maxSlots = 3, bool includeEmpty = true) {
				std::vector<std::vector<int>> states;
				std::vector<int> state(nLoose, 0);

				auto backtrack = [&](auto&& self, int start, int placed) -> void {
					if (includeEmpty || placed > 0) {
						states.push_back(state);
					}

					if (placed == maxSlots) return;

					for (int i = start; i < nLoose; ++i) {
						state[i] = 1; //object i leaves rack, placed in slot
						self(self, i + 1, placed + 1);
						state[i] = 0; //undo
					}
				};

				backtrack(backtrack, 0, 0);
				return states;
}

void DCH_CR_VR_test(const char* ext = "root"){
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
	
	std::string selection = "test";

	double mDCH = 500.0, mZ = 91.2, lumi_2016 = 35900, lumi_2017 = 45000, lumi_2018 = 58900.0; //139000;
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		cout<<filename[j]<<endl;
		TFile *ifile = new TFile(filename[j],"READ");
		std::string fname = filename[j];
		
		std::string year = "";
		if (fname.find("_2016pre") < fname.length()) year = "2016preVFP";
		else if (fname.find("_2016post") < fname.length()) year = "2016postVFP";
		else if (fname.find("_2017") < fname.length()) year = "2017";
		else if (fname.find("_2018") < fname.length()) year = "2018";
		if (year == "2016") continue;
		
		//if (fname.find("WJetsToLNu_NLO_2018") > fname.length()) continue;
		//if (fname.find("HppM1000_2018") > fname.length()) continue;
		//if (fname.find("ZZTo4L") > fname.length()) continue;
		//if (XSec(filename[j])==1) continue; 
		
		//cout<<XSec(filename[j])<<endl;
		const char* o_name;
		if (selection =="none") o_name = "hist";
		else if (selection =="Pre") o_name = "hist_MY";
		else if (selection =="APre") o_name = "hist_APre";
		else if (selection =="CR") o_name = "hist_CR";
		else if (selection =="VR") o_name = "hist_VR";
		else if (selection =="test") o_name = "hist_test_nopair_DY";
		else cout<< "SELECTION NOT DEFINED!!!"<<endl;
		char *oname = gSystem->ConcatFileName(o_name, filename[j]);
		TFile* ofile = new TFile(oname, "RECREATE"); 
		
		TH1D* hNWEvts;
		if(XSec(fname)!=1) hNWEvts = (TH1D*)ifile->Get("hNWEvts")->Clone("hNWEvts");	
		if (!hNWEvts) hNWEvts = (TH1D*)ifile->Get("hNEvts")->Clone("hNWEvts");
		hNWEvts->Write();
		double xs_weight = 1.0;
		
		TTree *tree = (TTree*)ifile->Get("Events");
		MyBranch(tree);
		
		// Compact histogram creation
       std::map<std::string, TH1D*> h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dRll, h_mT ;
        
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
        createHistograms(h_dRll, "h_dRll", "dRll", 1000, 0, 4);
        createHistograms(h_mT, "h_mT", "mT", 1000,0,500);
        
        //Loading FR histograms
        loadFR_Data2D tauFR("Data_fake_rates_combined.root", year, "tau");
        loadFR_Data2D muFR("Data_fake_rates_combined.root", year, "muon");
        loadFR_Data2D eleFR("Data_fake_rates_combined.root", year, "electron");
        
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
			/*bool veto = false; 
			for (int tidx =0; tidx <=cat_string.size(); tidx++){
				if (cat_string[tidx] != 't') continue;
				if (tidx == 0 and genPartFlav_1 != 5) veto = true;
				else if (tidx == 1 and genPartFlav_2 != 5) veto = true;
				else if (tidx == 2 and genPartFlav_3 != 5) veto = true;
				else if (tidx == 3 and genPartFlav_4 != 5) veto = true;
			}if (veto) continue;*/
			
			else if (cat <= 39 and cat > 21 and abs(q_1+q_2+q_3) == 3) continue; 
			//if (cat_string.size()!=2) continue;
			//if (Ntau != 0) continue;
			//if (Nlep == 0) continue;
			//if (cat_name != "mmt") continue;

			//cout<<"BEFORE"<<"\t"<<q_1<<"\t"<<q_2<<"\t"<<q_3<<"\t"<<q_4<<"\t"<<cat_name<<endl;			
			// (strlen(cat_name) == 3 and (abs(q_1+q_2+q_3)!=1 or abs(q_1) !=1 or abs(q_2) != 1 or abs(q_3)!=1))continue;
			// (strlen(cat_name) == 4 and (abs(q_1+q_2+q_3+q_4)!=0 or abs(q_1) !=1 or abs(q_2) != 1 or abs(q_3)!=1 or abs(q_4)!=1))continue;
			
			double evtwt_nom = brWeight*Generator_weight;
			if (year=="2018"){//HEM veto
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
					//cout<<cat_name<<"\t"<<TrigSF_1<<"\t"<<TrigSF_2<<endl;
					//cout<<pt_1<<"\t"<<pt_2<<endl;
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
			
			int nLooseObj = 0;//nLooseElectron+nLooseMuon+nLooseTau;
			if (lpt !=nullptr) nLooseObj = lpt->size();
			//std::cout << "lpt size = " << lpt->size() << std::endl;
			//if (cat_string.size() <2)continue;
			//if (nLooseObj < 2) continue;
						
			double fr[nLooseObj];
			int l_idx[nLooseObj]; int ilt = 0;
			for(int il = 0; il < nLooseObj; il++){//cout<<evtwt_nom<<"\t";
				if (abs(lflavor->at(il)) == 15) {
					fr[ilt] = tauFR.getFR(lpt->at(il), leta->at(il));
				}
				else if (abs(lflavor->at(il)) == 11) {
					fr[ilt] = eleFR.getFR(lpt->at(il), leta->at(il));
				}
				else if (abs(lflavor->at(il)) == 13) {
					fr[ilt] = muFR.getFR(lpt->at(il), leta->at(il));
				}
				l_idx[ilt] = il;
				cout<<nLooseObj<<"\t"<<l_idx[ilt]<<"\t"<<ilt<<"\t"<<il<<endl;
				ilt++;
			}
			
			auto loose_states = generateStates(nLooseObj, 4-cat_string.size(), true);
			

			auto fillSlot = [&](int catsize, int idx) {
				int slot = catsize+1; //slot is the emtpy index after last lepton in cat_string
				switch (slot) {
					case 2:  // cat_string already has 1 object -> fill lepton 2
						pt_2  = lpt->at(idx);
						eta_2 = leta->at(idx);
						phi_2 = lphi->at(idx);
						m_2   = lmass->at(idx);
						q_2   = lq->at(idx);
						d0_2  = ld0->at(idx);
						dZ_2  = ldZ->at(idx);
						iso_2 = liso->at(idx);
						
						pt_3  = -99;
						eta_3 = -99;
						phi_3 = -99;
						m_3   = -99;
						q_3   = -99;
						d0_3  = -99;
						dZ_3  = -99;
						iso_3 = -99;
						
						pt_4  = -99;
						eta_4 = -99;
						phi_4 = -99;
						m_4   = -99;
						q_4   = -99;
						d0_4  = -99;
						dZ_4  = -99;
						iso_4 = -99;
						break;

					case 3:  // fill lepton 3
						pt_3  = lpt->at(idx);
						eta_3 = leta->at(idx);
						phi_3 = lphi->at(idx);
						m_3   = lmass->at(idx);
						q_3   = lq->at(idx);
						d0_3  = ld0->at(idx);
						dZ_3  = ldZ->at(idx);
						iso_3 = liso->at(idx);
						
						pt_4  = -99;
						eta_4 = -99;
						phi_4 = -99;
						m_4   = -99;
						q_4   = -99;
						d0_4  = -99;
						dZ_4  = -99;
						iso_4 = -99;
						break;

					case 4:  // fill lepton 4
						pt_4  = lpt->at(idx);
						eta_4 = leta->at(idx);
						phi_4 = lphi->at(idx);
						m_4   = lmass->at(idx);
						q_4   = lq->at(idx);
						d0_4  = ld0->at(idx);
						dZ_4  = ldZ->at(idx);
						iso_4 = liso->at(idx);
						break;

					default:
						std::cerr << "ERROR: invalid tau slot " << slot << std::endl;
						break;
				}
			};
			
			for(int istate = 0; istate < loose_states.size(); istate++){//FR application loop
				double evtwt_fr = evtwt_nom;
				std::string newCat = cat_string;
				for(int jpos = 0; jpos < loose_states[istate].size(); jpos++){
					if(loose_states[istate][jpos]==1){
						evtwt_fr *= fr[jpos];
						fillSlot(newCat.size(), l_idx[jpos]);
						if (abs(lflavor->at(jpos))==11) newCat += "e";
						else if (abs(lflavor->at(jpos))==13) newCat += "m";
						else if (abs(lflavor->at(jpos))==15) newCat += "t";
					}
					else if(loose_states[istate][jpos]==0){
						evtwt_fr *= 1-fr[jpos]; 
					}
				}
					
				cat_name = const_cast<char*>(newCat.c_str());
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
cout<<newCat<<"\t"<<cat_name<<"\t"<<pt_1<<"\t"<<pt_2<<"\t"<<pt_3<<"\t"<<pt_4<<"\t"<<evtwt_fr<<endl;
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
	 "ee", "em", "mm", "eee", "eem", "eet", "emt", "emm", "mmm", "mmt",
	 "ett", "mtt", "eeee", "eeem", "eemm", "mmem", "mmmm", "eeet", "eemt",
	 "eett", "emmt", "emtt", "ettt", "mmmt", "mmtt", "mttt", "v_ee", "v_em", "v_mm", "v_eee", "v_eem", "v_eet", "v_emt", "v_emm", "v_mmm", "v_mmt",
	 "v_ett", "v_mtt", "v_eeee", "v_eeem", "v_eemm", "v_mmem", "v_mmmm", "v_eeet", "v_eemt",
	 "v_eett", "v_emmt", "v_emtt", "v_ettt", "v_mmmt", "v_mmtt", "v_mttt"};//makes lookup faster!!
				
				
				std::string channel = classifyTauRegion(cat_name, LT, OS_pair);
				//if (channel == "CR_2tau") cout<<cat_name<<"\t"<< OS_pair.size() <<"\t"<< OSSF_pair.size() <<"\t"<< Z_pair.size() <<"\t"<< Ztt_pair.size() <<endl;
				if(!histCh.count(channel)) continue;

				fillHistograms(channel, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, h_dRll,h_mT, met,0, OS_pair, SS_pair, evtwt_fr);//fills all the tau channels
				
				/*if( cat_string =="emt" ) fillHistograms(cat_string, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OSSF_pair, SS_pair, evtwt_fr);
				else if( cat_string =="ett" and q_2 == -q_3) fillHistograms(cat_string, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OSSF_pair, SS_pair, evtwt_fr);
				else if( cat_string =="mtt" and q_2 == -q_3) fillHistograms(cat_string, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OSSF_pair, SS_pair, evtwt_fr);*/
				
				std::string channel1 = classifyLepRegion(cat_name, OS_pair);

				//if (Z_pair.size()>1 and (LepV(Z_pair[1].first)+LepV(Z_pair[1].second)).M() > 102) {
				//cout<<cat_name<<"\t"<<channel1<<(LepV(Z_pair[1].first)+LepV(Z_pair[1].second)).M()<<"\t"<<Z_pair.size()<<"\t"<<Zv_pair.size()<<endl;
					//for (auto a:Z_pair) cout<<a.first<<"\t"<<a.second<<endl;}
				if(!histCh.count(channel1)) continue;
				
				if (Z_pair.size() == 1){//fills DY and WZ CRs
					double mT = (LepV(Z_pair[0].first)+LepV(Z_pair[0].second) + MET).Mt();
					if (strlen(cat_name)==3 and !(met>=40)) continue; //for WZ CR
					fillHistograms(channel1, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4,h_dRll,h_mT, met, mT, OS_pair, SS_pair, evtwt_fr);
				}
				/*if(Z_pair.size() ==2){//fills ZZ CR.
					fillHistograms(channel1, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, mT, OS_pair, SS_pair, evtwt_fr);
				}
				else if (Zv_pair.size() > 0 and Z_pair.size()==0){//fills Veto Regions
					channel1 = "v_"+channel1;
					fillHistograms(channel1, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met,mT, OS_pair, SS_pair, evtwt_fr);
				}*/
			}//FR application loop
		}//evt loop 
		ofile->cd();
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
		scaleAndWriteHistograms(h_dRll, xs_weight);
		scaleAndWriteHistograms(h_mT, xs_weight);
		delete tree;
		
		ofile->Close();
		delete ofile;

		ifile->Close();
		delete ifile;
	}
	gSystem->FreeDirectory(dirp);
}


