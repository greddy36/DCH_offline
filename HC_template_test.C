#include <TFile.h>
#include <TH1.h>
#include <TList.h>

void HC_template_test(const char* ext = ".root"){
 	TFile *ifile_sig1 = new TFile("hist/HppM500_2018.root","READ"); 
 	TFile *ifile_sig2 = new TFile("hist/HppM600_2018.root","READ"); 
 	TFile *ifile_sig3 = new TFile("hist/HppM800_2018.root","READ"); 
 	TFile *ifile_sig4 = new TFile("hist/HppM900_2018.root","READ");               
 	TFile *ifile_sig5 = new TFile("hist/HppM1000_2018.root","READ");               
 	TFile *ifile_sig6 = new TFile("hist/HppM1100_2018.root","READ");               
 	TFile *ifile_sig7 = new TFile("hist/HppM1200_2018.root","READ");               
 	TFile *ifile_sig8 = new TFile("hist/HppM1300_2018.root","READ");             
 	             
	TFile *ifile1 = new TFile("hist/DYJetsToLLM10to50_2018.root","READ");     
	TFile *ifile2 = new TFile("hist/DYJetsToLLM50_2018.root","READ"); 
		    
	TFile *ifile3 = new TFile("hist/WGToLNuG_2018.root","READ");
	TFile *ifile4 = new TFile("hist/WW_2018.root","READ");
	TFile *ifile5 = new TFile("hist/WWTo2L2Nu_2018.root","READ");
	TFile *ifile6 = new TFile("hist/WZ_2018.root","READ");
	TFile *ifile7 = new TFile("hist/WZTo2Q2L_2018.root","READ");
	TFile *ifile8 = new TFile("hist/WZTo3LNu_2018.root","READ");

	TFile *ifile9 = new TFile("hist/WWW_2018.root","READ");
	TFile *ifile10 = new TFile("hist/WZZ_2018.root","READ");
	TFile *ifile11 = new TFile("hist/ZZZ_2018.root","READ");

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

    // Create output file
    TFile* ofile = new TFile("nuisance_hist.root", "RECREATE");
	ofile->cd();
	const char *hist_list[] = {"h_Xmass_0t","h_Xmass_1t","h_Xmass_2t","h_Xmass_34t","h_Xmass_3lep"};
	float mDCH=500, lumi_2018 = 139000;
	for(int i = 0; i < sizeof(hist_list)/sizeof(hist_list[0]); i++){
		const char *signal500__channel;
		const char *signal600__channel;
		const char *signal700__channel;
		const char *signal800__channel;
		const char *signal900__channel;
		const char *signal1000__channel;
		const char *signal1100__channel;
		const char *signal1200__channel;
		const char *signal1300__channel;
		const char *signal1400__channel;
		const char *prompt__channel;
		const char *one_fake__channel;
		const char *prompt_red__channel;
		const char *fake__channel;
		if (i == 0){
			signal500__channel = "signal500__t0";
			signal600__channel = "signal600__t0";
			signal700__channel = "signal700__t0";
			signal800__channel = "signal800__t0";
			signal900__channel = "signal900__t0";
			signal1000__channel = "signal1000__t0";
			signal1100__channel = "signal1100__t0";
			signal1200__channel = "signal1200__t0";
			signal1300__channel = "signal1300__t0";
			signal1400__channel = "signal1400__t0";
			prompt__channel = "prompt__t0";
			one_fake__channel = "one_fake__t0";
			prompt_red__channel = "prompt_red__t0";
			fake__channel = "fake__t0";
		}
		if (i == 1){
			signal500__channel = "signal500__t1";
			signal600__channel = "signal600__t1";
			signal700__channel = "signal700__t1";
			signal800__channel = "signal800__t1";
			signal900__channel = "signal900__t1";
			signal1000__channel = "signal1000__t1";
			signal1100__channel = "signal1100__t1";
			signal1200__channel = "signal1200__t1";
			signal1300__channel = "signal1300__t1";
			signal1400__channel = "signal1400__t1";		
			prompt__channel = "prompt__t1";
			one_fake__channel = "one_fake__t1";
			prompt_red__channel = "prompt_red__t1";
			fake__channel = "fake__t1";
		}
		if (i == 2){
			signal500__channel = "signal500__t2";
			signal600__channel = "signal600__t2";
			signal700__channel = "signal700__t2";
			signal800__channel = "signal800__t2";
			signal900__channel = "signal900__t2";
			signal1000__channel = "signal1000__t2";
			signal1100__channel = "signal1100__t2";
			signal1200__channel = "signal1200__t2";
			signal1300__channel = "signal1300__t2";
			signal1400__channel = "signal1400__t2";			
			prompt__channel = "prompt__t2";
			one_fake__channel = "one_fake__t2";
			prompt_red__channel = "prompt_red__t2";
			fake__channel = "fake__t2";
		}
		if (i == 3){
			signal500__channel = "signal500__t34";
			signal600__channel = "signal600__t34";
			signal700__channel = "signal700__t34";
			signal800__channel = "signal800__t34";
			signal900__channel = "signal900__t34";
			signal1000__channel = "signal1000__t34";
			signal1100__channel = "signal1100__t34";
			signal1200__channel = "signal1200__t34";
			signal1300__channel = "signal1300__t34";
			signal1400__channel = "signal1400__t34";
			prompt__channel = "prompt__t34";
			one_fake__channel = "one_fake__t34";
			prompt_red__channel = "prompt_red__t34";
			fake__channel = "fake__t34";
		}
		if (i == 4){
			signal500__channel = "signal500__t3lep";
			signal600__channel = "signal600__t3lep";
			signal700__channel = "signal700__t3lep";
			signal800__channel = "signal800__t3lep";
			signal900__channel = "signal900__t3lep";
			signal1000__channel = "signal1000__t3lep";
			signal1100__channel = "signal1100__t3lep";
			signal1200__channel = "signal1200__t3lep";
			signal1300__channel = "signal1300__t3lep";
			signal1400__channel = "signal1400__t3lep";
			prompt__channel = "prompt__t3lep";
			one_fake__channel = "one_fake__t3lep";
			prompt_red__channel = "prompt_red__t3lep";
			fake__channel = "fake__t3lep";
		}
		int nbins = 3000; float xmin = 0, xmax = 6000;
		TH1F* h_data_t0 = new TH1F("data_obs__t0", "mDCH1", nbins, xmin, xmax);	
		TH1F* h_data_t1 = new TH1F("data_obs__t1", "mDCH1", nbins, xmin, xmax);			
		TH1F* h_data_t2 = new TH1F("data_obs__t2", "mDCH1", nbins, xmin, xmax);			
		TH1F* h_data_t34 = new TH1F("data_obs__t34", "mDCH1", nbins, xmin, xmax);
		TH1F* h_data_t3lep = new TH1F("data_obs__t3lep", "mDCH1", nbins, xmin, xmax);
		
		TH1F* h_signal500 = new TH1F(signal500__channel, "mDCH1", nbins, xmin, xmax);
		TH1F* h_signal600 = new TH1F(signal600__channel, "mDCH1", nbins, xmin, xmax);
		TH1F* h_signal700 = new TH1F(signal700__channel, "mDCH1", nbins, xmin, xmax);
		TH1F* h_signal800 = new TH1F(signal800__channel, "mDCH1", nbins, xmin, xmax);
		TH1F* h_signal900 = new TH1F(signal900__channel, "mDCH1", nbins, xmin, xmax);
		TH1F* h_signal1000 = new TH1F(signal1000__channel, "mDCH1", nbins, xmin, xmax);
		TH1F* h_signal1100 = new TH1F(signal1100__channel, "mDCH1", nbins, xmin, xmax);
		TH1F* h_signal1200 = new TH1F(signal1200__channel, "mDCH1", nbins, xmin, xmax);
		TH1F* h_signal1300 = new TH1F(signal1300__channel, "mDCH1", nbins, xmin, xmax);
		TH1F* h_signal1400 = new TH1F(signal1400__channel, "mDCH1", nbins, xmin, xmax);
		TH1F* h_prompt = new TH1F(prompt__channel, "mDCH1", nbins, xmin, xmax);						
		//TH1F* h_one_fake = new TH1F(one_fake__channel, "mDCH1", nbins, xmin, xmax);			
		//TH1F* h_prompt_red = new TH1F(prompt_red__channel, "mDCH1", nbins, xmin, xmax);			
		TH1F* h_fake = new TH1F(fake__channel, "mDCH1", nbins, xmin, xmax);			


		TH1F *h_sig1 = (TH1F*)ifile_sig1->Get(hist_list[i]);h_sig1->Scale(lumi_2018*0.001/176000); h_sig1->SetName(signal500__channel);
		TH1F *h_sig2 = (TH1F*)ifile_sig2->Get(hist_list[i]);h_sig2->Scale(lumi_2018*0.001/171000); h_sig2->SetName(signal600__channel);
		TH1F *h_sig3 = (TH1F*)ifile_sig3->Get(hist_list[i]);h_sig3->Scale(lumi_2018*0.001/176000); h_sig3->SetName(signal800__channel);
		TH1F *h_sig4 = (TH1F*)ifile_sig4->Get(hist_list[i]);h_sig4->Scale(lumi_2018*0.001/171000); h_sig4->SetName(signal900__channel);
		TH1F *h_sig5 = (TH1F*)ifile_sig5->Get(hist_list[i]);h_sig5->Scale(lumi_2018*0.001/175000); h_sig5->SetName(signal1000__channel);
		TH1F *h_sig6 = (TH1F*)ifile_sig6->Get(hist_list[i]);h_sig6->Scale(lumi_2018*0.001/170000); h_sig6->SetName(signal1100__channel);
		TH1F *h_sig7 = (TH1F*)ifile_sig7->Get(hist_list[i]);h_sig7->Scale(lumi_2018*0.001/176000); h_sig7->SetName(signal1200__channel);
		TH1F *h_sig8 = (TH1F*)ifile_sig8->Get(hist_list[i]);h_sig8->Scale(lumi_2018*0.001/110000); h_sig8->SetName(signal1300__channel);

	
		TH1F *h1 = (TH1F*)ifile1->Get(hist_list[i]);h1->Scale(lumi_2018*18610/94452816);
		TH1F *h2 = (TH1F*)ifile2->Get(hist_list[i]);h2->Scale(lumi_2018*6225.42/96233328);
		
		TH1F *h3 = (TH1F*)ifile3->Get(hist_list[i]);h3->Scale(lumi_2018*489/9850083);
		TH1F *h4 = (TH1F*)ifile4->Get(hist_list[i]);h4->Scale(lumi_2018*75.8/15679000);
		TH1F *h5 = (TH1F*)ifile5->Get(hist_list[i]);h5->Scale(lumi_2018*12.178/9994000);
		TH1F *h6 = (TH1F*)ifile6->Get(hist_list[i]);h6->Scale(lumi_2018*27.6/7940000);
		TH1F *h7 = (TH1F*)ifile7->Get(hist_list[i]);h7->Scale(lumi_2018*6.204/28576996);
		TH1F *h8 = (TH1F*)ifile8->Get(hist_list[i]);h8->Scale(lumi_2018*5.052/9821283);
		
		TH1F *h9 = (TH1F*)ifile9->Get(hist_list[i]);h9->Scale(lumi_2018*0.2086/240000);
		TH1F *h10 = (TH1F*)ifile10->Get(hist_list[i]);h10->Scale(lumi_2018*0.05565/300000);
		TH1F *h11 = (TH1F*)ifile11->Get(hist_list[i]);h11->Scale(lumi_2018*0.01398/250000);
		
		TH1F *h12 = (TH1F*)ifile12->Get(hist_list[i]);h12->Scale(lumi_2018*0.2043/26918526);
		TH1F *h1201 = (TH1F*)ifile1201->Get(hist_list[i]);h1201->Scale(lumi_2018*0.5407/32793815);
				
		TH1F *h13 = (TH1F*)ifile13->Get(hist_list[i]);h13->Scale(lumi_2018*1.325/56886000);
		TH1F *h14 = (TH1F*)ifile14->Get(hist_list[i]);h14->Scale(lumi_2018*3.22/26962069);
		TH1F *h15 = (TH1F*)ifile15->Get(hist_list[i]);h15->Scale(lumi_2018*1.325/97570000);
		
		TH1F *h16 = (TH1F*)ifile16->Get(hist_list[i]);h16->Scale(lumi_2018*3.74/19365999);
		TH1F *h17 = (TH1F*)ifile17->Get(hist_list[i]);h17->Scale(lumi_2018*69.09/95627000);
		TH1F *h18 = (TH1F*)ifile18->Get(hist_list[i]);h18->Scale(lumi_2018*115.3/178336000);
		TH1F *h19 = (TH1F*)ifile19->Get(hist_list[i]);h19->Scale(lumi_2018*35.85/7749000);
		TH1F *h20 = (TH1F*)ifile20->Get(hist_list[i]);h20->Scale(lumi_2018*35.85/7956000);
		TH1F *h21 = (TH1F*)ifile21->Get(hist_list[i]);h21->Scale(lumi_2018*0.5418/6828000);
		TH1F *h22 = (TH1F*)ifile22->Get(hist_list[i]);h22->Scale(lumi_2018*0.4975/854760);
		TH1F *h23 = (TH1F*)ifile23->Get(hist_list[i]);h23->Scale(lumi_2018*0.5269/989000);
		TH1F *h24 = (TH1F*)ifile24->Get(hist_list[i]);h24->Scale(lumi_2018*0.5269/2478000);
		TH1F *h25 = (TH1F*)ifile25->Get(hist_list[i]);h25->Scale(lumi_2018*0.7891/998626);
		TH1F *h26 = (TH1F*)ifile26->Get(hist_list[i]);h26->Scale(lumi_2018*0.7891/14971244);
		TH1F *h27 = (TH1F*)ifile27->Get(hist_list[i]);h27->Scale(lumi_2018*0.7891/14971244);
		
		bool isFourCh = false;
		if (isFourCh == true){
			h_fake->Add(h1);h_fake->Add(h2);h_fake->Add(h3);h_fake->Add(h4);h_fake->Add(h5);h_fake->Add(h6);h_fake->Add(h7);h_fake->Add(h8);h_fake->Add(h9);h_fake->Add(h12);h_fake->Add(h16);h_fake->Add(h17);h_fake->Add(h18);h_fake->Add(h19);h_fake->Add(h20);			
			h_prompt->Add(h10);h_prompt->Add(h11);h_prompt->Add(h1201);h_prompt->Add(h13);h_prompt->Add(h14);h_prompt->Add(h15);h_prompt->Add(h21);h_prompt->Add(h22);h_prompt->Add(h23);h_prompt->Add(h24);h_prompt->Add(h25);h_prompt->Add(h26);h_prompt->Add(h27);
		}
		else{
			h_fake->Add(h1);h_fake->Add(h2);h_fake->Add(h3);h_fake->Add(h4);h_fake->Add(h5);h_fake->Add(h7);h_fake->Add(h12);h_fake->Add(h16);h_fake->Add(h17);h_fake->Add(h18);h_fake->Add(h19);h_fake->Add(h20);		
			h_prompt->Add(h6);h_prompt->Add(h8);h_prompt->Add(h9);h_prompt->Add(h10);h_prompt->Add(h11);h_prompt->Add(h12);h_prompt->Add(h1201);h_prompt->Add(h13);h_prompt->Add(h14);h_prompt->Add(h15);h_prompt->Add(h21);h_prompt->Add(h22);h_prompt->Add(h23);h_prompt->Add(h24);h_prompt->Add(h25);h_prompt->Add(h26);h_prompt->Add(h27);
		}
		
		
		//setting overflow bins
		h_sig1->SetBinContent(nbins, h_sig1->GetBinContent(nbins+1));
		h_sig2->SetBinContent(nbins, h_sig2->GetBinContent(nbins+1));
		h_sig3->SetBinContent(nbins, h_sig3->GetBinContent(nbins+1));
		h_sig4->SetBinContent(nbins, h_sig4->GetBinContent(nbins+1));
		h_sig5->SetBinContent(nbins, h_sig5->GetBinContent(nbins+1));
		h_sig6->SetBinContent(nbins, h_sig6->GetBinContent(nbins+1));
		h_sig7->SetBinContent(nbins, h_sig7->GetBinContent(nbins+1));
		h_sig8->SetBinContent(nbins, h_sig8->GetBinContent(nbins+1));
		h_prompt->SetBinContent(nbins, h_prompt->GetBinContent(nbins+1));
		h_fake->SetBinContent(nbins, h_fake->GetBinContent(nbins+1));
		h_sig1->Rebin(200);
		h_sig2->Rebin(200);
		h_sig3->Rebin(200);
		h_sig4->Rebin(200);
		h_sig5->Rebin(200);
		h_sig6->Rebin(200);
		h_sig7->Rebin(200);
		h_sig8->Rebin(200);
		h_prompt->Rebin(200);
		h_fake->Rebin(200);

		ofile->cd();
		h_data_t0->Write();
		h_data_t1->Write();
		h_data_t2->Write();
		h_data_t34->Write();
		h_data_t3lep->Write();
		h_sig1->Write();
		h_sig2->Write();
		h_sig3->Write();
		h_sig4->Write();
		h_sig5->Write();
		h_sig6->Write();
		h_sig7->Write();
		h_sig8->Write();
		h_prompt->Write();
		//h_one_fake->Write();
		//h_prompt_red->Write();
		h_fake->Write();
	}

    std::cout << "Histograms added and saved" <<std::endl;
}
