#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include "TSystemDirectory.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TRandom3.h"
#include "Compression.h"
TRandom3 randCF(12345);


#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "include/MyBranch_FR_new.C"
#include "include/Kinematics.C"
//#include "include/MET_split.C"
#include "include/Xsections.C"

using std::string;
using std::vector;
using std::unordered_map;
using FRMap = std::unordered_map<std::string, std::vector<TH1D*>>;
using FRMap2D = std::unordered_map<std::string, TH2D*>;

const vector<string> channels = {
    "ee","em","et","mm","mt","tt",
    "eee","eem","eet","eme","emm","emt","ete","etm","ett",
    "mme","mmm","mmt","mte","mtm","mtt","tte","ttm","ttt",
    "eeee","eeem","eeet","eemm","eemt","eett",
    "emem","emet","emmm","emmt","emtt",
    "etet","etmm","etmt","ettt",
    "mmmm","mmmt","mmtt","mtmt","mttt","tttt"
};

// Histogram creation utility to avoid code duplication
void createHistograms(std::map<std::string, TH1D*>& histograms,
                      const std::string& prefix,
                      const std::string& label,
                      int bins, double low, double high) {
    for (const std::string& channel : {"VR_0tau","VR_1tau","VR_2tau","VR_3tau","VR_3lep0tau","VR_3lep1tau","VR_3lep2tau",
 "CR_0tau","CR_1tau","CR_2tau","CR_3tau","CR_3lep0tau","CR_3lep1tau","CR_3lep2tau",
 "SR_0tau","SR_1tau","SR_2tau","SR_3tau","SR_3lep0tau","SR_3lep1tau","SR_3lep2tau",
 "DYCR_0tau","DYCR_1tau","DYveto_0tau","DYveto_1tau",
 "ee", "em", "mm", "eee", "eem", "eet", "emt", "mme", "mmm", "mmt",
	 "ett", "mtt", "eeee", "eeem", "eemm", "mmem", "mmmm", "eeet", "eemt",
	 "eett", "mmet", "ttem", "ttet", "mmmt", "mmtt", "ttmt", "v_ee", "v_em", "v_mm", "v_eee", "v_eem", "v_eet", "v_emt", "v_mme", "v_mmm", "v_mmt",
	 "v_tte", "v_mtt", "v_eeee", "v_eeem", "v_eemm", "v_mmem", "v_mmmm", "v_eeet", "v_eemt",
	 "v_eett", "v_mmet", "v_ettm", "v_ettt", "v_mmmt", "v_mmtt", "v_ttmt"}) {
        std::string hist_name = prefix + "_" + channel;
        std::string hist_label = label + " " + channel;
        
        histograms[channel] = new TH1D(hist_name.c_str(), hist_label.c_str(), bins, low, high);
        histograms[channel]->Sumw2(); // for proper error propagation
    }
}

void fillHistograms(const std::string& channel,
					std::map<std::string, TH1D*>& h_mZ1, 
					std::map<std::string, TH1D*>& h_mZ2,
					std::map<std::string, TH1D*>& h_mH1, 
					std::map<std::string, TH1D*>& h_mH2,
					std::map<std::string, TH1D*>& h_met,
					std::map<std::string, TH1D*>& h_LT, 
					std::map<std::string, TH1D*>& h_pt1, 
					std::map<std::string, TH1D*>& h_pt2,
					std::map<std::string, TH1D*>& h_pt3,
					std::map<std::string, TH1D*>& h_pt4,
					std::map<std::string, TH1D*>& h_eta1,
					std::map<std::string, TH1D*>& h_eta2,
					std::map<std::string, TH1D*>& h_eta3,
					std::map<std::string, TH1D*>& h_eta4,
					std::map<std::string, TH1D*>& h_phi1,
					std::map<std::string, TH1D*>& h_phi2,
					std::map<std::string, TH1D*>& h_phi3,
					std::map<std::string, TH1D*>& h_phi4,
					double met,
					vector<pair<int, int>> OSSF_pair,
					vector<pair<int, int>> SS_pair,
                    double evtwt_nom) {
    h_met[channel]->Fill(met, evtwt_nom);
    h_LT[channel]->Fill(LepV(1).Pt()+LepV(2).Pt()+LepV(3).Pt()+LepV(4).Pt(), evtwt_nom);
	if (OSSF_pair.size()>0) {
		h_mZ1[channel]->Fill((LepV(OSSF_pair[0].first)+LepV(OSSF_pair[0].second)).M(), evtwt_nom);
		h_pt1[channel]->Fill(LepV(OSSF_pair[0].first).Pt(), evtwt_nom);
		h_pt2[channel]->Fill(LepV(OSSF_pair[0].second).Pt(), evtwt_nom);
		h_eta1[channel]->Fill(LepV(OSSF_pair[0].first).Eta(), evtwt_nom);
		h_eta2[channel]->Fill(LepV(OSSF_pair[0].second).Eta(), evtwt_nom);
		h_phi1[channel]->Fill(LepV(OSSF_pair[0].first).Phi(), evtwt_nom);
		h_phi2[channel]->Fill(LepV(OSSF_pair[0].second).Phi(), evtwt_nom);
    }
    if (OSSF_pair.size()>1) {
    	h_mZ2[channel]->Fill((LepV(OSSF_pair[1].first)+LepV(OSSF_pair[1].second)).M(), evtwt_nom);
    	h_pt3[channel]->Fill(LepV(OSSF_pair[1].first).Pt(), evtwt_nom);
    	h_pt4[channel]->Fill(LepV(OSSF_pair[1].second).Pt(), evtwt_nom);
    	h_eta3[channel]->Fill(LepV(OSSF_pair[1].first).Eta(), evtwt_nom);
		h_eta4[channel]->Fill(LepV(OSSF_pair[1].second).Eta(), evtwt_nom);
		h_phi3[channel]->Fill(LepV(OSSF_pair[1].first).Phi(), evtwt_nom);
		h_phi4[channel]->Fill(LepV(OSSF_pair[1].second).Phi(), evtwt_nom);
   	}
    if (SS_pair.size()>0) h_mH1[channel]->Fill((LepV(SS_pair[0].first)+LepV(SS_pair[0].second)).M(), evtwt_nom);
	if (SS_pair.size()>1) h_mH2[channel]->Fill((LepV(SS_pair[1].first)+LepV(SS_pair[1].second)).M(), evtwt_nom); 
    
}


void scaleAndWriteHistograms(std::map<std::string, TH1D*>& histograms, double xs_weight) {
    for (const std::string& channel : {"VR_0tau","VR_1tau","VR_2tau","VR_3tau","VR_3lep0tau","VR_3lep1tau","VR_3lep2tau",
 "CR_0tau","CR_1tau","CR_2tau","CR_3tau","CR_3lep0tau","CR_3lep1tau","CR_3lep2tau",
 "SR_0tau","SR_1tau","SR_2tau","SR_3tau","SR_3lep0tau","SR_3lep1tau","SR_3lep2tau",
 "DYCR_0tau","DYCR_1tau","DYveto_0tau","DYveto_1tau",
 "ee", "em", "mm", "eee", "eem", "eet", "emt", "mme", "mmm", "mmt",
	 "ett", "mtt", "eeee", "eeem", "eemm", "mmem", "mmmm", "eeet", "eemt",
	 "eett", "mmet", "ttem", "ttet", "mmmt", "mmtt", "ttmt", "v_ee", "v_em", "v_mm", "v_eee", "v_eem", "v_eet", "v_emt", "v_mme", "v_mmm", "v_mmt",
	 "v_tte", "v_mtt", "v_eeee", "v_eeem", "v_eemm", "v_mmem", "v_mmmm", "v_eeet", "v_eemt",
	 "v_eett", "v_mmet", "v_ettm", "v_ettt", "v_mmmt", "v_mmtt", "v_ttmt"}) {
        histograms[channel]->Scale(xs_weight);
        histograms[channel]->Write();
    }
}


double clampPt(double pt) {
    if (pt < 20) return 20.01;
    if (pt > 200) return 199.9;
    return pt;
}


double getTauFakeRate2D(double pt,//reads the value
                        double eta,
                        const std::string& year,
                        FRMap2D& FR_Data2D)
{
    auto it = FR_Data2D.find(year);

    if (it == FR_Data2D.end()) {
        std::cerr << "ERROR: DATA 2D tau fake rate not found for year "
                  << year << std::endl;
        return 0.0;
    }

    TH2D* h = it->second;
    if (!h) return 0.0;

    double ptc  = clampPt(pt);
    double aeta = std::fabs(eta);

    int xbin = std::clamp(h->GetXaxis()->FindBin(ptc),  1, h->GetNbinsX());
    int ybin = std::clamp(h->GetYaxis()->FindBin(aeta), 1, h->GetNbinsY());

    return std::clamp(h->GetBinContent(xbin, ybin), 0.0, 0.99);
}

void loadTauFR_Data2D(FRMap2D& FR_Data2D,//loads the FR from histo
                      const std::string& year)
{
    TString fileName =
        "Data_tau_fake_rates.root";

    TFile* f = TFile::Open(fileName);
    if (!f || f->IsZombie()) {
        std::cerr << "ERROR: cannot open DATA 2D FR file "
                  << fileName << std::endl;
        exit(1);
    }

    TString hName = Form("Data_%s_tau_fake_rate", year.c_str());

    TH2D* h = (TH2D*)f->Get(hName);
    if (!h) {
        std::cerr << "ERROR: missing DATA 2D FR histogram:\n"
                  << "  " << hName << std::endl;
        exit(1);
    }

    FR_Data2D[year] = (TH2D*)h->Clone(Form("%s_clone", hName.Data()));
    FR_Data2D[year]->SetDirectory(0);

    f->Close();

    std::cout << "[FR][DATA 2D] loaded " << hName << std::endl;
}

void DCH_run2_tauFR_new(string inYear="2016preVFP", string inCuts="tight", const char* ext="root") {
    (void)ext;
    
    year = inYear;
    cuts = inCuts;

    bool USEFR = true; // If we want to use FR weighting, else false
    std::string frMode = "Data"; // MC or Data, which fake rates to use on MC
    std::string sidebandMode = "L"; // Cuts used for Fake Rate "LNT or L"

    auto passFakeSelection = [&](int idx) {
        if (sidebandMode == "LNT") return passLooseNotTightTau(idx);
        else return passLooseTau(idx);
    };

    auto getEpsilon = [&](double f) {//it just chooses the type of FR application
        return (sidebandMode == "LNT") ? (f / (1.0 - f)) : f;
    };

    FRMap FR_Data; 
    FRMap2D FR_Data2D; 

    if (frMode == "MC") {
        std::cout << ">>> [TOGGLE] Mode: MC. Loading DY-based 1D Fake Rates..." << std::endl;
        loadTauFR_MC(FR_Data, year, "eet"); 
        loadTauFR_MC(FR_Data, year, "mmt");
    }
    else {
        std::cout << ">>> [TOGGLE] Mode: Data. Loading averaged DATA 2D Fake Rate..." << std::endl;
        loadTauFR_Data2D(FR_Data2D, year);
    }

    const char* inDir = ".";
    TString outDirBase = "FR_test";
    TString outDir = Form("%s/%s/%s", outDirBase.Data(), year.c_str(), cuts.c_str());
    gSystem->mkdir(outDir, kTRUE);

    // TSystemDirectory dir("indir", inDir);
    // TList* fileList = dir.GetListOfFiles();
    // vector<string> files;
    // if (fileList) {
    //     TIter next(fileList);
    //     TObject* obj;
    //     while ((obj = next())) {
    //         string fname = obj->GetName();
    //         if (fname.rfind(".root") == string::npos) continue;
    //         if (fname.rfind("._", 0) == 0) continue; 
    //         if (year != "run2" && fname.find(year) == string::npos) continue;
    //         files.emplace_back(Form("%s/%s", inDir, fname.c_str()));
    //     }
    // }

    // New logic using to read the file name from Filemap.h
    std::map<std::string, std::vector<std::string>> fileMap ;
    if (year == "2016preVFP") {
        fileMap = {{"DY",      {"DYJetsToLLM50_2016preVFP.root"}}};
           /* {"DY10_50", {"DYJetsToLLM10to50_2016preVFP.root"}},
            {"DY",      {"DYJetsToLLM50_2016preVFP.root"}},
            {"VV",      {"WW_2016preVFP.root", "WWTo2L2Nu_2016preVFP.root", "WZTo2Q2L_2016preVFP.root", "WZTo3LNu_2016preVFP.root"}},
            {"VVV",     {"WWW_2016preVFP.root", "WZZ_2016preVFP.root", "ZZZ_2016preVFP.root"}},
            {"ttV",     {"ttWJets_2016preVFP.root", "ttZJets_2016preVFP.root"}},
            {"WJ",      {"WJetsToLNu_NLO_part2_2016preVFP.root"}},
            {"ZZ",      {"ZZTo2L2Nu_2016preVFP.root", "ZZTo2Q2L_2016preVFP.root", "ZZTo4L_2016preVFP.root"}},
            {"ST",      {"ST_s-channel_2016preVFP.root", "ST_t-channel_antitop_2016preVFP.root", "ST_t-channel_top_2016preVFP.root", "ST_tW_antitop_2016preVFP.root", "ST_tW_top_2016preVFP.root"}},
            {"TTbar",   {"TTTo2L2Nu_2016preVFP.root", "TTToSemiLeptonic_2016preVFP.root", "TTToHadronic_2016preVFP.root"}},
            {"QCD",     {"QCD_HT50to100_2016preVFP.root", "QCD_HT100to200_2016preVFP.root", "QCD_HT200to300_2016preVFP.root", "QCD_HT300to500_2016preVFP.root", "QCD_HT500to700_2016preVFP.root", "QCD_HT700to1000_2016preVFP.root", "QCD_HT1000to1500_2016preVFP.root", "QCD_HT1500to2000_2016preVFP.root", "QCD_HT2000toInf_2016preVFP.root"}},
            {"other",   {"ttHToTauTau_2016preVFP.root", "ZHToMuMu_2016preVFP.root", "ZHToTauTau_2016preVFP.root", "GluGluZH_2016preVFP.root", "ttHToEE_2016preVFP.root", "ttHTo2L2Nu_2016preVFP.root", "ttHJetToNonbb_2016preVFP.root", "TWZToLL_2016preVFP.root", "HZJ_HToWWTo2L2Nu_ZTo2L_2016preVFP.root"}},
            {"data",    {"SingleElectronB_2016preVFP.root", "SingleElectronC_2016preVFP.root", "SingleElectronD_2016preVFP.root", "SingleElectronE_2016preVFP.root", "SingleElectronF_2016preVFP.root", "SingleMuonB_2016preVFP.root", "SingleMuonC_2016preVFP.root", "SingleMuonD_2016preVFP.root", "SingleMuonE_2016preVFP.root", "SingleMuonF_2016preVFP.root"}}
        };*/
    }
    else if (year == "2016postVFP") {
        fileMap = {
            {"DY10_50", {"DYJetsToLLM10to50_2016postVFP.root"}},
            {"DY",      {"DYJetsToLLM50_2016postVFP.root"}},
            {"VV",      {"WW_2016postVFP.root", "WWTo2L2Nu_2016postVFP.root", "WZTo2Q2L_2016postVFP.root", "WZTo3LNu_2016postVFP.root"}},
            {"VVV",     {"WWW_2016postVFP.root", "WZZ_2016postVFP.root", "ZZZ_2016postVFP.root"}},
            {"ttV",     {"ttWJets_2016postVFP.root", "ttZJets_2016postVFP.root"}},
            {"WJ",      {"WJetsToLNu_NLO_2016postVFP.root"}},
            {"ZZ",      {"ZZTo2L2Nu_2016postVFP.root", "ZZTo2Q2L_2016postVFP.root", "ZZTo4L_2016postVFP.root"}},
            {"ST",      {"ST_s-channel_2016postVFP.root", "ST_t-channel_antitop_2016postVFP.root", "ST_t-channel_top_2016postVFP.root", "ST_tW_antitop_2016postVFP.root", "ST_tW_top_2016postVFP.root"}},
            {"TTbar",   {"TTTo2L2Nu_2016postVFP.root", "TTToSemiLeptonic_2016postVFP.root", "TTToHadronic_2016postVFP.root"}},
            {"QCD",     {"QCD_HT50to100_2016postVFP.root", "QCD_HT100to200_2016postVFP.root", "QCD_HT200to300_2016postVFP.root", "QCD_HT300to500_2016postVFP.root", "QCD_HT500to700_2016postVFP.root", "QCD_HT700to1000_2016postVFP.root", "QCD_HT1000to1500_2016postVFP.root", "QCD_HT1500to2000_2016postVFP.root", "QCD_HT2000toInf_2016postVFP.root"}},
            {"other",   {"ttHToTauTau_2016postVFP.root", "ZHToMuMu_2016postVFP.root", "ZHToTauTau_2016postVFP.root", "GluGluZH_2016postVFP.root", "ttHToEE_2016postVFP.root", "ttHTo2L2Nu_2016postVFP.root"}},
            {"data",    {"SingleElectronF_2016postVFP.root", "SingleElectronG_2016postVFP.root", "SingleElectronH_2016postVFP.root", "SingleMuonF_2016postVFP.root", "SingleMuonG_2016postVFP.root", "SingleMuonH_2016postVFP.root"}}
        };
    }
    else if (year == "2017") {
        fileMap = {
            {"DY10_50", {"DYJetsToLLM10to50_2017.root"}},
            {"DY",      {"DYJetsToLLM50_2017.root"}},
            {"VV",      {"WW_2017.root", "WWTo2L2Nu_2017.root", "WZTo2Q2L_2017.root", "WZTo3LNu_2017.root"}},
            {"VVV",     {"WWW_2017.root", "WZZ_2017.root", "ZZZ_2017.root"}},
            {"ttV",     {"ttWJets_2017.root", "ttZJets_2017.root"}},
            {"WJ",      {"WJetsToLNu_NLO_2017.root"}},
            {"ZZ",      {"ZZTo2L2Nu_2017.root", "ZZTo2Q2L_2017.root", "ZZTo4L_2017.root"}},
            {"ST",      {"ST_s-channel_2017.root", "ST_t-channel_antitop_2017.root", "ST_t-channel_top_2017.root", "ST_tW_antitop_2017.root", "ST_tW_top_2017.root"}},
            {"TTbar",   {"TTTo2L2Nu_2017.root", "TTToSemiLeptonic_2017.root", "TTToHadronic_2017.root"}},
            {"QCD",     {"QCD_HT50to100_2017.root", "QCD_HT100to200_2017.root", "QCD_HT200to300_2017.root", "QCD_HT300to500_2017.root", "QCD_HT500to700_2017.root", "QCD_HT700to1000_2017.root", "QCD_HT1000to1500_2017.root", "QCD_HT1500to2000_2017.root", "QCD_HT2000toInf_2017.root"}},
            {"other",   {"ttHToTauTau_2017.root", "ZHToMuMu_2017.root", "ZHToTauTau_2017.root", "GluGluZH_2017.root", "ttHToEE_2017.root", "ttHTo2L2Nu_2017.root"}},
            {"data",    {"SingleElectronB_2017.root", "SingleElectronC_2017.root", "SingleElectronD_2017.root", "SingleElectronE_2017.root", "SingleElectronF_2017.root", "SingleMuonB_2017.root", "SingleMuonC_2017.root", "SingleMuonD_2017.root", "SingleMuonE_2017.root", "SingleMuonF_2017.root"}}
        };
    }
    else if (year == "2018") {
        fileMap = {
            {"DY10_50", {"DYJetsToLLM10to50_2018.root"}},
            {"DY",      {"DYJetsToLLM50_2018.root"}},
            {"VV",      {"WW_2018.root", "WWTo2L2Nu_2018.root", "WZTo2Q2L_2018.root", "WZTo3LNu_2018.root"}},
            {"VVV",     {"WWW_2018.root", "WZZ_2018.root", "ZZZ_2018.root"}},
            {"ttV",     {"ttWJets_2018.root", "ttZJets_2018.root"}},
            {"WJ",      {"WJetsToLNu_NLO_2018.root"}},
            {"ZZ",      {"ZZTo2L2Nu_2018.root", "ZZTo2Q2L_2018.root", "ZZTo4L_2018.root"}},
            {"ST",      {"ST_s-channel_2018.root", "ST_t-channel_antitop_2018.root", "ST_t-channel_top_2018.root", "ST_tW_antitop_2018.root", "ST_tW_top_2018.root"}},
            {"TTbar",   {"TTTo2L2Nu_2018.root", "TTToSemiLeptonic_2018.root", "TTToHadronic_2018.root"}},
            {"QCD",     {"QCD_HT50to100_2018.root", "QCD_HT100to200_2018.root", "QCD_HT200to300_2018.root", "QCD_HT300to500_2018.root", "QCD_HT500to700_2018.root", "QCD_HT700to1000_2018.root", "QCD_HT1000to1500_2018.root", "QCD_HT1500to2000_2018.root", "QCD_HT2000toInf_2018.root"}},
            {"other",   {"ttHToTauTau_2018.root", "ZHToMuMu_2018.root", "ZHToTauTau_2018.root", "GluGluZH_2018.root", "ttHToEE_2018.root", "ttHTo2L2Nu_2018.root"}},
            {"data",    {"EGammaA_2018.root", "EGammaB_2018.root", "EGammaC_2018.root", "EGammaD_2018.root", "SingleMuonA_2018.root", "SingleMuonB_2018.root", "SingleMuonC_2018.root", "SingleMuonD_2018.root"}}
        };
    }
    else if (year == "Run2") {
        fileMap = {
            {"DY10_50", {"DYJetsToLLM10to50_2016postVFP.root", "DYJetsToLLM10to50_2016preVFP.root", "DYJetsToLLM10to50_2017.root", "DYJetsToLLM10to50_2018.root"}},
            {"DY",      {"DYJetsToLLM50_2016postVFP.root", "DYJetsToLLM50_2016preVFP.root", "DYJetsToLLM50_2017.root", "DYJetsToLLM50_2018.root"}},
            {"VV",      {"WW_2016postVFP.root", "WWTo2L2Nu_2016postVFP.root", "WZTo2Q2L_2016postVFP.root", "WZTo3LNu_2016postVFP.root", "WW_2016preVFP.root", "WWTo2L2Nu_2016preVFP.root", "WZTo2Q2L_2016preVFP.root", "WZTo3LNu_2016preVFP.root", "WW_2017.root", "WWTo2L2Nu_2017.root", "WZTo2Q2L_2017.root", "WZTo3LNu_2017.root", "WW_2018.root", "WWTo2L2Nu_2018.root", "WZTo2Q2L_2018.root", "WZTo3LNu_2018.root"}},
            {"VVV",     {"WWW_2016postVFP.root", "WZZ_2016postVFP.root", "ZZZ_2016postVFP.root", "WWW_2016preVFP.root", "WZZ_2016preVFP.root", "ZZZ_2016preVFP.root", "WWW_2017.root", "WZZ_2017.root", "ZZZ_2017.root", "WWW_2018.root", "WZZ_2018.root", "ZZZ_2018.root"}},
            {"ttV",     {"ttWJets_2016postVFP.root", "ttZJets_2016postVFP.root", "ttWJets_2016preVFP.root", "ttZJets_2016preVFP.root", "ttWJets_2017.root", "ttZJets_2017.root", "ttWJets_2018.root", "ttZJets_2018.root"}},
            {"WJ",      {"WJetsToLNu_NLO_2016postVFP.root", "WJetsToLNu_NLO_part2_2016preVFP.root", "WJetsToLNu_NLO_2017.root", "WJetsToLNu_NLO_2018.root"}},
            {"ZZ",      {"ZZTo2L2Nu_2016postVFP.root", "ZZTo2Q2L_2016postVFP.root", "ZZTo4L_2016postVFP.root", "ZZTo2L2Nu_2016preVFP.root", "ZZTo2Q2L_2016preVFP.root", "ZZTo4L_2016preVFP.root", "ZZTo2L2Nu_2017.root", "ZZTo2Q2L_2017.root", "ZZTo4L_2017.root", "ZZTo2L2Nu_2018.root", "ZZTo2Q2L_2018.root", "ZZTo4L_2018.root"}},
            {"ST",      {"ST_s-channel_2016postVFP.root", "ST_t-channel_antitop_2016postVFP.root", "ST_t-channel_top_2016postVFP.root", "ST_tW_antitop_2016postVFP.root", "ST_tW_top_2016postVFP.root", "ST_s-channel_2016preVFP.root", "ST_t-channel_antitop_2016preVFP.root", "ST_t-channel_top_2016preVFP.root", "ST_tW_antitop_2016preVFP.root", "ST_tW_top_2016preVFP.root", "ST_s-channel_2017.root", "ST_t-channel_antitop_2017.root", "ST_t-channel_top_2017.root", "ST_tW_antitop_2017.root", "ST_tW_top_2017.root", "ST_s-channel_2018.root", "ST_t-channel_antitop_2018.root", "ST_t-channel_top_2018.root", "ST_tW_antitop_2018.root", "ST_tW_top_2018.root"}},
            {"TTbar",   {"TTTo2L2Nu_2016postVFP.root", "TTToSemiLeptonic_2016postVFP.root", "TTToHadronic_2016postVFP.root", "TTTo2L2Nu_2016preVFP.root", "TTToSemiLeptonic_2016preVFP.root", "TTToHadronic_2016preVFP.root", "TTTo2L2Nu_2017.root", "TTToSemiLeptonic_2017.root", "TTToHadronic_2017.root", "TTTo2L2Nu_2018.root", "TTToSemiLeptonic_2018.root", "TTToHadronic_2018.root"}},
            {"QCD",     {"QCD_HT50to100_2016postVFP.root", "QCD_HT100to200_2016postVFP.root", "QCD_HT200to300_2016postVFP.root", "QCD_HT300to500_2016postVFP.root", "QCD_HT500to700_2016postVFP.root", "QCD_HT700to1000_2016postVFP.root", "QCD_HT1000to1500_2016postVFP.root", "QCD_HT1500to2000_2016postVFP.root", "QCD_HT2000toInf_2016postVFP.root", "QCD_HT50to100_2016preVFP.root", "QCD_HT100to200_2016preVFP.root", "QCD_HT200to300_2016preVFP.root", "QCD_HT300to500_2016preVFP.root", "QCD_HT500to700_2016preVFP.root", "QCD_HT700to1000_2016preVFP.root", "QCD_HT1000to1500_2016preVFP.root", "QCD_HT1500to2000_2016preVFP.root", "QCD_HT2000toInf_2016preVFP.root", "QCD_HT50to100_2017.root", "QCD_HT100to200_2017.root", "QCD_HT200to300_2017.root", "QCD_HT300to500_2017.root", "QCD_HT500to700_2017.root", "QCD_HT700to1000_2017.root", "QCD_HT1000to1500_2017.root", "QCD_HT1500to2000_2017.root", "QCD_HT2000toInf_2017.root", "QCD_HT50to100_2018.root", "QCD_HT100to200_2018.root", "QCD_HT200to300_2018.root", "QCD_HT300to500_2018.root", "QCD_HT500to700_2018.root", "QCD_HT700to1000_2018.root", "QCD_HT1000to1500_2018.root", "QCD_HT1500to2000_2018.root", "QCD_HT2000toInf_2018.root"}},
            {"other",   {"ttHToTauTau_2016postVFP.root", "ZHToMuMu_2016postVFP.root", "ZHToTauTau_2016postVFP.root", "GluGluZH_2016postVFP.root", "ttHToEE_2016postVFP.root", "ttHTo2L2Nu_2016postVFP.root", "ttHToTauTau_2016preVFP.root", "ZHToMuMu_2016preVFP.root", "ZHToTauTau_2016preVFP.root", "GluGluZH_2016preVFP.root", "ttHToEE_2016preVFP.root", "ttHTo2L2Nu_2016preVFP.root", "ttHJetToNonbb_2016preVFP.root", "TWZToLL_2016preVFP.root", "HZJ_HToWWTo2L2Nu_ZTo2L_2016preVFP.root", "ttHToTauTau_2017.root", "ZHToMuMu_2017.root", "ZHToTauTau_2017.root", "GluGluZH_2017.root", "ttHToTauTau_2018.root", "ZHToMuMu_2018.root", "ZHToTauTau_2018.root", "GluGluZH_2018.root", "ttHToEE_2017.root", "ttHToEE_2018.root", "ttHTo2L2Nu_2017.root", "ttHTo2L2Nu_2018.root", "ttHJetToNonbb_2016postVFP.root", "ttHJetToNonbb_2017.root", "ttHJetToNonbb_2018.root", "TWZToLL_2016postVFP.root", "TWZToLL_2017.root", "TWZToLL_2018.root", "HZJ_HToWWTo2L2Nu_ZTo2L_2016postVFP.root", "HZJ_HToWWTo2L2Nu_ZTo2L_2017.root", "HZJ_HToWWTo2L2Nu_ZTo2L_2018.root"}},
            {"data",    {"SingleElectronB_2016preVFP.root", "SingleElectronC_2016preVFP.root", "SingleElectronD_2016preVFP.root", "SingleElectronE_2016preVFP.root", "SingleElectronF_2016preVFP.root", "SingleElectronF_2016postVFP.root", "SingleElectronG_2016postVFP.root", "SingleElectronH_2016postVFP.root", "SingleMuonB_2016preVFP.root", "SingleMuonC_2016preVFP.root", "SingleMuonD_2016preVFP.root", "SingleMuonE_2016preVFP.root", "SingleMuonF_2016preVFP.root", "SingleMuonF_2016postVFP.root", "SingleMuonG_2016postVFP.root", "SingleMuonH_2016postVFP.root", "SingleElectronB_2017.root", "SingleElectronC_2017.root", "SingleElectronD_2017.root", "SingleElectronE_2017.root", "SingleElectronF_2017.root", "SingleMuonB_2017.root", "SingleMuonC_2017.root", "SingleMuonD_2017.root", "SingleMuonE_2017.root", "SingleMuonF_2017.root", "EGammaA_2018.root", "EGammaB_2018.root", "EGammaC_2018.root", "EGammaD_2018.root", "SingleMuonA_2018.root", "SingleMuonB_2018.root", "SingleMuonC_2018.root", "SingleMuonD_2018.root"}}
        };
    }
    vector<string> files;

    if (fileMap.empty()) {
        std::cerr << "ERROR: No files found in Filemap for year: " << year << std::endl;
        return;
    }

    for (auto const& entry : fileMap) {
        for (const std::string& fName : entry.second) {
            files.emplace_back(std::string(inDir) + "/" + fName);
        }
    }
    // 
    
    double Lumi = (year=="2016preVFP")?19500:(year=="2016postVFP")?16400:(year=="2017")?41500:(year=="2018")?58900:(19500+16400+41500+58900);

    for (size_t j=0; j<files.size(); ++j) {
        std::cout << "\n[file " << j+1 << "/" << files.size() << "] " << files[j] << std::endl;

        TFile* f = TFile::Open(files[j].c_str());
        if (!f || f->IsZombie()) { 
            std::cout << "  [skip] cannot open\n"; 
            if (f) f->Close();
            continue; 
        }

        TTree* t = (TTree*)f->Get("Events");
        if (!t) { 
            std::cout << "  [skip] no Events tree\n"; 
            f->Close(); 
            continue; 
        }

        t->SetBranchStatus("*", 0);

        /*const char* brs[] = {
            "pt_1","pt_2","pt_3","pt_4",
            "eta_1","eta_2","eta_3","eta_4",
            "phi_1","phi_2","phi_3","phi_4",
            "m_1","m_2","m_3","m_4",
            "q_1","q_2","q_3","q_4",
            "d0_1","d0_2","d0_3","d0_4",
            "dZ_1","dZ_2","dZ_3","dZ_4",
            "iso_1","iso_2","iso_3","iso_4",
            "gen_match_1","gen_match_2","gen_match_3","gen_match_4",
            "EleID_WP90_1","EleID_WP90_2","EleID_WP90_3","EleID_WP90_4",
            "MuID_1","MuID_2","MuID_3","MuID_4",
            "TauIDe_1","TauIDe_2","TauIDe_3","TauIDe_4",
            "TauIDm_1","TauIDm_2","TauIDm_3","TauIDm_4",
            "TauIDj_1","TauIDj_2","TauIDj_3","TauIDj_4",
            "IDSF_1","IDSF_2","IDSF_3","IDSF_4",
            "ISOSF_1","ISOSF_2","ISOSF_3","ISOSF_4",
            "TrigSF_1","TrigSF_2","TrigSF_3","TrigSF_4",
            "isTrig_1","isTrig_2",
            "TauVsEleIDSF_1","TauVsEleIDSF_2","TauVsEleIDSF_3","TauVsEleIDSF_4",
            "TauVsMuIDSF_1","TauVsMuIDSF_2","TauVsMuIDSF_3","TauVsMuIDSF_4",
            "TauVsJetIDSF_1","TauVsJetIDSF_2","TauVsJetIDSF_3","TauVsJetIDSF_4",
            "cat","met","run",
            "Generator_weight","brWeight","L1PreFiringWeight_Nom","weightPUtruejson"
        };

        for (auto br : brs) t->SetBranchStatus(br, 1);*/

        MyBranch(t);  

        std::string filename = gSystem->BaseName(files[j].c_str());

        //double denom = hnevts ? hnevts->Integral() : 0;
        // bool isData = (XSec(files[j].c_str()) == 1);
        bool isData = (XSec(filename) == 1);
	if (isData) {f->Close(); continue;}
        bool isDY = (filename.find("DYJets") != std::string::npos);
        bool isWJ = (filename.find("WJets") != std::string::npos);
        bool isTT = (filename.find("TTTo") != std::string::npos);
        bool isQCD = (filename.find("QCD") != std::string::npos);
        bool isDY50 = (filename.find("DYJetsToLLM50") != std::string::npos);
        // double xsw = (XSec(files[j].c_str())!=1 && denom>0)? Lumi*XSec(files[j].c_str())/denom : 1.0;
        //double xsw = (XSec(filename) != 1 && denom > 0) ? Lumi * XSec(filename) / denom : 1.0;
        double xsw =1;
	TH1D* hNWEvts;
	if(XSec(filename)!=1) hNWEvts = (TH1D*)f->Get("hNWEvts")->Clone("hNWEvts");	
	if (!hNWEvts) hNWEvts = (TH1D*)f->Get("hNEvts")->Clone("hNWEvts");
	hNWEvts->Write();

	double xs_weight = 1.0;
        TString outName = Form("%s/hist_%s", outDir.Data(), gSystem->BaseName(files[j].c_str()));
        TFile* fout = new TFile(outName, "RECREATE");
        // fout->SetCompressionLevel(0);
        fout->SetCompressionSettings(409);

        unordered_map<string,TH1D*> h_mZ,h_mH;
        unordered_map<string,TH1D*> h_ST;
        unordered_map<string,TH1D*> h_pt[NlepMax],h_eta[NlepMax],h_phi[NlepMax],h_d0[NlepMax],h_dZ[NlepMax],h_iso[NlepMax];
        unordered_map<string,TH2D*> h_ST_mZ;
        unordered_map<string,TH2D*> h_pt_eta[NlepMax];
        unordered_map<string,TH1D*> h_genmatch[NlepMax];
        unordered_map<string,TH2D*> h_pt_phi[NlepMax];
        unordered_map<string,TH1D*> h_pt_etaBin1[NlepMax];  // |eta| < 0.5
        unordered_map<string,TH1D*> h_pt_etaBin2[NlepMax];  // 0.5–1.5
        unordered_map<string,TH1D*> h_pt_etaBin3[NlepMax];  // 1.5–2.5

				// Compact histogram creation
       std::map<std::string, TH1D*> h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4 ;
        
        createHistograms(h_mZ1, "h_mZ1", "mZ1", 5000,0,500);
        createHistograms(h_mZ2, "h_mZ2", "mZ2", 5000,0,500);
        createHistograms(h_mH1, "h_mH1", "mll1", 1000,0,1000);
        createHistograms(h_mH2, "h_mH2", "mll2", 1000,0,1000);
        createHistograms(h_met, "h_met", "MET", 100,0,500);
        createHistograms(h_LT, "h_LT", "LT", 1000,0,1000);
        createHistograms(h_pt1, "h_pt1", "pT1", 1000,0,500);
        createHistograms(h_eta1, "h_eta1", "Eta1", 1000, -3, 3);
        createHistograms(h_phi1, "h_phi1", "Phi1", 1000, -4, 4);
        createHistograms(h_pt2, "h_pt2", "pT2", 1000,0,250);
        createHistograms(h_eta2, "h_eta2", "Eta2", 1000, -3, 3);
        createHistograms(h_phi2, "h_phi2", "Phi2", 1000, -4, 4);
        createHistograms(h_pt3, "h_pt3", "pT3", 1000,0,250);
        createHistograms(h_eta3, "h_eta3", "Eta3", 1000, -3, 3);
        createHistograms(h_phi3, "h_phi3", "Phi3", 1000, -4, 4);
        createHistograms(h_pt4, "h_pt4", "pT4", 1000,0,250);
        createHistograms(h_eta4, "h_eta4", "Eta4", 1000, -3, 3);
        createHistograms(h_phi4, "h_phi4", "Phi4", 1000, -4, 4);
        
        Long64_t nEnt = t->GetEntriesFast();
        Long64_t pass = 0;

        for(Long64_t i=0;i<nEnt;i++){//evt loop
            t->GetEntry(i);

            if (i % 1000000 == 0 && i > 0)
                std::cout << "    processed " << i << " / " << nEnt << std::endl;

            string catstr = numberToCat(cat);
            char* cat_name = const_cast<char*>(catstr.c_str());
            
            if (std::find(channels.begin(), channels.end(), catstr) == channels.end()) continue;
            if (!(USEFR)) {
                if (!passEventCuts(catstr, isData, isDY, isTT, isWJ, isQCD, TIGHT)) continue;
            }
            if (USEFR) {
                if (!passEventCuts(catstr, isData, isDY, isTT, isWJ, isQCD, LOOSE)) continue;
            }
            // if (!passEventCuts(catstr, isData, isDY, isTT, isWJ, isQCD, LOOSE_NOT_TIGHT)) continue;

            vector<Lepton> L;

            if(pt_1>0) L.emplace_back(pt_1,eta_1,phi_1,m_1,q_1,d0_1,dZ_1,iso_1);
            if(pt_2>0) L.emplace_back(pt_2,eta_2,phi_2,m_2,q_2,d0_2,dZ_2,iso_2);
            if(pt_3>0) L.emplace_back(pt_3,eta_3,phi_3,m_3,q_3,d0_3,dZ_3,iso_3);
            if(pt_4>0) L.emplace_back(pt_4,eta_4,phi_4,m_4,q_4,d0_4,dZ_4,iso_4);

            double ST = 0.0;
            for(const auto& lep : L)
                ST += lep.pt;

            if (USEFR) {
            bool isFakeTau_eet_mmt = (!isData &&
                            (catstr == "eet" || catstr == "mmt") &&
                            gen_match_3 != 5);

            bool isRealTau_eet_mmt = (!isData &&
                            (catstr == "eet" || catstr == "mmt") &&
                            gen_match_3 == 5);

            if (!isData && (catstr == "eet" || catstr == "mmt")) {
                if (isRealTau_eet_mmt) {
                    if (!passTightTau(3))
                        continue;
                }

                if (isFakeTau_eet_mmt) {
                    if (!passFakeSelection(3))
                        continue;
                }
            }
            // 

            bool isRealTau_eett_mmtt = (!isData && 
                                        (catstr == "eett" || catstr == "mmtt") && 
                                        gen_match_3 == 5 && gen_match_4 == 5);

            bool isFakeTau_eett_mmtt = (!isData && 
                                        (catstr == "eett" || catstr == "mmtt") && 
                                        (gen_match_3 != 5 || gen_match_4 != 5));

            if (!isData && (catstr == "eett" || catstr == "mmtt")) {
                if (isRealTau_eett_mmtt) {
                    if (!(passTightTau(3) && passTightTau(4)))
                        continue;
                }

                if (isFakeTau_eett_mmtt) {
                    bool t3f = (gen_match_3 != 5);
                    bool t4f = (gen_match_4 != 5);

                    if (t3f && t4f) {
                        if (!(passFakeSelection(3) && passFakeSelection(4)))
                            continue;
                    }
                    else if (t3f && !t4f) {
                        if (!(passFakeSelection(3) && passTightTau(4))) 
                            continue;
                    }
                    else if (!t3f && t4f) {
                        if (!(passTightTau(3) && passFakeSelection(4))) continue;
                    }
                }
            }

            bool isRealTau_ett_mtt = (!isData && 
                                    (catstr == "ett" || catstr == "mtt") && 
                                    gen_match_2 == 5 && gen_match_3 == 5);

            bool isFakeTau_ett_mtt = (!isData && 
                                    (catstr == "ett" || catstr == "mtt") && 
                                    (gen_match_2 != 5 || gen_match_3 != 5));

            if (!isData && (catstr == "ett" || catstr == "mtt")) {

                if (isRealTau_ett_mtt) {
                    if (!(passTightTau(2) && passTightTau(3)))
                        continue;
                }
                else if (isFakeTau_ett_mtt) {
                    bool t2f = (gen_match_2 != 5);
                    bool t3f = (gen_match_3 != 5);

                    if (t2f && t3f) {
                        if (!(passFakeSelection(2) && passFakeSelection(3)))
                            continue;
                    }
                    else if (t2f && !t3f) {
                        if (!(passFakeSelection(2) && passTightTau(3))) 
                            continue;
                    }
                    else if (!t2f && t3f) {
                        if (!(passTightTau(2) && passFakeSelection(3))) 
                            continue;
                    }
                }
            }

            if (!isData && (catstr == "ettt" || catstr == "mttt")) {
                bool t2f = (gen_match_2 != 5);
                bool t3f = (gen_match_3 != 5);
                bool t4f = (gen_match_4 != 5);

                if (!t2f && !t3f && !t4f) {
                    if (!(passTightTau(2) && passTightTau(3) && passTightTau(4))) 
                        continue;
                }

                else {
                    if (t2f && t3f && t4f) {
                        if (!(passFakeSelection(2) && passFakeSelection(3) && passFakeSelection(4))) 
                            continue;
                    }                    
                    else if (t2f && t3f && !t4f) {
                        if (!(passFakeSelection(2) && passFakeSelection(3) && passTightTau(4))) 
                            continue;
                    }
                    else if (t2f && !t3f && t4f) {
                        if (!(passFakeSelection(2) && passTightTau(3) && passFakeSelection(4))) 
                            continue;
                    }
                    else if (!t2f && t3f && t4f) {
                        if (!(passTightTau(2) && passFakeSelection(3) && passFakeSelection(4))) 
                            continue;
                    }
                    else if (t2f && !t3f && !t4f) {
                        if (!(passFakeSelection(2) && passTightTau(3) && passTightTau(4))) 
                            continue;
                    }
                    else if (!t2f && t3f && !t4f) {
                        if (!(passTightTau(2) && passFakeSelection(3) && passTightTau(4))) 
                            continue;
                    }
                    else if (!t2f && !t3f && t4f) {
                        if (!(passTightTau(2) && passTightTau(3) && passFakeSelection(4))) 
                            continue;
                    }
                }
            }
            }
            else {
                if (!isData) {
                if (catstr == "eet" || catstr == "mmt") {
                    if (!passTightTau(3)) continue;
                }
                else if (catstr == "eett" || catstr == "mmtt") {
                    if (!(passTightTau(3) && passTightTau(4))) continue;
                }
                else if (catstr == "ett" || catstr == "mtt") {
                    if (!(passTightTau(2) && passTightTau(3))) continue;
                }
                else if (catstr == "ettt" || catstr == "mttt") {
                    if (!(passTightTau(2) && passTightTau(3) && passTightTau(4))) continue;
                }
            }
            }

            bool dup=false;
            for(size_t a=0;a<L.size() && !dup;a++){
                for(size_t b=a+1;b<L.size();b++){
                    if(isDuplicate(L[a],L[b])) { dup=true; break; }
                }
            }
            if(dup) continue;

            double evtwt_nom = 1.0;
            double w_FR = 1.0;


            double xsw_corrected = 1;// xsw;
            // if (!isData && isDY50) xsw_corrected *= 0.9936;

            if (!isData) {
                            evtwt_nom = Generator_weight * brWeight * xsw_corrected;
                            evtwt_nom *= L1PreFiringWeight_Nom * weightPUtruejson;

                            double id_sf = 1.0, iso_sf = 1.0;
                            double tauEle_sf = 1.0, tauMu_sf = 1.0, tauJet_sf = 1.0;

                            int nLep = catstr.size();
                            
                            if (nLep >= 1) {
                                id_sf *= IDSF_1; iso_sf *= ISOSF_1; 
                                tauEle_sf *= TauVsEleIDSF_1; tauMu_sf *= TauVsMuIDSF_1; tauJet_sf *= TauVsJetIDSF_1;
                            }
                            if (nLep >= 2) {
                                id_sf *= IDSF_2; iso_sf *= ISOSF_2;
                                tauEle_sf *= TauVsEleIDSF_2; tauMu_sf *= TauVsMuIDSF_2; tauJet_sf *= TauVsJetIDSF_2;
                            }
                            if (nLep >= 3) {
                                id_sf *= IDSF_3; iso_sf *= ISOSF_3;
                                tauEle_sf *= TauVsEleIDSF_3; tauMu_sf *= TauVsMuIDSF_3; tauJet_sf *= TauVsJetIDSF_3;
                            }
                            if (nLep >= 4) {
                                id_sf *= IDSF_4; iso_sf *= ISOSF_4;
                                tauEle_sf *= TauVsEleIDSF_4; tauMu_sf *= TauVsMuIDSF_4; tauJet_sf *= TauVsJetIDSF_4;
                            }

                            evtwt_nom *= id_sf * iso_sf * tauEle_sf * tauMu_sf * tauJet_sf;

                            double trig_sf = 1.0;

                            if (nLep < 3) {
                                if (isTrig_1 >= 1)      trig_sf = TrigSF_1;
                                else if (isTrig_1 == -1) trig_sf = TrigSF_2;
                            } 
                            else {
                                if (isTrig_1 >= 1 && isTrig_2 == 0)      trig_sf = TrigSF_1;
                                else if (isTrig_1 == -1 && isTrig_2 == 0) trig_sf = TrigSF_2;
                                else if (isTrig_2 >= 1 && isTrig_1 == 0)  trig_sf = TrigSF_3;
                                else if (isTrig_2 == -1 && isTrig_1 == 0) trig_sf = TrigSF_4;
                                else if (isTrig_1 == 2 && isTrig_2 == 2)  trig_sf = TrigSF_1;
                            }

                            evtwt_nom *= trig_sf;
                        }

            // if (!isData) {

            //     evtwt_nom = Generator_weight * brWeight * xsw_corrected;
            //     evtwt_nom *= L1PreFiringWeight_Nom * weightPUtruejson;

            //     double id_sf = 1.0, iso_sf = 1.0, trig_sf = 1.0;
            //     double tauEle_sf = 1.0, tauMu_sf = 1.0, tauJet_sf = 1.0;

            //     if (catstr.size() >= 1) {
            //         id_sf *= IDSF_1; iso_sf *= ISOSF_1; trig_sf *= TrigSF_1;
            //         tauEle_sf *= TauVsEleIDSF_1; tauMu_sf *= TauVsMuIDSF_1; tauJet_sf *= TauVsJetIDSF_1;
            //     }
            //     if (catstr.size() >= 2) {
            //         id_sf *= IDSF_2; iso_sf *= ISOSF_2; trig_sf *= TrigSF_2;
            //         tauEle_sf *= TauVsEleIDSF_2; tauMu_sf *= TauVsMuIDSF_2; tauJet_sf *= TauVsJetIDSF_2;
            //     }
            //     if (catstr.size() >= 3) {
            //         id_sf *= IDSF_3; iso_sf *= ISOSF_3; trig_sf *= TrigSF_3;
            //         tauEle_sf *= TauVsEleIDSF_3; tauMu_sf *= TauVsMuIDSF_3; tauJet_sf *= TauVsJetIDSF_3;
            //     }
            //     if (catstr.size() >= 4) {
            //         id_sf *= IDSF_4; iso_sf *= ISOSF_4; trig_sf *= TrigSF_4;
            //         tauEle_sf *= TauVsEleIDSF_4; tauMu_sf *= TauVsMuIDSF_4; tauJet_sf *= TauVsJetIDSF_4;
            //     }

            //     evtwt_nom *= id_sf * iso_sf * trig_sf * tauEle_sf * tauMu_sf * tauJet_sf;

            // }
            
			if (year=="2018"){//HEM veto
				if (isData and run >= 319077 and applyHEMveto(catstr) == "yes") continue;
				if (!isData and applyHEMveto(catstr) == "yes") evtwt_nom *= 0.35;
			}
            applyTauES(catstr);
            
            if (USEFR) {

                if (!isData && (catstr == "eet" || catstr == "mmt") && gen_match_3 != 5) {

                    double fData = getTauFakeRate2D(
                        L[2].pt,
                        L[2].eta,
                        year,
                        FR_Data2D
                    );

                    if (fData > 0.0 && fData < 1.0)
                        w_FR *= getEpsilon(fData);
                }

                if (!isData && (catstr == "eett" || catstr == "mmtt")) {

                    bool t3f = (gen_match_3 != 5);
                    bool t4f = (gen_match_4 != 5);

                    if (t3f || t4f) {

                        double f3 = getTauFakeRate2D(
                            L[2].pt,
                            L[2].eta,
                            year,
                            FR_Data2D
                        );

                        double f4 = getTauFakeRate2D(
                            L[3].pt,
                            L[3].eta,
                            year,
                            FR_Data2D
                        );

                        double F3 = getEpsilon(f3);
                        double F4 = getEpsilon(f4);

                        if (t3f && t4f)      w_FR *= (F3 * F4);
                        else if (t3f)        w_FR *= F3;
                        else if (t4f)        w_FR *= F4;
                    }
                }

                if (!isData && (catstr == "ett" || catstr == "mtt")) {

                    bool t2f = (gen_match_2 != 5);
                    bool t3f = (gen_match_3 != 5);

                    if (t2f || t3f) {

                        double f2 = getTauFakeRate2D(
                            L[1].pt,
                            L[1].eta,
                            year,
                            FR_Data2D
                        );

                        double f3 = getTauFakeRate2D(
                            L[2].pt,
                            L[2].eta,
                            year,
                            FR_Data2D
                        );

                        double F2 = getEpsilon(f2);
                        double F3 = getEpsilon(f3);

                        if (t2f && t3f)      w_FR *= (F2 * F3);
                        else if (t2f)        w_FR *= F2;
                        else if (t3f)        w_FR *= F3;
                    }
                }

                if (!isData && (catstr == "ettt" || catstr == "mttt")) {

                    bool t2f = (gen_match_2 != 5);
                    bool t3f = (gen_match_3 != 5);
                    bool t4f = (gen_match_4 != 5);

                    if (t2f || t3f || t4f) {

                        double f2 = getTauFakeRate2D(
                            L[1].pt,
                            L[1].eta,
                            year,
                            FR_Data2D
                        );

                        double f3 = getTauFakeRate2D(
                            L[2].pt,
                            L[2].eta,
                            year,
                            FR_Data2D
                        );

                        double f4 = getTauFakeRate2D(
                            L[3].pt,
                            L[3].eta,
                            year,
                            FR_Data2D
                        );

                        double F2 = getEpsilon(f2);
                        double F3 = getEpsilon(f3);
                        double F4 = getEpsilon(f4);

                        if (t2f && t3f && t4f)        w_FR *= (F2 * F3 * F4);
                        else if (t2f && t3f && !t4f)  w_FR *= (F2 * F3);
                        else if (t2f && !t3f && t4f)  w_FR *= (F2 * F4);
                        else if (!t2f && t3f && t4f)  w_FR *= (F3 * F4);
                        else if (t2f && !t3f && !t4f) w_FR *= F2;
                        else if (!t2f && t3f && !t4f) w_FR *= F3;
                        else if (!t2f && !t3f && t4f) w_FR *= F4;
                    }
                }
            }
            else {
                w_FR = 1.0;
            }

            evtwt_nom *= w_FR;

            pass++;
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
				// Sort the lepton variables in descending order based on pt
				/*std::sort(leptons.begin(), leptons.end(), [](const Lepton& a, const Lepton& b) {
					return a.pt > b.pt;
				});*/
				
				
				TLorentzVector MET;
				MET.SetPtEtaPhiM(met, 0, metphi, 0);
				double LT = LepV(1).Pt()+LepV(2).Pt()+LepV(3).Pt()+LepV(4).Pt();

				vector<pair<int, int>> Z_pair, Zv_pair, Ztt_pair, SS_pair;
				processPairs(cat_name, Z_pair, Zv_pair, Ztt_pair, SS_pair, Ztt_pair);//were putiing OSDF pairs in Ztt container for now.
				Zv_pair = removeOverlap(Zv_pair, strlen(cat_name));

				//don't remove duplicates in Zttpair yet as we'd lose et and mt too!
				//===============ordering leading pairs=====================
				std::sort(SS_pair.begin(), SS_pair.end(),[&](const std::pair<int,int>& a, const std::pair<int,int>& b){
					double pt_a = (LepV(a.first)  + LepV(a.second)).Pt();
					double pt_b = (LepV(b.first)  + LepV(b.second)).Pt();
					return pt_a > pt_b; // descending order of pt
				});
				
				std::sort(Z_pair.begin(), Z_pair.end(),[&](const std::pair<int,int>& a, const std::pair<int,int>& b){
					double pt_a = (LepV(a.first)  + LepV(a.second)).Pt();
					double pt_b = (LepV(b.first)  + LepV(b.second)).Pt();
					return pt_a > pt_b; // descending order of pt
				});
				
				std::sort(Zv_pair.begin(), Zv_pair.end(),[&](const std::pair<int,int>& a, const std::pair<int,int>& b){
					double pt_a = (LepV(a.first)  + LepV(a.second)).Pt();
					double pt_b = (LepV(b.first)  + LepV(b.second)).Pt();
					return pt_a > pt_b; // descending order of pt
				});
				std::sort(Ztt_pair.begin(), Ztt_pair.end(),[&](const std::pair<int,int>& a, const std::pair<int,int>& b){
					double pt_a = (LepV(a.first)  + LepV(a.second)).Pt();
					double pt_b = (LepV(b.first)  + LepV(b.second)).Pt();
					return pt_a > pt_b; // descending order of pt
				});				
				//===========================================================
				vector<pair<int, int>> OS_pair, OSSF_pair;
				OSSF_pair.insert(OSSF_pair.end(), Z_pair.begin(), Z_pair.end());
				OSSF_pair.insert(OSSF_pair.end(), Zv_pair.begin(), Zv_pair.end());
				OSSF_pair = removeOverlap(OSSF_pair, strlen(cat_name));

				OS_pair.insert(OS_pair.end(), OSSF_pair.begin(), OSSF_pair.end());
				OS_pair.insert(OS_pair.end(), Ztt_pair.begin(), Ztt_pair.end());
				OS_pair = removeOverlap(OS_pair, strlen(cat_name));

				std::unordered_set<std::string> histCh = {"VR_0tau","VR_1tau","VR_2tau","VR_3tau","VR_3lep0tau","VR_3lep1tau","VR_3lep2tau",
	 "CR_0tau","CR_1tau","CR_2tau","CR_3tau","CR_3lep0tau","CR_3lep1tau","CR_3lep2tau",
	 "SR_0tau","SR_1tau","SR_2tau","SR_3tau","SR_3lep0tau","SR_3lep1tau","SR_3lep2tau",
	 "DYCR_0tau","DYCR_1tau","DYveto_0tau","DYveto_1tau",
	 "ee", "em", "mm", "eee", "eem", "eet", "emt", "mme", "mmm", "mmt",
	 "ett", "mtt", "eeee", "eeem", "eemm", "mmem", "mmmm", "eeet", "eemt",
	 "eett", "mmet", "ttem", "ttet", "mmmt", "mmtt", "ttmt", "v_ee", "v_em", "v_mm", "v_eee", "v_eem", "v_eet", "v_emt", "v_mme", "v_mmm", "v_mmt",
	 "v_tte", "v_mtt", "v_eeee", "v_eeem", "v_eemm", "v_mmem", "v_mmmm", "v_eeet", "v_eemt",
	 "v_eett", "v_mmet", "v_ettm", "v_ettt", "v_mmmt", "v_mmtt", "v_ttmt"};//makes lookup faster!!
				

				std::string channel = classifyTauRegion(cat_name, LT, OS_pair);	
				//if (channel == "CR_2tau") cout<<cat_name<<"\t"<< OS_pair.size() <<"\t"<< OSSF_pair.size() <<"\t"<< Z_pair.size() <<"\t"<< Ztt_pair.size() <<endl;
				if(!histCh.count(channel)) continue;
				fillHistograms(channel, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OS_pair, SS_pair, evtwt_nom);//fills all the tau channels
				
				/*if( catstr =="emt" ) fillHistograms(catstr, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OSSF_pair, SS_pair, evtwt_nom);
				else if( catstr =="ett" and q_2 == -q_3) fillHistograms(catstr, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OSSF_pair, SS_pair, evtwt_nom);
				else if( catstr =="mtt" and q_2 == -q_3) fillHistograms(catstr, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OSSF_pair, SS_pair, evtwt_nom);*/
				
				std::string channel1 = classifyLepRegion(cat_name, OS_pair);
				if (channel1=="mmee") channel1 = "eemm";
				if (channel1=="mmee") channel1 = "eemm";
				//if (Z_pair.size()>1 and (LepV(Z_pair[1].first)+LepV(Z_pair[1].second)).M() > 102) {
				//cout<<cat_name<<"\t"<<channel1<<(LepV(Z_pair[1].first)+LepV(Z_pair[1].second)).M()<<"\t"<<Z_pair.size()<<"\t"<<Zv_pair.size()<<endl;
					//for (auto a:Z_pair) cout<<a.first<<"\t"<<a.second<<endl;}
				
				if(!histCh.count(channel1)) continue;
				
				if (Z_pair.size() == 1){//fills DY and WZ CRs
					if (strlen(cat_name)==3 and !(met>=40)) continue; //for WZ CR
					fillHistograms(channel1, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OS_pair, SS_pair, evtwt_nom);
				}
				if(Z_pair.size() ==2){//fills ZZ CR.
					fillHistograms(channel1, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OS_pair, SS_pair, evtwt_nom);
				}
				else if (Zv_pair.size() > 0 and Z_pair.size()==0){//fills Veto Regions
					channel1 = "v_"+channel1;
					fillHistograms(channel1, h_mZ1, h_mZ2, h_mH1, h_mH2, h_met, h_LT, h_pt1, h_pt2, h_pt3, h_pt4, h_eta1, h_eta2, h_eta3, h_eta4, h_phi1, h_phi2, h_phi3, h_phi4, met, OS_pair, SS_pair, evtwt_nom);
				}
        } 

		scaleAndWriteHistograms(h_mZ1, xs_weight);
		scaleAndWriteHistograms(h_mH1, xs_weight);
		scaleAndWriteHistograms(h_mZ2, xs_weight);
		scaleAndWriteHistograms(h_mH2, xs_weight);
		scaleAndWriteHistograms(h_met, xs_weight);
		scaleAndWriteHistograms(h_LT, xs_weight);
		scaleAndWriteHistograms(h_pt1, xs_weight);
		scaleAndWriteHistograms(h_pt2, xs_weight);
		scaleAndWriteHistograms(h_pt3, xs_weight);
		scaleAndWriteHistograms(h_pt4, xs_weight);
		scaleAndWriteHistograms(h_eta1, xs_weight);
		scaleAndWriteHistograms(h_eta2, xs_weight);
		scaleAndWriteHistograms(h_eta3, xs_weight);
		scaleAndWriteHistograms(h_eta4, xs_weight);
		scaleAndWriteHistograms(h_phi1, xs_weight);
		scaleAndWriteHistograms(h_phi2, xs_weight);
		scaleAndWriteHistograms(h_phi3, xs_weight);
		scaleAndWriteHistograms(h_phi4, xs_weight);

        fout->Close();
        f->Close();

        std::cout << "  [done] processed=" << pass << " written -> " << outName << std::endl;
}
}

