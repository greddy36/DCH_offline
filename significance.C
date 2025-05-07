#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>

void cummilative_hist(TH1D* histogram, TH1D* cumm_bkg, TH1D* signi_hist, THStack* stack, const char* trend, const char* isSig){
	TH1D* h_cumm = new TH1D("h_cumm", histogram->GetTitle(), histogram->GetNbinsX(), histogram->GetXaxis()->GetXmin() , histogram->GetXaxis()->GetXmax());
	float tmp_val = 0, tmp_denom;
	h_cumm->SetLineWidth(histogram->GetLineWidth());
	h_cumm->SetLineStyle(histogram->GetLineStyle());
	h_cumm->SetFillColor(histogram->GetFillColor());
	h_cumm->SetLineColor(histogram->GetLineColor());
	if (isSig == "Yes"){
		for (int i =0; i < histogram->GetNbinsX(); i++){ 
			if (trend == "inc"){
				tmp_val = histogram->Integral(0,i);
			}
			else if (trend == "dec"){
				tmp_val = histogram->Integral(i,histogram->GetNbinsX()+1);//+1 is to include overflow
			}
			else{
				tmp_val = histogram->GetBinContent(i);
			}
			h_cumm->SetBinContent(i, tmp_val);
			/*float del_bkg;
			del_bkg = TMath::Sqrt(cumm_bkg->GetBinContent(i)); 
			signi_hist->SetBinContent(i, 100*TMath::Sqrt(2*(tmp_val+del_bkg)*TMath::Log(1+tmp_val/(del_bkg+0.000001))-tmp_val));*/
			signi_hist->SetBinContent(i,1*tmp_val/(TMath::Sqrt(abs(cumm_bkg->GetBinContent(i)))+ 0.01));
			//cout<<signi_hist->GetBinContent(i)<<tmp_val<<endl;
		}
		h_cumm->Draw("hist same");//signal cummilative hist
	}
	else{//bkgs
		for (int i =0; i < histogram->GetNbinsX(); i++){ 
			if (trend == "inc"){
				tmp_val = histogram->Integral(0,i);
			}
			else if (trend == "dec"){
				tmp_val = histogram->Integral(i,histogram->GetNbinsX()+1);//+1 is to include overflow
			}
			else{
				tmp_val = histogram->GetBinContent(i);
			}
			h_cumm->SetBinContent(i, tmp_val);
			cumm_bkg->SetBinContent(i, cumm_bkg->GetBinContent(i)+tmp_val);
		}
		stack->Add(h_cumm);//bkgs will be stacked
	}		
	h_cumm->Clear();//prevent memory leak
}
void cummilative_hist(TH1D* histogram, TH1D* cumm_bkg, TH1D* signi_hist, THStack* stack, const char* trend){//overloaded function with 3 parameters
	cummilative_hist(histogram, cumm_bkg, signi_hist, stack, trend, "No");
}
	
void significance() {
	TFile *ifile_sig = new TFile("hist_VR/HppM500_2016.root","READ");               
	TFile *ifile_DY1 = new TFile("hist_VR/DYJetsToLLM10to50_2016.root","READ");     
	TFile *ifile_DY2 = new TFile("hist_VR/DYJetsToLLM50_2016.root","READ"); 
		    
	//TFile *ifile_VV1 = new TFile("hist_VR/WGToLNuG_2016.root","READ");
	TFile *ifile_VV2 = new TFile("hist_VR/WW_2016.root","READ");
	TFile *ifile_VV3 = new TFile("hist_VR/WWTo2L2Nu_2016.root","READ");
	//TFile *ifile_VV4 = new TFile("hist_VR/WZ_2016.root","READ");
	TFile *ifile_VV5 = new TFile("hist_VR/WZTo2Q2L_2016.root","READ");
	TFile *ifile_VV6 = new TFile("hist_VR/WZTo3LNu_2016.root","READ");

	TFile *ifile_VVV1 = new TFile("hist_VR/WWW_2016.root","READ");
	TFile *ifile_VVV2 = new TFile("hist_VR/WZZ_2016.root","READ");
	TFile *ifile_VVV3 = new TFile("hist_VR/ZZZ_2016.root","READ");

	TFile *ifile_ttV1 = new TFile("hist_VR/ttWJets_2016.root","READ");
	TFile *ifile_ttV2 = new TFile("hist_VR/ttZJets_2016.root","READ");
	
	TFile *ifile_WJ1 = new TFile("hist_VR/WJetsToLNu_NLO_2016.root","READ");
	TFile *ifile_WJ2 = new TFile("hist_VR/WJetsToLNu_HT-70To100_2016.root","READ");
	TFile *ifile_WJ3 = new TFile("hist_VR/WJetsToLNu_HT-100To200_2016.root","READ");
	TFile *ifile_WJ4 = new TFile("hist_VR/WJetsToLNu_HT-200To400_2016.root","READ");
	TFile *ifile_WJ5 = new TFile("hist_VR/WJetsToLNu_HT-400To600_2016.root","READ");
	TFile *ifile_WJ6 = new TFile("hist_VR/WJetsToLNu_HT-600To800_2016.root","READ");
	TFile *ifile_WJ7 = new TFile("hist_VR/WJetsToLNu_HT-800To1200_2016.root","READ");
	//TFile *ifile_WJ8 = new TFile("hist_VR/WJetsToLNu_HT-1200To2500_2016.root","READ");
	//TFile *ifile_WJ9 = new TFile("hist_VR/WJetsToLNu_HT-2500ToInf_2016.root","READ");
	
	TFile *ifile_ZZ1 = new TFile("hist_VR/ZZTo2L2Nu_2016.root","READ");
	TFile *ifile_ZZ2 = new TFile("hist_VR/ZZTo2Q2L_2016.root","READ");
	TFile *ifile_ZZ3 = new TFile("hist_VR/ZZTo4L_2016.root","READ");

	TFile *ifile_ST1 = new TFile("hist_VR/ST_s-channel_2016.root","READ");          
	TFile *ifile_ST2 = new TFile("hist_VR/ST_t-channel_antitop_2016.root","READ");  
	TFile *ifile_ST3 = new TFile("hist_VR/ST_t-channel_top_2016.root","READ");  
	TFile *ifile_ST4 = new TFile("hist_VR/ST_tW_antitop_2016.root","READ");  
	TFile *ifile_ST5 = new TFile("hist_VR/ST_tW_top_2016.root","READ");            

	TFile *ifile_ttH1 = new TFile("hist_VR/ttHTo2L2Nu_2016.root","READ");
	//TFile *ifile_ttH2 = new TFile("hist_VR/ttHToEE_2016.root","READ");
	//TFile *ifile_ttH3 = new TFile("hist_VR/ttHToMuMu_2016.root","READ");
	//TFile *ifile_ttH4 = new TFile("hist_VR/ttHToTauTau_2016.root","READ");
	
	TFile *ifile_TTbar1 = new TFile("hist_VR/TTTo2L2Nu_2016.root","READ");
	TFile *ifile_TTbar2 = new TFile("hist_VR/TTToSemiLeptonic_2016.root","READ");
	TFile *ifile_TTbar3 = new TFile("hist_VR/TTToHadronic_2016.root","READ");
	
	TFile *ifile_ZH1 = new TFile("hist_VR/ZHToMuMu_2016.root","READ");
	//TFile *ifile_ZH2 = new TFile("hist_VR/ZHToTauTau_2016.root","READ");
	TFile *ifile_ZH3 = new TFile("hist_VR/GluGluZH_2016.root","READ");
	
	TFile *ifile_D1 = new TFile("hist_VR/SingleElectron_2016.root","READ");
	//TFile *ifile_D2 = new TFile("hist_VR/DoubleMuon_2016.root","READ");
	//TFile *ifile_D3 = new TFile("hist_VR/Tau_2016.root","READ");
	//TFile *ifile_D4 = new TFile("hist_VR/MuonEG_2016.root","READ");
	TFile *ifile_D5 = new TFile("hist_VR/SingleMuon_2016.root","READ");

	std::string root_dir[] = {"0tau/","1tau/","2tau/","3tau/","3lep0tau/","3lep1tau/","3lep2tau/"};
	TCanvas* canvas = new TCanvas("canvas", "Stacked Histograms", 800, 700);	
	gStyle->SetOptStat(0);	gPad->SetLogy();
	for(int j = 0; j < sizeof(root_dir)/sizeof(root_dir[0]); j++){
		std::string hist_list[] = {"h_mll1", "h_mll2", "h_ST", "h_mZ1", "h_mZ2","h_mZ3","h_mZ4","h_met",/*"h_pT1","h_pT2","h_pT3","h_pT4","h_dR1","h_dR2","h_dR3","h_dR4","h_dRll","h_dRll2"*/};
		const char *hist_names[] = { "M1_{ll} mass", "M2_{ll} mass", "ST", "M1_{l+l-}", "M2_{l+l-}","M3_{l+l-}","M4_{l+l-}","MET",/*"Leading pT","Sub-Leading pT","3rd pT","4th pT","dR between 1st(+-) leptons","dR between 2nd(+-) leptons","dR between 3rd(+-) leptons","dR between 4th(+-) leptons","dR between 1st pair", "dR between 2nd pair"*/};
		for(int i = 0; i < sizeof(hist_names)/sizeof(hist_names[0]); i++){
			cout<<hist_names[i]<<endl;
			hist_list[i] = root_dir[j] + hist_list[i];
			char* h_name = const_cast<char*>(hist_list[i].c_str());//converting string to char
			TH1D *h_sig = (TH1D*)ifile_sig->Get(h_name); h_sig->SetLineStyle(5);h_sig->SetLineWidth(2);h_sig->SetLineColor(2);
			TH1D *h_DY1 = (TH1D*)ifile_DY1->Get(h_name);h_DY1->SetFillColor(7);//h_DY1->SetLineColor(7);
			TH1D *h_DY2 = (TH1D*)ifile_DY2->Get(h_name);h_DY2->SetFillColor(7);//h_DY2->SetLineColor(7);
			
			//TH1D *h_VV1 = (TH1D*)ifile_VV1->Get(h_name);h_VV1->SetFillColor(8);h_VV1->SetLineColor(8);
			TH1D *h_VV2 = (TH1D*)ifile_VV2->Get(h_name);h_VV2->SetFillColor(8);//h_VV2->SetLineColor(8);
			TH1D *h_VV3 = (TH1D*)ifile_VV3->Get(h_name);h_VV3->SetFillColor(8);//h_VV3->SetLineColor(8);
			//TH1D *h_VV4 = (TH1D*)ifile_VV4->Get(h_name);h_VV4->SetFillColor(8);//h_VV4->SetLineColor(8);
			TH1D *h_VV5 = (TH1D*)ifile_VV5->Get(h_name);h_VV5->SetFillColor(8);//h_VV5->SetLineColor(8);
			TH1D *h_VV6 = (TH1D*)ifile_VV6->Get(h_name);h_VV6->SetFillColor(8);//h_VV6->SetLineColor(8);
			
			TH1D *h_VVV1 = (TH1D*)ifile_VVV1->Get(h_name);h_VVV1->SetFillColor(6);//h_VVV1->SetLineColor(6);
			TH1D *h_VVV2 = (TH1D*)ifile_VVV2->Get(h_name);h_VVV2->SetFillColor(6);//h_VVV2->SetLineColor(6);
			TH1D *h_VVV3 = (TH1D*)ifile_VVV3->Get(h_name);h_VVV3->SetFillColor(6);//h_VVV3->SetLineColor(6);
			
			TH1D *h_ttV1 = (TH1D*)ifile_ttV1->Get(h_name);h_ttV1->SetFillColor(4);//h_ttV1->SetLineColor(4);
			TH1D *h_ttV2 = (TH1D*)ifile_ttV2->Get(h_name);h_ttV2->SetFillColor(4);//h_ttV2->SetLineColor(4);
			
			TH1D *h_WJ1 = (TH1D*)ifile_WJ1->Get(h_name);h_WJ1->SetFillColor(9);
			TH1D *h_WJ2 = (TH1D*)ifile_WJ2->Get(h_name);h_WJ2->SetFillColor(9);
			TH1D *h_WJ3 = (TH1D*)ifile_WJ3->Get(h_name);h_WJ3->SetFillColor(9);
			TH1D *h_WJ4 = (TH1D*)ifile_WJ4->Get(h_name);h_WJ4->SetFillColor(9);
			TH1D *h_WJ5 = (TH1D*)ifile_WJ5->Get(h_name);h_WJ5->SetFillColor(9);
			TH1D *h_WJ6 = (TH1D*)ifile_WJ6->Get(h_name);h_WJ6->SetFillColor(9);
			TH1D *h_WJ7 = (TH1D*)ifile_WJ7->Get(h_name);h_WJ7->SetFillColor(9);
			//TH1D *h_WJ8 = (TH1D*)ifile_WJ8->Get(h_name);h_WJ8->SetFillColor(9);
			//TH1D *h_WJ9 = (TH1D*)ifile_WJ9->Get(h_name);h_WJ9->SetFillColor(9);
				
			TH1D *h_ZZ1 = (TH1D*)ifile_ZZ1->Get(h_name);h_ZZ1->SetFillColor(5);//h_ZZ1->SetLineColor(5);
			TH1D *h_ZZ2 = (TH1D*)ifile_ZZ2->Get(h_name);h_ZZ2->SetFillColor(5);//h_ZZ2->SetLineColor(5);
			TH1D *h_ZZ3 = (TH1D*)ifile_ZZ3->Get(h_name);h_ZZ3->SetFillColor(5);//h_ZZ3->SetLineColor(5);
			
			TH1D *h_ST1 = (TH1D*)ifile_ST1->Get(h_name);h_ST1->SetFillColor(30);
			TH1D *h_ST2 = (TH1D*)ifile_ST2->Get(h_name);h_ST2->SetFillColor(30);
			TH1D *h_ST3 = (TH1D*)ifile_ST3->Get(h_name);h_ST3->SetFillColor(30);
			TH1D *h_ST4 = (TH1D*)ifile_ST4->Get(h_name);h_ST4->SetFillColor(30);
			TH1D *h_ST5 = (TH1D*)ifile_ST5->Get(h_name);h_ST5->SetFillColor(30);

			TH1D *h_TTbar1 = (TH1D*)ifile_TTbar1->Get(h_name);h_TTbar1->SetFillColor(46);
			TH1D *h_TTbar2 = (TH1D*)ifile_TTbar2->Get(h_name);h_TTbar2->SetFillColor(46);
			TH1D *h_TTbar3 = (TH1D*)ifile_TTbar3->Get(h_name);h_TTbar3->SetFillColor(46);
			TH1D *h_ttH1 = (TH1D*)ifile_ttH1->Get(h_name);h_ttH1->SetFillColor(28);
			//TH1D *h_ttH2 = (TH1D*)ifile_ttH2->Get(h_name);h_ttH2->SetFillColor(28);
			//TH1D *h_ttH3 = (TH1D*)ifile_ttH3->Get(h_name);h_ttH3->SetFillColor(28);
			//TH1D *h_ttH4 = (TH1D*)ifile_ttH4->Get(h_name);h_ttH4->SetFillColor(28);
			TH1D *h_ZH1 = (TH1D*)ifile_ZH1->Get(h_name);h_ZH1->SetFillColor(28);
			//TH1D *h_ZH2 = (TH1D*)ifile_ZH2->Get(h_name);h_ZH2->SetFillColor(28);
			TH1D *h_ZH3 = (TH1D*)ifile_ZH3->Get(h_name);h_ZH3->SetFillColor(28);
			
			TH1D *h_D1 = (TH1D*)ifile_D1->Get(h_name);
			//TH1D *h_D2 = (TH1D*)ifile_D2->Get(h_name);
			//TH1D *h_D3 = (TH1D*)ifile_D3->Get(h_name);
			//TH1D *h_D4 = (TH1D*)ifile_D4->Get(h_name);
			TH1D *h_D5 = (TH1D*)ifile_D5->Get(h_name);
			
			for (auto hist : {h_sig,h_DY1, h_DY2, /*h_VV1,*/ h_VV2, h_VV3, /*h_VV4,*/ h_VV5, h_VV6, h_VVV1, h_VVV2, h_VVV3, h_ttV1, h_ttV2, h_ZZ1, h_ZZ2, h_ZZ3, h_WJ1, h_WJ2, h_WJ3, h_WJ4, h_WJ5, h_WJ6, h_WJ7, /*h_WJ8, h_WJ9,*/ h_ST1, h_ST2, h_ST3, h_ST4, h_ST5, h_TTbar1, h_TTbar2, h_TTbar3,h_ttH1, /*h_ttH2, h_ttH3, h_ttH4,*/ h_ZH1,/* h_ZH2,*/ h_ZH3, h_D1, /*h_D2,hD3,h_D4,*/ h_D5}) {
				int nbins = hist->GetNbinsX();  // number of bins in X-axis
				double overflowContent = hist->GetBinContent(nbins + 1);  // overflow bin content
				double overflowError = hist->GetBinError(nbins + 1);      // overflow bin error

				// Update the last visible bin with overflow content
				hist->SetBinContent(nbins, hist->GetBinContent(nbins) + overflowContent);
				hist->SetBinError(nbins, sqrt(pow(hist->GetBinError(nbins), 2) + pow(overflowError, 2)));
				//hist->Rebin(5);		    
			}

			//################## Significance ########################
			TH1D* signi_hist = new TH1D("signi_hist", "", h_sig->GetNbinsX(), h_sig->GetXaxis()->GetXmin() , h_sig->GetXaxis()->GetXmax());
			signi_hist->SetLineWidth(3);
			signi_hist->SetLineStyle(2);
			signi_hist->SetLineColor(1);
			//########################################################
			// bkg_stack histograms
			THStack* bkg_stack = new THStack("bkg_stack", hist_names[i]);


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
			
			h_sig->Scale(h_bkg_total->GetMaximum()/h_sig->GetMaximum()); //to keep data visible on the canvas
			
			TH1D *h_data_total = (TH1D*)h_D1->Clone("h_data_total");
			h_data_total->SetMarkerColor(1);
			h_data_total->SetMarkerStyle(kFullDotLarge);
			//h_data_total->Add(h_D2);
			//h_data_total->Add(h_D4);
			h_data_total->Add(h_D5); 

	/*		canvas->Divide(1, 2);				
			// Adjust the upper pad (stacked plot)
			TPad *pad1 = (TPad*)canvas->cd(1);
			pad1->SetPad(0, 0.3, 1, 1);
			pad1->SetBottomMargin(0.01); // Remove bottom margin to reduce gap

			double max_data = h_data_total->GetMaximum();
			double max_bkg = bkg_stack->GetMaximum();
			bkg_stack->SetMaximum(std::max(max_data, max_bkg)*1.1);//give 10% extra space	*/	

			TH1D *cumm_bkg = new TH1D("cumm_bkg", "", h_sig->GetNbinsX(), h_sig->GetXaxis()->GetXmin() , h_sig->GetXaxis()->GetXmax());
			const char* trend = "";
			cummilative_hist(h_DY1, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_DY2, cumm_bkg,  signi_hist, bkg_stack, trend);
			//cummilative_hist(h_VV1, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_VV2, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_VV3, cumm_bkg,  signi_hist, bkg_stack, trend);
			//cummilative_hist(h_VV4, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_VV5, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_VV6, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_VVV1, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_VVV2, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_VVV3, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_ttV1, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_ttV2, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_WJ1, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_WJ2, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_WJ3, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_WJ4, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_WJ5, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_WJ6, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_WJ7, cumm_bkg,  signi_hist, bkg_stack, trend);
			//cummilative_hist(h_WJ8, cumm_bkg,  signi_hist, bkg_stack, trend);
			//cummilative_hist(h_WJ9, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_ZZ1, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_ZZ2, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_ZZ3, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_ST1, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_ST2, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_ST3, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_ST4, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_ST5, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_TTbar1, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_TTbar2, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_TTbar3, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_ttH1, cumm_bkg,  signi_hist, bkg_stack, trend);
			//cummilative_hist(h_ttH2, cumm_bkg,  signi_hist, bkg_stack, trend);
			//cummilative_hist(h_ttH3, cumm_bkg,  signi_hist, bkg_stack, trend);
			//cummilative_hist(h_ttH4, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_ZH1, cumm_bkg,  signi_hist, bkg_stack, trend);
			//cummilative_hist(h_ZH2, cumm_bkg,  signi_hist, bkg_stack, trend);
			cummilative_hist(h_ZH3, cumm_bkg,  signi_hist, bkg_stack, trend);
			bkg_stack->Draw("HIST");
			cummilative_hist(h_sig, cumm_bkg, signi_hist, bkg_stack, trend,"Yes");
			signi_hist->Draw("HIST SAME");
			//h_sig->Draw("SAME");
			
			// Customize the legend
			TLegend* legend = new TLegend(0.65, 0.5, 0.9, 0.9);	
			//legend->AddEntry(h_sig, "M900*1000");
			legend->AddEntry(h_VV6, "VV", "f");
			legend->AddEntry(h_VVV1, "VVV", "f");
			legend->AddEntry(h_DY1, "DY", "f");
			legend->AddEntry(h_ZZ1, "ZZ", "f");
			legend->AddEntry(h_ttV1, "ttV", "f");
			legend->AddEntry(h_WJ1, "WJ", "f");
			legend->AddEntry(h_ST1, "ST", "f");
			legend->AddEntry(h_TTbar1, "TTbar", "f");
			legend->AddEntry(h_ttH1, "other", "f");
			//legend->AddEntry(h_data_total, "Data");
			legend->AddEntry(h_sig, "M500");
			//legend->AddEntry(h_data_total, data2);
			legend->AddEntry(signi_hist, "S/#sqrt{B}","l");
			// Add more entries to the legend if needed
			//legend->Draw();

			// Create a TLatex object
			TLatex latex;
			latex.SetNDC(); // Use normalized coordinates (0 to 1)
			latex.SetTextSize(0.04); // Set text size
			latex.SetTextAlign(31); // Align right (horizontal) and top (vertical)
			latex.DrawLatex(0.95, 0.95, "2016"); // Position (x, y) and text
			//latex.DrawLatex(0.7, 0.95, hist_names[i]);
	/*		// Adjust the lower pad (ratio plot)
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
			line1->Draw();line2->Draw();line3->Draw();*/


			// Show the canvas
			canvas->Update();
			canvas->Modified();
			
			std::string s =  "hist_VR/";
			s = s + hist_list[i]+ "_"+ trend+".png";
			char* title = const_cast<char*>(s.c_str());//converting string to char
			canvas->SaveAs(title);
			canvas->Clear();
		}//hist_names loop
	}//root_dir loop
}
