#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <THStack.h>
#include <TPad.h>
#include <TLegend.h>
#include <vector>
#include <string>
#include <map>
#include "include/Xsections.C"

void StackHist_sig() {
	std::string summary_type = "tau_ch", year = "Run2";
    // Define histograms to retrieve
    const char *hist_list[] = 

	{
		/*"0tau/h_ST","1tau/h_ST","2tau/h_ST","3tau/h_ST","3lep0tau/h_ST","3lep1tau/h_ST","3lep2tau/h_ST",
		"0tau/h_mZ1","1tau/h_mZ1","2tau/h_mZ1","3tau/h_mZ1","3lep0tau/h_mZ1","3lep1tau/h_mZ1","3lep2tau/h_mZ1",
		"0tau/h_mZ2","1tau/h_mZ2","2tau/h_mZ2","3tau/h_mZ2","3lep0tau/h_mZ2","3lep1tau/h_mZ2","3lep2tau/h_mZ2",
		"0tau/h_mZ3","1tau/h_mZ3","2tau/h_mZ3","3tau/h_mZ3","3lep0tau/h_mZ3","3lep1tau/h_mZ3","3lep2tau/h_mZ3",
		"0tau/h_mZ4","1tau/h_mZ4","2tau/h_mZ4","3tau/h_mZ4","3lep0tau/h_mZ4","3lep1tau/h_mZ4","3lep2tau/h_mZ4",*/
		"0tau/h_mT1","1tau/h_mT1","2tau/h_mT1","3tau/h_mT1","3lep0tau/h_mT1","3lep1tau/h_mT1","3lep2tau/h_mT1",
		"0tau/h_mT2","1tau/h_mT2","2tau/h_mT2","3tau/h_mT2","3lep0tau/h_mT2","3lep1tau/h_mT2","3lep2tau/h_mT2",
		"0tau/h_mT1_opp","1tau/h_mT1_opp","2tau/h_mT1_opp","3tau/h_mT1_opp","3lep0tau/h_mT1_opp","3lep1tau/h_mT1_opp","3lep2tau/h_mT1_opp",
		"0tau/h_mT2_opp","1tau/h_mT2_opp","2tau/h_mT2_opp","3tau/h_mT2_opp","3lep0tau/h_mT2_opp","3lep1tau/h_mT2_opp","3lep2tau/h_mT2_opp",
		"0tau/h_mT3_opp","1tau/h_mT3_opp","2tau/h_mT3_opp","3tau/h_mT3_opp","3lep0tau/h_mT3_opp","3lep1tau/h_mT3_opp","3lep2tau/h_mT3_opp",
		"0tau/h_mT4_opp","1tau/h_mT4_opp","2tau/h_mT4_opp","3tau/h_mT4_opp","3lep0tau/h_mT4_opp","3lep1tau/h_mT4_opp","3lep2tau/h_mT4_opp",
		"0tau/h_mTtot1_opp","1tau/h_mTtot1_opp","2tau/h_mTtot1_opp","3tau/h_mTtot1_opp","3lep0tau/h_mTtot1_opp","3lep1tau/h_mTtot1_opp","3lep2tau/h_mTtot1_opp",
		"0tau/h_mTtot2_opp","1tau/h_mTtot2_opp","2tau/h_mTtot2_opp","3tau/h_mTtot2_opp","3lep0tau/h_mTtot2_opp","3lep1tau/h_mTtot2_opp","3lep2tau/h_mTtot2_opp",
		"0tau/h_mTtot3_opp","1tau/h_mTtot3_opp","2tau/h_mTtot3_opp","3tau/h_mTtot3_opp","3lep0tau/h_mTtot3_opp","3lep1tau/h_mTtot3_opp","3lep2tau/h_mTtot3_opp",
		"0tau/h_mTtot4_opp","1tau/h_mTtot4_opp","2tau/h_mTtot4_opp","3tau/h_mTtot4_opp","3lep0tau/h_mTtot4_opp","3lep1tau/h_mTtot4_opp","3lep2tau/h_mTtot4_opp",
		"0tau/h_mDCH1","1tau/h_mDCH1","2tau/h_mDCH1","3tau/h_mDCH1","3lep0tau/h_mDCH1","3lep1tau/h_mDCH1","3lep2tau/h_mDCH1",
		"0tau/h_mDCH2","1tau/h_mDCH2","2tau/h_mDCH2","3tau/h_mDCH2","3lep0tau/h_mDCH2","3lep1tau/h_mDCH2","3lep2tau/h_mDCH2",
		"0tau/h_mll1","1tau/h_mll1","2tau/h_mll1","3tau/h_mll1","3lep0tau/h_mll1","3lep1tau/h_mll1","3lep2tau/h_mll1",
		"0tau/h_mll2","1tau/h_mll2","2tau/h_mll2","3tau/h_mll2","3lep0tau/h_mll2","3lep1tau/h_mll2","3lep2tau/h_mll2",
		"0tau/h_met","1tau/h_met","2tau/h_met","3tau/h_met","3lep0tau/h_met","3lep1tau/h_met","3lep2tau/h_met",
		"0tau/cutflow","1tau/cutflow","2tau/cutflow","3tau/cutflow","3lep0tau/cutflow","3lep1tau/cutflow","3lep2tau/cutflow"
	};
	
    // Categories with input files
    std::map<std::string, std::vector<std::string>> files;
    if (year == "2016") files = {
        {"DY",    {"DYJetsToLLM10to50_2016.root", "DYJetsToLLM50_2016.root"}},
        {"VV",    {"WW_2016.root", "WWTo2L2Nu_2016.root", "WZTo2Q2L_2016.root", "WZTo3LNu_2016.root"}},
        {"VVV",   {"WWW_2016.root", "WZZ_2016.root", "ZZZ_2016.root"}},
        {"ttV",   {"ttWJets_2016.root", "ttZJets_2016.root"}},
        {"WJ",    {"WJetsToLNu_NLO_2016.root", "WJetsToLNu_HT-70To100_2016.root", "WJetsToLNu_HT-100To200_2016.root", 
                   "WJetsToLNu_HT-200To400_2016.root", "WJetsToLNu_HT-400To600_2016.root", 
                   "WJetsToLNu_HT-600To800_2016.root", "WJetsToLNu_HT-800To1200_2016.root", "WJetsToLNu_HT-1200To2500_2016.root", "WJetsToLNu_HT-2500ToInf_2016.root"}},
        {"ZZ",    {"ZZTo2L2Nu_2016.root", "ZZTo2Q2L_2016.root", "ZZTo4L_2016.root"}},
        {"ST",    {"ST_s-channel_2016.root", "ST_t-channel_antitop_2016.root", "ST_t-channel_top_2016.root", 
                   "ST_tW_antitop_2016.root", "ST_tW_top_2016.root"}},
        {"TTbar", {"TTTo2L2Nu_2016.root", "TTToSemiLeptonic_2016.root", "TTToHadronic_2016.root"}},
        {"other", {"ttHToTauTau_2016.root", "ZHToMuMu_2016.root","ZHToTauTau_2016.root", "GluGluZH_2016.root","ttHToEE_2016.root","ttHTo2L2Nu_2016.root"}},
        {"data",  {"SingleElectron_2016.root","EGamma_2016.root", "SingleMuon_2016.root"}}
    };
    else if (year == "2017") files = {
        {"DY",    {"DYJetsToLLM10to50_2017.root", "DYJetsToLLM50_2017.root"}},
        {"VV",    {"WW_2017.root", "WWTo2L2Nu_2017.root", "WZTo2Q2L_2017.root", "WZTo3LNu_2017.root"}},
        {"VVV",   {"WWW_2017.root", "WZZ_2017.root", "ZZZ_2017.root"}},
        {"ttV",   {"ttWJets_2017.root", "ttZJets_2017.root"}},
        {"WJ",    {"WJetsToLNu_NLO_2017.root", "WJetsToLNu_HT-70To100_2017.root", "WJetsToLNu_HT-100To200_2017.root", 
                   "WJetsToLNu_HT-200To400_2017.root", "WJetsToLNu_HT-400To600_2017.root", 
                   "WJetsToLNu_HT-600To800_2017.root", "WJetsToLNu_HT-800To1200_2017.root", "WJetsToLNu_HT-1200To2500_2017.root", "WJetsToLNu_HT-2500ToInf_2017.root"}},
        {"ZZ",    {"ZZTo2L2Nu_2017.root", "ZZTo2Q2L_2017.root", "ZZTo4L_2017.root"}},
        {"ST",    {"ST_s-channel_2017.root", "ST_t-channel_antitop_2017.root", "ST_t-channel_top_2017.root", 
                   "ST_tW_antitop_2017.root", "ST_tW_top_2017.root"}},
        {"TTbar", {"TTTo2L2Nu_2017.root", "TTToSemiLeptonic_2017.root", "TTToHadronic_2017.root"}},
        {"other", {"ttHToTauTau_2017.root", "ZHToMuMu_2017.root","ZHToTauTau_2017.root", "GluGluZH_2017.root","ttHToEE_2017.root", "ttHTo2L2Nu_2017.root"}},
        {"data",  {"SingleElectron_2017.root","EGamma_2017.root", "SingleMuon_2017.root"}}
    };
    else if (year == "2018") files = {
    	{"signal",    {"HppM1000_2016.root", "HppM1000_2017.root", "HppM1000_2018.root"}},
        {"DY",    {"DYJetsToLLM10to50_2016.root", "DYJetsToLLM50_2016.root","DYJetsToLLM10to50_2017.root", "DYJetsToLLM50_2017.root","DYJetsToLLM10to50_2018.root", "DYJetsToLLM50_2018.root"}},
        {"VV",    {"WW_2016.root", "WWTo2L2Nu_2016.root", "WZTo2Q2L_2016.root", "WZTo3LNu_2016.root","WW_2017.root", "WWTo2L2Nu_2017.root", "WZTo2Q2L_2017.root", "WZTo3LNu_2017.root","WW_2018.root", "WWTo2L2Nu_2018.root", "WZTo2Q2L_2018.root", "WZTo3LNu_2018.root"}},
        {"VVV",   {"WWW_2016.root", "WZZ_2016.root", "ZZZ_2016.root","WWW_2017.root", "WZZ_2017.root", "ZZZ_2017.root","WWW_2018.root", "WZZ_2018.root", "ZZZ_2018.root"}},
        {"ttW",   {"ttWJets_2016.root", "ttWJets_2017.root","ttWJets_2018.root"}},
        {"ttZ",   {"ttZJets_2016.root", "ttZJets_2017.root","ttZJets_2018.root"}},
        {"WJ",    {"WJetsToLNu_NLO_2016.root", "WJetsToLNu_HT-70To100_2016.root", "WJetsToLNu_HT-100To200_2016.root", 
                   "WJetsToLNu_HT-200To400_2016.root", "WJetsToLNu_HT-400To600_2016.root", 
                   "WJetsToLNu_HT-600To800_2016.root", "WJetsToLNu_HT-800To1200_2016.root", "WJetsToLNu_HT-1200To2500_2016.root", "WJetsToLNu_HT-2500ToInf_2016.root","WJetsToLNu_NLO_2017.root", "WJetsToLNu_HT-70To100_2017.root", "WJetsToLNu_HT-100To200_2017.root", 
                   "WJetsToLNu_HT-200To400_2017.root", "WJetsToLNu_HT-400To600_2017.root", 
                   "WJetsToLNu_HT-600To800_2017.root", "WJetsToLNu_HT-800To1200_2017.root", "WJetsToLNu_HT-1200To2500_2017.root", "WJetsToLNu_HT-2500ToInf_2017.root","WJetsToLNu_NLO_2018.root", "WJetsToLNu_HT-70To100_2018.root", "WJetsToLNu_HT-100To200_2018.root", 
                   "WJetsToLNu_HT-200To400_2018.root", "WJetsToLNu_HT-400To600_2018.root", 
                   "WJetsToLNu_HT-600To800_2018.root", "WJetsToLNu_HT-800To1200_2018.root", "WJetsToLNu_HT-1200To2500_2018.root", "WJetsToLNu_HT-2500ToInf_2018.root"}},
        {"ZZ",    {"ZZTo2L2Nu_2016.root", "ZZTo2Q2L_2016.root", "ZZTo4L_2016.root","ZZTo2L2Nu_2017.root", "ZZTo2Q2L_2017.root", "ZZTo4L_2017.root","ZZTo2L2Nu_2018.root", "ZZTo2Q2L_2018.root", "ZZTo4L_2018.root"}},
        {"ST",    {"ST_s-channel_2016.root", "ST_t-channel_antitop_2016.root", "ST_t-channel_top_2016.root", 
                   "ST_tW_antitop_2016.root", "ST_tW_top_2016.root","ST_s-channel_2017.root", "ST_t-channel_antitop_2017.root", "ST_t-channel_top_2017.root", 
                   "ST_tW_antitop_2017.root", "ST_tW_top_2017.root","ST_s-channel_2018.root", "ST_t-channel_antitop_2018.root", "ST_t-channel_top_2018.root", 
                   "ST_tW_antitop_2018.root", "ST_tW_top_2018.root"}},
        {"TTbar", {"TTTo2L2Nu_2016.root", "TTToSemiLeptonic_2016.root", "TTToHadronic_2016.root","TTTo2L2Nu_2017.root", "TTToSemiLeptonic_2017.root", "TTToHadronic_2017.root","TTTo2L2Nu_2018.root", "TTToSemiLeptonic_2018.root", "TTToHadronic_2018.root"}},
        {"ttH", {"ttHToTauTau_2016.root","ttHToTauTau_2017.root", "ttHToTauTau_2018.root","ttHToEE_2016.root","ttHToEE_2017.root", "ttHToEE_2018.root","ttHTo2L2Nu_2016.root","ttHTo2L2Nu_2017.root", "ttHTo2L2Nu_2018.root"}},
        {"ZH", {"ZHToMuMu_2016.root","ZHToTauTau_2016.root", "GluGluZH_2016.root", "ZHToMuMu_2017.root","ZHToTauTau_2017.root", "GluGluZH_2017.root", "ZHToMuMu_2018.root","ZHToTauTau_2018.root", "GluGluZH_2018.root"}},
        {"data",  {"SingleElectron_2016.root","EGamma_2016.root", "SingleMuon_2016.root","SingleElectron_2017.root","EGamma_2017.root", "SingleMuon_2017.root","SingleElectron_2018.root","EGamma_2018.root", "SingleMuon_2018.root"}}
       };
        else if (year == "Run2") files = {
    	{"signal",    {"HppM500_2016.root", "HppM500_2017.root", "HppM500_2018.root"}},
        {"DY",    {"DYJetsToLLM10to50_2016.root", "DYJetsToLLM50_2016.root","DYJetsToLLM10to50_2017.root", "DYJetsToLLM50_2017.root","DYJetsToLLM10to50_2018.root", "DYJetsToLLM50_2018.root"}},
        {"VV",    {"WW_2016.root", "WWTo2L2Nu_2016.root", "WZTo2Q2L_2016.root", "WZTo3LNu_2016.root","WW_2017.root", "WWTo2L2Nu_2017.root", "WZTo2Q2L_2017.root", "WZTo3LNu_2017.root","WW_2018.root", "WWTo2L2Nu_2018.root", "WZTo2Q2L_2018.root", "WZTo3LNu_2018.root"}},
        {"VVV",   {"WWW_2016.root", "WZZ_2016.root", "ZZZ_2016.root","WWW_2017.root", "WZZ_2017.root", "ZZZ_2017.root","WWW_2018.root", "WZZ_2018.root", "ZZZ_2018.root"}},
        {"ttW",   {"ttWJets_2016.root", "ttWJets_2017.root","ttWJets_2018.root"}},
        {"ttZ",   {"ttZJets_2016.root", "ttZJets_2017.root","ttZJets_2018.root"}},
        {"WJ",    {"WJetsToLNu_NLO_2016.root", "WJetsToLNu_HT-70To100_2016.root", "WJetsToLNu_HT-100To200_2016.root", 
                   "WJetsToLNu_HT-200To400_2016.root", "WJetsToLNu_HT-400To600_2016.root", 
                   "WJetsToLNu_HT-600To800_2016.root", "WJetsToLNu_HT-800To1200_2016.root", "WJetsToLNu_HT-1200To2500_2016.root", "WJetsToLNu_HT-2500ToInf_2016.root","WJetsToLNu_NLO_2017.root", "WJetsToLNu_HT-70To100_2017.root", "WJetsToLNu_HT-100To200_2017.root", 
                   "WJetsToLNu_HT-200To400_2017.root", "WJetsToLNu_HT-400To600_2017.root", 
                   "WJetsToLNu_HT-600To800_2017.root", "WJetsToLNu_HT-800To1200_2017.root", "WJetsToLNu_HT-1200To2500_2017.root", "WJetsToLNu_HT-2500ToInf_2017.root","WJetsToLNu_NLO_2018.root", "WJetsToLNu_HT-70To100_2018.root", "WJetsToLNu_HT-100To200_2018.root", 
                   "WJetsToLNu_HT-200To400_2018.root", "WJetsToLNu_HT-400To600_2018.root", 
                   "WJetsToLNu_HT-600To800_2018.root", "WJetsToLNu_HT-800To1200_2018.root", "WJetsToLNu_HT-1200To2500_2018.root", "WJetsToLNu_HT-2500ToInf_2018.root"}},
        {"ZZ",    {"ZZTo2L2Nu_2016.root", "ZZTo2Q2L_2016.root", "ZZTo4L_2016.root","ZZTo2L2Nu_2017.root", "ZZTo2Q2L_2017.root", "ZZTo4L_2017.root","ZZTo2L2Nu_2018.root", "ZZTo2Q2L_2018.root", "ZZTo4L_2018.root"}},
        {"ST",    {"ST_s-channel_2016.root", "ST_t-channel_antitop_2016.root", "ST_t-channel_top_2016.root", 
                   "ST_tW_antitop_2016.root", "ST_tW_top_2016.root","ST_s-channel_2017.root", "ST_t-channel_antitop_2017.root", "ST_t-channel_top_2017.root", 
                   "ST_tW_antitop_2017.root", "ST_tW_top_2017.root","ST_s-channel_2018.root", "ST_t-channel_antitop_2018.root", "ST_t-channel_top_2018.root", 
                   "ST_tW_antitop_2018.root", "ST_tW_top_2018.root"}},
        {"TTbar", {"TTTo2L2Nu_2016.root", "TTToSemiLeptonic_2016.root", "TTToHadronic_2016.root","TTTo2L2Nu_2017.root", "TTToSemiLeptonic_2017.root", "TTToHadronic_2017.root","TTTo2L2Nu_2018.root", "TTToSemiLeptonic_2018.root", "TTToHadronic_2018.root"}},
        {"ttH", {"ttHToTauTau_2016.root","ttHToTauTau_2017.root", "ttHToTauTau_2018.root","ttHToEE_2016.root","ttHToEE_2017.root", "ttHToEE_2018.root","ttHTo2L2Nu_2016.root","ttHTo2L2Nu_2017.root", "ttHTo2L2Nu_2018.root"}},
        {"ZH", {"ZHToMuMu_2016.root","ZHToTauTau_2016.root", "GluGluZH_2016.root", "ZHToMuMu_2017.root","ZHToTauTau_2017.root", "GluGluZH_2017.root", "ZHToMuMu_2018.root","ZHToTauTau_2018.root", "GluGluZH_2018.root"}}
    };
    std::map<std::string, std::vector<TFile*>> open_files;
    for (auto& kv : files) {
		for (const auto& fname : kv.second) {
		    TFile* file = new TFile(("hist_MY_mll/" + fname).c_str(), "READ");
		    if (!file || file->IsZombie()) continue;
	        open_files[kv.first].push_back(file);
	    }
	}
	TFile *ifile_D1 = new TFile("hist_MY_mll/HppM500_2016.root","READ");
  
	for (int i = 0; i < sizeof(hist_list)/sizeof(hist_list[0]); i++) {
		gStyle->SetOptStat(0);
		TCanvas* canvas = new TCanvas("canvas", "Stacked histograms", 800, 700);
		std::string name = hist_list[i];
		std::string hist_string;
		if(summary_type != "tau_ch"){
			size_t pos = name.rfind('_'); // find last underscore
			std::string channel = (pos != std::string::npos) ? name.substr(pos + 1) : ""; 
			hist_string += channel + " channel ";
			
			if (name.find("v_") < name.length()) hist_string += "in Z-veto";  
			else if (name.find("v_") > name.length()) hist_string += "in Z-window";
		}
		else {
			if (name.find("3lep") < name.length()) hist_string += "3l, ";
			if (name.find("0tau") < name.length()) hist_string += "0-#tau channel";
			else if (name.find("1tau") < name.length()) hist_string += "1-#tau channel";
			else if (name.find("2tau") < name.length()) hist_string += "2-#tau channel";
			else if (name.find("3tau") < name.length()) hist_string += "3-#tau channel";
		}
		char *hist_name = const_cast<char*>(hist_string.c_str());
		
		THStack* bkg_stack = new THStack("bkg_stack", hist_name);
		std::map<std::string, TH1D*> hist;
		std::map<std::string, int> fill_colors = {
		    {"DY", 7}, {"VV", 8}, {"VVV", 6}, {"ttW", 4}, {"ttZ", 2}, {"WJ", 9}, {"ZZ", 5},
		    {"ST", 30}, {"TTbar", 46}, {"ttH", 28},{"ZH", 29}
		};
		
		int bins = 0;
		for (auto& kv : open_files) {
			TH1D* tmp = (TH1D*)ifile_D1->Get(hist_list[i]);
			hist[kv.first]=(TH1D*)tmp->Clone();
		    //hist[kv.first]->Sumw2();
		    hist[kv.first]->Reset();
			for (auto* f : kv.second) {
		        TH1D* h = dynamic_cast<TH1D*>(f->Get(hist_list[i]));
		        if (!h) continue;
		        //h->Sumw2();
		        h->Scale(applyXSec(f));
		        //h->Rebin(10);
		        
				hist[kv.first]->Add(h);
				//cout<<hist[kv.first]->Integral()<<endl;
			}
			if (hist[kv.first]) {
				hist[kv.first]->SetFillColor(fill_colors[kv.first]);
				bins = hist[kv.first]->GetNbinsX();
			}
		}

		hist["VV"]->Scale(1.12631);
		hist["ZZ"]->Scale(1.31366);
		// Stack backgrounds
		//THStack* bkg_stack = new THStack("bkg_stack", "2l and 3l channel summary in Z-window;;Events");
		TH1D* h_bkg_total = (TH1D*)hist["DY"]->Clone("h_bkg_total");
		//h_bkg_total->Sumw2();
		h_bkg_total->Reset();
		for (const std::string& bkg_group : {"DY", "VV", "VVV", "ttW", "ttZ", "WJ", "ZZ", "ST", "TTbar", "ttH", "ZH"}) {
		    bkg_stack->Add(hist[bkg_group]);
		    h_bkg_total->Add(hist[bkg_group]);
		}
		
		//Signal
		//hist["signal"]->SetLineStyle(5);
		hist["signal"]->SetLineColor(1);
		//hist["signal"]->Scale();
		//hist["signal"]->Scale(h_bkg_total->Integral()/hist["signal"]->Integral());
		hist["signal"]->SetBinContent(bins, hist["signal"]->GetBinContent(bins)+hist["signal"]->GetBinContent(bins+1));
		
		// Draw main plot
		//gPad->SetLogy(1);
		cout<<hist["signal"]->Integral()<<"\t"<<h_bkg_total->Integral()<<endl;
		double padmax = std::max(hist["signal"]->GetMaximum(), h_bkg_total->GetMaximum());
		bkg_stack->SetMaximum(padmax*1.1); //Y max
		bkg_stack->Draw("hist");
		hist["signal"]->Draw("SAME hist");
		
		// Create a TLatex object
		TLatex latex;
		latex.SetNDC(); // Use normalized coordinates (0 to 1)
		latex.SetTextSize(0.04); // Set text size
		latex.SetTextAlign(31); // Align right (horizontal) and top (vertical)
		latex.DrawLatex(0.95, 0.95, const_cast<char*>(year.c_str())); // Position (x, y) and text

		auto legend = new TLegend(0.7, 0.6, 0.88, 0.88);
		//auto legend = new TLegend(0.12, 0.6, 0.3, 0.88);
		for (const std::string& bkg_group : {"DY", "VV", "VVV", "ttW", "ttZ", "WJ", "ZZ", "ST", "TTbar", "ttH", "ZH"}) {
		    legend->AddEntry(hist[bkg_group], bkg_group.c_str(), "f");
		}
		legend->AddEntry(hist["signal"], "M1000", "lep");
		//legend->Draw();

		std::string X_string;
		if (name.find("_WMt") < name.length()) X_string += "W transverse mass ";
		else if (name.find("_mZ") < name.length()) X_string += "mZ ";
		else if (name.find("_DCH") < name.length()) X_string += "M(ll) of leading pair";
		else if (name.find("_mH") < name.length()) X_string += "mH ";
		else if (name.find("_met") < name.length()) X_string += "Missing E_{T} ";
		else if (name.find("_ST") < name.length()) X_string += "S_{T} ";
		else if (name.find("_pt1") < name.length()) X_string += "pT-1 ";
		else if (name.find("_pt2") < name.length()) X_string += "pT-2 ";
		else if (name.find("_pt3") < name.length()) X_string += "pT-3 ";
		else if (name.find("_pt4") < name.length()) X_string += "Eta-4 ";
		else if (name.find("_eta1") < name.length()) X_string += "Eta-1";
		else if (name.find("_eta2") < name.length()) X_string += "Eta-2";
		else if (name.find("_eta3") < name.length()) X_string += "Eta-3";
		else if (name.find("_eta4") < name.length()) X_string += "Eta-4";
		else if (name.find("_phi1") < name.length()) X_string += "Phi-1";
		else if (name.find("_phi2") < name.length()) X_string += "Phi-2";
		else if (name.find("_phi3") < name.length()) X_string += "Phi-3";
		else if (name.find("_phi4") < name.length()) X_string += "Phi-4";
		else if (name.find("_iso1") < name.length()) X_string += "ISO-1";
		else if (name.find("_iso2") < name.length()) X_string += "ISO-2";
		else if (name.find("_iso3") < name.length()) X_string += "ISO-3";
		else if (name.find("_iso4") < name.length()) X_string += "ISO-4";
		else if (name.find("_dxy1") < name.length()) X_string += "dXY-1";
		else if (name.find("_dxy2") < name.length()) X_string += "dXY-2";
		else if (name.find("_dxy3") < name.length()) X_string += "dXY-3";
		else if (name.find("_dxy4") < name.length()) X_string += "dXY-4";
		else if (name.find("_dZ1") < name.length()) X_string += "dZ-1";
		else if (name.find("_dZ2") < name.length()) X_string += "dZ-2";
		else if (name.find("_dZ3") < name.length()) X_string += "dZ-3";
		else if (name.find("_dZ4") < name.length()) X_string += "dZ-4";
		else if (name.find("cutflow") < name.length()) X_string += "N-1 Cutflow";
		
		
		// Output
		std::string s =  "hist_MY_mll/", s1, s2;
		s1 = s + hist_list[i]+".png";
		//s2 = s + hist_list[i]+".svg";
		char* title1 = const_cast<char*>(s1.c_str());//converting string to char
		//char* title2 = const_cast<char*>(s2.c_str());//converting string to char
		canvas->SaveAs(title1);
		//canvas->SaveAs(title2);
		canvas->Clear();
	}
}
