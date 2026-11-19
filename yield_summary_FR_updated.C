#include <TFile.h>
#include <TH1.h>
#include <TH1D.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TString.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "include/Xsections.C"
#include "include/cms_plots.h"
#include "include/FileMap.h"
using namespace std;

// ========================== SETTINGS ==========================
const string SUMMARY_TYPE = "tau_ch"; // tau_ch, tau_ch-veto, 3lep, 3lep-veto, 4lep, 4lep-veto
const string YEAR = "Run2";
const string INPUT_DIR = "run2_noFR_metphi_zpt_recoil_roccor_toppt_chargeflip";
const string OUTPUT_DIR = "summary_plots";
const string TAU_VARIABLE = "LT";
const string FLAVOR_VARIABLE = "met";
const string SYSTEMATIC = ""; // nominal = "", or e.g. "eIdIsoUp"
const bool APPLY_XSEC_SCALE = false; // same default as stack macro; enable for unnormalized MC
const bool APPLY_OLD_NORM_FACTORS = true;
const bool INCLUDE_FAKE_UNCERT = true;
const bool INCLUDE_XSEC_UNCERT = true;
const bool INCLUDE_FLOW_BINS = true; // include original underflow/overflow in integrated yield
const bool LOG_Y = true;

const vector<string> TAU_CHANNELS = {
    "0tau", "1tau", "2tau", "3tau", "3lep0tau", "3lep1tau", "3lep2tau"
};
const vector<string> LEP_CHANNELS = {
    "eeee", "eeem", "eeet", "eemm", "eemt", "eett",
    "emem", "emet", "emmm", "emmt", "emtt",
    "etet", "etmm", "etmt", "ettt",
    "mmmm", "mmmt", "mmtt", "mtmt", "mttt", "tttt",
    "eee", "eem", "eet", "eme", "emm", "emt",
    "ete", "etm", "ett", "mme", "mmm", "mmt",
    "mte", "mtm", "mtt", "tte", "ttm", "ttt",
    "ee", "em", "et", "mm", "mt", "tt", "e", "m", "t"
};
const vector<string> BKGS = {"DY", "VV", "VVV", "ttV", "WJ", "ZZ", "ST", "TTbar", "other"};
const map<string,int> COLORS = {
    {"DY",7},{"VV",8},{"VVV",6},{"ttV",4},{"WJ",9},
    {"ZZ",5},{"ST",30},{"TTbar",46},{"other",28}
};

struct SummaryBin {
    string label;
    vector<string> histNames;
    string fakeCategory;
    bool skipFake;
};

string makeName(const string& var, const string& lepch,
                const string& region, const string& ch, const string& syst) {
    string n = "h_" + var + "_" + lepch + "_" + region + "_" + ch;
    if (!syst.empty()) n += "_" + syst;
    return n;
}

vector<SummaryBin> buildSummaryBins() {
    vector<SummaryBin> out;
    const bool veto = SUMMARY_TYPE.find("-veto") != string::npos;
    const string region = veto ? "VR" : "CR";

    if (SUMMARY_TYPE == "tau_ch" || SUMMARY_TYPE == "tau_ch-veto") {
        for (const string& ch : TAU_CHANNELS) {
            SummaryBin b;
            b.label = ch;
            b.fakeCategory = ch.find("3lep") == 0 ? "3lep" : "4lep";
            b.skipFake = false;
            for (const string& lepch : LEP_CHANNELS)
                b.histNames.push_back(makeName(TAU_VARIABLE, lepch, region, ch, SYSTEMATIC));
            out.push_back(b);
        }
    } else if (SUMMARY_TYPE == "3lep" || SUMMARY_TYPE == "3lep-veto" ||
               SUMMARY_TYPE == "4lep" || SUMMARY_TYPE == "4lep-veto") {
        // Keep the original summary-bin ordering, including the 2-lepton control bins.
        vector<string> flavors;
        if (SUMMARY_TYPE.find("3lep") == 0)
            flavors = {"ee","eee","eem","eet","ett","mm","emm","mmm","mmt","mtt"};
        else
            flavors = {"eeee","eeem","eemm","mmem","mmmm","eeet","eemt",
                       "eett","emtt","emmt","ettt","mmmt","mmtt","mttt"};

        for (const string& lepch : flavors) {
            SummaryBin b;
            b.label = lepch;
            b.fakeCategory = SUMMARY_TYPE;
            b.skipFake = (lepch == "ee" || lepch == "mm");
            // A 3-lepton flavor is only in 3lep* categories; 4-lepton flavors in 0tau..3tau.
            // 2-lepton control flavors are tried in every configured category; absent names are skipped.
            for (const string& ch : TAU_CHANNELS) {
                if (lepch.size() == 3 && ch.find("3lep") != 0) continue;
                if (lepch.size() == 4 && ch.find("3lep") == 0) continue;
                b.histNames.push_back(makeName(FLAVOR_VARIABLE, lepch, region, ch, SYSTEMATIC));
            }
            out.push_back(b);
        }
    } else {
        cerr << "Unknown SUMMARY_TYPE: " << SUMMARY_TYPE << endl;
    }
    return out;
}

// Read each original histogram only once; do not mutate TFile-owned objects.
// Returns yield and variance. Independent histogram contributions are combined in quadrature.
pair<double,double> fileBinYield(TFile* f, const SummaryBin& bin, const string& process,
                                 size_t& found) {
    double yield = 0.0, variance = 0.0;
    for (const string& name : bin.histNames) {
        TH1* h = dynamic_cast<TH1*>(f->Get(name.c_str()));
        if (!h) continue;
        ++found;
        const int low = INCLUDE_FLOW_BINS ? 0 : 1;
        const int high = INCLUDE_FLOW_BINS ? h->GetNbinsX()+1 : h->GetNbinsX();
        double stat = 0.0;
        const double raw = h->IntegralAndError(low, high, stat);
        const double scale = (process != "data" && APPLY_XSEC_SCALE) ? applyXSec(f) : 1.0;
        const double y = raw * scale;
        const double statErr = stat * std::abs(scale);
        double var = statErr * statErr;
        if (process != "data") {
            if (INCLUDE_XSEC_UNCERT) {
                const double xs = y * XSec_Uncert(f->GetName()) / 100.0;
                var += xs * xs;
            }
            if (INCLUDE_FAKE_UNCERT && !bin.skipFake) {
                const double fake2 = fake_uncert_squared(bin.fakeCategory, f->GetName());
                var += std::max(0.0, fake2) * y * y;
            }
        }
        yield += y;
        variance += var;
    }
    return {yield, variance};
}

void yield_summary_FR_updated() {
    gStyle->SetOptStat(0);
    gSystem->mkdir(OUTPUT_DIR.c_str(), true);
    const vector<SummaryBin> bins = buildSummaryBins();
    if (bins.empty()) return;

    map<string, vector<TFile*>> openFiles;
    const auto files = getFileMap(YEAR);
    for (const auto& kv : files) {
        for (const string& fname : kv.second) {
            const string path = INPUT_DIR + "/hist_" + fname;
            TFile* f = TFile::Open(path.c_str(), "READ");
            if (!f || f->IsZombie()) {
                cerr << "WARNING: cannot open " << path << endl;
                if (f) { f->Close(); delete f; }
                continue;
            }
            openFiles[kv.first].push_back(f);
        }
    }

    map<string, TH1D*> summaries;
    for (const string& proc : BKGS) {
        summaries[proc] = new TH1D(("summary_" + proc).c_str(), "", bins.size(), 0.5, bins.size()+0.5);
        summaries[proc]->SetDirectory(nullptr);
        summaries[proc]->Sumw2();
        summaries[proc]->SetFillColor(COLORS.at(proc));
        summaries[proc]->SetLineColor(kBlack);
    }
    summaries["data"] = new TH1D("summary_data", "", bins.size(), 0.5, bins.size()+0.5);
    summaries["data"]->SetDirectory(nullptr);
    summaries["data"]->Sumw2();

    for (size_t i=0; i<bins.size(); ++i) {
        cout << "\nBin " << i+1 << " (" << bins[i].label << ")" << endl;
        for (auto& kv : summaries) {
            double yield = 0, variance = 0;
            size_t found = 0;
            for (TFile* f : openFiles[kv.first]) {
                auto result = fileBinYield(f, bins[i], kv.first, found);
                yield += result.first;
                variance += result.second;
            }
            kv.second->SetBinContent(i+1, yield);
            kv.second->SetBinError(i+1, sqrt(std::max(0.0,variance)));
            cout << "  " << kv.first << ": " << found << " histograms, yield=" << yield
                 << " +/- " << sqrt(std::max(0.0,variance)) << endl;
        }
    }
    if (APPLY_OLD_NORM_FACTORS) {
        summaries["VV"]->Scale(1.033462);
        summaries["ZZ"]->Scale(1.284495);
    }

    THStack* stack = new THStack("summary_stack", ";;Events / bin");
    TH1D* total = (TH1D*)summaries[BKGS.front()]->Clone("summary_total");
    total->SetDirectory(nullptr);
    total->Reset();
    for (const string& proc : BKGS) {
        stack->Add(summaries[proc]);
        total->Add(summaries[proc]);
    }
    TH1D* data = summaries["data"];
    TCanvas* c = new TCanvas("summary_canvas", "Yield summary", 950, 750);
    TPad* p1 = new TPad("summary_top", "", 0,0.3,1,1);
    TPad* p2 = new TPad("summary_bottom", "", 0,0,1,0.3);
    p1->SetBottomMargin(0.02);
    p2->SetTopMargin(0.02);
    p2->SetBottomMargin(0.32);
    p1->Draw(); p2->Draw();
    p1->cd();
    if (LOG_Y) p1->SetLogy();
    stack->Draw("HIST");
    stack->SetMaximum(std::max(1.0, 1.5*std::max(stack->GetMaximum(), data->GetMaximum())));
    if (LOG_Y) stack->SetMinimum(0.1);
    data->SetMarkerStyle(20);
    data->SetMarkerColor(kBlack);
    data->SetLineColor(kBlack);
    data->Draw("E1 SAME");
    DrawCMSLabel();
    string description = "Yield summary " + SUMMARY_TYPE + " (" +
        (SUMMARY_TYPE.find("-veto") != string::npos ? "VR" : "CR") + ")";
    PlotDescription(const_cast<char*>(description.c_str()));
    TLegend* legend = new TLegend(0.12,0.58,0.31,0.88);
    legend->SetBorderSize(0);
    for (const string& proc : BKGS) legend->AddEntry(summaries[proc], proc.c_str(), "f");
    legend->AddEntry(data,"Data","lep");
    legend->Draw();

    p2->cd();
    TH1D* ratio = (TH1D*)data->Clone("summary_ratio");
    ratio->SetDirectory(nullptr);
    ratio->Reset();
    ratio->SetTitle("");
    ratio->SetMinimum(0);
    ratio->SetMaximum(2);
    ratio->SetMarkerStyle(20);
    ratio->GetYaxis()->SetTitle("Data / Background");
    ratio->GetYaxis()->SetNdivisions(505);
    ratio->GetYaxis()->SetTitleSize(0.09);
    ratio->GetYaxis()->SetTitleOffset(0.4);
    ratio->GetYaxis()->SetLabelSize(0.07);
    ratio->GetXaxis()->SetLabelSize(0.12);
    ratio->GetXaxis()->SetTitleSize(0.1);
    TH1D* band = (TH1D*)total->Clone("summary_band");
    band->SetDirectory(nullptr);
    band->Reset();
    for (size_t i=0; i<bins.size(); ++i) {
        int b = i+1;
        const double mc = total->GetBinContent(b);
        ratio->GetXaxis()->SetBinLabel(b, bins[i].label.c_str());
        if (mc > 0) {
            ratio->SetBinContent(b, data->GetBinContent(b)/mc);
            ratio->SetBinError(b, data->GetBinError(b)/mc);
            band->SetBinContent(b,1.0);
            band->SetBinError(b,total->GetBinError(b)/mc);
        }
    }
    ratio->Draw("E1");
    band->SetFillColor(kGray+2);
    band->SetFillStyle(3001);
    band->SetLineColor(0);
    band->Draw("E2 SAME");
    TLine* ref = new TLine(0.5,1,bins.size()+0.5,1);
    ref->SetLineStyle(2);
    ref->Draw();
    ratio->Draw("E1 SAME");
    c->cd();
    const string output = OUTPUT_DIR + "/summary_" + SUMMARY_TYPE + "_" + YEAR +
        (SYSTEMATIC.empty() ? "" : "_"+SYSTEMATIC);
    c->SaveAs((output+".png").c_str());
    c->SaveAs((output+".pdf").c_str());
    for (auto& kv : openFiles) for (TFile* f : kv.second) { f->Close(); delete f; }
    // ROOT owns drawn primitives through the canvas/pads; leave plot objects alive until ROOT exits.
}
