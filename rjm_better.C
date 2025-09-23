// met_reco_with_pz_options.cc
// Compile: g++ -O2 -std=c++17 `root-config --cflags --libs` met_reco_with_pz_options.cc -o met_reco_with_pz_options

#include <iostream>
#include <array>
#include <cmath>
#include <limits>
#include <vector>

#include "TLorentzVector.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TMinuit.h"
#include "TMath.h"

// ---------- Globals for Minuit (alphas fit) ----------
static std::array<TLorentzVector,4> gLep_ref, gLep_lab;
static TVector2 gMET_ref;
static TVector2 g_uT[4];
static double g_reg_alpha = 1e-3; // tiny regularizer weight

// alpha_i = x_i^2 to enforce non-negativity; Minuit params are x_i.
void fcn_alphas(int &npar, double *, double &f, double *x, int) {
    double a[4];
    for (int i=0;i<4;++i) a[i] = x[i]*x[i];

    // MET closure term (GeV^2)
    TVector2 met_fit(0,0);
    for (int i=0;i<4;++i) met_fit += a[i] * g_uT[i];
    TVector2 r = gMET_ref - met_fit;
    double term_met = r.Mod2();

    // Regularizer to pick small alphas among continuum
    double term_reg = 0;
    for (int i=0;i<4;++i) term_reg += a[i]*a[i];

    f = term_met + g_reg_alpha * term_reg;
}

// ---------- Helpers ----------
TLorentzVector make_collinear_nu_ref(const TLorentzVector &lep_ref, double a) {
    // a is transverse magnitude for neutrino in REF frame (GeV)
    double ptL = lep_ref.Pt();
    if (ptL <= 1e-12 || a <= 0) return TLorentzVector(0,0,0,0);
    double k = a / ptL;
    TVector3 pnu = k * lep_ref.Vect(); // collinear in 3D
    return TLorentzVector(pnu.X(), pnu.Y(), pnu.Z(), pnu.Mag()); // massless
}

// compute MH1 and MH2 in LAB given alphas (in REF) and neutrino pz policy applied
std::pair<double,double> masses_from_alphas_with_pzpolicy(
    const double a_ref[4],
    const std::string &pz_policy,
    const std::vector<double> &s_fit // used only for fit policy; size may be 0 -> ignored
) {
    // build neutrinos in REF: start with transverse a_ref and zero pz; then set pz according to policy
    TLorentzVector nu_ref[4];
    for (int i=0;i<4;++i) {
        // start as purely transverse massless vector along uT direction with magnitude a_ref[i]
        double pt_n = a_ref[i];
        if (pt_n <= 0) { nu_ref[i].SetPxPyPzE(0,0,0,0); continue; }
        // direction unit vector
        double ux = g_uT[i].X(), uy = g_uT[i].Y();
        double px = pt_n * ux, py = pt_n * uy;
        double pz = 0.0;
        if (pz_policy == "collinear") {
            double ptL = gLep_ref[i].Pt();
            double pzL = gLep_ref[i].Pz();
            double k = (ptL > 1e-12) ? (pt_n / ptL) : 0.0;
            pz = k * pzL;
        } else if (pz_policy == "equal_rapidity") {
            // y_n = y_l -> pz_n = pt_n * sinh(y_l)
            double yL = gLep_ref[i].Rapidity();
            pz = pt_n * std::sinh(yL);
        } else if (pz_policy == "fit") {
            // use scale factor s_fit[i] to scale lepton pz: pz_n = s_i * pz_lep
            if ((int)s_fit.size() == 4) {
                double pzL = gLep_ref[i].Pz();
                pz = s_fit[i] * pzL;
                // but ensure massless energy consistent:
                // energy = sqrt(px^2+py^2+pz^2)
            } else pz = 0.0;
        } else {
            // default fallback: collinear
            double ptL = gLep_ref[i].Pt();
            double pzL = gLep_ref[i].Pz();
            double k = (ptL > 1e-12) ? (pt_n / ptL) : 0.0;
            pz = k * pzL;
        }
        double E = std::sqrt(px*px + py*py + pz*pz);
        nu_ref[i].SetPxPyPzE(px, py, pz, E);
    }

    // boost nu_ref back to LAB: we need betaZ that was used to make REF; we can get it from gLep_lab sum
    TLorentzVector Pvis_lab(0,0,0,0);
    for (int i=0;i<4;++i) Pvis_lab += gLep_lab[i];
    double betaZ = (std::abs(Pvis_lab.E())>1e-12) ? (-Pvis_lab.Pz()/Pvis_lab.E()) : 0.0;

    TLorentzVector nu_lab[4];
    for (int i=0;i<4;++i) { nu_lab[i] = nu_ref[i]; nu_lab[i].Boost(0,0,-betaZ); }

    // Form H1 = (0+1) and H2 = (2+3)
    TLorentzVector H1 = gLep_lab[0] + gLep_lab[1] + nu_lab[0] + nu_lab[1];
    TLorentzVector H2 = gLep_lab[2] + gLep_lab[3] + nu_lab[2] + nu_lab[3];

    return { H1.M(), H2.M() };
}

// ---------- Fit for pz scale factors (fit policy) ----------
static std::array<double,4> g_alphas_for_pzfit; // store alphas for the fit FCN
static double g_pzfit_reg = 1e-2;
void fcn_pzfit(int &npar, double*, double &f, double *par, int) {
    // par are s0..s3 (scale factors for lepton pz)
    std::vector<double> s(4,0.0);
    for (int i=0;i<4;++i) s[i] = par[i];

    // compute masses with these s
    std::vector<double> s_vec(4);
    for (int i=0;i<4;++i) s_vec[i] = s[i];
    auto [m1,m2] = masses_from_alphas_with_pzpolicy(g_alphas_for_pzfit.data(), "fit", s_vec);

    double term_massdiff = (m1 - m2)*(m1 - m2);
    double term_reg = 0.0;
    for (int i=0;i<4;++i) term_reg += s[i]*s[i];

    f = term_massdiff + g_pzfit_reg * term_reg;
}

// ---------- Main routine: runs full flow for one event ----------
struct Result {
    bool ok = false;
    double alpha[4]={0,0,0,0}; // in REF frame
    double residual = 0;
    double MH1 = 0, MH2 = 0;
    TLorentzVector nu_lab[4];
};

Result run_reco_event(const std::array<TLorentzVector,4> &leps_lab, const TVector2 &MET_lab,
                      const std::string &pz_policy = "collinear",
                      bool run_pz_fit = false)
{
    Result out;
    gLep_lab = leps_lab;

    // 1) boost to REF where Pz_vis = 0
    TLorentzVector Pvis_lab(0,0,0,0);
    for (int i=0;i<4;++i) Pvis_lab += gLep_lab[i];
    double betaZ = (std::abs(Pvis_lab.E())>1e-12) ? (-Pvis_lab.Pz()/Pvis_lab.E()) : 0.0;

    gLep_ref = gLep_lab;
    for (int i=0;i<4;++i) gLep_ref[i].Boost(0,0,betaZ);

    // MET_ref unchanged under pure z-boost approximation
    gMET_ref = MET_lab;

    // unit transverse directions
    for (int i=0;i<4;++i) {
        double pt = gLep_ref[i].Pt();
        if (pt > 1e-12) g_uT[i] = TVector2(gLep_ref[i].Px()/pt, gLep_ref[i].Py()/pt);
        else g_uT[i] = TVector2(0,0);
    }

    // 2) Fit alphas with Minuit (params x_i where alpha_i = x_i^2)
    TMinuit minuit_a(4);
    minuit_a.SetFCN(fcn_alphas);
    minuit_a.SetPrintLevel(-1);

    double start[4];
    double step[4] = {0.5,0.5,0.5,0.5};
    double metmag = gMET_ref.Mod();
    for (int i=0;i<4;++i) start[i] = std::sqrt(std::max(0.0, metmag/4.0));

    for (int i=0;i<4;++i) minuit_a.DefineParameter(i, Form("x%d",i), start[i], step[i], 0, 0);

    int ierflg=0;
    minuit_a.Migrad();

    double xi, ex;
    double alphas[4];
    for (int i=0;i<4;++i) {
        minuit_a.GetParameter(i, xi, ex);
        alphas[i] = xi*xi;
    }

    // compute residual MET in REF
    TVector2 met_fit(0,0);
    for (int i=0;i<4;++i) met_fit += alphas[i] * g_uT[i];
    out.residual = (gMET_ref - met_fit).Mod();

    // 3) apply pz policy
    if (pz_policy == "fit" || run_pz_fit) {
        // prepare global for pz fit
        for (int i=0;i<4;++i) g_alphas_for_pzfit[i] = alphas[i];
        TMinuit minuit_pz(4);
        minuit_pz.SetFCN(fcn_pzfit);
        minuit_pz.SetPrintLevel(-1);
        // start s_i = k where k = alpha / pt_lep as a guess
        double sstart[4], sstep[4];
        for (int i=0;i<4;++i) {
            double ptL = gLep_ref[i].Pt();
            double pzL = gLep_ref[i].Pz();
            double kguess = (ptL>1e-12) ? ( (alphas[i]/ptL) / ( (pzL/ptL==0)?1.0:(pzL/ptL) ) ) : 0.0;
            // simpler start: s=alpha/pt if pzL and ptL both nonzero -> s ~ k
            sstart[i] = (ptL>1e-12) ? (alphas[i]/ptL) : 0.0;
            sstep[i] = std::max(0.1, fabs(sstart[i])*0.2 + 0.1);
            minuit_pz.DefineParameter(i, Form("s%d",i), sstart[i], sstep[i], -5.0, 5.0);
        }
        minuit_pz.Migrad();
        double sfit[4], err;
        for (int i=0;i<4;++i) { minuit_pz.GetParameter(i, sfit[i], err); }
        // now build neutrinos with fit sfit
        auto masses = masses_from_alphas_with_pzpolicy(alphas, "fit", std::vector<double>(sfit, sfit+4));
        out.MH1 = masses.first; out.MH2 = masses.second;
        // build nu_lab for output
        // reuse masses_from... behavior to get nu_lab: do small copy here
        // build nu_ref as in masses_from... then boost
        TLorentzVector nu_ref[4];
        for (int i=0;i<4;++i) {
            double pt_n = alphas[i];
            if (pt_n <= 0) { nu_ref[i].SetPxPyPzE(0,0,0,0); continue; }
            double ux = g_uT[i].X(), uy = g_uT[i].Y();
            double px = pt_n * ux, py = pt_n * uy;
            double pz = sfit[i] * gLep_ref[i].Pz();
            double E = std::sqrt(px*px + py*py + pz*pz);
            nu_ref[i].SetPxPyPzE(px,py,pz,E);
        }
        double betaZ = (std::abs(Pvis_lab.E())>1e-12) ? (-Pvis_lab.Pz()/Pvis_lab.E()) : 0.0; // careful: Pvis_lab not in scope
        // get betaZ via recompute
        TLorentzVector Pvis(0,0,0,0); for (int i=0;i<4;++i) Pvis += gLep_lab[i];
        betaZ = (std::abs(Pvis.E())>1e-12) ? (-Pvis.Pz()/Pvis.E()) : 0.0;
        for (int i=0;i<4;++i) { out.nu_lab[i] = nu_ref[i]; out.nu_lab[i].Boost(0,0,-betaZ); }
        out.ok = true;
        for (int i=0;i<4;++i) out.alpha[i] = alphas[i];
        return out;
    } else {
        // policies: "collinear" or "equal_rapidity" implemented directly
        auto masses = masses_from_alphas_with_pzpolicy(alphas, pz_policy, std::vector<double>());
        out.MH1 = masses.first; out.MH2 = masses.second;
        // build nu_lab for output
        TLorentzVector nu_ref[4];
        for (int i=0;i<4;++i) {
            double pt_n = alphas[i];
            if (pt_n <= 0) { nu_ref[i].SetPxPyPzE(0,0,0,0); continue; }
            double ux = g_uT[i].X(), uy = g_uT[i].Y();
            double px = pt_n * ux, py = pt_n * uy;
            double pz = 0.0;
            if (pz_policy == "collinear") {
                double ptL = gLep_ref[i].Pt(), pzL = gLep_ref[i].Pz();
                double k = (ptL>1e-12) ? (pt_n / ptL) : 0.0;
                pz = k * pzL;
            } else { // equal_rapidity
                double yL = gLep_ref[i].Rapidity();
                pz = pt_n * std::sinh(yL);
            }
            double E = std::sqrt(px*px + py*py + pz*pz);
            nu_ref[i].SetPxPyPzE(px,py,pz,E);
        }
        TLorentzVector Pvis(0,0,0,0); for (int i=0;i<4;++i) Pvis += gLep_lab[i];
        double betaZ = (std::abs(Pvis.E())>1e-12) ? (-Pvis.Pz()/Pvis.E()) : 0.0;
        for (int i=0;i<4;++i) { out.nu_lab[i] = nu_ref[i]; out.nu_lab[i].Boost(0,0,-betaZ); }
        out.ok = true;
        for (int i=0;i<4;++i) out.alpha[i] = alphas[i];
        return out;
    }
}
