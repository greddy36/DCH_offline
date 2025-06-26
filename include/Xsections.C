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
	else if(fname.find("WWTo2L2Nu") < fname.length() and fname.find("HZJ") > fname.length()) return 12.178;
	else if(fname.find("WWW_") < fname.length()) return 0.2086;
	else if(fname.find("WW_") < fname.length()) return 118.7;//75.8;
	else if(fname.find("WZTo2Q2L") < fname.length()) return 6.565;//6.204;
	else if(fname.find("WZTo3LNu") < fname.length()) return 5.257;//5.052;
	else if(fname.find("WZZ_") < fname.length()) return 0.05709;//0.05565;
	else if(fname.find("WZ_") < fname.length()) return 27.55;//0;
	else if(fname.find("ZHToMuMu") < fname.length()) return 0.7891*0.000218;
	else if(fname.find("ZHToTauTau") < fname.length()) return 0.7891*0.06256;
	else if(fname.find("ZZTo2L2Nu") < fname.length()) return 0.9738;
	else if(fname.find("ZZTo2Q2L") < fname.length()) return 3.698;
	else if(fname.find("ZZTo4L") < fname.length()) return 1.325;
	else if(fname.find("ZZZ_") < fname.length()) return 0.01476;//0.01398;
	else if(fname.find("GluGluZH_") < fname.length()) return 0.0616;
	else if(fname.find("DYJetsToLLM10to50") < fname.length()) return 18610;
	else if(fname.find("DYJetsToLLM50") < fname.length()) return 6077.22;
	else if(fname.find("ST_s-channel_") < fname.length()) return 10.4;//3.74;
	else if(fname.find("ST_t-channel_antitop_") < fname.length()) return 80.0;//69.09;
	else if(fname.find("ST_t-channel_top_") < fname.length()) return 134.2;//115.3;
	else if(fname.find("ST_tW_antitop_") < fname.length()) return 39.65;//35.85;
	else if(fname.find("ST_tW_top_") < fname.length()) return 39.65;//35.85;
	else if(fname.find("TTTo2L2Nu_") < fname.length()) return 88.51;
	else if(fname.find("TTToSemiLeptonic_") < fname.length()) return 366.29;
	else if(fname.find("TTToHadronic_") < fname.length()) return 378.93;
	else if(fname.find("ttHJetToNonbb") < fname.length()) return 0.24111;
	else if(fname.find("TWZToLL") < fname.length()) return 0.001669;
	else if(fname.find("HZJ") < fname.length()) return 0.00177;
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

double XSec_Uncert(std::string fname){//in %
	if(fname.find("ttHTo") < fname.length()) return 6.96;
	else if(fname.find("ttWJets") < fname.length()) return 7.47;
	else if(fname.find("ttZJets") < fname.length()) return 8.22;
	else if(fname.find("WW_") < fname.length()) return 5.77;
	else if(fname.find("WZTo2Q2L") < fname.length()) return 4.12;
	else if(fname.find("WZTo3LNu") < fname.length()) return 4.12;
	else if(fname.find("WZ_") < fname.length()) return 4.12;
	else if(fname.find("ZHToMuMu") < fname.length()) return 4.1;
	else if(fname.find("ZHToTauTau") < fname.length()) return 4.1;
	else if(fname.find("ZZTo2L2Nu") < fname.length()) return 4.41;
	else if(fname.find("ZZTo2Q2L") < fname.length()) return 4.41;
	else if(fname.find("ZZTo4L") < fname.length()) return 4.41;
	else if(fname.find("GluGluZH_") < fname.length()) return 4.1;
	else if(fname.find("DYJetsToLLM10to50") < fname.length()) return 0;
	else if(fname.find("DYJetsToLLM50") < fname.length()) return 2.49;
	else if(fname.find("ST_t-channel_antitop_") < fname.length()) return 18.82;
	else if(fname.find("ST_t-channel_top_") < fname.length()) return 14.29;
	else if(fname.find("ST_tW_antitop_") < fname.length()) return 11.05;
	else if(fname.find("ST_tW_top_") < fname.length()) return 11.05;
	else if(fname.find("TTTo") < fname.length()) return 3.19;
	else if(fname.find("WWW") < fname.length()) return 27.12;
	else if(fname.find("WZZ") < fname.length()) return 40.00;
	else{
		//std::cout<<"DON'T KNOW X-SEC FOR FILE "<<fname<<endl;
		return 0;
	}
}

double fake_uncert_squared(std::string lep_ch, std::string fname){//in relative value
	double quadr_uncert = 0;//needs more bkgs
	if(lep_ch == "3lep"){
		if(fname.find("DYJetsToLL") < fname.length()) return 0.03;
		else if(fname.find("TTTo2L2Nu") < fname.length()) return 0.03;
		else if(fname.find("TTToSemi") < fname.length()) return 0.03*0.03;
		else if(fname.find("TTToHadro") < fname.length()) return 0.03*0.03*0.03;
	}
	else if(lep_ch == "4lep"){
		if(fname.find("DYJetsToLL") < fname.length()) return 0.03*0.03;
		else if(fname.find("WZ") < fname.length() and fname.find("TWZ") > fname.length() and fname.find("WZZ") > fname.length()) return 0.03;
		else if(fname.find("TTTo2L2Nu") < fname.length()) return 0.03*.03;
		else if(fname.find("TTToSemi") < fname.length()) return 0.03*0.03*0.3;
		else if(fname.find("TTToHadro") < fname.length()) return 0.03*0.03*0.03*0.3;
	}
	return quadr_uncert;
}