double XSec(std::string fname){
	if(fname.find("ttHTo2L2Nu") < fname.length()) return 0.5418;
	else if(fname.find("ttHToEE") < fname.length()) return 0;
	else if(fname.find("ttHToMuMu") < fname.length()) return 0.5269*0.000218;
	else if(fname.find("ttHToTauTau") < fname.length()) return 0.5269*0.0627;
	else if(fname.find("ttWJets") < fname.length()) return 0.4611;
	else if(fname.find("ttZJets") < fname.length()) return 0.5407;
	else if(fname.find("WJetsToLNu_NLO") < fname.length()) return 67350;
	else if(fname.find("WJetsToLNu_HT-70To100") < fname.length()) return  1264.0*1.1421;
	else if(fname.find("WJetsToLNu_HT-100To200") < fname.length()) return 1256.0*1.1421;
	else if(fname.find("WJetsToLNu_HT-200To400") < fname.length()) return 335.5*1.1421;
	else if(fname.find("WJetsToLNu_HT-400To600") < fname.length()) return 45.25*1.1421;
	else if(fname.find("WJetsToLNu_HT-600To800") < fname.length()) return 10.97*1.1421;
	else if(fname.find("WJetsToLNu_HT-800To1200") < fname.length()) return 4.933*1.1421;
	else if(fname.find("WJetsToLNu_HT-1200To2500") < fname.length()) return 1.160*1.1421;
	else if(fname.find("WJetsToLNu_HT-2500ToInf") < fname.length()) return 0.02624*1.1421;
	else if(fname.find("WWTo2L2Nu") < fname.length()) return 12.178;
	else if(fname.find("WWW_") < fname.length()) return 0.2086;
	else if(fname.find("WW_") < fname.length()) return 118.7;//75.8;
	else if(fname.find("WZTo2Q2L") < fname.length()) return 6.565;//6.204;
	else if(fname.find("WZTo3LNu") < fname.length()) return 5.257;//5.052;
	else if(fname.find("WZZ_") < fname.length()) return 0.05709;//0.05565;
	else if(fname.find("WZ_") < fname.length()) return 27.55;//0;
	else if(fname.find("ZHToMuMu") < fname.length()) return 0.7891*0.000218;
	else if(fname.find("ZHToTauTau") < fname.length()) return 0.7891*0.06256;
	else if(fname.find("ZZTo2L2Nu") < fname.length()) return 1.031;//1.325;
	else if(fname.find("ZZTo2Q2L") < fname.length()) return 6.788;//3.22;
	else if(fname.find("ZZTo4L") < fname.length()) return 1.390;//1.325;
	else if(fname.find("ZZZ_") < fname.length()) return 0.01476;//0.01398;
	else if(fname.find("GluGluZH_") < fname.length()) return 0.0616;
	else if(fname.find("DYJetsToLLM10to50") < fname.length()) return 15810;//18610;
	else if(fname.find("DYJetsToLLM50") < fname.length()) return 6077.22;
	else if(fname.find("ST_s-channel_") < fname.length()) return 10.4;//3.74;
	else if(fname.find("ST_t-channel_antitop_") < fname.length()) return 80.0;//69.09;
	else if(fname.find("ST_t-channel_top_") < fname.length()) return 134.2;//115.3;
	else if(fname.find("ST_tW_antitop_") < fname.length()) return 39.65;//35.85;
	else if(fname.find("ST_tW_top_") < fname.length()) return 39.65;//35.85;
	else if(fname.find("TTTo2L2Nu_") < fname.length()) return 88.51;
	else if(fname.find("TTToSemiLeptonic_") < fname.length()) return 366.29;
	else if(fname.find("TTToHadronic_") < fname.length()) return 378.93;
	else if(fname.find("HppM") < fname.length()) return 0.001;//Signal
	else if(fname.find("EGamma") < fname.length()) return 1;//Data
	else if(fname.find("Muon") < fname.length()) return 1;//Data
	else if(fname.find("Tau") < fname.length()) return 1;//Data
	else if(fname.find("Single") < fname.length()) return 1;//Data
	else{
		//std::cout<<"DON'T KNOW X-SEC FOR FILE "<<fname<<endl;
		return 0;
	}
}