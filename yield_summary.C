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
#include "include/XSections.C"

void yield_summary() {
    gStyle->SetOptStat(0);
    TCanvas* canvas = new TCanvas("canvas", "Stacked histograms", 800, 700);

    // Split canvas for main plot and ratio plot
    TPad* pad1 = new TPad("pad1", "Top pad", 0.0, 0.3, 1.0, 1.0);
    TPad* pad2 = new TPad("pad2", "Bottom pad", 0.0, 0.0, 1.0, 0.3);
    pad1->SetBottomMargin(0.01);
    pad2->SetTopMargin(0.01);
    pad2->SetBottomMargin(0.3);
    pad1->Draw();
    pad2->Draw();
	
	THStack* bkg_stack;
	std::string summary_type = "tau_ch", year = "Run2";
    // Define histograms to retrieve
    std::vector<std::string> hist_list;
    if (summary_type == "tau_ch") {
    	hist_list = { "0tau/h_cat","1tau/h_cat","2tau/h_cat","3tau/h_cat","3lep0tau/h_cat","3lep1tau/h_cat","3lep2tau/h_cat"};
    	bkg_stack = new THStack("bkg_stack", "Yield summary in VR;;Events");
    }
    else if  (summary_type == "3lep") {
    	hist_list = {"h_met_ee","h_met_eee","h_met_eem","h_met_eet","h_metv_ett","h_met_mm","h_met_emm","h_met_mmm","h_met_mmt","h_metv_mtt"};
   		bkg_stack = new THStack("bkg_stack", "2l and 3l channel summary in Z-window;;Events");
    }
    else if  (summary_type == "3lep-veto") {
    	hist_list = {"h_metv_ee","h_metv_eee","h_metv_eem","h_metv_eet","h_met_ett","h_metv_mm","h_metv_emm","h_metv_mmm","h_metv_mmt","h_met_mtt"};
    	bkg_stack = new THStack("bkg_stack", "2l and 3l channel summary in Z-veto;;Events");
    }
    else if  (summary_type == "4lep") { 
    	hist_list = {"h_met_eeee","h_met_eeem","h_met_eemm","h_met_mmem","h_met_mmmm","h_met_eeet","h_met_eemt","h_met_eett","h_met_emtt","h_met_emmt","h_met_ettt","h_met_mmmt","h_met_mmtt","h_met_mttt"};
    	bkg_stack = new THStack("bkg_stack", "4l channel summary in Z-window;;Events");
    }
    else if  (summary_type == "4lep-veto") {
    	hist_list = {"h_metv_eeee","h_metv_eeem","h_metv_eemm","h_metv_mmem","h_metv_mmmm","h_metv_eeet","h_metv_eemt","h_metv_eett","h_metv_emtt","h_metv_emmt","h_metv_ettt","h_metv_mmmt","h_metv_mmtt","h_metv_mttt"};
    	bkg_stack = new THStack("bkg_stack", "4l channel summary in Z-veto;;Events");
    }
    int bins = hist_list.size();

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
        {"DY",    {"DYJetsToLLM10to50_2018.root", "DYJetsToLLM50_2018.root"}},
        {"VV",    {"WW_2018.root", "WWTo2L2Nu_2018.root", "WZTo2Q2L_2018.root", "WZTo3LNu_2018.root"}},
        {"VVV",   {"WWW_2018.root", "WZZ_2018.root", "ZZZ_2018.root"}},
        {"ttV",   {"ttWJets_2018.root", "ttZJets_2018.root"}},
        {"WJ",    {"WJetsToLNu_NLO_2018.root", "WJetsToLNu_HT-70To100_2018.root", "WJetsToLNu_HT-100To200_2018.root", 
                   "WJetsToLNu_HT-200To400_2018.root", "WJetsToLNu_HT-400To600_2018.root", 
                   "WJetsToLNu_HT-600To800_2018.root", "WJetsToLNu_HT-800To1200_2018.root", "WJetsToLNu_HT-1200To2500_2018.root", "WJetsToLNu_HT-2500ToInf_2018.root"}},
        {"ZZ",    {"ZZTo2L2Nu_2018.root", "ZZTo2Q2L_2018.root", "ZZTo4L_2018.root"}},
        {"ST",    {"ST_s-channel_2018.root", "ST_t-channel_antitop_2018.root", "ST_t-channel_top_2018.root", 
                   "ST_tW_antitop_2018.root", "ST_tW_top_2018.root"}},
        {"TTbar", {"TTTo2L2Nu_2018.root", "TTToSemiLeptonic_2018.root", "TTToHadronic_2018.root"}},
        {"other", {"ttHToTauTau_2018.root", "ZHToMuMu_2018.root","ZHToTauTau_2018.root", "GluGluZH_2018.root", "ttHToEE_2018.root", "ttHTo2L2Nu_2018.root"}},
        {"data",  {"SingleElectron_2018.root","EGamma_2018.root", "SingleMuon_2018.root"}}
    };
    else if (year == "Run2") files = {
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
        {"ZH", {"ZHToMuMu_2016.root","ZHToTauTau_2016.root", "GluGluZH_2016.root", "ZHToMuMu_2017.root","ZHToTauTau_2017.root", "GluGluZH_2017.root", "ZHToMuMu_2018.root","ZHToTauTau_2018.root", "GluGluZH_2018.root"}},
        {"other", {"ttHJetToNonbb_2016.root","ttHJetToNonbb_2017.root","ttHJetToNonbb_2018.root","TWZToLL_2016.root","TWZToLL_2017.root","TWZToLL_2018.root","HZJ_HToWWTo2L2Nu_ZTo2L_2016.root","HZJ_HToWWTo2L2Nu_ZTo2L_2017.root","HZJ_HToWWTo2L2Nu_ZTo2L_2018.root"}},
        {"data",  {"SingleElectron_2016.root","EGamma_2016.root", "SingleMuon_2016.root","SingleElectron_2017.root","EGamma_2017.root", "SingleMuon_2017.root","SingleElectron_2018.root","EGamma_2018.root", "SingleMuon_2018.root"}}
    };
	   
    std::map<std::string, TH1D*> h_summaries;
    std::map<std::string, int> fill_colors = {
        {"DY", 7}, {"VV", 8}, {"VVV", 6}, {"ttW", 4}, {"ttZ", 2}, {"WJ", 9}, {"ZZ", 5},
		    {"ST", 30}, {"TTbar", 46}, {"other", 28},{"ZH", 29}, {"data", 1}
    };

    // Open files
    std::map<std::string, std::vector<TFile*>> open_files;
    for (auto& kv : files) {
        for (const auto& fname : kv.second) {
        	TFile* file;
            if (summary_type == "tau_ch") file = new TFile(("hist_VR/" + fname).c_str(), "READ");
            else file = new TFile(("hist_test_nopair/" + fname).c_str(), "READ");
            if (!file || file->IsZombie()) continue;
	        open_files[kv.first].push_back(file);
        }
        h_summaries[kv.first] = new TH1D(("h_summary_" + kv.first).c_str(), "Yields;;Yield", bins, 0.5, bins + 0.5);
        h_summaries[kv.first]->Sumw2();
        h_summaries[kv.first]->SetFillColor(fill_colors[kv.first]);
    }

	
    // Loop over histograms and fill yield summaries and ratio plot
    //double tot_uncert_quadr[bins];
    for (int i = 0; i < bins; ++i) {
        std::string hist_name = hist_list[i];
        for (auto& kv : open_files) {
            double total = 0; 
            TH1D* h_sum = new TH1D("h_sum"," ;;;",1,0,1); h_sum->Sumw2();
            for (auto* f : kv.second) {
                TH1D* h = (TH1D*)f->Get(hist_name.c_str());
                if (h) {
                	h_sum->Sumw2();
                	h->Scale(applyXSec(f->GetName(), f->Get("hnevts")->Integral()));
                	h->Rebin(h->GetNbinsX());
                	double stat_err = h->GetBinError(1);//poisson error
                	double sys_err = h->GetBinContent(1)*XSec_Uncert(f->GetName())/100;
                	double tot_uncert_quadr = (stat_err*stat_err + sys_err*sys_err);
                	if (kv.first != "data") {
                		if(summary_type == "tau_ch"){
                			if (hist_name.find("3lep") < hist_name.length()) tot_uncert_quadr += fake_uncert_squared("3lep", f->GetName())*h->GetBinContent(1)*h->GetBinContent(1);
                			else tot_uncert_quadr += fake_uncert_squared("4lep", f->GetName())*h->GetBinContent(1)*h->GetBinContent(1);
                		}
                		else if(hist_name != "h_met_ee" and hist_name != "h_met_mm" and hist_name != "h_metv_ee" and hist_name != "h_metv_mm") tot_uncert_quadr += fake_uncert_squared(summary_type, f->GetName())*h->GetBinContent(1)*h->GetBinContent(1);
                	}
                	h->SetBinError(1,sqrt(tot_uncert_quadr));
                	h_sum->Add(h);
                }
            }
            h_summaries[kv.first]->SetBinContent(i+1, h_sum->GetBinContent(1));
            h_summaries[kv.first]->SetBinError(i+1, h_sum->GetBinError(1));
            cout<<i+1<<"\t"<<kv.first<<"\t"<<h_summaries[kv.first]->GetBinContent(i+1)<<endl;
        }
    }
    //========================scale facotrs===============
	h_summaries["ZZ"]->Scale(1.30291);
	h_summaries["VV"]->Scale(1.03002);
	//h_summaries["DY"]->SetBinContent(4, h_summaries["DY"]->GetBinContent(4)*1.21);
	//h_summaries["DY"]->SetBinContent(9, h_summaries["DY"]->GetBinContent(9)*1.21);
	//h_summaries["TTbar"]->SetBinContent(6, h_summaries["TTbar"]->GetBinContent(6)*2.5);
	//h_summaries["TTbar"]->SetBinContent(1, h_summaries["TTbar"]->GetBinContent(1)*1.5);
	
	//====================================================
    // Stack backgrounds
    TH1D* h_bkg_total = (TH1D*)h_summaries["DY"]->Clone("h_bkg_total");
    h_bkg_total->Reset(); h_bkg_total->Sumw2();
    for (const std::string& bkg_group : {"DY", "VV", "VVV", "ttW","ttZ", "WJ", "ZZ","ZH", "ST", "TTbar", "other"}) {
        bkg_stack->Add(h_summaries[bkg_group]);
        bkg_stack->SetMinimum(1); // Show zero bins
        h_bkg_total->Add(h_summaries[bkg_group]);
    }
    
    TH1D* h_mc_uncert_band = (TH1D*) h_bkg_total->Clone("h_mc_uncert_band");
    h_mc_uncert_band->Sumw2();
	h_mc_uncert_band->Reset(); // we'll fill the error by hand
	for (int i = 0; i < bins; ++i) {
		h_mc_uncert_band->SetBinContent(i+1, 1.0);  // center at ratio = 1
		if (h_bkg_total->GetBinContent(i+1) != 0) h_mc_uncert_band->SetBinError(i+1, h_bkg_total->GetBinError(i+1)/h_bkg_total->GetBinContent(i+1));//scaling error with bin content
		else h_mc_uncert_band->SetBinError(i+1,0);
	} 
	
    // Draw main plot
    pad1->cd();
    gPad->SetLogy(1);
    bkg_stack->Draw("hist");
    double pad_max = std::max(bkg_stack->GetMaximum(),h_summaries["data"]->GetMaximum());
	bkg_stack->SetMaximum(1.1*pad_max);
    h_summaries["data"]->SetMarkerStyle(20);
    h_summaries["data"]->SetMarkerColor(kBlack);
    h_summaries["data"]->Draw("E SAME");

	// Create a TLatex object
	TLatex latex;
	latex.SetNDC(); // Use normalized coordinates (0 to 1)
	latex.SetTextSize(0.04); // Set text size
	latex.SetTextAlign(31); // Align right (horizontal) and top (vertical)
	latex.DrawLatex(0.95, 0.95, const_cast<char*>(year.c_str())); // Position (x, y) and text

    //auto legend = new TLegend(0.7, 0.6, 0.88, 0.88);
    auto legend = new TLegend(0.12, 0.6, 0.3, 0.88);
    for (const std::string& bkg_group : {"DY", "VV", "VVV", "ttW","ttZ", "WJ", "ZZ","ZH", "ST", "TTbar", "other"}) {
        legend->AddEntry(h_summaries[bkg_group], bkg_group.c_str(), "f");
    }
    legend->AddEntry(h_summaries["data"], "Data", "lep");
    //legend->Draw();

    // Ratio histogram: data / MC
    TH1D* h_ratio = (TH1D*)h_summaries["data"]->Clone("h_ratio");
    h_ratio->SetTitle(""); // Remove the title for the ratio plot
	h_ratio->Divide(h_bkg_total);
	h_ratio->SetLineColor(kBlack);
	h_ratio->SetMarkerStyle(2);
	h_ratio->GetYaxis()->SetTitle("Data/MC");
	h_ratio->GetYaxis()->SetNdivisions(505);
	h_ratio->GetYaxis()->SetTitleSize(0.1);
	h_ratio->GetYaxis()->SetTitleOffset(0.5);
	h_ratio->GetYaxis()->SetLabelSize(0.07);
	h_ratio->GetXaxis()->SetTitleSize(0.1);
	
	if (summary_type == "tau_ch") {
		h_ratio->GetXaxis()->SetBinLabel(1,"0#tau 4l");
		h_ratio->GetXaxis()->SetBinLabel(2,"1#tau 4l");
		h_ratio->GetXaxis()->SetBinLabel(3,"2#tau 4l");
		h_ratio->GetXaxis()->SetBinLabel(4,"3#tau 4l");
		h_ratio->GetXaxis()->SetBinLabel(5,"0#tau 3l");
		h_ratio->GetXaxis()->SetBinLabel(6,"1#tau 3l");
		h_ratio->GetXaxis()->SetBinLabel(7,"2#tau 3l");
	}	
	else if (summary_type == "3lep" or summary_type == "3lep-veto" ) {
		h_ratio->GetXaxis()->SetBinLabel(1,"ee");
		h_ratio->GetXaxis()->SetBinLabel(2,"ee+e");
		h_ratio->GetXaxis()->SetBinLabel(3,"ee+#mu");
		h_ratio->GetXaxis()->SetBinLabel(4,"ee+#tau");
		h_ratio->GetXaxis()->SetBinLabel(5,"e#tau#tau");
		h_ratio->GetXaxis()->SetBinLabel(6,"#mu#mu");
		h_ratio->GetXaxis()->SetBinLabel(7,"#mu#mu+e");
		h_ratio->GetXaxis()->SetBinLabel(8,"#mu#mu+#mu");
		h_ratio->GetXaxis()->SetBinLabel(9,"#mu#mu+#tau");
		h_ratio->GetXaxis()->SetBinLabel(10,"#mu#tau#tau");
	}
	else if (summary_type == "4lep" or summary_type == "4lep-veto") {
		h_ratio->GetXaxis()->SetBinLabel(1,"eeee");
		h_ratio->GetXaxis()->SetBinLabel(2,"eee#mu");
		h_ratio->GetXaxis()->SetBinLabel(3,"ee#mu#mu");
		h_ratio->GetXaxis()->SetBinLabel(4,"#mu#mue#mu");
		h_ratio->GetXaxis()->SetBinLabel(5,"#mu#mu#mu#mu");
		h_ratio->GetXaxis()->SetBinLabel(6,"eee#tau");
		h_ratio->GetXaxis()->SetBinLabel(7,"ee#mu#tau");
		h_ratio->GetXaxis()->SetBinLabel(8,"ee#tau#tau");
		h_ratio->GetXaxis()->SetBinLabel(9,"e#mu#tau#tau");
		h_ratio->GetXaxis()->SetBinLabel(10,"e#mu#mu#tau");
		h_ratio->GetXaxis()->SetBinLabel(11,"e#tau#tau#tau");
		h_ratio->GetXaxis()->SetBinLabel(12,"#mu#mu#mu#tau");
		h_ratio->GetXaxis()->SetBinLabel(13,"#mu#mu#tau#tau");
		h_ratio->GetXaxis()->SetBinLabel(14,"#mu#tau#tau#tau");
	}
	
	h_ratio->GetXaxis()->SetLabelSize(0.15);
	h_ratio->SetMinimum(0); // Set the minimum y-value for the ratio plot
	h_ratio->SetMaximum(2); // Set the maximum y-value for the ratio plot
	
    // Draw ratio plot
    pad2->cd();
    h_ratio->SetMinimum(0.0);
    h_ratio->SetMaximum(2.0);
    h_ratio->Draw("E");
    
    h_mc_uncert_band->SetFillColor(kGray+2);
	h_mc_uncert_band->SetFillStyle(3001); // hatched
	h_mc_uncert_band->SetLineColor(0);
	h_mc_uncert_band->Draw("E2 same"); // as a filled error band
	
    // Draw lines for reference
	TLine *line1 = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
	TLine *line2 = new TLine(h_ratio->GetXaxis()->GetXmin(), 0.5, h_ratio->GetXaxis()->GetXmax(), 0.5);
	TLine *line3 = new TLine(h_ratio->GetXaxis()->GetXmin(), 1.5, h_ratio->GetXaxis()->GetXmax(), 1.5);
	line1->SetLineStyle(2);line2->SetLineStyle(2);line3->SetLineStyle(2);
	line1->Draw();line2->Draw();line3->Draw();

    // Output
    //std::string pdfname = "summary_"+summary_type+"_"+year+".pdf";
    std::string pngname = "summary_"+summary_type+"_"+year+".png";
    //canvas->SaveAs(const_cast<char*>(pdfname.c_str()));
    canvas->SaveAs(const_cast<char*>(pngname.c_str()));
}
