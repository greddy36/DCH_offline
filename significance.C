#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>

void cummilative_hist(TH1F* histogram, TH1F* tot_bkg, TH1F* signi_hist, THStack* stack, const char* trend, const char* isSig){
	TH1F* h_cumm = new TH1F("h_cumm", histogram->GetTitle(), histogram->GetNbinsX(), histogram->GetXaxis()->GetXmin() , histogram->GetXaxis()->GetXmax());
	float tmp_val = 0, tmp_denom;
	h_cumm->SetLineWidth(histogram->GetLineWidth());
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
			h_cumm->SetBinContent(i, tmp_val);
			float del_bkg;
			del_bkg = TMath::Sqrt(tot_bkg->GetBinContent(i)); 
			signi_hist->SetBinContent(i, 1700*TMath::Sqrt(2*(tmp_val+del_bkg)*TMath::Log(1+tmp_val/(del_bkg+0.000001))-tmp_val));
			//signi_hist->SetBinContent(i, 87*tmp_val/TMath::Sqrt(tot_bkg->GetBinContent(i)+0.000001));
		}
		h_cumm->Scale(1700);
		h_cumm->Draw("hist same");
		signi_hist->Draw("hist same");
	}
	else{//bkgs
		for (int i =0; i < histogram->GetNbinsX(); i++){ 
			if (trend == "inc"){
				tmp_val = histogram->Integral(0,i);
			}
			else if (trend == "dec"){
				tmp_val = histogram->Integral(i,histogram->GetNbinsX()+1);//+1 is to include overflow
			}
			h_cumm->SetBinContent(i, tmp_val);
			tmp_denom = tot_bkg->GetBinContent(i) + tmp_val;
			tot_bkg->SetBinContent(i, tmp_denom);
		}
		stack->Add(h_cumm);//bkgs will be stacked
	}		
	h_cumm->Clear();//prevent memory leak
}
void cummilative_hist(TH1F* histogram, TH1F* tot_bkg, TH1F* signi_hist, THStack* stack, const char* trend){//overloaded function with 3 parameters
	cummilative_hist(histogram, tot_bkg, signi_hist, stack, trend, "No");
}
	
void significance() {
	TFile *ifile_sig = new TFile("hist_0t/HppM500_2018.root","READ");               
	TFile *ifile1 = new TFile("hist_0t/DYJetsToLLM10to50_2018.root","READ");     
	TFile *ifile2 = new TFile("hist_0t/DYJetsToLLM50_2018.root","READ"); 
		    
	TFile *ifile3 = new TFile("hist_0t/WGToLNuG_2018.root","READ");
	TFile *ifile4 = new TFile("hist_0t/WW_2018.root","READ");
	TFile *ifile5 = new TFile("hist_0t/WWTo2L2Nu_2018.root","READ");
	TFile *ifile6 = new TFile("hist_0t/WZ_2018.root","READ");
	TFile *ifile7 = new TFile("hist_0t/WZTo2Q2L_2018.root","READ");
	TFile *ifile8 = new TFile("hist_0t/WZTo3LNu_2018.root","READ");

	TFile *ifile9 = new TFile("hist_0t/WWW_2018.root","READ");
	TFile *ifile10 = new TFile("hist_0t/WZZ_2018.root","READ");
	TFile *ifile11 = new TFile("hist_0t/ZZZ_2018.root","READ");

	TFile *ifile12 = new TFile("hist/ttWJets_2018.root","READ");
	TFile *ifile1201 = new TFile("hist/ttZJets_2018.root","READ");
	
	TFile *ifile13 = new TFile("hist/ZZTo2L2Nu_2018.root","READ");
	TFile *ifile14 = new TFile("hist/ZZTo2Q2L_2018.root","READ");
	TFile *ifile15 = new TFile("hist/ZZTo4L_2018.root","READ");

	TFile *ifile16 = new TFile("hist/ST_s-channel_2018.root","READ");          
	TFile *ifile17 = new TFile("hist/ST_t-channel_antitop_2018.root","READ");  
	TFile *ifile18 = new TFile("hist/ST_t-channel_top_2018.root","READ");  
	TFile *ifile19 = new TFile("hist/ST_tW_antitop_2018.root","READ");  
	TFile *ifile20 = new TFile("hist/ST_tW_top_2018.root","READ");            

	TFile *ifile21 = new TFile("hist/ttHTo2L2Nu_2018.root","READ");
	TFile *ifile22 = new TFile("hist/ttHToEE_2018.root","READ");
	TFile *ifile23 = new TFile("hist/ttHToMuMu_2018.root","READ");
	TFile *ifile24 = new TFile("hist/ttHToTauTau_2018.root","READ");
	
	TFile *ifile25 = new TFile("hist/ZHToMuMu_2018.root","READ");
	TFile *ifile26 = new TFile("hist/ZHToTauTau_2018.root","READ");
	TFile *ifile27 = new TFile("hist/GluGluZH_2018.root","READ");
	float lumi_2018 = 59600;
	//float nEvents = 

	const char *hist_list[] = {"cutflow", "h_mll", "h_mll2", "h_ST", "h_mZ1", "h_mZ2","h_mZ3","h_mZ4","h_met","h_pT1","h_pT2","h_pT3","h_pT4","h_dR","h_dRll","h_dRll2"};
	
	const char *stack_names[] = {"Cutflow", "DCH-1 mass", "DCH-2 mass", "ST", "Z mass from pair (1,3)", "Z mass from pair (1,4)","Z mass from pair (2,3)","Z mass from pair (2,4)","MET","Leading pT","Sub-Leading pT","3rd pT","4th pT","dR (+-) leptons","dR between 1st pair", "dR between 2nd pair"};
	TCanvas* canvas = new TCanvas("canvas", "Stacked Histograms", 800, 600);	

	for(int i = 0; i < sizeof(hist_list)/sizeof(hist_list[0]); i++){
		TH1F *h_sig = (TH1F*)ifile_sig->Get(hist_list[i]);h_sig->Scale(lumi_2018*0.0001487/176000); h_sig->SetLineWidth(2);h_sig->SetLineColor(2);
		
		TH1F *h1 = (TH1F*)ifile1->Get(hist_list[i]);h1->Scale(lumi_2018*18610/94452816);h1->SetFillColor(7);h1->SetLineColor(7);
		TH1F *h2 = (TH1F*)ifile2->Get(hist_list[i]);h2->Scale(lumi_2018*6225.42/96233328);h2->SetFillColor(7);h2->SetLineColor(7);
		
		TH1F *h3 = (TH1F*)ifile3->Get(hist_list[i]);h3->Scale(lumi_2018*489/9850083);h3->SetFillColor(8);h3->SetLineColor(8);
		TH1F *h4 = (TH1F*)ifile4->Get(hist_list[i]);h4->Scale(lumi_2018*75.8/15679000);h4->SetFillColor(8);h4->SetLineColor(8);
		TH1F *h5 = (TH1F*)ifile5->Get(hist_list[i]);h5->Scale(lumi_2018*12.178/9994000);h5->SetFillColor(8);h5->SetLineColor(8);
		TH1F *h6 = (TH1F*)ifile6->Get(hist_list[i]);h6->Scale(lumi_2018*27.6/7940000);h6->SetFillColor(8);h6->SetLineColor(8);
		TH1F *h7 = (TH1F*)ifile7->Get(hist_list[i]);h7->Scale(lumi_2018*6.204/28576996);h7->SetFillColor(8);h7->SetLineColor(8);
		TH1F *h8 = (TH1F*)ifile8->Get(hist_list[i]);h8->Scale(lumi_2018*5.052/9821283);h8->SetFillColor(8);h8->SetLineColor(8);
		
		TH1F *h9 = (TH1F*)ifile9->Get(hist_list[i]);h9->Scale(lumi_2018*0.2086/240000);h9->SetFillColor(6);h9->SetLineColor(6);
		TH1F *h10 = (TH1F*)ifile10->Get(hist_list[i]);h10->Scale(lumi_2018*0.05565/300000);h10->SetFillColor(6);h10->SetLineColor(6);
		TH1F *h11 = (TH1F*)ifile11->Get(hist_list[i]);h11->Scale(lumi_2018*0.01398/250000);h11->SetFillColor(6);h11->SetLineColor(6);
		
		TH1F *h12 = (TH1F*)ifile12->Get(hist_list[i]);h12->Scale(lumi_2018*0.2043/26918526);h12->SetFillColor(4);h12->SetLineColor(4);
		TH1F *h1201 = (TH1F*)ifile1201->Get(hist_list[i]);h1201->Scale(lumi_2018*0.5407/32793815);h1201->SetFillColor(4);h1201->SetLineColor(4);
				
		TH1F *h13 = (TH1F*)ifile13->Get(hist_list[i]);h13->Scale(lumi_2018*1.325/56886000);h13->SetFillColor(5);h13->SetLineColor(5);
		TH1F *h14 = (TH1F*)ifile14->Get(hist_list[i]);h14->Scale(lumi_2018*3.22/26962069);h14->SetFillColor(5);h14->SetLineColor(5);
		TH1F *h15 = (TH1F*)ifile15->Get(hist_list[i]);h15->Scale(lumi_2018*1.325/97570000);h15->SetFillColor(5);h15->SetLineColor(5);
		
		TH1F *h16 = (TH1F*)ifile16->Get(hist_list[i]);h16->Scale(lumi_2018*3.74/19365999);h16->SetFillColor(3);h16->SetLineColor(3);
		TH1F *h17 = (TH1F*)ifile17->Get(hist_list[i]);h17->Scale(lumi_2018*69.09/95627000);h17->SetFillColor(3);h17->SetLineColor(3);
		TH1F *h18 = (TH1F*)ifile18->Get(hist_list[i]);h18->Scale(lumi_2018*115.3/178336000);h18->SetFillColor(3);h18->SetLineColor(3);
		TH1F *h19 = (TH1F*)ifile19->Get(hist_list[i]);h19->Scale(lumi_2018*35.85/7749000);h19->SetFillColor(3);h19->SetLineColor(3);
		TH1F *h20 = (TH1F*)ifile20->Get(hist_list[i]);h20->Scale(lumi_2018*35.85/7956000);h20->SetFillColor(3);h20->SetLineColor(3);

		TH1F *h21 = (TH1F*)ifile21->Get(hist_list[i]);h21->Scale(lumi_2018*0.5418/6828000);h21->SetFillColor(9);h21->SetLineColor(9);
		TH1F *h22 = (TH1F*)ifile22->Get(hist_list[i]);h22->Scale(lumi_2018*0.4975/854760);h22->SetFillColor(9);h22->SetLineColor(9);
		TH1F *h23 = (TH1F*)ifile23->Get(hist_list[i]);h23->Scale(lumi_2018*0.5269/989000);h23->SetFillColor(9);h23->SetLineColor(9);
		TH1F *h24 = (TH1F*)ifile24->Get(hist_list[i]);h24->Scale(lumi_2018*0.5269/2478000);h24->SetFillColor(9);h24->SetLineColor(9);
		TH1F *h25 = (TH1F*)ifile25->Get(hist_list[i]);h25->Scale(lumi_2018*0.7891/998626);h25->SetFillColor(9);h25->SetLineColor(9);
		TH1F *h26 = (TH1F*)ifile26->Get(hist_list[i]);h26->Scale(lumi_2018*0.7891/14971244);h26->SetFillColor(9);h26->SetLineColor(9);
		TH1F *h27 = (TH1F*)ifile27->Get(hist_list[i]);h27->Scale(lumi_2018*0.7891/14971244);h27->SetFillColor(9);h27->SetLineColor(9);
		// Create a legend
		//TLegend* legend = new TLegend(0.1, 0.9, 0.3, 0.7);
		TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
		//################## Significance ########################
		TH1F* signi_hist = new TH1F("signi_hist", "", h_sig->GetNbinsX(), h_sig->GetXaxis()->GetXmin() , h_sig->GetXaxis()->GetXmax());
		signi_hist->SetLineWidth(3);
		signi_hist->SetLineStyle(2);
		signi_hist->SetLineColor(1);
		TH1F* tot_bkg = new TH1F("tot_bkg", "", h_sig->GetNbinsX(), h_sig->GetXaxis()->GetXmin() , h_sig->GetXaxis()->GetXmax());
		//########################################################
		// Stack histograms
		THStack* stack = new THStack("stack", stack_names[i]);
		/*stack->Add(h1);
		stack->Add(h2);
		stack->Add(h3);
		stack->Add(h4);
		stack->Add(h5);
		stack->Add(h6);
		stack->Add(h7);
		stack->Add(h8);
		stack->Add(h9);
		stack->Add(h10);
		stack->Add(h15); 
		stack->Add(h11);
		stack->Add(h12);
		stack->Add(h13);
		stack->Add(h14);
		stack->Add(h16);
		stack->Add(h17);
		stack->Add(h18);
		stack->Add(h19);
		stack->Add(h20);*/
		const char* trend = "inc";
		cummilative_hist(h1, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h2, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h3, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h4, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h5, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h6, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h7, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h8, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h9, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h10, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h11, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h12, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h13, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h14, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h15, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h16, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h17, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h18, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h19, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h20, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h21, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h22, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h23, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h24, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h25, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h26, tot_bkg,  signi_hist, stack, trend);
	    cummilative_hist(h27, tot_bkg,  signi_hist, stack, trend);
		stack->Draw("hist");
		//h_sig->Draw("hist same");
		cummilative_hist(h_sig, tot_bkg, signi_hist, stack, trend,"Yes");
		
		// Customize the legend
		legend->AddEntry(h_sig, "M500 x 1700", "l");
		legend->AddEntry(h8, "VV", "f");
		legend->AddEntry(h9, "VVV", "f");
		legend->AddEntry(h1, "DY", "f");
		legend->AddEntry(h13, "ZZ", "f");
		legend->AddEntry(h12, "TTVJets", "f");
		legend->AddEntry(h16, "ST", "f");
		legend->AddEntry(h21, "new BKGs", "f");
		legend->AddEntry(signi_hist, "S/#sqrt{B}","l");
		// Add more entries to the legend if needed
		legend->Draw();

		// Show the canvas
		canvas->Update();
		canvas->Modified();
		
		std::string s =  "hist_0t/";
		s = s + hist_list[i]+ "_"+ trend+".png";
		char* title = const_cast<char*>(s.c_str());//converting string to char
		canvas->SaveAs(title);
		canvas->Clear();
	}
}
