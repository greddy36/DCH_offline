using vec3 = std::array<double,3>;
using mat3 = std::array<std::array<double,3>,3>;

void BoostLeptonsZ(
    std::array<TLorentzVector, 4>& leptons,
    double betaZ
) {
    TVector3 boost(0,0,-betaZ);
    for (auto& l : leptons)
        l.Boost(boost);
}
vec2 operator*(double, const vec2&);
vec2 operator+(const vec2&, const vec2&);
vec2 operator-(const vec2&, const vec2&);
vec2 operator-(const vec2&);

std::tuple<double,double,double> FitAlphasNuPzZero(
    const std::array<TLorentzVector,4>& lep_in,
    const TVector3& met,
    const mat2& metcov,
    double m2_ll_A, double m2_ll_B,
    vec3& alpha,   // IN: seed, OUT: solution
    double& chi2min,
    int idx1, int idx2, int idx3,
    double lambda = 0.00001,
    int maxIter = 5
) {
    constexpr double eps = 1e-5;
    constexpr double damping = 0.3;
    
    // ---- MET covariance inverse
    mat2 SigmaMET = metcov;
    bool ok;
    mat2 Wmet = inv2(SigmaMET, ok);
    if (!ok)
        return {std::sqrt(m2_ll_A), std::sqrt(m2_ll_B), 0.0};

    // ---- Newton loop
    for (int iter = 0; iter < maxIter; ++iter) {

		//=====================INIT alphas======
		int idx4 = 0+1+2+3 - (idx1 + idx2 + idx3);//leftover idx
		TVector3 Lxy[4];
		for (int i=0;i<4;++i) {
			TVector3 v(lep_in[i].Vect().X(), lep_in[i].Vect().Y(), 0);
			Lxy[i] = v;
		}
					
		double A1 = Lxy[idx1].Dot(Lxy[idx3]);
		double A2 = Lxy[idx2].Dot(Lxy[idx3]);
		double K = Lxy[idx3].Dot(Lxy[idx3]);
		double C1 = (Lxy[idx1].Cross(Lxy[idx3])).Mag();
		double C2 = (Lxy[idx2].Cross(Lxy[idx3])).Mag();
		double N3 = (met.Cross(Lxy[idx3])).Mag();
		double S3 = met.Dot(Lxy[idx3]);
		
		double r = m2_ll_A/m2_ll_B;
		double A = C1*K*r;
		double B = A2*C1-C2*A1-K*N3*r;
		double C = -A2*N3+C2*(K*(1-r)+S3);
				
		alpha[0] = (-B+sqrt(B*B-4*A*C))*0.5/A;
		alpha[1] = (N3-alpha[0]*C1)/C2;
		alpha[2] = r*(1+alpha[0])*(1+alpha[1])-1;
		//====================================================

        // ---- compute ν-Pz boost
        double Pz = 0.0, Enu = 0.0;
        for (int i : {idx1, idx2, idx3}) {
            Pz  += alpha[i] * lep_in[i].Pz();
            Enu += alpha[i] * lep_in[i].E();
        }

        double betaZ = (Enu > 1e-6 ? Pz/Enu : 0.0);
        //double boostval = (lep_in[0]+lep_in[1]+lep_in[2]+lep_in[3]).Pz()/(lep_in[0]+lep_in[1]+lep_in[2]+lep_in[3]).E();
        double betaZ = (Enu > 1e-6 ? Pz/Enu : boostval);
		cout<<"BOOOOOOOOOOOST: "<<betaZ<<endl;
        // ---- boost leptons
        std::array<TLorentzVector,4> lep = lep_in;
        TVector3 boost(0,0,-betaZ);
        for (auto& l : lep)
            l.Boost(boost);

        // ---- predicted MET
        vec2 met_pred = {0.0, 0.0};
        for (int i : {idx1, idx2, idx3}) {
            met_pred[0] += alpha[i] * lep[i].Px();
            met_pred[1] += alpha[i] * lep[i].Py();
        }

        vec2 met_obs = {met.X(), met.Y()};
        vec2 dmet = {met_pred[0]-met_obs[0], met_pred[1]-met_obs[1]};
        double chi2_met = dot(dmet, mat2_vec(Wmet, dmet));

        // ---- masses
        double m2HA = m2_ll_A * (1+alpha[0])*(1+alpha[1]);
        double m2HB = m2_ll_B * (1+alpha[2]);

        double Delta = m2HA - m2HB;
        double chi2_mass = lambda * Delta * Delta;

        double chi2 = chi2_met + chi2_mass;

        // ---- numerical gradient
        vec3 grad = {0,0,0};
        for (int k = 0; k < 3; ++k) {
            vec3 a_eps = alpha;
            a_eps[k] += eps;

            double Pz_e = 0.0, Enu_e = 0.0;
            for (int i : {idx1, idx2, idx3}) {
                Pz_e  += a_eps[i] * lep_in[i].Pz();
                Enu_e += a_eps[i] * lep_in[i].E();
            }

            double betaZ_e = (Enu_e > 1e-6 ? Pz_e / Enu_e : 0.0);

            std::array<TLorentzVector,4> lep_e = lep_in;
            TVector3 boost_e(0,0,-betaZ_e);
            for (auto& l : lep_e)
                l.Boost(boost_e);

            vec2 met_p = {0,0};
            for (int i : {idx1, idx2, idx3}) {
                met_p[0] += a_eps[i] * lep_e[i].Px();
                met_p[1] += a_eps[i] * lep_e[i].Py();
            }

            vec2 dmet_e = {met_p[0]-met_obs[0], met_p[1]-met_obs[1]};
            double chi2_met_e = dot(dmet_e, mat2_vec(Wmet, dmet_e));

            double m2HA_e = m2_ll_A*(1+a_eps[0])*(1+a_eps[1]);
            double m2HB_e = m2_ll_B*(1+a_eps[2]);
            double chi2_e = chi2_met_e + lambda*(m2HA_e-m2HB_e)*(m2HA_e-m2HB_e);

            grad[k] = (chi2_e - chi2) / eps;
        }

        // ---- gradient step
        for (int k=0;k<3;k++)
            alpha[k] -= damping * grad[k];

        // ---- soft positivity
        for (int k=0;k<3;k++)
            if (alpha[k] < 0) alpha[k] *= 0.5;

        if (grad[0]*grad[0]+grad[1]*grad[1]+grad[2]*grad[2] < 1e-4) {
            chi2min = chi2;
            double mH1 = std::sqrt(std::max(0.0, m2HA));
            double mH2 = std::sqrt(std::max(0.0, m2HB));
            return {mH1, mH2, betaZ};
        }
    }

    // ---- fallback
    chi2min = 1e9;
    return {std::sqrt(m2_ll_A), std::sqrt(m2_ll_B), 0.0};
}


std::tuple<double,double,double> FitAlphas_ThreeNu_METCov(
    const std::array<TLorentzVector,4>& lep,
    const TVector3& met,
    const mat2& SigmaMET,
    vec3& alpha,          // OUT: alpha1,alpha2,alpha3
    double& chi2min,
    int idx1, int idx2, int idx3,
    int maxIter = 10
) {
	int idx4 = 0+1+2+3 - (idx1 + idx2 + idx3);//leftover idx
	// --- dilepton masses
    double m2_12 = (lep[idx1]+lep[idx2]).M2();
    double m2_34 = (lep[idx3]+lep[idx4]).M2();
    if (m2_12<=0 || m2_34<=0) return {sqrt(m2_12), sqrt(m2_34), 0};

    double r = m2_12 / m2_34;
    
	TVector3 Lxy[4];
	for (int i=0;i<4;++i) {
		TVector3 v(lep[i].Vect().X(), lep[i].Vect().Y(), 0);
		Lxy[i] = v;
	}
		
	// Build U = [k1 k2] as 2x2 (columns are k1,k2)
    mat2 U;
    U[0][0] = Lxy[idx1].X(); U[0][1] = Lxy[idx2].X();
    U[1][0] = Lxy[idx1].Y(); U[1][1] = Lxy[idx2].Y();
	
	// Invert U
    bool ok;
    mat2 Uinv = inv2(U, ok);
    if (!ok) {
        // nearly collinear k1/k2 -> cannot invert U
        return {sqrt(m2_12), sqrt(m2_34), 0};
    }
    // Sigma_alpha = Uinv * SigmaMET * (Uinv)^T
    mat2 tmp = mat2_mul(Uinv, SigmaMET);
    mat2 UinvT = mat2_transpose(Uinv);
    mat2 Sigma_alpha = mat2_mul(tmp, UinvT);
    
    // W = Sigma_alpha^{-1}
    mat2 W = inv2(Sigma_alpha, ok);
    if (!ok) {
        // extremely ill-conditioned Sigma_alpha
        return {sqrt(m2_12), sqrt(m2_34), 0};
    }
    
    // --- transverse lepton vectors
    vec2 k1{lep[idx1].Px(), lep[idx1].Py()};
    vec2 k2{lep[idx2].Px(), lep[idx2].Py()};
    vec2 k3{lep[idx3].Px(), lep[idx3].Py()};
    vec2 metT{met.X(), met.Y()};

    /*// --- invert MET covariance
    double det =
        SigmaMET[0][0]*SigmaMET[1][1]
      - SigmaMET[0][1]*SigmaMET[1][0];
    if (std::abs(det)<1e-12) return {sqrt(m2_12), sqrt(m2_34), 0};

    mat2 W {{
        { SigmaMET[1][1]/det, -SigmaMET[0][1]/det },
        { -SigmaMET[1][0]/det, SigmaMET[0][0]/det }
    }};*/

    // --- initial guess (MET-only, ignoring k3)
    double D = k1[0]*k2[1]-k1[1]*k2[0];
    if (std::abs(D)<1e-6) return {sqrt(m2_12), sqrt(m2_34), 0};
		//CRAPPPPPPPPPP NEEDS FIXING. WORNG METHOD
    alpha[0] = ( metT[0]*k2[1]-metT[1]*k2[0] )/D;
    alpha[1] = ( k1[0]*metT[1]-k1[1]*metT[0] )/D;

    double a1 = alpha[0]; 
    double a2 = alpha[1];
    double a3 = r*(1+a1)*(1+a2)-1;
    // --- Newton minimization
    for (int it=0; it<maxIter; ++it) {
		cout<<"alpha:" <<a1<<"\t"<<a2<<"\t"<<a3<<endl;
        vec2 pred =
            a1*k1 + a2*k2 + a3*k3;

        vec2 R = metT - pred;

        // Jacobian J_ij = ∂R_i / ∂α_j
        vec2 dR_da1 = -k1 - r*(1+a2)*k3;
        vec2 dR_da2 = -k2 - r*(1+a1)*k3;

        // Gradient g = 2 Jᵀ W R
        vec2 g;
        g[0] = 2*( dot(dR_da1, {W[0][0]*R[0]+W[0][1]*R[1],
                                W[1][0]*R[0]+W[1][1]*R[1]}) );
        g[1] = 2*( dot(dR_da2, {W[0][0]*R[0]+W[0][1]*R[1],
                                W[1][0]*R[0]+W[1][1]*R[1]}) );

        // Hessian H = 2 Jᵀ W J (Gauss–Newton)
        mat2 H{};
        vec2 Wd1{
            W[0][0]*dR_da1[0]+W[0][1]*dR_da1[1],
            W[1][0]*dR_da1[0]+W[1][1]*dR_da1[1]
        };
        vec2 Wd2{
            W[0][0]*dR_da2[0]+W[0][1]*dR_da2[1],
            W[1][0]*dR_da2[0]+W[1][1]*dR_da2[1]
        };

        H[0][0] = 2*dot(dR_da1, Wd1);
        H[0][1] = 2*dot(dR_da1, Wd2);
        H[1][0] = 2*dot(dR_da2, Wd1);
        H[1][1] = 2*dot(dR_da2, Wd2);

        double detH = H[0][0]*H[1][1]-H[0][1]*H[1][0];
        if (std::abs(detH)<1e-12) break;

        mat2 Hinv {{
            { H[1][1]/detH, -H[0][1]/detH },
            { -H[1][0]/detH, H[0][0]/detH }
        }};
		double step1 = Hinv[0][0]*g[0] + Hinv[0][1]*g[1];
		double step2 = Hinv[1][0]*g[0] + Hinv[1][1]*g[1];
		
        double tmp_a1 = a1 - 0.3*step1;//0.3 just randomly slected
        double tmp_a2 = a2 - 0.3*step2;
        double tmp_a3 = r*(1+tmp_a1)*(1+tmp_a2) - 1;
        if (tmp_a1<0 || tmp_a2<0 || tmp_a3<0) continue;
        a1 = tmp_a1; a2 = tmp_a2; a3 = tmp_a3;
    }

	cout<<"alpha:" <<a1<<"\t"<<a2<<"\t"<<a3<<endl;
    if (a1<0 || a2<0 || a3<0) return {sqrt(m2_12), sqrt(m2_34), 0};
	alpha[0] = a1; 
	alpha[1] = a2;
	alpha[2] = a3;
    // final chi2
    vec2 finalR =
        metT - ( alpha[0]*k1 + alpha[1]*k2 + alpha[2]*k3 );

    chi2min =
        dot(finalR,{W[0][0]*finalR[0]+W[0][1]*finalR[1],
                    W[1][0]*finalR[0]+W[1][1]*finalR[1]});

    return {sqrt((1+alpha[0])*(1+alpha[1])*m2_12), sqrt((1+alpha[2])*m2_34), 0};;
}

