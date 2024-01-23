#include <TFile.h>
#include <TH1.h>
#include <TList.h>

void HC_template(const char* ext = ".root"){
    // Open the input files
	const char* inDir = "hist";
	char* dir = gSystem->ExpandPathName(inDir);
	void* dirp = gSystem->OpenDirectory(dir);
	const char* entry;
	const char* filename[100];
	TString str; Int_t n = 0;
	while((entry = (char*)gSystem->GetDirEntry(dirp))){
	  	str = entry;
	  	if(str.EndsWith(ext)){
			filename[n++] = gSystem->ConcatFileName(dir, entry);
	  	}
	}
	gROOT->Reset();
    // Create output file
    TFile* ofile = new TFile("nuisance_hist.root", "RECREATE");
	ofile->cd();
	const char *hist_list[] = {"h_Xmass_0t","h_Xmass_1t","h_Xmass_2t","h_Xmass_34t"};
	float mDCH=500, lumi_2018 = 59600;
	for(int j = 0; j < sizeof(hist_list)/sizeof(hist_list[0]); j++){
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
		const char *other__channel;
		if (j == 0){
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
			other__channel = "other__t0";
		}
		if (j == 1){
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
			other__channel = "other__t1";
		}
		if (j == 2){
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
			other__channel = "other__t2";
		}
		if (j == 3){
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
			other__channel = "other__t34";
		}
		TH1F* h_data_t0 = new TH1F("data_obs__t0", "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);	
		TH1F* h_data_t1 = new TH1F("data_obs__t1", "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);			
		TH1F* h_data_t2 = new TH1F("data_obs__t2", "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);			
		TH1F* h_data_t34 = new TH1F("data_obs__t34", "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);
		
		TH1F* h_signal500 = new TH1F(signal500__channel, "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);
		TH1F* h_signal600 = new TH1F(signal600__channel, "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);
		TH1F* h_signal700 = new TH1F(signal700__channel, "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);
		TH1F* h_signal800 = new TH1F(signal800__channel, "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);
		TH1F* h_signal900 = new TH1F(signal900__channel, "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);
		TH1F* h_signal1000 = new TH1F(signal1000__channel, "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);
		TH1F* h_signal1100 = new TH1F(signal1100__channel, "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);
		TH1F* h_signal1200 = new TH1F(signal1200__channel, "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);
		TH1F* h_signal1300 = new TH1F(signal1300__channel, "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);
		TH1F* h_signal1400 = new TH1F(signal1400__channel, "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);
		TH1F* h_prompt = new TH1F(prompt__channel, "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);						
		TH1F* h_one_fake = new TH1F(one_fake__channel, "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);			
		TH1F* h_prompt_red = new TH1F(prompt_red__channel, "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);			
		TH1F* h_other = new TH1F(other__channel, "mDCH1+mDCH2", 1000, 0, 2*mDCH+3000);			
		for(int i = 0; i < n; i++){
			TFile *ifile = new TFile(filename[i],"READ");
			std::string s = filename[i];		
			TH1F *hist = (TH1F*)ifile->Get(hist_list[j]);
			if (s.find("HppM500") < s.length()){
				hist->SetName(signal500__channel);
				ofile->cd();
				hist->Write();
			}
			else if (s.find("HppM600") < s.length()){
				hist->SetName(signal600__channel);
				ofile->cd();
				hist->Write();
			}
			else if (s.find("HppM700") < s.length()){
				hist->SetName(signal700__channel);
				ofile->cd();
				hist->Write();
			}
			else if (s.find("HppM800") < s.length()){
				hist->SetName(signal800__channel);
				ofile->cd();
				hist->Write();
			}
			else if (s.find("HppM900") < s.length()){
				hist->SetName(signal900__channel);
				ofile->cd();
				hist->Write();
			}
			else if (s.find("HppM1000") < s.length()){
				hist->SetName(signal1000__channel);
				ofile->cd();
				hist->Write();
			}
			else if (s.find("HppM1100") < s.length()){
				hist->SetName(signal1100__channel);
				ofile->cd();
				hist->Write();
			}
			else if (s.find("HppM1200") < s.length()){
				hist->SetName(signal1200__channel);
				ofile->cd();
				hist->Write();
			}
			else if (s.find("HppM1300") < s.length()){
				hist->SetName(signal1300__channel);
				ofile->cd();
				hist->Write();
			}
			else if (s.find("HppM1400") < s.length()){
				hist->SetName(signal1400__channel);
				ofile->cd();
				hist->Write();
			}
			else if (s.find("ZZ") < s.length() || s.find("ZH") < s.length() || s.find("WZTo2Q2L") < s.length() ){//prompt
				h_prompt->Add(hist);
			}
			else if (s.find("WZ_") < s.length() || s.find("WZTo3LNu") < s.length() || s.find("WWW") < s.length() ){//one fake
				h_one_fake->Add(hist);
			}	
			else if (s.find("ttH") < s.length() || s.find("ttZ") < s.length() || s.find("ttW") < s.length()|| s.find("WWZ") < s.length() ){//reducible with btag and extra lep veto
				h_prompt_red->Add(hist);
			}
			else {
				h_other->Add(hist);
			}
		}
		ofile->cd();
		h_data_t0->Write();
		h_data_t1->Write();
		h_data_t2->Write();
		h_data_t34->Write();
		h_prompt->Write();
		h_one_fake->Write();
		h_prompt_red->Write();
		h_other->Write();
	}

    std::cout << "Histograms added and saved" <<std::endl;
}
