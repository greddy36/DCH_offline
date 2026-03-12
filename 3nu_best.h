struct Nu3FitResult {
  bool ok = false;
  double chi2 = 1e99;
  double mHA = 0.0, mHB = 0.0;

  // Neutrinos correspond to idxNu[0], idxNu[1], idxNu[2]
  std::array<TLorentzVector,3> nu;
  // (x_i, y_i) parameters in the lepton basis
  std::array<double,6> params{};
};


inline bool invert2x2(const mat2& S, mat2& Sinv) {
  double det = S[0][0]*S[1][1] - S[0][1]*S[1][0];
  if (std::abs(det) < 1e-18) return false;
  double id = 1.0/det;
  Sinv = {{
    {  S[1][1]*id, -S[0][1]*id },
    { -S[1][0]*id,  S[0][0]*id }
  }};
  return true;
}

inline vec2 mul(const mat2& A, const vec2& v) {
  return { A[0][0]*v[0] + A[0][1]*v[1],
           A[1][0]*v[0] + A[1][1]*v[1] };
}
inline double dot2(const vec2& a, const vec2& b) { return a[0]*b[0] + a[1]*b[1]; }

inline void lepton_basis_T(const TLorentzVector& l, TVector2& u, TVector2& uperp) {
  TVector2 pT(l.Px(), l.Py());
  double pt = pT.Mod();
  if (pt < 1e-12) { u.Set(1,0); uperp.Set(0,1); return; }
  u = (1.0/pt) * pT;
  uperp.Set(-u.Y(), u.X()); // rotate +90°
}

Nu3FitResult Fit3Neutrinos_GlobalLocal(
    const std::array<TLorentzVector,4>& lep,
    const TVector2& met,              // MET x,y
    const mat2& metCov,               // 2x2 covariance
    const std::array<int,3>& idxNu,   // which 3 leptons carry neutrinos
    const std::array<int,2>& pairA,   // two lepton indices for Higgs A (visible)
    const std::array<int,2>& pairB,   // two lepton indices for Higgs B (visible)
    double sigma_perp = 10.0,         // GeV scale for non-collinearity (y_i)
    double sigma_x    = 0.7,          // penalty scale for negative x_i (dimensionless-ish)
    double sigma_m    = 20.0,         // GeV for mass closeness
    int maxIter       = 60
) {
  Nu3FitResult out;

  // Invert MET covariance
  mat2 Wmet{};
  if (!invert2x2(metCov, Wmet)) return out;

  // Precompute bases for the 3 neutrino-carrying leptons
  std::array<TVector2,3> u{}, uperp{};
  for (int i=0;i<3;i++) lepton_basis_T(lep[idxNu[i]], u[i], uperp[i]);

  auto build_nu = [&](const std::array<double,6>& p) {
    std::array<TLorentzVector,3> nu;
    for (int i=0;i<3;i++) {
      double x = p[2*i], y = p[2*i+1];
      TVector2 vT = x*u[i] + y*uperp[i];
      double px = vT.X(), py = vT.Y();
      double pz = 0.0;                 // choose pz model here (keep 0 for stability)
      double E  = std::sqrt(px*px+py*py+pz*pz);
      nu[i].SetPxPyPzE(px,py,pz,E);
    }
    return nu;
  };

  auto chi2 = [&](const std::array<double,6>& p, double* mHA=nullptr, double* mHB=nullptr) -> double {
    auto nu = build_nu(p);

    // MET term
    TVector2 sumNu(0,0);
    for (int i=0;i<3;i++) sumNu += TVector2(nu[i].Px(), nu[i].Py());
    vec2 r = { met.X() - sumNu.X(), met.Y() - sumNu.Y() };
    double chi2_met = dot2(r, mul(Wmet, r));

    // collinearity term: y_i
    double chi2_col = 0.0;
    for (int i=0;i<3;i++) {
      double y = p[2*i+1];
      chi2_col += (y/sigma_perp)*(y/sigma_perp);
    }

    // positivity soft penalty on x_i < 0
    double chi2_pos = 0.0;
    for (int i=0;i<3;i++) {
      double x = p[2*i];
      if (x < 0) chi2_pos += (x/sigma_x)*(x/sigma_x);
    }

    // build Higgs candidates by attaching neutrino to its lepton (same index)
    auto nu_of_lep = [&](int lepIdx)->TLorentzVector {
      for (int i=0;i<3;i++) if (idxNu[i]==lepIdx) return nu[i];
      TLorentzVector z; z.SetPxPyPzE(0,0,0,0); return z; // no neutrino on that lepton
    };

    TLorentzVector HA = lep[pairA[0]] + lep[pairA[1]] + nu_of_lep(pairA[0]) + nu_of_lep(pairA[1]);
    TLorentzVector HB = lep[pairB[0]] + lep[pairB[1]] + nu_of_lep(pairB[0]) + nu_of_lep(pairB[1]);

    double mA = std::sqrt(std::max(0.0, HA.M2()));
    double mB = std::sqrt(std::max(0.0, HB.M2()));
    if (mHA) *mHA = mA;
    if (mHB) *mHB = mB;

    double chi2_m = ((mA-mB)/sigma_m)*((mA-mB)/sigma_m);

    return chi2_met + chi2_col + chi2_pos + chi2_m;
  };

  // --- Initial guess:
  // Put MET along lepton directions proportionally (purely collinear, y=0).
  std::array<double,6> p{};
  {
    // Solve least squares for x_i with y_i=0: minimize || MET - sum x_i u_i ||^2
    // Simple heuristic: distribute by projection onto u_i with non-negative clamp.
    TVector2 M = met;
    for (int i=0;i<3;i++) {
      double proj = M * u[i];          // dot
      p[2*i]   = std::max(0.0, proj);  // start non-negative
      p[2*i+1] = 0.0;
    }
    // rescale to match MET magnitude roughly
    TVector2 sum(0,0);
    for (int i=0;i<3;i++) sum += p[2*i]*u[i];
    double s = (sum.Mod() > 1e-9 ? M.Mod()/sum.Mod() : 1.0);
    for (int i=0;i<3;i++) p[2*i] *= s;
  }

  // --- Levenberg–Marquardt-ish loop (numerical gradient + backtracking)
  double mu = 1e-2;      // damping
  double f0 = chi2(p);
  for (int it=0; it<maxIter; ++it) {
    // numerical gradient
    std::array<double,6> g{};
    const double h = 1e-3; // step for finite diff in x,y units (GeV-ish)
    for (int k=0;k<6;k++) {
      auto pp = p; pp[k] += h;
      auto pm = p; pm[k] -= h;
      g[k] = (chi2(pp) - chi2(pm)) / (2*h);
    }

    // simple diagonal preconditioner / LM step: dp = - g / (diag + mu)
    // (Full Hessian is possible but heavy; this is robust and usually enough.)
    std::array<double,6> dp{};
    for (int k=0;k<6;k++) {
      double denom = (std::abs(g[k]) + mu);  // stabilizer
      dp[k] = - g[k] / denom;
    }

    // backtracking line search
    double t = 1.0;
    bool improved = false;
    std::array<double,6> p_try = p;
    for (int ls=0; ls<20; ++ls) {
      for (int k=0;k<6;k++) p_try[k] = p[k] + t*dp[k];
      double f1 = chi2(p_try);
      if (f1 < f0) {
        p = p_try;
        f0 = f1;
        improved = true;
        break;
      }
      t *= 0.5;
    }

    if (!improved) {
      mu *= 10.0;                 // increase damping
      if (mu > 1e6) break;
    } else {
      mu = std::max(1e-6, mu*0.7); // relax damping
    }

    // convergence
    double gnorm = 0.0;
    for (double v : g) gnorm += v*v;
    gnorm = std::sqrt(gnorm);
    if (gnorm < 1e-3) break;
  }

  // final
  double mA=0,mB=0;
  double finalChi2 = chi2(p, &mA, &mB);

  out.ok = std::isfinite(finalChi2);
  out.chi2 = finalChi2;
  out.mHA = mA;
  out.mHB = mB;
  out.params = p;
  out.nu = build_nu(p);

  return out;
}
