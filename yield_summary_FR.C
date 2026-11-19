#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <THStack.h>
#include <TPad.h>
#include <TLegend.h>
#include <vector>
#include <string>
#include <map>
#include "include/Xsections.C"
#include "include/cms_plots.h"
#include "include/FileMap.h"

void yield_summary_FR() {gErrorIgnoreLevel = kError; 
    gStyle->SetOptStat(0);
    TCanvas* canvas = new TCanvas("canvas", "Stacked histograms", 800, 700);

    // Split canvas for main plot and ratio plot
    TPad* pad1 = new TPad("pad1", "Top pad", 0.0, 0.3, 1.0, 1.0);
    TPad* pad2 = new TPad("pad2", "Bottom pad", 0.0, 0.0, 1.0, 0.3);
    pad1->SetBottomMargin(0.01);
    pad2->SetTopMargin(0.01);
    pad2->SetBottomMargin(0.3);
    pad1->Draw();
    pad2->Draw();
	
	THStack* bkg_stack;
	std::string summary_type = "tau_ch", year = "Run2";
    // Define histograms to retrieve
    std::vector<std::string> hist_list;
    const char* plot_description; 
    if (summary_type == "tau_ch") {
    	hist_list = { "h_LT_CR_0tau","h_LT_CR_1tau","h_LT_CR_2tau","h_LT_CR_3tau","h_LT_CR_3lep0tau","h_LT_CR_3lep1tau","h_LT_CR_3lep2tau"};
    	bkg_stack = new THStack("bkg_stack", " ;;Events / bin");//empty title
    	plot_description = "Yield summary in CR";
    }
    if (summary_type == "tau_ch-veto") {
    	hist_list = { "h_LT_VR_0tau","h_LT_VR_1tau","h_LT_VR_2tau","h_LT_VR_3tau","h_LT_VR_3lep0tau","h_LT_VR_3lep1tau","h_LT_VR_3lep2tau"};
    	bkg_stack = new THStack("bkg_stack", " ;;Events / bin");//empty title
    	plot_description = "Yield summary in VR";
    }
    else if  (summary_type == "3lep") {
    	hist_list = {"h_met_ee","h_met_eee","h_met_eem","h_met_eet","h_metv_ett","h_met_mm","h_met_emm","h_met_mmm","h_met_mmt","h_metv_mtt"};
   		bkg_stack = new THStack("bkg_stack", ";;Events / bin");
   		plot_description = "2l and 3l channel summary in Z-window";
    }
    else if  (summary_type == "3lep-veto") {
    	hist_list = {"h_metv_ee","h_metv_eee","h_metv_eem","h_metv_eet","h_met_ett","h_metv_mm","h_metv_mme","h_metv_mmm","h_metv_mmt","h_met_mtt"};
    	bkg_stack = new THStack("bkg_stack", ";;Events / bin");
    	plot_description = "2l and 3l channel summary in Z-veto";
    }
    else if  (summary_type == "4lep") { 
    	hist_list = {"h_met_eeee","h_met_eeem","h_met_eemm","h_met_mmem","h_met_mmmm","h_met_eeet","h_met_eemt","h_met_eett","h_met_emtt","h_met_emmt","h_met_ettt","h_met_mmmt","h_met_mmtt","h_met_mttt"};
    	bkg_stack = new THStack("bkg_stack", ";;Events / bin");
    	plot_description = "4l channel summary in Z-window";
    }
    else if  (summary_type == "4lep-veto") {
    	hist_list = {"h_metv_eeee","h_metv_eeem","h_metv_eemm","h_metv_mmem","h_metv_mmmm","h_metv_eeet","h_metv_eemt","h_metv_eett","h_metv_emtt","h_metv_emmt","h_metv_ettt","h_metv_mmmt","h_metv_mmtt","h_metv_mttt"};
    	bkg_stack = new THStack("bkg_stack", ";;Events / bin");
    	plot_description = "4l channel summary in Z-veto";
    }
    int bins = hist_list.size();

    std::map<std::string, TH1D*> h_summaries;
    std::map<std::string, int> fill_colors = {
            {"DY",7},{"VV",8},{"VVV",6},{"ttV",4},{"WJ",9},
    {"ZZ",5},{"ST",30},{"TTbar",46},{"other",28},{"data",1}
};
    
	// Open files
    map<string,vector<string>> files;
    files = getFileMap(year);
    std::map<std::string, std::vector<TFile*>> open_files;
	for (auto& kv : files) {
        for (const auto& fname : kv.second) {
        	//if (fname.find("preVFP") < fname.length()) continue;
        	TFile* file;
            if (summary_type == "tau_ch") file = new TFile(("hist_test_nopair_noFR/" + fname).c_str(), "READ");
            else file = new TFile(("hist_test_nopair_noFR/" + fname).c_str(), "READ");
            if (!file || file->IsZombie()) continue;
	        open_files[kv.first].push_back(file);
        }
        h_summaries[kv.first] = new TH1D(("h_summary_" + kv.first).c_str(), "Yields;;Yield", bins, 0.5, bins + 0.5);
        h_summaries[kv.first]->Sumw2();
        h_summaries[kv.first]->SetFillColor(fill_colors[kv.first]);
    }

    // Loop over histograms and fill yield summaries and ratio plot
    //double tot_uncert_quadr[bins];
    for (int i = 0; i < bins; ++i) {
        std::string hist_name = hist_list[i];
        for (auto& kv : open_files) {
            double total = 0; 
            TH1D* h_sum = new TH1D("h_sum"," ;;;",1,0,1); h_sum->Sumw2();
            for (auto* f : kv.second) {
            	string fname = f->GetName();
            	//if(fname.find("F_2016preVFP") < fname.length()) continue;
            	//if(kv.first != "data" and fname.find("2016preVFP") < fname.length()) continue;
            	TH1D* h = (TH1D*)f->Get(hist_name.c_str());
                if (h) {
                	h_sum->Sumw2();
                	h->Scale(applyXSec(f));
                	h->Rebin(h->GetNbinsX());
                	double stat_err = h->GetBinError(1);//poisson error
                	double sys_err = h->GetBinContent(1)*XSec_Uncert(f->GetName())/100;
                	double tot_uncert_quadr = (stat_err*stat_err + sys_err*sys_err);
                	if (kv.first != "data") {
                		if(summary_type == "tau_ch"){
                			if (hist_name.find("3lep") < hist_name.length()) tot_uncert_quadr += fake_uncert_squared("3lep", f->GetName())*h->GetBinContent(1)*h->GetBinContent(1);
                			else tot_uncert_quadr += fake_uncert_squared("4lep", f->GetName())*h->GetBinContent(1)*h->GetBinContent(1);
                		}
                		else if(hist_name != "h_met_ee" and hist_name != "h_met_mm" and hist_name != "h_metv_ee" and hist_name != "h_metv_mm") tot_uncert_quadr += fake_uncert_squared(summary_type, f->GetName())*h->GetBinContent(1)*h->GetBinContent(1);
                	}
                	h->SetBinError(1,sqrt(tot_uncert_quadr));
                	h_sum->Add(h);
                }
            }
            h_summaries[kv.first]->SetBinContent(i+1, h_sum->GetBinContent(1));
            h_summaries[kv.first]->SetBinError(i+1, h_sum->GetBinError(1));
            cout<<i+1<<"\t"<<kv.first<<"\t"<<h_summaries[kv.first]->GetBinError(i+1)<<endl;
        }
    }
    //========================scale facotrs===============
	h_summaries["ZZ"]->Scale(1.284495);
	h_summaries["VV"]->Scale(1.033462);
	//h_summaries["DY"]->SetBinContent(4, h_summaries["DY"]->GetBinContent(4)*1.21);
	//h_summaries["DY"]->SetBinContent(9, h_summaries["DY"]->GetBinContent(9)*1.21);
	//h_summaries["TTbar"]->SetBinContent(6, h_summaries["TTbar"]->GetBinContent(6)*2.5);
	//h_summaries["TTbar"]->SetBinContent(1, h_summaries["TTbar"]->GetBinContent(1)*1.5);
	
	//====================================================
    // Stack backgrounds
    TH1D* h_bkg_total = (TH1D*)h_summaries["DY"]->Clone("h_bkg_total");
    h_bkg_total->Reset(); h_bkg_total->Sumw2();
    for (const std::string& bkg_group : {"DY","VV","VVV","ttV","WJ","ZZ","ST","TTbar","other"}) {
        bkg_stack->Add(h_summaries[bkg_group]);
        bkg_stack->SetMinimum(1); // Show zero bins
        h_bkg_total->Add(h_summaries[bkg_group]);
    }
    
    TH1D* h_mc_uncert_band = (TH1D*) h_bkg_total->Clone("h_mc_uncert_band");
    h_mc_uncert_band->Sumw2();
	h_mc_uncert_band->Reset(); // we'll fill the error by hand
	for (int i = 0; i < bins; ++i) {
		h_mc_uncert_band->SetBinContent(i+1, 1.0);  // center at ratio = 1
		if (h_bkg_total->GetBinContent(i+1) != 0) h_mc_uncert_band->SetBinError(i+1, h_bkg_total->GetBinError(i+1)/h_bkg_total->GetBinContent(i+1));//scaling error with bin content
		else h_mc_uncert_band->SetBinError(i+1,0);
		//cout<<h_bkg_total->GetBinContent(i+1)<<"\t"<<h_bkg_total->GetBinError(i+1)<<"\t"<<h_mc_uncert_band->GetBinError(i+1)<<endl;
	} 
	
    // Draw main plot
    pad1->cd();
    gPad->SetLogy(1);
    bkg_stack->Draw("hist");
    double pad_max = std::max(bkg_stack->GetMaximum(),h_summaries["data"]->GetMaximum());
	bkg_stack->SetMaximum(1.1*pad_max);
    h_summaries["data"]->SetMarkerStyle(20);
    h_summaries["data"]->SetMarkerColor(kBlack);
    h_summaries["data"]->Draw("E SAME ");

	// Create a TLatex object
	DrawCMSLabel();
	PlotDescription(plot_description);
	
    //auto legend = new TLegend(0.7, 0.6, 0.88, 0.88);
    auto legend = new TLegend(0.12, 0.6, 0.3, 0.88);
    for (const std::string& bkg_group : {"DY","VV","VVV","ttV","WJ","ZZ","ST","TTbar","other"}) {
        legend->AddEntry(h_summaries[bkg_group], bkg_group.c_str(), "f");
    }
    legend->AddEntry(h_summaries["data"], "Data", "lep");
    legend->SetBorderSize(0);
    legend->Draw();

    // Ratio histogram: data / MC
    TH1D* h_ratio = (TH1D*)h_summaries["data"]->Clone("h_ratio");
    h_ratio->SetTitle(""); // Remove the title for the ratio plot
	h_ratio->Divide(h_bkg_total);
	h_ratio->SetLineColor(kBlack);
	h_ratio->SetMarkerStyle(20);
	h_ratio->GetYaxis()->SetTitle("Data / Background");
	h_ratio->GetYaxis()->SetNdivisions(505);
	h_ratio->GetYaxis()->SetTitleSize(0.09);
	h_ratio->GetYaxis()->SetTitleOffset(0.4);
	h_ratio->GetYaxis()->SetLabelSize(0.07);
	h_ratio->GetXaxis()->SetTitleSize(0.1);
	
	if (summary_type == "tau_ch") {
		h_ratio->GetXaxis()->SetBinLabel(1,"4l,0#tau");
		h_ratio->GetXaxis()->SetBinLabel(2,"4l,1#tau");
		h_ratio->GetXaxis()->SetBinLabel(3,"4l,2#tau");
		h_ratio->GetXaxis()->SetBinLabel(4,"4l,3#tau");
		h_ratio->GetXaxis()->SetBinLabel(5,"3l,0#tau");
		h_ratio->GetXaxis()->SetBinLabel(6,"3l,1#tau");
		h_ratio->GetXaxis()->SetBinLabel(7,"3l,2#tau");
	}	
	else if (summary_type == "3lep" or summary_type == "3lep-veto" ) {
		h_ratio->GetXaxis()->SetBinLabel(1,"ee");
		h_ratio->GetXaxis()->SetBinLabel(2,"ee+e");
		h_ratio->GetXaxis()->SetBinLabel(3,"ee+#mu");
		h_ratio->GetXaxis()->SetBinLabel(4,"ee+#tau");
		h_ratio->GetXaxis()->SetBinLabel(5,"e#tau#tau");
		h_ratio->GetXaxis()->SetBinLabel(6,"#mu#mu");
		h_ratio->GetXaxis()->SetBinLabel(7,"#mu#mu+e");
		h_ratio->GetXaxis()->SetBinLabel(8,"#mu#mu+#mu");
		h_ratio->GetXaxis()->SetBinLabel(9,"#mu#mu+#tau");
		h_ratio->GetXaxis()->SetBinLabel(10,"#mu#tau#tau");
	}
	else if (summary_type == "4lep" or summary_type == "4lep-veto") {
		h_ratio->GetXaxis()->SetBinLabel(1,"eeee");
		h_ratio->GetXaxis()->SetBinLabel(2,"eee#mu");
		h_ratio->GetXaxis()->SetBinLabel(3,"ee#mu#mu");
		h_ratio->GetXaxis()->SetBinLabel(4,"#mu#mue#mu");
		h_ratio->GetXaxis()->SetBinLabel(5,"#mu#mu#mu#mu");
		h_ratio->GetXaxis()->SetBinLabel(6,"eee#tau");
		h_ratio->GetXaxis()->SetBinLabel(7,"ee#mu#tau");
		h_ratio->GetXaxis()->SetBinLabel(8,"ee#tau#tau");
		h_ratio->GetXaxis()->SetBinLabel(9,"e#mu#tau#tau");
		h_ratio->GetXaxis()->SetBinLabel(10,"e#mu#mu#tau");
		h_ratio->GetXaxis()->SetBinLabel(11,"e#tau#tau#tau");
		h_ratio->GetXaxis()->SetBinLabel(12,"#mu#mu#mu#tau");
		h_ratio->GetXaxis()->SetBinLabel(13,"#mu#mu#tau#tau");
		h_ratio->GetXaxis()->SetBinLabel(14,"#mu#tau#tau#tau");
	}
	
	h_ratio->GetXaxis()->SetLabelSize(0.15);
	h_ratio->SetMinimum(0); // Set the minimum y-value for the ratio plot
	h_ratio->SetMaximum(2); // Set the maximum y-value for the ratio plot
	
    // Draw ratio plot
    pad2->cd();
    h_ratio->SetMinimum(0.0);
    h_ratio->SetMaximum(2.0);
    h_ratio->Draw("E");
    
    h_mc_uncert_band->SetFillColor(kGray+2);
	h_mc_uncert_band->SetFillStyle(3001); // hatched
	h_mc_uncert_band->SetLineColor(0);
	h_mc_uncert_band->Draw("E2 same"); // as a filled error band
	
    // Draw lines for reference
	TLine *line1 = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
	TLine *line2 = new TLine(h_ratio->GetXaxis()->GetXmin(), 0.5, h_ratio->GetXaxis()->GetXmax(), 0.5);
	TLine *line3 = new TLine(h_ratio->GetXaxis()->GetXmin(), 1.5, h_ratio->GetXaxis()->GetXmax(), 1.5);
	line1->SetLineStyle(2);line2->SetLineStyle(2);line3->SetLineStyle(2);
	line1->Draw();line2->Draw();line3->Draw();

    // Output
    //std::string pdfname = "summary_"+summary_type+"_"+year+".pdf";
    std::string pngname = "summary_"+summary_type+"_"+year+".png";
    //canvas->SaveAs(const_cast<char*>(pdfname.c_str()));
    canvas->SaveAs(const_cast<char*>(pngname.c_str()));
}
