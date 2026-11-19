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
#include <cmath>
#include <limits>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <TGraphAsymmErrors.h>
#include "include/Xsections.C"
#include "include/cms_plots.h"
#include "include/FileMap.h"

using namespace std;

// ========================== USER SETTINGS ==========================
const string INPUT_DIR = "run2_tauFR_all_corrections_hist";
const string OUTPUT_DIR = "stack_plots";
const string YEAR = "Run2";
const string SUMMARY_TYPE = "tau_ch";   // "lep_ch" = inclusive lepch
const vector<string> VARIABLES = {"LT", "mZ1","met","mH1",//"mZ2", "mH2",
								/*"pt1","pt2", "pt3", "pt4",
								"eta1","eta2", "eta3", "eta4",
								"phi1","phi2", "phi3", "phi4",
								"iso1","iso2", "iso3", "iso4",
								"dxy1","dxy2", "dxy3", "dxy4",
								"dZ1","dZ2", "dZ3", "dZ4",*/};
const vector<string> SYSTEMATICS = {""};  //systematic to plot e.g. {"", "eIdIsoUp", "eIdIsoDown"}
const vector<string> fullSystList = {//systematic to use in the band
    "eIdIso",
    "eReco",
    "eTrig",
    "l1Prefire",
    "muId",
    "muIso",
    "muTrig",
    "roccor",
    "tauES",
    "tauVsEle",
    "tauVsJet",
    "tauVsMu",
    //"xsec"//already in xsec file
};

const vector<string> LEP_CHANNELS = {
        "eeee", "eeem", "eeet", "eemm", "eemt", "eett",
                "emem", "emet", "emmm", "emmt", "emtt",
                        "etet", "etmm", "etmt", "ettt",
                                "mmmm", "mmmt", "mmtt",
                                        "mtmt", "mttt",
                                                "tttt",
          "eee", "eem", "eet",
          "eme", "emm", "emt",
          "ete", "etm", "ett",
          "mme", "mmm", "mmt",
          "mte", "mtm", "mtt",
          "tte", "ttm", "ttt",
          "ee","em","et","mm","mt","tt","e","m","t"};
const vector<string> REGIONS = {"VR"};//,"DYCR", "SR", "SS_incl","SS_Zwin","SS_Zveto","OS_incl","OS_Zwin","OS_Zveto"};
const vector<string> CHANNELS = {"0tau","1tau","2tau"};
const bool LOG_Y = true;
const double SIGNAL_SCALE = 1;
const bool DRAW_SIGNAL = false;
const bool APPLY_XSEC_SCALE = false; // Set true only if input histograms are NOT normalized
const bool APPLY_OLD_NORM_FACTORS = true; // VV * 1.033462, ZZ * 1.284495
const bool INCLUDE_FAKE_UNCERT = true; // legacy fake-rate variance already included in nominal errors
const bool DRAW_SYST_BAND = true; // nominal plots only
const int REBIN_FACTOR = 1; // common rebin factor for ALL histograms, 1 = none

map<string, pair<double, double>> X_RANGES = {
    {"mZ1",   {70, 110}},
	{"mZ2",   {0, 250}},
    {"mH1", {0, 500}},
    {"mH2", {0, 500}},
    {"met",   {0, 200}},
    {"LT",    {0, 1000}}
};
// ==================================================================

const vector<string> BKGS = {"DY","VV","VVV","ttV","WJ","ZZ","ST","TTbar","other"};
const map<string,int> COLORS = {
    {"DY",7},{"VV",8},{"VVV",6},{"ttV",4},{"WJ",9},
    {"ZZ",5},{"ST",30},{"TTbar",46},{"other",28}
};



string histName(const string& var, const string& lepch, const string& region,
                const string& ch, const string& syst) {
    string n = "h_" + var + "_" + lepch;
    if (!region.empty()) n += "_" + region;
    if (!ch.empty()) n += "_" + ch;
    if (!syst.empty()) n += "_" + syst;
    return n;
}

// SUMMARY_TYPE == "tau_ch": sum over lepch at fixed (var, region, ch, syst).
// Otherwise: sum over ch at fixed (var, lepch, region, syst).
vector<string> selectedNames(const string& var, const string& region,
                             const string& category, const string& syst) {
    vector<string> out;
    if (SUMMARY_TYPE == "tau_ch") {
        for (const auto& lepch : LEP_CHANNELS)
            out.push_back(histName(var, lepch, region, category, syst));
    } else {
        for (const auto& ch : CHANNELS)
            out.push_back(histName(var, category, region, ch, syst));
    }
    return out;
}
void MergeOverflowInRange(TH1* h, double xmin, double xmax)
{
    if (!h || !(xmin < xmax)) return;
    const int nb = h->GetNbinsX();
    const int first = std::max(1, std::min(nb, h->GetXaxis()->FindFixBin(xmin)));
    const int last = std::max(1, std::min(nb,
        h->GetXaxis()->FindFixBin(std::nextafter(xmax, -std::numeric_limits<double>::infinity()))));
    if (first > last) return;

    // Handle one-bin ranges without double counting.
    if (first == last) {
        double content = 0, err2 = 0;
        for (int i = 0; i <= nb + 1; ++i) {
            content += h->GetBinContent(i);
            err2 += std::pow(h->GetBinError(i), 2);
            h->SetBinContent(i, 0);
            h->SetBinError(i, 0);
        }
        h->SetBinContent(first, content);
        h->SetBinError(first, std::sqrt(err2));
        return;
    }

    double low = 0, lowErr2 = 0, high = 0, highErr2 = 0;
    for (int i = 0; i <= first; ++i) {
        low += h->GetBinContent(i);
        lowErr2 += std::pow(h->GetBinError(i), 2);
    }
    for (int i = last; i <= nb + 1; ++i) {
        high += h->GetBinContent(i);
        highErr2 += std::pow(h->GetBinError(i), 2);
    }
    for (int i = 0; i <= nb + 1; ++i) {
        if (i < first || i > last) {
            h->SetBinContent(i, 0);
            h->SetBinError(i, 0);
        }
    }
    h->SetBinContent(first, low);
    h->SetBinError(first, std::sqrt(lowErr2));
    h->SetBinContent(last, high);
    h->SetBinError(last, std::sqrt(highErr2));
}
double NBINS = 10;//total number of bins you'd see in the plot
// Apply exactly the same binning and custom range to nominal and variations.
void prepareForPlot(TH1D* h, double xmin, double xmax) {
    if (!h) return;
    const double fullWidth = h->GetXaxis()->GetXmax() - h->GetXaxis()->GetXmin();
    if (fullWidth > 0 && xmax > xmin) {
        int factor = static_cast<int>(std::round((xmax-xmin) / fullWidth * h->GetNbinsX() / NBINS));//total number of bins you'd see in the plot
        factor = std::max(1, factor);
        // ROOT requires a compatible integer factor; avoid truncated remainder bins.
        while (factor > 1 && h->GetNbinsX() % factor != 0) --factor;
        if (factor > 1) h->Rebin(factor);
    }
    MergeOverflowInRange(h, xmin, xmax);
}

string axisTitle(const string& var) {
    const map<string,string> labels = {
        {"mH1","Leading SS pair invariant mass [GeV]"},
        {"mH2","Sub-leading SS pair invariant mass [GeV]"},
        {"met","E_{T}^{miss} [GeV]"},
        {"LT","L_{T} [GeV]"},
        {"mZ1","Leading OSSF pair invariant mass [GeV]"},
        {"mZ2","Sub-leading OSSF pair invariant mass [GeV]"},
        {"WMt","W transverse mass [GeV]"}
    };
    auto it = labels.find(var);
    return it == labels.end() ? var : it->second;
}

// Returns a detached copy; never rebin or modify the original TFile histogram.
TH1D* copyHistogram(TFile* f, const string& name) {
    auto* src = dynamic_cast<TH1D*>(f->Get(name.c_str()));
    if (!src) return nullptr;
    static unsigned long serial = 0;
    auto* h = (TH1D*)src->Clone(Form("tmp_%lu", ++serial));
    h->SetDirectory(nullptr);
    h->Sumw2();
    if (REBIN_FACTOR > 1) h->Rebin(REBIN_FACTOR);
    return h;
}

bool compatible(const TH1D* a, const TH1D* b) {
    if (a->GetNbinsX() != b->GetNbinsX()) return false;
    for (int i=1; i<=a->GetNbinsX()+1; ++i)
        if (std::abs(a->GetXaxis()->GetBinLowEdge(i)-b->GetXaxis()->GetBinLowEdge(i)) > 1e-7)
            return false;
    return true;
}

// Apply per-file normalization/systematic error BEFORE adding to the process total.
void prepareSample(TH1D* h, TFile* f, const string& process, const string& name) {
    if (process == "data") return;
    if (APPLY_XSEC_SCALE) h->Scale(applyXSec(f));
    for (int b=1; b<=h->GetNbinsX(); ++b) {
        const double y = h->GetBinContent(b);
        const double stat = h->GetBinError(b);
        const double xsec = y * XSec_Uncert(f->GetName()) / 100.;
        double variance = stat*stat + xsec*xsec;
        if (INCLUDE_FAKE_UNCERT) {
            double fake = 0.;
            if (SUMMARY_TYPE == "tau_ch") {
                fake = fake_uncert_squared(name.find("3lep") != string::npos ? "3lep" : "4lep", f->GetName());
            } else if (name.find("h_met_ee") == string::npos &&
                       name.find("h_met_mm") == string::npos &&
                       name.find("h_metv_ee") == string::npos &&
                       name.find("h_metv_mm") == string::npos) {
                fake = fake_uncert_squared(SUMMARY_TYPE, f->GetName());
            }
            variance += fake*y*y; // fake_uncert_squared returns a squared fractional uncertainty
        }
        h->SetBinError(b, std::sqrt(std::max(0.,variance)));
//	if(variance>0.0001) cout<<h->GetName()<<" fake rate uncert is: "<<variance<<endl;
    }
}

TGraphAsymmErrors* MakeRatioUncertaintyBand(
    TH1D* nominal,
    const map<string, pair<TH1D*, TH1D*>>& systematics
)
{
    int nbins = nominal->GetNbinsX();

    TGraphAsymmErrors* band = new TGraphAsymmErrors(nbins);

    for (int i = 1; i <= nbins; i++)
    {
        double B = nominal->GetBinContent(i);
        double stat = nominal->GetBinError(i);

        double errUp2 = stat * stat;
        double errDown2 = stat * stat;

        for (const auto& kv : systematics)
        {
            TH1D* hUp = kv.second.first;
            TH1D* hDown = kv.second.second;

            if (!hUp || !hDown)
                continue;

            double up = hUp->GetBinContent(i) - B;
            double down = hDown->GetBinContent(i) - B;

            double deltaPlus = std::max({0.0, up, down});
            double deltaMinus = std::max({0.0, -up, -down});

            errUp2 += deltaPlus * deltaPlus;
            errDown2 += deltaMinus * deltaMinus;
        }

        double x = nominal->GetBinCenter(i);
        double ex = nominal->GetBinWidth(i) / 2.0;

        double eyUp = 0;
        double eyDown = 0;

        if (B > 0)
        {
            eyUp = sqrt(errUp2) / B;
            eyDown = sqrt(errDown2) / B;
        }

        band->SetPoint(i - 1, x, 1.0);
        band->SetPointError(
            i - 1,
            ex, ex,
            eyDown, eyUp
        );
    }

    band->SetFillColor(kGray + 2);
    band->SetFillStyle(3001);
    band->SetLineColor(kGray + 2);

    return band;
}

TH1D* combineProcess(const vector<TFile*>& input, const vector<string>& names,
                     const string& process, const string& outputName) {
    TH1D* sum = nullptr;
    size_t found = 0;
    for (TFile* f : input) {
        if (!f || f->IsZombie()) continue;
        for (const auto& name : names) {
            TH1D* h = copyHistogram(f,name);
            if (!h) continue;
            prepareSample(h,f,process,name);
            if (!sum) {
                sum = (TH1D*)h->Clone(outputName.c_str());
                sum->SetDirectory(nullptr);
            } else if (compatible(sum,h)) {
                sum->Add(h);
            } else {
                cerr << "WARNING: incompatible bins in " << f->GetName() << ":" << name << endl;
            }
            ++found;
            delete h;
        }
    }
    cout << "  " << process << ": " << found << " histograms found\n";
    return sum;
}

// Sum the same exclusive categories/files as the nominal process histogram.
// Missing variation for a particular file/category uses its nominal shape.
// A completely absent nuisance therefore gives zero shift, not a missing process.
TH1D* combineProcessVariation(
    const vector<TFile*>& input,
    const vector<string>& nominalNames,
    const string& process,
    const string& systSuffix,
    const string& outputName,
    double xmin, double xmax,
    size_t& variedCount,
    size_t& fallbackCount)
{
    TH1D* sum = nullptr;
    variedCount = fallbackCount = 0;
    for (TFile* f : input) {
        if (!f || f->IsZombie()) continue;
        for (const string& nominalName : nominalNames) {
            // Only include entries present in nominal selection.
            if (!f->Get(nominalName.c_str())) continue;
            const string variedName = nominalName + "_" + systSuffix;
            TH1D* h = copyHistogram(f, variedName);
            if (h) ++variedCount;
            else {
                h = copyHistogram(f, nominalName);
                ++fallbackCount;
            }
            if (!h) continue;
            prepareSample(h, f, process, nominalName);
            if (!sum) {
                sum = (TH1D*)h->Clone(outputName.c_str());
                sum->SetDirectory(nullptr);
            } else if (compatible(sum, h)) {
                sum->Add(h);
            } else {
                cerr << "WARNING: incompatible bins in " << f->GetName()
                     << ":" << variedName << endl;
            }
            delete h;
        }
    }
    if (sum) {
        if (APPLY_OLD_NORM_FACTORS) {
            if (process == "VV") sum->Scale(1.033462);
            if (process == "ZZ") sum->Scale(1.284495);
        }
        prepareForPlot(sum, xmin, xmax);
    }
    return sum;
}

void StackHist_test() {
    gStyle->SetOptStat(0);
    gSystem->mkdir(OUTPUT_DIR.c_str(),true);
    map<string,vector<string>> files;
    string year = YEAR;
    files = getFileMap(YEAR);
    map<string,vector<TFile*>> open_files;
    for (const auto& kv : files) {
        for (const auto& fname : kv.second) {
            string path = INPUT_DIR + "/hist_" + fname;
            TFile* f = TFile::Open(path.c_str(),"READ");
            if (!f || f->IsZombie()) {
                cerr << "WARNING: cannot open " << path << endl;
                if (f) {f->Close(); delete f;}
                continue;
            }
            open_files[kv.first].push_back(f);
        }
    }

    unsigned plotNumber = 0;
    const vector<string>& plotCategories =
        (SUMMARY_TYPE == "tau_ch") ? CHANNELS : LEP_CHANNELS;

    for (const auto& var : VARIABLES)
    for (const auto& region : REGIONS)
    for (const auto& category : plotCategories)
    for (const auto& syst : SYSTEMATICS) {
        vector<string> names = selectedNames(var, region, category, syst);
        if (names.empty()) continue;

        // tau_ch: h_<var>_<region>_<ch>_<systematic>
        // other : h_<var>_<lepch>_<region>_<systematic>
        string mergedName = "h_" + var + "_" +
            (SUMMARY_TYPE == "tau_ch" ? region + "_" + category
                                       : category + "_" + region) +
            (syst.empty() ? "" : "_" + syst);

        cout << "\nCombining "
             << (SUMMARY_TYPE == "tau_ch" ? "lepton flavors" : "tau channels")
             << " into " << mergedName
             << " (" << names.size() << " categories)" << endl;
        
        double xmin = 0, xmax = 2000;
        if (X_RANGES.count(var)) {
			xmin = X_RANGES.at(var).first;
			xmax = X_RANGES.at(var).second;
		}
		        
        map<string,TH1D*> hist;
        for (const auto& kv : open_files) {
            hist[kv.first] = combineProcess(kv.second,names,kv.first,
                Form("%s_%s",kv.first.c_str(),mergedName.c_str()));
        }
        if (APPLY_OLD_NORM_FACTORS) {
            if (hist["VV"]) hist["VV"]->Scale(1.033462);
            if (hist["ZZ"]) hist["ZZ"]->Scale(1.284495);
        }
        for (auto& kv : hist)
            if (kv.second) prepareForPlot(kv.second, xmin, xmax);

        TH1D* total = nullptr;
        THStack* stack = new THStack(Form("stack_%u",plotNumber),"");
        for (const auto& proc : BKGS) {
            TH1D* h = hist[proc];
            if (!h) continue;
            h->SetFillColor(COLORS.at(proc));
            h->SetLineColor(kBlack);
            stack->Add(h);
            if (!total) {
                total = (TH1D*)h->Clone(Form("total_%u",plotNumber));
                total->SetDirectory(nullptr);
            } else total->Add(h);
        }
        if (!total) {
            cerr << "No backgrounds for " << var << "; skipping\n";
            for (auto& kv:hist) delete kv.second;
            delete stack;
            ++plotNumber;
            continue;
        }
        TH1D* data = hist["data"];
        TH1D* signal = hist["signal"];
        TCanvas* c = new TCanvas(Form("c_%u",plotNumber),"Stack",800,700);
        TPad* pad1 = new TPad(Form("pad1_%u",plotNumber),"",0,0.3,1,1);
        TPad* pad2 = new TPad(Form("pad2_%u",plotNumber),"",0,0,1,0.3);
        pad1->SetBottomMargin(0.01);
		pad2->SetTopMargin(0.01); pad2->SetBottomMargin(0.3);
		pad1->Draw(); pad2->Draw();
        pad1->cd();
        if (LOG_Y) pad1->SetLogy();
        stack->Draw("HIST");
        stack->GetXaxis()->SetRangeUser(xmin, xmax);
	const double binwidth = total->GetXaxis()->GetBinWidth(1);
	stack->GetYaxis()->SetTitle(Form("Events / %.6g GeV", binwidth));
        stack->GetYaxis()->SetTitleOffset(1.2);
        double ymax = std::max(total->GetMaximum(),data ? data->GetMaximum() : 0.);
        if (DRAW_SIGNAL && signal && SIGNAL_SCALE > 0)
            ymax = std::max(ymax, SIGNAL_SCALE*signal->GetMaximum());
        stack->SetMaximum((LOG_Y ? 15. : 1.4) * std::max(ymax,1.));
        if (LOG_Y) stack->SetMinimum(0.1);
        if (data) {
            data->SetMarkerStyle(20); data->SetMarkerSize(0.8);
            data->SetLineColor(kBlack);
            data->Draw("E1 SAME");
        }
        if (DRAW_SIGNAL && signal) {
            signal->Scale(SIGNAL_SCALE);
            signal->SetFillStyle(0); signal->SetLineColor(kRed);
            signal->SetLineWidth(3); signal->Draw("HIST SAME");
        }
        DrawCMSLabel();
        string description = makeHistString(category)+" channel";
        if (!syst.empty()) description += " / " + syst;
        PlotDescription(const_cast<char*>(description.c_str()));
        TLegend* leg = new TLegend(0.7, 0.6, 0.9, 0.88);
        leg->SetBorderSize(0); //leg->SetTextSize(0.027);
        for (const auto& proc : BKGS)
            if (hist[proc]) leg->AddEntry(hist[proc],proc.c_str(),"f");
        if (data) leg->AddEntry(data,"Data","lep");
        if (DRAW_SIGNAL && signal)
            leg->AddEntry(signal,Form("Signal #times %.0f",SIGNAL_SCALE),"l");
        leg->Draw();

        pad2->cd();
        TH1D* ratio = (TH1D*)total->Clone(Form("ratio_%u",plotNumber));
        ratio->SetDirectory(nullptr); ratio->Reset();
        ratio->GetXaxis()->SetRangeUser(xmin, xmax);
        ratio->SetTitle("");
        ratio->GetYaxis()->SetTitle("Data / Background");
        ratio->GetXaxis()->SetTitle(axisTitle(var).c_str());
        ratio->GetYaxis()->SetNdivisions(505);
        ratio->GetYaxis()->SetTitleSize(0.09);
        ratio->GetYaxis()->SetTitleOffset(0.4);
        ratio->GetYaxis()->SetLabelSize(0.07);
        ratio->GetXaxis()->SetTitleSize(0.1);
        ratio->GetXaxis()->SetLabelSize(0.1);
        ratio->SetMinimum(0); ratio->SetMaximum(2);
        ratio->SetMarkerStyle(20);
        if (data) {
            for (int b=1;b<=ratio->GetNbinsX();++b) {
                double mc = total->GetBinContent(b);
                if (mc <= 0) continue;
                ratio->SetBinContent(b,data->GetBinContent(b)/mc);
                ratio->SetBinError(b,data->GetBinError(b)/mc);
            }
        }
        ratio->Draw(data ? "E1" : "AXIS");
        TGraphAsymmErrors* systBand = nullptr;
        if (DRAW_SYST_BAND && syst.empty()) {
            map<string, pair<TH1D*, TH1D*>> systTotals;
            for (const string& nuisance : fullSystList) {
                TH1D* totalUp = (TH1D*)total->Clone(Form("up_%s_%u", nuisance.c_str(), plotNumber));
                TH1D* totalDown = (TH1D*)total->Clone(Form("down_%s_%u", nuisance.c_str(), plotNumber));
                totalUp->SetDirectory(nullptr); totalDown->SetDirectory(nullptr);
                totalUp->Reset(); totalDown->Reset();
                size_t upFound = 0, downFound = 0, upFallback = 0, downFallback = 0;
                for (const string& process : BKGS) {
                    if (!hist[process]) continue;
                    auto it = open_files.find(process);
                    if (it == open_files.end()) continue;
                    size_t nf = 0, nb = 0;
                    TH1D* hUp = combineProcessVariation(it->second, names, process,
                        nuisance + "Up", Form("%s_%s_up_%u", process.c_str(), nuisance.c_str(), plotNumber),
                        xmin, xmax, nf, nb);
                    upFound += nf; upFallback += nb;
                    nf = nb = 0;
                    TH1D* hDown = combineProcessVariation(it->second, names, process,
                        nuisance + "Down", Form("%s_%s_down_%u", process.c_str(), nuisance.c_str(), plotNumber),
                        xmin, xmax, nf, nb);
                    downFound += nf; downFallback += nb;
                    if (hUp && compatible(totalUp, hUp)) totalUp->Add(hUp);
                    else if (hUp) cerr << "WARNING: Up binning mismatch for " << process << endl;
                    if (hDown && compatible(totalDown, hDown)) totalDown->Add(hDown);
                    else if (hDown) cerr << "WARNING: Down binning mismatch for " << process << endl;
                    delete hUp; delete hDown;
                }
                cout << "  nuisance " << nuisance << ": Up=" << upFound
                     << " Down=" << downFound << " nominal fallbacks="
                     << upFallback << "/" << downFallback << endl;
                if (upFound == 0 && downFound == 0) {
                    delete totalUp; delete totalDown;
                    continue;
                }
                systTotals[nuisance] = {totalUp, totalDown};
            }
            systBand = MakeRatioUncertaintyBand(total, systTotals);
            systBand->Draw("E2 SAME");
            for (auto& kv : systTotals) {
                delete kv.second.first;
                delete kv.second.second;
            }
        } else {
            // For nonnominal plots show statistical/legacy normalization errors only.
            systBand = MakeRatioUncertaintyBand(total, {});
            systBand->Draw("E2 SAME");
        }
        if (data) ratio->Draw("E1 SAME");
      
        // Draw lines for reference
		TLine *line1 = new TLine(xmin, 1, xmax, 1);
		TLine *line2 = new TLine(xmin, 0.5, xmax, 0.5);
		TLine *line3 = new TLine(xmin, 1.5, xmax, 1.5);
		line1->SetLineStyle(2);line2->SetLineStyle(2);line3->SetLineStyle(2);
		line1->Draw(); line2->Draw(); line3->Draw();
		
        c->cd();
        string base = OUTPUT_DIR + "/h_" + mergedName.substr(2);
	if (year!="Run2") base+="_"+year;
        c->SaveAs((base+".pdf").c_str());
        c->SaveAs((base+".png").c_str());
        // Cleanup after canvas has finished rendering/saving.
        delete c;
        delete ratio; delete systBand; delete total;
        delete stack;
        for (auto& kv:hist) delete kv.second;
        ++plotNumber;
    }
    for (auto& kv : open_files)
        for (TFile* f : kv.second) {f->Close(); delete f;}
}
