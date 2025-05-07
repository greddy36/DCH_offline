#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>

void yield_summary_test() {
	TFile *ifile_sig = new TFile("hist_CR/WW_2016.root","READ");               
	TFile *ifile_DY1 = new TFile("hist_CR/DYJetsToLLM10to50_2016.root","READ");     
	TFile *ifile_DY2 = new TFile("hist_CR/DYJetsToLLM50_2016.root","READ"); 
		    
	//TFile *ifile_VV1 = new TFile("hist_CR/WGToLNuG_2016.root","READ");
	TFile *ifile_VV2 = new TFile("hist_CR/WW_2016.root","READ");
	TFile *ifile_VV3 = new TFile("hist_CR/WWTo2L2Nu_2016.root","READ");
	//TFile *ifile_VV4 = new TFile("hist_CR/WZ_2016.root","READ");
	TFile *ifile_VV5 = new TFile("hist_CR/WZTo2Q2L_2016.root","READ");
	TFile *ifile_VV6 = new TFile("hist_CR/WZTo3LNu_2016.root","READ");

	TFile *ifile_VVV1 = new TFile("hist_CR/WWW_2016.root","READ");
	TFile *ifile_VVV2 = new TFile("hist_CR/WZZ_2016.root","READ");
	TFile *ifile_VVV3 = new TFile("hist_CR/ZZZ_2016.root","READ");

	TFile *ifile_ttV1 = new TFile("hist_CR/ttWJets_2016.root","READ");
	TFile *ifile_ttV2 = new TFile("hist_CR/ttZJets_2016.root","READ");
	
	TFile *ifile_WJ1 = new TFile("hist_CR/WJetsToLNu_NLO_2016.root","READ");
	TFile *ifile_WJ2 = new TFile("hist_CR/WJetsToLNu_HT-70To100_2016.root","READ");
	TFile *ifile_WJ3 = new TFile("hist_CR/WJetsToLNu_HT-100To200_2016.root","READ");
	TFile *ifile_WJ4 = new TFile("hist_CR/WJetsToLNu_HT-200To400_2016.root","READ");
	TFile *ifile_WJ5 = new TFile("hist_CR/WJetsToLNu_HT-400To600_2016.root","READ");
	TFile *ifile_WJ6 = new TFile("hist_CR/WJetsToLNu_HT-600To800_2016.root","READ");
	TFile *ifile_WJ7 = new TFile("hist_CR/WJetsToLNu_HT-800To1200_2016.root","READ");
	//TFile *ifile_WJ8 = new TFile("hist_CR/WJetsToLNu_HT-1200To2500_2016.root","READ");
	//TFile *ifile_WJ9 = new TFile("hist_CR/WJetsToLNu_HT-2500ToInf_2016.root","READ");
	
	TFile *ifile_ZZ1 = new TFile("hist_CR/ZZTo2L2Nu_2016.root","READ");
	TFile *ifile_ZZ2 = new TFile("hist_CR/ZZTo2Q2L_2016.root","READ");
	TFile *ifile_ZZ3 = new TFile("hist_CR/ZZTo4L_2016.root","READ");

	TFile *ifile_ST1 = new TFile("hist_CR/ST_s-channel_2016.root","READ");          
	TFile *ifile_ST2 = new TFile("hist_CR/ST_t-channel_antitop_2016.root","READ");  
	TFile *ifile_ST3 = new TFile("hist_CR/ST_t-channel_top_2016.root","READ");  
	TFile *ifile_ST4 = new TFile("hist_CR/ST_tW_antitop_2016.root","READ");  
	TFile *ifile_ST5 = new TFile("hist_CR/ST_tW_top_2016.root","READ");            

	TFile *ifile_ttH1 = new TFile("hist_CR/ttHTo2L2Nu_2016.root","READ");
	//TFile *ifile_ttH2 = new TFile("hist_CR/ttHToEE_2016.root","READ");
	//TFile *ifile_ttH3 = new TFile("hist_CR/ttHToMuMu_2016.root","READ");
	//TFile *ifile_ttH4 = new TFile("hist_CR/ttHToTauTau_2016.root","READ");
	
	TFile *ifile_TTbar1 = new TFile("hist_CR/TTTo2L2Nu_2016.root","READ");
	TFile *ifile_TTbar2 = new TFile("hist_CR/TTToSemiLeptonic_2016.root","READ");
	TFile *ifile_TTbar3 = new TFile("hist_CR/TTToHadronic_2016.root","READ");
	
	TFile *ifile_ZH1 = new TFile("hist_CR/ZHToMuMu_2016.root","READ");
	//TFile *ifile_ZH2 = new TFile("hist_CR/ZHToTauTau_2016.root","READ");
	TFile *ifile_ZH3 = new TFile("hist_CR/GluGluZH_2016.root","READ");
	
	TFile *ifile_D1 = new TFile("hist_CR/SingleElectron_2016.root","READ");
	//TFile *ifile_D2 = new TFile("hist_CR/DoubleMuon_2016.root","READ");
	//TFile *ifile_D3 = new TFile("hist_CR/Tau_2016.root","READ");
	//TFile *ifile_D4 = new TFile("hist_CR/MuonEG_2016.root","READ");
	TFile *ifile_D5 = new TFile("hist_CR/SingleMuon_2016.root","READ");

	const char *hist_list[] = {"0tau/h_cat","1tau/h_cat","2tau/h_cat","3tau/h_cat","3lep0tau/h_cat","3lep1tau/h_cat","3lep2tau/h_cat"};
	
	const char *hist_names[] = {"yields in 0-#tau 4l", "yields in 1-#tau 4l","yields in 2-#tau 4l","yields in 3-#tau -4l","yields in 0-#tau 3l","yields in 1-#tau 3l","yields in 2-#tau 3l"};

	TCanvas* canvas = new TCanvas("canvas", "Stacked histograms", 800, 700);//600);
	gStyle->SetOptStat(0);	
	
// make changes to take in xs from a csv file
	for(int i = 0; i < sizeof(hist_list)/sizeof(hist_list[0]); i++){
		//TH1D *h_sig = (TH1D*)ifile_sig->Get(hist_list[i]); h_sig->SetLineStyle(5);h_sig->SetLineWidth(2);h_sig->SetLineColor(2);h_sig->Scale(10);
		TH1D *h_DY1 = (TH1D*)ifile_DY1->Get(hist_list[i]);h_DY1->SetFillColor(7);//h_DY1->SetLineColor(7);
		TH1D *h_DY2 = (TH1D*)ifile_DY2->Get(hist_list[i]);h_DY2->SetFillColor(7);//h_DY2->SetLineColor(7);
		
		//TH1D *h_VV1 = (TH1D*)ifile_VV1->Get(hist_list[i]);h_VV1->SetFillColor(8);h_VV1->SetLineColor(8);
		TH1D *h_VV2 = (TH1D*)ifile_VV2->Get(hist_list[i]);h_VV2->SetFillColor(8);//h_VV2->SetLineColor(8);
		TH1D *h_VV3 = (TH1D*)ifile_VV3->Get(hist_list[i]);h_VV3->SetFillColor(8);//h_VV3->SetLineColor(8);
		//TH1D *h_VV4 = (TH1D*)ifile_VV4->Get(hist_list[i]);h_VV4->SetFillColor(8);//h_VV4->SetLineColor(8);
		TH1D *h_VV5 = (TH1D*)ifile_VV5->Get(hist_list[i]);h_VV5->SetFillColor(8);//h_VV5->SetLineColor(8);
		TH1D *h_VV6 = (TH1D*)ifile_VV6->Get(hist_list[i]);h_VV6->SetFillColor(8);//h_VV6->SetLineColor(8);
		
		TH1D *h_VVV1 = (TH1D*)ifile_VVV1->Get(hist_list[i]);h_VVV1->SetFillColor(6);//h_VVV1->SetLineColor(6);
		TH1D *h_VVV2 = (TH1D*)ifile_VVV2->Get(hist_list[i]);h_VVV2->SetFillColor(6);//h_VVV2->SetLineColor(6);
		TH1D *h_VVV3 = (TH1D*)ifile_VVV3->Get(hist_list[i]);h_VVV3->SetFillColor(6);//h_VVV3->SetLineColor(6);
		
		TH1D *h_ttV1 = (TH1D*)ifile_ttV1->Get(hist_list[i]);h_ttV1->SetFillColor(4);//h_ttV1->SetLineColor(4);
		TH1D *h_ttV2 = (TH1D*)ifile_ttV2->Get(hist_list[i]);h_ttV2->SetFillColor(4);//h_ttV2->SetLineColor(4);
		
		TH1D *h_WJ1 = (TH1D*)ifile_WJ1->Get(hist_list[i]);h_WJ1->SetFillColor(9);
		TH1D *h_WJ2 = (TH1D*)ifile_WJ2->Get(hist_list[i]);h_WJ2->SetFillColor(9);
		TH1D *h_WJ3 = (TH1D*)ifile_WJ3->Get(hist_list[i]);h_WJ3->SetFillColor(9);
		TH1D *h_WJ4 = (TH1D*)ifile_WJ4->Get(hist_list[i]);h_WJ4->SetFillColor(9);
		TH1D *h_WJ5 = (TH1D*)ifile_WJ5->Get(hist_list[i]);h_WJ5->SetFillColor(9);
		TH1D *h_WJ6 = (TH1D*)ifile_WJ6->Get(hist_list[i]);h_WJ6->SetFillColor(9);
		TH1D *h_WJ7 = (TH1D*)ifile_WJ7->Get(hist_list[i]);h_WJ7->SetFillColor(9);
		//TH1D *h_WJ8 = (TH1D*)ifile_WJ8->Get(hist_list[i]);h_WJ8->SetFillColor(9);
		//TH1D *h_WJ9 = (TH1D*)ifile_WJ9->Get(hist_list[i]);h_WJ9->SetFillColor(9);
			
		TH1D *h_ZZ1 = (TH1D*)ifile_ZZ1->Get(hist_list[i]);h_ZZ1->SetFillColor(5);//h_ZZ1->SetLineColor(5);
		TH1D *h_ZZ2 = (TH1D*)ifile_ZZ2->Get(hist_list[i]);h_ZZ2->SetFillColor(5);//h_ZZ2->SetLineColor(5);
		TH1D *h_ZZ3 = (TH1D*)ifile_ZZ3->Get(hist_list[i]);h_ZZ3->SetFillColor(5);//h_ZZ3->SetLineColor(5);
		
		TH1D *h_ST1 = (TH1D*)ifile_ST1->Get(hist_list[i]);h_ST1->SetFillColor(30);
		TH1D *h_ST2 = (TH1D*)ifile_ST2->Get(hist_list[i]);h_ST2->SetFillColor(30);
		TH1D *h_ST3 = (TH1D*)ifile_ST3->Get(hist_list[i]);h_ST3->SetFillColor(30);
		TH1D *h_ST4 = (TH1D*)ifile_ST4->Get(hist_list[i]);h_ST4->SetFillColor(30);
		TH1D *h_ST5 = (TH1D*)ifile_ST5->Get(hist_list[i]);h_ST5->SetFillColor(30);

		TH1D *h_TTbar1 = (TH1D*)ifile_TTbar1->Get(hist_list[i]);h_TTbar1->SetFillColor(46);
		TH1D *h_TTbar2 = (TH1D*)ifile_TTbar2->Get(hist_list[i]);h_TTbar2->SetFillColor(46);
		TH1D *h_TTbar3 = (TH1D*)ifile_TTbar3->Get(hist_list[i]);h_TTbar3->SetFillColor(46);
		TH1D *h_ttH1 = (TH1D*)ifile_ttH1->Get(hist_list[i]);h_ttH1->SetFillColor(28);
		//TH1D *h_ttH2 = (TH1D*)ifile_ttH2->Get(hist_list[i]);h_ttH2->SetFillColor(28);
		//TH1D *h_ttH3 = (TH1D*)ifile_ttH3->Get(hist_list[i]);h_ttH3->SetFillColor(28);
		//TH1D *h_ttH4 = (TH1D*)ifile_ttH4->Get(hist_list[i]);h_ttH4->SetFillColor(28);
		TH1D *h_ZH1 = (TH1D*)ifile_ZH1->Get(hist_list[i]);h_ZH1->SetFillColor(28);
		//TH1D *h_ZH2 = (TH1D*)ifile_ZH2->Get(hist_list[i]);h_ZH2->SetFillColor(28);
		TH1D *h_ZH3 = (TH1D*)ifile_ZH3->Get(hist_list[i]);h_ZH3->SetFillColor(28);
		
		TH1D *h_D1 = (TH1D*)ifile_D1->Get(hist_list[i]);
		//TH1D *h_D2 = (TH1D*)ifile_D2->Get(hist_list[i]);
		//TH1D *h_D3 = (TH1D*)ifile_D3->Get(hist_list[i]);
		//TH1D *h_D4 = (TH1D*)ifile_D4->Get(hist_list[i]);
		TH1D *h_D5 = (TH1D*)ifile_D5->Get(hist_list[i]);
		
		for (auto hist : {h_DY1, h_DY2, /*h_VV1,*/ h_VV2, h_VV3, /*h_VV4,*/ h_VV5, h_VV6, h_VVV1, h_VVV2, h_VVV3, h_ttV1, h_ttV2, h_ZZ1, h_ZZ2, h_ZZ3, h_WJ1, h_WJ2, h_WJ3, h_WJ4, h_WJ5, h_WJ6, h_WJ7, /*h_WJ8, h_WJ9,*/ h_ST1, h_ST2, h_ST3, h_ST4, h_ST5, h_TTbar1, h_TTbar2, h_TTbar3,h_ttH1,/* h_ttH2, h_ttH3,h_ttH4,*/ h_ZH1,/* h_ZH2,*/ h_ZH3, h_D1, /*h_D2,hD3,h_D4,*/ h_D5}) {
		    int nbins = hist->GetNbinsX();  // number of bins in X-axis
		    double overflowContent = hist->GetBinContent(nbins + 1);  // overflow bin content
		    double overflowError = hist->GetBinError(nbins + 1);      // overflow bin error

		    // Update the last visible bin with overflow content
		    hist->SetBinContent(nbins, hist->GetBinContent(nbins) + overflowContent);
		    hist->SetBinError(nbins, sqrt(pow(hist->GetBinError(nbins), 2) + pow(overflowError, 2)));
		    //hist->Rebin(5);		    
		}
		
		float DY_count = h_DY1->Integral()+h_DY2->Integral();
		float VV_count = /*h_VV1->Integral()+*/h_VV2->Integral()+h_VV3->Integral()+/*h_VV4->Integral()+*/h_VV5->Integral()+h_VV6->Integral();
		float VVV_count = h_VVV1->Integral()+h_VVV2->Integral()+h_VVV3->Integral();
		float ttV_count = h_ttV1->Integral()+h_ttV2->Integral();
		float WJ_count = h_WJ1->Integral()+h_WJ2->Integral()+h_WJ3->Integral()+h_WJ4->Integral()+h_WJ5->Integral()+h_WJ6->Integral()+h_WJ7->Integral();//+h_WJ8->Integral()+h_WJ9->Integral();
		float ZZ_count = h_ZZ1->Integral()+h_ZZ2->Integral()+h_ZZ3->Integral();
		float ST_count = h_ST1->Integral()+h_ST2->Integral()+h_ST3->Integral()+h_ST4->Integral()+h_ST5->Integral();
		float TT_count = h_TTbar1->Integral()+h_TTbar2->Integral()+h_TTbar3->Integral();
		float other_count = h_ttH1->Integral()/*+h_ttH2->Integral()+h_ttH3->Integral()+h_ttH4->Integral()*/+h_ZH1->Integral()/*+h_ZH2->Integral()*/+h_ZH3->Integral();
		float data_count = h_D1->Integral()/*+h_D2->Integral()+h_D3->Integral()+h_D4->Integral()+h_D5->Integral()*/;
		//float data_count1 = h_D2->Integral();
		//float data_count2 = h_D4->Integral();
		float data_count3 = h_D5->Integral();
				
		TString DY_legend = "DY"+ TString::Format("\t %.2f", DY_count);//Set precision to 2 decimal places
		TString VV_legend = "VV"+ TString::Format("\t %.2f", VV_count);
		TString VVV_legend = "VVV"+ TString::Format("\t %.2f", VVV_count);
		TString ttV_legend = "ttV"+ TString::Format("\t %.2f", ttV_count);
		TString WJ_legend = "WJ"+ TString::Format("\t %.2f", WJ_count);
		TString ZZ_legend = "ZZ"+ TString::Format("\t %.2f", ZZ_count);
		TString ST_legend = "ST"+ TString::Format("\t %.2f", ST_count);
		TString TT_legend = "TTbar"+ TString::Format("\t %.2f", TT_count);
		TString other_legend = "other Bkg"+ TString::Format("\t %.2f", other_count);
		TString data_legend = "EGamma Data"+ TString::Format("\t %.0f", data_count);
		//TString data_legend1 = "DoubleMu Data"+ TString::Format("\t %.0f", data_count1);
		//TString data_legend2 = "MuonEG Data"+ TString::Format("\t %.0f", data_count2);
		TString data_legend3 = "SingleMu Data"+ TString::Format("\t %.0f", data_count3);
		
		// bkg_stack histograms
		THStack* bkg_stack = new THStack("bkg_stack", hist_names[i]);
		bkg_stack->Add(h_DY1);
		bkg_stack->Add(h_DY2);
		//bkg_stack->Add(h_VV1);
		bkg_stack->Add(h_VV2);
		bkg_stack->Add(h_VV3);
		//bkg_stack->Add(h_VV4);
		bkg_stack->Add(h_VV5);
		bkg_stack->Add(h_VV6);
		bkg_stack->Add(h_VVV1);
		bkg_stack->Add(h_VVV2);
		bkg_stack->Add(h_VVV3);
		bkg_stack->Add(h_ttV1);
		bkg_stack->Add(h_ttV2);
		bkg_stack->Add(h_WJ1);
		bkg_stack->Add(h_WJ2);
		bkg_stack->Add(h_WJ3);
		bkg_stack->Add(h_WJ4);
		bkg_stack->Add(h_WJ5);
		bkg_stack->Add(h_WJ6);
		bkg_stack->Add(h_WJ7);
		//bkg_stack->Add(h_WJ8);
		//bkg_stack->Add(h_WJ9);
		bkg_stack->Add(h_ZZ1);
		bkg_stack->Add(h_ZZ2);
		bkg_stack->Add(h_ZZ3);
		bkg_stack->Add(h_ST1);
		bkg_stack->Add(h_ST2);
		bkg_stack->Add(h_ST3);
		bkg_stack->Add(h_ST4);
		bkg_stack->Add(h_ST5);
		bkg_stack->Add(h_TTbar1);
		bkg_stack->Add(h_TTbar2);
		bkg_stack->Add(h_TTbar3);
		bkg_stack->Add(h_ttH1);
		//bkg_stack->Add(h_ttH2);
		//bkg_stack->Add(h_ttH3);
		//bkg_stack->Add(h_ttH4);	
		bkg_stack->Add(h_ZH1);
		//bkg_stack->Add(h_ZH2);
		bkg_stack->Add(h_ZH3);
		

		TH1D *h_bkg_total = (TH1D*)h_DY1->Clone("h_bkg_total");
    	h_bkg_total->Add(h_DY2);
    	//h_bkg_total->Add(h_VV1);
		h_bkg_total->Add(h_VV2);
		h_bkg_total->Add(h_VV3);
		//h_bkg_total->Add(h_VV4);
		h_bkg_total->Add(h_VV5);
		h_bkg_total->Add(h_VV6);
		h_bkg_total->Add(h_VVV1);
		h_bkg_total->Add(h_VVV2);
		h_bkg_total->Add(h_VVV3);
		h_bkg_total->Add(h_ttV1);
		h_bkg_total->Add(h_ttV2);
		h_bkg_total->Add(h_WJ1);
		h_bkg_total->Add(h_WJ2);
		h_bkg_total->Add(h_WJ3);
		h_bkg_total->Add(h_WJ4);
		h_bkg_total->Add(h_WJ5);
		h_bkg_total->Add(h_WJ6);
		h_bkg_total->Add(h_WJ7);
		//h_bkg_total->Add(h_WJ8);
		//h_bkg_total->Add(h_WJ9);
		h_bkg_total->Add(h_ZZ1);
		h_bkg_total->Add(h_ZZ2);
		h_bkg_total->Add(h_ZZ3);
		h_bkg_total->Add(h_ST1);
		h_bkg_total->Add(h_ST2);
		h_bkg_total->Add(h_ST3);
		h_bkg_total->Add(h_ST4);
		h_bkg_total->Add(h_ST5);
		h_bkg_total->Add(h_TTbar1);
		h_bkg_total->Add(h_TTbar2);
		h_bkg_total->Add(h_TTbar3);
		h_bkg_total->Add(h_ttH1);
		//h_bkg_total->Add(h_ttH2);
		//h_bkg_total->Add(h_ttH3);
		//h_bkg_total->Add(h_ttH4);
		h_bkg_total->Add(h_ZH1);
		//h_bkg_total->Add(h_ZH2);
		h_bkg_total->Add(h_ZH3);
		TH1D *h_data_total = (TH1D*)h_D1->Clone("h_data_total");
		h_data_total->SetTitle(hist_names[i]);
		h_data_total->SetMarkerColor(1);
		h_data_total->SetMarkerStyle(kFullDotLarge);
		//h_data_total->Add(h_D2);
		//h_data_total->Add(h_D4);
		h_data_total->Add(h_D5);

		canvas->Divide(1, 2);				
		// Adjust the upper pad (stacked plot)
		TPad *pad1 = (TPad*)canvas->cd(1);
		pad1->SetPad(0, 0.3, 1, 1);
		pad1->SetBottomMargin(0.01); // Remove bottom margin to reduce gap

		double max_data = h_data_total->GetMaximum();
		double max_bkg = bkg_stack->GetMaximum();
		bkg_stack->SetMaximum(std::max(max_data, max_bkg)*1.1);//give 10% extra space
		bkg_stack->Draw("HIST");		
		h_data_total->Draw("E SAME");
		
		/*TPaveText *textbox = new TPaveText(0.4, 0.85, 0.6, 0.9, "NDC");
		textbox->AddText("Era D");
		textbox->Draw();*/
		
		//TLegend* legend = new TLegend(0.1, 0.9, 0.3, 0.7);
		TLegend* legend = new TLegend(0.65, 0.5, 0.9, 0.9);	
		//legend->AddEntry(h_sig, "M900*1000");
		legend->AddEntry(h_VV6, VV_legend, "f");
		legend->AddEntry(h_VVV1, VVV_legend, "f");
		legend->AddEntry(h_DY1, DY_legend, "f");
		legend->AddEntry(h_ZZ1, ZZ_legend, "f");
		legend->AddEntry(h_ttV1, ttV_legend, "f");
		legend->AddEntry(h_WJ1, WJ_legend, "f");
		legend->AddEntry(h_ST1, ST_legend, "f");
		legend->AddEntry(h_TTbar1, TT_legend, "f");
		legend->AddEntry(h_ttH1, other_legend, "f");
		legend->AddEntry(h_data_total, data_legend);
		legend->AddEntry(h_data_total, data_legend3);
		//legend->AddEntry(h_data_total, data_legend1);
		//legend->AddEntry(h_data_total, data_legend2);
		//legend->Draw();		

		// Create a TLatex object
		TLatex latex;
		latex.SetNDC(); // Use normalized coordinates (0 to 1)
		latex.SetTextSize(0.04); // Set text size
		latex.SetTextAlign(31); // Align right (horizontal) and top (vertical)
		latex.DrawLatex(0.95, 0.95, "2016"); // Position (x, y) and text

		// Adjust the lower pad (ratio plot)
		TPad *pad2 = (TPad*)canvas->cd(2);
		pad2->SetPad(0, 0, 1, 0.3);
		pad2->SetTopMargin(0.01);
		pad2->SetBottomMargin(0.3);
		
		// Create the Data/MC ratio plot
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
		h_ratio->GetXaxis()->SetLabelSize(0.1);
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
		
		std::string s =  "hist/", s1, s2;
		s1 = s + i +".png";
		//s2 = s + hist_list[i]+".svg";
		char* title1 = const_cast<char*>(s1.c_str());//converting string to char
		//char* title2 = const_cast<char*>(s2.c_str());//converting string to char
		canvas->SaveAs(title1);
		//canvas->SaveAs(title2);
		canvas->Clear();
	}
}
