// RooFit scale factor fitting code (modular, cleaner)
#include <RooDataHist.h>
#include <RooHistPdf.h>
#include <RooRealVar.h>
#include <RooExtendPdf.h>
#include <RooFormulaVar.h>
#include <RooGaussian.h>
#include <RooProdPdf.h>
#include <RooAddPdf.h>
#include <RooPlot.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1D.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace RooFit;

// Function to load histograms from file list
TH1D* loadHistogram(const std::vector<std::string>& files, const std::string& histname) {
    TH1D* h_total = nullptr;
    std::string input_dir = "hist_CR_ZZ/";
    for (const auto& file : files) {
        TFile* f = new TFile((input_dir + file).c_str(), "READ");
        if (!f || f->IsZombie()) continue;
        TH1D* h = (TH1D*)f->Get(histname.c_str());
        if (!h) continue;
        if (!h_total) h_total = (TH1D*)h->Clone();
        else h_total->Add(h);
    }
    return h_total;
}

RooExtendPdf* make_constrained_pdf(const std::string& name, TH1D* hist, RooRealVar& x, double rel_uncert, RooArgSet& constraints) {
    RooDataHist* dh = new RooDataHist((name + "_hist").c_str(), (name + " hist").c_str(), x, Import(*hist));
    RooHistPdf* pdf = new RooHistPdf((name + "_pdf").c_str(), (name + " PDF").c_str(), x, *dh);

    double nominal = hist->Integral();

    RooRealVar* nuis = new RooRealVar((name + "_nuis").c_str(), (name + " nuisance").c_str(), 0, -5, 5);
    RooGaussian* constraint = new RooGaussian((name + "_constraint").c_str(), "", *nuis, RooConst(0.), RooConst(1.));
    constraints.add(*constraint);

    RooFormulaVar* norm = new RooFormulaVar((name + "_norm_constr").c_str(), "@0*(1 + @1*@2)",
                                            RooArgList(RooConst(nominal), *nuis, RooConst(rel_uncert)));

    return new RooExtendPdf((name + "_ext").c_str(), (name + " Extended").c_str(), *pdf, *norm);
}


// Perform fit in a control region
void fit_scale_factor(std::map<std::string, std::vector<std::string>>& file_map,
                      const std::string& control_region_name,
                      const std::string& target,
                      const std::vector<std::string>& backgrounds,
                      const std::string& fit_variable = "0tau/h_ST") {

    RooRealVar x("x", "Discriminating Variable", 0, 1000);
    std::map<std::string, TH1D*> histograms;
    std::map<std::string, RooDataHist*> roo_dh;
    std::map<std::string, RooHistPdf*> roo_pdf;
    std::map<std::string, RooRealVar*> norms;
    std::map<std::string, RooExtendPdf*> pdf_ext;

    // Load and create PDFs
    for (const auto& bkg : backgrounds) {
        TH1D* h = loadHistogram(file_map[bkg], fit_variable);
        if (!h) continue;
        histograms[bkg] = h;
        roo_dh[bkg] = new RooDataHist((bkg + "_hist").c_str(), bkg.c_str(), x, Import(*h));
        roo_pdf[bkg] = new RooHistPdf((bkg + "_pdf").c_str(), bkg.c_str(), x, *roo_dh[bkg]);
        norms[bkg] = new RooRealVar((bkg + "_norm").c_str(), bkg.c_str(), h->Integral(), 0, 10*h->Integral());
        pdf_ext[bkg] = new RooExtendPdf((bkg + "_ext").c_str(), bkg.c_str(), *roo_pdf[bkg], *norms[bkg]);
    }

    // Build model
    RooArgList model_comps;
    for (const auto& bkg : backgrounds) {
        model_comps.add(*pdf_ext[bkg]);
    }
    RooAddPdf model_core("model_core", "Sum of components", model_comps);

    // Fit
    TH1D* h_data = loadHistogram(file_map["data"], fit_variable);
    RooDataHist data_obs("data_obs", "Observed", x, Import(*h_data));
    model_core.fitTo(data_obs, Extended(true), PrintLevel(-1));

    // Plot
    RooPlot* frame = x.frame();
    data_obs.plotOn(frame);
    model_core.plotOn(frame);
    for (const auto& bkg : backgrounds) {
        model_core.plotOn(frame, Components((bkg + "_ext").c_str()), LineStyle(kDashed));
    }
    frame->Draw();

    // Print scale factor
    double fitted = norms[target]->getVal();
    double nominal = histograms[target]->Integral();
    double err = norms[target]->getError();
    std::cout << control_region_name << " SF for " << target << " = " << fitted / nominal
              << " +- " << err / nominal << std::endl;
}

// Example usage
void roofit_test_new() {
    std::map<std::string, std::vector<std::string>> file_map = {
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

    fit_scale_factor(file_map, "ZZ_CR", "ZZ", {"ZZ", "DY", "ST", "TTbar","VV","VVV","ttW","ttZ","WJ","ZH","other"});
    //fit_scale_factor(file_map, "VV_CR", "VV", {"VV","ZZ", "DY", "ST", "TTbar","VVV","ttW","ttZ","WJ","ZH","other"});
    //fit_scale_factor(file_map, "ttZ_CR", "ttZ", {"ttZ", "ZH","ZZ", "DY", "ST", "TTbar","VV","VVV","ttW","WJ","other"});
    //fit_scale_factor(file_map, "ZH_CR", "ZH", {"ZH","ZZ", "DY", "ST", "TTbar","VV","VVV","ttW","ttZ","WJ","other"});
}
