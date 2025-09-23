//To apply various kinematics selections right after online analysis.
#include "TMath.h"
#include <cmath>
#include <vector>
#include "TF1.h"
#include "TFile.h"
#include <TDirectory.h>
#include "include/MyBranch.C"//branch definitons
#include "include/Kinematics.C"//Kine fns
#include "include/MET_split.C"
#include "include/Xsections.C"

void processPairs( const char* cat_name, vector<pair<int, int>>& Z_pair, vector<pair<int, int>>& Zv_pair, vector<pair<int, int>>& H_pair, vector<pair<int,int>>& opp_pair) {//global function to process pairs
	int len = strlen(cat_name);
	for (int m = 1; m <= len; ++m) {
		for (int n = m + 1; n <= len; ++n) {
			string pair_name = pairFunc(m, n, cat_name, 20);
			if (pair_name == "Zwindow") Z_pair.push_back({m,n});
			else if (pair_name == "Zv") Zv_pair.push_back({m,n});
			else if (pair_name == "ZttPair") Zv_pair.push_back({m,n});
			else if (pair_name == "oppPair") opp_pair.push_back({m,n});
			else if (pair_name == "DCH") H_pair.push_back({m,n});
			else continue;
		}
	}
}

void n_minus_one_cutflow(const std::string& excludeCut,
                         std::map<std::string, TH1D*>& cutflowHists,
                         const std::string& channel,
                         const std::map<std::string, bool>& cutbools)
{
    const std::vector<std::string> cutNames = {"M_ll1","M_ll2","ST", "dRll", "dRlplm"};

    // Safety check
    if (cutflowHists.find(channel) == cutflowHists.end()) {
        std::cerr << "Warning: Channel '" << channel << "' not found in cutflow map!" << std::endl;
        return;
        
    }

    bool pass = true;
    for (const auto& cut : cutNames) {
        if (cut == excludeCut) continue;
        auto it = cutbools.find(cut);
        if (it == cutbools.end() || !it->second) {
            pass = false;
            break;
        }
    }

    if (pass) {
        int bin = cutflowHists[channel]->GetXaxis()->FindBin(excludeCut.c_str());
        cutflowHists[channel]->AddBinContent(bin);
    }
}



void FillHists(TDirectory* rootDir, std::map<std::string, TTree*> trim_tree, std::map< std::string, double > hist_variable_map, double evtwt_nom, std::map<std::string, TH1D*> h_mll1, std::map<std::string, TH1D*> h_mll2, std::map<std::string, TH1D*> h_cat, std::map<std::string, TH1D*> h_gencat){
	rootDir->cd();
	const char* dirName = rootDir->GetName();
	trim_tree[dirName]->Fill();
	h_mll1[dirName]->Fill(hist_variable_map["mll1"], evtwt_nom);
	h_mll2[dirName]->Fill(hist_variable_map["mll2"], evtwt_nom);
	h_cat[dirName]->Fill(hist_variable_map["cat"], evtwt_nom);
	h_gencat[dirName]->Fill(hist_variable_map["gen_cat"], evtwt_nom);
}

void WriteHists(TDirectory* rootDir, std::map<std::string, TTree*> trim_tree, std::map<std::string, TH1D*> h_mll1, std::map<std::string, TH1D*> h_mll2, std::map<std::string, TH1D*> h_cat, std::map<std::string, TH1D*> h_gencat){
	rootDir->cd();
	const char* dirName = rootDir->GetName();
	trim_tree[dirName]->Write();
	h_mll1[dirName]->Write();
	h_mll2[dirName]->Write();
	h_cat[dirName]->Write();
	h_gencat[dirName]->Write();
}

void DCH_presel_peter(const char* ext = ".root"){
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
	
	std::string selection = "Pre";

	double mDCH = 500, mZ = 91.2;
	//TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	for(int j = 0; j < nfiles; j++){
		TFile *ifile = new TFile(filename[j],"READ");
		std::string fname = filename[j];
		if (fname.find("_2018.") > fname.length()) continue;
		//if (fname.find("ttZ") > fname.length() and fname.find("ZH") > fname.length()) continue;
		if (XSec(filename[j])==1) continue; 
		cout<<filename[j]<<endl;
		
		const char* o_name;
		if (selection =="none") o_name = "hist";
		else if (selection =="Pre") o_name = "hist_peter";
		else if (selection =="APre") o_name = "hist_APre";
		else if (selection =="CR") o_name = "hist_CR";
		else if (selection =="VR") o_name = "hist_VR";
		else if (selection =="test") o_name = "hist_test";
		else cout<< "SELECTION NOT DEFINED!!!"<<endl;
		char *oname = gSystem->ConcatFileName(o_name, filename[j]);
		TFile* ofile = new TFile(oname, "RECREATE"); 
		TDirectory* eeeeDir = ofile->mkdir("eeee");
		TDirectory* eeemDir = ofile->mkdir("eeem");
		TDirectory* ememDir = ofile->mkdir("emem");
		TDirectory* eemmDir = ofile->mkdir("eemm");
		TDirectory* emmmDir = ofile->mkdir("emmm");
		TDirectory* mmmmDir = ofile->mkdir("mmmm");


		TH1D* hnevts;
		if(XSec(fname)!=1){
			hnevts = (TH1D*)ifile->Get("hNWEvts")->Clone("hnevts");
			if (!hnevts) hnevts = (TH1D*)ifile->Get("hNEvts")->Clone("hnevts");
		}
		hnevts->Write();
		double xs_wt = applyXSec(ifile);
		
		TTree *tree = (TTree*)ifile->Get("Events");
		MyBranch(tree);
		
		std::map<std::string, TTree*> trimmed_tree;
						
		double xmin = 0, xmax = mDCH+1000; int binw = 10; int nbins = (xmax-xmin)/binw;
		
		std::map<std::string, TH1D*>h_mll1, h_mll2,h_cat, h_gencat;
		double mll_1, mll_2, dR_1, dR_2, evtwt;
		for(auto rootDirName: {"eeee","eeem","emem","eemm","emmm","mmmm"}){
			trimmed_tree[rootDirName] = new TTree("Events", "trees");
			trimmed_tree[rootDirName]->Branch("mll1", &mll_1);
			trimmed_tree[rootDirName]->Branch("mll2", &mll_2);
			trimmed_tree[rootDirName]->Branch("cat", &cat);
			trimmed_tree[rootDirName]->Branch("gen_cat", &gen_cat);
			trimmed_tree[rootDirName]->Branch("evtwt", &evtwt);
			
			h_mll1[rootDirName] = new TH1D("h_mll1", "mll_1", nbins, xmin, xmax);
			h_mll1[rootDirName]->Sumw2();
			h_mll2[rootDirName] = new TH1D("h_mll2", "mll_2", nbins, xmin, xmax);
			h_mll2[rootDirName]->Sumw2();
			h_cat[rootDirName] = new TH1D("h_cat", "cat", 46,0,46);
			h_cat[rootDirName]->Sumw2();
			h_gencat[rootDirName] = new TH1D("h_gencat", "gen cat", 22,0,22);
			h_gencat[rootDirName]->Sumw2();
		}
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
			if (cat > 21  and abs(q_1+q_2+q_3) != 1) continue;
			if (strlen(cat_name)<=2) continue; 
			
			if (Ntau != 0) continue;  
			string gencat_string = numberToCat(gen_cat);
			char* gencat_name = const_cast<char*>(gencat_string.c_str());
			if (fname.find("Hpp") < fname.length() and cat_lepCount(gencat_name,'e','m') != 4) continue;
			
			/*if (fname.find("HppM") < fname.length()){
				std::string Gencat_str = numberToCat(gen_cat);
				if (Gencat_str.substr(0,2) == "tt"  )
					brWeight = brWeight*6;
				else if ( Gencat_str.substr(0,2) == "ee" || Gencat_str.substr(0,2) == "mm" || Gencat_str.substr(0,2) == "em" || Gencat_str.substr(0,2) == "mt" || Gencat_str.substr(0,2) == "et")
					brWeight = brWeight*0;
				if (Gencat_str.substr(2,2) == "tt" )
					brWeight = brWeight*6;
				else if ( Gencat_str.substr(2,2) == "ee" || Gencat_str.substr(2,2) == "mm" || Gencat_str.substr(2,2) == "em" || Gencat_str.substr(2,2) == "mt" || Gencat_str.substr(2,2) == "et")
					brWeight = brWeight*0;
			
				//if (Gencat_str.substr(0,2) == Gencat_str.substr(2,2))
					//brWeight = brWeight*2;
				//cout<<brWeight<<"\t"<<Gencat_str<<endl;
			}*/
			
			double evtwt_nom = xs_wt*Generator_weight;//paul will apply the br weights
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
			
			//Sort the lepton variables in descending order based on pt
			/*std::sort(leptons.begin(), leptons.end(), [](const Lepton& a, const Lepton& b) 
				return a.pt > b.pt;
			});*/
			
			double st = 0;
			if (strlen(cat_name)==4) st = pt_1+pt_2+pt_3+pt_4;
			else if (strlen(cat_name)==3) st = pt_1+pt_2+pt_3;
			
			/*void processPairs( const char* cat_name, vector<pair<int, int>>& Z_pair, vector<pair<int, int>>& Zv_pair, vector<pair<int, int>>& H_pair) {//global function to process pairs
				int len = strlen(cat_name);
				for (int m = 1; m <= len; ++m) {
					for (int n = m + 1; n <= len; ++n) {
						string pair_name = pairFunc(m, n, cat_name, 20);
						if (pair_name == "Zwindow") Z_pair.push_back({m,n});
						else if (pair_name == "Zv") Zv_pair.push_back({m,n});
						else if (pair_name == "DCH") H_pair.push_back({m,n});
						else continue;
					}
				}
			}	*/		
			TLorentzVector MET; MET.SetPtEtaPhiM(met, 0, metphi, 0);
//==============================================================================
			if (selection == "Pre"){	
				vector<pair<int, int>> SFopp_pair, opp_pair, H_pair;
				processPairs(cat_name, SFopp_pair, SFopp_pair, H_pair, opp_pair);
				if (SFopp_pair.size() < 1) continue; 
				//cout<< SFopp_pair.size()<<endl;
				double mll1 = (LepV(H_pair[0].first)+LepV(H_pair[0].second)).M();
				double mZ1 = (LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second)).M();
				double mZ2 = (LepV(SFopp_pair[1].first)+LepV(SFopp_pair[1].second)).M();
				double dRll = deltaR(LepV(H_pair[0].first),LepV(H_pair[0].second));
				double mll2 = (LepV(H_pair[1].first)+LepV(H_pair[1].second)).M();
				double mZ3 = (LepV(SFopp_pair[2].first)+LepV(SFopp_pair[2].second)).M();
				double mZ4 = (LepV(SFopp_pair[3].first)+LepV(SFopp_pair[3].second)).M();	
				double dRll2 = deltaR(LepV(H_pair[1].first),LepV(H_pair[1].second));
				double dR1 = deltaR(LepV(SFopp_pair[0].first),LepV(SFopp_pair[0].second));
				double dR2 = deltaR(LepV(SFopp_pair[1].first),LepV(SFopp_pair[1].second));
				double dR3 = deltaR(LepV(SFopp_pair[2].first),LepV(SFopp_pair[2].second));
				double dR4 = deltaR(LepV(SFopp_pair[3].first),LepV(SFopp_pair[3].second));
				double mT1 = calculateMT(LepV(H_pair[0].first)+LepV(H_pair[0].second),MET);
				double mT2 = calculateMT(LepV(H_pair[1].first)+LepV(H_pair[1].second),MET);
				double mTtot1 = calculateMTtot(LepV(H_pair[0].first),LepV(H_pair[0].second));
				double mTtot2 = calculateMTtot(LepV(H_pair[1].first),LepV(H_pair[1].second));
				double mT1_opp = calculateMT(LepV(SFopp_pair[0].first)+LepV(SFopp_pair[0].second),MET);
				double mT2_opp = calculateMT(LepV(SFopp_pair[1].first)+LepV(SFopp_pair[1].second),MET);
				double mT3_opp = calculateMT(LepV(SFopp_pair[2].first)+LepV(SFopp_pair[2].second),MET);
				double mT4_opp = calculateMT(LepV(SFopp_pair[3].first)+LepV(SFopp_pair[3].second),MET);
				double mTtot1_opp = calculateMTtot(LepV(SFopp_pair[0].first),LepV(SFopp_pair[0].second));
				double mTtot2_opp = calculateMTtot(LepV(SFopp_pair[1].first),LepV(SFopp_pair[1].second));
				double mTtot3_opp = calculateMTtot(LepV(SFopp_pair[2].first),LepV(SFopp_pair[2].second));
				double mTtot4_opp = calculateMTtot(LepV(SFopp_pair[3].first),LepV(SFopp_pair[3].second));
				int W_lep_idx =remaining_idx(SFopp_pair, cat_name);
				
				if (abs(mZ1-mZ) < 10 or abs(mZ2-mZ) < 10 or abs(mZ3-mZ) < 10 or abs(mZ4-mZ) < 10) continue;
				if (st < 360) continue;

				std::map< std::string, double > hist_variable_map = { 
																{"mll1", mll1},
																{"mll2", mll2},
																{"cat", cat},
																{"gen_cat", gen_cat}
				};
				mll_1 = mll1; mll_2 = mll2; evtwt = evtwt_nom;
				//cout<<gencat_name<<endl;
				if (fname.find("Hpp") < fname.length() and gencat_string != cat_string) continue;
				if (cat_string == "eeee") FillHists(eeeeDir, trimmed_tree, hist_variable_map, evtwt_nom, h_mll1, h_mll2, h_cat, h_gencat);	
				else if (cat_string == "eeem") FillHists(eeemDir, trimmed_tree, hist_variable_map, evtwt_nom, h_mll1, h_mll2, h_cat, h_gencat);	
				else if (cat_string == "emem") FillHists(ememDir, trimmed_tree, hist_variable_map, evtwt_nom, h_mll1, h_mll2, h_cat, h_gencat);	
				else if (cat_string == "eemm") FillHists(eemmDir, trimmed_tree, hist_variable_map, evtwt_nom, h_mll1, h_mll2, h_cat, h_gencat);	
				else if (cat_string == "emmm") FillHists(emmmDir, trimmed_tree, hist_variable_map, evtwt_nom, h_mll1, h_mll2, h_cat, h_gencat);	
				else if (cat_string == "mmmm") FillHists(mmmmDir, trimmed_tree, hist_variable_map, evtwt_nom, h_mll1, h_mll2, h_cat, h_gencat);	
			}
		}//evt loop
		WriteHists(eeeeDir, trimmed_tree, h_mll1, h_mll2,h_cat, h_gencat );
		WriteHists(eeemDir, trimmed_tree, h_mll1, h_mll2,h_cat, h_gencat );
		WriteHists(ememDir, trimmed_tree, h_mll1, h_mll2,h_cat, h_gencat );
		WriteHists(eemmDir, trimmed_tree, h_mll1, h_mll2,h_cat, h_gencat );
		WriteHists(emmmDir, trimmed_tree, h_mll1, h_mll2,h_cat, h_gencat );
		WriteHists(mmmmDir, trimmed_tree, h_mll1, h_mll2,h_cat, h_gencat );
		
		delete tree;
	}
	gSystem->FreeDirectory(dirp);
}

