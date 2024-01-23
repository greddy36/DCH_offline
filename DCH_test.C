#include "TMath.h"
#include <cmath>
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"

void DCH_test(){
	TCanvas *can= new TCanvas("can","can",700,500); gStyle->SetOptStat(0); 
	TFile *ifile_sig1 = new TFile("HppM500_2018.root","READ");
	TFile *ifile_sig2 = new TFile("HppM900_2018.root","READ"); 
	TFile *ifile_bkg1 = new TFile("ZZTo4L_2018.root","READ"); 
	TFile *ifile_bkg2 = new TFile("ZZTo2Q2L_2018.root","READ"); 
	
	TTree *tree_sig1 = (TTree*)ifile_sig1->Get("Events");
	tree_sig1->SetLineColor(kRed);
	TTree *tree_bkg1 = (TTree*)ifile_bkg1->Get("Events");
	tree_bkg1->SetLineColor(kBlue);
	TTree *tree_bkg2 = (TTree*)ifile_bkg2->Get("Events");
	tree_bkg2->SetLineColor(kGreen);
		    
		    
	const char *condition = "";
    //const char *condition = "pt_1 >120 && pt_2>90 && pt_3 > 100 && pt_4>90";
    //const char *condition = "mll >250 && mll2>200";
    //const char *condition = "pt_1+pt_2 > 210 && pt_3+pt_4 > 190";
	//const char *condition = "(mll >250 && mll2>200)&(pt_1+pt_2 > 210 && pt_3+pt_4 > 190)";
    const char *var[] = {"mll","mll2","pt_1","pt_2","pt_3","pt_4","eta_1","eta_2","eta_3","eta_4","phi_1","phi_2","phi_3","phi_4","cat","d0_1","d0_2","d0_3","d0_4","dZ_1","dZ_2","dZ_3","dZ_4","met","metphi"};
    for (int i = 0; i <= sizeof(var)/sizeof(var[0])-1; i++){
		tree_sig1->Draw(var[i],condition,"norm hist"); 
		tree_bkg1->Draw(var[i],condition,"norm hist same");
		//tree_bkg2->Draw(var[i],condition,"norm hist same");
		
		TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
		legend->AddEntry(tree_sig1, "M500", "l");
		legend->AddEntry(tree_bkg1, "ZZto4L", "l");
		//legend->AddEntry(tree_bkg2, "ZZto2Q2L", "l");
		legend->Draw();
		
		std::string title="plots/";
		title.append(var[i]);
		title.append(".png");
		can->SaveAs(const_cast<char*>(title.c_str()));
	}
	cout<< "Signal : "<<tree_sig1->GetEntries(condition)*1.0*59.6*1000/176000<<endl; 
	cout<< "ZZto4L : "<<tree_bkg1->GetEntries(condition)*1.325*59.6*1000/97570000<<endl;
	cout<< "ZZto2Q2L : "<<tree_bkg2->GetEntries(condition)*3.22*59.6*1000/26962069<<endl;
}
/*    cat = {1:'eeee',2:'eeem',3:'eeet',4:'eemm',5:'eemt',6:'eett',
               7:'emem',8:'emet',9:'emmm',10:'emmt',11:'emtt',
                      12:'etet',13:'etmm',14:'etmt',15:'ettt',
                             16:'mmmm',17:'mmmt',18:'mmtt',
                                    19:'mtmt',20:'mttt',
                                           21:'tttt'}
*/