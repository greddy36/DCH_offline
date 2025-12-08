#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>


void tmp() {
	TFile *ifile = TFile::Open("hist_MY/skim_500_2018.root");
	TH2D* hxy1 = new TH2D("hxy1","mH_{1} vs. d#phi_{l1l3}", 50,0,5,100,0,1500);
	TH2D* hxy2 = new TH2D("hxy1","mH_{2} vs. d#phi_{l1l3}", 50,0,5,100,0,1500);
	std::string root_dir[] = {"0tau/","1tau/","2tau/","3tau/"};
	TTree *tree = (TTree*)ifile->Get("2tau/Events");
	Double_t dRll1, dRll2, mH1, mH2;
	tree->SetBranchAddress("dR2",&dRll1);
	tree->SetBranchAddress("dR2",&dRll2);
	tree->SetBranchAddress("mll1",&mH1);
	tree->SetBranchAddress("mll2",&mH2);
	for (int i =0; i < tree->GetEntries(); i++){
		tree->GetEntry(i);
		hxy1->Fill(dRll2,mH1);
		hxy2->Fill(dRll2,mH2);
	}
	TCanvas *c1 = new TCanvas("c1","",900,400);
    c1->Divide(2,1);
    c1->cd(1); hxy1->Draw("COLZ");
    c1->cd(2); hxy2->Draw("COLZ");
    c1->SaveAs("mHvsDphi_opp.png");
}