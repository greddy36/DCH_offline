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
        "tte", "ttm", "ttt"
    };

    // Check if the index is within the valid range
    if (index < 1 || index > catNames.size()) {
        return "Invalid index";
    }

    // Return the corresponding cat name
    return catNames[index - 1];
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
		float xs_weight = 1;
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
		
	
		TH1F* h_mZ1 = new TH1F("h_mZ1", "mZ (e+e- & e)", 25, 0, 200);
		TH1F* h_mZ2 = new TH1F("h_mZ2", "mZ (e+e- & m)", 25, 0, 200);
		TH1F* h_mZ3 = new TH1F("h_mZ3", "mZ (m+m- & e)", 25, 0, 200);
		TH1F* h_mZ4 = new TH1F("h_mZ4", "mZ (m+m- & m)", 25, 0, 200);
		TH1F* h_mZv1 = new TH1F("h_mZv1", "Z-veto (e+e- & e)", 25, 0, 300);
		TH1F* h_mZv2 = new TH1F("h_mZv2", "Z-veto (e+e- & m)", 25, 0, 300);
		TH1F* h_mZv3 = new TH1F("h_mZv3", "Z-veto (m+m- & e)", 25, 0, 300);
		TH1F* h_mZv4 = new TH1F("h_mZv4", "Z-veto (m+m- & m)", 25, 0, 300);

		TH1F* h_mH1 = new TH1F("h_mH1", "mll (e+e- & e)", 25, 0, 500);
		TH1F* h_mH2 = new TH1F("h_mH2", "mll (e+e- & m)", 25, 0, 500);
		TH1F* h_mH3 = new TH1F("h_mH3", "mll (m+m- & e)", 25, 0, 500);
		TH1F* h_mH4 = new TH1F("h_mH4", "mll (m+m- & m)", 25, 0, 500);
		TH1F* h_mHv1 = new TH1F("h_mHv1", "mll in Z-veto (e+e- & e)", 25, 0, 500);
		TH1F* h_mHv2 = new TH1F("h_mHv2", "mll in Z-veto (e+e- & m)", 25, 0, 500);
		TH1F* h_mHv3 = new TH1F("h_mHv3", "mll in Z-veto (m+m- & e)", 25, 0, 500);
		TH1F* h_mHv4 = new TH1F("h_mHv4", "mll in Z-veto (m+m- & m)", 25, 0, 500);	

		TH1F* h_pt1_1 = new TH1F("h_pt1_1", "pt1 (e+e- & e)", 25, 0, 300);
		TH1F* h_pt1_2 = new TH1F("h_pt1_2", "pt1 (e+e- & m)", 25, 0, 300);
		TH1F* h_pt1_3 = new TH1F("h_pt1_3", "pt1 (m+m- & e)", 25, 0, 300);
		TH1F* h_pt1_4 = new TH1F("h_pt1_4", "pt1 (m+m- & m)", 25, 0, 300);
		TH1F* h_pt1_v1 = new TH1F("h_pt1_v1", "pt1 in Z-veto (e+e- & e)", 25, 0, 300);
		TH1F* h_pt1_v2 = new TH1F("h_pt1_v2", "pt1 in Z-veto (e+e- & m)", 25, 0, 300);
		TH1F* h_pt1_v3 = new TH1F("h_pt1_v3", "pt1 in Z-veto (m+m- & e)", 25, 0, 300);
		TH1F* h_pt1_v4 = new TH1F("h_pt1_v4", "pt1 in Z-veto (m+m- & m)", 25, 0, 300);
	
		TH1F* h_pt2_1 = new TH1F("h_pt2_1", "pt2 (e+e- & e)", 25, 0, 300);
		TH1F* h_pt2_2 = new TH1F("h_pt2_2", "pt2 (e+e- & m)", 25, 0, 300);
		TH1F* h_pt2_3 = new TH1F("h_pt2_3", "pt2 (m+m- & e)", 25, 0, 300);
		TH1F* h_pt2_4 = new TH1F("h_pt2_4", "pt2 (m+m- & m)", 25, 0, 300);
		TH1F* h_pt2_v1 = new TH1F("h_pt2_v1", "pt2 in Z-veto (e+e- & e)", 25, 0, 300);
		TH1F* h_pt2_v2 = new TH1F("h_pt2_v2", "pt2 in Z-veto (e+e- & m)", 25, 0, 300);
		TH1F* h_pt2_v3 = new TH1F("h_pt2_v3", "pt2 in Z-veto (m+m- & e)", 25, 0, 300);
		TH1F* h_pt2_v4 = new TH1F("h_pt2_v4", "pt2 in Z-veto (m+m- & m)", 25, 0, 300);		

	
		TH1F* h_pt3_1 = new TH1F("h_pt3_1", "pt3 (e+e- & e)", 25, 0, 300);
		TH1F* h_pt3_2 = new TH1F("h_pt3_2", "pt3 (e+e- & m)", 25, 0, 300);
		TH1F* h_pt3_3 = new TH1F("h_pt3_3", "pt3 (m+m- & e)", 25, 0, 300);
		TH1F* h_pt3_4 = new TH1F("h_pt3_4", "pt3 (m+m- & m)", 25, 0, 300);
		TH1F* h_pt3_v1 = new TH1F("h_pt3_v1", "pt3 in Z-veto (e+e- & e)", 25, 0, 300);
		TH1F* h_pt3_v2 = new TH1F("h_pt3_v2", "pt3 in Z-veto (e+e- & m)", 25, 0, 300);
		TH1F* h_pt3_v3 = new TH1F("h_pt3_v3", "pt3 in Z-veto (m+m- & e)", 25, 0, 300);
		TH1F* h_pt3_v4 = new TH1F("h_pt3_v4", "pt3 in Z-veto (m+m- & m)", 25, 0, 300);	

		TH1F* h_met1 = new TH1F("h_met1", "met (e+e- & e)", 25, 0, 300);
		TH1F* h_met2 = new TH1F("h_met2", "met (e+e- & m)", 25, 0, 300);
		TH1F* h_met3 = new TH1F("h_met3", "met (m+m- & e)", 25, 0, 300);
		TH1F* h_met4 = new TH1F("h_met4", "met (m+m- & m)", 25, 0, 300);
		TH1F* h_metv1 = new TH1F("h_metv1", "met in Z-veto (e+e- & e)", 25, 0, 300);
		TH1F* h_metv2 = new TH1F("h_metv2", "met in Z-veto (e+e- & m)", 25, 0, 300);
		TH1F* h_metv3 = new TH1F("h_metv3", "met in Z-veto (m+m- & e)", 25, 0, 300);
		TH1F* h_metv4 = new TH1F("h_metv4", "met in Z-veto (m+m- & m)", 25, 0, 300);	
		
		TH1F* h_MT1 = new TH1F("h_MT1", "MT (e+e- & e)", 25, 0, 500);
		TH1F* h_MT2 = new TH1F("h_MT2", "MT (e+e- & m)", 25, 0, 500);
		TH1F* h_MT3 = new TH1F("h_MT3", "MT (m+m- & e)", 25, 0, 500);
		TH1F* h_MT4 = new TH1F("h_MT4", "MT (m+m- & m)", 25, 0, 500);
		TH1F* h_MTv1 = new TH1F("h_MTv1", "MT in Z-veto (e+e- & e)", 25, 0, 500);
		TH1F* h_MTv2 = new TH1F("h_MTv2", "MT in Z-veto (e+e- & m)", 25, 0, 500);
		TH1F* h_MTv3 = new TH1F("h_MTv3", "MT in Z-veto (m+m- & e)", 25, 0, 500);
		TH1F* h_MTv4 = new TH1F("h_MTv4", "MT in Z-veto (m+m- & m)", 25, 0, 500);	
		
		TH1F* h_mZ5 = new TH1F("h_mZ5", "mZ (e+e- & ee)", 25, 0, 200);
		TH1F* h_mZ6 = new TH1F("h_mZ6", "mZ (e+e- & em)", 25, 0, 200);
		TH1F* h_mZ7 = new TH1F("h_mZ7", "mZ (e+e- & mm)", 25, 0, 200);
		TH1F* h_mZ8 = new TH1F("h_mZ8", "mZ (m+m- & ee)", 25, 0, 200);
		TH1F* h_mZ9 = new TH1F("h_mZ9", "mZ (m+m- & em)", 25, 0, 200);	
		TH1F* h_mZ10 = new TH1F("h_mZ10", "mZ in Z-veto (m+m- & mm)", 25, 0, 200);	
		TH1F* h_mZv5 = new TH1F("h_mZv5", "mZ in Z-veto (e+e- & ee)", 25, 0, 200);
		TH1F* h_mZv6 = new TH1F("h_mZv6", "mZ in Z-veto (e+e- & em)", 25, 0, 200);
		TH1F* h_mZv7 = new TH1F("h_mZv7", "mZ in Z-veto (e+e- & mm)", 25, 0, 200);
		TH1F* h_mZv8 = new TH1F("h_mZv8", "mZ in Z-veto (m+m- & ee)", 25, 0, 200);
		TH1F* h_mZv9 = new TH1F("h_mZv9", "mZ in Z-veto (m+m- & em)", 25, 0, 200);	
		TH1F* h_mZv10 = new TH1F("h_mZv10", "mZ in Z-veto (m+m- & mm)", 25, 0, 200);

		TH1F* h_mH5 = new TH1F("h_mH5", "mll (e+e- & ee)", 25, 0, 500);
		TH1F* h_mH6 = new TH1F("h_mH6", "mll (e+e- & em)", 25, 0, 500);
		TH1F* h_mH7 = new TH1F("h_mH7", "mll (m+m- & mm)", 25, 0, 500);
		TH1F* h_mH8 = new TH1F("h_mH8", "mll (m+m- & ee)", 25, 0, 500);
		TH1F* h_mH9 = new TH1F("h_mH9", "mll (m+m- & em)", 25, 0, 500);
		TH1F* h_mH10 = new TH1F("h_mH10", "mll in Z-veto (m+m- & mm)", 25, 0, 500);
		TH1F* h_mHv5 = new TH1F("h_mHv5", "mll in Z-veto (e+e- & ee)", 25, 0, 500);
		TH1F* h_mHv6 = new TH1F("h_mHv6", "mll in Z-veto (e+e- & em)", 25, 0, 500);
		TH1F* h_mHv7 = new TH1F("h_mHv7", "mll in Z-veto (m+m- & mm)", 25, 0, 500);
		TH1F* h_mHv8 = new TH1F("h_mHv8", "mll in Z-veto (m+m- & ee)", 25, 0, 500);
		TH1F* h_mHv9 = new TH1F("h_mHv9", "mll in Z-veto (m+m- & em)", 25, 0, 500);
		TH1F* h_mHv10 = new TH1F("h_mHv10", "mll in Z-veto (m+m- & mm)", 25, 0, 500);
						
		TH1F* h_met5 = new TH1F("h_met5", "met (e+e- & ee)", 25, 0, 300);
		TH1F* h_met6 = new TH1F("h_met6", "met (e+e- & em)", 25, 0, 300);
		TH1F* h_met7 = new TH1F("h_met7", "met (m+m- & mm)", 25, 0, 300);
		TH1F* h_met8 = new TH1F("h_met8", "met (m+m- & ee)", 25, 0, 300);
		TH1F* h_met9 = new TH1F("h_met9", "met (m+m- & em)", 25, 0, 300);
		TH1F* h_met10 = new TH1F("h_met10", "met in Z-veto (m+m- & mm)", 25, 0, 300);
		TH1F* h_metv5 = new TH1F("h_metv5", "met in Z-veto (e+e- & ee)", 25, 0, 300);
		TH1F* h_metv6 = new TH1F("h_metv6", "met in Z-veto (e+e- & em)", 25, 0, 300);
		TH1F* h_metv7 = new TH1F("h_metv7", "met in Z-veto (m+m- & mm)", 25, 0, 300);
		TH1F* h_metv8 = new TH1F("h_metv8", "met in Z-veto (m+m- & ee)", 25, 0, 300);
		TH1F* h_metv9 = new TH1F("h_metv9", "met in Z-veto (m+m- & em)", 25, 0, 300);
		TH1F* h_metv10 = new TH1F("h_metv10", "met in Z-veto (m+m- & mm)", 25, 0, 300);
						
		TH1F* h_MT5 = new TH1F("h_MT5", "MT (e+e- & ee)", 25, 0, 500);
		TH1F* h_MT6 = new TH1F("h_MT6", "MT (e+e- & em)", 25, 0, 500);
		TH1F* h_MT7 = new TH1F("h_MT7", "MT (m+m- & mm)", 25, 0, 500);
		TH1F* h_MT8 = new TH1F("h_MT8", "MT (m+m- & ee)", 25, 0, 500);
		TH1F* h_MT9 = new TH1F("h_MT9", "MT (m+m- & em)", 25, 0, 500);			
		TH1F* h_MT10 = new TH1F("h_MT10", "MT in Z-veto (m+m- & mm)", 25, 0, 500);			
		TH1F* h_MTv5 = new TH1F("h_MTv5", "MT in Z-veto (e+e- & ee)", 25, 0, 500);
		TH1F* h_MTv6 = new TH1F("h_MTv6", "MT in Z-veto (e+e- & em)", 25, 0, 500);
		TH1F* h_MTv7 = new TH1F("h_MTv7", "MT in Z-veto (m+m- & mm)", 25, 0, 500);
		TH1F* h_MTv8 = new TH1F("h_MTv8", "MT in Z-veto (m+m- & ee)", 25, 0, 500);
		TH1F* h_MTv9 = new TH1F("h_MTv9", "MT in Z-veto (m+m- & em)", 25, 0, 500);			
		TH1F* h_MTv10 = new TH1F("h_MTv10", "MT in Z-veto (m+m- & mm)", 25, 0, 500);
		
		for (int i =0; i < tree->GetEntries(); i++){
			tree->GetEntry(i);			
			float *lep_pt, *tau_pt;
			string cat_string = getCatName(cat);
			char* cat_name = const_cast<char*>(cat_string.c_str());
			int Nlep = cat_lepCount(cat_name,'e','m'); 
			int Ntau = strlen(cat_name)-Nlep; 			
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
			}//cout<<evtwt_nom<< filename[j]<<endl;		 			

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
						cout<<leptons[w].mass <<"\t"<< leptons[w].pt <<"\t"<<leptons[w].eta <<"\t"<< leptons[w].phi<<endl;
						cout<<leptons[x].mass <<"\t"<< leptons[x].pt <<"\t"<<leptons[x].eta <<"\t"<< leptons[x].phi<<endl;
						cout<<cat<<" xx"<<endl;
						break;
						}
					}
				}
				if (foundDup == true) continue;
				
			
				std::vector<int> Zcands = ZCandMaker(cat_name, 20);	
				TLorentzVector L1 = LepV(Zcands[0]), L2 = LepV(Zcands[1]), L3 = LepV(Zcands[2]), L4 = LepV(Zcands[3]);
				int Q[] = {-99, -99, -99, -99};
				for(int iq = 0; iq <= 3; iq++){
					if (Zcands[iq] == 1) Q[iq] = q_1;
					else if (Zcands[iq] == 2) Q[iq] = q_2;
					else if (Zcands[iq] == 3) Q[iq] = q_3;
					else if (Zcands[iq] == 4) Q[iq] = q_4;
				}
				int q1=Q[0],q2=Q[1],q3=Q[2],q4=Q[3];
				float mll_1=-99/*leading H mass*/, mll_2=-99, mllt_2=-99;
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
				}
	
				//cout<<"AFTER "<<"\t"<<q1<<"\t"<<q2<<"\t"<<q3<<"\t"<<q4<<"\t"<<Zcands[0]<<Zcands[1]<<Zcands[2]<<Zcands[3]<<"\t"<<cat_name<<endl;
				if (cat_string== "eee" and abs((L1+L2).M()-mZ) < 20 ){ 
					//cout<<cat_name<<"\t"<<abs((L1+L3).M()-mZ)<<endl;
					h_mZ1->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH1->Fill(mll_1, brWeight*evtwt_nom);
					h_pt1_1->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2_1->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3_1->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_met1->Fill(met, brWeight*evtwt_nom);
					h_MT1->Fill(met+L3.Mt(), brWeight*evtwt_nom);
				}
				else if ((cat_string== "eme" or cat_string== "eem" or cat_string == "mee") and abs((L1+L2).M()-mZ) < 20 ){ 
					h_mZ2->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH2->Fill(mll_1, brWeight*evtwt_nom);
					h_pt1_2->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2_2->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3_2->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_met2->Fill(met, brWeight*evtwt_nom);
					h_MT2->Fill(met+L3.Mt(), brWeight*evtwt_nom);
				}
				else if ((cat_string== "emm" or cat_string== "mme" or cat_string == "mem") and abs((L1+L2).M()-mZ) < 20 ){ 
					h_mZ3->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH3->Fill(mll_1, brWeight*evtwt_nom);
					h_pt1_3->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2_3->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3_3->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_met3->Fill(met, brWeight*evtwt_nom);
					h_MT3->Fill(met+L3.Mt(), brWeight*evtwt_nom);
				}
				else if( cat_string== "mmm" and abs((L1+L2).M()-mZ) < 20 ){ 
					h_mZ4->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH4->Fill(mll_1, brWeight*evtwt_nom);
					h_pt1_4->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2_4->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3_4->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_met4->Fill(met, brWeight*evtwt_nom);
					h_MT4->Fill(met+L3.Mt(), brWeight*evtwt_nom);
				}
				else if( cat_string== "eeee" and abs((L1+L2).M()-mZ) < 20 ){ 
					h_mZ5->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH5->Fill(mll_1, brWeight*evtwt_nom);
					h_met5->Fill(met, brWeight*evtwt_nom);
					h_MT5->Fill(met+mllt_2, brWeight*evtwt_nom);
				}
				else if( cat_lepCount(cat_name,'e','g') == 3 and cat_lepCount(cat_name,'m','g') == 1 and abs((L1+L2).M()-mZ) < 20 ){ 
					h_mZ6->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH6->Fill(mll_1, brWeight*evtwt_nom);
					h_met6->Fill(met, brWeight*evtwt_nom);
					h_MT6->Fill(met+mllt_2, brWeight*evtwt_nom);
				}
				else if( cat_lepCount(cat_name,'e','g') == 2 and cat_lepCount(cat_name,'m','g') == 2 and abs((L1+L2).M()-mZ) < 20 ){ 
					h_mZ7->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH7->Fill(mll_1, brWeight*evtwt_nom);
					h_met7->Fill(met, brWeight*evtwt_nom);
					h_MT7->Fill(met+mllt_2, brWeight*evtwt_nom);
				}
				else if( cat_string =="blabla" and abs((L1+L2).M()-mZ) < 20 ){ 
					h_mZ8->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH8->Fill(mll_1, brWeight*evtwt_nom);
					h_met8->Fill(met, brWeight*evtwt_nom);
					h_MT8->Fill(met+mllt_2, brWeight*evtwt_nom);
				}
				else if( cat_lepCount(cat_name,'e','g') == 1 and cat_lepCount(cat_name,'m','g') == 3 and abs((L1+L2).M()-mZ) < 20 ){ 
					h_mZ9->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH9->Fill(mll_1, brWeight*evtwt_nom);
					h_met9->Fill(met, brWeight*evtwt_nom);
					h_MT9->Fill(met+mllt_2, brWeight*evtwt_nom);
				}
				else if( cat_string== "mmmm" and abs((L1+L2).M()-mZ) < 20 ){ 
					h_mZ10->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mH10->Fill(mll_1, brWeight*evtwt_nom);
					h_met10->Fill(met, brWeight*evtwt_nom);
					h_MT10->Fill(met+mllt_2, brWeight*evtwt_nom);
				}	
				
				/*std::vector<int> ZcandsV = ZVetoMaker(cat_name, 20);	
				L1 = LepV(ZcandsV[0]), L2 = LepV(ZcandsV[1]), L3 = LepV(ZcandsV[2]), L4 = LepV(ZcandsV[3]);
				for(int iq = 0; iq <= 3; iq++){
					if (Zcands[iq] == 1) Q[iq] = q_1;
					else if (Zcands[iq] == 2) Q[iq] = q_2;
					else if (Zcands[iq] == 3) Q[iq] = q_3;
					else if (Zcands[iq] == 4) Q[iq] = q_4;
				}
				q1=Q[0]; q2=Q[1]; q3=Q[2]; q4=Q[3]
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
				
				if (cat_string== "eee" and abs((L1+L2).M()-mZ) >= 20 ){ 
					h_mZv1->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mHv1->Fill(mll_1, brWeight*evtwt_nom);
					h_pt1_v1->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2_v1->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3_v1->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_metv1->Fill(met, brWeight*evtwt_nom);
					h_MTv1->Fill(met+L3.Mt(), brWeight*evtwt_nom);
				}
				else if ((cat_string== "eme" or cat_string== "eem" or cat_string == "mee")and abs((L1+L2).M()-mZ) >= 20 ){  
					h_mZv2->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mHv2->Fill(mll_1, brWeight*evtwt_nom);
					h_pt1_v2->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2_v2->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3_v2->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_metv2->Fill(met, brWeight*evtwt_nom);
					h_MTv2->Fill(met+L3.Mt(), brWeight*evtwt_nom);
				}
				else if ((cat_string== "emm" or cat_string== "mme" or cat_string == "mem") and abs((L1+L2).M()-mZ) >= 20 ){ 
					h_mZv3->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mHv3->Fill(mll_1, brWeight*evtwt_nom);
					h_pt1_v3->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2_v3->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3_v3->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_metv3->Fill(met, brWeight*evtwt_nom);
					h_MTv3->Fill(met+L3.Mt(), brWeight*evtwt_nom);
				}
				else if( cat_string== "mmm" and abs((L1+L2).M()-mZ) >= 20 ){ 
					h_mZv4->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mHv4->Fill(mll_1, brWeight*evtwt_nom);
					h_pt1_v4->Fill(L1.Pt(), brWeight*evtwt_nom);
					h_pt2_v4->Fill(L2.Pt(), brWeight*evtwt_nom);
					h_pt3_v4->Fill(L3.Pt(), brWeight*evtwt_nom);
					h_metv4->Fill(met, brWeight*evtwt_nom);
					h_MTv4->Fill(met+L3.Mt(), brWeight*evtwt_nom);
				}
				else if( cat_string== "eeee" and abs((L1+L2).M()-mZ) >= 20 ){ 
					h_mZv5->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mHv5->Fill(mll_1, brWeight*evtwt_nom);
					h_metv5->Fill(met, brWeight*evtwt_nom);
					h_MT5->Fill(met+mllt_2, brWeight*evtwt_nom);
				}
				else if( cat_lepCount(cat_name,'e','g') == 3 and cat_lepCount(cat_name,'m','g') == 1 and abs((L1+L2).M()-mZ) >= 20 ){ 
					h_mZv6->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mHv6->Fill(mll_1, brWeight*evtwt_nom);
					h_metv6->Fill(met, brWeight*evtwt_nom);
					h_MTv6->Fill(met+mllt_2, brWeight*evtwt_nom);
				}
				else if( cat_lepCount(cat_name,'e','g') == 2 and cat_lepCount(cat_name,'m','g') == 2 and abs((L1+L2).M()-mZ) >= 20 ){ 
					h_mZv7->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mHv7->Fill(mll_1, brWeight*evtwt_nom);
					h_metv7->Fill(met, brWeight*evtwt_nom);
					h_MTv7->Fill(met+mllt_2, brWeight*evtwt_nom);
				}
				else if( cat_string =="blabla" and abs((L1+L2).M()-mZ) >= 20 ){ 
					h_mZv8->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mHv8->Fill(mll_1, brWeight*evtwt_nom);
					h_metv8->Fill(met, brWeight*evtwt_nom);
					h_MTv8->Fill(met+mllt_2, brWeight*evtwt_nom);
				}
				else if( cat_lepCount(cat_name,'e','g') == 1 and cat_lepCount(cat_name,'m','g') == 3 and abs((L1+L2).M()-mZ) >= 20 ){ 
					h_mZv9->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mHv9->Fill(mll_1, brWeight*evtwt_nom);
					h_metv9->Fill(met, brWeight*evtwt_nom);
					h_MTv9->Fill(met+mllt_2, brWeight*evtwt_nom);
				}
				else if( cat_string== "mmmm" and abs((L1+L2).M()-mZ) >= 20 ){ 
					h_mZv10->Fill((L1+L2).M(), brWeight*evtwt_nom);
					h_mHv10->Fill(mll_1, brWeight*evtwt_nom);
					h_metv10->Fill(met, brWeight*evtwt_nom);
					h_MTv10->Fill(met+mllt_2, brWeight*evtwt_nom);
				}
			}
		}//evt loop 

		h_mZ1->Scale(xs_weight);
		h_mZ2->Scale(xs_weight);
		h_mZ3->Scale(xs_weight);
		h_mZ4->Scale(xs_weight);
		h_mZv1->Scale(xs_weight);
		h_mZv2->Scale(xs_weight);
		h_mZv3->Scale(xs_weight);
		h_mZv4->Scale(xs_weight);
		
		h_mH1->Scale(xs_weight);
		h_mH2->Scale(xs_weight);
		h_mH3->Scale(xs_weight);
		h_mH4->Scale(xs_weight);
		h_mHv1->Scale(xs_weight);
		h_mHv2->Scale(xs_weight);
		h_mHv3->Scale(xs_weight);
		h_mHv4->Scale(xs_weight);
		
		h_met1->Scale(xs_weight);
		h_met2->Scale(xs_weight);
		h_met3->Scale(xs_weight);
		h_met4->Scale(xs_weight);
		h_metv1->Scale(xs_weight);
		h_metv2->Scale(xs_weight);
		h_metv3->Scale(xs_weight);
		h_metv4->Scale(xs_weight);

		h_MT1->Scale(xs_weight);
		h_MT2->Scale(xs_weight);
		h_MT3->Scale(xs_weight);
		h_MT4->Scale(xs_weight);
		h_MTv1->Scale(xs_weight);
		h_MTv2->Scale(xs_weight);
		h_MTv3->Scale(xs_weight);
		h_MTv4->Scale(xs_weight);

		h_pt1_1->Scale(xs_weight);
		h_pt2_1->Scale(xs_weight);
		h_pt3_1->Scale(xs_weight);
		h_pt1_v1->Scale(xs_weight);
		h_pt2_v1->Scale(xs_weight);
		h_pt3_v1->Scale(xs_weight);
	
		h_pt1_2->Scale(xs_weight);
		h_pt2_2->Scale(xs_weight);
		h_pt3_2->Scale(xs_weight);
		h_pt1_v2->Scale(xs_weight);
		h_pt2_v2->Scale(xs_weight);
		h_pt3_v2->Scale(xs_weight);

		h_pt1_3->Scale(xs_weight);
		h_pt2_3->Scale(xs_weight);
		h_pt3_3->Scale(xs_weight);
		h_pt1_v3->Scale(xs_weight);
		h_pt2_v3->Scale(xs_weight);
		h_pt3_v3->Scale(xs_weight);

		h_pt1_4->Scale(xs_weight);
		h_pt2_4->Scale(xs_weight);
		h_pt3_4->Scale(xs_weight);
		h_pt1_v4->Scale(xs_weight);
		h_pt2_v4->Scale(xs_weight);
		h_pt3_v4->Scale(xs_weight);

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

		h_mZ5->Scale(xs_weight);
		h_mZ6->Scale(xs_weight);
		h_mZ7->Scale(xs_weight);
		h_mZ8->Scale(xs_weight);
		h_mZ9->Scale(xs_weight);
		h_mZ10->Scale(xs_weight);
		h_mZv5->Scale(xs_weight);
		h_mZv6->Scale(xs_weight);
		h_mZv7->Scale(xs_weight);
		h_mZv8->Scale(xs_weight);
		h_mZv9->Scale(xs_weight);
		h_mZv10->Scale(xs_weight);

		h_mH5->Scale(xs_weight);
		h_mH6->Scale(xs_weight);
		h_mH7->Scale(xs_weight);
		h_mH8->Scale(xs_weight);
		h_mH9->Scale(xs_weight);
		h_mH10->Scale(xs_weight);
		h_mHv5->Scale(xs_weight);
		h_mHv6->Scale(xs_weight);
		h_mHv7->Scale(xs_weight);
		h_mHv8->Scale(xs_weight);
		h_mHv9->Scale(xs_weight);
		h_mHv10->Scale(xs_weight);
		
		h_met5->Scale(xs_weight);
		h_met6->Scale(xs_weight);
		h_met7->Scale(xs_weight);
		h_met8->Scale(xs_weight);
		h_met9->Scale(xs_weight);
		h_met10->Scale(xs_weight);		
		h_metv5->Scale(xs_weight);
		h_metv6->Scale(xs_weight);
		h_metv7->Scale(xs_weight);
		h_metv8->Scale(xs_weight);
		h_metv9->Scale(xs_weight);
		h_metv10->Scale(xs_weight);	
		
		h_MT5->Write();
		h_MT6->Write();
		h_MT7->Write();
		h_MT8->Write();
		h_MT9->Write();
		h_MT10->Write();
		h_MTv5->Write();
		h_MTv6->Write();
		h_MTv7->Write();
		h_MTv8->Write();
		h_MTv9->Write();
		h_MTv10->Write();
				
		h_mZ5->Write();
		h_mZ6->Write();
		h_mZ7->Write();
		h_mZ8->Write();
		h_mZ9->Write();
		h_mZ10->Write();
		h_mZv5->Write();
		h_mZv6->Write();
		h_mZv7->Write();
		h_mZv8->Write();
		h_mZv9->Write();
		h_mZv10->Write();
		
		h_mH5->Write();
		h_mH6->Write();
		h_mH7->Write();
		h_mH8->Write();
		h_mH9->Write();
		h_mH10->Write();
		h_mHv5->Write();
		h_mHv6->Write();
		h_mHv7->Write();
		h_mHv8->Write();
		h_mHv9->Write();
		h_mHv10->Write();
		
		h_met5->Write();
		h_met6->Write();
		h_met7->Write();
		h_met8->Write();
		h_met9->Write();
		h_met10->Write();		
		h_metv5->Write();
		h_metv6->Write();
		h_metv7->Write();
		h_metv8->Write();
		h_metv9->Write();
		h_metv10->Write();		

		h_MT5->Write();
		h_MT6->Write();
		h_MT7->Write();
		h_MT8->Write();
		h_MT9->Write();
		h_MT10->Write();
		h_MTv5->Write();
		h_MTv6->Write();
		h_MTv7->Write();
		h_MTv8->Write();
		h_MTv9->Write();
		h_MTv10->Write();
		//cout<< j <<"\t"<< oname <<endl;
		printf("%s %f\n", oname, XSec(filename[j])*lumi_2018/hnevts->Integral() );
		delete tree;
	}
	gSystem->FreeDirectory(dirp);
}

