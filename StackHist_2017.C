#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>

void StackHist_2017() {
	TFile *ifile_sig = new TFile("hist_test_nopair/WW_2017.root","READ");               
	TFile *ifile_DY1 = new TFile("hist_test_nopair/DYJetsToLLM10to50_2017.root","READ");     
	TFile *ifile_DY2 = new TFile("hist_test_nopair/DYJetsToLLM50_2017.root","READ"); 
		    
	//TFile *ifile_VV1 = new TFile("hist_test_nopair/WGToLNuG_2017.root","READ");
	TFile *ifile_VV2 = new TFile("hist_test_nopair/WW_2017.root","READ");
	TFile *ifile_VV3 = new TFile("hist_test_nopair/WWTo2L2Nu_2017.root","READ");
	//TFile *ifile_VV4 = new TFile("hist_test_nopair/WZ_2017.root","READ");
	TFile *ifile_VV5 = new TFile("hist_test_nopair/WZTo2Q2L_2017.root","READ");
	TFile *ifile_VV6 = new TFile("hist_test_nopair/WZTo3LNu_2017.root","READ");

	TFile *ifile_VVV1 = new TFile("hist_test_nopair/WWW_2017.root","READ");
	TFile *ifile_VVV2 = new TFile("hist_test_nopair/WZZ_2017.root","READ");
	TFile *ifile_VVV3 = new TFile("hist_test_nopair/ZZZ_2017.root","READ");

	TFile *ifile_ttV1 = new TFile("hist_test_nopair/ttWJets_2017.root","READ");
	TFile *ifile_ttV2 = new TFile("hist_test_nopair/ttZJets_2017.root","READ");
	
	TFile *ifile_WJ1 = new TFile("hist_test_nopair/WJetsToLNu_NLO_2017.root","READ");
	TFile *ifile_WJ2 = new TFile("hist_test_nopair/WJetsToLNu_HT-70To100_2017.root","READ");
	TFile *ifile_WJ3 = new TFile("hist_test_nopair/WJetsToLNu_HT-100To200_2017.root","READ");
	TFile *ifile_WJ4 = new TFile("hist_test_nopair/WJetsToLNu_HT-200To400_2017.root","READ");
	TFile *ifile_WJ5 = new TFile("hist_test_nopair/WJetsToLNu_HT-400To600_2017.root","READ");
	TFile *ifile_WJ6 = new TFile("hist_test_nopair/WJetsToLNu_HT-600To800_2017.root","READ");
	TFile *ifile_WJ7 = new TFile("hist_test_nopair/WJetsToLNu_HT-800To1200_2017.root","READ");
	//TFile *ifile_WJ8 = new TFile("hist_test_nopair/WJetsToLNu_HT-1200To2500_2017.root","READ");
	//TFile *ifile_WJ9 = new TFile("hist_test_nopair/WJetsToLNu_HT-2500ToInf_2017.root","READ");
	
	TFile *ifile_ZZ1 = new TFile("hist_test_nopair/ZZTo2L2Nu_2017.root","READ");
	TFile *ifile_ZZ2 = new TFile("hist_test_nopair/ZZTo2Q2L_2017.root","READ");
	TFile *ifile_ZZ3 = new TFile("hist_test_nopair/ZZTo4L_2017.root","READ");

	TFile *ifile_ST1 = new TFile("hist_test_nopair/ST_s-channel_2017.root","READ");          
	TFile *ifile_ST2 = new TFile("hist_test_nopair/ST_t-channel_antitop_2017.root","READ");  
	TFile *ifile_ST3 = new TFile("hist_test_nopair/ST_t-channel_top_2017.root","READ");  
	TFile *ifile_ST4 = new TFile("hist_test_nopair/ST_tW_antitop_2017.root","READ");  
	TFile *ifile_ST5 = new TFile("hist_test_nopair/ST_tW_top_2017.root","READ");            

	//TFile *ifile_ttH1 = new TFile("hist_test_nopair/ttHTo2L2Nu_2017.root","READ");
	//TFile *ifile_ttH2 = new TFile("hist_test_nopair/ttHToEE_2017.root","READ");
	//TFile *ifile_ttH3 = new TFile("hist_test_nopair/ttHToMuMu_2017.root","READ");
	TFile *ifile_ttH4 = new TFile("hist_test_nopair/ttHToTauTau_2017.root","READ");
	
	TFile *ifile_TTbar1 = new TFile("hist_test_nopair/TTTo2L2Nu_2017.root","READ");
	TFile *ifile_TTbar2 = new TFile("hist_test_nopair/TTToSemiLeptonic_2017.root","READ");
	TFile *ifile_TTbar3 = new TFile("hist_test_nopair/TTToHadronic_2017.root","READ");
	
	TFile *ifile_ZH1 = new TFile("hist_test_nopair/ZHToMuMu_2017.root","READ");
	//TFile *ifile_ZH2 = new TFile("hist_test_nopair/ZHToTauTau_2017.root","READ");
	TFile *ifile_ZH3 = new TFile("hist_test_nopair/GluGluZH_2017.root","READ");
	
	TFile *ifile_D1 = new TFile("hist_test_nopair/SingleElectron_2017.root","READ");
	//TFile *ifile_D2 = new TFile("hist_test_nopair/DoubleMuon_2017.root","READ");
	//TFile *ifile_D3 = new TFile("hist_test_nopair/Tau_2017.root","READ");
	//TFile *ifile_D4 = new TFile("hist_test_nopair/MuonEG_2017.root","READ");
	TFile *ifile_D5 = new TFile("hist_test_nopair/SingleMuon_2017.root","READ");

	//float nEvents = 

	/*const char *hist_list[] = {"cutflow","h_Xmass_0t","h_Xmass_1t","h_Xmass_2t", "h_Xmass_34t", "h_ST", "h_ll1_pt_4L","h_ll1_pt_3L","h_mZ1", "h_mZ2","h_mZ3","h_mZ4","h_mZ1_3L", "h_mZ2_3L","h_mZ3_3L","h_mZ4_3L","h_met","h_pT1","h_pT2","h_pT3","h_pT4","h_dR","h_dRll","h_dRll2"};*/
	
	/*const char *hist_names[] = {"Cutflow","mll1 in Z(e+e-) + l region","mll1 in Z(m+m-) + l region", "mll1 in Z-veto(e+e-) + l region", "mll1 in Z-veto(m+m-) + l region", "ST", "Leading pair pT in 4L","Leading pair pT in 3L","Z mass from pair (1,3) in 4L", "Z mass from pair (1,4) in 4L","Z mass from pair (2,3) in 4L","Z mass from pair (2,4) in 4L", "Z mass from pair (1,3) in 3L", "Z mass from pair (1,4) in 3L","Z mass from pair (2,3)","Z mass from pair (2,4)","MET","Leading pT","Sub-Leading pT","3rd pT","4th pT","dR (+-) leptons; DR; Events","dR between 1st pair", "dR between 2nd pair"};*/


	const char *hist_list[] = {
"h_mZ1","h_mZ2","h_mZ3","h_mZ4","h_mZ5","h_mZ6","h_mZ7","h_mZ8","h_mZ9","h_mZ10","h_mZ11","h_mZ12","h_mZ13","h_mZ14","h_mZ15","h_mZ16","h_mZ17",

"h_mZv1","h_mZv2","h_mZv3","h_mZv4","h_mZv5","h_mZv6","h_mZv7","h_mZv8","h_mZv9","h_mZv10","h_mZv11","h_mZv12","h_mZv13","h_mZv14","h_mZv15","h_mZv16","h_mZv17",

"h_mH1","h_mH2","h_mH3","h_mH4","h_mH5","h_mH6","h_mH7","h_mH8","h_mH9","h_mH10","h_mH11","h_mH12","h_mH13","h_mH14","h_mH15","h_mH16","h_mH17",

"h_mHv1","h_mHv2","h_mHv3","h_mHv4","h_mHv5","h_mHv6","h_mHv7","h_mHv8","h_mHv9","h_mHv10","h_mHv11","h_mHv12","h_mHv13","h_mHv14","h_mHv15","h_mHv16","h_mHv17",
 
"h_met1","h_met2","h_met3","h_met4","h_met5","h_met6","h_met7","h_met8","h_met9","h_met10","h_met11","h_met12","h_met13","h_met14","h_met15","h_met16","h_met17",

"h_metv1","h_metv2","h_metv3","h_metv4","h_metv5","h_metv6","h_metv7","h_metv8","h_metv9","h_metv10","h_metv11","h_metv12","h_metv13","h_metv14","h_metv15","h_metv16","h_metv17",

"h_pt11", "h_pt21","h_pt31","h_pt41","h_pt12", "h_pt22","h_pt32","h_pt42","h_pt13", "h_pt23","h_pt33","h_pt43","h_pt14", "h_pt24","h_pt34","h_pt44","h_pt15", "h_pt25","h_pt35","h_pt45","h_pt16", "h_pt26","h_pt36","h_pt46","h_pt17", "h_pt27","h_pt37","h_pt47","h_pt17", "h_pt28","h_pt38","h_pt48","h_pt19", "h_pt29","h_pt39","h_pt49","h_pt110", "h_pt210","h_pt310","h_pt410","h_pt111", "h_pt211","h_pt311","h_pt411","h_pt112", "h_pt212","h_pt312","h_pt412","h_pt113", "h_pt213","h_pt313","h_pt413","h_pt114","h_pt214","h_pt314","h_pt414","h_pt115","h_pt215","h_pt315","h_pt415","h_pt116","h_pt216","h_pt316","h_pt416","h_pt117","h_pt217","h_pt317","h_pt417",

"h_pt1v1", "h_pt2v1","h_pt3v1","h_pt4v1","h_pt1v2", "h_pt2v2","h_pt3v2","h_pt4v2","h_pt1v3", "h_pt2v3","h_pt3v3","h_pt4v3","h_pt1v4", "h_pt2v4","h_pt3v4","h_pt4v4","h_pt1v5", "h_pt2v5","h_pt3v5","h_pt4v5","h_pt1v6", "h_pt2v6","h_pt3v6","h_pt4v6","h_pt1v7", "h_pt2v7","h_pt3v7","h_pt4v7","h_pt1v8", "h_pt2v8","h_pt3v8","h_pt4v8","h_pt1v9", "h_pt2v9","h_pt3v9","h_pt4v9","h_pt1v10", "h_pt2v10","h_pt3v10","h_pt4v10","h_pt1v11","h_pt2v11","h_pt3v11","h_pt4v11","h_pt1v12", "h_pt2v12","h_pt3v12","h_pt4v12","h_pt1v13", "h_pt2v13","h_pt3v13","h_pt4v13","h_pt1v14","h_pt2v14","h_pt3v14","h_pt4v14","h_pt1v15","h_pt2v15","h_pt3v15","h_pt4v15","h_pt1v16","h_pt2v16","h_pt3v16","h_pt4v16","h_pt1v17","h_pt2v17","h_pt3v17","h_pt4v17",

"h_eta11", "h_eta21","h_eta31","h_eta41","h_eta12", "h_eta22","h_eta32","h_eta42","h_eta13", "h_eta23","h_eta33","h_eta43","h_eta14", "h_eta24","h_eta34","h_eta44","h_eta15", "h_eta25","h_eta35","h_eta45","h_eta16", "h_eta26","h_eta36","h_eta46","h_eta17", "h_eta27","h_eta37","h_eta47","h_eta18", "h_eta28","h_eta38","h_eta48","h_eta19", "h_eta29","h_eta39","h_eta49","h_eta110", "h_eta210","h_eta310","h_eta410","h_eta111", "h_eta211","h_eta311","h_eta411","h_eta112", "h_eta212","h_eta312","h_eta412","h_eta113", "h_eta213","h_eta313","h_eta413","h_eta114","h_eta214","h_eta314","h_eta414","h_eta115","h_eta215","h_eta315","h_eta415","h_eta116","h_eta216","h_eta316","h_eta416","h_eta117","h_eta217","h_eta317","h_eta417",


"h_eta1v1", "h_eta2v1","h_eta3v1","h_eta4v1","h_eta1v2", "h_eta2v2","h_eta3v2","h_eta4v2","h_eta1v3", "h_eta2v3","h_eta3v3","h_eta4v3","h_eta1v4", "h_eta2v4","h_eta3v4","h_eta4v4","h_eta1v5", "h_eta2v5","h_eta3v5","h_eta4v5","h_eta1v6", "h_eta2v6","h_eta3v6","h_eta4v6","h_eta1v7", "h_eta2v7","h_eta3v7","h_eta4v7","h_eta1v8", "h_eta2v8","h_eta3v8","h_eta4v8","h_eta1v9", "h_eta2v9","h_eta3v9","h_eta4v9","h_eta1v10", "h_eta2v10","h_eta3v10","h_eta4v10","h_eta1v11","h_eta2v11","h_eta3v11","h_eta4v11","h_eta1v12", "h_eta2v12","h_eta3v12","h_eta4v12","h_eta1v13", "h_eta2v13","h_eta3v13","h_eta4v13","h_eta1v14","h_eta2v14","h_eta3v14","h_eta4v14","h_eta1v15","h_eta2v15","h_eta3v15","h_eta4v15","h_eta1v16","h_eta2v16","h_eta3v16","h_eta4v16","h_eta1v17","h_eta2v17","h_eta3v17","h_eta4v17",

"h_phi11", "h_phi21","h_phi31","h_phi41","h_phi12", "h_phi22","h_phi32","h_phi42","h_phi13", "h_phi23","h_phi33","h_phi43","h_phi14", "h_phi24","h_phi34","h_phi44","h_phi15", "h_phi25","h_phi35","h_phi45","h_phi16", "h_phi26","h_phi36","h_phi46","h_phi17", "h_phi27","h_phi37","h_phi47","h_phi18", "h_phi28","h_phi38","h_phi48","h_phi19", "h_phi29","h_phi39","h_phi49","h_phi110", "h_phi210","h_phi310","h_phi410","h_phi111", "h_phi211","h_phi311","h_phi411","h_phi112", "h_phi212","h_phi312","h_phi412","h_phi113", "h_phi213","h_phi313","h_phi413","h_phi114","h_phi214","h_phi314","h_phi414","h_phi115","h_phi215","h_phi315","h_phi415","h_phi116","h_phi216","h_phi316","h_phi416","h_phi117","h_phi217","h_phi317","h_phi417",

"h_phi1v1", "h_phi2v1","h_phi3v1","h_phi4v1","h_phi1v2", "h_phi2v2","h_phi3v2","h_phi4v2","h_phi1v3", "h_phi2v3","h_phi3v3","h_phi4v3","h_phi1v4", "h_phi2v4","h_phi3v4","h_phi4v4","h_phi1v5", "h_phi2v5","h_phi3v5","h_phi4v5","h_phi1v6", "h_phi2v6","h_phi3v6","h_phi4v6","h_phi1v7", "h_phi2v7","h_phi3v7","h_phi4v7","h_phi1v8", "h_phi2v8","h_phi3v8","h_phi4v8","h_phi1v9", "h_phi2v9","h_phi3v9","h_phi4v9","h_phi1v10", "h_phi2v10","h_phi3v10","h_phi4v10","h_phi1v11","h_phi2v11","h_phi3v11","h_phi4v11","h_phi1v12", "h_phi2v12","h_phi3v12","h_phi4v12","h_phi1v13", "h_phi2v13","h_phi3v13","h_phi4v13","h_phi1v14","h_phi2v14","h_phi3v14","h_phi4v14","h_phi1v15","h_phi2v15","h_phi3v15","h_phi4v15","h_phi1v16","h_phi2v16","h_phi3v16","h_phi4v16","h_phi1v17","h_phi2v17","h_phi3v17","h_phi4v17",

"h_dxy11", "h_dxy21","h_dxy31","h_dxy41","h_dxy12", "h_dxy22","h_dxy32","h_dxy42","h_dxy13", "h_dxy23","h_dxy33","h_dxy43","h_dxy14", "h_dxy24","h_dxy34","h_dxy44","h_dxy15", "h_dxy25","h_dxy35","h_dxy45","h_dxy16", "h_dxy26","h_dxy36","h_dxy46","h_dxy17", "h_dxy27","h_dxy37","h_dxy47","h_dxy17", "h_dxy28","h_dxy38","h_dxy48","h_dxy19", "h_dxy29","h_dxy39","h_dxy49","h_dxy110", "h_dxy210","h_dxy310","h_dxy410","h_dxy111","h_dxy211","h_dxy311","h_dxy411","h_dxy112", "h_dxy212","h_dxy312","h_dxy412","h_dxy113", "h_dxy213","h_dxy313","h_dxy413","h_dxy114","h_dxy214","h_dxy314","h_dxy414","h_dxy115","h_dxy215","h_dxy315","h_dxy415","h_dxy116","h_dxy216","h_dxy316","h_dxy416","h_dxy117","h_dxy217","h_dxy317","h_dxy417",

"h_dxy1v1", "h_dxy2v1","h_dxy3v1","h_dxy4v1","h_dxy1v2", "h_dxy2v2","h_dxy3v2","h_dxy4v2","h_dxy1v3", "h_dxy2v3","h_dxy3v3","h_dxy4v3","h_dxy1v4", "h_dxy2v4","h_dxy3v4","h_dxy4v4","h_dxy1v5", "h_dxy2v5","h_dxy3v5","h_dxy4v5","h_dxy1v6", "h_dxy2v6","h_dxy3v6","h_dxy4v6","h_dxy1v7", "h_dxy2v7","h_dxy3v7","h_dxy4v7","h_dxy1v8", "h_dxy2v8","h_dxy3v8","h_dxy4v8","h_dxy1v9", "h_dxy2v9","h_dxy3v9","h_dxy4v9","h_dxy1v10", "h_dxy2v10","h_dxy3v10","h_dxy4v10","h_dxy1v11","h_dxy2v11","h_dxy3v11","h_dxy4v11","h_dxy1v12", "h_dxy2v12","h_dxy3v12","h_dxy4v12","h_dxy1v13", "h_dxy2v13","h_dxy3v13","h_dxy4v13","h_dxy1v14","h_dxy2v14","h_dxy3v14","h_dxy4v14","h_dxy1v15","h_dxy2v15","h_dxy3v15","h_dxy4v15","h_dxy1v16","h_dxy2v16","h_dxy3v16","h_dxy4v16","h_dxy1v17","h_dxy2v17","h_dxy3v17","h_dxy4v17",

"h_dZ11", "h_dZ21","h_dZ31","h_dZ41","h_dZ12", "h_dZ22","h_dZ32","h_dZ42","h_dZ13", "h_dZ23","h_dZ33","h_dZ43","h_dZ14", "h_dZ24","h_dZ34","h_dZ44","h_dZ15", "h_dZ25","h_dZ35","h_dZ45","h_dZ16", "h_dZ26","h_dZ36","h_dZ46","h_dZ17", "h_dZ27","h_dZ37","h_dZ47","h_dZ18", "h_dZ28","h_dZ38","h_dZ48","h_dZ19", "h_dZ29","h_dZ39","h_dZ49","h_dZ110", "h_dZ210","h_dZ310","h_dZ410","h_dZ111","h_dZ211","h_dZ311","h_dZ411","h_dZ112", "h_dZ212","h_dZ312","h_dZ412","h_dZ113", "h_dZ213","h_dZ313","h_dZ413","h_dZ114","h_dZ214","h_dZ314","h_dZ414","h_dZ115","h_dZ215","h_dZ315","h_dZ415","h_dZ116","h_dZ216","h_dZ316","h_dZ416","h_dZ117","h_dZ217","h_dZ317","h_dZ417",

"h_dZ1v1", "h_dZ2v1","h_dZ3v1","h_dZ4v1","h_dZ1v2", "h_dZ2v2","h_dZ3v2","h_dZ4v2","h_dZ1v3", "h_dZ2v3","h_dZ3v3","h_dZ4v3","h_dZ1v4", "h_dZ2v4","h_dZ3v4","h_dZ4v4","h_dZ1v5", "h_dZ2v5","h_dZ3v5","h_dZ4v5","h_dZ1v6", "h_dZ2v6","h_dZ3v6","h_dZ4v6","h_dZ1v7", "h_dZ2v7","h_dZ3v7","h_dZ4v7","h_dZ1v8", "h_dZ2v8","h_dZ3v8","h_dZ4v8","h_dZ1v9", "h_dZ2v9","h_dZ3v9","h_dZ4v9","h_dZ1v10", "h_dZ2v10","h_dZ3v10","h_dZ4v10","h_dZ1v11","h_dZ2v11","h_dZ3v11","h_dZ4v11","h_dZ1v12", "h_dZ2v12","h_dZ3v12","h_dZ4v12","h_dZ1v13", "h_dZ2v13","h_dZ3v13","h_dZ4v13","h_dZ1v14","h_dZ2v14","h_dZ3v14","h_dZ4v14","h_dZ1v15","h_dZ2v15","h_dZ3v15","h_dZ4v15","h_dZ1v16","h_dZ2v16","h_dZ3v16","h_dZ4v16","h_dZ1v17","h_dZ2v17","h_dZ3v17","h_dZ4v17",


"h_iso11", "h_iso21","h_iso31","h_iso41","h_iso12", "h_iso22","h_iso32","h_iso42","h_iso13", "h_iso23","h_iso33","h_iso43","h_iso14", "h_iso24","h_iso34","h_iso44","h_iso15", "h_iso25","h_iso35","h_iso45","h_iso16", "h_iso26","h_iso36","h_iso46","h_iso17", "h_iso27","h_iso37","h_iso47","h_iso18", "h_iso28","h_iso38","h_iso48","h_iso19", "h_iso29","h_iso39","h_iso49","h_iso110", "h_iso210","h_iso310","h_iso410","h_iso111","h_iso211","h_iso311","h_iso411","h_iso112", "h_iso212","h_iso312","h_iso412","h_iso113", "h_iso213","h_iso313","h_iso413","h_iso114","h_iso214","h_iso314","h_iso414","h_iso115","h_iso215","h_iso315","h_iso415","h_iso116","h_iso216","h_iso316","h_iso416","h_iso117","h_iso217","h_iso317","h_iso417",

"h_iso1v1", "h_iso2v1","h_iso3v1","h_iso4v1","h_iso1v2", "h_iso2v2","h_iso3v2","h_iso4v2","h_iso1v3", "h_iso2v3","h_iso3v3","h_iso4v3","h_iso1v4", "h_iso2v4","h_iso3v4","h_iso4v4","h_iso1v5", "h_iso2v5","h_iso3v5","h_iso4v5","h_iso1v6", "h_iso2v6","h_iso3v6","h_iso4v6","h_iso1v7", "h_iso2v7","h_iso3v7","h_iso4v7","h_iso1v8", "h_iso2v8","h_iso3v8","h_iso4v8","h_iso1v9", "h_iso2v9","h_iso3v9","h_iso4v9","h_iso1v10", "h_iso2v10","h_iso3v10","h_iso4v10","h_iso1v11","h_iso2v11","h_iso3v11","h_iso4v11","h_iso1v12", "h_iso2v12","h_iso3v12","h_iso4v12","h_iso1v13", "h_iso2v13","h_iso3v13","h_iso4v13","h_iso1v14","h_iso2v14","h_iso3v14","h_iso4v14","h_iso1v15","h_iso2v15","h_iso3v15","h_iso4v15","h_iso1v16","h_iso2v16","h_iso3v16","h_iso4v16","h_iso1v17","h_iso2v17","h_iso3v17","h_iso4v17",

	};
	
	const char *hist_names[] = {
	"mZ (e+e- & e) in Z-window","mZ (e+e- & m) in Z-window","mZ (m+m- & e) in Z-window","mZ (m+m- & m) in Z-window","mZ (e+e- & e+e-) in Z-window","mZ (e+e- & em) in Z-window","mZ (e+e- & m+m-) in Z-window","mZ (emt) in Z-window","mZ (m+m- & em) in Z-window","mZ (m+m- & m+m-) in Z-window","mZ (e+e-) in Z-window","mZ (e m) in Z-window","mZ (m+m-) in Z-window","mZ (e+e- & t) in Z-window","mZ (m+m- & t) in Z-window","mZ (ett) in Z-window","mZ (mtt) in Z-window",
	
	"mZ (e+e- & e) in Z-veto","mZ (e+e- & m) in Z-veto","mZ (m+m- & e) in Z-veto","mZ (m+m- & m) in Z-veto","mZ (e+e- & e+e-) in Z-veto","mZ (e+e- & em) in Z-veto","mZ (e+e- & m+m-) in Z-veto","mZ (emt) in Z-veto","mZ (m+m- & em) in Z-veto","mZ (m+m- & m+m-) in Z-veto","mZ (e+e-) in Z-veto","mZ (e m) in Z-veto","mZ (m+m-) in Z-veto","mZ (e+e- & t) in Z-veto","mZ (m+m- & t) in Z-veto","mZ (ett) in Z-veto","mZ (mtt) in Z-veto",
	
	"mH (e+e- & e) in Z-window","mH (e+e- & m) in Z-window","mH (m+m- & e) in Z-window","mH (m+m- & m) in Z-window","mH (e+e- & e+e-) in Z-window","mH (e+e- & em) in Z-window","mH (e+e- & m+m-) in Z-window","mH (emt) in Z-window","mH (m+m- & em) in Z-window","mH (m+m- & m+m-) in Z-window","mH (e+e-) in Z-window","mH (e m) in Z-window","mH (m+m-) in Z-window","mH (e+e- & t) in Z-window","mH (m+m- & t) in Z-window","mH (ett) in Z-window","mH (mtt) in Z-window",
	
	"mH (e+e- & e) in Z-veto","mH (e+e- & m) in Z-veto","mH (m+m- & e) in Z-veto","mH (m+m- & m) in Z-veto","mH (e+e- & e+e-) in Z-veto","mH (e+e- & em) in Z-veto","mH (e+e- & m+m-) in Z-veto","mH (emt) in Z-veto","mH (m+m- & em) in Z-veto","mH (m+m- & m+m-) in Z-veto","mH (e+e-) in Z-veto","mH (e m) in Z-veto","mH (m+m-) in Z-veto","mH (e+e- & t) in Z-veto","mH (m+m- & t) in Z-veto","mH (ett) in Z-veto","mH (mtt) in Z-veto",
	
	"MET (e+e- & e) in Z-window","MET (e+e- & m) in Z-window","MET (m+m- & e) in Z-window","MET (m+m- & m) in Z-window","MET (e+e- & e+e-) in Z-window","MET (e+e- & em) in Z-window","MET (e+e- & m+m-) in Z-window","MET (emt) in Z-window","MET (m+m- & em) in Z-window","MET (m+m- & m+m-) in Z-window","MET (e+e-) in Z-window","MET (e m) in Z-window","MET (m+m-) in Z-window","MET (e+e- & t) in Z-window","MET (m+m- & t) in Z-window","MET (ett) in Z-window","MET (mtt) in Z-window",
	
	"MET (e+e- & e) in Z-veto","MET (e+e- & m) in Z-veto","MET (m+m- & e) in Z-veto","MET (m+m- & m) in Z-veto","MET (e+e- & e+e-) in Z-veto","MET (e+e- & em) in Z-veto","MET (e+e- & m+m-) in Z-veto","MET (emt) in Z-veto","MET (m+m- & em) in Z-veto","MET (m+m- & m+m-) in Z-veto","MET (e+e-) in Z-veto","MET (e m) in Z-veto","MET (m+m-) in Z-veto","MET (e+e- & t) in Z-veto","MET (m+m- & t) in Z-veto","MET (ett) in Z-veto","MET (mtt) in Z-veto",
	
	"pT1 (e+e- & e) in Z-window","pT2 (e+e- & e) in Z-window","pT3 (e+e- & e) in Z-window","pT4 (e+e- & e) in Z-window",
	"pT1 (e+e- & m) in Z-window","pT2 (e+e- & m) in Z-window","pT3 (e+e- & m) in Z-window","pT4 (e+e- & m) in Z-window",
	"pT1 (m+m- & e) in Z-window","pT2 (m+m- & e) in Z-window","pT3 (m+m- & e) in Z-window","pT4 (m+m- & e) in Z-window",
	"pT1 (m+m- & m) in Z-window","pT2 (m+m- & m) in Z-window","pT3 (m+m- & m) in Z-window","pT4 (m+m- & m) in Z-window",
	"pT1 (e+e- & e+e-) in Z-window","pT2 (e+e- & e+e-) in Z-window","pT3 (e+e- & e+e-) in Z-window","pT4 (e+e- & e+e-) in Z-window",
	"pT1 (e+e- & em) in Z-window","pT2 (e+e- & em) in Z-window","pT3 (e+e- & em) in Z-window","pT4 (e+e- & em) in Z-window",
	"pT1 (e+e- & m+m-) in Z-window","pT2 (e+e- & m+m-) in Z-window","pT3 (e+e- & m+m-) in Z-window","pT4 (e+e- & m+m-) in Z-window",
	"pT1 (emt) in Z-window","pT2 (emt) in Z-window","pT3 (emt) in Z-window","pT4 (emt) in Z-window",
	"pT1 (m+m- & em) in Z-window","pT2 (m+m- & em) in Z-window","pT3 (m+m- & em) in Z-window","pT4 (m+m- & em) in Z-window",
	"pT1 (m+m- & m+m-) in Z-window","pT2 (m+m- & m+m-) in Z-window","pT3 (m+m- & m+m-) in Z-window","pT4 (m+m- & m+m-) in Z-window",
	"pT1 (e+e-) in Z-window","pT2 (e+e-) in Z-window","pT3 (e+e-) in Z-window","pT4 (e+e-) in Z-window",
	"pT1 (e m) in Z-window","pT2 (e m) in Z-window","pT3 (e m) in Z-window","pT4 (e m) in Z-window",
	"pT1 (m+m-) in Z-window","pT2 (m+m-) in Z-window","pT3 (m+m-) in Z-window","pT4 (m+m-) in Z-window",
	"pT1 (e+e- & t) in Z-window","pT2 (e+e- & t) in Z-window","pT3 (e+e- & t) in Z-window","pT4 (e+e- & t) in Z-window",
	"pT1 (m+m- & t) in Z-window","pT2 (m+m- & t) in Z-window","pT3 (m+m- & t) in Z-window","pT4 (m+m- & t) in Z-window",
	"pT1 (ett) in Z-window","pT2 (ett) in Z-window","pT3 (ett) in Z-window","pT4 (ett) in Z-window",
	"pT1 (mtt) in Z-window","pT2 (mtt) in Z-window","pT3 (mtt) in Z-window","pT4 (mtt) in Z-window",
	
	
	"pT1 (e+e- & e) in Z-veto","pT2 (e+e- & e) in Z-veto","pT3 (e+e- & e) in Z-veto","pT4 (e+e- & e) in Z-veto",
	"pT1 (e+e- & m) in Z-veto","pT2 (e+e- & m) in Z-veto","pT3 (e+e- & m) in Z-veto","pT4 (e+e- & m) in Z-veto",
	"pT1 (m+m- & e) in Z-veto","pT2 (m+m- & e) in Z-veto","pT3 (m+m- & e) in Z-veto","pT4 (m+m- & e) in Z-veto",
	"pT1 (m+m- & m) in Z-veto","pT2 (m+m- & m) in Z-veto","pT3 (m+m- & m) in Z-veto","pT4 (m+m- & m) in Z-veto",
	"pT1 (e+e- & e) in Z-veto","pT2 (e+e- & e+e-) in Z-veto","pT3 (e+e- & e+e-) in Z-veto","pT4 (e+e- & e+e-) in Z-veto",
	"pT1 (e+e- & em) in Z-veto","pT2 (e+e- & em) in Z-veto","pT3 (e+e- & em) in Z-veto","pT4 (e+e- & em) in Z-veto",
	"pT1 (e+e- & m+m-) in Z-veto","pT2 (e+e- & m+m-) in Z-veto","pT3 (e+e- & m+m-) in Z-veto","pT4 (e+e- & m+m-) in Z-veto",
	"pT1 (emt) in Z-veto","pT2 (emt) in Z-veto","pT3 (emt) in Z-veto","pT4 (emt) in Z-veto",
	"pT1 (m+m- & em) in Z-veto","pT2 (m+m- & em) in Z-veto","pT3 (m+m- & em) in Z-veto","pT4 (m+m- & em) in Z-veto",
	"pT1 (m+m- & m+m-) in Z-veto","pT2 (m+m- & m+m-) in Z-veto","pT3 (m+m- & m+m-) in Z-veto","pT4 (m+m- & m+m-) in Z-veto",
	"pT1 (e+e-) in Z-veto","pT2 (e+e-) in Z-veto","pT3 (e+e-) in Z-veto","pT4 (e+e-) in Z-veto",
	"pT1 (e m) in Z-veto","pT2 (e m) in Z-veto","pT3 (e m) in Z-veto","pT4 (e m) in Z-veto",
	"pT1 (m+m-) in Z-veto","pT2 (m+m-) in Z-veto","pT3 (m+m-) in Z-veto","pT4 (m+m-) in Z-veto",
	"pT1 (e+e- & t) in Z-veto","pT2 (e+e- & t) in Z-veto","pT3 (e+e- & t) in Z-veto","pT4 (e+e- & t) in Z-veto",
	"pT1 (m+m- & t) in Z-veto","pT2 (m+m- & t) in Z-veto","pT3 (m+m- & t) in Z-veto","pT4 (m+m- & t) in Z-veto",
	"pT1 (ett) in Z-veto","pT2 (ett) in Z-veto","pT3 (ett) in Z-veto","pT4 (ett) in Z-veto",
	"pT1 (mtt) in Z-veto","pT2 (mtt) in Z-veto","pT3 (mtt) in Z-veto","pT4 (mtt) in Z-veto",

	"Eta1 (e+e- & e) in Z-window","Eta2 (e+e- & e) in Z-window","Eta3 (e+e- & e) in Z-window","Eta4 (e+e- & e) in Z-window",
	"Eta1 (e+e- & m) in Z-window","Eta2 (e+e- & m) in Z-window","Eta3 (e+e- & m) in Z-window","Eta4 (e+e- & m) in Z-window",
	"Eta1 (m+m- & e) in Z-window","Eta2 (m+m- & e) in Z-window","Eta3 (m+m- & e) in Z-window","Eta4 (m+m- & e) in Z-window",
	"Eta1 (m+m- & m) in Z-window","Eta2 (m+m- & m) in Z-window","Eta3 (m+m- & m) in Z-window","Eta4 (m+m- & m) in Z-window",
	"Eta1 (e+e- & e+e-) in Z-window","Eta2 (e+e- & e+e-) in Z-window","Eta3 (e+e- & e+e-) in Z-window","Eta4 (e+e- & e+e-) in Z-window",
	"Eta1 (e+e- & em) in Z-window","Eta2 (e+e- & em) in Z-window","Eta3 (e+e- & em) in Z-window","Eta4 (e+e- & em) in Z-window",
	"Eta1 (e+e- & m+m-) in Z-window","Eta2 (e+e- & m+m-) in Z-window","Eta3 (e+e- & m+m-) in Z-window","Eta4 (e+e- & m+m-) in Z-window",
	"Eta1 (emt) in Z-window","Eta2 (emt) in Z-window","Eta3 (emt) in Z-window","Eta4 (emt) in Z-window",
	"Eta1 (m+m- & em) in Z-window","Eta2 (m+m- & em) in Z-window","Eta3 (m+m- & em) in Z-window","Eta4 (m+m- & em) in Z-window",
	"Eta1 (m+m- & m+m-) in Z-window","Eta2 (m+m- & m+m-) in Z-window","Eta3 (m+m- & m+m-) in Z-window","Eta4 (m+m- & m+m-) in Z-window",
	"Eta1 (e+e-) in Z-window","Eta2 (e+e-) in Z-window","Eta3 (e+e-) in Z-window","Eta4 (e+e-) in Z-window",
	"Eta1 (e m) in Z-window","Eta2 (e m) in Z-window","Eta3 (e m) in Z-window","Eta4 (e m) in Z-window",
	"Eta1 (m+m-) in Z-window","Eta2 (m+m-) in Z-window","Eta3 (m+m-) in Z-window","Eta4 (m+m-) in Z-window",
	"Eta1 (e+e- & t) in Z-window","Eta2 (e+e- & t) in Z-window","Eta3 (e+e- & t) in Z-window","Eta4 (e+e- & t) in Z-window",
	"Eta1 (m+m- & t) in Z-window","Eta2 (m+m- & t) in Z-window","Eta3 (m+m- & t) in Z-window","Eta4 (m+m- & t) in Z-window",
	"Eta1 (ett) in Z-window","Eta2 (ett) in Z-window","Eta3 (ett) in Z-window","Eta4 (ett) in Z-window",
	"Eta1 (mtt) in Z-window","Eta2 (mtt) in Z-window","Eta3 (mtt) in Z-window","Eta4 (mtt) in Z-window",

	"Eta1 (e+e- & e) in Z-veto","Eta2 (e+e- & e) in Z-veto","Eta3 (e+e- & e) in Z-veto","Eta4 (e+e- & e) in Z-veto",
	"Eta1 (e+e- & m) in Z-veto","Eta2 (e+e- & m) in Z-veto","Eta3 (e+e- & m) in Z-veto","Eta4 (e+e- & m) in Z-veto",
	"Eta1 (m+m- & e) in Z-veto","Eta2 (m+m- & e) in Z-veto","Eta3 (m+m- & e) in Z-veto","Eta4 (m+m- & e) in Z-veto",
	"Eta1 (m+m- & m) in Z-veto","Eta2 (m+m- & m) in Z-veto","Eta3 (m+m- & m) in Z-veto","Eta4 (m+m- & m) in Z-veto",
	"Eta1 (e+e- & e+e-) in Z-veto","Eta2 (e+e- & e+e-) in Z-veto","Eta3 (e+e- & e+e-) in Z-veto","Eta4 (e+e- & e+e-) in Z-veto",
	"Eta1 (e+e- & em) in Z-veto","Eta2 (e+e- & em) in Z-veto","Eta3 (e+e- & em) in Z-veto","Eta4 (e+e- & em) in Z-veto",
	"Eta1 (e+e- & m+m-) in Z-veto","Eta2 (e+e- & m+m-) in Z-veto","Eta3 (e+e- & m+m-) in Z-veto","Eta4 (e+e- & m+m-) in Z-veto",
	"Eta1 (emt) in Z-veto","Eta2 (emt) in Z-veto","Eta3 (emt) in Z-veto","Eta4 (emt) in Z-veto",
	"Eta1 (m+m- & em) in Z-veto","Eta2 (m+m- & em) in Z-veto","Eta3 (m+m- & em) in Z-veto","Eta4 (m+m- & em) in Z-veto",
	"Eta1 (m+m- & m+m-) in Z-veto","Eta2 (m+m- & m+m-) in Z-veto","Eta3 (m+m- & m+m-) in Z-veto","Eta4 (m+m- & m+m-) in Z-veto",
	"Eta1 (e+e-) in Z-veto","Eta2 (e+e-) in Z-veto","Eta3 (e+e-) in Z-veto","Eta4 (e+e-) in Z-veto",
	"Eta1 (e m) in Z-veto","Eta2 (e m) in Z-veto","Eta3 (e m) in Z-veto","Eta4 (e m) in Z-veto",
	"Eta1 (m+m-) in Z-veto","Eta2 (m+m-) in Z-veto","Eta3 (m+m-) in Z-veto","Eta4 (m+m-) in Z-veto",
	"Eta1 (e+e- & t) in Z-veto","Eta2 (e+e- & t) in Z-veto","Eta3 (e+e- & t) in Z-veto","Eta4 (e+e- & t) in Z-veto",
	"Eta1 (m+m- & t) in Z-veto","Eta2 (m+m- & t) in Z-veto","Eta3 (m+m- & t) in Z-veto","Eta4 (m+m- & t) in Z-veto",
	"Eta1 (ett) in Z-veto","Eta2 (ett) in Z-veto","Eta3 (ett) in Z-veto","Eta4 (ett) in Z-veto",
	"Eta1 (mtt) in Z-veto","Eta2 (mtt) in Z-veto","Eta3 (mtt) in Z-veto","Eta4 (mtt) in Z-veto",

	"Phi1 (e+e- & e) in Z-window","Phi2 (e+e- & e) in Z-window","Phi3 (e+e- & e) in Z-window","Phi4 (e+e- & e) in Z-window",
	"Phi1 (e+e- & m) in Z-window","Phi2 (e+e- & m) in Z-window","Phi3 (e+e- & m) in Z-window","Phi4 (e+e- & m) in Z-window",
	"Phi1 (m+m- & e) in Z-window","Phi2 (m+m- & e) in Z-window","Phi3 (m+m- & e) in Z-window","Phi4 (m+m- & e) in Z-window",
	"Phi1 (m+m- & m) in Z-window","Phi2 (m+m- & m) in Z-window","Phi3 (m+m- & m) in Z-window","Phi4 (m+m- & m) in Z-window",
	"Phi1 (e+e- & e+e-) in Z-window","Phi2 (e+e- & e+e-) in Z-window","Phi3 (e+e- & e+e-) in Z-window","Phi4 (e+e- & e+e-) in Z-window",
	"Phi1 (e+e- & em) in Z-window","Phi2 (e+e- & em) in Z-window","Phi3 (e+e- & em) in Z-window","Phi4 (e+e- & em) in Z-window",
	"Phi1 (e+e- & m+m-) in Z-window","Phi2 (e+e- & m+m-) in Z-window","Phi3 (e+e- & m+m-) in Z-window","Phi4 (e+e- & m+m-) in Z-window",
	"Phi1 (emt) in Z-window","Phi2 (emt) in Z-window","Phi3 (emt) in Z-window","Phi4 (emt) in Z-window",
	"Phi1 (m+m- & em) in Z-window","Phi2 (m+m- & em) in Z-window","Phi3 (m+m- & em) in Z-window","Phi4 (m+m- & em) in Z-window",
	"Phi1 (m+m- & m+m-) in Z-window","Phi2 (m+m- & m+m-) in Z-window","Phi3 (m+m- & m+m-) in Z-window","Phi4 (m+m- & m+m-) in Z-window",
	"Phi1 (e+e-) in Z-window","Phi2 (e+e-) in Z-window","Phi3 (e+e-) in Z-window","Phi4 (e+e-) in Z-window",
	"Phi1 (e m) in Z-window","Phi2 (e m) in Z-window","Phi3 (e m) in Z-window","Phi4 (e m) in Z-window",
	"Phi1 (m+m-) in Z-window","Phi2 (m+m-) in Z-window","Phi3 (m+m-) in Z-window","Phi4 (m+m-) in Z-window",
	"Phi1 (e+e- & t) in Z-window","Phi2 (e+e- & t) in Z-window","Phi3 (e+e- & t) in Z-window","Phi4 (e+e- & t) in Z-window",
	"Phi1 (m+m- & t) in Z-window","Phi2 (m+m- & t) in Z-window","Phi3 (m+m- & t) in Z-window","Phi4 (m+m- & t) in Z-window",
	"Phi1 (ett) in Z-window","Phi2 (ett) in Z-window","Phi3 (ett) in Z-window","Phi4 (ett) in Z-window",
	"Phi1 (mtt) in Z-window","Phi2 (mtt) in Z-window","Phi3 (mtt) in Z-window","Phi4 (mtt) in Z-window",

	"Phi1 (e+e- & e) in Z-veto","Phi2 (e+e- & e) in Z-veto","Phi3 (e+e- & e) in Z-veto","Phi4 (e+e- & e) in Z-veto",
	"Phi1 (e+e- & m) in Z-veto","Phi2 (e+e- & m) in Z-veto","Phi3 (e+e- & m) in Z-veto","Phi4 (e+e- & m) in Z-veto",
	"Phi1 (m+m- & e) in Z-veto","Phi2 (m+m- & e) in Z-veto","Phi3 (m+m- & e) in Z-veto","Phi4 (m+m- & e) in Z-veto",
	"Phi1 (m+m- & m) in Z-veto","Phi2 (m+m- & m) in Z-veto","Phi3 (m+m- & m) in Z-veto","Phi4 (m+m- & m) in Z-veto",
	"Phi1 (e+e- & e+e-) in Z-veto","Phi2 (e+e- & e+e-) in Z-veto","Phi3 (e+e- & e+e-) in Z-veto","Phi4 (e+e- & e+e-) in Z-veto",
	"Phi1 (e+e- & em) in Z-veto","Phi2 (e+e- & em) in Z-veto","Phi3 (e+e- & em) in Z-veto","Phi4 (e+e- & em) in Z-veto",
	"Phi1 (e+e- & m+m-) in Z-veto","Phi2 (e+e- & m+m-) in Z-veto","Phi3 (e+e- & m+m-) in Z-veto","Phi4 (e+e- & m+m-) in Z-veto",
	"Phi1 (emt) in Z-veto","Phi2 (emt) in Z-veto","Phi3 (emt) in Z-veto","Phi4 (emt) in Z-veto",
	"Phi1 (m+m- & em) in Z-veto","Phi2 (m+m- & em) in Z-veto","Phi3 (m+m- & em) in Z-veto","Phi4 (m+m- & em) in Z-veto",
	"Phi1 (m+m- & m+m-) in Z-veto","Phi2 (m+m- & m+m-) in Z-veto","Phi3 (m+m- & m+m-) in Z-veto","Phi4 (m+m- & m+m-) in Z-veto",
	"Phi1 (e+e-) in Z-veto","Phi2 (e+e-) in Z-veto","Phi3 (e+e-) in Z-veto","Phi4 (e+e-) in Z-veto",
	"Phi1 (e m) in Z-veto","Phi2 (e m) in Z-veto","Phi3 (e m) in Z-veto","Phi4 (e m) in Z-veto",
	"Phi1 (m+m-) in Z-veto","Phi2 (m+m-) in Z-veto","Phi3 (m+m-) in Z-veto","Phi4 (m+m-) in Z-veto",
	"Phi1 (e+e- & t) in Z-veto","Phi2 (e+e- & t) in Z-veto","Phi3 (e+e- & t) in Z-veto","Phi4 (e+e- & t) in Z-veto",
	"Phi1 (m+m- & t) in Z-veto","Phi2 (m+m- & t) in Z-veto","Phi3 (m+m- & t) in Z-veto","Phi4 (m+m- & t) in Z-veto",
	"Phi1 (ett) in Z-veto","Phi2 (ett) in Z-veto","Phi3 (ett) in Z-veto","Phi4 (ett) in Z-veto",
	"Phi1 (mtt) in Z-veto","Phi2 (mtt) in Z-veto","Phi3 (mtt) in Z-veto","Phi4 (mtt) in Z-veto",
	
	"dXY1 (e+e- & e) in Z-window","dXY2 (e+e- & e) in Z-window","dXY3 (e+e- & e) in Z-window","dXY4 (e+e- & e) in Z-window",
	"dXY1 (e+e- & m) in Z-window","dXY2 (e+e- & m) in Z-window","dXY3 (e+e- & m) in Z-window","dXY4 (e+e- & m) in Z-window",
	"dXY1 (m+m- & e) in Z-window","dXY2 (m+m- & e) in Z-window","dXY3 (m+m- & e) in Z-window","dXY4 (m+m- & e) in Z-window",
	"dXY1 (m+m- & m) in Z-window","dXY2 (m+m- & m) in Z-window","dXY3 (m+m- & m) in Z-window","dXY4 (m+m- & m) in Z-window",
	"dXY1 (e+e- & e+e-) in Z-window","dXY2 (e+e- & e+e-) in Z-window","dXY3 (e+e- & e+e-) in Z-window","dXY4 (e+e- & e+e-) in Z-window",
	"dXY1 (e+e- & em) in Z-window","dXY2 (e+e- & em) in Z-window","dXY3 (e+e- & em) in Z-window","dXY4 (e+e- & em) in Z-window",
	"dXY1 (e+e- & m+m-) in Z-window","dXY2 (e+e- & m+m-) in Z-window","dXY3 (e+e- & m+m-) in Z-window","dXY4 (e+e- & m+m-) in Z-window",
	"dXY1 (emt) in Z-window","dXY2 (emt) in Z-window","dXY3 (emt) in Z-window","dXY4 (emt) in Z-window",
	"dXY1 (m+m- & em) in Z-window","dXY2 (m+m- & em) in Z-window","dXY3 (m+m- & em) in Z-window","dXY4 (m+m- & em) in Z-window",
	"dXY1 (m+m- & m+m-) in Z-window","dXY2 (m+m- & m+m-) in Z-window","dXY3 (m+m- & m+m-) in Z-window","dXY4 (m+m- & m+m-) in Z-window",
	"dXY1 (e+e-) in Z-window","dXY2 (e+e-) in Z-window","dXY3 (e+e-) in Z-window","dXY4 (e+e-) in Z-window",
	"dXY1 (e m) in Z-window","dXY2 (e m) in Z-window","dXY3 (e m) in Z-window","dXY4 (e m) in Z-window",
	"dXY1 (m+m-) in Z-window","dXY2 (m+m-) in Z-window","dXY3 (m+m-) in Z-window","dXY4 (m+m-) in Z-window",
	"dXY1 (e+e- & t) in Z-window","dXY2 (e+e- & t) in Z-window","dXY3 (e+e- & t) in Z-window","dXY4 (e+e- & t) in Z-window",
	"dXY1 (m+m- & t) in Z-window","dXY2 (m+m- & t) in Z-window","dXY3 (m+m- & t) in Z-window","dXY4 (m+m- & t) in Z-window",
	"dXY1 (ett) in Z-window","dXY2 (ett) in Z-window","dXY3 (ett) in Z-window","dXY4 (ett) in Z-window",
	"dXY1 (mtt) in Z-window","dXY2 (mtt) in Z-window","dXY3 (mtt) in Z-window","dXY4 (mtt) in Z-window",
	
	
	"dXY1 (e+e- & e) in Z-veto","dXY2 (e+e- & e) in Z-veto","dXY3 (e+e- & e) in Z-veto","dXY4 (e+e- & e) in Z-veto",
	"dXY1 (e+e- & m) in Z-veto","dXY2 (e+e- & m) in Z-veto","dXY3 (e+e- & m) in Z-veto","dXY4 (e+e- & m) in Z-veto",
	"dXY1 (m+m- & e) in Z-veto","dXY2 (m+m- & e) in Z-veto","dXY3 (m+m- & e) in Z-veto","dXY4 (m+m- & e) in Z-veto",
	"dXY1 (m+m- & m) in Z-veto","dXY2 (m+m- & m) in Z-veto","dXY3 (m+m- & m) in Z-veto","dXY4 (m+m- & m) in Z-veto",
	"dXY1 (e+e- & e+e-) in Z-veto","dXY2 (e+e- & e+e-) in Z-veto","dXY3 (e+e- & e+e-) in Z-veto","dXY4 (e+e- & e+e-) in Z-veto",
	"dXY1 (e+e- & em) in Z-veto","dXY2 (e+e- & em) in Z-veto","dXY3 (e+e- & em) in Z-veto","dXY4 (e+e- & em) in Z-veto",
	"dXY1 (e+e- & m+m-) in Z-veto","dXY2 (e+e- & m+m-) in Z-veto","dXY3 (e+e- & m+m-) in Z-veto","dXY4 (e+e- & m+m-) in Z-veto",
	"dXY1 (emt) in Z-veto","dXY2 (emt) in Z-veto","dXY3 (emt) in Z-veto","dXY4 (emt) in Z-veto",
	"dXY1 (m+m- & em) in Z-veto","dXY2 (m+m- & em) in Z-veto","dXY3 (m+m- & em) in Z-veto","dXY4 (m+m- & em) in Z-veto",
	"dXY1 (m+m- & m+m-) in Z-veto","dXY2 (m+m- & m+m-) in Z-veto","dXY3 (m+m- & m+m-) in Z-veto","dXY4 (m+m- & m+m-) in Z-veto",
	"dXY1 (e+e-) in Z-veto","dXY2 (e+e-) in Z-veto","dXY3 (e+e-) in Z-veto","dXY4 (e+e-) in Z-veto",
	"dXY1 (e m) in Z-veto","dXY2 (e m) in Z-veto","dXY3 (e m) in Z-veto","dXY4 (e m) in Z-veto",
	"dXY1 (m+m-) in Z-veto","dXY2 (m+m-) in Z-veto","dXY3 (m+m-) in Z-veto","dXY4 (m+m-) in Z-veto",
	"dXY1 (e+e- & t) in Z-veto","dXY2 (e+e- & t) in Z-veto","dXY3 (e+e- & t) in Z-veto","dXY4 (e+e- & t) in Z-veto",
	"dXY1 (m+m- & t) in Z-veto","dXY2 (m+m- & t) in Z-veto","dXY3 (m+m- & t) in Z-veto","dXY4 (m+m- & t) in Z-veto",
	"dXY1 (ett) in Z-veto","dXY2 (ett) in Z-veto","dXY3 (ett) in Z-veto","dXY4 (ett) in Z-veto",
	"dXY1 (mtt) in Z-veto","dXY2 (mtt) in Z-veto","dXY3 (mtt) in Z-veto","dXY4 (mtt) in Z-veto",
	
	"dZ1 (e+e- & e) in Z-window","dZ2 (e+e- & e) in Z-window","dZ3 (e+e- & e) in Z-window","dZ4 (e+e- & e) in Z-window",
	"dZ1 (e+e- & m) in Z-window","dZ2 (e+e- & m) in Z-window","dZ3 (e+e- & m) in Z-window","dZ4 (e+e- & m) in Z-window",
	"dZ1 (m+m- & e) in Z-window","dZ2 (m+m- & e) in Z-window","dZ3 (m+m- & e) in Z-window","dZ4 (m+m- & e) in Z-window",
	"dZ1 (m+m- & m) in Z-window","dZ2 (m+m- & m) in Z-window","dZ3 (m+m- & m) in Z-window","dZ4 (m+m- & m) in Z-window",
	"dZ1 (e+e- & e+e-) in Z-window","dZ2 (e+e- & e+e-) in Z-window","dZ3 (e+e- & e+e-) in Z-window","dZ4 (e+e- & e+e-) in Z-window",
	"dZ1 (e+e- & em) in Z-window","dZ2 (e+e- & em) in Z-window","dZ3 (e+e- & em) in Z-window","dZ4 (e+e- & em) in Z-window",
	"dZ1 (e+e- & m+m-) in Z-window","dZ2 (e+e- & m+m-) in Z-window","dZ3 (e+e- & m+m-) in Z-window","dZ4 (e+e- & m+m-) in Z-window",
	"dZ1 (emt) in Z-window","dZ2 (emt) in Z-window","dZ3 (emt) in Z-window","dZ4 (emt) in Z-window",
	"dZ1 (m+m- & em) in Z-window","dZ2 (m+m- & em) in Z-window","dZ3 (m+m- & em) in Z-window","dZ4 (m+m- & em) in Z-window",
	"dZ1 (m+m- & m+m-) in Z-window","dZ2 (m+m- & m+m-) in Z-window","dZ3 (m+m- & m+m-) in Z-window","dZ4 (m+m- & m+m-) in Z-window",
	"dZ1 (e+e-) in Z-window","dZ2 (e+e-) in Z-window","dZ3 (e+e-) in Z-window","dZ4 (e+e-) in Z-window",
	"dZ1 (e m) in Z-window","dZ2 (e m) in Z-window","dZ3 (e m) in Z-window","dZ4 (e m) in Z-window",
	"dZ1 (m+m-) in Z-window","dZ2 (m+m-) in Z-window","dZ3 (m+m-) in Z-window","dZ4 (m+m-) in Z-window",
	"dZ1 (e+e- & t) in Z-window","dZ2 (e+e- & t) in Z-window","dZ3 (e+e- & t) in Z-window","dZ4 (e+e- & t) in Z-window",
	"dZ1 (m+m- & t) in Z-window","dZ2 (m+m- & t) in Z-window","dZ3 (m+m- & t) in Z-window","dZ4 (m+m- & t) in Z-window",
	"dZ1 (ett) in Z-window","dZ2 (ett) in Z-window","dZ3 (ett) in Z-window","dZ4 (ett) in Z-window",
	"dZ1 (mtt) in Z-window","dZ2 (mtt) in Z-window","dZ3 (mtt) in Z-window","dZ4 (mtt) in Z-window",
	
	"dZ1 (e+e- & e) in Z-veto","dZ2 (e+e- & e) in Z-veto","dZ3 (e+e- & e) in Z-veto","dZ4 (e+e- & e) in Z-veto",
	"dZ1 (e+e- & m) in Z-veto","dZ2 (e+e- & m) in Z-veto","dZ3 (e+e- & m) in Z-veto","dZ4 (e+e- & m) in Z-veto",
	"dZ1 (m+m- & e) in Z-veto","dZ2 (m+m- & e) in Z-veto","dZ3 (m+m- & e) in Z-veto","dZ4 (m+m- & e) in Z-veto",
	"dZ1 (m+m- & m) in Z-veto","dZ2 (m+m- & m) in Z-veto","dZ3 (m+m- & m) in Z-veto","dZ4 (m+m- & m) in Z-veto",
	"dZ1 (e+e- & e+e-) in Z-veto","dZ2 (e+e- & e+e-) in Z-veto","dZ3 (e+e- & e+e-) in Z-veto","dZ4 (e+e- & e+e-) in Z-veto",
	"dZ1 (e+e- & em) in Z-veto","dZ2 (e+e- & em) in Z-veto","dZ3 (e+e- & em) in Z-veto","dZ4 (e+e- & em) in Z-veto",
	"dZ1 (e+e- & m+m-) in Z-veto","dZ2 (e+e- & m+m-) in Z-veto","dZ3 (e+e- & m+m-) in Z-veto","dZ4 (e+e- & m+m-) in Z-veto",
	"dZ1 (emt) in Z-veto","dZ2 (emt) in Z-veto","dZ3 (emt) in Z-veto","dZ4 (emt) in Z-veto",
	"dZ1 (m+m- & em) in Z-veto","dZ2 (m+m- & em) in Z-veto","dZ3 (m+m- & em) in Z-veto","dZ4 (m+m- & em) in Z-veto",
	"dZ1 (m+m- & m+m-) in Z-veto","dZ2 (m+m- & m+m-) in Z-veto","dZ3 (m+m- & m+m-) in Z-veto","dZ4 (m+m- & m+m-) in Z-veto",
	"dZ1 (e+e-) in Z-veto","dZ2 (e+e-) in Z-veto","dZ3 (e+e-) in Z-veto","dZ4 (e+e-) in Z-veto",
	"dZ1 (e m) in Z-veto","dZ2 (e m) in Z-veto","dZ3 (e m) in Z-veto","dZ4 (e m) in Z-veto",
	"dZ1 (m+m-) in Z-veto","dZ2 (m+m-) in Z-veto","dZ3 (m+m-) in Z-veto","dZ4 (m+m-) in Z-veto",
	"dZ1 (e+e- & t) in Z-veto","dZ2 (e+e- & t) in Z-veto","dZ3 (e+e- & t) in Z-veto","dZ4 (e+e- & t) in Z-veto",
	"dZ1 (m+m- & t) in Z-veto","dZ2 (m+m- & t) in Z-veto","dZ3 (m+m- & t) in Z-veto","dZ4 (m+m- & t) in Z-veto",
	"dZ1 (ett) in Z-veto","dZ2 (ett) in Z-veto","dZ3 (ett) in Z-veto","dZ4 (ett) in Z-veto",
	"dZ1 (mtt) in Z-veto","dZ2 (mtt) in Z-veto","dZ3 (mtt) in Z-veto","dZ4 (mtt) in Z-veto",

	"ISO1 (e+e- & e) in Z-window","ISO2 (e+e- & e) in Z-window","ISO3 (e+e- & e) in Z-window","ISO4 (e+e- & e) in Z-window",
	"ISO1 (e+e- & m) in Z-window","ISO2 (e+e- & m) in Z-window","ISO3 (e+e- & m) in Z-window","ISO4 (e+e- & m) in Z-window",
	"ISO1 (m+m- & e) in Z-window","ISO2 (m+m- & e) in Z-window","ISO3 (m+m- & e) in Z-window","ISO4 (m+m- & e) in Z-window",
	"ISO1 (m+m- & m) in Z-window","ISO2 (m+m- & m) in Z-window","ISO3 (m+m- & m) in Z-window","ISO4 (m+m- & m) in Z-window",
	"ISO1 (e+e- & e+e-) in Z-window","ISO2 (e+e- & e+e-) in Z-window","ISO3 (e+e- & e+e-) in Z-window","ISO4 (e+e- & e+e-) in Z-window",
	"ISO1 (e+e- & em) in Z-window","ISO2 (e+e- & em) in Z-window","ISO3 (e+e- & em) in Z-window","ISO4 (e+e- & em) in Z-window",
	"ISO1 (e+e- & m+m-) in Z-window","ISO2 (e+e- & m+m-) in Z-window","ISO3 (e+e- & m+m-) in Z-window","ISO4 (e+e- & m+m-) in Z-window",
	"ISO1 (emt) in Z-window","ISO2 (emt) in Z-window","ISO3 (emt) in Z-window","ISO4 (emt) in Z-window",
	"ISO1 (m+m- & em) in Z-window","ISO2 (m+m- & em) in Z-window","ISO3 (m+m- & em) in Z-window","ISO4 (m+m- & em) in Z-window",
	"ISO1 (m+m- & m+m-) in Z-window","ISO2 (m+m- & m+m-) in Z-window","ISO3 (m+m- & m+m-) in Z-window","ISO4 (m+m- & m+m-) in Z-window",
	"ISO1 (e+e-) in Z-window","ISO2 (e+e-) in Z-window","ISO3 (e+e-) in Z-window","ISO4 (e+e-) in Z-window",
	"ISO1 (e m) in Z-window","ISO2 (e m) in Z-window","ISO3 (e m) in Z-window","ISO4 (e m) in Z-window",
	"ISO1 (m+m-) in Z-window","ISO2 (m+m-) in Z-window","ISO3 (m+m-) in Z-window","ISO4 (m+m-) in Z-window",
	"ISO1 (e+e- & t) in Z-window","ISO2 (e+e- & t) in Z-window","ISO3 (e+e- & t) in Z-window","ISO4 (e+e- & t) in Z-window",
	"ISO1 (m+m- & t) in Z-window","ISO2 (m+m- & t) in Z-window","ISO3 (m+m- & t) in Z-window","ISO4 (m+m- & t) in Z-window",
	"ISO1 (ett) in Z-window","ISO2 (ett) in Z-window","ISO3 (ett) in Z-window","ISO4 (ett) in Z-window",
	"ISO1 (mtt) in Z-window","ISO2 (mtt) in Z-window","ISO3 (mtt) in Z-window","ISO4 (mtt) in Z-window",

	"ISO1 (e+e- & e) in Z-veto","ISO2 (e+e- & e) in Z-veto","ISO3 (e+e- & e) in Z-veto","ISO4 (e+e- & e) in Z-veto",
	"ISO1 (e+e- & m) in Z-veto","ISO2 (e+e- & m) in Z-veto","ISO3 (e+e- & m) in Z-veto","ISO4 (e+e- & m) in Z-veto",
	"ISO1 (m+m- & e) in Z-veto","ISO2 (m+m- & e) in Z-veto","ISO3 (m+m- & e) in Z-veto","ISO4 (m+m- & e) in Z-veto",
	"ISO1 (m+m- & m) in Z-veto","ISO2 (m+m- & m) in Z-veto","ISO3 (m+m- & m) in Z-veto","ISO4 (m+m- & m) in Z-veto",
	"ISO1 (e+e- & e+e-) in Z-veto","ISO2 (e+e- & e+e-) in Z-veto","ISO3 (e+e- & e+e-) in Z-veto","ISO4 (e+e- & e+e-) in Z-veto",
	"ISO1 (e+e- & em) in Z-veto","ISO2 (e+e- & em) in Z-veto","ISO3 (e+e- & em) in Z-veto","ISO4 (e+e- & em) in Z-veto",
	"ISO1 (e+e- & m+m-) in Z-veto","ISO2 (e+e- & m+m-) in Z-veto","ISO3 (e+e- & m+m-) in Z-veto","ISO4 (e+e- & m+m-) in Z-veto",
	"ISO1 (emt) in Z-veto","ISO2 (emt) in Z-veto","ISO3 (emt) in Z-veto","ISO4 (emt) in Z-veto",
	"ISO1 (m+m- & em) in Z-veto","ISO2 (m+m- & em) in Z-veto","ISO3 (m+m- & em) in Z-veto","ISO4 (m+m- & em) in Z-veto",
	"ISO1 (m+m- & m+m-) in Z-veto","ISO2 (m+m- & m+m-) in Z-veto","ISO3 (m+m- & m+m-) in Z-veto","ISO4 (m+m- & m+m-) in Z-veto",
	"ISO1 (e+e-) in Z-veto","ISO2 (e+e-) in Z-veto","ISO3 (e+e-) in Z-veto","ISO4 (e+e-) in Z-veto",
	"ISO1 (e m) in Z-veto","ISO2 (e m) in Z-veto","ISO3 (e m) in Z-veto","ISO4 (e m) in Z-veto",
	"ISO1 (m+m-) in Z-veto","ISO2 (m+m-) in Z-veto","ISO3 (m+m-) in Z-veto","ISO4 (m+m-) in Z-veto",
	"ISO1 (e+e- & t) in Z-veto","ISO2 (e+e- & t) in Z-veto","ISO3 (e+e- & t) in Z-veto","ISO4 (e+e- & t) in Z-veto",
	"ISO1 (m+m- & t) in Z-veto","ISO2 (m+m- & t) in Z-veto","ISO3 (m+m- & t) in Z-veto","ISO4 (m+m- & t) in Z-veto",
	"ISO1 (ett) in Z-veto","ISO2 (ett) in Z-veto","ISO3 (ett) in Z-veto","ISO4 (ett) in Z-veto",
	"ISO1 (mtt) in Z-veto","ISO2 (mtt) in Z-veto","ISO3 (mtt) in Z-veto","ISO4 (mtt) in Z-veto",
	};
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
		//TH1D *h_ttH1 = (TH1D*)ifile_ttH1->Get(hist_list[i]);h_ttH1->SetFillColor(28);
		//TH1D *h_ttH2 = (TH1D*)ifile_ttH2->Get(hist_list[i]);h_ttH2->SetFillColor(28);
		//TH1D *h_ttH3 = (TH1D*)ifile_ttH3->Get(hist_list[i]);h_ttH3->SetFillColor(28);
		TH1D *h_ttH4 = (TH1D*)ifile_ttH4->Get(hist_list[i]);h_ttH4->SetFillColor(28);
		TH1D *h_ZH1 = (TH1D*)ifile_ZH1->Get(hist_list[i]);h_ZH1->SetFillColor(28);
		//TH1D *h_ZH2 = (TH1D*)ifile_ZH2->Get(hist_list[i]);h_ZH2->SetFillColor(28);
		TH1D *h_ZH3 = (TH1D*)ifile_ZH3->Get(hist_list[i]);h_ZH3->SetFillColor(28);
		
		TH1D *h_D1 = (TH1D*)ifile_D1->Get(hist_list[i]);
		//TH1D *h_D2 = (TH1D*)ifile_D2->Get(hist_list[i]);
		//TH1D *h_D3 = (TH1D*)ifile_D3->Get(hist_list[i]);
		//TH1D *h_D4 = (TH1D*)ifile_D4->Get(hist_list[i]);
		TH1D *h_D5 = (TH1D*)ifile_D5->Get(hist_list[i]);
		
		for (auto hist : {h_DY1, h_DY2, /*h_VV1,*/ h_VV2, h_VV3, /*h_VV4,*/ h_VV5, h_VV6, h_VVV1, h_VVV2, h_VVV3, h_ttV1, h_ttV2, h_ZZ1, h_ZZ2, h_ZZ3, h_WJ1, h_WJ2, h_WJ3, h_WJ4, h_WJ5, h_WJ6, h_WJ7, /*h_WJ8, h_WJ9,*/ h_ST1, h_ST2, h_ST3, h_ST4, h_ST5, h_TTbar1, h_TTbar2, h_TTbar3,/*h_ttH1, h_ttH2, h_ttH3,*/ h_ttH4, h_ZH1,/* h_ZH2,*/ h_ZH3, h_D1, /*h_D2,hD3,h_D4,*/ h_D5}) {
		    int nbins = hist->GetNbinsX();  // number of bins in X-axis
		    double overflowContent = hist->GetBinContent(nbins + 1);  // overflow bin content
		    double overflowError = hist->GetBinError(nbins + 1);      // overflow bin error

		    // Update the last visible bin with overflow content
		    hist->SetBinContent(nbins, hist->GetBinContent(nbins) + overflowContent);
		    hist->SetBinError(nbins, sqrt(pow(hist->GetBinError(nbins), 2) + pow(overflowError, 2)));
		    hist->Rebin(5);		    
		}
		
		float DY_count = h_DY1->Integral()+h_DY2->Integral();
		float VV_count = /*h_VV1->Integral()+*/h_VV2->Integral()+h_VV3->Integral()+/*h_VV4->Integral()+*/h_VV5->Integral()+h_VV6->Integral();
		float VVV_count = h_VVV1->Integral()+h_VVV2->Integral()+h_VVV3->Integral();
		float ttV_count = h_ttV1->Integral()+h_ttV2->Integral();
		float WJ_count = h_WJ1->Integral()+h_WJ2->Integral()+h_WJ3->Integral()+h_WJ4->Integral()+h_WJ5->Integral()+h_WJ6->Integral()+h_WJ7->Integral();//+h_WJ8->Integral()+h_WJ9->Integral();
		float ZZ_count = h_ZZ1->Integral()+h_ZZ2->Integral()+h_ZZ3->Integral();
		float ST_count = h_ST1->Integral()+h_ST2->Integral()+h_ST3->Integral()+h_ST4->Integral()+h_ST5->Integral();
		float TT_count = h_TTbar1->Integral()+h_TTbar2->Integral()+h_TTbar3->Integral();
		float other_count = /*h_ttH1->Integral()+h_ttH2->Integral()+h_ttH3->Integral()+*/h_ttH4->Integral()+h_ZH1->Integral()/*+h_ZH2->Integral()*/+h_ZH3->Integral();
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
		//bkg_stack->Add(h_ttH1);
		//bkg_stack->Add(h_ttH2);
		//bkg_stack->Add(h_ttH3);
		bkg_stack->Add(h_ttH4);	
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
		//h_bkg_total->Add(h_ttH1);
		//h_bkg_total->Add(h_ttH2);
		//h_bkg_total->Add(h_ttH3);
		h_bkg_total->Add(h_ttH4);
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
		legend->AddEntry(h_ttH4, other_legend, "f");
		legend->AddEntry(h_data_total, data_legend);
		legend->AddEntry(h_data_total, data_legend3);
		//legend->AddEntry(h_data_total, data_legend1);
		//legend->AddEntry(h_data_total, data_legend2);
		legend->Draw();		

		// Create a TLatex object
		TLatex latex;
		latex.SetNDC(); // Use normalized coordinates (0 to 1)
		latex.SetTextSize(0.04); // Set text size
		latex.SetTextAlign(31); // Align right (horizontal) and top (vertical)
		latex.DrawLatex(0.95, 0.95, "2017"); // Position (x, y) and text

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
		
		std::string s =  "hist_test_nopair/2017/", s1, s2;
		s1 = s + hist_list[i]+".png";
		//s2 = s + hist_list[i]+".svg";
		char* title1 = const_cast<char*>(s1.c_str());//converting string to char
		//char* title2 = const_cast<char*>(s2.c_str());//converting string to char
		canvas->SaveAs(title1);
		//canvas->SaveAs(title2);
		canvas->Clear();
	}
}
