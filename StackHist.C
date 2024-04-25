#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>

void StackHist() {
	TFile *ifile_sig = new TFile("hist_test/HppM900_2018.root","READ");               
	TFile *ifile1 = new TFile("hist_test/DYJetsToLLM10to50_2018.root","READ");     
	TFile *ifile2 = new TFile("hist_test/DYJetsToLLM50_2018.root","READ"); 
		    
	//TFile *ifile3 = new TFile("hist_test/WGToLNuG_2018.root","READ");
	TFile *ifile4 = new TFile("hist_test/WW_2018.root","READ");
	TFile *ifile5 = new TFile("hist_test/WWTo2L2Nu_2018.root","READ");
	//TFile *ifile6 = new TFile("hist_test/WZ_2018.root","READ");
	TFile *ifile7 = new TFile("hist_test/WZTo2Q2L_2018.root","READ");
	TFile *ifile8 = new TFile("hist_test/WZTo3LNu_2018.root","READ");

	TFile *ifile9 = new TFile("hist_test/WWW_2018.root","READ");
	TFile *ifile10 = new TFile("hist_test/WZZ_2018.root","READ");
	TFile *ifile11 = new TFile("hist_test/ZZZ_2018.root","READ");

	TFile *ifile12 = new TFile("hist_test/ttWJets_2018.root","READ");
	TFile *ifile1201 = new TFile("hist_test/ttZJets_2018.root","READ");
	
	TFile *ifile13 = new TFile("hist_test/ZZTo2L2Nu_2018.root","READ");
	TFile *ifile14 = new TFile("hist_test/ZZTo2Q2L_2018.root","READ");
	TFile *ifile15 = new TFile("hist_test/ZZTo4L_2018.root","READ");

	TFile *ifile16 = new TFile("hist_test/ST_s-channel_2018.root","READ");          
	TFile *ifile17 = new TFile("hist_test/ST_t-channel_antitop_2018.root","READ");  
	TFile *ifile18 = new TFile("hist_test/ST_t-channel_top_2018.root","READ");  
	TFile *ifile19 = new TFile("hist_test/ST_tW_antitop_2018.root","READ");  
	TFile *ifile20 = new TFile("hist_test/ST_tW_top_2018.root","READ");            

	//TFile *ifile21 = new TFile("hist_test/ttHTo2L2Nu_2018.root","READ");
	TFile *ifile21 = new TFile("hist_test/ttHToEE_2018.root","READ");
	TFile *ifile22 = new TFile("hist_test/ttHToEE_2018.root","READ");
	//TFile *ifile23 = new TFile("hist_test/ttHToMuMu_2018.root","READ");
	TFile *ifile23 = new TFile("hist_test/ttHToEE_2018.root","READ");
	TFile *ifile24 = new TFile("hist_test/ttHToTauTau_2018.root","READ");
	
	TFile *ifile25 = new TFile("hist_test/ZHToMuMu_2018.root","READ");
	TFile *ifile26 = new TFile("hist_test/ZHToTauTau_2018.root","READ");
	TFile *ifile27 = new TFile("hist_test/GluGluZH_2018.root","READ");
	
	TFile *ifileD1 = new TFile("hist_test/EGamma_2018.root","READ");
	TFile *ifileD2 = new TFile("hist_test/DoubleMuon_2018.root","READ");
	TFile *ifileD3 = new TFile("hist_test/SingleMuon_2018.root","READ");
	TFile *ifileD4 = new TFile("hist_test/MuonEG_2018.root","READ");
	TFile *ifileD5 = new TFile("hist_test/Tau_2018.root","READ");

	//float nEvents = 

	const char *hist_list[] = {/*"cutflow",*/"h_Xmass_0t","h_Xmass_1t","h_Xmass_2t", "h_Xmass_34t", "h_ST", "h_ll1_pt_4L","h_ll1_pt_3L","h_mZ1", "h_mZ2","h_mZ3","h_mZ4","h_mZ1_3L", "h_mZ2_3L","h_mZ3_3L","h_mZ4_3L","h_met","h_pT1","h_pT2","h_pT3","h_pT4","h_dR","h_dRll","h_dRll2"};
	
	const char *hist_names[] = {/*"Cutflow",*/"mll1 in Z(e+e-) + l region","mll1 in Z(m+m-) + l region", "mll1 in Z-veto(e+e-) + l region", "mll1 in Z-veto(m+m-) + l region", "ST", "Leading pair pT in 4L","Leading pair pT in 3L","Z mass from pair (1,3) in 4L", "Z mass from pair (1,4) in 4L","Z mass from pair (2,3) in 4L","Z mass from pair (2,4) in 4L", "Z mass from pair (1,3) in 3L", "Z mass from pair (1,4) in 3L","Z mass from pair (2,3)","Z mass from pair (2,4)","MET","Leading pT","Sub-Leading pT","3rd pT","4th pT","dR (+-) leptons; DR; Events","dR between 1st pair", "dR between 2nd pair"};
	TCanvas* canvas = new TCanvas("canvas", "Stacked histograms", 800, 700);//600);
	gStyle->SetOptStat(0);	
	
// make changes to take in xs from a csv file
	for(int i = 0; i < sizeof(hist_list)/sizeof(hist_list[0]); i++){
		TH1F *h_sig = (TH1F*)ifile_sig->Get(hist_list[i]); h_sig->SetLineStyle(5);h_sig->SetLineWidth(2);h_sig->SetLineColor(2);h_sig->Scale(10);
		
		TH1F *h1 = (TH1F*)ifile1->Get(hist_list[i]);h1->SetFillColor(7);//h1->SetLineColor(7);
		TH1F *h2 = (TH1F*)ifile2->Get(hist_list[i]);h2->SetFillColor(7);//h2->SetLineColor(7);
		
		//TH1F *h3 = (TH1F*)ifile3->Get(hist_list[i]);h3->SetFillColor(8);h3->SetLineColor(8);
		TH1F *h4 = (TH1F*)ifile4->Get(hist_list[i]);h4->SetFillColor(8);//h4->SetLineColor(8);
		TH1F *h5 = (TH1F*)ifile5->Get(hist_list[i]);h5->SetFillColor(8);//h5->SetLineColor(8);
		//TH1F *h6 = (TH1F*)ifile6->Get(hist_list[i]);h6->SetFillColor(8);//h6->SetLineColor(8);
		TH1F *h7 = (TH1F*)ifile7->Get(hist_list[i]);h7->SetFillColor(8);//h7->SetLineColor(8);
		TH1F *h8 = (TH1F*)ifile8->Get(hist_list[i]);h8->SetFillColor(8);//h8->SetLineColor(8);
		
		TH1F *h9 = (TH1F*)ifile9->Get(hist_list[i]);h9->SetFillColor(6);//h9->SetLineColor(6);
		TH1F *h10 = (TH1F*)ifile10->Get(hist_list[i]);h10->SetFillColor(6);//h10->SetLineColor(6);
		TH1F *h11 = (TH1F*)ifile11->Get(hist_list[i]);h11->SetFillColor(6);//h11->SetLineColor(6);
		
		TH1F *h12 = (TH1F*)ifile12->Get(hist_list[i]);h12->SetFillColor(4);//h12->SetLineColor(4);
		TH1F *h1201 = (TH1F*)ifile1201->Get(hist_list[i]);h1201->SetFillColor(4);//h1201->SetLineColor(4);
				
		TH1F *h13 = (TH1F*)ifile13->Get(hist_list[i]);h13->SetFillColor(5);//h13->SetLineColor(5);
		TH1F *h14 = (TH1F*)ifile14->Get(hist_list[i]);h14->SetFillColor(5);//h14->SetLineColor(5);
		TH1F *h15 = (TH1F*)ifile15->Get(hist_list[i]);h15->SetFillColor(5);//h15->SetLineColor(5);
		
		TH1F *h16 = (TH1F*)ifile16->Get(hist_list[i]);h16->SetFillColor(30);
		TH1F *h17 = (TH1F*)ifile17->Get(hist_list[i]);h17->SetFillColor(30);
		TH1F *h18 = (TH1F*)ifile18->Get(hist_list[i]);h18->SetFillColor(30);
		TH1F *h19 = (TH1F*)ifile19->Get(hist_list[i]);h19->SetFillColor(30);
		TH1F *h20 = (TH1F*)ifile20->Get(hist_list[i]);h20->SetFillColor(30);

		TH1F *h21 = (TH1F*)ifile21->Get(hist_list[i]);h21->SetFillColor(28);
		TH1F *h22 = (TH1F*)ifile22->Get(hist_list[i]);h22->SetFillColor(28);
		TH1F *h23 = (TH1F*)ifile23->Get(hist_list[i]);h23->SetFillColor(28);
		TH1F *h24 = (TH1F*)ifile24->Get(hist_list[i]);h24->SetFillColor(28);
		TH1F *h25 = (TH1F*)ifile25->Get(hist_list[i]);h25->SetFillColor(28);
		TH1F *h26 = (TH1F*)ifile26->Get(hist_list[i]);h26->SetFillColor(28);
		TH1F *h27 = (TH1F*)ifile27->Get(hist_list[i]);h27->SetFillColor(28);
		
		TH1F *hD1 = (TH1F*)ifileD1->Get(hist_list[i]);
		TH1F *hD2 = (TH1F*)ifileD2->Get(hist_list[i]);
		TH1F *hD3 = (TH1F*)ifileD3->Get(hist_list[i]);
		TH1F *hD4 = (TH1F*)ifileD4->Get(hist_list[i]);
		TH1F *hD5 = (TH1F*)ifileD5->Get(hist_list[i]);hD5->SetMarkerColor(1);hD5->SetMarkerStyle(kFullDotLarge);
		
		// bkg_stack histograms
		THStack* bkg_stack = new THStack("bkg_stack", hist_names[i]);
		bkg_stack->Add(h1);
		bkg_stack->Add(h2);
		//bkg_stack->Add(h3);
		bkg_stack->Add(h4);
		bkg_stack->Add(h5);
		//bkg_stack->Add(h6);
		bkg_stack->Add(h7);
		bkg_stack->Add(h8);
		bkg_stack->Add(h9);
		bkg_stack->Add(h10);
		bkg_stack->Add(h15); 
		bkg_stack->Add(h11);
		bkg_stack->Add(h12);
		bkg_stack->Add(h1201);
		bkg_stack->Add(h13);
		bkg_stack->Add(h14);
		bkg_stack->Add(h16);
		bkg_stack->Add(h17);
		bkg_stack->Add(h18);
		bkg_stack->Add(h19);
		bkg_stack->Add(h20);
		bkg_stack->Add(h21);
		bkg_stack->Add(h22);
		bkg_stack->Add(h23);
		bkg_stack->Add(h24);
		bkg_stack->Add(h25);
		bkg_stack->Add(h26);
		bkg_stack->Add(h27);	
		
		hD5->Add(hD1);
		hD5->Add(hD2);
		hD5->Add(hD3);
		hD5->Add(hD4);
		
		//hD5->Draw("e");// hD5->SetStats(0);
		//bkg_stack->Draw("hist same");
		//h_sig->Draw("hist same");
				
		auto rp = new TRatioPlot(bkg_stack,hD5);
		rp->SetSeparationMargin(0.01);
		rp->Draw();

		//rp->GetLowYaxis()->SetRange(0,2);
		
		rp->GetUpperPad()->cd();
		// CReate a legend
		//TLegend* legend = new TLegend(0.1, 0.9, 0.3, 0.7);
		TLegend* legend = new TLegend(0.6, 0.6, 0.9, 0.9);	
		//legend->AddEntry(h_sig, "M900*1000");
		legend->AddEntry(h8, "VV", "f");
		legend->AddEntry(h9, "VVV", "f");
		legend->AddEntry(h1, "DY", "f");
		legend->AddEntry(h13, "ZZ", "f");
		legend->AddEntry(h12, "TTVJets", "f");
		legend->AddEntry(h16, "ST", "f");
		legend->AddEntry(h21, "other BKGs", "f");
		legend->AddEntry(hD5, "Data");
		legend->AddEntry(rp, "Bkg/Data");
		// Add more entries to the legend if needed
		legend->Draw();

		// Show the canvas
		canvas->Update();
		canvas->Modified();
		
		std::string s =  "hist_test/";
		s = s + hist_list[i]+".png";
		char* title = const_cast<char*>(s.c_str());//converting string to char
		canvas->SaveAs(title);
		canvas->Clear();
	}
}
