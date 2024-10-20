#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>

void StackHist_test() {
	TFile *ifile_sig = new TFile("hist_test_nopair/HppM900_2018.root","READ");               
	TFile *ifile1 = new TFile("hist_test_nopair/DYJetsToLLM10to50_2018.root","READ");     
	TFile *ifile2 = new TFile("hist_test_nopair/DYJetsToLLM50_2018.root","READ"); 
		    
	//TFile *ifile3 = new TFile("hist_test_nopair/WGToLNuG_2018.root","READ");
	TFile *ifile4 = new TFile("hist_test_nopair/WW_2018.root","READ");
	TFile *ifile5 = new TFile("hist_test_nopair/WWTo2L2Nu_2018.root","READ");
	//TFile *ifile6 = new TFile("hist_test_nopair/WZ_2018.root","READ");
	TFile *ifile7 = new TFile("hist_test_nopair/WZTo2Q2L_2018.root","READ");
	TFile *ifile8 = new TFile("hist_test_nopair/WZTo3LNu_2018.root","READ");

	TFile *ifile9 = new TFile("hist_test_nopair/WWW_2018.root","READ");
	TFile *ifile10 = new TFile("hist_test_nopair/WZZ_2018.root","READ");
	TFile *ifile11 = new TFile("hist_test_nopair/ZZZ_2018.root","READ");

	TFile *ifile12 = new TFile("hist_test_nopair/ttWJets_2018.root","READ");
	TFile *ifile1201 = new TFile("hist_test_nopair/ttZJets_2018.root","READ");
	
	TFile *ifile13 = new TFile("hist_test_nopair/ZZTo2L2Nu_2018.root","READ");
	TFile *ifile14 = new TFile("hist_test_nopair/ZZTo2Q2L_2018.root","READ");
	TFile *ifile15 = new TFile("hist_test_nopair/ZZTo4L_2018.root","READ");

	TFile *ifile16 = new TFile("hist_test_nopair/ST_s-channel_2018.root","READ");          
	TFile *ifile17 = new TFile("hist_test_nopair/ST_t-channel_antitop_2018.root","READ");  
	TFile *ifile18 = new TFile("hist_test_nopair/ST_t-channel_top_2018.root","READ");  
	TFile *ifile19 = new TFile("hist_test_nopair/ST_tW_antitop_2018.root","READ");  
	TFile *ifile20 = new TFile("hist_test_nopair/ST_tW_top_2018.root","READ");            

	TFile *ifile21 = new TFile("hist_test_nopair/ttHTo2L2Nu_2018.root","READ");
	//TFile *ifile22 = new TFile("hist_test_nopair/ttHToEE_2018.root","READ");
	//TFile *ifile23 = new TFile("hist_test_nopair/ttHToMuMu_2018.root","READ");
	TFile *ifile24 = new TFile("hist_test_nopair/ttHToTauTau_2018.root","READ");
	
	TFile *ifile25 = new TFile("hist_test_nopair/ZHToMuMu_2018.root","READ");
	TFile *ifile26 = new TFile("hist_test_nopair/ZHToTauTau_2018.root","READ");
	TFile *ifile27 = new TFile("hist_test_nopair/GluGluZH_2018.root","READ");
	
	TFile *ifileD1 = new TFile("hist_test_nopair/EGamma_2018.root","READ");
	//TFile *ifileD2 = new TFile("hist_test_nopair/DoubleMuon_2018.root","READ");
	//TFile *ifileD3 = new TFile("hist_test_nopair/Tau_2018.root","READ");
	//TFile *ifileD4 = new TFile("hist_test_nopair/MuonEG_2018.root","READ");
	TFile *ifileD5 = new TFile("hist_test_nopair/SingleMuon_2018.root","READ");

	//float nEvents = 

	/*const char *hist_list[] = {"cutflow","h_Xmass_0t","h_Xmass_1t","h_Xmass_2t", "h_Xmass_34t", "h_ST", "h_ll1_pt_4L","h_ll1_pt_3L","h_mZ1", "h_mZ2","h_mZ3","h_mZ4","h_mZ1_3L", "h_mZ2_3L","h_mZ3_3L","h_mZ4_3L","h_met","h_pT1","h_pT2","h_pT3","h_pT4","h_dR","h_dRll","h_dRll2"};*/
	
	/*const char *hist_names[] = {"Cutflow","mll1 in Z(e+e-) + l region","mll1 in Z(m+m-) + l region", "mll1 in Z-veto(e+e-) + l region", "mll1 in Z-veto(m+m-) + l region", "ST", "Leading pair pT in 4L","Leading pair pT in 3L","Z mass from pair (1,3) in 4L", "Z mass from pair (1,4) in 4L","Z mass from pair (2,3) in 4L","Z mass from pair (2,4) in 4L", "Z mass from pair (1,3) in 3L", "Z mass from pair (1,4) in 3L","Z mass from pair (2,3)","Z mass from pair (2,4)","MET","Leading pT","Sub-Leading pT","3rd pT","4th pT","dR (+-) leptons; DR; Events","dR between 1st pair", "dR between 2nd pair"};*/


	const char *hist_list[] = {
"h_mZ1","h_mZ2","h_mZ3","h_mZ4","h_mZ5","h_mZ6","h_mZ7","h_mZ8","h_mZ9","h_mZ10",

"h_mZv1","h_mZv2","h_mZv3","h_mZv4","h_mZv5","h_mZv6","h_mZv7","h_mZv8","h_mZv9","h_mZv10",

"h_mH1","h_mH2","h_mH3","h_mH4","h_mH5","h_mH6","h_mH7","h_mH8","h_mH9","h_mH10",

"h_mHv1","h_mHv2","h_mHv3","h_mHv4","h_mHv5","h_mHv6","h_mHv7","h_mHv8","h_mHv9","h_mHv10",
 
"h_met1","h_met2","h_met3","h_met4","h_met5","h_met6","h_met7","h_met8","h_met9","h_met10",

"h_metv1","h_metv2","h_metv3","h_metv4","h_metv5","h_metv6","h_metv7","h_metv8","h_metv9","h_metv10",

"h_pt11", "h_pt21","h_pt31","h_pt41","h_pt12", "h_pt22","h_pt32","h_pt42","h_pt13", "h_pt23","h_pt33","h_pt43","h_pt14", "h_pt24","h_pt34","h_pt44","h_pt15", "h_pt25","h_pt35","h_pt45","h_pt16", "h_pt26","h_pt36","h_pt46","h_pt17", "h_pt27","h_pt37","h_pt47","h_pt17", "h_pt28","h_pt38","h_pt48","h_pt19", "h_pt29","h_pt39","h_pt49","h_pt110", "h_pt210","h_pt310","h_pt410",

"h_pt1v1", "h_pt2v1","h_pt3v1","h_pt4v1","h_pt1v2", "h_pt2v2","h_pt3v2","h_pt4v2","h_pt1v3", "h_pt2v3","h_pt3v3","h_pt4v3","h_pt1v4", "h_pt2v4","h_pt3v4","h_pt4v4","h_pt1v5", "h_pt2v5","h_pt3v5","h_pt4v5","h_pt1v6", "h_pt2v6","h_pt3v6","h_pt4v6","h_pt1v7", "h_pt2v7","h_pt3v7","h_pt4v7","h_pt1v8", "h_pt2v8","h_pt3v8","h_pt4v8","h_pt1v9", "h_pt2v9","h_pt3v9","h_pt4v9","h_pt1v10", "h_pt2v10","h_pt3v10","h_pt4v10",

"h_eta11", "h_eta21","h_eta31","h_eta41","h_eta12", "h_eta22","h_eta32","h_eta42","h_eta13", "h_eta23","h_eta33","h_eta43","h_eta14", "h_eta24","h_eta34","h_eta44","h_eta15", "h_eta25","h_eta35","h_eta45","h_eta16", "h_eta26","h_eta36","h_eta46","h_eta17", "h_eta27","h_eta37","h_eta47","h_eta18", "h_eta28","h_eta38","h_eta48","h_eta19", "h_eta29","h_eta39","h_eta49","h_eta110", "h_eta210","h_eta310","h_eta410",

"h_eta1v1", "h_eta2v1","h_eta3v1","h_eta4v1","h_eta1v2", "h_eta2v2","h_eta3v2","h_eta4v2","h_eta1v3", "h_eta2v3","h_eta3v3","h_eta4v3","h_eta1v4", "h_eta2v4","h_eta3v4","h_eta4v4","h_eta1v5", "h_eta2v5","h_eta3v5","h_eta4v5","h_eta1v6", "h_eta2v6","h_eta3v6","h_eta4v6","h_eta1v7", "h_eta2v7","h_eta3v7","h_eta4v7","h_eta1v8", "h_eta2v8","h_eta3v8","h_eta4v8","h_eta1v9", "h_eta2v9","h_eta3v9","h_eta4v9","h_eta1v10", "h_eta2v10","h_eta3v10","h_eta4v10",

"h_phi11", "h_phi21","h_phi31","h_phi41","h_phi12", "h_phi22","h_phi32","h_phi42","h_phi13", "h_phi23","h_phi33","h_phi43","h_phi14", "h_phi24","h_phi34","h_phi44","h_phi15", "h_phi25","h_phi35","h_phi45","h_phi16", "h_phi26","h_phi36","h_phi46","h_phi17", "h_phi27","h_phi37","h_phi47","h_phi18", "h_phi28","h_phi38","h_phi48","h_phi19", "h_phi29","h_phi39","h_phi49","h_phi110", "h_phi210","h_phi310","h_phi410",

"h_phi1v1", "h_phi2v1","h_phi3v1","h_phi4v1","h_phi1v2", "h_phi2v2","h_phi3v2","h_phi4v2","h_phi1v3", "h_phi2v3","h_phi3v3","h_phi4v3","h_phi1v4", "h_phi2v4","h_phi3v4","h_phi4v4","h_phi1v5", "h_phi2v5","h_phi3v5","h_phi4v5","h_phi1v6", "h_phi2v6","h_phi3v6","h_phi4v6","h_phi1v7", "h_phi2v7","h_phi3v7","h_phi4v7","h_phi1v8", "h_phi2v8","h_phi3v8","h_phi4v8","h_phi1v9", "h_phi2v9","h_phi3v9","h_phi4v9","h_phi1v10", "h_phi2v10","h_phi3v10","h_phi4v10",

"h_dxy11", "h_dxy21","h_dxy31","h_dxy41","h_dxy12", "h_dxy22","h_dxy32","h_dxy42","h_dxy13", "h_dxy23","h_dxy33","h_dxy43","h_dxy14", "h_dxy24","h_dxy34","h_dxy44","h_dxy15", "h_dxy25","h_dxy35","h_dxy45","h_dxy16", "h_dxy26","h_dxy36","h_dxy46","h_dxy17", "h_dxy27","h_dxy37","h_dxy47","h_dxy17", "h_dxy28","h_dxy38","h_dxy48","h_dxy19", "h_dxy29","h_dxy39","h_dxy49","h_dxy110", "h_dxy210","h_dxy310","h_dxy410",

"h_dxy1v1", "h_dxy2v1","h_dxy3v1","h_dxy4v1","h_dxy1v2", "h_dxy2v2","h_dxy3v2","h_dxy4v2","h_dxy1v3", "h_dxy2v3","h_dxy3v3","h_dxy4v3","h_dxy1v4", "h_dxy2v4","h_dxy3v4","h_dxy4v4","h_dxy1v5", "h_dxy2v5","h_dxy3v5","h_dxy4v5","h_dxy1v6", "h_dxy2v6","h_dxy3v6","h_dxy4v6","h_dxy1v7", "h_dxy2v7","h_dxy3v7","h_dxy4v7","h_dxy1v8", "h_dxy2v8","h_dxy3v8","h_dxy4v8","h_dxy1v9", "h_dxy2v9","h_dxy3v9","h_dxy4v9","h_dxy1v10", "h_dxy2v10","h_dxy3v10","h_dxy4v10",

"h_dZ11", "h_dZ21","h_dZ31","h_dZ41","h_dZ12", "h_dZ22","h_dZ32","h_dZ42","h_dZ13", "h_dZ23","h_dZ33","h_dZ43","h_dZ14", "h_dZ24","h_dZ34","h_dZ44","h_dZ15", "h_dZ25","h_dZ35","h_dZ45","h_dZ16", "h_dZ26","h_dZ36","h_dZ46","h_dZ17", "h_dZ27","h_dZ37","h_dZ47","h_dZ18", "h_dZ28","h_dZ38","h_dZ48","h_dZ19", "h_dZ29","h_dZ39","h_dZ49","h_dZ110", "h_dZ210","h_dZ310","h_dZ410",

"h_dZ1v1", "h_dZ2v1","h_dZ3v1","h_dZ4v1","h_dZ1v2", "h_dZ2v2","h_dZ3v2","h_dZ4v2","h_dZ1v3", "h_dZ2v3","h_dZ3v3","h_dZ4v3","h_dZ1v4", "h_dZ2v4","h_dZ3v4","h_dZ4v4","h_dZ1v5", "h_dZ2v5","h_dZ3v5","h_dZ4v5","h_dZ1v6", "h_dZ2v6","h_dZ3v6","h_dZ4v6","h_dZ1v7", "h_dZ2v7","h_dZ3v7","h_dZ4v7","h_dZ1v8", "h_dZ2v8","h_dZ3v8","h_dZ4v8","h_dZ1v9", "h_dZ2v9","h_dZ3v9","h_dZ4v9","h_dZ1v10", "h_dZ2v10","h_dZ3v10","h_dZ4v10",

"h_iso11", "h_iso21","h_iso31","h_iso41","h_iso12", "h_iso22","h_iso32","h_iso42","h_iso13", "h_iso23","h_iso33","h_iso43","h_iso14", "h_iso24","h_iso34","h_iso44","h_iso15", "h_iso25","h_iso35","h_iso45","h_iso16", "h_iso26","h_iso36","h_iso46","h_iso17", "h_iso27","h_iso37","h_iso47","h_iso18", "h_iso28","h_iso38","h_iso48","h_iso19", "h_iso29","h_iso39","h_iso49","h_iso110", "h_iso210","h_iso310","h_iso410",

"h_iso1v1", "h_iso2v1","h_iso3v1","h_iso4v1","h_iso1v2", "h_iso2v2","h_iso3v2","h_iso4v2","h_iso1v3", "h_iso2v3","h_iso3v3","h_iso4v3","h_iso1v4", "h_iso2v4","h_iso3v4","h_iso4v4","h_iso1v5", "h_iso2v5","h_iso3v5","h_iso4v5","h_iso1v6", "h_iso2v6","h_iso3v6","h_iso4v6","h_iso1v7", "h_iso2v7","h_iso3v7","h_iso4v7","h_iso1v8", "h_iso2v8","h_iso3v8","h_iso4v8","h_iso1v9", "h_iso2v9","h_iso3v9","h_iso4v9","h_iso1v10", "h_iso2v10","h_iso3v10","h_iso4v10",

	};
	
	const char *hist_names[] = {
	"mZ (e+e- & e) in Z-window","mZ (e+e- & m) in Z-window","mZ (m+m- & e) in Z-window","mZ (m+m- & m) in Z-window","mZ (e+e- & e+e-) in Z-window","mZ (e+e- & em) in Z-window","mZ (e+e- & m+m-) in Z-window","mZ (blabla) in Z-window","mZ (m+m- & em) in Z-window","mZ (m+m- & m+m-) in Z-window",
	
	"mZ (e+e- & e) in Z-veto","mZ (e+e- & m) in Z-veto","mZ (m+m- & e) in Z-veto","mZ (m+m- & m) in Z-veto","mZ (e+e- & e+e-) in Z-veto","mZ (e+e- & em) in Z-veto","mZ (e+e- & m+m-) in Z-veto","mZ (blabla) in Z-veto","mZ (m+m- & em) in Z-veto","mZ (m+m- & m+m-) in Z-veto",
	
	"mH (e+e- & e) in Z-window","mH (e+e- & m) in Z-window","mH (m+m- & e) in Z-window","mH (m+m- & m) in Z-window","mH (e+e- & e+e-) in Z-window","mH (e+e- & em) in Z-window","mH (e+e- & m+m-) in Z-window","mH (blabla) in Z-window","mH (m+m- & em) in Z-window","mH (m+m- & m+m-) in Z-window",
	
	"mH (e+e- & e) in Z-veto","mH (e+e- & m) in Z-veto","mH (m+m- & e) in Z-veto","mH (m+m- & m) in Z-veto","mH (e+e- & e+e-) in Z-veto","mH (e+e- & em) in Z-veto","mH (e+e- & m+m-) in Z-veto","mH (blabla) in Z-veto","mH (m+m- & em) in Z-veto","mH (m+m- & m+m-) in Z-veto",
	
	"MET (e+e- & e) in Z-window","MET (e+e- & m) in Z-window","MET (m+m- & e) in Z-window","MET (m+m- & m) in Z-window","MET (e+e- & e+e-) in Z-window","MET (e+e- & em) in Z-window","MET (e+e- & m+m-) in Z-window","MET (blabla) in Z-window","MET (m+m- & em) in Z-window","MET (m+m- & m+m-) in Z-window",
	
	"MET (e+e- & e) in Z-veto","MET (e+e- & m) in Z-veto","MET (m+m- & e) in Z-veto","MET (m+m- & m) in Z-veto","MET (e+e- & e+e-) in Z-veto","MET (e+e- & em) in Z-veto","MET (m+m- & e) in Z-veto","MET (blabla) in Z-veto","MET (m+m- & em) in Z-veto","MET (m+m- & m+m-) in Z-veto",
	
	"pT1 (e+e- & e) in Z-window","pT2 (e+e- & e) in Z-window","pT3 (e+e- & e) in Z-window","pT4 (e+e- & e) in Z-window",
	"pT1 (e+e- & m) in Z-window","pT2 (e+e- & m) in Z-window","pT3 (e+e- & m) in Z-window","pT4 (e+e- & m) in Z-window",
	"pT1 (m+m- & e) in Z-window","pT2 (m+m- & e) in Z-window","pT3 (m+m- & e) in Z-window","pT4 (m+m- & e) in Z-window",
	"pT1 (m+m- & m) in Z-window","pT2 (m+m- & m) in Z-window","pT3 (m+m- & m) in Z-window","pT4 (m+m- & m) in Z-window",
	"pT1 (e+e- & e+e-) in Z-window","pT2 (e+e- & e+e-) in Z-window","pT3 (e+e- & e+e-) in Z-window","pT4 (e+e- & e+e-) in Z-window",
	"pT1 (e+e- & em) in Z-window","pT2 (e+e- & em) in Z-window","pT3 (e+e- & em) in Z-window","pT4 (e+e- & em) in Z-window",
	"pT1 (e+e- & m+m-) in Z-window","pT2 (e+e- & m+m-) in Z-window","pT3 (e+e- & m+m-) in Z-window","pT4 (e+e- & m+m-) in Z-window",
	"pT1 (blabla) in Z-window","pT2 (blabla) in Z-window","pT3 (blabla) in Z-window","pT4 (blabla) in Z-window",
	"pT1 (m+m- & em) in Z-window","pT2 (m+m- & em) in Z-window","pT3 (m+m- & em) in Z-window","pT4 (m+m- & em) in Z-window",
	"pT1 (m+m- & m+m-) in Z-window","pT2 (m+m- & m+m-) in Z-window","pT3 (m+m- & m+m-) in Z-window","pT4 (m+m- & m+m-) in Z-window",
	
	"pT1 (e+e- & e) in Z-veto","pT2 (e+e- & e) in Z-veto","pT3 (e+e- & e) in Z-veto","pT4 (e+e- & e) in Z-veto",
	"pT1 (e+e- & m) in Z-veto","pT2 (e+e- & m) in Z-veto","pT3 (e+e- & m) in Z-veto","pT4 (e+e- & m) in Z-veto",
	"pT1 (m+m- & e) in Z-veto","pT2 (m+m- & e) in Z-veto","pT3 (m+m- & e) in Z-veto","pT4 (m+m- & e) in Z-veto",
	"pT1 (m+m- & m) in Z-veto","pT2 (m+m- & m) in Z-veto","pT3 (m+m- & m) in Z-veto","pT4 (m+m- & m) in Z-veto",
	"pT1 (e+e- & e) in Z-veto","pT2 (e+e- & e+e-) in Z-veto","pT3 (e+e- & e+e-) in Z-veto","pT4 (e+e- & e+e-) in Z-veto",
	"pT1 (e+e- & em) in Z-veto","pT2 (e+e- & em) in Z-veto","pT3 (e+e- & em) in Z-veto","pT4 (e+e- & em) in Z-veto",
	"pT1 (e+e- & m+m-) in Z-veto","pT2 (e+e- & m+m-) in Z-veto","pT3 (e+e- & m+m-) in Z-veto","pT4 (e+e- & m+m-) in Z-veto",
	"pT1 (blabla) in Z-veto","pT2 (blabla) in Z-veto","pT3 (blabla) in Z-veto","pT4 (blabla) in Z-veto",
	"pT1 (m+m- & em) in Z-veto","pT2 (m+m- & em) in Z-veto","pT3 (m+m- & em) in Z-veto","pT4 (m+m- & em) in Z-veto",
	"pT1 (m+m- & m+m-) in Z-veto","pT2 (m+m- & m+m-) in Z-veto","pT3 (m+m- & m+m-) in Z-veto","pT4 (m+m- & m+m-) in Z-veto",

	"Eta1 (e+e- & e) in Z-window","Eta2 (e+e- & e) in Z-window","Eta3 (e+e- & e) in Z-window","Eta4 (e+e- & e) in Z-window",
	"Eta1 (e+e- & m) in Z-window","Eta2 (e+e- & m) in Z-window","Eta3 (e+e- & m) in Z-window","Eta4 (e+e- & m) in Z-window",
	"Eta1 (m+m- & e) in Z-window","Eta2 (m+m- & e) in Z-window","Eta3 (m+m- & e) in Z-window","Eta4 (m+m- & e) in Z-window",
	"Eta1 (m+m- & m) in Z-window","Eta2 (m+m- & m) in Z-window","Eta3 (m+m- & m) in Z-window","Eta4 (m+m- & m) in Z-window",
	"Eta1 (e+e- & e+e-) in Z-window","Eta2 (e+e- & e+e-) in Z-window","Eta3 (e+e- & e+e-) in Z-window","Eta4 (e+e- & e+e-) in Z-window",
	"Eta1 (e+e- & em) in Z-window","Eta2 (e+e- & em) in Z-window","Eta3 (e+e- & em) in Z-window","Eta4 (e+e- & em) in Z-window",
	"Eta1 (e+e- & m+m-) in Z-window","Eta2 (e+e- & m+m-) in Z-window","Eta3 (e+e- & m+m-) in Z-window","Eta4 (e+e- & m+m-) in Z-window",
	"Eta1 (blabla) in Z-window","Eta2 (blabla) in Z-window","Eta3 (blabla) in Z-window","Eta4 (blabla) in Z-window",
	"Eta1 (m+m- & em) in Z-window","Eta2 (m+m- & em) in Z-window","Eta3 (m+m- & em) in Z-window","Eta4 (m+m- & em) in Z-window",
	"Eta1 (m+m- & m+m-) in Z-window","Eta2 (m+m- & m+m-) in Z-window","Eta3 (m+m- & m+m-) in Z-window","Eta4 (m+m- & m+m-) in Z-window",

	"Eta1 (e+e- & e) in Z-veto","Eta2 (e+e- & e) in Z-veto","Eta3 (e+e- & e) in Z-veto","Eta4 (e+e- & e) in Z-veto",
	"Eta1 (e+e- & m) in Z-veto","Eta2 (e+e- & m) in Z-veto","Eta3 (e+e- & m) in Z-veto","Eta4 (e+e- & m) in Z-veto",
	"Eta1 (m+m- & e) in Z-veto","Eta2 (m+m- & e) in Z-veto","Eta3 (m+m- & e) in Z-veto","Eta4 (m+m- & e) in Z-veto",
	"Eta1 (m+m- & m) in Z-veto","Eta2 (m+m- & m) in Z-veto","Eta3 (m+m- & m) in Z-veto","Eta4 (m+m- & m) in Z-veto",
	"Eta1 (e+e- & e+e-) in Z-veto","Eta2 (e+e- & e+e-) in Z-veto","Eta3 (e+e- & e+e-) in Z-veto","Eta4 (e+e- & e+e-) in Z-veto",
	"Eta1 (e+e- & em) in Z-veto","Eta2 (e+e- & em) in Z-veto","Eta3 (e+e- & em) in Z-veto","Eta4 (e+e- & em) in Z-veto",
	"Eta1 (e+e- & m+m-) in Z-veto","Eta2 (e+e- & m+m-) in Z-veto","Eta3 (e+e- & m+m-) in Z-veto","Eta4 (e+e- & m+m-) in Z-veto",
	"Eta1 (blabla) in Z-veto","Eta2 (blabla) in Z-veto","Eta3 (blabla) in Z-veto","Eta4 (blabla) in Z-veto",
	"Eta1 (m+m- & em) in Z-veto","Eta2 (m+m- & em) in Z-veto","Eta3 (m+m- & em) in Z-veto","Eta4 (m+m- & em) in Z-veto",
	"Eta1 (m+m- & m+m-) in Z-veto","Eta2 (m+m- & m+m-) in Z-veto","Eta3 (m+m- & m+m-) in Z-veto","Eta4 (m+m- & m+m-) in Z-veto",

	"Phi1 (e+e- & e) in Z-window","Phi2 (e+e- & e) in Z-window","Phi3 (e+e- & e) in Z-window","Phi4 (e+e- & e) in Z-window",
	"Phi1 (e+e- & m) in Z-window","Phi2 (e+e- & m) in Z-window","Phi3 (e+e- & m) in Z-window","Phi4 (e+e- & m) in Z-window",
	"Phi1 (m+m- & e) in Z-window","Phi2 (m+m- & e) in Z-window","Phi3 (m+m- & e) in Z-window","Phi4 (m+m- & e) in Z-window",
	"Phi1 (m+m- & m) in Z-window","Phi2 (m+m- & m) in Z-window","Phi3 (m+m- & m) in Z-window","Phi4 (m+m- & m) in Z-window",
	"Phi1 (e+e- & e+e-) in Z-window","Phi2 (e+e- & e+e-) in Z-window","Phi3 (e+e- & e+e-) in Z-window","Phi4 (e+e- & e+e-) in Z-window",
	"Phi1 (e+e- & em) in Z-window","Phi2 (e+e- & em) in Z-window","Phi3 (e+e- & em) in Z-window","Phi4 (e+e- & em) in Z-window",
	"Phi1 (e+e- & m+m-) in Z-window","Phi2 (e+e- & m+m-) in Z-window","Phi3 (e+e- & m+m-) in Z-window","Phi4 (e+e- & m+m-) in Z-window",
	"Phi1 (blabla) in Z-window","Phi2 (blabla) in Z-window","Phi3 (blabla) in Z-window","Phi4 (blabla) in Z-window",
	"Phi1 (m+m- & em) in Z-window","Phi2 (m+m- & em) in Z-window","Phi3 (m+m- & em) in Z-window","Phi4 (m+m- & em) in Z-window",
	"Phi1 (m+m- & m+m-) in Z-window","Phi2 (m+m- & m+m-) in Z-window","Phi3 (m+m- & m+m-) in Z-window","Phi4 (m+m- & m+m-) in Z-window",

	"Phi1 (e+e- & e) in Z-veto","Phi2 (e+e- & e) in Z-veto","Phi3 (e+e- & e) in Z-veto","Phi4 (e+e- & e) in Z-veto",
	"Phi1 (e+e- & m) in Z-veto","Phi2 (e+e- & m) in Z-veto","Phi3 (e+e- & m) in Z-veto","Phi4 (e+e- & m) in Z-veto",
	"Phi1 (m+m- & e) in Z-veto","Phi2 (m+m- & e) in Z-veto","Phi3 (m+m- & e) in Z-veto","Phi4 (m+m- & e) in Z-veto",
	"Phi1 (m+m- & m) in Z-veto","Phi2 (m+m- & m) in Z-veto","Phi3 (m+m- & m) in Z-veto","Phi4 (m+m- & m) in Z-veto",
	"Phi1 (e+e- & e+e-) in Z-veto","Phi2 (e+e- & e+e-) in Z-veto","Phi3 (e+e- & e+e-) in Z-veto","Phi4 (e+e- & e+e-) in Z-veto",
	"Phi1 (e+e- & em) in Z-veto","Phi2 (e+e- & em) in Z-veto","Phi3 (e+e- & em) in Z-veto","Phi4 (e+e- & em) in Z-veto",
	"Phi1 (e+e- & m+m-) in Z-veto","Phi2 (e+e- & m+m-) in Z-veto","Phi3 (e+e- & m+m-) in Z-veto","Phi4 (e+e- & m+m-) in Z-veto",
	"Phi1 (blabla) in Z-veto","Phi2 (blabla) in Z-veto","Phi3 (blabla) in Z-veto","Phi4 (blabla) in Z-veto",
	"Phi1 (m+m- & em) in Z-veto","Phi2 (m+m- & em) in Z-veto","Phi3 (m+m- & em) in Z-veto","Phi4 (m+m- & em) in Z-veto",
	"Phi1 (m+m- & m+m-) in Z-veto","Phi2 (m+m- & m+m-) in Z-veto","Phi3 (m+m- & m+m-) in Z-veto","Phi4 (m+m- & m+m-) in Z-veto",
	"dXY1 (e+e- & e) in Z-window","dXY2 (e+e- & e) in Z-window","dXY3 (e+e- & e) in Z-window","dXY4 (e+e- & e) in Z-window",
	"dXY1 (e+e- & m) in Z-window","dXY2 (e+e- & m) in Z-window","dXY3 (e+e- & m) in Z-window","dXY4 (e+e- & m) in Z-window",
	"dXY1 (m+m- & e) in Z-window","dXY2 (m+m- & e) in Z-window","dXY3 (m+m- & e) in Z-window","dXY4 (m+m- & e) in Z-window",
	"dXY1 (m+m- & m) in Z-window","dXY2 (m+m- & m) in Z-window","dXY3 (m+m- & m) in Z-window","dXY4 (m+m- & m) in Z-window",
	"dXY1 (e+e- & e+e-) in Z-window","dXY2 (e+e- & e+e-) in Z-window","dXY3 (e+e- & e+e-) in Z-window","dXY4 (e+e- & e+e-) in Z-window",
	"dXY1 (e+e- & em) in Z-window","dXY2 (e+e- & em) in Z-window","dXY3 (e+e- & em) in Z-window","dXY4 (e+e- & em) in Z-window",
	"dXY1 (e+e- & m+m-) in Z-window","dXY2 (e+e- & m+m-) in Z-window","dXY3 (e+e- & m+m-) in Z-window","dXY4 (e+e- & m+m-) in Z-window",
	"dXY1 (blabla) in Z-window","dXY2 (blabla) in Z-window","dXY3 (blabla) in Z-window","dXY4 (blabla) in Z-window",
	"dXY1 (m+m- & em) in Z-window","dXY2 (m+m- & em) in Z-window","dXY3 (m+m- & em) in Z-window","dXY4 (m+m- & em) in Z-window",
	"dXY1 (m+m- & m+m-) in Z-window","dXY2 (m+m- & m+m-) in Z-window","dXY3 (m+m- & m+m-) in Z-window","dXY4 (m+m- & m+m-) in Z-window",
	
	"dXY1 (e+e- & e) in Z-veto","dXY2 (e+e- & e) in Z-veto","dXY3 (e+e- & e) in Z-veto","dXY4 (e+e- & e) in Z-veto",
	"dXY1 (e+e- & m) in Z-veto","dXY2 (e+e- & m) in Z-veto","dXY3 (e+e- & m) in Z-veto","dXY4 (e+e- & m) in Z-veto",
	"dXY1 (m+m- & e) in Z-veto","dXY2 (m+m- & e) in Z-veto","dXY3 (m+m- & e) in Z-veto","dXY4 (m+m- & e) in Z-veto",
	"dXY1 (m+m- & m) in Z-veto","dXY2 (m+m- & m) in Z-veto","dXY3 (m+m- & m) in Z-veto","dXY4 (m+m- & m) in Z-veto",
	"dXY1 (e+e- & e+e-) in Z-veto","dXY2 (e+e- & e+e-) in Z-veto","dXY3 (e+e- & e+e-) in Z-veto","dXY4 (e+e- & e+e-) in Z-veto",
	"dXY1 (e+e- & em) in Z-veto","dXY2 (e+e- & em) in Z-veto","dXY3 (e+e- & em) in Z-veto","dXY4 (e+e- & em) in Z-veto",
	"dXY1 (e+e- & m+m-) in Z-veto","dXY2 (e+e- & m+m-) in Z-veto","dXY3 (e+e- & m+m-) in Z-veto","dXY4 (e+e- & m+m-) in Z-veto",
	"dXY1 (blabla) in Z-veto","dXY2 (blabla) in Z-veto","dXY3 (blabla) in Z-veto","dXY4 (blabla) in Z-veto",
	"dXY1 (m+m- & em) in Z-veto","dXY2 (m+m- & em) in Z-veto","dXY3 (m+m- & em) in Z-veto","dXY4 (m+m- & em) in Z-veto",
	"dXY1 (m+m- & m+m-) in Z-veto","dXY2 (m+m- & m+m-) in Z-veto","dXY3 (m+m- & m+m-) in Z-veto","dXY4 (m+m- & m+m-) in Z-veto",
	
	"dZ1 (e+e- & e) in Z-window","dZ2 (e+e- & e) in Z-window","dZ3 (e+e- & e) in Z-window","dZ4 (e+e- & e) in Z-window",
	"dZ1 (e+e- & m) in Z-window","dZ2 (e+e- & m) in Z-window","dZ3 (e+e- & m) in Z-window","dZ4 (e+e- & m) in Z-window",
	"dZ1 (m+m- & e) in Z-window","dZ2 (m+m- & e) in Z-window","dZ3 (m+m- & e) in Z-window","dZ4 (m+m- & e) in Z-window",
	"dZ1 (m+m- & m) in Z-window","dZ2 (m+m- & m) in Z-window","dZ3 (m+m- & m) in Z-window","dZ4 (m+m- & m) in Z-window",
	"dZ1 (e+e- & e+e-) in Z-window","dZ2 (e+e- & e+e-) in Z-window","dZ3 (e+e- & e+e-) in Z-window","dZ4 (e+e- & e+e-) in Z-window",
	"dZ1 (e+e- & em) in Z-window","dZ2 (e+e- & em) in Z-window","dZ3 (e+e- & em) in Z-window","dZ4 (e+e- & em) in Z-window",
	"dZ1 (e+e- & m+m-) in Z-window","dZ2 (e+e- & m+m-) in Z-window","dZ3 (e+e- & m+m-) in Z-window","dZ4 (e+e- & m+m-) in Z-window",
	"dZ1 (blabla) in Z-window","dZ2 (blabla) in Z-window","dZ3 (blabla) in Z-window","dZ4 (blabla) in Z-window",
	"dZ1 (m+m- & em) in Z-window","dZ2 (m+m- & em) in Z-window","dZ3 (m+m- & em) in Z-window","dZ4 (m+m- & em) in Z-window",
	"dZ1 (m+m- & m+m-) in Z-window","dZ2 (m+m- & m+m-) in Z-window","dZ3 (m+m- & m+m-) in Z-window","dZ4 (m+m- & m+m-) in Z-window",

	"dZ1 (e+e- & e) in Z-veto","dZ2 (e+e- & e) in Z-veto","dZ3 (e+e- & e) in Z-veto","dZ4 (e+e- & e) in Z-veto",
	"dZ1 (e+e- & m) in Z-veto","dZ2 (e+e- & m) in Z-veto","dZ3 (e+e- & m) in Z-veto","dZ4 (e+e- & m) in Z-veto",
	"dZ1 (m+m- & e) in Z-veto","dZ2 (m+m- & e) in Z-veto","dZ3 (m+m- & e) in Z-veto","dZ4 (m+m- & e) in Z-veto",
	"dZ1 (m+m- & m) in Z-veto","dZ2 (m+m- & m) in Z-veto","dZ3 (m+m- & m) in Z-veto","dZ4 (m+m- & m) in Z-veto",
	"dZ1 (e+e- & e+e-) in Z-veto","dZ2 (e+e- & e+e-) in Z-veto","dZ3 (e+e- & e+e-) in Z-veto","dZ4 (e+e- & e+e-) in Z-veto",
	"dZ1 (e+e- & em) in Z-veto","dZ2 (e+e- & em) in Z-veto","dZ3 (e+e- & em) in Z-veto","dZ4 (e+e- & em) in Z-veto",
	"dZ1 (e+e- & m+m-) in Z-veto","dZ2 (e+e- & m+m-) in Z-veto","dZ3 (e+e- & m+m-) in Z-veto","dZ4 (e+e- & m+m-) in Z-veto",
	"dZ1 (blabla) in Z-veto","dZ2 (blabla) in Z-veto","dZ3 (blabla) in Z-veto","dZ4 (blabla) in Z-veto",
	"dZ1 (m+m- & em) in Z-veto","dZ2 (m+m- & em) in Z-veto","dZ3 (m+m- & em) in Z-veto","dZ4 (m+m- & em) in Z-veto",
	"dZ1 (m+m- & m+m-) in Z-veto","dZ2 (m+m- & m+m-) in Z-veto","dZ3 (m+m- & m+m-) in Z-veto","dZ4 (m+m- & m+m-) in Z-veto",

	"ISO1 (e+e- & e) in Z-window","ISO2 (e+e- & e) in Z-window","ISO3 (e+e- & e) in Z-window","ISO4 (e+e- & e) in Z-window",
	"ISO1 (e+e- & m) in Z-window","ISO2 (e+e- & m) in Z-window","ISO3 (e+e- & m) in Z-window","ISO4 (e+e- & m) in Z-window",
	"ISO1 (m+m- & e) in Z-window","ISO2 (m+m- & e) in Z-window","ISO3 (m+m- & e) in Z-window","ISO4 (m+m- & e) in Z-window",
	"ISO1 (m+m- & m) in Z-window","ISO2 (m+m- & m) in Z-window","ISO3 (m+m- & m) in Z-window","ISO4 (m+m- & m) in Z-window",
	"ISO1 (e+e- & e+e-) in Z-window","ISO2 (e+e- & e+e-) in Z-window","ISO3 (e+e- & e+e-) in Z-window","ISO4 (e+e- & e+e-) in Z-window",
	"ISO1 (e+e- & em) in Z-window","ISO2 (e+e- & em) in Z-window","ISO3 (e+e- & em) in Z-window","ISO4 (e+e- & em) in Z-window",
	"ISO1 (e+e- & m+m-) in Z-window","ISO2 (e+e- & m+m-) in Z-window","ISO3 (e+e- & m+m-) in Z-window","ISO4 (e+e- & m+m-) in Z-window",
	"ISO1 (blabla) in Z-window","ISO2 (blabla) in Z-window","ISO3 (blabla) in Z-window","ISO4 (blabla) in Z-window",
	"ISO1 (m+m- & em) in Z-window","ISO2 (m+m- & em) in Z-window","ISO3 (m+m- & em) in Z-window","ISO4 (m+m- & em) in Z-window",
	"ISO1 (m+m- & m+m-) in Z-window","ISO2 (m+m- & m+m-) in Z-window","ISO3 (m+m- & m+m-) in Z-window","ISO4 (m+m- & m+m-) in Z-window",

	"ISO1 (e+e- & e) in Z-veto","ISO2 (e+e- & e) in Z-veto","ISO3 (e+e- & e) in Z-veto","ISO4 (e+e- & e) in Z-veto",
	"ISO1 (e+e- & m) in Z-veto","ISO2 (e+e- & m) in Z-veto","ISO3 (e+e- & m) in Z-veto","ISO4 (e+e- & m) in Z-veto",
	"ISO1 (m+m- & e) in Z-veto","ISO2 (m+m- & e) in Z-veto","ISO3 (m+m- & e) in Z-veto","ISO4 (m+m- & e) in Z-veto",
	"ISO1 (m+m- & m) in Z-veto","ISO2 (m+m- & m) in Z-veto","ISO3 (m+m- & m) in Z-veto","ISO4 (m+m- & m) in Z-veto",
	"ISO1 (e+e- & e+e-) in Z-veto","ISO2 (e+e- & e+e-) in Z-veto","ISO3 (e+e- & e+e-) in Z-veto","ISO4 (e+e- & e+e-) in Z-veto",
	"ISO1 (e+e- & em) in Z-veto","ISO2 (e+e- & em) in Z-veto","ISO3 (e+e- & em) in Z-veto","ISO4 (e+e- & em) in Z-veto",
	"ISO1 (e+e- & m+m-) in Z-veto","ISO2 (e+e- & m+m-) in Z-veto","ISO3 (e+e- & m+m-) in Z-veto","ISO4 (e+e- & m+m-) in Z-veto",
	"ISO1 (blabla) in Z-veto","ISO2 (blabla) in Z-veto","ISO3 (blabla) in Z-veto","ISO4 (blabla) in Z-veto",
	"ISO1 (m+m- & em) in Z-veto","ISO2 (m+m- & em) in Z-veto","ISO3 (m+m- & em) in Z-veto","ISO4 (m+m- & em) in Z-veto",
	"ISO1 (m+m- & m+m-) in Z-veto","ISO2 (m+m- & m+m-) in Z-veto","ISO3 (m+m- & m+m-) in Z-veto","ISO4 (m+m- & m+m-) in Z-veto",

	};
	TCanvas* canvas = new TCanvas("canvas", "Stacked histograms", 800, 700);//600);
	gStyle->SetOptStat(0);	
	
// make changes to take in xs from a csv file
	for(int i = 0; i < sizeof(hist_list)/sizeof(hist_list[0]); i++){
		//TH1F *h_sig = (TH1F*)ifile_sig->Get(hist_list[i]); h_sig->SetLineStyle(5);h_sig->SetLineWidth(2);h_sig->SetLineColor(2);h_sig->Scale(10);
		
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
		//TH1F *h22 = (TH1F*)ifile22->Get(hist_list[i]);h22->SetFillColor(28);
		//TH1F *h23 = (TH1F*)ifile23->Get(hist_list[i]);h23->SetFillColor(28);
		TH1F *h24 = (TH1F*)ifile24->Get(hist_list[i]);h24->SetFillColor(28);
		TH1F *h25 = (TH1F*)ifile25->Get(hist_list[i]);h25->SetFillColor(28);
		TH1F *h26 = (TH1F*)ifile26->Get(hist_list[i]);h26->SetFillColor(28);
		TH1F *h27 = (TH1F*)ifile27->Get(hist_list[i]);h27->SetFillColor(28);
		
		TH1F *hD1 = (TH1F*)ifileD1->Get(hist_list[i]);
		//TH1F *hD2 = (TH1F*)ifileD2->Get(hist_list[i]);
		//TH1F *hD3 = (TH1F*)ifileD3->Get(hist_list[i]);
		//TH1F *hD4 = (TH1F*)ifileD4->Get(hist_list[i]);
		TH1F *hD5 = (TH1F*)ifileD5->Get(hist_list[i]);
				
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
		//bkg_stack->Add(h22);
		//bkg_stack->Add(h23);
		bkg_stack->Add(h24);
		bkg_stack->Add(h25);
		bkg_stack->Add(h26);
		bkg_stack->Add(h27);

		TH1F *h_bkg_total = (TH1F*)h1->Clone("h_bkg_total");
    	h_bkg_total->Add(h2);
    	//h_bkg_total->Add(h3);
		h_bkg_total->Add(h4);
		h_bkg_total->Add(h5);
		//h_bkg_total->Add(h6);
		h_bkg_total->Add(h7);
		h_bkg_total->Add(h8);
		h_bkg_total->Add(h9);
		h_bkg_total->Add(h10);
		h_bkg_total->Add(h15); 
		h_bkg_total->Add(h11);
		h_bkg_total->Add(h12);
		h_bkg_total->Add(h1201);
		h_bkg_total->Add(h13);
		h_bkg_total->Add(h14);
		h_bkg_total->Add(h16);
		h_bkg_total->Add(h17);
		h_bkg_total->Add(h18);
		h_bkg_total->Add(h19);
		h_bkg_total->Add(h20);
		h_bkg_total->Add(h21);
		//h_bkg_total->Add(h22);
		//h_bkg_total->Add(h23);
		h_bkg_total->Add(h24);
		h_bkg_total->Add(h25);
		h_bkg_total->Add(h26);
		h_bkg_total->Add(h27);
		
		TH1F *h_data_total = (TH1F*)hD1->Clone("h_data_total");
		h_data_total->SetMarkerColor(1);
		h_data_total->SetMarkerStyle(kFullDotLarge);
		h_data_total->Add(hD5);

		canvas->Divide(1, 2);				
		// Adjust the upper pad (stacked plot)
		TPad *pad1 = (TPad*)canvas->cd(1);
		pad1->SetPad(0, 0.3, 1, 1);
		pad1->SetBottomMargin(0.01); // Remove bottom margin to reduce gap
		
		
		h_data_total->Draw();
		bkg_stack->Draw("HIST SAME");
		
		//TLegend* legend = new TLegend(0.1, 0.9, 0.3, 0.7);
		TLegend* legend = new TLegend(0.65, 0.65, 0.9, 0.9);	
		//legend->AddEntry(h_sig, "M900*1000");
		legend->AddEntry(h8, "VV", "f");
		legend->AddEntry(h9, "VVV", "f");
		legend->AddEntry(h1, "DY", "f");
		legend->AddEntry(h13, "ZZ", "f");
		legend->AddEntry(h12, "TTVJets", "f");
		legend->AddEntry(h16, "ST", "f");
		legend->AddEntry(h24, "other BKGs", "f");
		legend->AddEntry(h_data_total, "Data");
		legend->Draw();		


		// Adjust the lower pad (ratio plot)
		TPad *pad2 = (TPad*)canvas->cd(2);
		pad2->SetPad(0, 0, 1, 0.3);
		pad2->SetTopMargin(0.01);
		pad2->SetBottomMargin(0.3);
		
		// Create the Data/MC ratio plot
		TH1F *h_ratio = (TH1F*)h_data_total->Clone("h_ratio");
		h_ratio->Divide(h_bkg_total);
		h_ratio->SetLineColor(kBlack);
		h_ratio->SetMarkerStyle(2);
		h_ratio->SetTitle(""); // Remove the title for the ratio plot
		h_ratio->GetYaxis()->SetTitle("Data/MC");
		h_ratio->GetYaxis()->SetNdivisions(505);
		h_ratio->GetYaxis()->SetTitleSize(0.07);
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
		
		std::string s =  "hist_test_nopair/";
		s = s + hist_list[i]+".png";
		char* title = const_cast<char*>(s.c_str());//converting string to char
		canvas->SaveAs(title);
		canvas->Clear();
	}
}
