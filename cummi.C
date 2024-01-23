#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>

void cummi() {
	TFile *ifile_sig = new TFile("hist/HppM500_2018.root","READ"); 
	TH1F* hpx = (TH1F*)ifile_sig->Get("h_mZ1");
	TH1F* h_cumm = new TH1F("h_cumm", hpx->GetTitle(), hpx->GetNbinsX(), hpx->GetXaxis()->GetXmin() , hpx->GetXaxis()->GetXmax());

	float tmp_val = 0;
	for (int i =0; i < hpx->GetNbinsX(); i++){ 
		tmp_val = hpx->Integral(i,101);
		cout<<i<<"\t"<<tmp_val<<endl;    
		h_cumm->SetBinContent(i, tmp_val);
		// Show the canvas
		//canvas->Update();
		//canvas->Modified();
	}
	cout<<h_cumm->GetBinContent(hpx->GetNbinsX()+1)<<endl;
	h_cumm->Draw();
	std::string s =  "cummi";
	s = s+".png";
	char* title = const_cast<char*>(s.c_str());//converting string to char
	//canvas->SaveAs(title);
}
