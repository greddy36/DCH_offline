// fixed_pairs_met_fit.cc
#include <iostream>
#include <array>
#include <cmath>
#include <limits>
#include <algorithm>

#include "TLorentzVector.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TMinuit.h"

// ---------------- Result struct ----------------
struct RecoResult {
    bool ok = false;
    double a[4] = {0,0,0,0};   // MET components (GeV) along lep 1..4 in ref frame
    double residual = 0.0;     // |MET - sum a_i u_i| (GeV)
    double MH1 = 0.0, MH2 = 0.0; // reconstructed Higgs masses (lab)
    TLorentzVector nu_lab[4];  // neutrinos in lab
};

// --------------- Globals for Minuit FCN ---------------
static std::array<TLorentzVector,4> gLep_ref, gLep_lab;
static TVector2 gMET_ref, gMET_lab;
static double g_betaZ = 0.0;

// unit transverse directions in ref frame
static TVector2 g_uT[4];

// penalties (tunable)
static double L_MET = 1.0;         // MET-closure penalty weight
static double L_equal = 50.0;      // equal-mass penalty weight
static double L_minSol = 1e-4;     // tiny regularization on alphas

// Helper: make massless collinear nu given lepton and desired transverse magnitude a (in same frame)
static TLorentzVector make_collinear_nu(const TLorentzVector& lep, double a_geV) {
    const double pt = lep.Pt();
    if (pt <= 1e-12 || a_geV <= 0) return TLorentzVector(0,0,0,0);
    const double k = a_geV / pt;         // scale 3-momentum
    TVector3 p = k * lep.Vect();
    return TLorentzVector(p.X(), p.Y(), p.Z(), p.Mag()); // massless
}

// Build MH1 (l1,l2 + nus1,2) and MH2 (l3,l4 + nus3,4) in LAB
static std::pair<double,double> masses_from_alphas_lab(const double a[4]) {
    // Build neutrinos in REF first
    TLorentzVector nu_ref[4];
    for (int i=0;i<4;++i) nu_ref[i] = make_collinear_nu(gLep_ref[i], a[i]);
    // Boost back to LAB
    TLorentzVector nu_lab[4];
    for (int i=0;i<4;++i){ nu_lab[i] = nu_ref[i]; nu_lab[i].Boost(0,0,-g_betaZ); }

    // Fixed pairs: (0,1) = H1, (2,3) = H2
    TLorentzVector H1 = gLep_lab[0] + gLep_lab[1] + nu_lab[0] + nu_lab[1];
    TLorentzVector H2 = gLep_lab[2] + gLep_lab[3] + nu_lab[2] + nu_lab[3];
    return {H1.M(), H2.M()};
}

// Minuit FCN: params x[0..3] where alpha_i = x_i^2 to enforce alpha_i >= 0
void minfn(int &npar, double*, double &f, double *x, int) {
    double a[4];
    for (int i=0;i<4;++i) a[i] = x[i]*x[i];

    // MET closure in REF
    TVector2 met_fit(0,0);
    for (int i=0;i<4;++i) met_fit += a[i] * g_uT[i];
    TVector2 r = gMET_ref - met_fit;
    const double term_met = r.Mod2(); // GeV^2

    // Higgs mass equality penalty in LAB
    auto [MH1, MH2] = masses_from_alphas_lab(a);
    const double term_equal = (MH1 - MH2)*(MH1 - MH2);

    // Minimal solution bias (pick smaller alphas among continuum)
    double term_reg = 0.0;
    for (int i=0;i<4;++i) term_reg += a[i]*a[i];

    f = L_MET*term_met + L_equal*term_equal + L_minSol*term_reg;
}

// Main reconstruction function
RecoResult reconstruct(const std::array<TLorentzVector,4>& leptons_lab,
                                   const TVector2& MET_lab,
                                   double lambda_MET = 1.0,
                                   double lambda_equal = 50.0,
                                   double lambda_minSol = 1e-4)
{
    RecoResult out;
    gLep_lab = leptons_lab;
    gMET_lab = MET_lab;

    // Compute z-boost to make Pz_vis = 0 (REF frame)
    TLorentzVector Pvis(0,0,0,0);
    for (auto &L : gLep_lab) Pvis += L;
    g_betaZ = (std::abs(Pvis.E())>1e-12) ? (-Pvis.Pz()/Pvis.E()) : 0.0;

    // Build REF leptons (boost by +betaZ) and REF MET (unchanged under z-boost)
    gLep_ref = gLep_lab;
    for (auto &L : gLep_ref) L.Boost(0,0,g_betaZ);
    gMET_ref = gMET_lab;

    // Precompute unit transverse directions in REF
    for (int i=0;i<4;++i) {
        const double pt = gLep_ref[i].Pt();
        if (pt > 1e-12) g_uT[i] = TVector2(gLep_ref[i].Px()/pt, gLep_ref[i].Py()/pt);
        else            g_uT[i] = TVector2(0,0);
    }

    // Set penalties
    L_MET = lambda_MET;
    L_equal = lambda_equal;
    L_minSol = lambda_minSol;

    // Minimize
    TMinuit minuit(4);
    minuit.SetFCN(minfn);
    minuit.SetPrintLevel(-1);

    // Initial guesses: split MET equally onto each pair direction
    double start[4] = { std::sqrt(std::max(0.0, gMET_ref.Mod()/4.0)),
                        std::sqrt(std::max(0.0, gMET_ref.Mod()/4.0)),
                        std::sqrt(std::max(0.0, gMET_ref.Mod()/4.0)),
                        std::sqrt(std::max(0.0, gMET_ref.Mod()/4.0)) };
    double step[4]  = { 0.2, 0.2, 0.2, 0.2 };

    for (int i=0;i<4;++i)
        minuit.DefineParameter(i, Form("x%d",i), start[i], step[i], 0, 0);

    int ierr=0;
    minuit.Migrad();

    // Retrieve solution
    double x[4], ex;
    for (int i=0;i<4;++i) { minuit.GetParameter(i, x[i], ex); out.a[i] = x[i]*x[i]; }

    // Compute residual and masses
    TVector2 fit(0,0);
    for (int i=0;i<4;++i) fit += out.a[i] * g_uT[i];
    out.residual = (gMET_ref - fit).Mod();

    auto [MH1, MH2] = masses_from_alphas_lab(out.a);
    out.MH1 = MH1; out.MH2 = MH2;

    // Build and store neutrinos in LAB for output
    TLorentzVector nu_ref[4], nu_lab[4];
    for (int i=0;i<4;++i) nu_ref[i] = make_collinear_nu(gLep_ref[i], out.a[i]);
    for (int i=0;i<4;++i) { nu_lab[i] = nu_ref[i]; nu_lab[i].Boost(0,0,-g_betaZ); out.nu_lab[i] = nu_lab[i]; }

    // Basic sanity: positive alphas and reasonable residual
    out.ok = true;
    return out;
}
