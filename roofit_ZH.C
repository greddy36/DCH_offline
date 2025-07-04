#include <RooDataSet.h>
#include <RooExponential.h>
#include <RooPlot.h>
#include <RooRealVar.h>
#include <TCanvas.h>
#include "include/XSections.C"

using namespace RooFit;

void roofit_ZH(){
	std::string year = "run2";
	
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
        {"other", {"ttHToTauTau_2016.root", "ZHToMuMu_2016.root","ZHToTauTau_2016.root", "GluGluZH_2016.root"}},
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
        {"other", {"ttHToTauTau_2017.root", "ZHToMuMu_2017.root","ZHToTauTau_2017.root", "GluGluZH_2017.root"}},
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
        {"other", {"ttHToTauTau_2018.root", "ZHToMuMu_2018.root","ZHToTauTau_2018.root", "GluGluZH_2018.root"}},
        {"data",  {"SingleElectron_2018.root","EGamma_2018.root", "SingleMuon_2018.root"}}
    };
    else if (year == "run2") files = {
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
    
    std::map<std::string, TH1D*> h_bkg_group;
    std::map<std::string, int> fill_colors = {
        {"DY", 7}, {"VV", 8}, {"VVV", 6}, {"ttW", 4}, {"ttZ", 2}, {"WJ", 9}, {"ZZ", 5},
		    {"ST", 30}, {"TTbar", 46}, {"other", 28},{"ZH", 29}, {"data", 1}
    };

    // Open files
    std::map<std::string, std::vector<TFile*>> open_files;
    for (auto& kv : files) {
        for (const auto& fname : kv.second) {
			TFile* file = new TFile(("hist_CR/" + fname).c_str(), "READ");
            if (!file || file->IsZombie()) continue;
	        open_files[kv.first].push_back(file);
	        //cout<<fname<<endl;
        }
    }
   	std::map<std::string, double> tot_uncert_quadr;
    for (auto& kv : open_files) {
			for (auto* f : kv.second) {
				TH1D* h = (TH1D*)f->Get("0tau/h_ST");
				if(!h) continue;
				h->Sumw2();
		       	h->Scale(applyXSec(f));
				if (!h_bkg_group[kv.first]){
					h_bkg_group[kv.first]= dynamic_cast<TH1D*>(h);
                	tot_uncert_quadr[kv.first] = fake_uncert_squared("4lep", f->GetName())*h->Integral()*h->Integral();
        		}
		       	else {
		       		h_bkg_group[kv.first]->Add(h);
		       		tot_uncert_quadr[kv.first] += fake_uncert_squared("4lep", f->GetName())*h->Integral()*h->Integral();
		       	}
		       	cout<<kv.first<<"\t"<<tot_uncert_quadr[kv.first]<<"\t"<<h_bkg_group[kv.first]->Integral()<<endl;
			}
	}
	//.h_bkg_group["ZZ"]->Scale(1.30897);
	//h_bkg_group["ttZ"]->Scale(0.671211);
	//h_bkg_group["ZH"]->Add(h_bkg_group["ttZ"]);
	TH1D* h_other_bkg = (TH1D*)h_bkg_group["other"]->Clone(); 
	h_other_bkg->Add(h_bkg_group["DY"]);
	h_other_bkg->Add(h_bkg_group["ZZ"]);
	h_other_bkg->Add(h_bkg_group["VVV"]);
	h_other_bkg->Add(h_bkg_group["ttW"]);
	h_other_bkg->Add(h_bkg_group["ttZ"]);
	h_other_bkg->Add(h_bkg_group["VV"]);
	h_other_bkg->Add(h_bkg_group["WJ"]);
	h_other_bkg->Add(h_bkg_group["ST"]);
	h_other_bkg->Add(h_bkg_group["TTbar"]);
	//Define normalizations and uncertainty
	double other_nominal = h_other_bkg->Integral();
	double other_uncert = sqrt(tot_uncert_quadr["other"]+tot_uncert_quadr["DY"]+tot_uncert_quadr["ttW"]+tot_uncert_quadr["ttZ"]+tot_uncert_quadr["VV"]+tot_uncert_quadr["ZZ"]+tot_uncert_quadr["VVV"]+tot_uncert_quadr["WJ"]+tot_uncert_quadr["ST"]+tot_uncert_quadr["TTbar"])/h_other_bkg->Integral();
	//cout<<other_uncert<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
	
	RooRealVar x("x", "MET variable", 0, 200);//Discriminating Variable

	RooDataHist other_hist("other_hist", "Other", x, Import(*h_other_bkg));
	RooHistPdf other_pdf("other_pdf", "Other PDF", x, other_hist);
	
	//Add Gaussian constraints for uncertainty
	RooRealVar other_nuis("other_nuis", "Other nuisance", 0, -5, 5);//initialize with 0 as the scaling to nominal value happens in RooFormulaVar
	RooGaussian other_constraint("other_constraint", "Other constraint", other_nuis, RooConst(0.), RooConst(1.));//centers at 0. and varies by +-1.
	RooFormulaVar other_norm_constrained("other_norm_constrained", "@0*(1 + @1*@2)", RooArgList(RooConst(other_nominal), other_nuis, other_uncert));
	
	RooRealVar other_norm("other_norm", "Other yield", h_other_bkg->Integral(), 0.0, 10.0 * h_other_bkg->Integral());
RooExtendPdf other_ext("other_ext", "Other Extended PDF", other_pdf, other_norm_constrained);

	//ZH component
	RooDataHist zh_hist("zh_hist", "ZH", x, Import(*h_bkg_group["ZH"]));
	RooHistPdf zh_pdf("zh_pdf", "ZH PDF", x, zh_hist);
	RooRealVar zh_norm("zh_norm", "ZH yield", h_bkg_group["ZH"]->Integral(), 0.0, 10.0 * h_bkg_group["ZH"]->Integral());
	RooExtendPdf zh_ext("zh_ext", "ZH Extended", zh_pdf, zh_norm);

	//Build full model with constraints
	RooAddPdf model_core("model_core", "Total Model without constraints", RooArgList(zh_ext, other_ext));
	RooProdPdf model("model", "Model with constraints", RooArgSet(model_core, other_constraint));

	//Fit to data
	RooDataHist data_obs("data_obs", "Observed Data", x, Import(*h_bkg_group["data"]));
	model.fitTo(data_obs, Extended(true), PrintLevel(-1));

	RooPlot* frame = x.frame();
	data_obs.plotOn(frame);
	model.plotOn(frame);//full model, blue by default
	model.plotOn(frame, Components("zh_ext"), LineColor(3));
	model.plotOn(frame, Components("other_ext"), LineColor(2));
	
	frame->Draw();
	double zh_fitted = zh_norm.getVal();
	double zh_nominal = h_bkg_group["ZH"]->Integral();
	double zh_fit_err = zh_norm.getError(); 
	double scale_factor_ZH = zh_fitted / zh_nominal;
	double sf_err = zh_fit_err / zh_nominal;

	std::cout << "ZH scale factor = " << scale_factor_ZH <<"+-"<< sf_err<< std::endl;

}
