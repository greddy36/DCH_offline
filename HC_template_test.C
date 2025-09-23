//Makes nuisance histograms for HC
#include <TFile.h>
#include <TH1.h>
#include <TList.h>
#include "include/Xsections.C"

const char* sampleKind(std::string fname, std::string hist_name){
	if (hist_name.find("3lep") > hist_name.length()){//4lep
		int len = fname.length();
		if (fname.find("HppM500_") < len) return "M500";
		else if (fname.find("HppM500_") < len) return "M500";
		else if (fname.find("HppM600_") < len) return "M600";
		else if (fname.find("HppM700_") < len) return "M700";
		else if (fname.find("HppM800_") < len) return "M800";
		else if (fname.find("HppM900_") < len) return "M900";
		else if (fname.find("HppM1000_") < len) return "M1000";
		else if (fname.find("HppM1100_") < len) return "M1100";
		else if (fname.find("HppM1200_") < len) return "M1200";
		else if (fname.find("HppM1300_") < len) return "M1300";
		else if (fname.find("HppM1400_") < len) return "M1400";
		else if (fname.find("ZZ_") < len ||
			fname.find("ZZTo4L") < len ||
			fname.find("HZJ") < len ||
			fname.find("ttH") < len ||
			fname.find("ttZ") < len ||
			fname.find("ZH") < len  ||
			fname.find("HZJ") < len ||
			fname.find("TWZ") < len )
			return "prompt";
		else if (fname.find("WWW_") < len ||
			fname.find("WZ_") < len ||
			fname.find("WZTo3LNu") < len ||
			fname.find("DY") < len ||
			fname.find("WGToLNuG") < len ||
			fname.find("WWTo2L2Nu") < len ||
			fname.find("ZZTo2L2Nu") < len ||
			fname.find("ZZTo2Q2L") < len ||
			fname.find("WZTo2Q2L") < len ||
			fname.find("ttW") < len ||
			fname.find("ST_") < len ||
			fname.find("QCD") < len ||
			fname.find("WJetsToLNu") < len ||
			fname.find("TTToSemiLep") < len ||
			fname.find("TTToHadr") < len ||
			fname.find("TTTo2L2Nu") < len)
			return "fake";
		else if (fname.find("EGamma") < len || fname.find("Single") < len)
			return "data";
		else return "BLABLA in 4lep";
	}
	else if (hist_name.find("3lep") < hist_name.length()){
		int len = fname.length();
		if (fname.find("HppM500_") < len) return "M500";
		else if (fname.find("HppM500_") < len) return "M500";
		else if (fname.find("HppM600_") < len) return "M600";
		else if (fname.find("HppM700_") < len) return "M700";
		else if (fname.find("HppM800_") < len) return "M800";
		else if (fname.find("HppM900_") < len) return "M900";
		else if (fname.find("HppM1000_") < len) return "M1000";
		else if (fname.find("HppM1100_") < len) return "M1100";
		else if (fname.find("HppM1200_") < len) return "M1200";
		else if (fname.find("HppM1300_") < len) return "M1300";
		else if (fname.find("HppM1400_") < len) return "M1400";
		else if (fname.find("ZZ_") < len ||
			fname.find("ZZTo4L") < len ||
			fname.find("ttH") < len ||
			fname.find("HZJ") < len ||
			fname.find("ttZ") < len ||
			fname.find("ZH") < len ||
			fname.find("HZJ") < len ||
			fname.find("TWZ") < len ||
			fname.find("WWW_") < len ||
			fname.find("WZ_") < len ||
			fname.find("WZTo3LNu") < len ||
			fname.find("ttW") < len )
			return "prompt";
		else if (
			fname.find("DY") < len ||
			fname.find("WGToLNuG") < len ||
			fname.find("WWTo2L2Nu") < len ||
			fname.find("ZZTo2L2Nu") < len ||
			fname.find("ZZTo2Q2L") < len ||
			fname.find("WZTo2Q2L") < len ||
			fname.find("ST_") < len ||
			fname.find("QCD") < len ||
			fname.find("WJetsToLNu") < len ||
			fname.find("TTToSemiLep") < len ||
			fname.find("TTToHadr") < len ||
			fname.find("TTTo2L2Nu") < len)
			return "fake";
		else if (fname.find("EGamma") < len || fname.find("Single") < len)
			return "data";
		else return "BLABLA in 3lep";
	}
}

void HC_template_test(const char* ext = "2018.root"){
	const char* inDir = "hist_MY";
	char* dir = gSystem->ExpandPathName(inDir);
	void* dirp = gSystem->OpenDirectory(dir);
	const char* entry;
	const char* filename[100];
	TString str; Int_t nfiles = 0;
	while((entry = (char*)gSystem->GetDirEntry(dirp))){
	  	str = entry;
	  	if(str.EndsWith(ext)){
			filename[nfiles++] = gSystem->ConcatFileName(dir, entry);
	  	}
	}
	gROOT->Reset();

    // Create output file
    TFile* ofile = new TFile("hist_MY/nuisance_hist_2018_fineNEWallbkginprompt.root", "RECREATE");
	const char* prompt__channel;
	const char* fake__channel;
	
	float xmin = 0, xmax = 1500; int binw = 10; int nbins = (xmax-xmin)/binw; 
	TH1F* h_data_t0 = new TH1F("data_obs__t0", "mll1", nbins, xmin, xmax);	
	TH1F* h_data_t1 = new TH1F("data_obs__t1", "mll1", nbins, xmin, xmax);			
	TH1F* h_data_t2 = new TH1F("data_obs__t2", "mll1", nbins, xmin, xmax);			
	TH1F* h_data_t3 = new TH1F("data_obs__t3", "mll1", nbins, xmin, xmax);
	TH1F* h_data_t03l = new TH1F("data_obs__t03l", "mll1", nbins, xmin, xmax);
	TH1F* h_data_t13l = new TH1F("data_obs__t13l", "mll1", nbins, xmin, xmax);
	TH1F* h_data_t23l = new TH1F("data_obs__t23l", "mll1", nbins, xmin, xmax);
	ofile->cd();
	h_data_t0->Write();
	h_data_t1->Write();
	h_data_t2->Write();
	h_data_t3->Write();
	h_data_t03l->Write();
	h_data_t13l->Write();
	h_data_t23l->Write();

	const char *hist_list[] = {"0tau/h_mll1","1tau/h_mll1","2tau/h_mll1","3tau/h_mll1","3lep0tau/h_mll1","3lep1tau/h_mll1","3lep2tau/h_mll1"};
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
		if (hist_list[i] == "0tau/h_mll1"){
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
		else if (hist_list[i] == "1tau/h_mll1"){
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
		else if (hist_list[i] == "2tau/h_mll1"){ 
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
		else if (hist_list[i] == "3tau/h_mll1"){
			signal500__channel = "signal500__t3";
			signal600__channel = "signal600__t3";
			signal700__channel = "signal700__t3";
			signal800__channel = "signal800__t3";
			signal900__channel = "signal900__t3";
			signal1000__channel = "signal1000__t3";
			signal1100__channel = "signal1100__t3";
			signal1200__channel = "signal1200__t3";
			signal1300__channel = "signal1300__t3";
			signal1400__channel = "signal1400__t3";
			prompt__channel = "prompt__t3";
			one_fake__channel = "one_fake__t3";
			prompt_red__channel = "prompt_red__t3";
			fake__channel = "fake__t3";
		}
		else if (hist_list[i] == "3lep0tau/h_mll1"){
			signal500__channel = "signal500__t03l";
			signal600__channel = "signal600__t03l";
			signal700__channel = "signal700__t03l";
			signal800__channel = "signal800__t03l";
			signal900__channel = "signal900__t03l";
			signal1000__channel = "signal1000__t03l";
			signal1100__channel = "signal1100__t03l";
			signal1200__channel = "signal1200__t03l";
			signal1300__channel = "signal1300__t03l";
			signal1400__channel = "signal1400__t03l";
			prompt__channel = "prompt__t03l";
			one_fake__channel = "one_fake__t03l";
			prompt_red__channel = "prompt_red__t03l";
			fake__channel = "fake__t03l";
		}
		else if (hist_list[i] == "3lep1tau/h_mll1"){
			signal500__channel = "signal500__t13l";
			signal600__channel = "signal600__t13l";
			signal700__channel = "signal700__t13l";
			signal800__channel = "signal800__t13l";
			signal900__channel = "signal900__t13l";
			signal1000__channel = "signal1000__t13l";
			signal1100__channel = "signal1100__t13l";
			signal1200__channel = "signal1200__t13l";
			signal1300__channel = "signal1300__t13l";
			signal1400__channel = "signal1400__t13l";
			prompt__channel = "prompt__t13l";
			one_fake__channel = "one_fake__t13l";
			prompt_red__channel = "prompt_red__t13l";
			fake__channel = "fake__t13l";
		}
		else if (hist_list[i] == "3lep2tau/h_mll1"){
			signal500__channel = "signal500__t23l";
			signal600__channel = "signal600__t23l";
			signal700__channel = "signal700__t23l";
			signal800__channel = "signal800__t23l";
			signal900__channel = "signal900__t23l";
			signal1000__channel = "signal1000__t23l";
			signal1100__channel = "signal1100__t23l";
			signal1200__channel = "signal1200__t23l";
			signal1300__channel = "signal1300__t23l";
			signal1400__channel = "signal1400__t23l";
			prompt__channel = "prompt__t23l";
			one_fake__channel = "one_fake__t23l";
			prompt_red__channel = "prompt_red__t23l";
			fake__channel = "fake__t23l";
		}

		TH1F* h_M500 = new TH1F(signal500__channel, "mll1", nbins, xmin, xmax);
		TH1F* h_M600 = new TH1F(signal600__channel, "mll1", nbins, xmin, xmax);
		TH1F* h_M700 = new TH1F(signal700__channel, "mll1", nbins, xmin, xmax);
		TH1F* h_M800 = new TH1F(signal800__channel, "mll1", nbins, xmin, xmax);
		TH1F* h_M900 = new TH1F(signal900__channel, "mll1", nbins, xmin, xmax);
		TH1F* h_M1000 = new TH1F(signal1000__channel, "mll1", nbins, xmin, xmax);
		TH1F* h_M1100 = new TH1F(signal1100__channel, "mll1", nbins, xmin, xmax);
		TH1F* h_M1200 = new TH1F(signal1200__channel, "mll1", nbins, xmin, xmax);
		TH1F* h_M1300 = new TH1F(signal1300__channel, "mll1", nbins, xmin, xmax);
		TH1F* h_M1400 = new TH1F(signal1400__channel, "mll1", nbins, xmin, xmax);		
		TH1F* h_prompt = new TH1F(prompt__channel, "mll1", nbins, xmin, xmax);						
		TH1F* h_fake = new TH1F(fake__channel, "mll1", nbins, xmin, xmax);	
		//TH1F* h_one_fake = new TH1F(one_fake__channel, "mll1", nbins, xmin, xmax);			
		//TH1F* h_prompt_red = new TH1F(prompt_red__channel, "mll1", nbins, xmin, xmax);			
		for(int j = 0; j < nfiles; j++){
			TFile *ifile = new TFile(filename[j],"READ");
			TH1F *h = (TH1F*)ifile->Get(hist_list[i]);
			if (h) h->Scale(applyXSec(ifile));
			
			if (sampleKind(filename[j],hist_list[i])== "M500") h_M500->Add(h);
			else if (sampleKind(filename[j],hist_list[i])== "M600") h_M600->Add(h);
			else if (sampleKind(filename[j],hist_list[i])== "M700") h_M700->Add(h);
			else if (sampleKind(filename[j],hist_list[i])== "M800") h_M800->Add(h);
			else if (sampleKind(filename[j],hist_list[i])== "M900") h_M900->Add(h);
			else if (sampleKind(filename[j],hist_list[i])== "M1000") h_M1000->Add(h);
			else if (sampleKind(filename[j],hist_list[i])== "M1100") h_M1100->Add(h);
			else if (sampleKind(filename[j],hist_list[i])== "M1200") h_M1200->Add(h);
			else if (sampleKind(filename[j],hist_list[i])== "M1300") h_M1300->Add(h);
			else if (sampleKind(filename[j],hist_list[i])== "M1400") h_M1400->Add(h);
			else if (sampleKind(filename[j],hist_list[i])== "fake") h_prompt->Add(h);
			else if (sampleKind(filename[j],hist_list[i])== "prompt") h_prompt->Add(h);
			else continue;
			cout<<sampleKind(filename[j],hist_list[i])<<";"<<filename[j]<<";"<<h->Integral()<<endl;
		}
		//setting overflow bins
		h_prompt->SetBinContent(nbins, h_prompt->GetBinContent(nbins+1));
		h_fake->SetBinContent(nbins, h_fake->GetBinContent(nbins+1));
		/*h_M500->Rebin(2);
		h_M600->Rebin(2);
		h_M700->Rebin(2);
		h_M800->Rebin(2);
		h_M900->Rebin(2);
		h_M1000->Rebin(2);
		h_M1100->Rebin(2);
		h_M1200->Rebin(2);
		h_M1300->Rebin(2);
		h_M1400->Rebin(2);
		h_prompt->Rebin(2);
		h_fake->Rebin(2);*/
		
		ofile->cd();
		h_M500->Write();
		h_M600->Write();
		//h_M700->Write();
		h_M800->Write();
		h_M900->Write();
		h_M1000->Write();
		h_M1100->Write();
		h_M1200->Write();
		h_M1300->Write();
		//h_M1400->Write();		
		h_prompt->Write();
		//h_one_fake->Write();
		//h_prompt_red->Write();
		h_fake->Write();

		std::cout << "Histograms added and saved" <<std::endl;
	}//file loop
}
