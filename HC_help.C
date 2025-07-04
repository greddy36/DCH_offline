//prints the uncert that needs to be in the HC datacard
#include <TFile.h>
#include <TH1.h>
#include <TList.h>
#include "include/XSections.C"

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
			fname.find("ZH") < len )
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
			fname.find("ST_") < len)
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
			fname.find("HZJ") < len ||
			fname.find("ttH") < len ||
			fname.find("ttZ") < len ||
			fname.find("ZH") < len ||
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
			fname.find("ST_") < len)
			return "fake";
		else if (fname.find("EGamma") < len || fname.find("Single") < len)
			return "data";
		else return "BLABLA in 3lep";
	}
}
void HC_help(const char* ext = "2018.root"){
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
	const char *hist_list[] = {"0tau/h_mTtot1","1tau/h_mTtot1","2tau/h_mTtot1","3tau/h_mTtot1","3lep0tau/h_mTtot1","3lep1tau/h_mTtot1","3lep2tau/h_mTtot1"};
	for(int i = 0; i < sizeof(hist_list)/sizeof(hist_list[0]); i++){
		std::string hist_name = hist_list[i];
		for(int j = 0; j < nfiles; j++){
			TFile *ifile = new TFile(filename[j],"READ");
			TH1D* h = (TH1D*)ifile->Get(hist_name.c_str());
			if (h) {
                	double sys_err = h->Integral()*XSec_Uncert(ifile->GetName())/100;
					//if (sampleKind(filename[j],hist_list[i]) == "prompt") cout<<"XSprompt"<<"\t"<<filename[j]<<"\t"<<hist_list[i]<<"\t"<< h->Integral()<<"\t"<<sys_err*sys_err<<endl;
					//if (sampleKind(filename[j],hist_list[i]) == "fake") cout<<"XSfake"<<"\t"<<filename[j]<<"\t"<<hist_list[i]<<"\t"<< h->Integral()<<"\t"<<sys_err*sys_err<<endl;
					
					std::string hist_name = hist_list[i];
					if (sampleKind(filename[j],hist_list[i]) == "fake"){
						if (hist_name.find("3lep") > hist_name.length())//4lep
							cout<<"fakeNorm"<<"\t"<<filename[j]<<"\t"<<hist_list[i]<<"\t"<< h->Integral()<<"\t"<<fake_uncert_squared("4lep", ifile->GetName())<<endl;
						else if (hist_name.find("3lep") < hist_name.length())//3lep
							cout<<"fakeNorm"<<"\t"<<filename[j]<<"\t"<<hist_list[i]<<"\t"<< h->Integral()<<"\t"<<fake_uncert_squared("3lep", ifile->GetName())<<endl;
						
					}
			}
		}
		cout<<""<<endl;
	}
}
