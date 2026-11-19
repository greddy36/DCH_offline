#include <TFile.h>
#include <TKey.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TString.h>

#include <iostream>

void plot_metvsdmll(const char* filename = "../run2_noFR_metphi_zpt_recoil_roccor_toppt_chargeflip_SR/2018/masstree_HppM1000_2018.root");
{
    TFile file(filename, "READ");
    if (file.IsZombie()) {
        std::cerr << "Cannot open " << filename << '\n';
        return;
    }

    gStyle->SetOptStat(0);
    gStyle->SetPalette(kBird);

	const char* CHANNELS[] = {"0tau", "1tau", "2tau", "3tau","3lep0tau","3lep1tau","3lep2tau"};
	
    for(auto ch : CHANNELS){

        TTree* tree = nullptr;
        file.GetObject(ch, tree);
        if (!tree) continue;

        TString channel = tree->GetName();

        if (!tree->GetBranch("met") ||
            !tree->GetBranch("mll1") ||
            !tree->GetBranch("mll2")) {
            std::cerr << "Skipping " << channel
                      << ": missing met, mll1, or mll2 branch\n";
            continue;
        }

        TCanvas canvas("canvas", "", 900, 750);
        canvas.SetRightMargin(0.16);
        canvas.SetLeftMargin(0.13);

        // ROOT Draw syntax is "y:x".
        // Automatic axis ranges; 80 bins along each axis.
        tree->Draw(
            "(mll1-mll2):met>>h_metvsdmll(80,0,0,80,0,0)",
            "",
            "COLZ"
        );

        auto* hist = dynamic_cast<TH2D*>(
            file.Get("h_metvsdmll")
        );

        if (hist) {
            hist->SetTitle(
                Form("%s;MET [GeV];m_{ll1} - m_{ll2} [GeV];Events",
                     channel.Data())
            );

            canvas.SaveAs(
                Form("%s_metvsdmll.png", channel.Data())
            );

            delete hist;
        }
    }
}