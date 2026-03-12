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

void StackHist_test() {
	std::string summary_type = "tau_c", year = "Run2";
    // Define histograms to retrieve
    const char *hist_list[] = 
    {
"h_mZ1_ee","h_mZ1_em","h_mZ1_mm","h_mZ1_eee","h_mZ1_eem","h_mZ1_eet","h_mZ1_emt","h_mZ1_emm","h_mZ1_mmm","h_mZ1_mmt","h_mZ1_ett","h_mZ1_mtt","h_mZ1_eeee","h_mZ1_eeem","h_mZ1_eemm","h_mZ1_mmem","h_mZ1_mmmm","h_mZ1_eeet","h_mZ1_eemt","h_mZ1_eett","h_mZ1_emtt","h_mZ1_emmt","h_mZ1_ettt","h_mZ1_mmmt","h_mZ1_mmtt","h_mZ1_mttt",

"h_mH1_ee","h_mH1_em","h_mH1_mm","h_mH1_eee","h_mH1_eem","h_mH1_eet","h_mH1_emt","h_mH1_emm","h_mH1_mmm","h_mH1_mmt","h_mH1_ett","h_mH1_mtt","h_mH1_eeee","h_mH1_eeem","h_mH1_eemm","h_mH1_mmem","h_mH1_mmmm","h_mH1_eeet","h_mH1_eemt","h_mH1_eett","h_mH1_emtt","h_mH1_emmt","h_mH1_ettt","h_mH1_mmmt","h_mH1_mmtt","h_mH1_mttt",

"h_mZ2_ee","h_mZ2_em","h_mZ2_mm","h_mZ2_eee","h_mZ2_eem","h_mZ2_eet","h_mZ2_emt","h_mZ2_emm","h_mZ2_mmm","h_mZ2_mmt","h_mZ2_ett","h_mZ2_mtt","h_mZ2_eeee","h_mZ2_eeem","h_mZ2_eemm","h_mZ2_mmem","h_mZ2_mmmm","h_mZ2_eeet","h_mZ2_eemt","h_mZ2_eett","h_mZ2_emtt","h_mZ2_emmt","h_mZ2_ettt","h_mZ2_mmmt","h_mZ2_mmtt","h_mZ2_mttt",

"h_mH2_ee","h_mH2_em","h_mH2_mm","h_mH2_eee","h_mH2_eem","h_mH2_eet","h_mH2_emt","h_mH2_emm","h_mH2_mmm","h_mH2_mmt","h_mH2_ett","h_mH2_mtt","h_mH2_eeee","h_mH2_eeem","h_mH2_eemm","h_mH2_mmem","h_mH2_mmmm","h_mH2_eeet","h_mH2_eemt","h_mH2_eett","h_mH2_emtt","h_mH2_emmt","h_mH2_ettt","h_mH2_mmmt","h_mH2_mmtt","h_mH2_mttt",

"h_met_ee","h_met_em","h_met_mm","h_met_eee","h_met_eem","h_met_eet","h_met_emt","h_met_emm","h_met_mmm","h_met_mmt","h_met_ett","h_met_mtt","h_met_eeee","h_met_eeem","h_met_eemm","h_met_mmem","h_met_mmmm","h_met_eeet","h_met_eemt","h_met_eett","h_met_emtt","h_met_emmt","h_met_ettt","h_met_mmmt","h_met_mmtt","h_met_mttt",

"h_LT_ee","h_LT_em","h_LT_mm","h_LT_eee","h_LT_eem","h_LT_eet","h_LT_emt","h_LT_emm","h_LT_mmm","h_LT_mmt","h_LT_ett","h_LT_mtt","h_LT_eeee","h_LT_eeem","h_LT_eemm","h_LT_mmem","h_LT_mmmm","h_LT_eeet","h_LT_eemt","h_LT_eett","h_LT_emtt","h_LT_emmt","h_LT_ettt","h_LT_mmmt","h_LT_mmtt","h_LT_mttt",

"h_pt1_ee","h_pt1_em","h_pt1_mm","h_pt1_eee","h_pt1_eem","h_pt1_eet","h_pt1_emt","h_pt1_emm","h_pt1_mmm","h_pt1_mmt","h_pt1_ett","h_pt1_mtt","h_pt1_eeee","h_pt1_eeem","h_pt1_eemm","h_pt1_mmem","h_pt1_mmmm","h_pt1_eeet","h_pt1_eemt","h_pt1_eett","h_pt1_emtt","h_pt1_emmt","h_pt1_ettt","h_pt1_mmmt","h_pt1_mmtt","h_pt1_mttt",

"h_pt2_ee","h_pt2_em","h_pt2_mm","h_pt2_eee","h_pt2_eem","h_pt2_eet","h_pt2_emt","h_pt2_emm","h_pt2_mmm","h_pt2_mmt","h_pt2_ett","h_pt2_mtt","h_pt2_eeee","h_pt2_eeem","h_pt2_eemm","h_pt2_mmem","h_pt2_mmmm","h_pt2_eeet","h_pt2_eemt","h_pt2_eett","h_pt2_emtt","h_pt2_emmt","h_pt2_ettt","h_pt2_mmmt","h_pt2_mmtt","h_pt2_mttt",

"h_pt3_ee","h_pt3_em","h_pt3_mm","h_pt3_eee","h_pt3_eem","h_pt3_eet","h_pt3_emt","h_pt3_emm","h_pt3_mmm","h_pt3_mmt","h_pt3_ett","h_pt3_mtt","h_pt3_eeee","h_pt3_eeem","h_pt3_eemm","h_pt3_mmem","h_pt3_mmmm","h_pt3_eeet","h_pt3_eemt","h_pt3_eett","h_pt3_emtt","h_pt3_emmt","h_pt3_ettt","h_pt3_mmmt","h_pt3_mmtt","h_pt3_mttt",

"h_pt4_ee","h_pt4_em","h_pt4_mm","h_pt4_eee","h_pt4_eem","h_pt4_eet","h_pt4_emt","h_pt4_emm","h_pt4_mmm","h_pt4_mmt","h_pt4_ett","h_pt4_mtt","h_pt4_eeee","h_pt4_eeem","h_pt4_eemm","h_pt4_mmem","h_pt4_mmmm","h_pt4_eeet","h_pt4_eemt","h_pt4_eett","h_pt4_emtt","h_pt4_emmt","h_pt4_ettt","h_pt4_mmmt","h_pt4_mmtt","h_pt4_mttt",

"h_eta1_ee","h_eta1_em","h_eta1_mm","h_eta1_eee","h_eta1_eem","h_eta1_eet","h_eta1_emt","h_eta1_emm","h_eta1_mmm","h_eta1_mmt","h_eta1_ett","h_eta1_mtt","h_eta1_eeee","h_eta1_eeem","h_eta1_eemm","h_eta1_mmem","h_eta1_mmmm","h_eta1_eeet","h_eta1_eemt","h_eta1_eett","h_eta1_emtt","h_eta1_emmt","h_eta1_ettt","h_eta1_mmmt","h_eta1_mmtt","h_eta1_mttt",

"h_eta2_ee","h_eta2_em","h_eta2_mm","h_eta2_eee","h_eta2_eem","h_eta2_eet","h_eta2_emt","h_eta2_emm","h_eta2_mmm","h_eta2_mmt","h_eta2_ett","h_eta2_mtt","h_eta2_eeee","h_eta2_eeem","h_eta2_eemm","h_eta2_mmem","h_eta2_mmmm","h_eta2_eeet","h_eta2_eemt","h_eta2_eett","h_eta2_emtt","h_eta2_emmt","h_eta2_ettt","h_eta2_mmmt","h_eta2_mmtt","h_eta2_mttt",

"h_eta3_ee","h_eta3_em","h_eta3_mm","h_eta3_eee","h_eta3_eem","h_eta3_eet","h_eta3_emt","h_eta3_emm","h_eta3_mmm","h_eta3_mmt","h_eta3_ett","h_eta3_mtt","h_eta3_eeee","h_eta3_eeem","h_eta3_eemm","h_eta3_mmem","h_eta3_mmmm","h_eta3_eeet","h_eta3_eemt","h_eta3_eett","h_eta3_emtt","h_eta3_emmt","h_eta3_ettt","h_eta3_mmmt","h_eta3_mmtt","h_eta3_mttt",

"h_eta4_ee","h_eta4_em","h_eta4_mm","h_eta4_eee","h_eta4_eem","h_eta4_eet","h_eta4_emt","h_eta4_emm","h_eta4_mmm","h_eta4_mmt","h_eta4_ett","h_eta4_mtt","h_eta4_eeee","h_eta4_eeem","h_eta4_eemm","h_eta4_mmem","h_eta4_mmmm","h_eta4_eeet","h_eta4_eemt","h_eta4_eett","h_eta4_emtt","h_eta4_emmt","h_eta4_ettt","h_eta4_mmmt","h_eta4_mmtt","h_eta4_mttt",

"h_phi1_ee","h_phi1_em","h_phi1_mm","h_phi1_eee","h_phi1_eem","h_phi1_eet","h_phi1_emt","h_phi1_emm","h_phi1_mmm","h_phi1_mmt","h_phi1_ett","h_phi1_mtt","h_phi1_eeee","h_phi1_eeem","h_phi1_eemm","h_phi1_mmem","h_phi1_mmmm","h_phi1_eeet","h_phi1_eemt","h_phi1_eett","h_phi1_emtt","h_phi1_emmt","h_phi1_ettt","h_phi1_mmmt","h_phi1_mmtt","h_phi1_mttt",

"h_phi2_ee","h_phi2_em","h_phi2_mm","h_phi2_eee","h_phi2_eem","h_phi2_eet","h_phi2_emt","h_phi2_emm","h_phi2_mmm","h_phi2_mmt","h_phi2_ett","h_phi2_mtt","h_phi2_eeee","h_phi2_eeem","h_phi2_eemm","h_phi2_mmem","h_phi2_mmmm","h_phi2_eeet","h_phi2_eemt","h_phi2_eett","h_phi2_emtt","h_phi2_emmt","h_phi2_ettt","h_phi2_mmmt","h_phi2_mmtt","h_phi2_mttt",

"h_phi3_ee","h_phi3_em","h_phi3_mm","h_phi3_eee","h_phi3_eem","h_phi3_eet","h_phi3_emt","h_phi3_emm","h_phi3_mmm","h_phi3_mmt","h_phi3_ett","h_phi3_mtt","h_phi3_eeee","h_phi3_eeem","h_phi3_eemm","h_phi3_mmem","h_phi3_mmmm","h_phi3_eeet","h_phi3_eemt","h_phi3_eett","h_phi3_emtt","h_phi3_emmt","h_phi3_ettt","h_phi3_mmmt","h_phi3_mmtt","h_phi3_mttt",

"h_phi4_ee","h_phi4_em","h_phi4_mm","h_phi4_eee","h_phi4_eem","h_phi4_eet","h_phi4_emt","h_phi4_emm","h_phi4_mmm","h_phi4_mmt","h_phi4_ett","h_phi4_mtt","h_phi4_eeee","h_phi4_eeem","h_phi4_eemm","h_phi4_mmem","h_phi4_mmmm","h_phi4_eeet","h_phi4_eemt","h_phi4_eett","h_phi4_emtt","h_phi4_emmt","h_phi4_ettt","h_phi4_mmmt","h_phi4_mmtt","h_phi4_mttt",

/*

"h_mZ1v_ee","h_mZ1v_em","h_mZ1v_mm","h_mZ1v_eee","h_mZ1v_eem","h_mZ1v_eet","h_mZ1v_emt","h_mZ1v_emm","h_mZ1v_mmm","h_mZ1v_mmt","h_mZ1v_ett","h_mZ1v_mtt","h_mZ1v_eeee","h_mZ1v_eeem","h_mZ1v_eemm","h_mZ1v_mmem","h_mZ1v_mmmm","h_mZ1v_eeet","h_mZ1v_eemt","h_mZ1v_eett","h_mZ1v_emtt","h_mZ1v_emmt","h_mZ1v_ettt","h_mZ1v_mmmt","h_mZ1v_mmtt","h_mZ1v_mttt",

"h_mH1v_ee","h_mH1v_em","h_mH1v_mm","h_mH1v_eee","h_mH1v_eem","h_mH1v_eet","h_mH1v_emt","h_mH1v_emm","h_mH1v_mmm","h_mH1v_mmt","h_mH1v_ett","h_mH1v_mtt","h_mH1v_eeee","h_mH1v_eeem","h_mH1v_eemm","h_mH1v_mmem","h_mH1v_mmmm","h_mH1v_eeet","h_mH1v_eemt","h_mH1v_eett","h_mH1v_emtt","h_mH1v_emmt","h_mH1v_ettt","h_mH1v_mmmt","h_mH1v_mmtt","h_mH1v_mttt",

"h_mZ2v_ee","h_mZ2v_em","h_mZ2v_mm","h_mZ2v_eee","h_mZ2v_eem","h_mZ2v_eet","h_mZ2v_emt","h_mZ2v_emm","h_mZ2v_mmm","h_mZ2v_mmt","h_mZ2v_ett","h_mZ2v_mtt","h_mZ2v_eeee","h_mZ2v_eeem","h_mZ2v_eemm","h_mZ2v_mmem","h_mZ2v_mmmm","h_mZ2v_eeet","h_mZ2v_eemt","h_mZ2v_eett","h_mZ2v_emtt","h_mZ2v_emmt","h_mZ2v_ettt","h_mZ2v_mmmt","h_mZ2v_mmtt","h_mZ2v_mttt",

"h_mH2v_ee","h_mH2v_em","h_mH2v_mm","h_mH2v_eee","h_mH2v_eem","h_mH2v_eet","h_mH2v_emt","h_mH2v_emm","h_mH2v_mmm","h_mH2v_mmt","h_mH2v_ett","h_mH2v_mtt","h_mH2v_eeee","h_mH2v_eeem","h_mH2v_eemm","h_mH2v_mmem","h_mH2v_mmmm","h_mH2v_eeet","h_mH2v_eemt","h_mH2v_eett","h_mH2v_emtt","h_mH2v_emmt","h_mH2v_ettt","h_mH2v_mmmt","h_mH2v_mmtt","h_mH2v_mttt",

"h_metv_ee","h_metv_em","h_metv_mm","h_metv_eee","h_metv_eem","h_metv_eet","h_metv_emt","h_metv_emm","h_metv_mmm","h_metv_mmt","h_metv_ett","h_metv_mtt","h_metv_eeee","h_metv_eeem","h_metv_eemm","h_metv_mmem","h_metv_mmmm","h_metv_eeet","h_metv_eemt","h_metv_eett","h_metv_emtt","h_metv_emmt","h_metv_ettt","h_metv_mmmt","h_metv_mmtt","h_metv_mttt",

"h_LTv_ee","h_LTv_em","h_LTv_mm","h_LTv_eee","h_LTv_eem","h_LTv_eet","h_LTv_emt","h_LTv_emm","h_LTv_mmm","h_LTv_mmt","h_LTv_ett","h_LTv_mtt","h_LTv_eeee","h_LTv_eeem","h_LTv_eemm","h_LTv_mmem","h_LTv_mmmm","h_LTv_eeet","h_LTv_eemt","h_LTv_eett","h_LTv_emtt","h_LTv_emmt","h_LTv_ettt","h_LTv_mmmt","h_LTv_mmtt","h_LTv_mttt",

"h_pt1v_ee","h_pt1v_em","h_pt1v_mm","h_pt1v_eee","h_pt1v_eem","h_pt1v_eet","h_pt1v_emt","h_pt1v_emm","h_pt1v_mmm","h_pt1v_mmt","h_pt1v_ett","h_pt1v_mtt","h_pt1v_eeee","h_pt1v_eeem","h_pt1v_eemm","h_pt1v_mmem","h_pt1v_mmmm","h_pt1v_eeet","h_pt1v_eemt","h_pt1v_eett","h_pt1v_emtt","h_pt1v_emmt","h_pt1v_ettt","h_pt1v_mmmt","h_pt1v_mmtt","h_pt1v_mttt",

"h_pt2v_ee","h_pt2v_em","h_pt2v_mm","h_pt2v_eee","h_pt2v_eem","h_pt2v_eet","h_pt2v_emt","h_pt2v_emm","h_pt2v_mmm","h_pt2v_mmt","h_pt2v_ett","h_pt2v_mtt","h_pt2v_eeee","h_pt2v_eeem","h_pt2v_eemm","h_pt2v_mmem","h_pt2v_mmmm","h_pt2v_eeet","h_pt2v_eemt","h_pt2v_eett","h_pt2v_emtt","h_pt2v_emmt","h_pt2v_ettt","h_pt2v_mmmt","h_pt2v_mmtt","h_pt2v_mttt",

"h_pt3v_ee","h_pt3v_em","h_pt3v_mm","h_pt3v_eee","h_pt3v_eem","h_pt3v_eet","h_pt3v_emt","h_pt3v_emm","h_pt3v_mmm","h_pt3v_mmt","h_pt3v_ett","h_pt3v_mtt","h_pt3v_eeee","h_pt3v_eeem","h_pt3v_eemm","h_pt3v_mmem","h_pt3v_mmmm","h_pt3v_eeet","h_pt3v_eemt","h_pt3v_eett","h_pt3v_emtt","h_pt3v_emmt","h_pt3v_ettt","h_pt3v_mmmt","h_pt3v_mmtt","h_pt3v_mttt",

"h_pt4v_ee","h_pt4v_em","h_pt4v_mm","h_pt4v_eee","h_pt4v_eem","h_pt4v_eet","h_pt4v_emt","h_pt4v_emm","h_pt4v_mmm","h_pt4v_mmt","h_pt4v_ett","h_pt4v_mtt","h_pt4v_eeee","h_pt4v_eeem","h_pt4v_eemm","h_pt4v_mmem","h_pt4v_mmmm","h_pt4v_eeet","h_pt4v_eemt","h_pt4v_eett","h_pt4v_emtt","h_pt4v_emmt","h_pt4v_ettt","h_pt4v_mmmt","h_pt4v_mmtt","h_pt4v_mttt",

"h_eta1v_ee","h_eta1v_em","h_eta1v_mm","h_eta1v_eee","h_eta1v_eem","h_eta1v_eet","h_eta1v_emt","h_eta1v_emm","h_eta1v_mmm","h_eta1v_mmt","h_eta1v_ett","h_eta1v_mtt","h_eta1v_eeee","h_eta1v_eeem","h_eta1v_eemm","h_eta1v_mmem","h_eta1v_mmmm","h_eta1v_eeet","h_eta1v_eemt","h_eta1v_eett","h_eta1v_emtt","h_eta1v_emmt","h_eta1v_ettt","h_eta1v_mmmt","h_eta1v_mmtt","h_eta1v_mttt",

"h_eta2v_ee","h_eta2v_em","h_eta2v_mm","h_eta2v_eee","h_eta2v_eem","h_eta2v_eet","h_eta2v_emt","h_eta2v_emm","h_eta2v_mmm","h_eta2v_mmt","h_eta2v_ett","h_eta2v_mtt","h_eta2v_eeee","h_eta2v_eeem","h_eta2v_eemm","h_eta2v_mmem","h_eta2v_mmmm","h_eta2v_eeet","h_eta2v_eemt","h_eta2v_eett","h_eta2v_emtt","h_eta2v_emmt","h_eta2v_ettt","h_eta2v_mmmt","h_eta2v_mmtt","h_eta2v_mttt",

"h_eta3v_ee","h_eta3v_em","h_eta3v_mm","h_eta3v_eee","h_eta3v_eem","h_eta3v_eet","h_eta3v_emt","h_eta3v_emm","h_eta3v_mmm","h_eta3v_mmt","h_eta3v_ett","h_eta3v_mtt","h_eta3v_eeee","h_eta3v_eeem","h_eta3v_eemm","h_eta3v_mmem","h_eta3v_mmmm","h_eta3v_eeet","h_eta3v_eemt","h_eta3v_eett","h_eta3v_emtt","h_eta3v_emmt","h_eta3v_ettt","h_eta3v_mmmt","h_eta3v_mmtt","h_eta3v_mttt",

"h_eta4v_ee","h_eta4v_em","h_eta4v_mm","h_eta4v_eee","h_eta4v_eem","h_eta4v_eet","h_eta4v_emt","h_eta4v_emm","h_eta4v_mmm","h_eta4v_mmt","h_eta4v_ett","h_eta4v_mtt","h_eta4v_eeee","h_eta4v_eeem","h_eta4v_eemm","h_eta4v_mmem","h_eta4v_mmmm","h_eta4v_eeet","h_eta4v_eemt","h_eta4v_eett","h_eta4v_emtt","h_eta4v_emmt","h_eta4v_ettt","h_eta4v_mmmt","h_eta4v_mmtt","h_eta4v_mttt",

"h_phi1v_ee","h_phi1v_em","h_phi1v_mm","h_phi1v_eee","h_phi1v_eem","h_phi1v_eet","h_phi1v_emt","h_phi1v_emm","h_phi1v_mmm","h_phi1v_mmt","h_phi1v_ett","h_phi1v_mtt","h_phi1v_eeee","h_phi1v_eeem","h_phi1v_eemm","h_phi1v_mmem","h_phi1v_mmmm","h_phi1v_eeet","h_phi1v_eemt","h_phi1v_eett","h_phi1v_emtt","h_phi1v_emmt","h_phi1v_ettt","h_phi1v_mmmt","h_phi1v_mmtt","h_phi1v_mttt",

"h_phi2v_ee","h_phi2v_em","h_phi2v_mm","h_phi2v_eee","h_phi2v_eem","h_phi2v_eet","h_phi2v_emt","h_phi2v_emm","h_phi2v_mmm","h_phi2v_mmt","h_phi2v_ett","h_phi2v_mtt","h_phi2v_eeee","h_phi2v_eeem","h_phi2v_eemm","h_phi2v_mmem","h_phi2v_mmmm","h_phi2v_eeet","h_phi2v_eemt","h_phi2v_eett","h_phi2v_emtt","h_phi2v_emmt","h_phi2v_ettt","h_phi2v_mmmt","h_phi2v_mmtt","h_phi2v_mttt",

"h_phi3v_ee","h_phi3v_em","h_phi3v_mm","h_phi3v_eee","h_phi3v_eem","h_phi3v_eet","h_phi3v_emt","h_phi3v_emm","h_phi3v_mmm","h_phi3v_mmt","h_phi3v_ett","h_phi3v_mtt","h_phi3v_eeee","h_phi3v_eeem","h_phi3v_eemm","h_phi3v_mmem","h_phi3v_mmmm","h_phi3v_eeet","h_phi3v_eemt","h_phi3v_eett","h_phi3v_emtt","h_phi3v_emmt","h_phi3v_ettt","h_phi3v_mmmt","h_phi3v_mmtt","h_phi3v_mttt",

"h_phi4v_ee","h_phi4v_em","h_phi4v_mm","h_phi4v_eee","h_phi4v_eem","h_phi4v_eet","h_phi4v_emt","h_phi4v_emm","h_phi4v_mmm","h_phi4v_mmt","h_phi4v_ett","h_phi4v_mtt","h_phi4v_eeee","h_phi4v_eeem","h_phi4v_eemm","h_phi4v_mmem","h_phi4v_mmmm","h_phi4v_eeet","h_phi4v_eemt","h_phi4v_eett","h_phi4v_emtt","h_phi4v_emmt","h_phi4v_ettt","h_phi4v_mmmt","h_phi4v_mmtt","h_phi4v_mttt",
*/
	};

	const char *hist_list2[] = {
		"0tau/h_ST","1tau/h_ST","2tau/h_ST","3tau/h_ST","3lep0tau/h_ST","3lep1tau/h_ST","3lep2tau/h_ST",
		"0tau/h_mZ1","1tau/h_mZ1","2tau/h_mZ1","3tau/h_mZ1","3lep0tau/h_mZ1","3lep1tau/h_mZ1","3lep2tau/h_mZ1",
		"0tau/h_mZ2","1tau/h_mZ2","2tau/h_mZ2","3tau/h_mZ2","3lep0tau/h_mZ2","3lep1tau/h_mZ2","3lep2tau/h_mZ2",
		"0tau/h_mZ3","1tau/h_mZ3","2tau/h_mZ3","3tau/h_mZ3","3lep0tau/h_mZ3","3lep1tau/h_mZ3","3lep2tau/h_mZ3",
		"0tau/h_mZ4","1tau/h_mZ4","2tau/h_mZ4","3tau/h_mZ4","3lep0tau/h_mZ4","3lep1tau/h_mZ4","3lep2tau/h_mZ4",
		"0tau/h_mTtot1","1tau/h_mTtot1","2tau/h_mTtot1","3tau/h_mTtot1","3lep0tau/h_mTtot1","3lep1tau/h_mTtot1","3lep2tau/h_mTtot1",
		"0tau/h_mTtot2","1tau/h_mTtot2","2tau/h_mTtot2","3tau/h_mTtot2","3lep0tau/h_mTtot2","3lep1tau/h_mTtot2","3lep2tau/h_mTtot2",
		"0tau/h_mll1","1tau/h_mll1","2tau/h_mll1","3tau/h_mll1","3lep0tau/h_mll1","3lep1tau/h_mll1","3lep2tau/h_mll1",
		"0tau/h_mll2","1tau/h_mll2","2tau/h_mll2","3tau/h_mll2","3lep0tau/h_mll2","3lep1tau/h_mll2","3lep2tau/h_mll2",
		"0tau/h_met","1tau/h_met","2tau/h_met","3tau/h_met","3lep0tau/h_met","3lep1tau/h_met","3lep2tau/h_met"
	};
	const char *hist_list1[] = {
	
"h_mZ1_VR_0tau", "h_mZ2_VR_0tau", 
"h_mZ1_VR_1tau", "h_mZ2_VR_1tau", 
"h_mZ1_VR_2tau", "h_mZ2_VR_2tau", 
"h_mZ1_VR_3tau", "h_mZ2_VR_3tau",
"h_mZ1_VR_3lep0tau", "h_mZ2_VR_3lep0tau", 
"h_mZ1_VR_3lep1tau", "h_mZ2_VR_3lep1tau", 
"h_mZ1_VR_3lep2tau", "h_mZ2_VR_3lep2tau", 
	};
	
	
    // Categories with input files
    std::map<std::string, std::vector<std::string>> files;
    if (year == "2016") files = {
        {"DY",    {"DYJetsToLLM10to50_2016.root", "DYJetsToLLM50_2016.root"}},
        {"VV",    {"WW_2016.root", "WWTo2L2Nu_2016.root", "WZTo2Q2L_2016.root", "WZTo3LNu_2016.root"}},
        {"VVV",   {"WWW_2016.root", "WZZ_2016.root", "ZZZ_2016.root"}},
        {"ttV",   {"ttWJets_2016.root", "ttZJets_2016.root"}},
        {"WJ",    {"WJetsToLNu_NLO_2016.root", "WJetsToLNu_HT-70To100_2016.root", "WJetsToLNu_HT-100To200_2016.root", 
                   "WJetsToLNu_HT-200To400_2016.root", "WJetsToLNu_HT-400To600_2016.root", 
                   "WJetsToLNu_HT-600To800_2016.root", "WJetsToLNu_HT-800To1200_2016.root", "WJetsToLNu_HT-1200To2500_2016.root", "WJetsToLNu_HT-2500ToInf_2016.root"}},
        {"ZZ",    {"ZZTo2L2Nu_2016.root", "ZZTo2Q2L_2016.root", "ZZTo4L_2016.root"}},
        {"ST",    {"ST_s-channel_2016.root", "ST_t-channel_antitop_2016.root", "ST_t-channel_top_2016.root", 
                   "ST_tW_antitop_2016.root", "ST_tW_top_2016.root"}},
        {"TTbar", {"TTTo2L2Nu_2016.root", "TTToSemiLeptonic_2016.root", "TTToHadronic_2016.root"}},
        {"other", {"ttHToTauTau_2016.root", "ZHToMuMu_2016.root","ZHToTauTau_2016.root", "GluGluZH_2016.root","ttHToEE_2016.root","ttHTo2L2Nu_2016.root"}},
        {"data",  {"SingleElectron_2016.root","EGamma_2016.root", "SingleMuon_2016.root"}}
    };
    else if (year == "2017") files = {
        {"DY",    {"DYJetsToLLM10to50_2017.root", "DYJetsToLLM50_2017.root"}},
        {"VV",    {"WW_2017.root", "WWTo2L2Nu_2017.root", "WZTo2Q2L_2017.root", "WZTo3LNu_2017.root"}},
        {"VVV",   {"WWW_2017.root", "WZZ_2017.root", "ZZZ_2017.root"}},
        {"ttV",   {"ttWJets_2017.root", "ttZJets_2017.root"}},
        {"WJ",    {"WJetsToLNu_NLO_2017.root", "WJetsToLNu_HT-70To100_2017.root", "WJetsToLNu_HT-100To200_2017.root", 
                   "WJetsToLNu_HT-200To400_2017.root", "WJetsToLNu_HT-400To600_2017.root", 
                   "WJetsToLNu_HT-600To800_2017.root", "WJetsToLNu_HT-800To1200_2017.root", "WJetsToLNu_HT-1200To2500_2017.root", "WJetsToLNu_HT-2500ToInf_2017.root"}},
        {"ZZ",    {"ZZTo2L2Nu_2017.root", "ZZTo2Q2L_2017.root", "ZZTo4L_2017.root"}},
        {"ST",    {"ST_s-channel_2017.root", "ST_t-channel_antitop_2017.root", "ST_t-channel_top_2017.root", 
                   "ST_tW_antitop_2017.root", "ST_tW_top_2017.root"}},
        {"TTbar", {"TTTo2L2Nu_2017.root", "TTToSemiLeptonic_2017.root", "TTToHadronic_2017.root"}},
        {"other", {"ttHToTauTau_2017.root", "ZHToMuMu_2017.root","ZHToTauTau_2017.root", "GluGluZH_2017.root","ttHToEE_2017.root", "ttHTo2L2Nu_2017.root"}},
        {"data",  {"SingleElectron_2017.root","EGamma_2017.root", "SingleMuon_2017.root"}}
    };
    else if (year == "2018") files = {
        {"DY",    {"DYJetsToLLM10to50_2018.root", "DYJetsToLLM50_2018.root"}},
        {"VV",    {"WW_2018.root", "WWTo2L2Nu_2018.root", "WZTo2Q2L_2018.root", "WZTo3LNu_2018.root"}},
        {"VVV",   {"WWW_2018.root", "WZZ_2018.root", "ZZZ_2018.root"}},
        {"ttV",   {"ttWJets_2018.root", "ttZJets_2018.root"}},
        {"WJ",    {"WJetsToLNu_NLO_2018.root", "WJetsToLNu_HT-70To100_2018.root", "WJetsToLNu_HT-100To200_2018.root", 
                   "WJetsToLNu_HT-200To400_2018.root", "WJetsToLNu_HT-400To600_2018.root", 
                   "WJetsToLNu_HT-600To800_2018.root", "WJetsToLNu_HT-800To1200_2018.root", "WJetsToLNu_HT-1200To2500_2018.root", "WJetsToLNu_HT-2500ToInf_2018.root"}},
        {"ZZ",    {"ZZTo2L2Nu_2018.root", "ZZTo2Q2L_2018.root", "ZZTo4L_2018.root"}},
        {"ST",    {"ST_s-channel_2018.root", "ST_t-channel_antitop_2018.root", "ST_t-channel_top_2018.root", 
                   "ST_tW_antitop_2018.root", "ST_tW_top_2018.root"}},
        {"TTbar", {"TTTo2L2Nu_2018.root", "TTToSemiLeptonic_2018.root", "TTToHadronic_2018.root"}},
        {"other", {"ttHToTauTau_2018.root", "ZHToMuMu_2018.root","ZHToTauTau_2018.root", "GluGluZH_2018.root", "ttHToEE_2018.root", "ttHTo2L2Nu_2018.root"}},
        {"data",  {"SingleElectron_2018.root","EGamma_2018.root", "SingleMuon_2018.root"}}
    };
    else if (year == "Run2") files = {
    	{"signal",    {"HppM1000_2016.root", "HppM1000_2017.root", "HppM1000_2018.root"}},
        {"DY",    {"DYJetsToLLM10to50_2016.root", "DYJetsToLLM50_2016.root","DYJetsToLLM10to50_2017.root", "DYJetsToLLM50_2017.root","DYJetsToLLM10to50_2018.root", "DYJetsToLLM50_2018.root"}},
        {"VV",    {"WW_2016.root", "WWTo2L2Nu_2016.root", "WZTo2Q2L_2016.root", "WZTo3LNu_2016.root","WW_2017.root", "WWTo2L2Nu_2017.root", "WZTo2Q2L_2017.root", "WZTo3LNu_2017.root","WW_2018.root", "WWTo2L2Nu_2018.root", "WZTo2Q2L_2018.root", "WZTo3LNu_2018.root"}},
        {"VVV",   {"WWW_2016.root", "WZZ_2016.root", "ZZZ_2016.root","WWW_2017.root", "WZZ_2017.root", "ZZZ_2017.root","WWW_2018.root", "WZZ_2018.root", "ZZZ_2018.root"}},
        {"ttV",   {"ttWJets_2016.root", "ttZJets_2016.root","ttWJets_2017.root", "ttZJets_2017.root","ttWJets_2018.root", "ttZJets_2018.root"}},
        {"WJ",    {"WJetsToLNu_NLO_2016.root", "WJetsToLNu_HT-70To100_2016.root", "WJetsToLNu_HT-100To200_2016.root", 
                   "WJetsToLNu_HT-200To400_2016.root", "WJetsToLNu_HT-400To600_2016.root", 
                   "WJetsToLNu_HT-600To800_2016.root", "WJetsToLNu_HT-800To1200_2016.root", "WJetsToLNu_HT-1200To2500_2016.root", "WJetsToLNu_HT-2500ToInf_2016.root","WJetsToLNu_NLO_2017.root", "WJetsToLNu_HT-70To100_2017.root", "WJetsToLNu_HT-100To200_2017.root", 
                   "WJetsToLNu_HT-200To400_2017.root", "WJetsToLNu_HT-400To600_2017.root", 
                   "WJetsToLNu_HT-600To800_2017.root", "WJetsToLNu_HT-800To1200_2017.root", "WJetsToLNu_HT-1200To2500_2017.root", "WJetsToLNu_HT-2500ToInf_2017.root","WJetsToLNu_NLO_2018.root", "WJetsToLNu_HT-70To100_2018.root", "WJetsToLNu_HT-100To200_2018.root", 
                   "WJetsToLNu_HT-200To400_2018.root", "WJetsToLNu_HT-400To600_2018.root", 
                   "WJetsToLNu_HT-600To800_2018.root", "WJetsToLNu_HT-800To1200_2018.root", "WJetsToLNu_HT-1200To2500_2018.root", "WJetsToLNu_HT-2500ToInf_2018.root"}},
        {"ZZ",    {"ZZTo2L2Nu_2016.root", "ZZTo2Q2L_2016.root", "ZZTo4L_2016.root","ZZTo2L2Nu_2017.root", "ZZTo2Q2L_2017.root", "ZZTo4L_2017.root","ZZTo2L2Nu_2018.root", "ZZTo2Q2L_2018.root", "ZZTo4L_2018.root"}},
      /*  {"ZZ",    {"ZZTo2L2Nu_2016.root", "ZZTo2Q2L_2016.root", "ZZTo2L2Nu_2017.root", "ZZTo2Q2L_2017.root", "ZZTo2L2Nu_2018.root", "ZZTo2Q2L_2018.root"}},
        {"ZZto4L",    {"ZZTo4L_2016.root","ZZTo4L_2017.root","ZZTo4L_2018.root"}},*/
        {"ST",    {"ST_s-channel_2016.root", "ST_t-channel_antitop_2016.root", "ST_t-channel_top_2016.root", 
                   "ST_tW_antitop_2016.root", "ST_tW_top_2016.root","ST_s-channel_2017.root", "ST_t-channel_antitop_2017.root", "ST_t-channel_top_2017.root", 
                   "ST_tW_antitop_2017.root", "ST_tW_top_2017.root","ST_s-channel_2018.root", "ST_t-channel_antitop_2018.root", "ST_t-channel_top_2018.root", 
                   "ST_tW_antitop_2018.root", "ST_tW_top_2018.root"}},
        {"TTbar", {"TTTo2L2Nu_2016.root", "TTToSemiLeptonic_2016.root", "TTToHadronic_2016.root","TTTo2L2Nu_2017.root", "TTToSemiLeptonic_2017.root", "TTToHadronic_2017.root","TTTo2L2Nu_2018.root", "TTToSemiLeptonic_2018.root", "TTToHadronic_2018.root"}},
        {"other", {"ttHToTauTau_2016.root", "ZHToMuMu_2016.root","ZHToTauTau_2016.root", "GluGluZH_2016.root","ttHToTauTau_2017.root", "ZHToMuMu_2017.root","ZHToTauTau_2017.root", "GluGluZH_2017.root","ttHToTauTau_2018.root", "ZHToMuMu_2018.root","ZHToTauTau_2018.root", "GluGluZH_2018.root","ttHToEE_2016.root","ttHToEE_2017.root", "ttHToEE_2018.root","ttHTo2L2Nu_2016.root","ttHTo2L2Nu_2017.root", "ttHTo2L2Nu_2018.root","ttHJetToNonbb_2016.root","ttHJetToNonbb_2017.root","ttHJetToNonbb_2018.root","TWZToLL_2016.root","TWZToLL_2017.root","TWZToLL_2018.root","HZJ_HToWWTo2L2Nu_ZTo2L_2016.root","HZJ_HToWWTo2L2Nu_ZTo2L_2017.root","HZJ_HToWWTo2L2Nu_ZTo2L_2018.root"}},
        {"data",  {"SingleElectronB_2016.root","SingleElectronC_2016.root","SingleElectronD_2016.root","SingleElectronE_2016.root","SingleElectronF_2016.root","SingleElectronG_2016.root","SingleElectronH_2016.root", "SingleMuonB_2016.root","SingleMuonC_2016.root","SingleMuonD_2016.root","SingleMuonE_2016.root","SingleMuonF_2016.root","SingleMuonG_2016.root","SingleMuonH_2016.root","SingleElectronB_2017.root","SingleElectronC_2017.root","SingleElectronD_2017.root","SingleElectronE_2017.root","SingleElectronF_2017.root", "SingleMuonB_2017.root","SingleMuonC_2017.root","SingleMuonD_2017.root","SingleMuonE_2017.root","SingleMuonF_2017.root","EGammaA_2018.root","EGammaB_2018.root","EGammaC_2018.root","EGammaD_2018.root", "SingleMuonA_2018.root","SingleMuonB_2018.root","SingleMuonC_2018.root","SingleMuonD_2018.root"}}
    };
    std::map<std::string, std::vector<TFile*>> open_files;
    for (auto& kv : files) {
		for (const auto& fname : kv.second) {
		    TFile* file = new TFile(("hist_test_nopair/" + fname).c_str(), "READ");
		    if (!file || file->IsZombie()) continue;
	        open_files[kv.first].push_back(file);
	    }
	}
	TFile *ifile_D1 = new TFile("hist_test_nopair/EGammaA_2018.root","READ");

	for (int i = 0; i < sizeof(hist_list)/sizeof(hist_list[0]); i++) {

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

		std::string name = hist_list[i];
		std::string hist_string;

		if(summary_type != "tau_ch"){
		    size_t pos = name.rfind('_');// find last underscore
		    std::string channel = (pos != std::string::npos) ? name.substr(pos + 1) : "";

		    if (channel == "mm") hist_string = "#it{#mu#mu}";
		    else if (channel == "mmm") hist_string = "#it{#mu#mu,#mu}";
		    else if (channel == "mmmm") hist_string = "#it{#mu#mu,#mu#mu}";
		    else if (channel == "eemm") hist_string = "#it{ee,#mu#mu}";
		    else if (channel == "emm") hist_string = "#it{#mu#mu,e}";
		    else if (channel == "eem") hist_string = "#it{ee,#mu}";
		    else hist_string += channel;
		    hist_string += " channel ";
		    
			//if (name.find("v_") < name.length()) hist_string += "in Z-veto";  
			//else if (name.find("v_") > name.length()) hist_string += "in Z-window";
		}
		else{

		    if (name.find("3lep") < name.length()) hist_string += "#it{3l,}";
		    else hist_string += "#it{4l,}";

		    if (name.find("0tau") < name.length()) hist_string += "#it{0#tau} channel";
		    else if (name.find("1tau") < name.length()) hist_string += "#it{1#tau} channel";
		    else if (name.find("2tau") < name.length()) hist_string += "#it{2#tau} channel";
		    else if (name.find("3tau") < name.length()) hist_string += "#it{3#tau} channel";
		}

		char *hist_name = const_cast<char*>(hist_string.c_str());

		THStack* bkg_stack = new THStack("bkg_stack", "");//empty title
		std::map<std::string, TH1D*> hist;
		std::map<std::string, int> fill_colors = {
		    {"DY",7},{"VV",8},{"VVV",6},{"ttV",4},{"WJ",9},{"ZZ",5},
		    {"ST",30},{"TTbar",46},{"other",28},{"data",1}
		};

		int xmin = 50;
		int xmax = 150;

		int bins = 0;
		for (auto& kv : open_files) {

		    TH1D* tmp = (TH1D*)ifile_D1->Get(hist_list[i]);
		    hist[kv.first] = (TH1D*)tmp->Clone();
		    hist[kv.first]->Sumw2();
		    hist[kv.first]->Reset();

		    for (auto* f : kv.second) {
		        TH1D* h = dynamic_cast<TH1D*>(f->Get(hist_list[i]));
		        if (!h) continue;
		        h->Sumw2();
		        h->Scale(applyXSec(f));
		        //h->Rebin(2);

		       //========== merge overflow ==========
				int firstBin = h->GetXaxis()->FindBin(xmin);
				int lastBin  = h->GetXaxis()->FindBin(xmax);

				int nb = h->GetNbinsX();

				double content = h->GetBinContent(lastBin);
				double error   = h->GetBinError(lastBin);

				// add everything above xmax including overflow
				for(int b = lastBin+1; b <= nb+1; b++){
					content += h->GetBinContent(b);
					error = sqrt(error*error + pow(h->GetBinError(b),2));
				}

				// set new last bin
				h->SetBinContent(lastBin-1,content);
				h->SetBinError(lastBin-1,error);
		        //=======================================
		        
		        if (kv.first != "data") {
					for (int ib = 1; ib <= h->GetNbinsX(); ib++) {
						double stat_err = h->GetBinError(ib);
						double sys_err = h->GetBinContent(ib) * XSec_Uncert(f->GetName()) / 100.0;
		          		double tot_uncert_quadr = (stat_err*stat_err + sys_err*sys_err);
		          		if(summary_type == "tau_ch"){
		            		if (name.find("3lep") < name.length())
		                        tot_uncert_quadr += fake_uncert_squared("3lep", f->GetName())*pow(h->GetBinContent(ib),2);
		            		else tot_uncert_quadr += fake_uncert_squared("4lep", f->GetName())*pow(h->GetBinContent(ib),2);
		            	}
		            	else if(name != "h_met_ee" and name != "h_met_mm" and name != "h_metv_ee" and name != "h_metv_mm") tot_uncert_quadr += fake_uncert_squared(summary_type, f->GetName())*pow(h->GetBinContent(ib),2);
		            	//cout<<tot_uncert_quadr[ib]<<endl;
		            	h->SetBinError(ib,sqrt(tot_uncert_quadr));
					}
				}
				hist[kv.first]->Add(h);
			}
			if (hist[kv.first]) {
				hist[kv.first]->SetFillColor(fill_colors[kv.first]);
				bins = hist[kv.first]->GetNbinsX();//since we rebinned and changed range
				
			}
		}
		
		/*hist["VV"]->Scale(1.12631);
		hist["ZZ"]->Scale(1.31366);*/
		hist["VV"]->Scale(1.03002);
		hist["ZZ"]->Scale(1.30291);
		// Stack backgrounds
		//THStack* bkg_stack = new THStack("bkg_stack", "2l and 3l channel summary in Z-window;;Events");
		TH1D* h_bkg_total = (TH1D*)hist["DY"]->Clone("h_bkg_total");
		h_bkg_total->Sumw2();
		h_bkg_total->Reset();
		for (const std::string& bkg_group : {"DY", "VV", "VVV", "ttV", "WJ", "ZZ", "ST", "TTbar", "other"}) {
		    bkg_stack->Add(hist[bkg_group]);
		    h_bkg_total->Add(hist[bkg_group]);
		}
		
		TH1D* h_mc_uncert_band = (TH1D*) h_bkg_total->Clone("h_mc_uncert_band");
		h_mc_uncert_band->Sumw2();
		h_mc_uncert_band->Reset(); // we'll fill the error by hand
		for (int j = 1; j <= bins; j++) {
			h_mc_uncert_band->SetBinContent(j, 1.0);  // center at ratio = 1
			if (h_bkg_total->GetBinContent(j) > 0) h_mc_uncert_band->SetBinError(j, h_bkg_total->GetBinError(j)/h_bkg_total->GetBinContent(j));//scaling error with bin content
			else h_mc_uncert_band->SetBinError(j,0);
			//cout<<h_bkg_total->GetBinError(j)<<"\t"<<h_bkg_total->GetBinContent(j)<<endl;
		}
		
		// Draw main plot
		pad1->cd();
		//gPad->SetLogy(1);
		bkg_stack->Draw("hist");
		bkg_stack->GetXaxis()->SetRangeUser(xmin,xmax);

		double pad_max = std::max(bkg_stack->GetMaximum(),hist["data"]->GetMaximum());
		bkg_stack->SetMaximum(1.1*pad_max);
		hist["data"]->SetMarkerStyle(20);
		hist["data"]->SetMarkerColor(kBlack);
		bkg_stack->GetYaxis()->SetTitle("Events / bin");
		hist["data"]->Draw("E SAME");

		//Signal
		hist["signal"]->SetLineStyle(5);
		hist["signal"]->SetLineColor(2);
		hist["signal"]->Scale(100);
		//hist["signal"]->Scale(h_bkg_total->Integral()/hist["signal"]->Integral());
		hist["signal"]->SetBinContent(bins, hist["signal"]->GetBinContent(bins)+hist["signal"]->GetBinContent(bins+1));
		//hist["signal"]->Draw("SAME");
		//hist["signal"]->GetXaxis()->SetRangeUser(xmin,xmax);
		
		// Create a TLatex object
		DrawCMSLabel();
		PlotDescription(hist_name);
		
		auto legend = new TLegend(0.7, 0.5, 0.88, 0.88);
		//auto legend = new TLegend(0.12, 0.6, 0.3, 0.88);
		for (const std::string& bkg_group : {"DY", "VV", "VVV", "ttV", "WJ", "ZZ", "ST", "TTbar", "other"}) {
		    legend->AddEntry(hist[bkg_group], bkg_group.c_str(), "f");
		}
		legend->AddEntry(hist["data"], "Data", "lep");
		legend->Draw();

		std::string X_string;
		if (name.find("_WMt") < name.length()) X_string += "W transverse mass ";
		else if (name.find("_mZ") < name.length()) X_string += "mZ ";
		else if (name.find("_mll") < name.length()) X_string += "M(ll) of leading pair";
		else if (name.find("_mH") < name.length()) X_string += "mH ";
		else if (name.find("_met") < name.length()) X_string += "E_{T}^{miss} ";
		else if (name.find("_LT") < name.length()) X_string += "L_{T} ";
		else if (name.find("_pt1") < name.length()) X_string += "pT-1 ";
		else if (name.find("_pt2") < name.length()) X_string += "pT-2 ";
		else if (name.find("_pt3") < name.length()) X_string += "pT-3 ";
		else if (name.find("_pt4") < name.length()) X_string += "Eta-4 ";
		else if (name.find("_eta1") < name.length()) X_string += "Eta-1";
		else if (name.find("_eta2") < name.length()) X_string += "Eta-2";
		else if (name.find("_eta3") < name.length()) X_string += "Eta-3";
		else if (name.find("_eta4") < name.length()) X_string += "Eta-4";
		else if (name.find("_phi1") < name.length()) X_string += "Phi-1";
		else if (name.find("_phi2") < name.length()) X_string += "Phi-2";
		else if (name.find("_phi3") < name.length()) X_string += "Phi-3";
		else if (name.find("_phi4") < name.length()) X_string += "Phi-4";
		else if (name.find("_iso1") < name.length()) X_string += "ISO-1";
		else if (name.find("_iso2") < name.length()) X_string += "ISO-2";
		else if (name.find("_iso3") < name.length()) X_string += "ISO-3";
		else if (name.find("_iso4") < name.length()) X_string += "ISO-4";
		else if (name.find("_dxy1") < name.length()) X_string += "dXY-1";
		else if (name.find("_dxy2") < name.length()) X_string += "dXY-2";
		else if (name.find("_dxy3") < name.length()) X_string += "dXY-3";
		else if (name.find("_dxy4") < name.length()) X_string += "dXY-4";
		else if (name.find("_dZ1") < name.length()) X_string += "dZ-1";
		else if (name.find("_dZ2") < name.length()) X_string += "dZ-2";
		else if (name.find("_dZ3") < name.length()) X_string += "dZ-3";
		else if (name.find("_dZ4") < name.length()) X_string += "dZ-4";

		// Ratio histogram: data / MC
		TH1D* h_ratio = (TH1D*)hist["data"]->Clone("h_ratio");
		h_ratio->Sumw2();
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
		h_ratio->GetXaxis()->SetLabelSize(0.1);
		h_ratio->GetXaxis()->SetTitle(const_cast<char*>(X_string.c_str()));
		h_ratio->SetMinimum(0); // Set the minimum y-value for the ratio plot
		h_ratio->SetMaximum(2); // Set the maximum y-value for the ratio plot
		
		// Draw ratio plot
		pad2->cd();
		h_ratio->SetMinimum(0.0);
		h_ratio->SetMaximum(2.0);
		h_ratio->Draw("E");
		h_ratio->GetXaxis()->SetRangeUser(xmin,xmax);

		h_mc_uncert_band->SetFillColor(kGray+2);
		h_mc_uncert_band->SetFillStyle(3001); // hatched
		h_mc_uncert_band->SetLineColor(0);
		h_mc_uncert_band->Draw("E2 same"); // as a filled error band
		h_mc_uncert_band->GetXaxis()->SetRangeUser(xmin,xmax);
		
		// Draw lines for reference
		TLine *line1 = new TLine(xmin, 1, xmax, 1);
		TLine *line2 = new TLine(xmin, 0.5, xmax, 0.5);
		TLine *line3 = new TLine(xmin, 1.5, xmax, 1.5);
		line1->SetLineStyle(2);line2->SetLineStyle(2);line3->SetLineStyle(2);
		line1->Draw(); line2->Draw(); line3->Draw();


		// Output
		std::string s =  "hist_test_nopair/", s1, s2;
		s1 = s + hist_list[i]+".pdf";
		s2 = s + hist_list[i]+".png";
		char* title1 = const_cast<char*>(s1.c_str());//converting string to char
		char* title2 = const_cast<char*>(s2.c_str());//converting string to char
		canvas->SaveAs(title1);
		canvas->SaveAs(title2);
		canvas->Clear();
	}
}
