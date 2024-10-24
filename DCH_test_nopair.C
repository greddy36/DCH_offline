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
		//std::cout<<"DON'T KNOW X-SEC FOR FILE "<<fname<<endl;
		return 0;
	}
}

std::string getCatName(int index) {
    std::vector<std::string> catNames = {
        "eeee", "eeem", "eeet", "eemm", "eemt", "eett",
        "emem", "emet", "emmm", "emmt", "emtt",
        "etet", "etmm", "etmt", "ettt",
        "mmmm", "mmmt", "mmtt",
        "mtmt", "mttt",
        "tttt",
        "eee", "eem", "eet",
        "eme", "emm", "emt",
        "ete", "etm", "ett",
        "mme", "mmm", "mmt",
        "mte", "mtm", "mtt",
        "tte", "ttm", "ttt",
        "ee","em","et","mm","mt","tt"
    };

    // Check if the index is within the valid range
    if (index < 1 || index > catNames.size()) {
        return "Invalid index";
    }

    // Return the corresponding cat name
    return catNames[index - 1];
}

// Histogram creation utility to avoid code duplication
void createHistograms(std::vector<TH1F*>& histograms, const std::string& prefix, const std::string& label, int bins, float low, float high) {
    for (int i = 0; i <= 13; i++) {
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

	float mDCH = 500, mZ = 91.2, lumi_2018 = 58900;//139000;
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		TH1D* hnevts = (TH1D*)ifile->Get("hNEvts");
		double xs_weight = 1;
		if(XSec(filename[j])!=1) xs_weight = lumi_2018*XSec(filename[j])/hnevts->Integral();
		
		std::string fname = filename[j];
		//if (fname.find("DY") > fname.length()) continue;
		
		//cout<<filename[j]<<endl;
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
        std::vector<TH1F*> h_mZ, h_mZv, h_mH, h_mHv, h_met, h_metv, h_pt1, h_pt2, h_pt3, h_pt4, h_pt1v, h_pt2v, h_pt3v, h_pt4v, h_eta1, h_eta2, h_eta3, h_eta4, h_eta1v, h_eta2v, h_eta3v, h_eta4v, h_phi1, h_phi2, h_phi3, h_phi4, h_phi1v, h_phi2v, h_phi3v, h_phi4v, h_dxy1, h_dxy2, h_dxy3, h_dxy4, h_dZ1, h_dZ2, h_dZ3, h_dZ4, h_iso1, h_iso2, h_iso3, h_iso4, h_dxy1v, h_dxy2v, h_dxy3v, h_dxy4v, h_dZ1v, h_dZ2v, h_dZ3v, h_dZ4v, h_iso1v, h_iso2v, h_iso3v, h_iso4v;
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
        
        
		for (int i =0; i < tree->GetEntries(); i++){
			tree->GetEntry(i);			
			float *lep_pt, *tau_pt;
			string cat_string = getCatName(cat);
			char* cat_name = const_cast<char*>(cat_string.c_str());
			int Nlep = cat_lepCount(cat_name,'e','m'); 
			int Ntau = strlen(cat_name)-Nlep; 	
			if (cat <= 21  and q_1+q_2+q_3+q_4 != 0) continue; 
			if (Ntau != 0) continue;
			//cout<<"BEFORE"<<"\t"<<q_1<<"\t"<<q_2<<"\t"<<q_3<<"\t"<<q_4<<"\t"<<cat_name<<endl;			
			// (strlen(cat_name) == 3 and (abs(q_1+q_2+q_3)!=1 or abs(q_1) !=1 or abs(q_2) != 1 or abs(q_3)!=1))continue;
			// (strlen(cat_name) == 4 and (abs(q_1+q_2+q_3+q_4)!=0 or abs(q_1) !=1 or abs(q_2) != 1 or abs(q_3)!=1 or abs(q_4)!=1))continue;
			
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
				//evtwt_nom = IDSF_1*IDSF_2*ISOSF_1*ISOSF_2*weightPUtruejson*TrigSF_1;
			}//cout<<evtwt_nom<< filename[j]<<endl;		 			

			if(selection == "test"){//My tests
				bool foundDup = false;
				std::vector<Lepton> leptons = {
					Lepton(pt_1, eta_1, phi_1, m_1, q_1, d0_1, dZ_1, iso_1),
					Lepton(pt_2, eta_2, phi_2, m_2, q_2, d0_2, dZ_2, iso_2),
					Lepton(pt_3, eta_3, phi_3, m_3, q_3, d0_3, dZ_3, iso_3),
					Lepton(pt_4, eta_4, phi_4, m_4, q_4, d0_4, dZ_4, iso_4),
				};
				for (int w = 0; w < 4 && !foundDup; ++w) {
					for (int x = w + 1; x < 4; ++x) {
						if (isDuplicate(leptons[w], leptons[x])){
						foundDup = true;
						//cout<<leptons[w].mass <<"\t"<< leptons[w].pt <<"\t"<<leptons[w].eta <<"\t"<< leptons[w].phi<<endl;
						//cout<<leptons[x].mass <<"\t"<< leptons[x].pt <<"\t"<<leptons[x].eta <<"\t"<< leptons[x].phi<<endl;
						//cout<<cat<<" xx"<<endl;
						break;
						}
					}
				}
				if (foundDup == true and strlen(cat_name)>2) continue;
				// Sort the lepton variables in descending order based on pt
				std::sort(leptons.begin(), leptons.end(), [](const Lepton& a, const Lepton& b) {
					return a.pt > b.pt;
				});

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
				float mll_1=-99, mll_2=-99, mllt_2=-99;
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

				std::vector<float> mZ, mZv, mH;
				for(int m = 1; m <= 4; ++m){
					for(int n = m+1; n <=4; ++n){
						string pair_name = pairFunc(m,n,cat_name,20);
						if(pair_name=="Z") mZ.push_back((LepV(m)+LepV(n)).M());
						else if(pair_name=="Zv") mZv.push_back((LepV(m)+LepV(n)).M());
						else if(pair_name=="DCH") mH.push_back((LepV(m)+LepV(n)).M());
						else continue;
					}
				}
				
				std::sort(mH.begin(), mH.end(), [](float a, float b) {
						return a > b;
				});
				if (mZ.size() !=0 ) {
					std::sort(mZ.begin(), mZ.end(), [](float a, float b) {
						return a > b;
					});
					if (cat_string== "ee"){ 
						//cout<<brWeight<<"\t"<<evtwt_nom<<endl;
						h_mZ[11]->Fill(mZ[0], brWeight*evtwt_nom);
						h_mH[11]->Fill(mH[0], brWeight*evtwt_nom);
						h_met[11]->Fill(met, brWeight*evtwt_nom);
						h_pt1[11]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2[11]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3[11]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4[11]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1[11]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2[11]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3[11]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4[11]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1[11]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2[11]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3[11]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4[11]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1[11]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2[11]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3[11]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4[11]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1[11]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2[11]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3[11]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4[11]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1[11]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2[11]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3[11]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4[11]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if (cat_string== "em"){ 
						//cout<<cat_name<<"\t"<<abs((L1+L3).M()-mZ)<<endl;
						h_mZ[12]->Fill(mZ[0], brWeight*evtwt_nom);
						h_mH[12]->Fill(mH[0], brWeight*evtwt_nom);
						h_met[12]->Fill(met, brWeight*evtwt_nom);
						h_pt1[12]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2[12]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3[12]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4[12]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1[12]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2[12]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3[12]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4[12]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1[12]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2[12]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3[12]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4[12]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1[12]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2[12]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3[12]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4[12]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1[12]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2[12]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3[12]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4[12]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1[12]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2[12]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3[12]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4[12]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if (cat_string== "mm"){ 
						//cout<<cat_name<<"\t"<<abs((L1+L3).M()-mZ)<<endl;
						h_mZ[13]->Fill(mZ[0], brWeight*evtwt_nom);
						h_mH[13]->Fill(mH[0], brWeight*evtwt_nom);
						h_met[13]->Fill(met, brWeight*evtwt_nom);
						h_pt1[13]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2[13]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3[13]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4[13]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1[13]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2[13]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3[13]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4[13]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1[13]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2[13]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3[13]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4[13]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1[13]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2[13]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3[13]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4[13]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1[13]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2[13]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3[13]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4[13]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1[13]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2[13]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3[13]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4[13]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if (cat_string== "eee"){ 
						//cout<<cat_name<<"\t"<<abs((L1+L3).M()-mZ)<<endl;
						h_mZ[1]->Fill(mZ[0], brWeight*evtwt_nom);
						h_mH[1]->Fill(mH[0], brWeight*evtwt_nom);
						h_met[1]->Fill(met, brWeight*evtwt_nom);
						h_pt1[1]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2[1]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3[1]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4[1]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1[1]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2[1]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3[1]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4[1]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1[1]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2[1]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3[1]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4[1]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1[1]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2[1]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3[1]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4[1]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1[1]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2[1]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3[1]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4[1]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1[1]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2[1]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3[1]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4[1]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if ((cat_string== "eme" or cat_string== "eem" or cat_string == "mee")){ 
						h_mZ[2]->Fill(mZ[0], brWeight*evtwt_nom);
						h_mH[2]->Fill(mH[0], brWeight*evtwt_nom);
						h_met[2]->Fill(met, brWeight*evtwt_nom);
						h_pt1[2]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2[2]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3[2]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4[2]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1[2]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2[2]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3[2]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4[2]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1[2]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2[2]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3[2]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4[2]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1[2]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2[2]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3[2]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4[2]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1[2]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2[2]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3[2]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4[2]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1[2]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2[2]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3[2]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4[2]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if ((cat_string== "emm" or cat_string== "mme" or cat_string == "mem") ){ 
						h_mZ[3]->Fill(mZ[0], brWeight*evtwt_nom);
						h_mH[3]->Fill(mH[0], brWeight*evtwt_nom);
						h_met[3]->Fill(met, brWeight*evtwt_nom);
						h_pt1[3]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2[3]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3[3]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4[3]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1[3]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2[3]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3[3]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4[3]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1[3]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2[3]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3[3]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4[3]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1[3]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2[3]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3[3]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4[3]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1[3]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2[3]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3[3]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4[3]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1[3]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2[3]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3[3]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4[3]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if( cat_string== "mmm" ){ 
						h_mZ[4]->Fill(mZ[0], brWeight*evtwt_nom);
						h_mH[4]->Fill(mH[0], brWeight*evtwt_nom);
						h_met[4]->Fill(met, brWeight*evtwt_nom);
						h_pt1[4]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2[4]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3[4]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4[4]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1[4]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2[4]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3[4]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4[4]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1[4]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2[4]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3[4]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4[4]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1[4]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2[4]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3[4]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4[4]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1[4]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2[4]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3[4]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4[4]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1[4]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2[4]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3[4]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4[4]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					if(mZ.size()<2) continue;
					if( cat_string== "eeee" ){ 
						h_mZ[5]->Fill(mZ[0], brWeight*evtwt_nom);
						h_mH[5]->Fill(mH[0], brWeight*evtwt_nom);
						h_met[5]->Fill(met, brWeight*evtwt_nom);
						h_pt1[5]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2[5]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3[5]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4[5]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1[5]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2[5]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3[5]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4[5]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1[5]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2[5]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3[5]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4[5]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1[5]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2[5]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3[5]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4[5]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1[5]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2[5]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3[5]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4[5]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1[5]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2[5]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3[5]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4[5]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if( cat_lepCount(cat_name,'e','g') == 3 and cat_lepCount(cat_name,'m','g') == 1 ){ 
						h_mZ[6]->Fill(mZ[0], brWeight*evtwt_nom);
						h_mH[6]->Fill(mH[0], brWeight*evtwt_nom);
						h_met[6]->Fill(met, brWeight*evtwt_nom);
						h_pt1[6]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2[6]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3[6]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4[6]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1[6]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2[6]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3[6]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4[6]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1[6]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2[6]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3[6]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4[6]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1[6]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2[6]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3[6]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4[6]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1[6]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2[6]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3[6]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4[6]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1[6]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2[6]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3[6]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4[6]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if( cat_lepCount(cat_name,'e','g') == 2 and cat_lepCount(cat_name,'m','g') == 2 ){ 
						h_mZ[7]->Fill(mZ[0], brWeight*evtwt_nom);
						h_mH[7]->Fill(mH[0], brWeight*evtwt_nom);
						h_met[7]->Fill(met, brWeight*evtwt_nom);
						h_pt1[7]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2[7]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3[7]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4[7]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1[7]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2[7]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3[7]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4[7]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1[7]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2[7]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3[7]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4[7]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1[7]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2[7]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3[7]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4[7]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1[7]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2[7]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3[7]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4[7]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1[7]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2[7]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3[7]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4[7]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if( cat_string =="blabla" ){ 
						h_mZ[8]->Fill(mZ[0], brWeight*evtwt_nom);
						h_mH[8]->Fill(mH[0], brWeight*evtwt_nom);
						h_met[8]->Fill(met, brWeight*evtwt_nom);
						h_pt1[8]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2[8]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3[8]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4[8]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1[8]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2[8]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3[8]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4[8]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1[8]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2[8]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3[8]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4[8]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1[8]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2[8]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3[8]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4[8]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1[8]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2[8]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3[8]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4[8]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1[8]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2[8]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3[8]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4[8]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if( cat_lepCount(cat_name,'e','g') == 1 and cat_lepCount(cat_name,'m','g') == 3 ){ 
						h_mZ[9]->Fill(mZ[0], brWeight*evtwt_nom);
						h_mH[9]->Fill(mH[0], brWeight*evtwt_nom);
						h_met[9]->Fill(met, brWeight*evtwt_nom);
						h_pt1[9]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2[9]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3[9]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4[9]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1[9]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2[9]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3[9]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4[9]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1[9]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2[9]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3[9]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4[9]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1[9]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2[9]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3[9]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4[9]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1[9]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2[9]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3[9]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4[9]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1[9]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2[9]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3[9]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4[9]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if( cat_string== "mmmm" ){ 
						h_mZ[10]->Fill(mZ[0], brWeight*evtwt_nom);
						h_mH[10]->Fill(mH[0], brWeight*evtwt_nom);
						h_met[10]->Fill(met, brWeight*evtwt_nom);
						h_pt1[10]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2[10]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3[10]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4[10]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1[10]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2[10]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3[10]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4[10]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1[10]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2[10]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3[10]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4[10]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1[10]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2[10]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3[10]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4[10]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1[10]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2[10]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3[10]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4[10]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1[10]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2[10]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3[10]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4[10]->Fill(leptons[3].iso, brWeight*evtwt_nom);
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
				if (mZv.size() !=0 and mZ.size() ==0){ 
					std::sort(mZv.begin(), mZv.end(), [](float a, float b) {
						return a > b;
					});//cout<<mZv[11]<<endl;
					if (cat_string== "ee" ){ 
						h_mZv[11]->Fill(mZv[0], brWeight*evtwt_nom);
						h_mHv[11]->Fill(mH[0], brWeight*evtwt_nom);
						h_metv[11]->Fill(met, brWeight*evtwt_nom);
						h_pt1v[11]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2v[11]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3v[11]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4v[11]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1v[11]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2v[11]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3v[11]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4v[11]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1v[11]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2v[11]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3v[11]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4v[11]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1v[11]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2v[11]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3v[11]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4v[11]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1v[11]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2v[11]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3v[11]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4v[11]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1v[11]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2v[11]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3v[11]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4v[11]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					if (cat_string== "em" ){ 
						h_mZv[11]->Fill(mZv[0], brWeight*evtwt_nom);
						h_mHv[11]->Fill(mH[0], brWeight*evtwt_nom);
						h_metv[11]->Fill(met, brWeight*evtwt_nom);
						h_pt1v[11]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2v[11]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3v[11]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4v[11]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1v[11]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2v[11]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3v[11]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4v[11]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1v[11]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2v[11]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3v[11]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4v[11]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1v[11]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2v[11]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3v[11]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4v[11]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1v[11]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2v[11]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3v[11]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4v[11]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1v[11]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2v[11]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3v[11]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4v[11]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					if (cat_string== "mm" ){ 
						h_mZv[11]->Fill(mZv[0], brWeight*evtwt_nom);
						h_mHv[11]->Fill(mH[0], brWeight*evtwt_nom);
						h_metv[11]->Fill(met, brWeight*evtwt_nom);
						h_pt1v[11]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2v[11]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3v[11]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4v[11]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1v[11]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2v[11]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3v[11]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4v[11]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1v[11]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2v[11]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3v[11]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4v[11]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1v[11]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2v[11]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3v[11]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4v[11]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1v[11]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2v[11]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3v[11]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4v[11]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1v[11]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2v[11]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3v[11]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4v[11]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					if (cat_string== "eee" ){ 
						h_mZv[1]->Fill(mZv[0], brWeight*evtwt_nom);
						h_mHv[1]->Fill(mH[0], brWeight*evtwt_nom);
						h_metv[1]->Fill(met, brWeight*evtwt_nom);
						h_pt1v[1]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2v[1]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3v[1]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4v[1]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1v[1]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2v[1]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3v[1]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4v[1]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1v[1]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2v[1]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3v[1]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4v[1]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1v[1]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2v[1]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3v[1]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4v[1]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1v[1]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2v[1]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3v[1]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4v[1]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1v[1]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2v[1]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3v[1]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4v[1]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if ((cat_string== "eme" or cat_string== "eem" or cat_string == "mee")  ){  
						h_mZv[2]->Fill(mZv[0], brWeight*evtwt_nom);
						h_mHv[2]->Fill(mH[0], brWeight*evtwt_nom);
						h_metv[2]->Fill(met, brWeight*evtwt_nom);
						h_pt1v[2]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2v[2]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3v[2]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4v[2]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1v[2]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2v[2]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3v[2]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4v[2]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1v[2]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2v[2]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3v[2]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4v[2]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1v[2]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2v[2]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3v[2]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4v[2]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1v[2]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2v[2]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3v[2]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4v[2]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1v[2]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2v[2]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3v[2]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4v[2]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if ((cat_string== "emm" or cat_string== "mme" or cat_string == "mem")  ){ 
						h_mZv[3]->Fill(mZv[0], brWeight*evtwt_nom);
						h_mHv[3]->Fill(mH[0], brWeight*evtwt_nom);
						h_metv[3]->Fill(met, brWeight*evtwt_nom);
						h_pt1v[3]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2v[3]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3v[3]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4v[3]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1v[3]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2v[3]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3v[3]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4v[3]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1v[3]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2v[3]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3v[3]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4v[3]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1v[3]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2v[3]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3v[3]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4v[3]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1v[3]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2v[3]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3v[3]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4v[3]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1v[3]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2v[3]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3v[3]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4v[3]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if( cat_string== "mmm"  ){ 
						h_mZv[4]->Fill(mZv[0], brWeight*evtwt_nom);
						h_mHv[4]->Fill(mH[0], brWeight*evtwt_nom);
						h_metv[4]->Fill(met, brWeight*evtwt_nom);
						h_pt1v[4]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2v[4]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3v[4]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4v[4]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1v[4]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2v[4]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3v[4]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4v[4]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1v[4]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2v[4]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3v[4]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4v[4]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1v[4]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2v[4]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3v[4]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4v[4]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1v[4]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2v[4]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3v[4]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4v[4]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1v[4]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2v[4]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3v[4]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4v[4]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					if(mZv.size()<2) continue;
					if( cat_string== "eeee"  ){ 
						h_mZv[5]->Fill(mZv[0], brWeight*evtwt_nom);
						h_mHv[5]->Fill(mH[0], brWeight*evtwt_nom);
						h_metv[5]->Fill(met, brWeight*evtwt_nom);
						h_pt1v[5]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2v[5]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3v[5]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4v[5]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1v[5]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2v[5]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3v[5]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4v[5]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1v[5]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2v[5]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3v[5]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4v[5]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1v[5]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2v[5]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3v[5]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4v[5]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1v[5]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2v[5]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3v[5]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4v[5]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1v[5]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2v[5]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3v[5]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4v[5]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if( cat_lepCount(cat_name,'e','g') == 3 and cat_lepCount(cat_name,'m','g') == 1  ){ 
						h_mZv[6]->Fill(mZv[0], brWeight*evtwt_nom);
						h_mHv[6]->Fill(mH[0], brWeight*evtwt_nom);
						h_metv[6]->Fill(met, brWeight*evtwt_nom);
						h_pt1v[6]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2v[6]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3v[6]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4v[6]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1v[6]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2v[6]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3v[6]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4v[6]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1v[6]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2v[6]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3v[6]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4v[6]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1v[6]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2v[6]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3v[6]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4v[6]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1v[6]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2v[6]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3v[6]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4v[6]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1v[6]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2v[6]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3v[6]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4v[6]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if( cat_lepCount(cat_name,'e','g') == 2 and cat_lepCount(cat_name,'m','g') == 2  ){ 
						h_mZv[7]->Fill(mZv[0], brWeight*evtwt_nom);
						h_mHv[7]->Fill(mH[0], brWeight*evtwt_nom);
						h_metv[7]->Fill(met, brWeight*evtwt_nom);
						h_pt1v[7]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2v[7]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3v[7]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4v[7]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1v[7]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2v[7]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3v[7]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4v[7]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1v[7]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2v[7]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3v[7]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4v[7]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1v[7]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2v[7]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3v[7]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4v[7]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1v[7]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2v[7]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3v[7]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4v[7]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1v[7]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2v[7]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3v[7]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4v[7]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if( cat_string =="blabla"  ){ 
						h_mZv[8]->Fill(mZv[0], brWeight*evtwt_nom);
						h_mHv[8]->Fill(mH[0], brWeight*evtwt_nom);
						h_metv[8]->Fill(met, brWeight*evtwt_nom);
						h_pt1v[8]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2v[8]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3v[8]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4v[8]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1v[8]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2v[8]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3v[8]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4v[8]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1v[8]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2v[8]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3v[8]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4v[8]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1v[8]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2v[8]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3v[8]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4v[8]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1v[8]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2v[8]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3v[8]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4v[8]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1v[8]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2v[8]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3v[8]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4v[8]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if( cat_lepCount(cat_name,'e','g') == 1 and cat_lepCount(cat_name,'m','g') == 3  ){ 
						h_mZv[9]->Fill(mZv[0], brWeight*evtwt_nom);
						h_mHv[9]->Fill(mH[0], brWeight*evtwt_nom);
						h_metv[9]->Fill(met, brWeight*evtwt_nom);
						h_pt1v[9]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2v[9]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3v[9]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4v[9]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1v[9]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2v[9]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3v[9]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4v[9]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1v[9]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2v[9]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3v[9]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4v[9]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1v[9]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2v[9]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3v[9]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4v[9]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1v[9]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2v[9]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3v[9]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4v[9]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1v[9]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2v[9]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3v[9]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4v[9]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
					else if( cat_string== "mmmm"  ){ 
						h_mZv[10]->Fill(mZv[0], brWeight*evtwt_nom);
						h_mHv[10]->Fill(mH[0], brWeight*evtwt_nom);
						h_metv[10]->Fill(met, brWeight*evtwt_nom);
						h_pt1v[10]->Fill(leptons[0].pt, brWeight*evtwt_nom);
						h_pt2v[10]->Fill(leptons[1].pt, brWeight*evtwt_nom);
						h_pt3v[10]->Fill(leptons[2].pt, brWeight*evtwt_nom);
						h_pt4v[10]->Fill(leptons[3].pt, brWeight*evtwt_nom);
						h_eta1v[10]->Fill(leptons[0].eta, brWeight*evtwt_nom);
						h_eta2v[10]->Fill(leptons[1].eta, brWeight*evtwt_nom);
						h_eta3v[10]->Fill(leptons[2].eta, brWeight*evtwt_nom);
						h_eta4v[10]->Fill(leptons[3].eta, brWeight*evtwt_nom);
						h_phi1v[10]->Fill(leptons[0].phi, brWeight*evtwt_nom);
						h_phi2v[10]->Fill(leptons[1].phi, brWeight*evtwt_nom);
						h_phi3v[10]->Fill(leptons[2].phi, brWeight*evtwt_nom);
						h_phi4v[10]->Fill(leptons[3].phi, brWeight*evtwt_nom);
						h_dxy1v[10]->Fill(leptons[0].d0, brWeight*evtwt_nom);
						h_dxy2v[10]->Fill(leptons[1].d0, brWeight*evtwt_nom);
						h_dxy3v[10]->Fill(leptons[2].d0, brWeight*evtwt_nom);
						h_dxy4v[10]->Fill(leptons[3].d0, brWeight*evtwt_nom);
						h_dZ1v[10]->Fill(leptons[0].dZ, brWeight*evtwt_nom);
						h_dZ2v[10]->Fill(leptons[1].dZ, brWeight*evtwt_nom);
						h_dZ3v[10]->Fill(leptons[2].dZ, brWeight*evtwt_nom);
						h_dZ4v[10]->Fill(leptons[3].dZ, brWeight*evtwt_nom);
						h_iso1v[10]->Fill(leptons[0].iso, brWeight*evtwt_nom);
						h_iso2v[10]->Fill(leptons[1].iso, brWeight*evtwt_nom);
						h_iso3v[10]->Fill(leptons[2].iso, brWeight*evtwt_nom);
						h_iso4v[10]->Fill(leptons[3].iso, brWeight*evtwt_nom);
					}
				}
			}//selections loop
		}//evt loop 
		hnevts->Write();	
		h_mZ[11]->Draw();
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

