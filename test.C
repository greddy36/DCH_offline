
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>

void test() {
	TFile *ifile_sig = new TFile("hist_test_nopair/WW_2018.root","READ");               
	TFile *ifile_DY1 = new TFile("hist_test_nopair/DYJetsToLLM10to50_2018.root","READ");     
	TFile *ifile_DY2 = new TFile("hist_test_nopair/DYJetsToLLM50_2018.root","READ"); 
		    
	//TFile *ifile_VV1 = new TFile("hist_test_nopair/WGToLNuG_2018.root","READ");
	TFile *ifile_VV2 = new TFile("hist_test_nopair/WW_2018.root","READ");
	TFile *ifile_VV3 = new TFile("hist_test_nopair/WWTo2L2Nu_2018.root","READ");
	//TFile *ifile_VV4 = new TFile("hist_test_nopair/WZ_2018.root","READ");
	TFile *ifile_VV5 = new TFile("hist_test_nopair/WZTo2Q2L_2018.root","READ");
	TFile *ifile_VV6 = new TFile("hist_test_nopair/WZTo3LNu_2018.root","READ");

	TFile *ifile_VVV1 = new TFile("hist_test_nopair/WWW_2018.root","READ");
	TFile *ifile_VVV2 = new TFile("hist_test_nopair/WZZ_2018.root","READ");
	TFile *ifile_VVV3 = new TFile("hist_test_nopair/ZZZ_2018.root","READ");

	TFile *ifile_ttV1 = new TFile("hist_test_nopair/ttWJets_2018.root","READ");
	TFile *ifile_ttV2 = new TFile("hist_test_nopair/ttZJets_2018.root","READ");
	
	TFile *ifile_WJ1 = new TFile("hist_test_nopair/WJetsToLNu_NLO_2018.root","READ");
	TFile *ifile_WJ2 = new TFile("hist_test_nopair/WJetsToLNu_HT-70To100_2018.root","READ");
	TFile *ifile_WJ3 = new TFile("hist_test_nopair/WJetsToLNu_HT-100To200_2018.root","READ");
	TFile *ifile_WJ4 = new TFile("hist_test_nopair/WJetsToLNu_HT-200To400_2018.root","READ");
	TFile *ifile_WJ5 = new TFile("hist_test_nopair/WJetsToLNu_HT-400To600_2018.root","READ");
	TFile *ifile_WJ6 = new TFile("hist_test_nopair/WJetsToLNu_HT-600To800_2018.root","READ");
	TFile *ifile_WJ7 = new TFile("hist_test_nopair/WJetsToLNu_HT-800To1200_2018.root","READ");
	//TFile *ifile_WJ8 = new TFile("hist_test_nopair/WJetsToLNu_HT-1200To2500_2018.root","READ");
	//TFile *ifile_WJ9 = new TFile("hist_test_nopair/WJetsToLNu_HT-2500ToInf_2018.root","READ");
	
	TFile *ifile_ZZ1 = new TFile("hist_test_nopair/ZZTo2L2Nu_2018.root","READ");
	TFile *ifile_ZZ2 = new TFile("hist_test_nopair/ZZTo2Q2L_2018.root","READ");
	TFile *ifile_ZZ3 = new TFile("hist_test_nopair/ZZTo4L_2018.root","READ");

	TFile *ifile_ST1 = new TFile("hist_test_nopair/ST_s-channel_2018.root","READ");          
	TFile *ifile_ST2 = new TFile("hist_test_nopair/ST_t-channel_antitop_2018.root","READ");  
	TFile *ifile_ST3 = new TFile("hist_test_nopair/ST_t-channel_top_2018.root","READ");  
	TFile *ifile_ST4 = new TFile("hist_test_nopair/ST_tW_antitop_2018.root","READ");  
	TFile *ifile_ST5 = new TFile("hist_test_nopair/ST_tW_top_2018.root","READ");            

	//TFile *ifile_ttH1 = new TFile("hist_test_nopair/ttHTo2L2Nu_2018.root","READ");
	//TFile *ifile_ttH2 = new TFile("hist_test_nopair/ttHToEE_2018.root","READ");
	//TFile *ifile_ttH3 = new TFile("hist_test_nopair/ttHToMuMu_2018.root","READ");
	TFile *ifile_ttH4 = new TFile("hist_test_nopair/ttHToTauTau_2018.root","READ");
	
	TFile *ifile_TTbar1 = new TFile("hist_test_nopair/TTTo2L2Nu_2018.root","READ");
	TFile *ifile_TTbar2 = new TFile("hist_test_nopair/TTToSemiLeptonic_2018.root","READ");
	TFile *ifile_TTbar3 = new TFile("hist_test_nopair/TTToHadronic_2018.root","READ");
	
	TFile *ifile_ZH1 = new TFile("hist_test_nopair/ZHToMuMu_2018.root","READ");
	//TFile *ifile_ZH2 = new TFile("hist_test_nopair/ZHToTauTau_2018.root","READ");
	TFile *ifile_ZH3 = new TFile("hist_test_nopair/GluGluZH_2018.root","READ");
	
	TFile *ifile_D1 = new TFile("hist_test_nopair/EGamma_2018.root","READ");
	//TFile *ifile_D2 = new TFile("hist_test_nopair/DoubleMuon_2018.root","READ");
	//TFile *ifile_D3 = new TFile("hist_test_nopair/Tau_2018.root","READ");
	//TFile *ifile_D4 = new TFile("hist_test_nopair/MuonEG_2018.root","READ");
	TFile *ifile_D5 = new TFile("hist_test_nopair/SingleMuon_2018.root","READ");

	const char *hist_list[] = { 
"h_metv11","h_metv1","h_metv2","h_metv14","h_metv13","h_metv3","h_metv4","h_metv15",

/*"h_metv5","h_metv6","h_metv7","h_metv9","h_metv10",*/
	};
	
	TCanvas* canvas = new TCanvas("canvas", "Stacked histograms", 800, 700);//600);
	gStyle->SetOptStat(0);	
	int num = sizeof(hist_list)/sizeof(hist_list[0]);
	
	TH1F* h_summary_DY = new TH1F("h_summary_DY", "Channel Yields;;Yield", num, 0.5, num + 0.5);
	TH1F* h_summary_VV = new TH1F("h_summary_VV", " Yields;;Yield", num, 0.5, num + 0.5);
	TH1F* h_summary_VVV = new TH1F("h_summary_VVV", " Yields;;Yield", num, 0.5, num + 0.5);
	TH1F* h_summary_ttV = new TH1F("h_summary_ttV", " Yields;;Yield", num, 0.5, num + 0.5);
	TH1F* h_summary_WJ = new TH1F("h_summary_WJ", " Yields;;Yield", num, 0.5, num + 0.5);
	TH1F* h_summary_ZZ = new TH1F("h_summary_ZZ", " Yields;;Yield", num, 0.5, num + 0.5);
	TH1F* h_summary_ST = new TH1F("h_summary_ST", " Yields;;Yield", num, 0.5, num + 0.5);
	TH1F* h_summary_TTbar = new TH1F("h_summary_TTbar", " Yields;;Yield", num, 0.5, num + 0.5);
	TH1F* h_summary_other = new TH1F("h_summary_other", " Yields;;Yield", num, 0.5, num + 0.5);
	TH1F* h_summary_data = new TH1F("h_summary_DY", " Yields;;Yield", num, 0.5, num + 0.5);
	// make changes to take in xs from a csv file
	for(int i = 0; i < num; i++){
		TH1D *h_DY1 = (TH1D*)ifile_DY1->Get(hist_list[i]);
		TH1D *h_DY2 = (TH1D*)ifile_DY2->Get(hist_list[i]);
		
		TH1D *h_VV2 = (TH1D*)ifile_VV2->Get(hist_list[i]);
		TH1D *h_VV3 = (TH1D*)ifile_VV3->Get(hist_list[i]);
		TH1D *h_VV5 = (TH1D*)ifile_VV5->Get(hist_list[i]);
		TH1D *h_VV6 = (TH1D*)ifile_VV6->Get(hist_list[i]);
		
		TH1D *h_VVV1 = (TH1D*)ifile_VVV1->Get(hist_list[i]);
		TH1D *h_VVV2 = (TH1D*)ifile_VVV2->Get(hist_list[i]);
		TH1D *h_VVV3 = (TH1D*)ifile_VVV3->Get(hist_list[i]);
		
		TH1D *h_ttV1 = (TH1D*)ifile_ttV1->Get(hist_list[i]);
		TH1D *h_ttV2 = (TH1D*)ifile_ttV2->Get(hist_list[i]);
		
		TH1D *h_WJ1 = (TH1D*)ifile_WJ1->Get(hist_list[i]);
		TH1D *h_WJ2 = (TH1D*)ifile_WJ2->Get(hist_list[i]);
		TH1D *h_WJ3 = (TH1D*)ifile_WJ3->Get(hist_list[i]);
		TH1D *h_WJ4 = (TH1D*)ifile_WJ4->Get(hist_list[i]);
		TH1D *h_WJ5 = (TH1D*)ifile_WJ5->Get(hist_list[i]);
		TH1D *h_WJ6 = (TH1D*)ifile_WJ6->Get(hist_list[i]);
		TH1D *h_WJ7 = (TH1D*)ifile_WJ7->Get(hist_list[i]);
		//TH1D *h_WJ8 = (TH1D*)ifile_WJ8->Get(hist_list[i]);
		//TH1D *h_WJ9 = (TH1D*)ifile_WJ9->Get(hist_list[i]);
			
		TH1D *h_ZZ1 = (TH1D*)ifile_ZZ1->Get(hist_list[i]);
		TH1D *h_ZZ2 = (TH1D*)ifile_ZZ2->Get(hist_list[i]);
		TH1D *h_ZZ3 = (TH1D*)ifile_ZZ3->Get(hist_list[i]);
		
		TH1D *h_ST1 = (TH1D*)ifile_ST1->Get(hist_list[i]);
		TH1D *h_ST2 = (TH1D*)ifile_ST2->Get(hist_list[i]);
		TH1D *h_ST3 = (TH1D*)ifile_ST3->Get(hist_list[i]);
		TH1D *h_ST4 = (TH1D*)ifile_ST4->Get(hist_list[i]);
		TH1D *h_ST5 = (TH1D*)ifile_ST5->Get(hist_list[i]);
		
		TH1D *h_TTbar1 = (TH1D*)ifile_TTbar1->Get(hist_list[i]);
		TH1D *h_TTbar2 = (TH1D*)ifile_TTbar2->Get(hist_list[i]);
		TH1D *h_TTbar3 = (TH1D*)ifile_TTbar3->Get(hist_list[i]);
		//TH1D *h_ttH1 = (TH1D*)ifile_ttH1->Get(hist_list[i]);
		//TH1D *h_ttH2 = (TH1D*)ifile_ttH2->Get(hist_list[i]);
		//TH1D *h_ttH3 = (TH1D*)ifile_ttH3->Get(hist_list[i]);
		TH1D *h_ttH4 = (TH1D*)ifile_ttH4->Get(hist_list[i]);
		TH1D *h_ZH1 = (TH1D*)ifile_ZH1->Get(hist_list[i]);
		//TH1D *h_ZH2 = (TH1D*)ifile_ZH2->Get(hist_list[i]);
		TH1D *h_ZH3 = (TH1D*)ifile_ZH3->Get(hist_list[i]);
		
		TH1D *h_D1 = (TH1D*)ifile_D1->Get(hist_list[i]);
		//TH1D *h_D2 = (TH1D*)ifile_D2->Get(hist_list[i]);
		//TH1D *h_D3 = (TH1D*)ifile_D3->Get(hist_list[i]);
		//TH1D *h_D4 = (TH1D*)ifile_D4->Get(hist_list[i]);
		TH1D *h_D5 = (TH1D*)ifile_D5->Get(hist_list[i]);
		
	
		
		float DY_count = h_DY1->Integral()+h_DY2->Integral();
		float VV_count = /*h_VV1->Integral()+*/h_VV2->Integral()+h_VV3->Integral()+/*h_VV4->Integral()+*/h_VV5->Integral()+h_VV6->Integral();
		float VVV_count = h_VVV1->Integral()+h_VVV2->Integral()+h_VVV3->Integral();
		float ttV_count = h_ttV1->Integral()+h_ttV2->Integral();
		float WJ_count = h_WJ1->Integral()+h_WJ2->Integral()+h_WJ3->Integral()+h_WJ4->Integral()+h_WJ5->Integral()+h_WJ6->Integral()+h_WJ7->Integral()/*+h_WJ8->Integral()+h_WJ9->Integral()*/;
		float ZZ_count = h_ZZ1->Integral()+h_ZZ2->Integral()+h_ZZ3->Integral();
		float ST_count = h_ST1->Integral()+h_ST2->Integral()+h_ST3->Integral()+h_ST4->Integral()+h_ST5->Integral();
		float TT_count = h_TTbar1->Integral()+h_TTbar2->Integral()+h_TTbar3->Integral();
		float other_count = /*h_ttH1->Integral()+h_ttH2->Integral()+h_ttH3->Integral()+*/h_ttH4->Integral()+h_ZH1->Integral()+/*h_ZH2->Integral()+*/h_ZH3->Integral();
		float data_count = h_D1->Integral()/*+h_D2->Integral()+h_D3->Integral()+h_D4->Integral()+h_D5->Integral()*/;
		//float data_count1 = h_D2->Integral();
		//float data_count2 = h_D4->Integral();
		float data_count3 = h_D5->Integral();
		
		h_summary_DY->SetBinContent(i+1,DY_count);h_summary_DY->SetFillColor(7);
		h_summary_VV->SetBinContent(i+1,VV_count);h_summary_VV->SetFillColor(8);
		h_summary_VVV->SetBinContent(i+1,VVV_count);h_summary_VVV->SetFillColor(6);
		h_summary_ttV->SetBinContent(i+1,ttV_count);h_summary_ttV->SetFillColor(4);
		h_summary_WJ->SetBinContent(i+1,WJ_count);h_summary_WJ->SetFillColor(9);
		h_summary_ZZ->SetBinContent(i+1,ZZ_count);h_summary_ZZ->SetFillColor(5);
		h_summary_ST->SetBinContent(i+1,ST_count);h_summary_ST->SetFillColor(30);
		h_summary_TTbar->SetBinContent(i+1,TT_count);h_summary_TTbar->SetFillColor(46);
		h_summary_other->SetBinContent(i+1,other_count);h_summary_other->SetFillColor(28);
		h_summary_data->SetBinContent(i+1,data_count+data_count3);
	}

	THStack* bkg_stack = new THStack("bkg_stack", "2l and 3l channel summary in Z-veto");
	bkg_stack->Add(h_summary_DY);
	bkg_stack->Add(h_summary_VV);
	bkg_stack->Add(h_summary_VVV);
	bkg_stack->Add(h_summary_ttV);
	bkg_stack->Add(h_summary_WJ);
	bkg_stack->Add(h_summary_ST);
	bkg_stack->Add(h_summary_ZZ);
	bkg_stack->Add(h_summary_TTbar);
	bkg_stack->Add(h_summary_other);
		
	TH1D *h_bkg_total = (TH1D*)h_summary_DY->Clone("h_bkg_total");
    h_bkg_total->Add(h_summary_VV);
	h_bkg_total->Add(h_summary_VVV);
	h_bkg_total->Add(h_summary_ttV);
	h_bkg_total->Add(h_summary_WJ);
	h_bkg_total->Add(h_summary_ST);
	h_bkg_total->Add(h_summary_ZZ);
	h_bkg_total->Add(h_summary_TTbar);
	h_bkg_total->Add(h_summary_other);
	
	TH1D *h_data_total = (TH1D*)h_summary_data->Clone("h_data_total");
	h_data_total->SetMarkerColor(1);
	h_data_total->SetMarkerStyle(kFullDotLarge);
	for(int i = 0; i < num; i++){
		h_bkg_total->SetBinError(i+1,sqrt(h_bkg_total->GetBinContent(i+1)));
		h_data_total->SetBinError(i+1,sqrt(h_data_total->GetBinContent(i+1)));
	}
	canvas->Divide(1, 2);				
	// Adjust the upper pad (stacked plot)
	TPad *pad1 = (TPad*)canvas->cd(1);
	pad1->SetPad(0, 0.3, 1, 1);
	pad1->SetBottomMargin(0.01); // Remove bottom margin to reduce gap
	double max_data = h_data_total->GetMaximum();
	double max_bkg = bkg_stack->GetMaximum();
	bkg_stack->SetMaximum(std::max(max_data, max_bkg)*1.1);//give 10% extra space
	gPad->SetLogy(1);
	bkg_stack->Draw("HIST");		
	h_data_total->Draw("E SAME");
	
	/*TPaveText *textbox = new TPaveText(0.4, 0.85, 0.6, 0.9, "NDC");
	textbox->AddText("Era D");
	textbox->Draw();*/
	
	//TLegend* legend = new TLegend(0.1, 0.9, 0.3, 0.55);
	TLegend* legend = new TLegend(0.65, 0.5, 0.9, 0.9);	
	//legend->AddEntry(h_sig, "M900*1000");
	legend->AddEntry(h_summary_VV, "VV", "f");
	legend->AddEntry(h_summary_VVV, "VVV", "f");
	legend->AddEntry(h_summary_DY, "DY", "f");
	legend->AddEntry(h_summary_ZZ, "ZZ", "f");
	legend->AddEntry(h_summary_ttV, "ttV", "f");
	legend->AddEntry(h_summary_WJ, "WJ", "f");
	legend->AddEntry(h_summary_ST, "ST", "f");
	legend->AddEntry(h_summary_TTbar, "TTbar", "f");
	legend->AddEntry(h_summary_other, "Others", "f");
	legend->AddEntry(h_summary_data, "Data");
	legend->Draw();		


	// Adjust the lower pad (ratio plot)
	TPad *pad2 = (TPad*)canvas->cd(2);
	pad2->SetPad(0, 0, 1, 0.3);
	pad2->SetTopMargin(0.01);
	pad2->SetBottomMargin(0.3);
	
	// Create the Data/MC ratio plot
	//auto h_ratio = new TRatioPlot(h_data_total, h_bkg_total);
	TH1D *h_ratio = (TH1D*)h_data_total->Clone("h_ratio");
	h_ratio->Divide(h_bkg_total);
	h_ratio->SetLineColor(kBlack);
	h_ratio->SetMarkerStyle(2);
	h_ratio->SetTitle(""); // Remove the title for the ratio plot
	h_ratio->GetYaxis()->SetTitle("Data/MC");
	h_ratio->GetYaxis()->SetNdivisions(505);
	h_ratio->GetYaxis()->SetTitleSize(0.1);
	h_ratio->GetYaxis()->SetTitleOffset(0.5);
	h_ratio->GetYaxis()->SetLabelSize(0.07);
	h_ratio->GetXaxis()->SetTitleSize(0.1);
	/*h_ratio->GetXaxis()->SetBinLabel(1,"eeee");
	h_ratio->GetXaxis()->SetBinLabel(2,"eee#mu");
	h_ratio->GetXaxis()->SetBinLabel(3,"ee#mu#mu");
	h_ratio->GetXaxis()->SetBinLabel(4,"#mu#mue#mu");
	h_ratio->GetXaxis()->SetBinLabel(5,"#mu#mu#mu#mu");*/
	h_ratio->GetXaxis()->SetBinLabel(1,"ee");
	h_ratio->GetXaxis()->SetBinLabel(2,"ee+e");
	h_ratio->GetXaxis()->SetBinLabel(3,"ee+#mu");
	h_ratio->GetXaxis()->SetBinLabel(4,"ee+#tau");
	h_ratio->GetXaxis()->SetBinLabel(5,"#mu#mu");
	h_ratio->GetXaxis()->SetBinLabel(6,"#mu#mu+e");
	h_ratio->GetXaxis()->SetBinLabel(7,"#mu#mu+#mu");
	h_ratio->GetXaxis()->SetBinLabel(8,"#mu#mu+#tau");
	h_ratio->GetXaxis()->SetLabelSize(0.15);
	h_ratio->SetMinimum(0); // Set the minimum y-value for the ratio plot
	h_ratio->SetMaximum(2); // Set the maximum y-value for the ratio plot
	h_ratio->Draw("E");
		
	// Draw lines for reference
	TLine *line1 = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
	TLine *line2 = new TLine(h_ratio->GetXaxis()->GetXmin(), 0.5, h_ratio->GetXaxis()->GetXmax(), 0.5);
	TLine *line3 = new TLine(h_ratio->GetXaxis()->GetXmin(), 1.5, h_ratio->GetXaxis()->GetXmax(), 1.5);
	line1->SetLineStyle(2);line2->SetLineStyle(2);line3->SetLineStyle(2);
	line1->Draw();line2->Draw();line3->Draw();

	// Show the canvas
	canvas->Update();
	canvas->Modified();
		
	canvas->SaveAs("hist_test_nopair/summary.png");
	canvas->Clear();
}
