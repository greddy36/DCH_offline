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
#include "include/XSections.C"

void StackHist() {
	std::string summary_type = "tau_ch", year = "Run2";
    // Define histograms to retrieve
    const char *hist_list[] = 
    /*{"h_WMt_ee","h_WMt_em","h_WMt_mm","h_WMt_eee","h_WMt_eem","h_WMt_eet","h_WMt_emt","h_WMt_emm","h_WMt_mmm","h_WMt_mmt","h_WMt_ett","h_WMt_mtt","h_WMt_eeee","h_WMt_eeem","h_WMt_eemm","h_WMt_mmem","h_WMt_mmmm","h_WMt_eeet","h_WMt_eemt","h_WMt_eett","h_WMt_emtt","h_WMt_emmt","h_WMt_ettt","h_WMt_mmmt","h_WMt_mmtt","h_WMt_mttt",
	
	"h_WMtv_ee","h_WMtv_em","h_WMtv_mm","h_WMtv_eee","h_WMtv_eem","h_WMtv_eet","h_WMtv_emt","h_WMtv_emm","h_WMtv_mmm","h_WMtv_mmt","h_WMtv_ett","h_WMtv_mtt","h_WMtv_eeee","h_WMtv_eeem","h_WMtv_eemm","h_WMtv_mmem","h_WMtv_mmmm","h_WMtv_eeet","h_WMtv_eemt","h_WMtv_eett","h_WMtv_emtt","h_WMtv_emmt","h_WMtv_ettt","h_WMtv_mmmt","h_WMt_mmtt","h_WMt_mttt",
	
"h_mZ_ee","h_mZ_em","h_mZ_mm","h_mZ_eee","h_mZ_eem","h_mZ_eet","h_mZ_emt","h_mZ_emm","h_mZ_mmm","h_mZ_mmt","h_mZ_ett","h_mZ_mtt","h_mZ_eeee","h_mZ_eeem","h_mZ_eemm","h_mZ_mmem","h_mZ_mmmm","h_mZ_eeet","h_mZ_eemt","h_mZ_eett","h_mZ_emtt","h_mZ_emmt","h_mZ_ettt","h_mZ_mmmt","h_mZ_mmtt","h_mZ_mttt",

"h_mZv_ee","h_mZv_em","h_mZv_mm","h_mZv_eee","h_mZv_eem","h_mZv_eet","h_mZv_emt","h_mZv_emm","h_mZv_mmm","h_mZv_mmt","h_mZv_ett","h_mZv_mtt","h_mZv_eeee","h_mZv_eeem","h_mZv_eemm","h_mZv_mmem","h_mZv_mmmm","h_mZv_eeet","h_mZv_eemt","h_mZv_eett","h_mZv_emtt","h_mZv_emmt","h_mZv_ettt","h_mZv_mmmt","h_mZv_mmtt","h_mZv_mttt",

"h_mH_ee","h_mH_em","h_mH_mm","h_mH_eee","h_mH_eem","h_mH_eet","h_mH_emt","h_mH_emm","h_mH_mmm","h_mH_mmt","h_mH_ett","h_mH_mtt","h_mH_eeee","h_mH_eeem","h_mH_eemm","h_mH_mmem","h_mH_mmmm","h_mH_eeet","h_mH_eemt","h_mH_eett","h_mH_emtt","h_mH_emmt","h_mH_ettt","h_mH_mmmt","h_mH_mmtt","h_mH_mttt",

"h_mHv_ee","h_mHv_em","h_mHv_mm","h_mHv_eee","h_mHv_eem","h_mHv_eet","h_mHv_emt","h_mHv_emm","h_mHv_mmm","h_mHv_mmt","h_mHv_ett","h_mHv_mtt","h_mHv_eeee","h_mHv_eeem","h_mHv_eemm","h_mHv_mmem","h_mHv_mmmm","h_mHv_eeet","h_mHv_eemt","h_mHv_eett","h_mHv_emtt","h_mHv_emmt","h_mHv_ettt","h_mHv_mmmt","h_mHv_mmtt","h_mHv_mttt",

"h_met_ee","h_met_em","h_met_mm","h_met_eee","h_met_eem","h_met_eet","h_met_emt","h_met_emm","h_met_mmm","h_met_mmt","h_met_ett","h_met_mtt","h_met_eeee","h_met_eeem","h_met_eemm","h_met_mmem","h_met_mmmm","h_met_eeet","h_met_eemt","h_met_eett","h_met_emtt","h_met_emmt","h_met_ettt","h_met_mmmt","h_met_mmtt","h_met_mttt",

"h_metv_ee","h_metv_em","h_metv_mm","h_metv_eee","h_metv_eem","h_metv_eet","h_metv_emt","h_metv_emm","h_metv_mmm","h_metv_mmt","h_metv_ett","h_metv_mtt","h_metv_eeee","h_metv_eeem","h_metv_eemm","h_metv_mmem","h_metv_mmmm","h_metv_eeet","h_metv_eemt","h_metv_eett","h_metv_emtt","h_metv_emmt","h_metv_ettt","h_metv_mmmt","h_metv_mmtt","h_metv_mttt",

"h_pt1_ee","h_pt1_em","h_pt1_mm","h_pt1_eee","h_pt1_eem","h_pt1_eet","h_pt1_emt","h_pt1_emm","h_pt1_mmm","h_pt1_mmt","h_pt1_ett","h_pt1_mtt","h_pt1_eeee","h_pt1_eeem","h_pt1_eemm","h_pt1_mmem","h_pt1_mmmm","h_pt1_eeet","h_pt1_eemt","h_pt1_eett","h_pt1_emtt","h_pt1_emmt","h_pt1_ettt","h_pt1_mmmt","h_pt1_mmtt","h_pt1_mttt",

"h_pt1v_ee","h_pt1v_em","h_pt1v_mm","h_pt1v_eee","h_pt1v_eem","h_pt1v_eet","h_pt1v_emt","h_pt1v_emm","h_pt1v_mmm","h_pt1v_mmt","h_pt1v_ett","h_pt1v_mtt","h_pt1v_eeee","h_pt1v_eeem","h_pt1v_eemm","h_pt1v_mmem","h_pt1v_mmmm","h_pt1v_eeet","h_pt1v_eemt","h_pt1v_eett","h_pt1v_emtt","h_pt1v_emmt","h_pt1v_ettt","h_pt1v_mmmt","h_pt1v_mmtt","h_pt1v_mttt",

"h_pt2_ee","h_pt2_em","h_pt2_mm","h_pt2_eee","h_pt2_eem","h_pt2_eet","h_pt2_emt","h_pt2_emm","h_pt2_mmm","h_pt2_mmt","h_pt2_ett","h_pt2_mtt","h_pt2_eeee","h_pt2_eeem","h_pt2_eemm","h_pt2_mmem","h_pt2_mmmm","h_pt2_eeet","h_pt2_eemt","h_pt2_eett","h_pt2_emtt","h_pt2_emmt","h_pt2_ettt","h_pt2_mmmt","h_pt2_mmtt","h_pt2_mttt",

"h_pt2v_ee","h_pt2v_em","h_pt2v_mm","h_pt2v_eee","h_pt2v_eem","h_pt2v_eet","h_pt2v_emt","h_pt2v_emm","h_pt2v_mmm","h_pt2v_mmt","h_pt2v_ett","h_pt2v_mtt","h_pt2v_eeee","h_pt2v_eeem","h_pt2v_eemm","h_pt2v_mmem","h_pt2v_mmmm","h_pt2v_eeet","h_pt2v_eemt","h_pt2v_eett","h_pt2v_emtt","h_pt2v_emmt","h_pt2v_ettt","h_pt2v_mmmt","h_pt2v_mmtt","h_pt2v_mttt",

"h_pt3_ee","h_pt3_em","h_pt3_mm","h_pt3_eee","h_pt3_eem","h_pt3_eet","h_pt3_emt","h_pt3_emm","h_pt3_mmm","h_pt3_mmt","h_pt3_ett","h_pt3_mtt","h_pt3_eeee","h_pt3_eeem","h_pt3_eemm","h_pt3_mmem","h_pt3_mmmm","h_pt3_eeet","h_pt3_eemt","h_pt3_eett","h_pt3_emtt","h_pt3_emmt","h_pt3_ettt","h_pt3_mmmt","h_pt3_mmtt","h_pt3_mttt",

"h_pt3v_ee","h_pt3v_em","h_pt3v_mm","h_pt3v_eee","h_pt3v_eem","h_pt3v_eet","h_pt3v_emt","h_pt3v_emm","h_pt3v_mmm","h_pt3v_mmt","h_pt3v_ett","h_pt3v_mtt","h_pt3v_eeee","h_pt3v_eeem","h_pt3v_eemm","h_pt3v_mmem","h_pt3v_mmmm","h_pt3v_eeet","h_pt3v_eemt","h_pt3v_eett","h_pt3v_emtt","h_pt3v_emmt","h_pt3v_ettt","h_pt3v_mmmt","h_pt3v_mmtt","h_pt3v_mttt",

"h_pt4_ee","h_pt4_em","h_pt4_mm","h_pt4_eee","h_pt4_eem","h_pt4_eet","h_pt4_emt","h_pt4_emm","h_pt4_mmm","h_pt4_mmt","h_pt4_ett","h_pt4_mtt","h_pt4_eeee","h_pt4_eeem","h_pt4_eemm","h_pt4_mmem","h_pt4_mmmm","h_pt4_eeet","h_pt4_eemt","h_pt4_eett","h_pt4_emtt","h_pt4_emmt","h_pt4_ettt","h_pt4_mmmt","h_pt4_mmtt","h_pt4_mttt",

"h_pt4v_ee","h_pt4v_em","h_pt4v_mm","h_pt4v_eee","h_pt4v_eem","h_pt4v_eet","h_pt4v_emt","h_pt4v_emm","h_pt4v_mmm","h_pt4v_mmt","h_pt4v_ett","h_pt4v_mtt","h_pt4v_eeee","h_pt4v_eeem","h_pt4v_eemm","h_pt4v_mmem","h_pt4v_mmmm","h_pt4v_eeet","h_pt4v_eemt","h_pt4v_eett","h_pt4v_emtt","h_pt4v_emmt","h_pt4v_ettt","h_pt4v_mmmt","h_pt4v_mmtt","h_pt4v_mttt",

"h_eta1_ee","h_eta1_em","h_eta1_mm","h_eta1_eee","h_eta1_eem","h_eta1_eet","h_eta1_emt","h_eta1_emm","h_eta1_mmm","h_eta1_mmt","h_eta1_ett","h_eta1_mtt","h_eta1_eeee","h_eta1_eeem","h_eta1_eemm","h_eta1_mmem","h_eta1_mmmm","h_eta1_eeet","h_eta1_eemt","h_eta1_eett","h_eta1_emtt","h_eta1_emmt","h_eta1_ettt","h_eta1_mmmt","h_eta1_mmtt","h_eta1_mttt",

"h_eta1v_ee","h_eta1v_em","h_eta1v_mm","h_eta1v_eee","h_eta1v_eem","h_eta1v_eet","h_eta1v_emt","h_eta1v_emm","h_eta1v_mmm","h_eta1v_mmt","h_eta1v_ett","h_eta1v_mtt","h_eta1v_eeee","h_eta1v_eeem","h_eta1v_eemm","h_eta1v_mmem","h_eta1v_mmmm","h_eta1v_eeet","h_eta1v_eemt","h_eta1v_eett","h_eta1v_emtt","h_eta1v_emmt","h_eta1v_ettt","h_eta1v_mmmt","h_eta1v_mmtt","h_eta1v_mttt",

"h_eta2_ee","h_eta2_em","h_eta2_mm","h_eta2_eee","h_eta2_eem","h_eta2_eet","h_eta2_emt","h_eta2_emm","h_eta2_mmm","h_eta2_mmt","h_eta2_ett","h_eta2_mtt","h_eta2_eeee","h_eta2_eeem","h_eta2_eemm","h_eta2_mmem","h_eta2_mmmm","h_eta2_eeet","h_eta2_eemt","h_eta2_eett","h_eta2_emtt","h_eta2_emmt","h_eta2_ettt","h_eta2_mmmt","h_eta2_mmtt","h_eta2_mttt",

"h_eta2v_ee","h_eta2v_em","h_eta2v_mm","h_eta2v_eee","h_eta2v_eem","h_eta2v_eet","h_eta2v_emt","h_eta2v_emm","h_eta2v_mmm","h_eta2v_mmt","h_eta2v_ett","h_eta2v_mtt","h_eta2v_eeee","h_eta2v_eeem","h_eta2v_eemm","h_eta2v_mmem","h_eta2v_mmmm","h_eta2v_eeet","h_eta2v_eemt","h_eta2v_eett","h_eta2v_emtt","h_eta2v_emmt","h_eta2v_ettt","h_eta2v_mmmt","h_eta2v_mmtt","h_eta2v_mttt",

"h_eta3_ee","h_eta3_em","h_eta3_mm","h_eta3_eee","h_eta3_eem","h_eta3_eet","h_eta3_emt","h_eta3_emm","h_eta3_mmm","h_eta3_mmt","h_eta3_ett","h_eta3_mtt","h_eta3_eeee","h_eta3_eeem","h_eta3_eemm","h_eta3_mmem","h_eta3_mmmm","h_eta3_eeet","h_eta3_eemt","h_eta3_eett","h_eta3_emtt","h_eta3_emmt","h_eta3_ettt","h_eta3_mmmt","h_eta3_mmtt","h_eta3_mttt",

"h_eta3v_ee","h_eta3v_em","h_eta3v_mm","h_eta3v_eee","h_eta3v_eem","h_eta3v_eet","h_eta3v_emt","h_eta3v_emm","h_eta3v_mmm","h_eta3v_mmt","h_eta3v_ett","h_eta3v_mtt","h_eta3v_eeee","h_eta3v_eeem","h_eta3v_eemm","h_eta3v_mmem","h_eta3v_mmmm","h_eta3v_eeet","h_eta3v_eemt","h_eta3v_eett","h_eta3v_emtt","h_eta3v_emmt","h_eta3v_ettt","h_eta3v_mmmt","h_eta3v_mmtt","h_eta3v_mttt",

"h_eta4_ee","h_eta4_em","h_eta4_mm","h_eta4_eee","h_eta4_eem","h_eta4_eet","h_eta4_emt","h_eta4_emm","h_eta4_mmm","h_eta4_mmt","h_eta4_ett","h_eta4_mtt","h_eta4_eeee","h_eta4_eeem","h_eta4_eemm","h_eta4_mmem","h_eta4_mmmm","h_eta4_eeet","h_eta4_eemt","h_eta4_eett","h_eta4_emtt","h_eta4_emmt","h_eta4_ettt","h_eta4_mmmt","h_eta4_mmtt","h_eta4_mttt",

"h_eta4v_ee","h_eta4v_em","h_eta4v_mm","h_eta4v_eee","h_eta4v_eem","h_eta4v_eet","h_eta4v_emt","h_eta4v_emm","h_eta4v_mmm","h_eta4v_mmt","h_eta4v_ett","h_eta4v_mtt","h_eta4v_eeee","h_eta4v_eeem","h_eta4v_eemm","h_eta4v_mmem","h_eta4v_mmmm","h_eta4v_eeet","h_eta4v_eemt","h_eta4v_eett","h_eta4v_emtt","h_eta4v_emmt","h_eta4v_ettt","h_eta4v_mmmt","h_eta4v_mmtt","h_eta4v_mttt",

"h_phi1_ee","h_phi1_em","h_phi1_mm","h_phi1_eee","h_phi1_eem","h_phi1_eet","h_phi1_emt","h_phi1_emm","h_phi1_mmm","h_phi1_mmt","h_phi1_ett","h_phi1_mtt","h_phi1_eeee","h_phi1_eeem","h_phi1_eemm","h_phi1_mmem","h_phi1_mmmm","h_phi1_eeet","h_phi1_eemt","h_phi1_eett","h_phi1_emtt","h_phi1_emmt","h_phi1_ettt","h_phi1_mmmt","h_phi1_mmtt","h_phi1_mttt",

"h_phi1v_ee","h_phi1v_em","h_phi1v_mm","h_phi1v_eee","h_phi1v_eem","h_phi1v_eet","h_phi1v_emt","h_phi1v_emm","h_phi1v_mmm","h_phi1v_mmt","h_phi1v_ett","h_phi1v_mtt","h_phi1v_eeee","h_phi1v_eeem","h_phi1v_eemm","h_phi1v_mmem","h_phi1v_mmmm","h_phi1v_eeet","h_phi1v_eemt","h_phi1v_eett","h_phi1v_emtt","h_phi1v_emmt","h_phi1v_ettt","h_phi1v_mmmt","h_phi1v_mmtt","h_phi1v_mttt",

"h_phi2_ee","h_phi2_em","h_phi2_mm","h_phi2_eee","h_phi2_eem","h_phi2_eet","h_phi2_emt","h_phi2_emm","h_phi2_mmm","h_phi2_mmt","h_phi2_ett","h_phi2_mtt","h_phi2_eeee","h_phi2_eeem","h_phi2_eemm","h_phi2_mmem","h_phi2_mmmm","h_phi2_eeet","h_phi2_eemt","h_phi2_eett","h_phi2_emtt","h_phi2_emmt","h_phi2_ettt","h_phi2_mmmt","h_phi2_mmtt","h_phi2_mttt",

"h_phi2v_ee","h_phi2v_em","h_phi2v_mm","h_phi2v_eee","h_phi2v_eem","h_phi2v_eet","h_phi2v_emt","h_phi2v_emm","h_phi2v_mmm","h_phi2v_mmt","h_phi2v_ett","h_phi2v_mtt","h_phi2v_eeee","h_phi2v_eeem","h_phi2v_eemm","h_phi2v_mmem","h_phi2v_mmmm","h_phi2v_eeet","h_phi2v_eemt","h_phi2v_eett","h_phi2v_emtt","h_phi2v_emmt","h_phi2v_ettt","h_phi2v_mmmt","h_phi2v_mmtt","h_phi2v_mttt",

"h_phi3_ee","h_phi3_em","h_phi3_mm","h_phi3_eee","h_phi3_eem","h_phi3_eet","h_phi3_emt","h_phi3_emm","h_phi3_mmm","h_phi3_mmt","h_phi3_ett","h_phi3_mtt","h_phi3_eeee","h_phi3_eeem","h_phi3_eemm","h_phi3_mmem","h_phi3_mmmm","h_phi3_eeet","h_phi3_eemt","h_phi3_eett","h_phi3_emtt","h_phi3_emmt","h_phi3_ettt","h_phi3_mmmt","h_phi3_mmtt","h_phi3_mttt",

"h_phi3v_ee","h_phi3v_em","h_phi3v_mm","h_phi3v_eee","h_phi3v_eem","h_phi3v_eet","h_phi3v_emt","h_phi3v_emm","h_phi3v_mmm","h_phi3v_mmt","h_phi3v_ett","h_phi3v_mtt","h_phi3v_eeee","h_phi3v_eeem","h_phi3v_eemm","h_phi3v_mmem","h_phi3v_mmmm","h_phi3v_eeet","h_phi3v_eemt","h_phi3v_eett","h_phi3v_emtt","h_phi3v_emmt","h_phi3v_ettt","h_phi3v_mmmt","h_phi3v_mmtt","h_phi3v_mttt",

"h_phi4_ee","h_phi4_em","h_phi4_mm","h_phi4_eee","h_phi4_eem","h_phi4_eet","h_phi4_emt","h_phi4_emm","h_phi4_mmm","h_phi4_mmt","h_phi4_ett","h_phi4_mtt","h_phi4_eeee","h_phi4_eeem","h_phi4_eemm","h_phi4_mmem","h_phi4_mmmm","h_phi4_eeet","h_phi4_eemt","h_phi4_eett","h_phi4_emtt","h_phi4_emmt","h_phi4_ettt","h_phi4_mmmt","h_phi4_mmtt","h_phi4_mttt",

"h_phi4v_ee","h_phi4v_em","h_phi4v_mm","h_phi4v_eee","h_phi4v_eem","h_phi4v_eet","h_phi4v_emt","h_phi4v_emm","h_phi4v_mmm","h_phi4v_mmt","h_phi4v_ett","h_phi4v_mtt","h_phi4v_eeee","h_phi4v_eeem","h_phi4v_eemm","h_phi4v_mmem","h_phi4v_mmmm","h_phi4v_eeet","h_phi4v_eemt","h_phi4v_eett","h_phi4v_emtt","h_phi4v_emmt","h_phi4v_ettt","h_phi4v_mmmt","h_phi4v_mmtt","h_phi4v_mttt",

"h_dxy1_ee","h_dxy1_em","h_dxy1_mm","h_dxy1_eee","h_dxy1_eem","h_dxy1_eet","h_dxy1_emt","h_dxy1_emm","h_dxy1_mmm","h_dxy1_mmt","h_dxy1_ett","h_dxy1_mtt","h_dxy1_eeee","h_dxy1_eeem","h_dxy1_eemm","h_dxy1_mmem","h_dxy1_mmmm","h_dxy1_eeet","h_dxy1_eemt","h_dxy1_eett","h_dxy1_emtt","h_dxy1_emmt","h_dxy1_ettt","h_dxy1_mmmt","h_dxy1_mmtt","h_dxy1_mttt",

"h_dxy1v_ee","h_dxy1v_em","h_dxy1v_mm","h_dxy1v_eee","h_dxy1v_eem","h_dxy1v_eet","h_dxy1v_emt","h_dxy1v_emm","h_dxy1v_mmm","h_dxy1v_mmt","h_dxy1v_ett","h_dxy1v_mtt","h_dxy1v_eeee","h_dxy1v_eeem","h_dxy1v_eemm","h_dxy1v_mmem","h_dxy1v_mmmm","h_dxy1v_eeet","h_dxy1v_eemt","h_dxy1v_eett","h_dxy1v_emtt","h_dxy1v_emmt","h_dxy1v_ettt","h_dxy1v_mmmt","h_dxy1v_mmtt","h_dxy1v_mttt",

"h_dxy2_ee","h_dxy2_em","h_dxy2_mm","h_dxy2_eee","h_dxy2_eem","h_dxy2_eet","h_dxy2_emt","h_dxy2_emm","h_dxy2_mmm","h_dxy2_mmt","h_dxy2_ett","h_dxy2_mtt","h_dxy2_eeee","h_dxy2_eeem","h_dxy2_eemm","h_dxy2_mmem","h_dxy2_mmmm","h_dxy2_eeet","h_dxy2_eemt","h_dxy2_eett","h_dxy2_emtt","h_dxy2_emmt","h_dxy2_ettt","h_dxy2_mmmt","h_dxy2_mmtt","h_dxy2_mttt",

"h_dxy2v_ee","h_dxy2v_em","h_dxy2v_mm","h_dxy2v_eee","h_dxy2v_eem","h_dxy2v_eet","h_dxy2v_emt","h_dxy2v_emm","h_dxy2v_mmm","h_dxy2v_mmt","h_dxy2v_ett","h_dxy2v_mtt","h_dxy2v_eeee","h_dxy2v_eeem","h_dxy2v_eemm","h_dxy2v_mmem","h_dxy2v_mmmm","h_dxy2v_eeet","h_dxy2v_eemt","h_dxy2v_eett","h_dxy2v_emtt","h_dxy2v_emmt","h_dxy2v_ettt","h_dxy2v_mmmt","h_dxy2v_mmtt","h_dxy2v_mttt",

"h_dxy3_ee","h_dxy3_em","h_dxy3_mm","h_dxy3_eee","h_dxy3_eem","h_dxy3_eet","h_dxy3_emt","h_dxy3_emm","h_dxy3_mmm","h_dxy3_mmt","h_dxy3_ett","h_dxy3_mtt","h_dxy3_eeee","h_dxy3_eeem","h_dxy3_eemm","h_dxy3_mmem","h_dxy3_mmmm","h_dxy3_eeet","h_dxy3_eemt","h_dxy3_eett","h_dxy3_emtt","h_dxy3_emmt","h_dxy3_ettt","h_dxy3_mmmt","h_dxy3_mmtt","h_dxy3_mttt",

"h_dxy3v_ee","h_dxy3v_em","h_dxy3v_mm","h_dxy3v_eee","h_dxy3v_eem","h_dxy3v_eet","h_dxy3v_emt","h_dxy3v_emm","h_dxy3v_mmm","h_dxy3v_mmt","h_dxy3v_ett","h_dxy3v_mtt","h_dxy3v_eeee","h_dxy3v_eeem","h_dxy3v_eemm","h_dxy3v_mmem","h_dxy3v_mmmm","h_dxy3v_eeet","h_dxy3v_eemt","h_dxy3v_eett","h_dxy3v_emtt","h_dxy3v_emmt","h_dxy3v_ettt","h_dxy3v_mmmt","h_dxy3v_mmtt","h_dxy3v_mttt",

"h_dxy4_ee","h_dxy4_em","h_dxy4_mm","h_dxy4_eee","h_dxy4_eem","h_dxy4_eet","h_dxy4_emt","h_dxy4_emm","h_dxy4_mmm","h_dxy4_mmt","h_dxy4_ett","h_dxy4_mtt","h_dxy4_eeee","h_dxy4_eeem","h_dxy4_eemm","h_dxy4_mmem","h_dxy4_mmmm","h_dxy4_eeet","h_dxy4_eemt","h_dxy4_eett","h_dxy4_emtt","h_dxy4_emmt","h_dxy4_ettt","h_dxy4_mmmt","h_dxy4_mmtt","h_dxy4_mttt",

"h_dxy4v_ee","h_dxy4v_em","h_dxy4v_mm","h_dxy4v_eee","h_dxy4v_eem","h_dxy4v_eet","h_dxy4v_emt","h_dxy4v_emm","h_dxy4v_mmm","h_dxy4v_mmt","h_dxy4v_ett","h_dxy4v_mtt","h_dxy4v_eeee","h_dxy4v_eeem","h_dxy4v_eemm","h_dxy4v_mmem","h_dxy4v_mmmm","h_dxy4v_eeet","h_dxy4v_eemt","h_dxy4v_eett","h_dxy4v_emtt","h_dxy4v_emmt","h_dxy4v_ettt","h_dxy4v_mmmt","h_dxy4v_mmtt","h_dxy4v_mttt",

"h_dZ1_ee","h_dZ1_em","h_dZ1_mm","h_dZ1_eee","h_dZ1_eem","h_dZ1_eet","h_dZ1_emt","h_dZ1_emm","h_dZ1_mmm","h_dZ1_mmt","h_dZ1_ett","h_dZ1_mtt","h_dZ1_eeee","h_dZ1_eeem","h_dZ1_eemm","h_dZ1_mmem","h_dZ1_mmmm","h_dZ1_eeet","h_dZ1_eemt","h_dZ1_eett","h_dZ1_emtt","h_dZ1_emmt","h_dZ1_ettt","h_dZ1_mmmt","h_dZ1_mmtt","h_dZ1_mttt",

"h_dZ1v_ee","h_dZ1v_em","h_dZ1v_mm","h_dZ1v_eee","h_dZ1v_eem","h_dZ1v_eet","h_dZ1v_emt","h_dZ1v_emm","h_dZ1v_mmm","h_dZ1v_mmt","h_dZ1v_ett","h_dZ1v_mtt","h_dZ1v_eeee","h_dZ1v_eeem","h_dZ1v_eemm","h_dZ1v_mmem","h_dZ1v_mmmm","h_dZ1v_eeet","h_dZ1v_eemt","h_dZ1v_eett","h_dZ1v_emtt","h_dZ1v_emmt","h_dZ1v_ettt","h_dZ1v_mmmt","h_dZ1v_mmtt","h_dZ1v_mttt",

"h_dZ2_ee","h_dZ2_em","h_dZ2_mm","h_dZ2_eee","h_dZ2_eem","h_dZ2_eet","h_dZ2_emt","h_dZ2_emm","h_dZ2_mmm","h_dZ2_mmt","h_dZ2_ett","h_dZ2_mtt","h_dZ2_eeee","h_dZ2_eeem","h_dZ2_eemm","h_dZ2_mmem","h_dZ2_mmmm","h_dZ2_eeet","h_dZ2_eemt","h_dZ2_eett","h_dZ2_emtt","h_dZ2_emmt","h_dZ2_ettt","h_dZ2_mmmt","h_dZ2_mmtt","h_dZ2_mttt",

"h_dZ2v_ee","h_dZ2v_em","h_dZ2v_mm","h_dZ2v_eee","h_dZ2v_eem","h_dZ2v_eet","h_dZ2v_emt","h_dZ2v_emm","h_dZ2v_mmm","h_dZ2v_mmt","h_dZ2v_ett","h_dZ2v_mtt","h_dZ2v_eeee","h_dZ2v_eeem","h_dZ2v_eemm","h_dZ2v_mmem","h_dZ2v_mmmm","h_dZ2v_eeet","h_dZ2v_eemt","h_dZ2v_eett","h_dZ2v_emtt","h_dZ2v_emmt","h_dZ2v_ettt","h_dZ2v_mmmt","h_dZ2v_mmtt","h_dZ2v_mttt",

"h_dZ3_ee","h_dZ3_em","h_dZ3_mm","h_dZ3_eee","h_dZ3_eem","h_dZ3_eet","h_dZ3_emt","h_dZ3_emm","h_dZ3_mmm","h_dZ3_mmt","h_dZ3_ett","h_dZ3_mtt","h_dZ3_eeee","h_dZ3_eeem","h_dZ3_eemm","h_dZ3_mmem","h_dZ3_mmmm","h_dZ3_eeet","h_dZ3_eemt","h_dZ3_eett","h_dZ3_emtt","h_dZ3_emmt","h_dZ3_ettt","h_dZ3_mmmt","h_dZ3_mmtt","h_dZ3_mttt",

"h_dZ3v_ee","h_dZ3v_em","h_dZ3v_mm","h_dZ3v_eee","h_dZ3v_eem","h_dZ3v_eet","h_dZ3v_emt","h_dZ3v_emm","h_dZ3v_mmm","h_dZ3v_mmt","h_dZ3v_ett","h_dZ3v_mtt","h_dZ3v_eeee","h_dZ3v_eeem","h_dZ3v_eemm","h_dZ3v_mmem","h_dZ3v_mmmm","h_dZ3v_eeet","h_dZ3v_eemt","h_dZ3v_eett","h_dZ3v_emtt","h_dZ3v_emmt","h_dZ3v_ettt","h_dZ3v_mmmt","h_dZ3v_mmtt","h_dZ3v_mttt",

"h_dZ4_ee","h_dZ4_em","h_dZ4_mm","h_dZ4_eee","h_dZ4_eem","h_dZ4_eet","h_dZ4_emt","h_dZ4_emm","h_dZ4_mmm","h_dZ4_mmt","h_dZ4_ett","h_dZ4_mtt","h_dZ4_eeee","h_dZ4_eeem","h_dZ4_eemm","h_dZ4_mmem","h_dZ4_mmmm","h_dZ4_eeet","h_dZ4_eemt","h_dZ4_eett","h_dZ4_emtt","h_dZ4_emmt","h_dZ4_ettt","h_dZ4_mmmt","h_dZ4_mmtt","h_dZ4_mttt",

"h_dZ4v_ee","h_dZ4v_em","h_dZ4v_mm","h_dZ4v_eee","h_dZ4v_eem","h_dZ4v_eet","h_dZ4v_emt","h_dZ4v_emm","h_dZ4v_mmm","h_dZ4v_mmt","h_dZ4v_ett","h_dZ4v_mtt","h_dZ4v_eeee","h_dZ4v_eeem","h_dZ4v_eemm","h_dZ4v_mmem","h_dZ4v_mmmm","h_dZ4v_eeet","h_dZ4v_eemt","h_dZ4v_eett","h_dZ4v_emtt","h_dZ4v_emmt","h_dZ4v_ettt","h_dZ4v_mmmt","h_dZ4v_mmtt","h_dZ4v_mttt",

"h_iso1_ee","h_iso1_em","h_iso1_mm","h_iso1_eee","h_iso1_eem","h_iso1_eet","h_iso1_emt","h_iso1_emm","h_iso1_mmm","h_iso1_mmt","h_iso1_ett","h_iso1_mtt","h_iso1_eeee","h_iso1_eeem","h_iso1_eemm","h_iso1_mmem","h_iso1_mmmm","h_iso1_eeet","h_iso1_eemt","h_iso1_eett","h_iso1_emtt","h_iso1_emmt","h_iso1_ettt","h_iso1_mmmt","h_iso1_mmtt","h_iso1_mttt",

"h_iso1v_ee","h_iso1v_em","h_iso1v_mm","h_iso1v_eee","h_iso1v_eem","h_iso1v_eet","h_iso1v_emt","h_iso1v_emm","h_iso1v_mmm","h_iso1v_mmt","h_iso1v_ett","h_iso1v_mtt","h_iso1v_eeee","h_iso1v_eeem","h_iso1v_eemm","h_iso1v_mmem","h_iso1v_mmmm","h_iso1v_eeet","h_iso1v_eemt","h_iso1v_eett","h_iso1v_emtt","h_iso1v_emmt","h_iso1v_ettt","h_iso1v_mmmt","h_iso1v_mmtt","h_iso1v_mttt",

"h_iso2_ee","h_iso2_em","h_iso2_mm","h_iso2_eee","h_iso2_eem","h_iso2_eet","h_iso2_emt","h_iso2_emm","h_iso2_mmm","h_iso2_mmt","h_iso2_ett","h_iso2_mtt","h_iso2_eeee","h_iso2_eeem","h_iso2_eemm","h_iso2_mmem","h_iso2_mmmm","h_iso2_eeet","h_iso2_eemt","h_iso2_eett","h_iso2_emtt","h_iso2_emmt","h_iso2_ettt","h_iso2_mmmt","h_iso2_mmtt","h_iso2_mttt",

"h_iso2v_ee","h_iso2v_em","h_iso2v_mm","h_iso2v_eee","h_iso2v_eem","h_iso2v_eet","h_iso2v_emt","h_iso2v_emm","h_iso2v_mmm","h_iso2v_mmt","h_iso2v_ett","h_iso2v_mtt","h_iso2v_eeee","h_iso2v_eeem","h_iso2v_eemm","h_iso2v_mmem","h_iso2v_mmmm","h_iso2v_eeet","h_iso2v_eemt","h_iso2v_eett","h_iso2v_emtt","h_iso2v_emmt","h_iso2v_ettt","h_iso2v_mmmt","h_iso2v_mmtt","h_iso2v_mttt",

"h_iso3_ee","h_iso3_em","h_iso3_mm","h_iso3_eee","h_iso3_eem","h_iso3_eet","h_iso3_emt","h_iso3_emm","h_iso3_mmm","h_iso3_mmt","h_iso3_ett","h_iso3_mtt","h_iso3_eeee","h_iso3_eeem","h_iso3_eemm","h_iso3_mmem","h_iso3_mmmm","h_iso3_eeet","h_iso3_eemt","h_iso3_eett","h_iso3_emtt","h_iso3_emmt","h_iso3_ettt","h_iso3_mmmt","h_iso3_mmtt","h_iso3_mttt",

"h_iso3v_ee","h_iso3v_em","h_iso3v_mm","h_iso3v_eee","h_iso3v_eem","h_iso3v_eet","h_iso3v_emt","h_iso3v_emm","h_iso3v_mmm","h_iso3v_mmt","h_iso3v_ett","h_iso3v_mtt","h_iso3v_eeee","h_iso3v_eeem","h_iso3v_eemm","h_iso3v_mmem","h_iso3v_mmmm","h_iso3v_eeet","h_iso3v_eemt","h_iso3v_eett","h_iso3v_emtt","h_iso3v_emmt","h_iso3v_ettt","h_iso3v_mmmt","h_iso3v_mmtt","h_iso3v_mttt",

"h_iso4_ee","h_iso4_em","h_iso4_mm","h_iso4_eee","h_iso4_eem","h_iso4_eet","h_iso4_emt","h_iso4_emm","h_iso4_mmm","h_iso4_mmt","h_iso4_ett","h_iso4_mtt","h_iso4_eeee","h_iso4_eeem","h_iso4_eemm","h_iso4_mmem","h_iso4_mmmm","h_iso4_eeet","h_iso4_eemt","h_iso4_eett","h_iso4_emtt","h_iso4_emmt","h_iso4_ettt","h_iso4_mmmt","h_iso4_mmtt","h_iso4_mttt",

"h_iso4v_ee","h_iso4v_em","h_iso4v_mm","h_iso4v_eee","h_iso4v_eem","h_iso4v_eet","h_iso4v_emt","h_iso4v_emm","h_iso4v_mmm","h_iso4v_mmt","h_iso4v_ett","h_iso4v_mtt","h_iso4v_eeee","h_iso4v_eeem","h_iso4v_eemm","h_iso4v_mmem","h_iso4v_mmmm","h_iso4v_eeet","h_iso4v_eemt","h_iso4v_eett","h_iso4v_emtt","h_iso4v_emmt","h_iso4v_ettt","h_iso4v_mmmt","h_iso4v_mmtt","h_iso4v_mttt"

	};*/

	{
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
        {"data",  {"SingleElectron_2016.root","EGamma_2016.root", "SingleMuon_2016.root","SingleElectron_2017.root","EGamma_2017.root", "SingleMuon_2017.root","SingleElectron_2018.root","EGamma_2018.root", "SingleMuon_2018.root"}}
    };
    std::map<std::string, std::vector<TFile*>> open_files;
    for (auto& kv : files) {
		for (const auto& fname : kv.second) {
		    TFile* file = new TFile(("hist_CR/" + fname).c_str(), "READ");
		    if (!file || file->IsZombie()) continue;
	        open_files[kv.first].push_back(file);
	    }
	}
	TFile *ifile_D1 = new TFile("hist_CR/EGamma_2018.root","READ");
  
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
			size_t pos = name.rfind('_'); // find last underscore
			std::string channel = (pos != std::string::npos) ? name.substr(pos + 1) : ""; 
			hist_string += channel + " channel ";
			
			if (name.find("v_") < name.length()) hist_string += "in Z-veto";  
			else if (name.find("v_") > name.length()) hist_string += "in Z-window";
		}
		else {
			if (name.find("3lep") < name.length()) hist_string += "3l, ";
			if (name.find("0tau") < name.length()) hist_string += "0-#tau channel";
			else if (name.find("1tau") < name.length()) hist_string += "1-#tau channel";
			else if (name.find("2tau") < name.length()) hist_string += "2-#tau channel";
			else if (name.find("3tau") < name.length()) hist_string += "3-#tau channel";
		}
		char *hist_name = const_cast<char*>(hist_string.c_str());
		
		THStack* bkg_stack = new THStack("bkg_stack", hist_name);
		std::map<std::string, TH1D*> hist;
		std::map<std::string, int> fill_colors = {
		    {"DY", 7}, {"VV", 8}, {"VVV", 6}, {"ttV", 4}, {"WJ", 9}, {"ZZ", 5},
		    {"ST", 30}, {"TTbar", 46}, {"other", 28}, {"data", 1}
		};
		
		int bins = 0;
		for (auto& kv : open_files) {
			TH1D* tmp = (TH1D*)ifile_D1->Get(hist_list[i]);
			hist[kv.first]=(TH1D*)tmp->Clone();
		    hist[kv.first]->Sumw2();
		    hist[kv.first]->Reset();
		    double tot_uncert_quadr[tmp->GetNbinsX()];
			for (auto* f : kv.second) {
		        TH1D* h = dynamic_cast<TH1D*>(f->Get(hist_list[i]));
		        if (!h) continue;
		        h->Sumw2();
		        h->Rebin(5);
				if (kv.first != "data") {
					for (int ib = 1; ib <= h->GetNbinsX(); ib++) {
						double stat_err = h->GetBinError(ib);
						double sys_err = h->GetBinContent(ib) * XSec_Uncert(f->GetName()) / 100.0;
		          		double tot_uncert_quadr = (stat_err*stat_err + sys_err*sys_err);
		          		if(summary_type == "tau_ch"){
		            		if (name.find("3lep") < name.length()) tot_uncert_quadr += fake_uncert_squared("3lep", f->GetName())*h->GetBinContent(ib)*h->GetBinContent(ib);
		            		else tot_uncert_quadr += fake_uncert_squared("4lep", f->GetName())*h->GetBinContent(ib)*h->GetBinContent(ib);
		            	}
		            	else if(name != "h_met_ee" and name != "h_met_mm" and name != "h_metv_ee" and name != "h_metv_mm") tot_uncert_quadr += fake_uncert_squared(summary_type, f->GetName())*h->GetBinContent(ib)*h->GetBinContent(ib);
		            	//cout<<tot_uncert_quadr[ib]<<endl;
		            	h->SetBinError(ib,sqrt(tot_uncert_quadr));
					}
				}
				hist[kv.first]->Add(h);
			}
			if (hist[kv.first]) {
				hist[kv.first]->SetFillColor(fill_colors[kv.first]);
				bins = hist[kv.first]->GetNbinsX();
			}
		}

		hist["VV"]->Scale(1.12631);
		hist["ZZ"]->Scale(1.31366);
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
			cout<<h_bkg_total->GetBinError(j)<<"\t"<<h_bkg_total->GetBinContent(j)<<endl;
		}
		
		// Draw main plot
		pad1->cd();
		//gPad->SetLogy(1);
		bkg_stack->Draw("hist");
		double pad_max = std::max(bkg_stack->GetMaximum(),hist["data"]->GetMaximum());
		bkg_stack->SetMaximum(1.1*pad_max);
		hist["data"]->SetMarkerStyle(20);
		hist["data"]->SetMarkerColor(kBlack);
		bkg_stack->GetYaxis()->SetTitle("Events");
		hist["data"]->Draw("E SAME");

		//Signal
		hist["signal"]->SetLineStyle(5);
		hist["signal"]->SetLineColor(2);
		hist["signal"]->Scale(100);
		//hist["signal"]->Scale(h_bkg_total->Integral()/hist["signal"]->Integral());
		hist["signal"]->SetBinContent(bins, hist["signal"]->GetBinContent(bins)+hist["signal"]->GetBinContent(bins+1));
		//hist["signal"]->Draw("SAME");
		
		// Create a TLatex object
		TLatex latex;
		latex.SetNDC(); // Use normalized coordinates (0 to 1)
		latex.SetTextSize(0.04); // Set text size
		latex.SetTextAlign(31); // Align right (horizontal) and top (vertical)
		latex.DrawLatex(0.95, 0.95, const_cast<char*>(year.c_str())); // Position (x, y) and text

		auto legend = new TLegend(0.7, 0.6, 0.88, 0.88);
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
		else if (name.find("_met") < name.length()) X_string += "Missing E_{T} ";
		else if (name.find("_ST") < name.length()) X_string += "S_{T} ";
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
		h_ratio->SetMarkerStyle(2);
		h_ratio->GetYaxis()->SetTitle("Data/MC");
		h_ratio->GetYaxis()->SetNdivisions(505);
		h_ratio->GetYaxis()->SetTitleSize(0.1);
		h_ratio->GetYaxis()->SetTitleOffset(0.5);
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
		std::string s =  "hist_CR/", s1, s2;
		s1 = s + hist_list[i]+".png";
		//s2 = s + hist_list[i]+".svg";
		char* title1 = const_cast<char*>(s1.c_str());//converting string to char
		//char* title2 = const_cast<char*>(s2.c_str());//converting string to char
		canvas->SaveAs(title1);
		//canvas->SaveAs(title2);
		canvas->Clear();
	}
}
