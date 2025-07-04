#include <RooDataSet.h>
#include <RooExponential.h>
#include <RooPlot.h>
#include <RooRealVar.h>
#include <TCanvas.h>
#include "include/XSections.C"

using namespace RooFit;

void roofit_test(){
	std::string year = "run2";
	
    // Categories with input files
    std::map<std::string, std::vector<std::string>> files;
	if (year == "run2") files = {
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
			TFile* file = new TFile(("hist_CR_ZH/" + fname).c_str(), "READ");
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
	h_bkg_group["ZZ"]->Scale(1.30897);
	TH1D* h_other_bkg = (TH1D*)h_bkg_group["other"]->Clone(); 
	h_other_bkg->Add(h_bkg_group["DY"]);
	h_other_bkg->Add(h_bkg_group["VVV"]);
	h_other_bkg->Add(h_bkg_group["ttW"]);
	h_other_bkg->Add(h_bkg_group["WJ"]);
	h_other_bkg->Add(h_bkg_group["ST"]);
	h_other_bkg->Add(h_bkg_group["TTbar"]);
	//Define normalizations and uncertainty
	double other_nominal = h_other_bkg->Integral();
	double other_uncert = sqrt(tot_uncert_quadr["other"]+tot_uncert_quadr["DY"]+tot_uncert_quadr["VV"]+tot_uncert_quadr["VVV"]+tot_uncert_quadr["ttW"]+tot_uncert_quadr["WJ"]+tot_uncert_quadr["ST"]+tot_uncert_quadr["TTbar"])/h_other_bkg->Integral();
	//cout<<other_uncert<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
	
	RooRealVar x("x", "S_{T} variable", 0, 1000);//Discriminating Variable

	RooDataHist other_hist("other_hist", "Other", x, Import(*h_other_bkg));
	RooHistPdf other_pdf("other_pdf", "Other PDF", x, other_hist);
	
	//Add Gaussian constraints for uncertainty
	RooRealVar other_nuis("other_nuis", "Other nuisance", 0, -5, 5);//initialize with 0 as the scaling to nominal value happens in RooFormulaVar
	RooGaussian other_constraint("other_constraint", "Other constraint", other_nuis, RooConst(0.), RooConst(1.));//centers at 0. and varies by +-1.
	RooFormulaVar other_norm_constrained("other_norm_constrained", "@0*(1 + @1*@2)", RooArgList(RooConst(other_nominal), other_nuis, other_uncert));
	
	RooRealVar other_norm("other_norm", "Other yield", h_other_bkg->Integral(), 0.0, 10.0 * h_other_bkg->Integral());
RooExtendPdf other_ext("other_ext", "Other Extended PDF", other_pdf, other_norm_constrained);

	//ZZ component
	RooDataHist zz_hist("zz_hist", "ZZ", x, Import(*h_bkg_group["ZZ"]));
	RooHistPdf zz_pdf("zz_pdf", "ZZ PDF", x, zz_hist);
	RooRealVar zz_norm("zz_norm", "ZZ yield", h_bkg_group["ZZ"]->Integral(), 0.0, 10.0 * h_bkg_group["ZZ"]->Integral());
	RooExtendPdf zz_ext("zz_ext", "ZZ Extended", zz_pdf, zz_norm);

	// We'll now refactor to include VV, ZH, and ttZ scale factors

	// --- Create PDFs and normalizations for each background ---

	// VV
	RooDataHist vv_hist("vv_hist", "VV", x, Import(*h_bkg_group["VV"]));
	RooHistPdf vv_pdf("vv_pdf", "VV PDF", x, vv_hist);
	RooRealVar vv_norm("vv_norm", "VV yield", h_bkg_group["VV"]->Integral(), 0.0, 10.0 * h_bkg_group["VV"]->Integral());
	RooExtendPdf vv_ext("vv_ext", "VV Extended", vv_pdf, vv_norm);

	// ZH
	RooDataHist zh_hist("zh_hist", "ZH", x, Import(*h_bkg_group["ZH"])); // assuming 'other' includes ZH; otherwise isolate ZH hist
	RooHistPdf zh_pdf("zh_pdf", "ZH PDF", x, zh_hist);
	RooRealVar zh_norm("zh_norm", "ZH yield", h_bkg_group["ZH"]->Integral(), 0.0, 10.0 * h_bkg_group["ZH"]->Integral());
	RooExtendPdf zh_ext("zh_ext", "ZH Extended", zh_pdf, zh_norm);

	// ttZ
	RooDataHist ttz_hist("ttz_hist", "ttZ", x, Import(*h_bkg_group["ttZ"]));
	RooHistPdf ttz_pdf("ttz_pdf", "ttZ PDF", x, ttz_hist);
	RooRealVar ttz_norm("ttz_norm", "ttZ yield", h_bkg_group["ttZ"]->Integral(), 0.0, 10.0 * h_bkg_group["ttZ"]->Integral());
	RooExtendPdf ttz_ext("ttz_ext", "ttZ Extended", ttz_pdf, ttz_norm);

	// --- Update model ---
	RooAddPdf model_core("model_core", "Model", RooArgList(zz_ext, vv_ext, zh_ext, ttz_ext, other_ext));
	RooProdPdf model("model", "Model with constraints", RooArgSet(model_core, other_constraint));

	//Fit to data
	RooDataHist data_obs("data_obs", "Observed Data", x, Import(*h_bkg_group["data"]));
	model.fitTo(data_obs, Extended(true), PrintLevel(-1));

	// --- Plot ---
	RooPlot* frame = x.frame();
	model.plotOn(frame);
	model.plotOn(frame, Components("zz_ext"), LineColor(kRed));
	model.plotOn(frame, Components("vv_ext"), LineColor(kBlue));
	model.plotOn(frame, Components("zh_ext"), LineColor(kGreen+2));
	model.plotOn(frame, Components("ttz_ext"), LineColor(kOrange));
	model.plotOn(frame, Components("other_ext"), LineColor(kMagenta));
	frame->Draw();
	// --- Output scale factors ---
	double zz_sf = zz_norm.getVal() / h_bkg_group["ZZ"]->Integral();
	double vv_sf = vv_norm.getVal() / h_bkg_group["VV"]->Integral();
	double zh_sf = zh_norm.getVal() / h_bkg_group["other"]->Integral();
	double ttz_sf = ttz_norm.getVal() / h_bkg_group["ttZ"]->Integral();

	std::cout << "ZZ SF:  " << zz_sf  << " +- " << zz_norm.getError()/h_bkg_group["ZZ"]->Integral() << std::endl;
	std::cout << "VV SF:  " << vv_sf  << " +- " << vv_norm.getError()/h_bkg_group["VV"]->Integral() << std::endl;
	std::cout << "ZH SF:  " << zh_sf  << " +- " << zh_norm.getError()/h_bkg_group["other"]->Integral() << std::endl;
	std::cout << "ttZ SF: " << ttz_sf << " +- " << ttz_norm.getError()/h_bkg_group["ttZ"]->Integral() << std::endl;

}