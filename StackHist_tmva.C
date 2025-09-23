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

void StackHist_tmva() {
	std::string summary_type = "tau_ch", year = "Run2";
    // Define histograms to retrieve
    const char *dir_list[] = {"0tau","1tau","2tau","3tau","3lep0tau","3lep1tau","3lep2tau"};
	
    // Categories with input files
    std::map<std::string, std::vector<std::string>> files;
	if (year == "Run2") files = {
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
        {"ZH", {"ZHToMuMu_2016.root","ZHToTauTau_2016.root", "GluGluZH_2016.root", "ZHToMuMu_2017.root","ZHToTauTau_2017.root", "GluGluZH_2017.root", "ZHToMuMu_2018.root","ZHToTauTau_2018.root", "GluGluZH_2018.root"}},
 
    };
    std::map<std::string, std::vector<TFile*>> open_files;
    for (auto& kv : files) {
		for (const auto& fname : kv.second) {
		    TFile* file = new TFile(("mva_hist_MY/" + fname).c_str(), "READ");
		    if (!file || file->IsZombie()) continue;
	        open_files[kv.first].push_back(file);
	    }
	}
	TFile *ifile_D1 = new TFile("mva_hist_MY/HppM500_2016.root","READ");
  
	for (int i = 0; i < sizeof(dir_list)/sizeof(dir_list[0]); i++) {
		gStyle->SetOptStat(0);
		TCanvas* canvas = new TCanvas("canvas", "Stacked histograms", 800, 700);
		std::string name = dir_list[i];
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
			hist[kv.first]= new TH1D("hist", "", 100, -1, 1);
			for (auto* f : kv.second) {
				TDirectory *dir = (TDirectory*)f->Get(name.c_str());
				TTree *tree = (TTree*)dir->Get("Events");
				double evtwt;
				tree->SetBranchAddress("evtwt",&evtwt);
				tree->Draw("mvaScore >> h(100, -1, 1)","evtwt");
				
				//tree->Draw("mll1 >> h(100, 0, 1500)", "evtwt");
		        TH1D* h = (TH1D*)gDirectory->Get("h");//from memory
		        if (!h) continue;
		        //h->Rebin(5);
				hist[kv.first]->Add(h);
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
		h_bkg_total->Sumw2();
		h_bkg_total->Reset();
		for (const std::string& bkg_group : {"DY", "VV", "VVV", "ttW", "ttZ", "WJ", "ZZ", "ST", "TTbar", "ttH", "ZH"}) {
		    bkg_stack->Add(hist[bkg_group]);
		    h_bkg_total->Add(hist[bkg_group]);
		}
		
		TH1D* h_mc_uncert_band = (TH1D*) h_bkg_total->Clone("h_mc_uncert_band");
		h_mc_uncert_band->Sumw2();
		h_mc_uncert_band->Reset(); // we'll fill the error by hand
		for (int j = 1; j <= bins; j++) {
			h_mc_uncert_band->SetBinContent(j, 1.0);  // center at ratio = 1
			if (h_bkg_total->GetBinContent(j) > 0) h_mc_uncert_band->SetBinError(j, h_bkg_total->GetBinError(j)/h_bkg_total->GetBinContent(j));//scaling error with bin content
			else h_mc_uncert_band->SetBinError(j,0);
			//cout<<h_bkg_total->GetBinError(j)<<"\t"<<h_bkg_total->GetBinContent(j)<<endl;
		}
		
		// Draw main plot
		//gPad->SetLogy(1);
		bkg_stack->Draw("hist");

		bkg_stack->GetYaxis()->SetTitle("Events");
		bkg_stack->GetXaxis()->SetTitle("MVA score");
		//Signal
		hist["signal"]->SetLineStyle(5);
		hist["signal"]->SetLineColor(2);
		//hist["signal"]->Scale(100);
		hist["signal"]->Scale(h_bkg_total->Integral()/hist["signal"]->Integral());
		hist["signal"]->SetBinContent(bins, hist["signal"]->GetBinContent(bins)+hist["signal"]->GetBinContent(bins+1));
		hist["signal"]->Draw("hist SAME");
		cout<<hist["signal"]->Integral()<<endl;
		
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
		legend->AddEntry(hist["signal"], "M500", "lep");
		legend->Draw();

		std::string X_string;
		if (name.find("_WMt") < name.length()) X_string += "W transverse mass ";
		else if (name.find("_mZ") < name.length()) X_string += "mZ ";
		else if (name.find("_mll") < name.length()) X_string += "M(ll) of leading pair";
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
		else if (name.find("mvaScore") < name.length()) X_string += "N-1 Cutflow";
		
		
		// Output
		std::string s =  "mva_hist_MY/", s1, s2;
		s1 = s + dir_list[i]+".png";
		//s2 = s + dir_list[i]+".svg";
		char* title1 = const_cast<char*>(s1.c_str());//converting string to char
		//char* title2 = const_cast<char*>(s2.c_str());//converting string to char
		canvas->SaveAs(title1);
		//canvas->SaveAs(title2);
		canvas->Clear();
	}
}
