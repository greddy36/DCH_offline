#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include "include/Xsections.C"

double getBinSignificance(double s, double b) {
    if (s <= 0 or b <= 0) return 0;
    return sqrt(2 * ((s + b) * log(1 + s/b) - s));//Asimov/Posisson approximation
}

double getBinSignificanceWithUncertainty(double s, double b, double sigma_b) {
    if (s <= 0 or b <= 0) return 0;
    if (sigma_b == 0) return getBinSignificance(s, b);

    double term1 = (s + b) * log((s + b) * (b + sigma_b * sigma_b) / (b * b + (s + b) * sigma_b * sigma_b));
    double term2 = (b * b / (sigma_b * sigma_b)) * log(1 + (sigma_b * sigma_b * s) / (b * (b + sigma_b * sigma_b)));
    double Z = sqrt(2 * (term1 - term2));

    return Z;
}


void cummilative_hist(TH1D* histogram, TH1D* cumm_bkg, TH1D* signi_hist, THStack* stack, const char* trend, const char* isSig){
	TH1D* h_cumm = new TH1D("h_cumm", histogram->GetTitle(), histogram->GetNbinsX(), histogram->GetXaxis()->GetXmin() , histogram->GetXaxis()->GetXmax());
	float tmp_val = 0, tmp_denom;
	h_cumm->SetLineWidth(histogram->GetLineWidth());
	h_cumm->SetLineStyle(histogram->GetLineStyle());
	h_cumm->SetFillColor(histogram->GetFillColor());
	h_cumm->SetLineColor(histogram->GetLineColor());
	if (isSig == "Yes"){
		for (int i =0; i < histogram->GetNbinsX(); i++){ 
			if (trend == "inc"){
				tmp_val = histogram->Integral(0,i);
			}
			else if (trend == "dec"){
				tmp_val = histogram->Integral(i,histogram->GetNbinsX()+1);//+1 is to include overflow
			}
			else{
				tmp_val = histogram->GetBinContent(i);
			}
			h_cumm->SetBinContent(i, tmp_val);
			signi_hist->SetBinContent(i, getBinSignificanceWithUncertainty(tmp_val, cumm_bkg->GetBinContent(i),0.1*cumm_bkg->GetBinContent(i)));
		}
		h_cumm->Scale(cumm_bkg->Integral()/h_cumm->Integral());
		h_cumm->Draw("hist same");//signal cummilative hist
		cout<<h_cumm->Integral()<<endl;
	}
	else{//bkgs
		for (int i =0; i < histogram->GetNbinsX(); i++){ 
			if (trend == "inc"){
				tmp_val = histogram->Integral(0,i);
			}
			else if (trend == "dec"){
				tmp_val = histogram->Integral(i,histogram->GetNbinsX()+1);//+1 is to include overflow
			}
			else{
				tmp_val = histogram->GetBinContent(i);
			}
			h_cumm->SetBinContent(i, tmp_val);
			cumm_bkg->SetBinContent(i, cumm_bkg->GetBinContent(i)+tmp_val);
		}
		stack->Add(h_cumm);//bkgs will be stacked
	}		
	h_cumm->Clear();//prevent memory leak
}
void cummilative_hist(TH1D* histogram, TH1D* cumm_bkg, TH1D* signi_hist, THStack* stack, const char* trend){//overloaded function with 3 parameters
	cummilative_hist(histogram, cumm_bkg, signi_hist, stack, trend, "No");
}
	
void plot_2d() {
	    // Categories with input files
	std::string summary_type = "tau_ch", year = "Run2"; const char* trend = "inc";
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
        {"ZH", {"ZHToMuMu_2016.root","ZHToTauTau_2016.root", "GluGluZH_2016.root", "ZHToMuMu_2017.root","ZHToTauTau_2017.root", "GluGluZH_2017.root", "ZHToMuMu_2018.root","ZHToTauTau_2018.root", "GluGluZH_2018.root"}}
    };
    std::map<std::string, std::vector<TFile*>> open_files;
    for (auto& kv : files) {
		for (const auto& fname : kv.second) {
		    TFile* file = new TFile(("hist_peter/" + fname).c_str(), "READ");
		    if (!file || file->IsZombie()) continue;
	        open_files[kv.first].push_back(file);
	    }
	}
	TFile *ifile_D1 = new TFile("hist_peter/HppM500_2016.root","READ");
	
	std::string root_dir[] = {"0tau/","1tau/","2tau/","3tau/"/*,"3lep0tau/","3lep1tau/","3lep2tau/"*/};
	TCanvas* canvas = new TCanvas("canvas", "Stacked Histograms", 800, 700);	
	gStyle->SetOptStat(0);	//gPad->SetLogy();
	for(int j = 0; j < sizeof(root_dir)/sizeof(root_dir[0]); j++){
		std::string hist_name1 = root_dir[j] + "h_mll1";
		std::string hist_name2 = root_dir[j] + "h_mll2";
		
		THStack* bkg_stack = new THStack("bkg_stack", "Mll");
		std::map<std::string, TH1D*> hist1 hist2;
		std::map<std::string, int> fill_colors = {
			{"DY", 7}, {"VV", 8}, {"VVV", 6}, {"ttW", 4}, {"ttZ", 2}, {"WJ", 9}, {"ZZ", 5},
			{"ST", 30}, {"TTbar", 46}, {"ttH", 28},{"ZH", 29}
		};
		int bins = 0;
		for (auto& kv : open_files) {
			TH1D* tmp = (TH1D*)ifile_D1->Get(hist_name1.c_str());
			hist1[kv.first]=(TH1D*)tmp->Clone();
			hist2[kv.first]=(TH1D*)tmp->Clone();
			hist1[kv.first]->Sumw2(); hist1[kv.first]->Reset();
			hist2[kv.first]->Sumw2(); hist2[kv.first]->Reset();
			for (auto* f : kv.second) {
			    TH1D* h1 = dynamic_cast<TH1D*>(f->Get(hist_name1.c_str()));
			    TH1D* h2 = dynamic_cast<TH1D*>(f->Get(hist_name2.c_str()));
			    if (!h1 or !h2) continue;
			    h1->Scale(applyXSec(f));
			    h2->Scale(applyXSec(f));
			    //h->Rebin(5);
				hist1[kv.first]->Add(h1);
				hist2[kv.first]->Add(h2);
			}
			if (hist1[kv.first] and hist2[kv.first]) {
				hist1[kv.first]->SetFillColor(fill_colors[kv.first]);
				hist2[kv.first]->SetFillColor(fill_colors[kv.first]);
				bins = hist1[kv.first]->GetNbinsX();
			}
		}
		
		hist1["VV"]->Scale(1.12631); hist2["VV"]->Scale(1.12631);
		hist1["ZZ"]->Scale(1.31366); hist2["ZZ"]->Scale(1.31366);
 		
		//################## Significance ########################
		TH1D* signi_hist = new TH1D("signi_hist", "", hist1["signal"]->GetNbinsX(), hist1["signal"]->GetXaxis()->GetXmax() , hist1["signal"]->GetXaxis()->GetXmax());
		signi_hist->SetLineWidth(3);
		signi_hist->SetLineStyle(2);
		signi_hist->SetLineColor(1);
		//########################################################

		TH1D *cumm_bkg = new TH1D("cumm_bkg", "", hist1["signal"]->GetNbinsX(), hist1["signal"]->GetXaxis()->GetXmax() , hist1["signal"]->GetXaxis()->GetXmax());
		
		for (const std::string& bkg_group : {"DY", "VV", "VVV", "ttW", "ttZ", "WJ", "ZZ", "ST", "TTbar", "ttH", "ZH"}) {
			cummilative_hist(hist1[bkg_group], cumm_bkg,  signi_hist, bkg_stack, trend);
		}
		bkg_stack->Draw("HIST");
		
		hist1["signal"]->SetLineColor(2);
		hist1["signal"]->SetLineWidth(2);
		//hist1["signal"]->Scale(10);
		//hist1["signal"]->Draw("SAME");
		cummilative_hist(hist1["signal"], cumm_bkg, signi_hist, bkg_stack, trend,"Yes");
		
		signi_hist->Scale(bkg_stack->GetMaximum()/signi_hist->GetMaximum());
		signi_hist->Draw("HIST SAME");
		
		// Create a TLatex object
		TLatex latex;
		latex.SetNDC(); // Use normalized coordinates (0 to 1)
		latex.SetTextSize(0.04); // Set text size
		latex.SetTextAlign(31); // Align right (horizontal) and top (vertical)
		latex.DrawLatex(0.95, 0.95, const_cast<char*>(year.c_str())); // Position (x, y) and text

		auto legend = new TLegend(0.7, 0.6, 0.88, 0.88);
		//auto legend = new TLegend(0.12, 0.6, 0.3, 0.88);
		for (const std::string& bkg_group : {"DY", "VV", "VVV", "ttW", "ttZ", "WJ", "ZZ", "ST", "TTbar", "ttH", "ZH"}) {
			legend->AddEntry(hist1[bkg_group], bkg_group.c_str(), "f");
		}
		legend->AddEntry(hist1["signal"], "M500", "lep");
		legend->AddEntry(signi_hist, "Sigificance", "lep");
		//legend->Draw();

		// Show the canvas
		canvas->Update();
		canvas->Modified();
		
		std::string s =  "hist_peter/";
		s = s + hist_name1+ "_"+ trend+".png";
		char* title = const_cast<char*>(s.c_str());//converting string to char
		canvas->SaveAs(title);
		canvas->Clear();
	}//root_dir loop
}
