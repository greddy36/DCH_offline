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

// ---------- Utility: solve 2x2 linear system for pair (i,j) ----------
static std::tuple<bool,double,double,double>
solve_pair_analytic(const TVector2 &MET, const TVector2 &ui, const TVector2 &uj) {
    // Solve for ai, aj in ui*ai + uj*aj = MET (2 equations)
    // Gram matrix G = [[ui·ui, ui·uj],[uj·ui, uj·uj]], b = [ui·MET, uj·MET]
    double uiu = ui.Mod2();
    double uju = uj.Mod2();
    double uij = ui.X()*uj.X() + ui.Y()*uj.Y();
    double bi  = ui.X()*MET.X() + ui.Y()*MET.Y();
    double bj  = uj.X()*MET.X() + uj.Y()*MET.Y();

    double det = uiu*uju - uij*uij;
    if (std::abs(det) < 1e-12) {
        // nearly collinear: fallback to projecting MET onto each axis in turn (non-negative)
        double ai = (uiu>0) ? std::max(0.0, bi/uiu) : 0.0;
        TVector2 r = MET - ai * ui;
        double aj = (uju>0) ? std::max(0.0, (uj.X()*r.X()+uj.Y()*r.Y())/uju) : 0.0;
        TVector2 resid = MET - ai*ui - aj*uj;
        return { (ai>=0 && aj>=0), ai, aj, resid.Mod() };
    }

    double ai = (  uju*bi - uij*bj ) / det;
    double aj = ( -uij*bi + uiu*bj ) / det;
    TVector2 resid = MET - ai*ui - aj*uj;
    return { (ai >= -1e-12 && aj >= -1e-12), ai, aj, resid.Mod() };
}

// alpha_i = x_i^2 to enforce non-negativity; Minuit params are x_i.
void fcn_alphas_minuit(int &npar, double *, double &f, double *x, int) {
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

// Signature:
// returns pair<MH1, MH2>. If zero_opposite==true, any neutrino whose 3-vector
// dot lepton_3vec <= eps will be treated as zero for the mass computation.
// Optionally fills zeroedIndices (size 4) and nu_lab_out (size 4).
std::pair<double,double> masses_from_alphas_with_pzpolicy(
    const double a_ref[4],
    const std::string &pz_policy,
    const std::vector<double> &s_fit, // for "fit" policy; size==4 expected
    bool zero_opposite,
    std::array<bool,4>* zeroedIndices = nullptr,
    std::array<TLorentzVector,4>* nu_lab_out = nullptr
) {
    // build neutrinos in REF
    TLorentzVector nu_ref[4];
    for (int i=0;i<4;++i) {
        double pt_n = a_ref[i];
        if (pt_n <= 0) { nu_ref[i].SetPxPyPzE(0,0,0,0); continue; }
        double ux = g_uT[i].X(), uy = g_uT[i].Y();
        double px = pt_n * ux, py = pt_n * uy;
        double pz = 0.0;
        if (pz_policy == "collinear") {
            double ptL = gLep_ref[i].Pt();
            double pzL = gLep_ref[i].Pz();
            double k = (ptL>1e-12) ? (pt_n / ptL) : 0.0;
            pz = k * pzL;
        } else if (pz_policy == "equal_rapidity") {
            double yL = gLep_ref[i].Rapidity();
            pz = pt_n * std::sinh(yL);
        } else if (pz_policy == "fit") {
            if ((int)s_fit.size() == 4) {
                double pzL = gLep_ref[i].Pz();
                pz = s_fit[i] * pzL;
            } else pz = 0.0;
        } else {
            // fallback to collinear
            double ptL = gLep_ref[i].Pt();
            double pzL = gLep_ref[i].Pz();
            double k = (ptL>1e-12) ? (pt_n / ptL) : 0.0;
            pz = k * pzL;
        }
        double E = std::sqrt(px*px + py*py + pz*pz);
        nu_ref[i].SetPxPyPzE(px,py,pz,E);
    }

    // If requested, zero neutrinos that are anti-aligned with their lepton:
    std::array<bool,4> zeroed = {false,false,false,false};
    if (zero_opposite) {
        const double eps = 1e-8;
        for (int i=0;i<4;++i) {
            if (nu_ref[i].P() <= 0) { zeroed[i] = true; nu_ref[i].SetPxPyPzE(0,0,0,0); continue; }
            double dot = nu_ref[i].Vect().Dot(gLep_ref[i].Vect());
            if (dot <= eps) { // not pointing in same direction -> discard neutrino
                zeroed[i] = true;
                nu_ref[i].SetPxPyPzE(0,0,0,0);
            }
        }
        if (zeroedIndices) *zeroedIndices = zeroed;
    }

    // compute betaZ to boost back to lab
    TLorentzVector Pvis_lab(0,0,0,0);
    for (int i=0;i<4;++i) Pvis_lab += gLep_lab[i];
    double betaZ = (std::abs(Pvis_lab.E())>1e-12) ? (-Pvis_lab.Pz()/Pvis_lab.E()) : 0.0;

    // boost nu_ref -> nu_lab and optionally fill nu_lab_out
    TLorentzVector nu_lab[4];
    for (int i=0;i<4;++i) { nu_lab[i] = nu_ref[i]; nu_lab[i].Boost(0,0,-betaZ); }
    if (nu_lab_out) for (int i=0;i<4;++i) (*nu_lab_out)[i] = nu_lab[i];

    // build H1=(0,1), H2=(2,3)
    TLorentzVector H1 = gLep_lab[0] + gLep_lab[1] + nu_lab[0] + nu_lab[1];
    TLorentzVector H2 = gLep_lab[2] + gLep_lab[3] + nu_lab[2] + nu_lab[3];

    return { H1.M(), H2.M() };
}

// ---------- Fit for pz scale factors (fit policy) ----------
static std::array<double,4> g_alphas_for_pzfit; // store alphas for the fit FCN
static double g_pzfit_reg = 1e-2;
void fcn_pzfit(int &npar, double*, double &f, double *par, int) {
    std::vector<double> s(4,0.0);
    for (int i=0;i<4;++i) s[i] = par[i];
    auto [m1,m2] = masses_from_alphas_with_pzpolicy(g_alphas_for_pzfit.data(), "fit", s, /*zero_opposite=*/false, nullptr, nullptr);
    double term_massdiff = (m1 - m2)*(m1 - m2);
    double term_reg = 0.0;
    for (int i=0;i<4;++i) term_reg += s[i]*s[i];
    f = term_massdiff + g_pzfit_reg * term_reg;
}

// ---------- Main routine: runs full flow for one event ----------
struct Result {
    bool ok = false;
    double alpha[4]={0,0,0,0}; // in REF frame (final, possibly zeroed)
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

    // MET_ref unchanged under pure z-boost
    gMET_ref = MET_lab;

    // unit transverse directions
    for (int i=0;i<4;++i) {
        double pt = gLep_ref[i].Pt();
        if (pt > 1e-12) g_uT[i] = TVector2(gLep_ref[i].Px()/pt, gLep_ref[i].Py()/pt);
        else g_uT[i] = TVector2(0,0);
    }

    // -------- Try analytic solutions with <=2 alphas --------
    double best_resid = std::numeric_limits<double>::infinity();
    double best_alphas[4] = {0,0,0,0};
    int best_nonzero_count = 0;

    // 1) Single-lepton projections
    for (int i=0;i<4;++i) {
        double ai = std::max(0.0, g_uT[i].X()*gMET_ref.X() + g_uT[i].Y()*gMET_ref.Y());
        TVector2 fit = ai * g_uT[i];
        double resid = (gMET_ref - fit).Mod();
        if (resid < best_resid) {
            best_resid = resid;
            std::fill(std::begin(best_alphas), std::end(best_alphas), 0.0);
            best_alphas[i] = ai;
            best_nonzero_count = (ai > 1e-9) ? 1 : 0;
        }
    }

    // 2) Pairs (i,j)
    for (int i=0;i<4;++i){
        for (int j=i+1;j<4;++j){
            auto [ok, ai, aj, resid] = solve_pair_analytic(gMET_ref, g_uT[i], g_uT[j]);
            if (!ok) continue;
            if (resid < best_resid) {
                best_resid = resid;
                std::fill(std::begin(best_alphas), std::end(best_alphas), 0.0);
                best_alphas[i] = ai;
                best_alphas[j] = aj;
                best_nonzero_count = ((ai>1e-9) + (aj>1e-9));
            }
        }
    }

    // Accept analytic solution if residual is small enough.
    // Threshold can be tuned; we choose something like MET * 1e-3 + 0.5 GeV absolute.
    double accept_thresh = std::max(1e-3 * gMET_ref.Mod(), 0.5);
    bool analytic_ok = (best_nonzero_count <= 2 && best_resid <= accept_thresh);

    double alphas[4] = {0,0,0,0};
    if (analytic_ok) {
        // Use analytic solution (no Minuit)
        for (int i=0;i<4;++i) alphas[i] = best_alphas[i];
    } else {
        // Fallback: full Minuit fit (handles 3 or 4 non-zero alphas)
        TMinuit minuit_a(4);
        minuit_a.SetFCN(fcn_alphas_minuit);
        minuit_a.SetPrintLevel(-1);

        double metmag = gMET_ref.Mod();
        double start[4];
        double step[4] = {0.5,0.5,0.5,0.5};
        for (int i=0;i<4;++i) start[i] = std::sqrt(std::max(0.0, metmag/4.0));
        for (int i=0;i<4;++i) minuit_a.DefineParameter(i, Form("x%d",i), start[i], step[i], 0, 0);

        minuit_a.Migrad();

        double xi, ex;
        for (int i=0;i<4;++i) { minuit_a.GetParameter(i, xi, ex); alphas[i] = xi*xi; }
    }

    // Compute residual before dot-check
    TVector2 met_fit_before(0,0);
    for (int i=0;i<4;++i) met_fit_before += alphas[i] * g_uT[i];
    double resid_before = (gMET_ref - met_fit_before).Mod();

    // If requested, run pz-fit (we will prepare sfit_vec if needed)
    std::vector<double> sfit_vec;
    if (pz_policy == "fit" || run_pz_fit) {
        for (int i=0;i<4;++i) g_alphas_for_pzfit[i] = alphas[i];
        TMinuit minuit_pz(4);
        minuit_pz.SetFCN(fcn_pzfit);
        minuit_pz.SetPrintLevel(-1);
        for (int i=0;i<4;++i) {
            double ptL = gLep_ref[i].Pt();
            double sstart = (ptL>1e-12) ? (alphas[i]/ptL) : 0.0;
            double sstep = std::max(0.1, fabs(sstart)*0.2 + 0.1);
            minuit_pz.DefineParameter(i, Form("s%d",i), sstart, sstep, -10.0, 10.0);
        }
        minuit_pz.Migrad();
        double sfit[4], err;
        for (int i=0;i<4;++i) { minuit_pz.GetParameter(i, sfit[i], err); }
        sfit_vec.assign(sfit, sfit+4);
    }

    // Final mass computation with dot-check; zero neutrinos anti-aligned with lepton
    std::array<bool,4> zeroed = {false,false,false,false};
    std::array<TLorentzVector,4> nu_lab_out;
    auto masses = masses_from_alphas_with_pzpolicy(alphas, pz_policy, sfit_vec, /*zero_opposite=*/true, &zeroed, &nu_lab_out);
    out.MH1 = masses.first; out.MH2 = masses.second;

    // Apply zeroing and build final neutrinos/loss
    for (int i=0;i<4;++i) {
        out.alpha[i] = zeroed[i] ? 0.0 : alphas[i];
        out.nu_lab[i] = nu_lab_out[i];
    }

    // If zeroing removed some alphas and we used analytic solution, it's safe.
    // If zeroing removed many alphas and analytic had been used, consider re-solving analytically for
    // the reduced system. We'll implement a simple re-solve for <=2 survivors to improve closure.
    // Count survivors:
    std::vector<int> survivors;
    for (int i=0;i<4;++i) if (out.alpha[i] > 1e-9) survivors.push_back(i);

    if ((int)survivors.size() <= 2) {
        // Re-solve exactly for survivors (improve closure)
        if (survivors.size() == 1) {
            int i = survivors[0];
            double ai = std::max(0.0, g_uT[i].X()*gMET_ref.X() + g_uT[i].Y()*gMET_ref.Y());
            out.alpha[i] = ai;
        } else if (survivors.size() == 2) {
            int i = survivors[0], j = survivors[1];
            auto [ok, ai, aj, resid] = solve_pair_analytic(gMET_ref, g_uT[i], g_uT[j]);
            if (ok) { out.alpha[i] = ai; out.alpha[j] = aj; }
            // else keep existing values (from previous step)
        }
        // rebuild nu_lab with final alphas (and pz policy)
        std::array<TLorentzVector,4> nu_ref;
        for (int i=0;i<4;++i) {
            double pt_n = out.alpha[i];
            if (pt_n <= 0) { nu_ref[i].SetPxPyPzE(0,0,0,0); continue; }
            double ux = g_uT[i].X(), uy = g_uT[i].Y();
            double px = pt_n * ux, py = pt_n * uy;
            double pz = 0.0;
            if (pz_policy == "collinear") {
                double ptL = gLep_ref[i].Pt();
                double pzL = gLep_ref[i].Pz();
                double k = (ptL>1e-12) ? (pt_n / ptL) : 0.0;
                pz = k * pzL;
            } else if (pz_policy == "equal_rapidity") {
                double yL = gLep_ref[i].Rapidity();
                pz = pt_n * std::sinh(yL);
            } else if (pz_policy == "fit") {
                if ((int)sfit_vec.size() == 4) pz = sfit_vec[i] * gLep_ref[i].Pz();
            }
            double E = std::sqrt(px*px + py*py + pz*pz);
            nu_ref[i].SetPxPyPzE(px,py,pz,E);
        }
        // boost back to lab
        TLorentzVector Pvis(0,0,0,0); for (int k=0;k<4;++k) Pvis += gLep_lab[k];
        double betaZ_lab = (std::abs(Pvis.E())>1e-12) ? (-Pvis.Pz()/Pvis.E()) : 0.0;
        for (int i=0;i<4;++i) { out.nu_lab[i] = nu_ref[i]; out.nu_lab[i].Boost(0,0,-betaZ_lab); }
        // recompute masses & residual
        auto masses2 = masses_from_alphas_with_pzpolicy(out.alpha, pz_policy, sfit_vec, /*zero_opposite=*/false, nullptr, nullptr);
        out.MH1 = masses2.first; out.MH2 = masses2.second;
    }

    // Recompute final residual MET in REF
    TVector2 met_fit_after(0,0);
    for (int i=0;i<4;++i) met_fit_after += out.alpha[i] * g_uT[i];
    out.residual = (gMET_ref - met_fit_after).Mod();

    out.ok = true;
    return out;
}
