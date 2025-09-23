// g++ -O2 -std=c++17 `root-config --cflags --libs` met_projection_reco.cc -o met_projection_reco

#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <limits>
#include <utility>
#include <algorithm>

#include "TLorentzVector.h"
#include "TVector2.h"
#include "TMath.h"

struct RecoResult {
    bool   ok = false;
    int    i = -1, j = -1;          // indices of leptons that got neutrinos
    double a_i = 0., a_j = 0.;      // MET components along those leptons (GeV)
    double residual = 0.;           // |MET - a_i u_i - a_j u_j| (GeV)
    int    dch1_L = -1, dch1_R = -1;// chosen pairing for decay chains (indices in 0..3)
    double M1 = 0., M2 = 0.;        // reconstructed parent masses (GeV)
    TLorentzVector nu_i_lab, nu_j_lab;
};

// Solve 2x2 for non-negative least squares on span{u_i, u_j}
// Returns (ok, a_i, a_j, residual)
static std::tuple<bool,double,double,double>
solve_pair_nonneg(const TVector2& MET, const TVector2& ui, const TVector2& uj)
{
    // Gram matrix G = [[ui·ui, ui·uj],[uj·ui, uj·uj]], b = [ui·MET, uj·MET]
    const double uiu = ui.Mod2();
    const double uju = uj.Mod2();
    const double uij = ui.X()*uj.X() + ui.Y()*uj.Y();
    const double bi  = ui.X()*MET.X() + ui.Y()*MET.Y();
    const double bj  = uj.X()*MET.X() + uj.Y()*MET.Y();

    // Guard near-singular
    const double det = uiu*uju - uij*uij;
    if (std::abs(det) < 1e-8) {
        // Nearly collinear; fall back to one-dimensional non-negative projections
        double ai = (uiu>0) ? std::max(0.0, bi/uiu) : 0.0;
        TVector2 r1 = MET - ai*ui;
        double aj = (uju>0) ? std::max(0.0, (uj.X()*r1.X()+uj.Y()*r1.Y())/uju) : 0.0;
        TVector2 r = MET - ai*ui - aj*uj;
        return { (ai>=0 and aj>=0), ai, aj, r.Mod() };
    }

    double ai = ( uju*bi - uij*bj) / det;
    double aj = (-uij*bi + uiu*bj) / det;

    // Enforce non-negativity; if violated, project onto edges
    auto residual_of = [&](double a1, double a2){
        TVector2 r = MET - a1*ui - a2*uj;
        return r.Mod();
    };

    if (ai >= 0.0 and aj >= 0.0) {
        return {true, ai, aj, residual_of(ai,aj)};
    }

    // Edge: aj = 0, solve ai >= 0
    double ai_edge = (uiu>0) ? std::max(0.0, bi/uiu) : 0.0;
    double r_edge1 = residual_of(ai_edge, 0.0);

    // Edge: ai = 0, solve aj >= 0
    double aj_edge = (uju>0) ? std::max(0.0, bj/uju) : 0.0;
    double r_edge2 = residual_of(0.0, aj_edge);

    if (r_edge1 <= r_edge2) return { ai_edge>=0, ai_edge, 0.0, r_edge1 };
    else                    return { aj_edge>=0, 0.0, aj_edge, r_edge2 };
}

// Build a massless, collinear neutrino along lepton 3-vector.
// We know its transverse magnitude must be "a" (the coefficient along lepton dir in the transverse plane).
static TLorentzVector make_collinear_nu(const TLorentzVector& lep, double a /*GeV*/)
{
    const double ptL = lep.Pt();
    if ((ptL <= 1e-9) or (a <= 0)) return TLorentzVector(0,0,0,0);

    // Scale factor so that the neutrino transverse momentum equals 'a'
    const double k = a / ptL;  // p_nu = k * p_lep (3-vector)
    TVector3 pnu = k * lep.Vect();
    const double Enu = pnu.Mag(); // massless
    return TLorentzVector(pnu.X(), pnu.Y(), pnu.Z(), Enu);
}

// Perform the full procedure:
// 1) Longitudinally boost visibles so sum pz(vis)=0
// 2) Project MET onto lepton transverse directions (unit vectors)
// 3) Choose the best lepton pair (non-negative) minimizing residual
// 4) Build collinear neutrinos in that frame, then pick DCH pairing to minimize |M1-M2|
// 5) Boost neutrinos back to lab; compute masses in lab
RecoResult reconstruct(const std::array<TLorentzVector,4>& leptons_lab, const TVector2& MET_lab)
{
    RecoResult out;

    // 1) Build visible sum and compute z-boost to make Pz_vis=0
    TLorentzVector Pvis_lab(0,0,0,0);
    for (auto& L: leptons_lab) Pvis_lab += L;
    const double betaZ = (std::abs(Pvis_lab.E())>1e-9) ? (-Pvis_lab.Pz()/Pvis_lab.E()) : 0.0;

    // Copy leptons and boost to the "reference" frame
    std::array<TLorentzVector,4> L_ref = leptons_lab;
    for (auto& L: L_ref) L.Boost(0,0,betaZ);

    // MET has no z-component; under pure z-boost, transverse MET is unchanged
    TVector2 MET_ref = MET_lab; // good approximation

    // 2) Unit vectors along lepton directions in transverse plane
    std::array<TVector2,4> uT;
    for (int i=0;i<4;++i){
        if (L_ref[i].Pt() > 0) {
            uT[i] = TVector2(L_ref[i].Px()/L_ref[i].Pt(), L_ref[i].Py()/L_ref[i].Pt());
        } else {
            uT[i] = TVector2(0,0);
        }
    }

    // 3) Try all 6 pairs; solve NNLS and pick best residual with positive coefficients
    double bestR = std::numeric_limits<double>::infinity();
    int bestI=-1, bestJ=-1;
    double best_ai=0., best_aj=0.;
    for (int i=0;i<4;++i){
        for (int j=i+1;j<4;++j){
            auto [ok, ai, aj, r] = solve_pair_nonneg(MET_ref, uT[i], uT[j]);
            // Discard if coefficient along a lepton would be (effectively) negative
            if ((!ok) or (ai<1e-6 and aj<1e-6)) continue;
            if (r < bestR){
                bestR = r; bestI = i; bestJ = j; best_ai = ai; best_aj = aj;
            }
        }
    }
    if ((bestI<0) or (bestJ<0)){
        // No valid pair; try the single best projection (still enforce non-negativity)
        int kbest = -1; double akbest=0.; double rbest = std::numeric_limits<double>::infinity();
        for (int k=0;k<4;++k){
            double ak = std::max(0.0, uT[k].X()*MET_ref.X() + uT[k].Y()*MET_ref.Y()); // since u is unit, this is dot
            TVector2 r = MET_ref - ak*uT[k];
            if (ak>1e-6 and r.Mod()<rbest){ rbest = r.Mod(); kbest = k; akbest = ak; }
        }
        if (kbest<0) return out; // give up
        bestI = kbest; bestJ = -1; best_ai = akbest; best_aj = 0.; bestR = rbest;
    }

    // Build neutrinos in reference frame along those leptons
    TLorentzVector nuI_ref = make_collinear_nu(L_ref[bestI], best_ai);
    TLorentzVector nuJ_ref(0,0,0,0);
    if (bestJ>=0) nuJ_ref = make_collinear_nu(L_ref[bestJ], best_aj);

    // 4) Choose decay-chain pairing to make M1 ~ M2
    // All pairings of four leptons into two disjoint pairs:
    // (0-1,2-3), (0-2,1-3), (0-3,1-2)
    struct Pairing { std::pair<int,int> A; std::pair<int,int> B; };
    std::array<Pairing,3> pairings{{ {{0,1},{2,3}}, {{0,2},{1,3}}, {{0,3},{1,2}} }};//WORNG as we already pair the leptons based on charge

    double bestDelta = std::numeric_limits<double>::infinity();
    int bestP = -1;

    // We'll construct taus (lep + possible nu if that lep is bestI/bestJ) in the reference frame,
    // then form parent candidates as sums of the two taus in each chain.
    for (int p=0;p<3;++p){
        auto A = pairings[p].A;
        auto B = pairings[p].B;

        auto buildTau = [&](int idx)->TLorentzVector{
            TLorentzVector tau = L_ref[idx];
            if (idx==bestI) tau += nuI_ref;
            if (bestJ>=0 and idx==bestJ) tau += nuJ_ref;
            return tau;
        };

        TLorentzVector tA1 = buildTau(A.first );
        TLorentzVector tA2 = buildTau(A.second);
        TLorentzVector tB1 = buildTau(B.first );
        TLorentzVector tB2 = buildTau(B.second);

        TLorentzVector parent1 = tA1 + tA2;
        TLorentzVector parent2 = tB1 + tB2;

        double M1 = parent1.M();
        double M2 = parent2.M();
        double d = std::abs(M1 - M2);

        if (d < bestDelta){
            bestDelta = d; bestP = p;
        }
    }

    if (bestP<0) return out;

    // 5) Boost neutrinos back to lab and compute final masses using LAB leptons
    TLorentzVector nuI_lab = nuI_ref; TLorentzVector nuJ_lab = nuJ_ref;
    nuI_lab.Boost(0,0,-betaZ);
    nuJ_lab.Boost(0,0,-betaZ);

    auto P = pairings[bestP];
    auto buildTau_lab = [&](int idx)->TLorentzVector{
        TLorentzVector tau = leptons_lab[idx];
        if (idx==bestI) tau += nuI_lab;
        if (bestJ>=0 and idx==bestJ) tau += nuJ_lab;
        return tau;
    };

    TLorentzVector tA1_lab = buildTau_lab(P.A.first );
    TLorentzVector tA2_lab = buildTau_lab(P.A.second);
    TLorentzVector tB1_lab = buildTau_lab(P.B.first );
    TLorentzVector tB2_lab = buildTau_lab(P.B.second);

    TLorentzVector parent1_lab = tA1_lab + tA2_lab;
    TLorentzVector parent2_lab = tB1_lab + tB2_lab;

    out.ok = true;
    out.i = bestI; out.j = bestJ;
    out.a_i = best_ai; out.a_j = best_aj;
    out.residual = bestR;
    out.dch1_L = P.A.first; out.dch1_R = P.A.second;
    out.M1 = parent1_lab.M(); out.M2 = parent2_lab.M();
    out.nu_i_lab = nuI_lab; out.nu_j_lab = nuJ_lab;
    return out;
}


