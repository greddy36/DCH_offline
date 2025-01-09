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


double XSec(std::string fname){
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

void test(const char* ext = "root"){
	const char* inDir = "inputs_nopair";
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

	double mDCH = 500.0, mZ = 91.2, lumi_2018 = 58900.0;//139000;
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		cout<<filename[j]<<endl;
		
		std::string fname = filename[j];
		if (fname.find("EGamma_2018_old") > fname.length()) continue;
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
		else if (selection =="test") o_name = "../hist_test_nopair";
		else cout<< "SELECTION NOT DEFINED!!!"<<endl;
		char *oname = gSystem->ConcatFileName(o_name, filename[j]);
		TFile* ofile = new TFile(oname, "RECREATE"); 
		TTree *tree = (TTree*)ifile->Get("Events");
		MyBranch(tree);
        
		for (int i =0; i < tree->GetEntries(); i++){
			tree->GetEntry(i);
			string cat_string = getCatName(cat);
			char* cat_name = const_cast<char*>(cat_string.c_str());
			int Nlep = cat_lepCount(cat_name,'e','m'); 
			int Ntau = strlen(cat_name)-Nlep; 	
			if (cat <= 21  and q_1+q_2+q_3+q_4 != 0) continue; 
			//if (Ntau != 0) continue;
			//if (Nlep == 0) continue;
			//if (cat_name != "mmt") continue;

			//cout<<"BEFORE"<<"\t"<<q_1<<"\t"<<q_2<<"\t"<<q_3<<"\t"<<q_4<<"\t"<<cat_name<<endl;			
			// (strlen(cat_name) == 3 and (abs(q_1+q_2+q_3)!=1 or abs(q_1) !=1 or abs(q_2) != 1 or abs(q_3)!=1))continue;
			// (strlen(cat_name) == 4 and (abs(q_1+q_2+q_3+q_4)!=0 or abs(q_1) !=1 or abs(q_2) != 1 or abs(q_3)!=1 or abs(q_4)!=1))continue;
			
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
			//cout<<evtwt_nom<<endl;

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
				/*std::vector<int> Zcands = ZCandMaker(cat_name, 20);					TLorentzVector L1 = LepV(Zcands[0]), L2 = LepV(Zcands[1]), L3 = epV(Zcands[2]), L4 = LepV(Zcands[3]);
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
			std::vector<double> mZ, mZv, mH;
			for(int m = 1; m <= strlen(cat_name); ++m){
				for(int n = m+1; n <= strlen(cat_name); ++n){
					string pair_name = pairFunc(m,n,cat_name,20);
					if(pair_name=="Zwindow") mZ.push_back((LepV(m)+LepV(n)).M());
					else if(pair_name=="Zv") mZv.push_back((LepV(m)+LepV(n)).M());
					else if(pair_name=="DCH") mH.push_back((LepV(m)+LepV(n)).M());
					//else if(pair_name=="found nothing") cout<<"found nothing"<<endl;
					else continue;
				}
			}
			//std::sort(mH.begin(), mH.end(), [](double a, double b){return a > b;});
			if (mZ.size() >0 ) {
				if (cat_string== "eee") cout<<run<<endl;
			}
		}//evt loop 
		delete tree;
	}
	gSystem->FreeDirectory(dirp);
}

