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
#include "include/cms_plots.h"
using namespace std;

// ============================================================
// Configuration
// ============================================================

const char* INPUT_FILE = "combined_hist_LTmet.root";

bool LOG_Y = false;

// Channels to plot
vector<string> CHANNELS = {
    //"tau0",
    //"tau1",
    //"tau2",
    //"tau3",
    "lep3tau0",
    "lep3tau1",
    "lep3tau2"
};

// Variables to plot
vector<string> VARIABLES = {
	"mll1",
	"LTmet",
    //"mH1",
    //"mH1",
    //"mH2",
};

// ============================================================
// Background colors
// ============================================================

map<string, int> fill_colors = {
    {"DY",     7},
    {"VV",     8},
    {"VVV",    6},
    {"ttV",    4},
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
// h_mll1_tau0_DY       -> DY
// h_mll1_tau0_ZZ       -> ZZ
// h_mll1_tau0_TTbar    -> TTbar
// h_mll1_tau0_M500    -> M500
//
// ============================================================

string GetProcessName(TString histName)
{
    string name = histName.Data();

    size_t pos = name.rfind("_");

    if (pos == string::npos)
        return name;

    return name.substr(pos + 1);
}


// ============================================================
// Identify signal
// ============================================================

bool IsSignal(string process)
{	//return process.find("M500")  != string::npos;
    return process.find("M500")  != string::npos ||
           //process.find("M600")  != string::npos ||
           //process.find("M700")  != string::npos ||
           //process.find("M800") != string::npos ||
           //process.find("M900")  != string::npos ||
           process.find("M1500")  != string::npos; //||
           //process.find("M1100") != string::npos ||
           //process.find("M1200")  != string::npos ||
           //process.find("M1300") != string::npos ||
           //process.find("M1400") != string::npos;*/
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
        cout << "ERROR: Cannot open " << INPUT_FILE << endl;
        return;
    }

    cout << "Opened " << INPUT_FILE << endl;


    // ========================================================
    // Loop over CHANNELS
    // ========================================================
	for (const string& var : VARIABLES){
		for (const string& channel : CHANNELS){
		    cout << endl;
		    cout << "==================================================" << endl;
		    cout << "Processing channel: " << channel << endl;
		    cout << "==================================================" << endl;

		    // ----------------------------------------------------
		    // Containers
		    // ----------------------------------------------------

		    vector<TH1*> backgrounds;
		    vector<TH1*> signals;

		    // ----------------------------------------------------
		    // Loop through ROOT file
		    // ----------------------------------------------------

		    TIter next(file->GetListOfKeys());

		    TKey* key;

		    while ((key = (TKey*)next()))
		    {
		        TClass* cl = gROOT->GetClass(key->GetClassName());

		        if (!cl)
		            continue;

		        if (!cl->InheritsFrom("TH1"))
		            continue;

		        TH1* h = (TH1*)key->ReadObj();

		        if (!h)
		            continue;


		        TString name = h->GetName();


		        // ------------------------------------------------
		        // Select mll1 histograms
		        // ------------------------------------------------

		        if (!name.Contains(var)) continue;
				if (name.Contains("flat")) continue;
		        if (name.Contains("Up") || name.Contains("Down"))
		            continue;


		        // ------------------------------------------------
		        // Select current channel
		        // ------------------------------------------------

		        if (!name.Contains(Form("_%s_", channel.c_str())))
		            continue;


		        // ------------------------------------------------
		        // Process name
		        // ------------------------------------------------

		        string process = GetProcessName(name);

		        cout << "Found: " << name << "  -->  " << process << endl;

		        // ------------------------------------------------
		        // Ignore data
		        // ------------------------------------------------

		        if (process == "data") continue;
		        if (name.Contains("data_obs")) continue;

		        // ------------------------------------------------
		        // Signal
		        // ------------------------------------------------

		        if (IsSignal(process)){
		            signals.push_back(h);
		        }


		        // ------------------------------------------------
		        // Background
		        // ------------------------------------------------

		        else if (fill_colors.find(process) != fill_colors.end()){
		            backgrounds.push_back(h);
		        }

		    }


		    // ====================================================
		    // Print summary
		    // ====================================================

		    cout << endl;

		    cout << "Channel: " << channel << endl;
		    cout << "Background histograms: "
		         << backgrounds.size() << endl;

		    cout << "Signal histograms: "
		         << signals.size() << endl;

		    cout << endl;


		    // ----------------------------------------------------
		    // Skip if nothing found
		    // ----------------------------------------------------

		    if (backgrounds.empty() && signals.empty())
		    {
		        cout << "WARNING: No histograms found for "
		             << channel << endl;

		        continue;
		    }


		    // ====================================================
		    // Legend
		    // ====================================================

		    TLegend* leg = new TLegend(0.70, 0.60, 0.90, 0.88);

		    leg->SetBorderSize(0);


		    // ====================================================
		    // Background stack
		    // ====================================================

		    THStack* stack = new THStack(Form("stack_%s", channel.c_str()), "");

		    // ----------------------------------------------------
		    // Add backgrounds
		    // ----------------------------------------------------
			double bkg_integral = 0;
		    for (TH1* h : backgrounds)
		    {
		        string process = GetProcessName(h->GetName());

		        TH1* hcopy = (TH1*)h->Clone(Form("%s_stack_%s",h->GetName(),channel.c_str()));

		        hcopy->SetDirectory(0);

		        // ------------------------------------------------
		        // Color
		        // ------------------------------------------------

		        int color = fill_colors[process];

		        hcopy->SetFillColor(color);
		        hcopy->SetLineColor(kBlack);
		        hcopy->SetLineWidth(1);


		        // ------------------------------------------------
		        // Add to stack
		        // ------------------------------------------------

		        stack->Add(hcopy);
				bkg_integral += hcopy->Integral();
		        // ------------------------------------------------
		        // Legend
		        // ------------------------------------------------

		        leg->AddEntry(hcopy,process.c_str(),"f");
		        
		    }


		    // ====================================================
		    // Canvas
		    // ====================================================

		    TCanvas* c1 = new TCanvas(
		        Form("c1_%s", channel.c_str()),
		        Form("Background + Signal - %s", channel.c_str()),
		        800, 700 );

		    c1->SetLeftMargin(0.12);
		    c1->SetRightMargin(0.05);
		    c1->SetBottomMargin(0.12);
		    c1->SetTopMargin(0.08);


		    if (LOG_Y) c1->SetLogy();

		    // ====================================================
		    // Draw background stack
		    // ====================================================

		    if (!backgrounds.empty())
		    {
		        stack->Draw("HIST");

		        //stack->SetMaximum( 1.1 * stack->GetMaximum() );

		        if (var=="mll1") stack->GetXaxis()->SetLimits(0, 2000);
		        else if (var=="LTmet") stack->GetXaxis()->SetLimits(0, 5000);
		        
		        string x_title = "Invariant mass of ";
				if (var.find("2") != string::npos) x_title += "sub-";
		        x_title += "leading SS pair ";
		        if (var.find("DCH") != string::npos or var.find("mH") != string::npos ) x_title += "+ #nu's ";
		        x_title += "[GeV]";
		        stack->GetXaxis()->SetTitle(x_title.c_str());
		        if (var.find("LTmet") != string::npos) stack->GetXaxis()->SetTitle("L_{T}+E_{T}^{miss} [GeV]");
		        
		        if (var=="mll1") stack->GetYaxis()->SetTitle("Events / 40 GeV");
				else if (var=="LTmet") stack->GetYaxis()->SetTitle("Events / 100 GeV");
				
		        stack->GetXaxis()->SetTitleSize(0.040);
		        stack->GetYaxis()->SetTitleSize(0.040);

		        stack->GetXaxis()->SetLabelSize(0.030);
		        stack->GetYaxis()->SetLabelSize(0.030);
		    }


		    // ====================================================
		    // Draw signals
		    // ====================================================

		    for (unsigned int i = 0; i < signals.size(); i++){
		        TH1* h = signals[i];

		        TH1* hcopy = (TH1*)h->Clone(Form("%s_signal_%s",h->GetName(), channel.c_str()));

		        hcopy->SetDirectory(0);
		        
		        if (var.find("mll") != string::npos) {
		        	hcopy->SetLineColor(kBlue); 
		        	hcopy->SetFillColor(kBlue);
		        }
		        else {
		        	hcopy->SetLineColor(kRed); 
		        	hcopy->SetFillColor(kRed);
		        }
		        hcopy->SetLineWidth(2);
		        hcopy->SetFillStyle(3003 + i);


		        // ------------------------------------------------
		        // Scale signal to stack integral
		        // ------------------------------------------------
		        if (!backgrounds.empty() && hcopy->GetMaximum() > 0){
		            //hcopy->Scale( bkg_integral / hcopy->Integral());
		        }

		        hcopy->Draw("HIST SAME");

		        if (i==0) leg->AddEntry(hcopy,"H^{#pm#pm} (500 GeV)","f");
		        else if (i==1) leg->AddEntry(hcopy,"H^{#pm#pm} (1500 GeV)","f");
		        
		        double padmax = std::max(stack->GetMaximum(), hcopy->GetMaximum());
		        stack->SetMaximum( 1.1 * padmax);
		    }

			
		    // ====================================================
		    // Legend
		    // ====================================================

		    leg->Draw();


		    // ====================================================
		    // CMS label
		    // ====================================================

		    TLatex tex;

		    tex.SetNDC();

		    tex.SetTextFont(62);
		    tex.SetTextSize(0.055);

		    DrawCMSLabel();
			string description = makeHistString(channel);
		    PlotDescription(const_cast<char*>(description.c_str()));
		    // ====================================================
		    // Redraw axes
		    // ====================================================

		    gPad->RedrawAxis();


		    // ====================================================
		    // Output filenames
		    // ====================================================

		    string output_png =
		        "stack_" + channel + "_" + var +".png";

		    string output_pdf =
		        "stack_" + channel + "_" + var +".pdf";


		    // ====================================================
		    // Save
		    // ====================================================

		    c1->SaveAs(output_png.c_str());
		    c1->SaveAs(output_pdf.c_str());


		    cout << "Saved " << output_png << endl;
		    cout << "Saved " << output_pdf << endl;


		    // ====================================================
		    // Cleanup
		    // ====================================================

		    delete leg;
		    delete stack;
		    delete c1;
		}//channel loop
	}//variable loop

    // ========================================================
    // Close file
    // ========================================================

    file->Close();

    cout << endl;
    cout << "Finished all CHANNELS." << endl;
}