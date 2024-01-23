#include "TMath.h"
#include <cmath>
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TStyle.h"

void DCH() {
    TCanvas *can = new TCanvas("can", "can", 700, 500);
    gStyle->SetOptStat(0);

    TFile *ifile_sig1 = new TFile("HppMM500_001.root", "READ");
    TFile *ifile_bkg1 = new TFile("ZZTo4L_2018.root", "READ");
    TFile *ifile_bkg2 = new TFile("ZZTo2Q2L_2018.root", "READ");

    TTree *tree_sig1 = (TTree *)ifile_sig1->Get("Events");
    tree_sig1->SetLineColor(kRed);
    TTree *tree_bkg1 = (TTree *)ifile_bkg1->Get("Events");
    tree_bkg1->SetLineColor(kBlue);
    TTree *tree_bkg2 = (TTree *)ifile_bkg2->Get("Events");
    tree_bkg2->SetLineColor(kGreen);

    const char *condition = "1"; //"pt_1+pt_2 > 210 && pt_3+pt_4 > 190";//"pt_1 >120 && pt_2>90 && pt_3 > 100 && pt_4>90";//"mll >200 && mll2>160";

    const char *var[] = {"mll", "mll2", "pt_1", "pt_2", "pt_3", "pt_4", "eta_1", "eta_2", "eta_3", "eta_4", "phi_1", "phi_2", "phi_3", "phi_4", "cat", "d0_1", "d0_2", "d0_3", "d0_4", "dZ_1", "dZ_2", "dZ_3", "dZ_4", "met", "metphi",""};
    int numVars = sizeof(var) / sizeof(var[0]); // Correct way to get the number of elements in var

    for (int i = 0; i < numVars-1; i++) {
        TH1F *hist_sig1 = new TH1F("hist_sig1", "DCH M500", 100, tree_sig1->GetMinimum(var[i]), tree_sig1->GetMaximum(var[i]));
        TH1F *hist_bkg1 = new TH1F("hist_bkg1", "ZZto4L", 100, tree_bkg1->GetMinimum(var[i]), tree_bkg1->GetMaximum(var[i]));
        TH1F *hist_bkg2 = new TH1F("hist_bkg2", "ZZto2Q2L", 100, tree_bkg2->GetMinimum(var[i]), tree_bkg2->GetMaximum(var[i]));

        tree_sig1->Draw(Form("%s>>hist_sig1", var[i]), condition, "norm");
        tree_bkg1->Draw(Form("%s>>hist_bkg1", var[i]), condition, "norm");
        tree_bkg2->Draw(Form("%s>>hist_bkg2", var[i]), condition, "norm");

        hist_sig1->Scale(1.0*59.6*1000/176000);
        hist_bkg1->Scale(1.325*59.6*1000/97570000);
        hist_bkg2->Scale(3.22*59.6*1000/26962069);

        hist_sig1->SetLineColor(kRed);
        hist_bkg1->SetLineColor(kBlue);
        hist_bkg2->SetLineColor(kGreen);

        hist_sig1->Draw("hist");
        hist_bkg1->Draw("same hist");
        hist_bkg2->Draw("same hist");

        TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
        legend->AddEntry(hist_sig1, "DCH M500", "l");
        legend->AddEntry(hist_bkg1, "ZZto4L", "l");
        legend->AddEntry(hist_bkg2, "ZZto2Q2L", "l");
        legend->Draw();

        std::string title = "";
        title.append(var[i]);
        title.append("_2.png");
        can->SaveAs(const_cast<char *>(title.c_str()));
    }
    cout << "Signal : " << tree_sig1->GetEntries(condition) << endl;
    cout << "ZZto4L : " << tree_bkg1->GetEntries(condition) << endl;
    cout << "ZZto2Q2L : " << tree_bkg2->GetEntries(condition) << endl;
}
