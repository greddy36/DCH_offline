#include <TFile.h>
#include <TH1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TKey.h>
#include <TClass.h>
#include <TROOT.h>
#include <TLatex.h>

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;


// ============================================================
// Configuration
// ============================================================

const char* INPUT_FILE = "combined_hist_mDCH1.root";

const char* OUTPUT_PNG  = "stack_lep3tau0_mDCH1.png";
const char* OUTPUT_PDF  = "stack.pdf";

bool LOG_Y = false;


// ============================================================
// Background colors
// ============================================================

map<string, int> fill_colors = {
    {"DY",     7},
    {"WZ",     8},
    {"VV",     8},
    {"VVV",    6},
    {"ttW",    4},
    {"ttZ",    2},
    {"WJ",     9},
    {"QCD",   11},
    {"ZZ",     5},
    {"ST",    30},
    {"TTbar", 46},
    {"other", 28},
    {"ZH",    29},
    {"data",   1}
};


// ============================================================
// Get process name from histogram name
//
// Example:
//
// h_mDCH1_lep3tau0_DY       -> DY
// h_mDCH1_lep3tau0_ZZ       -> ZZ
// h_mDCH1_lep3tau0_TTbar    -> TTbar
// h_mDCH1_lep3tau0_M500     -> M500
//
// ============================================================

string GetProcessName(TString histName)
{
    string name = histName.Data();

    // Find final underscore
    size_t pos = name.rfind("_");

    if (pos == string::npos)
        return name;

    return name.substr(pos + 1);
}


// ============================================================
// Check if histogram is a signal
//
// Anything ending in M<number> is treated as signal.
//
// M500
// M600
// M1000
// M1500
//
// ============================================================

bool IsSignal(string process)
{
	return process.find("M1000")!=string::npos;
}


// ============================================================
// Main
// ============================================================

void stack_templates()
{
    // --------------------------------------------------------
    // Open ROOT file
    // --------------------------------------------------------

    TFile* file = TFile::Open(INPUT_FILE);

    if (!file || file->IsZombie()){
        cout << "ERROR: Cannot open "<< INPUT_FILE << endl;
        return;
    }
    cout << "Opened "<< INPUT_FILE<< endl;


    // --------------------------------------------------------
    // Containers
    // --------------------------------------------------------

    vector<TH1*> backgrounds;
    vector<TH1*> signals;


    // --------------------------------------------------------
    // Loop through ROOT file
    // --------------------------------------------------------

    TIter next(file->GetListOfKeys());

    TKey* key;


    while ((key = (TKey*)next()))
    {
        TClass* cl = gROOT->GetClass(key->GetClassName());
        if (!cl) continue;
        if (!cl->InheritsFrom("TH1")) continue;
        TH1* h = (TH1*)key->ReadObj();
        if (!h) continue;

        TString name = h->GetName();
        if (name.Contains("Up") or name.Contains("Down")) continue;
        if (!name.Contains("_lep3tau0")) continue;

        // ----------------------------------------------------
        // Process name
        // ----------------------------------------------------

        string process = GetProcessName(name);

        cout << "Found: "<< name<< "  -->  "<< process << endl;

        // ----------------------------------------------------
        // Ignore data
        // ----------------------------------------------------

        if (process == "data") continue;

        if (name.Contains("data_obs")) continue;

        // ----------------------------------------------------
        // Signal
        // ----------------------------------------------------

        if (IsSignal(process)){
            signals.push_back(h);
        }

        // ----------------------------------------------------
        // Background
        // ----------------------------------------------------

        else if (fill_colors.find(process) != fill_colors.end()){
            backgrounds.push_back(h);
        }

        // ----------------------------------------------------
        // Unknown process
        // ----------------------------------------------------

        else{
            cout << "WARNING: Unknown process "<< process<< " -- skipping"<< endl;
        }
    }
    // ========================================================
    // Print summary
    // ========================================================

    cout << endl;
    cout << "Background histograms: "<< backgrounds.size()<< endl;
    cout << "Signal histograms: "<< signals.size()<< endl;
    cout << endl;

    // ========================================================
    // Background stack
    // ========================================================

    THStack* stack =new THStack("stack","");

    // --------------------------------------------------------
    // Add backgrounds
    // --------------------------------------------------------

    for (TH1* h : backgrounds){
        string process =GetProcessName(h->GetName());
        TH1* hcopy =(TH1*)h->Clone(Form("%s_stack",h->GetName()));
        hcopy->SetDirectory(0);

        // ----------------------------------------------------
        // Your color map
        // ----------------------------------------------------

        int color = fill_colors[process];

        hcopy->SetFillColor(color);
        hcopy->SetLineColor(kBlack);
        hcopy->SetLineWidth(1);

        stack->Add(hcopy);
    }


    // ========================================================
    // Canvas
    // ========================================================

    TCanvas* c1 = new TCanvas("c1","Background + Signal",900,700);

    c1->SetLeftMargin(0.12);
    c1->SetRightMargin(0.05);
    c1->SetBottomMargin(0.12);
    c1->SetTopMargin(0.08);

    if (LOG_Y) c1->SetLogy();

    // ========================================================
    // Draw background stack
    // ========================================================

    if (backgrounds.size() > 0){
        stack->Draw("HIST");
        stack->GetXaxis()->SetTitle(backgrounds[0]->GetXaxis()->GetTitle());
        stack->GetYaxis()->SetTitle("Events");
        stack->GetXaxis()->SetTitleSize(0.045);
        stack->GetYaxis()->SetTitleSize(0.045);
        stack->GetXaxis()->SetLabelSize(0.040);
        stack->GetYaxis()->SetLabelSize(0.040);
    }

    // ========================================================
    // Signal colors
    // ========================================================

    vector<int> signal_colors = {kRed};


    // ========================================================
    // Draw signals as dotted lines
    // ========================================================

    for (unsigned int i = 0;i < signals.size();i++){
        TH1* h =signals[i];
        TH1* hcopy =(TH1*)h->Clone(Form("%s_signal",h->GetName()));
        hcopy->SetDirectory(0);
        hcopy->SetLineColor(signal_colors[i % signal_colors.size()]);
        hcopy->SetLineWidth(3);
        // ----------------------------------------------------
        // Dotted line
        // ----------------------------------------------------
        hcopy->SetLineStyle(3);
        hcopy->SetFillStyle(0);
		hcopy->Scale(100);
        hcopy->Draw("HIST SAME");
    }

    // ========================================================
    // Legend
    // ========================================================

    TLegend* leg = new TLegend(0.65,0.50,0.90,0.88);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetTextFont(42);
    leg->SetTextSize(0.030);

    // --------------------------------------------------------
    // Background legend
    // --------------------------------------------------------

    for (TH1* h : backgrounds){
        leg->AddEntry(h,GetProcessName(h->GetName()).c_str(),"f");
    }

    // --------------------------------------------------------
    // Signal legend
    // --------------------------------------------------------
    for (TH1* h : signals){
        leg->AddEntry(h,GetProcessName(h->GetName()).c_str(),"l");
    }
    
    leg->Draw();
    // ========================================================
    // CMS label
    // ========================================================
    TLatex tex;
    tex.SetNDC();
    tex.SetTextFont(62);
    tex.SetTextSize(0.055);
    tex.DrawLatex(
        0.13,
        0.92,
        "CMS"
    );

    tex.SetTextFont(52);
    tex.SetTextSize(0.045);

    tex.DrawLatex(0.22,0.92,"Preliminary");

    tex.SetTextFont(42);
    tex.SetTextSize(0.040);

    tex.DrawLatex(0.72,0.92,"138 fb^{-1} (13 TeV)");
    // ========================================================
    // Grid
    // ========================================================
    c1->SetGridx(false);
    c1->SetGridy(true);
    // ========================================================
    // Redraw axes
    // ========================================================
    gPad->RedrawAxis();
    // =======================================================
    // Save
    // ========================================================
    c1->SaveAs(OUTPUT_PNG);
    c1->SaveAs(OUTPUT_PDF);

    cout << endl;
    cout << "Saved "<< OUTPUT_PNG<< endl;
    cout << "Saved "<< OUTPUT_PDF<< endl;
}