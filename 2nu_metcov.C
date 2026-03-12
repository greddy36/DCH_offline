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

//========================helpers for matrix operations============
using vec2 = std::array<double,2>;
using mat2 = std::array<std::array<double,2>,2>;

inline double det2(const mat2 &A) {
    return A[0][0]*A[1][1] - A[0][1]*A[1][0];
}
inline mat2 inv2(const mat2 &A, bool &ok) {
    double d = det2(A);
    const double eps = 1e-12;
    ok = std::fabs(d) > eps;
    if (!ok) return mat2{{{0,0},{0,0}}};
    double id = 1.0/d;
    mat2 R;
    R[0][0] =  A[1][1]*id;
    R[0][1] = -A[0][1]*id;
    R[1][0] = -A[1][0]*id;
    R[1][1] =  A[0][0]*id;
    return R;
}
inline vec2 mat2_vec(const mat2 &A, const vec2 &v) {
    return vec2{ A[0][0]*v[0] + A[0][1]*v[1],
                 A[1][0]*v[0] + A[1][1]*v[1] };
}
inline mat2 mat2_mul(const mat2 &A, const mat2 &B) {
    mat2 C{};
    for (int i=0;i<2;++i) for (int j=0;j<2;++j) {
        C[i][j] = A[i][0]*B[0][j] + A[i][1]*B[1][j];
    }
    return C;
}
inline mat2 mat2_transpose(const mat2 &A){
    mat2 B;
    B[0][0]=A[0][0]; B[0][1]=A[1][0];
    B[1][0]=A[0][1]; B[1][1]=A[1][1];
    return B;
}
inline vec2 vec2_add(const vec2 &a, const vec2 &b){ return vec2{a[0]+b[0], a[1]+b[1]}; }
inline vec2 vec2_sub(const vec2 &a, const vec2 &b){ return vec2{a[0]-b[0], a[1]-b[1]}; }
inline vec2 scalar_vec(double s, const vec2 &v){ return vec2{ s*v[0], s*v[1] }; }
inline mat2 outer(const vec2 &a, const vec2 &b){
    mat2 M; M[0][0]=a[0]*b[0]; M[0][1]=a[0]*b[1]; M[1][0]=a[1]*b[0]; M[1][1]=a[1]*b[1]; return M;
}
inline double dot(const vec2 &a, const vec2 &b){ return a[0]*b[0] + a[1]*b[1]; }

// Add small diagonal regularization (if desired) to a matrix:
inline mat2 add_diag(const mat2 &A, double eps) {
    mat2 B = A;
    B[0][0] += eps;
    B[1][1] += eps;
    return B;
}

inline double quad(TVector3 &a, const mat2 &M, TVector3 &b) {
    return a.X()*(M[0][0]*b.X() + M[0][1]*b.Y()) +
           a.Y()*(M[1][0]*b.X() + M[1][1]*b.Y());
}

inline vec2 add(const vec2 &a,const vec2 &b){ return vec2{a[0]+b[0], a[1]+b[1]}; }
inline vec2 subv(const vec2 &a,const vec2 &b){ return vec2{a[0]-b[0], a[1]-b[1]}; }
inline vec2 scalev(double s,const vec2 &v){ return vec2{s*v[0], s*v[1]}; }

// Solve H x = b for 2x2 H using inv2
inline bool solve2(const mat2 &H, const vec2 &b, vec2 &x) {
    bool ok;
    mat2 Hi = inv2(H, ok);
    if (!ok) return false;
    x = mat2_vec(Hi, b);
    return true;
}
//==========================================================================
/*
 Solve for alpha in MET = alpha * L using MET covariance.

 Inputs:
   L         : lepton transverse vector (px, py)
   MET       : measured MET vector
   Sigma_met : 2x2 MET covariance

 Outputs:
   alpha     : best-fit alpha
   sigma2    : variance of alpha
   chi2min   : minimum chi^2

 Returns:
   true on success, false if covariance is singular or L too small
*/
bool SolveOneNeutrinoAlpha(
    TVector3 &L,
    TVector3 &MET,
    const mat2 &Sigma_met,
    double &alpha,
    double &sigma2,
    double &chi2min
) {
    // Check lepton magnitude
    /*double L2 = L.X()+L.X() + L.Y()+L.Y();
    if (L2 < 1e-12) return false;

    // Invert MET covariance
    bool ok;
    mat2 W = inv2(Sigma_met, ok);
    if (!ok) return false;

    // Compute numerator and denominator
    double num = quad(L, W, MET); // L^T W MET
    double den = quad(L, W, L);   // L^T W L

    if (den < 1e-14) return false;

    // Best-fit alpha
    alpha = num / den;

    // Variance
    sigma2 = 1.0 / den;

    // Minimum chi2
    double METW_MET = quad(MET, W, MET);
    chi2min = METW_MET - (num*num)/den;*/

    // Invert MET covariance
    bool ok;
    mat2 W = inv2(Sigma_met, ok);

    // Best-fit alpha
    alpha = MET.Mag();//L.Mag();

    // Variance
    sigma2 = 1.0;
    // Minimum chi2
    chi2min = 0;
    
    return true;
}

/* For simple case when the neutrinos are from opposite DCH
 Returns:
   - alpha_star (size 2)
   - cov_alpha_star (2x2)
   - chi2min (minimized chi2)
   - M2star (profiled M^2)
 Returns true on success, false on failure (matrix singular).
 Notes:
   - m2_ll_A, m2_ll_B are the dilepton mass squared (GeV^2 or whatever units you use).
   - sigmaM_A, sigmaM_B are the uncertainties (σ_M) for the masses (same units as sqrt(m2) or here used as sigma in eq; the formula uses sigma^2 so we square them).
   - No positivity constraint on alpha is enforced here.
*/
bool FitAlphasWithMETCov(
    TVector3 &Lxy1, TVector3 &Lxy2,
    TVector3 &MET,
    const mat2 &Sigma_met,
    double m2_ll_A, double m2_ll_B,
    double alpha_A, double alpha_B,
    vec2 &alpha_star,
	mat2 &cov_alpha_star,
	double &chi2min, 
	double &M2star
) {
	double Delta = 0000.0; // GeV^2 (tune this!)

    // Build U = [k1 k2] as 2x2 (columns are k1,k2)
    mat2 U;
    U[0][0] = Lxy1.X(); U[0][1] = Lxy2.X();
    U[1][0] = Lxy1.Y(); U[1][1] = Lxy2.Y();
	
	vec2 alpha = {{alpha_A, alpha_B}};
	
	vec2 met;
	met[0] = MET.X(); met[1] = MET.Y();
	
    // Invert U
    bool ok;
    mat2 Uinv = inv2(U, ok);
    if (!ok) {
        // nearly collinear k1/k2 -> cannot invert U
        return false;
    }

    // Step 1: alpha_hat = U^{-1} * met
    vec2 alpha_hat = mat2_vec(Uinv, met);

    // Sigma_alpha = Uinv * Sigma_met * (Uinv)^T
    mat2 tmp = mat2_mul(Uinv, Sigma_met);
    mat2 UinvT = mat2_transpose(Uinv);
    mat2 Sigma_alpha = mat2_mul(tmp, UinvT);

    // W = Sigma_alpha^{-1}
    mat2 W = inv2(Sigma_alpha, ok);
    if (!ok) {
        // extremely ill-conditioned Sigma_alpha
        return false;
    }
    
	double sigmaM_A = 0.02*sqrt(m2_ll_A), sigmaM_B = 0.02*sqrt(m2_ll_B);
    // Step 2: mass-constraint width lambda = 1 / (sigmaM_A^2 + sigmaM_B^2)
    double lambda = 1.0 / (sigmaM_A*sigmaM_A + sigmaM_B*sigmaM_B);

    // c vector: [ m2_ll_A, - m2_ll_B ]  (so c^T alpha + d = m2_A*alpha1 - m2_B*alpha2 + d)
    vec2 c = { m2_ll_A, -m2_ll_B };
    double d = m2_ll_A - m2_ll_B;

    // beta = c^T Sigma_alpha c  (scalar)
    // compute Sigma_alpha * c
    vec2 Sigma_alpha_c = mat2_vec(Sigma_alpha, c);
    double beta = dot(c, Sigma_alpha_c);

    // compute scalar s = c^T alpha_hat + d
    double s = dot(c, alpha_hat) + d;

    // denominator denom = 1 + lambda * beta
    double denom = 1.0 + lambda * beta;
    if (std::fabs(denom) < 1e-15) {
        // numerical trouble
        return false;
    }

   /* // Step 3: alpha* = alpha_hat - (lambda * Sigma_alpha * c * s) / denom
    vec2 term = scalar_vec(lambda * s / denom, Sigma_alpha_c); // Sigma_alpha*c scaled
    
    alpha_star = vec2{ alpha_hat[0] - term[0], alpha_hat[1] - term[1] };

    // Sigma_alpha,* = Sigma_alpha - (lambda * Sigma_alpha * c c^T Sigma_alpha) / denom
    // Implement numerator matrix N = lambda * (Sigma_alpha * c) (Sigma_alpha * c)^T
    mat2 numerator = outer(Sigma_alpha_c, Sigma_alpha_c);
    mat2 correction;
    double scale = lambda / denom;
    for (int i=0;i<2;++i) for (int j=0;j<2;++j)
        correction[i][j] = scale * numerator[i][j];
        
    for (int i=0;i<2;++i) for (int j=0;j<2;++j)
        cov_alpha_star[i][j] = Sigma_alpha[i][j] - correction[i][j];

    // Step 4: minimized chi2: chi2min = lambda * s^2 / denom
    chi2min = 0.00001*lambda * s * s / denom;*/
	
	double s_raw = dot(c, alpha_hat) + d;
	double s_eff = 0.0;
	if (std::abs(s_raw) > Delta)
    	s_eff = (s_raw > 0 ? 1.0 : -1.0) * (std::abs(s_raw) - Delta);
	// Step 3: alpha* = alpha_hat - (lambda * Sigma_alpha * c * s) / denom
    vec2 term = scalar_vec(lambda * s_eff / denom, Sigma_alpha_c);
    
    alpha_star = vec2{ alpha_hat[0] - term[0], alpha_hat[1] - term[1] };

    // Sigma_alpha,* = Sigma_alpha - (lambda * Sigma_alpha * c c^T Sigma_alpha) / denom
    // Implement numerator matrix N = lambda * (Sigma_alpha * c) (Sigma_alpha * c)^T
    mat2 numerator = outer(Sigma_alpha_c, Sigma_alpha_c);
    mat2 correction;
    double scale = lambda / denom;
    for (int i=0;i<2;++i) for (int j=0;j<2;++j)
        correction[i][j] = scale * numerator[i][j];
        
    for (int i=0;i<2;++i) for (int j=0;j<2;++j)
        cov_alpha_star[i][j] = Sigma_alpha[i][j] - correction[i][j];

    // Step 4: minimized chi2: chi2min = lambda * s^2 / denom
   chi2min = 0.00001*lambda * s_eff * s_eff / denom;



    // Optional: profiled common mass squared M2* per eq (6)
    // XA = m2_ll_A * (1 + alpha1*)
    // XB = m2_ll_B * (1 + alpha2*)
    
    double XA = m2_ll_A * (1.0 + alpha_star[0]);
    double XB = m2_ll_B * (1.0 + alpha_star[1]);
    double wA = 1.0 / (sigmaM_A*sigmaM_A);
    double wB = 1.0 / (sigmaM_B*sigmaM_B);
    M2star = (XA * wA + XB * wB) / (wA + wB);
	
    return true;
}



/*For the case when newutrinos are from the same DCH
 multiplicative Gauss-Newton solver.

 Inputs:
  k1,k2 : 2D vectors (columns of U)
  met   : measured MET (2D)
  Sigma_met : MET covariance (2x2)
  mvisA  : visible mass for system A (the multiplicative side)
  mvisB  : visible mass for system B (fixed)
  sigmaM_A, sigmaM_B : mass uncertainties (sigma, not variance)

 Params:
  maxIter (default 20), tol for delta norm

 Outputs:
  alpha_star (2), cov_alpha_star (2x2), chi2_mass (value of lambda * f^2/(1+... denom) approx),
  returns true if converged / success, false otherwise.

 Note: this routine does NOT enforce alpha >= 0. If you need non-negativity, enforce after solution (or modify iteration).
*/
bool FitAlphasMultiplicativeGN(
    TVector3 &Lxy1, TVector3 &Lxy2,
    TVector3 &MET,
    const mat2 &Sigma_met,
    double mvisA, double mvisB,
    vec2 &alpha_star,
    mat2 &cov_alpha_star,
    double &chi2_mass,
    vec2 &alpha,
    int maxIter = 20,
    double tol = 1e-6
) {
    // Build U
    mat2 U;
    U[0][0] = Lxy1.X(); U[0][1] = Lxy2.X();
    U[1][0] = Lxy1.Y(); U[1][1] = Lxy2.Y();
    
    vec2 met;
	met[0] = MET.X(); met[1] = MET.Y();
	
    bool ok;
    mat2 Uinv = inv2(U, ok);
    if (!ok) return false; // nearly collinear
    // alpha_hat (linear solution)
    vec2 alpha_hat = mat2_vec(Uinv, met);

    // Sigma_alpha and its inverse W
    mat2 tmp = mat2_mul(Uinv, Sigma_met);
    mat2 UinvT = mat2_transpose(Uinv);
    mat2 Sigma_alpha = mat2_mul(tmp, UinvT);

    mat2 W = inv2(Sigma_alpha, ok);
    if (!ok) return false;
	double sigmaM_A = 0.02*mvisA, sigmaM_B = 0.02*mvisB;
    // lambda weight for mass constraint
    double lambda = 1.0 / (sigmaM_A*sigmaM_A + sigmaM_B*sigmaM_B);

    // Initialize alpha to alpha_hat as a starting guess
    //vec2 alpha = alpha_hat;
    
    // Iterative Gauss-Newton
    for (int iter = 0; iter < maxIter; ++iter) {
        // compute M_A(alpha) = mvisA * sqrt((1+alpha1)*(1+alpha2))
        double onep_a1 = 1.0 + alpha[0];
        double onep_a2 = 1.0 + alpha[1];
        if (onep_a1 <= 0 || onep_a2 <= 0) {
            // invalid region -> cannot take sqrt; abort
            //cout<<"BAD SQRT"<<endl;
            return false;
        }
        double MA = mvisA * std::sqrt(onep_a1 * onep_a2);
        double MB = mvisB; // fixed in this case

        double f = MA - MB; // scalar residual

        // Jacobian J = df/dalpha (1x2)
        // dMA/dalpha1 = (1/2) * mvisA * sqrt((1+alpha2)/(1+alpha1)) = MA / (2*(1+alpha1))
        // similarly for alpha2
        double dMA_da1 = MA / (2.0 * onep_a1);
        double dMA_da2 = MA / (2.0 * onep_a2);
        vec2 J = { dMA_da1, dMA_da2 }; // row vector

        // Build gradient: g = W*(alpha - alpha_hat) + lambda * J^T * f
        vec2 alpha_diff = subv(alpha, alpha_hat);
        vec2 Wad = mat2_vec(W, alpha_diff); // W*(alpha - alpha_hat)
        vec2 JT_f = scalev(f, J);          // J^T * f (componentwise)
        vec2 grad = add(Wad, scalev(lambda, JT_f)); // 2-vector

        // Build approximate Hessian: H = W + lambda * J^T J  (2x2)
        mat2 JTJ = outer(J, J); // 2x2
        mat2 H = mat2_mul(W, mat2{{{1,0},{0,1}}}); // copy W
        for (int a=0;a<2;++a) for (int b=0;b<2;++b)
            H[a][b] += lambda * JTJ[a][b];

        // Solve H * delta = -grad
        vec2 rhs = scalev(-1.0, grad);
        vec2 delta;
        if (!solve2(H, rhs, delta)) {
            // ill-conditioned Hessian
			cout<<"BAD HESSIAN"<<endl;
            return false;
        }

        // update
        alpha = add(alpha, delta);

        // convergence check
        double dn = std::sqrt(delta[0]*delta[0] + delta[1]*delta[1]);
        if (dn < tol) break;
    }

    // final outputs
    alpha_star = alpha;

    // Final covariance approximation = H^{-1}
    // Recompute final J and H to return covariance
    double onep_a1f = 1.0 + alpha_star[0];
    double onep_a2f = 1.0 + alpha_star[1];
    if (onep_a1f <= 0 || onep_a2f <= 0) return false;
    double MAf = mvisA * std::sqrt(onep_a1f * onep_a2f);
    vec2 Jf = { MAf / (2.0 * onep_a1f), MAf / (2.0 * onep_a2f) };
    mat2 JTJf = outer(Jf, Jf);
    mat2 Hfinal = W;
    for (int a=0;a<2;++a) for (int b=0;b<2;++b)
        Hfinal[a][b] += lambda * JTJf[a][b];

    mat2 Hinv = inv2(Hfinal, ok);
    if (!ok) return false;
    cov_alpha_star = Hinv;

    // chi2 contribution from mass term: approx 0.5 * lambda * f^2 ; but for reporting follow same as earlier:
    // We'll compute chi2_mass = 0.5 * lambda * f^2 (or lambda * f^2 / 2)
    double MA_final = MAf;
    double MB_final = mvisB;
    double ffinal = MA_final - MB_final;
    //chi2_mass = 0.5 * lambda * ffinal * ffinal;
	    
    double beta_eff = dot(Jf, mat2_vec(Sigma_alpha, Jf));
    chi2_mass = lambda * ffinal*ffinal / (1 + lambda*beta_eff);
    
    return true;
}


std::tuple<int, double, double, double, double, bool> get_legs_comb(std::string cat, const std::array<TLorentzVector,4> &Lep_lab, TLorentzVector &MET_lab, const mat2 &metcov, bool doPrint=false){//this gives valid lepton legs with neutrinos
	std::cout << std::fixed;
    std::cout << std::setprecision(6);
    
	//Boosting to have Pz_tot(vis) = 0
	double betaZ = 0, sumE = 0; 
	std::array<TLorentzVector,4> Lep_ref; 
	TVector3 MET_ref; TVector3 Lxy[4];
	double alpha[4] = {0,0,0,0}; 
	for (int i=0;i<4;++i) {
		sumE += Lep_lab[i].E(); 
		betaZ += Lep_lab[i].Pz();
	}
	betaZ = betaZ/sumE;
	for (int i=0;i<4;++i) {
		Lep_ref[i] = Lep_lab[i]; 
		//Lep_ref[i].Boost(0,0,-betaZ);
		//print4Vec(Lep_ref[i]);
		MET_ref = MET_lab.Vect(); //no need to boost met
		TVector3 v(Lep_ref[i].Vect().X(), Lep_ref[i].Vect().Y(), 0);
		
		Lxy[i] = v;
	}
	std::vector<int> ileg; //this saves the tau leg indices
	for (int i=0;i<4;++i) {
        if (cat[i]=='t') ileg.push_back(i); 
    }
    double mll_1 = (Lep_ref[0]+Lep_ref[1]).M();
    double mll_2 = (Lep_ref[2]+Lep_ref[3]).M();
    
    double bestChi2 = 1e15; double best_Chi2 = 1e15; double bestchi2 = 1e15; double chee2 = 999999999;
	double chi2min; double chi2_mass;
	double M2star;
	double bestdPhi = 999;
	//for 2 alphas
	float dmH = 99999;//abs(mll_1 - mll_2) ;
	bool isOpp = true;

    for (int i=0;i<4;i++){
    	for (int j=i+1;j<4;j++){
    		
    		bool i_in = std::find(ileg.begin(), ileg.end(), i) != ileg.end();
            bool j_in = std::find(ileg.begin(), ileg.end(), j) != ileg.end();
            //the below if-else is to assign scan only if the leg has a tau
            //if (ileg.size()==1 and !(i_in or j_in)) continue;
			//else if (ileg.size()>1 and !(i_in and j_in)) continue;
    		
    		//below is just initialization. I chose to use the analystic solutions for the initial values. Just a choice, could even be 0.
			double alpha1 = MET_ref.Cross(Lxy[j].Unit())*Lxy[i].Unit().Cross(Lxy[j].Unit())/Lxy[i].Unit().Cross(Lxy[j].Unit()).Mag2();
			double alpha2 = MET_ref.Cross(Lxy[i].Unit())*Lxy[j].Unit().Cross(Lxy[i].Unit())/Lxy[j].Unit().Cross(Lxy[i].Unit()).Mag2();
			alpha1 = alpha1/Lxy[i].Mag(); alpha2 = alpha2/Lxy[j].Mag();
			
			//if (doPrint)cout<<"alpha1: "<<sqrt(1+alpha1)*mll_1<<"\t alpha2: "<<sqrt(1+alpha2)*mll_2<<endl;
			//if (alpha1 <= 0 or alpha2 <= 0) continue;
			
			double mHa =  -99, mHb = -999; 
			/*if ((i==0 and j==2) or (i==0 and j==3) or (i==1 and j==2) or (i==1 and j==3)){

				mHa = sqrt(1+alpha1)*mll_1;
				mHb = sqrt(1+alpha2)*mll_2;
			}
			else if (i==0 and j==1){
				mHa = sqrt((1+alpha1)*(1+alpha2))*mll_1;
			 	mHb = mll_2;
			}
			else if (i==2 and j==3){
				mHa = mll_1;
				mHb = sqrt((1+alpha1)*(1+alpha2))*mll_2;
			}
			
			cout<<"mH1: "<<mHa<<"\t mH2: "<<mHb<<endl;
			if (abs(mHa - mHb) >= dmH) continue;
			dmH = abs(mHa - mHb);
			for(int l=0; l<4; l++) alpha[l]=0;
			alpha[i] = alpha1;
			alpha[j] = alpha2;*/
			
			vec2 alpha_star = {{0,0}};
			mat2 cov_alpha_star = {{{0, 0},{0, 0}}};
			vec2 alpha_init = {{alpha1,alpha2}};	
			if ((i==0 and j==2) or (i==0 and j==3) or (i==1 and j==2) or (i==1 and j==3)){ 
				//continue;
				bool ok1 = FitAlphasWithMETCov(
				Lxy[i], Lxy[j],
				MET_ref,
				metcov,
				(Lep_ref[0]+Lep_ref[1]).M2(), (Lep_ref[2]+Lep_ref[3]).M2(),
				alpha1, alpha2,
				alpha_star,
				cov_alpha_star,
				chi2min,
				M2star
				);if(!ok1) continue;
				//if (doPrint) cout<<i<<j<<"\t chi2: "<<chi2min<<" alpha1: "<<alpha_star[0]<<"\t alpha2: "<<alpha_star[1]<<"\t mH(cov): "<<sqrt(M2star)<<" dPhi: "<<deltaPhi(Lep_ref[i], Lep_ref[j])<<endl;
				if (alpha_star[0] <= 0 or alpha_star[1] <= 0) continue;
				
				if (chi2min > bestChi2) continue;
				bestChi2 = chi2min; bestdPhi = deltaPhi(Lep_ref[i], Lep_ref[j]);
				for(int l=0; l<4; l++) alpha[l]=0;
				alpha[i] = alpha_star[0];
				alpha[j] = alpha_star[1];
				
				mHa = sqrt(1+alpha_star[0])*mll_1;
				mHb = sqrt(1+alpha_star[1])*mll_2;
				//cout<<mHa<<"\t"<<mHb<<endl;
				isOpp = true;
			}
			else if (i==0 and j==1){ //continue;
				bool ok2 = FitAlphasMultiplicativeGN(
				Lxy[i], Lxy[j],
				MET_ref,
				metcov,
				mll_1, mll_2,
				alpha_star,
				cov_alpha_star,
				chi2min,
				alpha_init,
				20,
				1e-6
				);if(!ok2) continue;
				//if (doPrint) cout<<i<<j<<"\t chi2: "<<chi2min<<" alpha1: "<<alpha_star[0]<<"\t alpha2: "<<alpha_star[1]<<"\t dPhi: "<<deltaPhi(Lep_ref[i], Lep_ref[j])<<endl;
				if (alpha_star[0] <= 0 or alpha_star[1] <= 0) continue;
				
				if (chi2min > bestChi2) continue;
				bestChi2 = chi2min;bestdPhi = deltaPhi(Lep_ref[i], Lep_ref[j]);
				for(int l=0; l<4; l++) alpha[l]=0;
				alpha[i] = alpha_star[0];
				alpha[j] = alpha_star[1];
				//cout<<"cov mH: "<<sqrt(M2star)<<endl;
				
				mHa = sqrt((1+alpha_star[0])*(1+alpha_star[1]))*mll_1;
			 	mHb = mll_2;
			 	//cout<<mHa<<"\t"<<mHb<<endl;
			 	isOpp = false;
			}
			else if (i==2 and j==3){//continue;
				bool ok2 = FitAlphasMultiplicativeGN(
				Lxy[i], Lxy[j],
				MET_ref,
				metcov,
				mll_2, mll_1,
				alpha_star,
				cov_alpha_star,
				chi2min,
				alpha_init,
				20,
				1e-6
				);if(!ok2) continue;
				//if (doPrint) cout<<i<<j<<"\t chi2: "<<chi2min<<" alpha1: "<<alpha_star[0]<<"\t alpha2: "<<alpha_star[1]<<"\t dPhi: "<<deltaPhi(Lep_ref[i], Lep_ref[j])<<endl;
				if (alpha_star[0] <= 0 or alpha_star[1] <= 0) continue;
				
				if (chi2min > bestChi2) continue;
				bestChi2 = chi2min;bestdPhi = deltaPhi(Lep_ref[i], Lep_ref[j]);
				for(int l=0; l<4; l++) alpha[l]=0;
				alpha[i] = alpha_star[0];
				alpha[j] = alpha_star[1];
				//cout<<"cov mH: "<<sqrt(M2star)<<endl;
				
				mHa = mll_1;
				mHb = sqrt((1+alpha_star[0])*(1+alpha_star[1]))*mll_2;
				//cout<<mHa<<"\t"<<mHb<<endl;
				isOpp = false;
			}

			//cout<<"mH1: "<<mHa<<"\t mH2: "<<mHb<<"\t M2star: "<<M2star<<endl;
    	}
    }
    
    //BoostLeptonsZ(Lep_ref, betaZ);
    TLorentzVector nu[4]; int nlegs =0;
    for (int i=0;i<4;++i) {//making neutrinos
    	//nu[i].SetPxPyPzE(alpha[i]*Lep_ref[i].Px(), alpha[i]*Lep_ref[i].Py(), alpha[i]*Lep_ref[i].Pz(), alpha[i]*Lep_ref[i].E());
    	nu[i] = alpha[i]*Lep_ref[i]; 
    	if (nu[i].E()>0) nlegs +=1;
    }
    
    double MDCH1 = (nu[0]+nu[1]+Lep_ref[0]+Lep_ref[1]).M();
	double MDCH2 = (nu[2]+nu[3]+Lep_ref[2]+Lep_ref[3]).M();

	if (doPrint){
		for (int i=0;i<4;++i) {cout<<"nu"<<i<<": "; print4Vec(nu[i]);}
		for (int i=0;i<4;++i) {cout<<"Lep"<<i<<": "; print4Vec(Lep_ref[i]);}
		cout<<"MET "<<MET_ref.Mag()<<"\t"<<"Sum (nu pT) "<<(nu[0]+nu[1]+nu[2]+nu[3]).Pt()<<endl;
		cout<<"Mll "<< mll_1 <<"\t"<< mll_2 <<endl;
		cout<<"DCH masses "<< MDCH1 <<"\t"<< MDCH2<<endl;
	}
    //cout<<nlegs<<endl;
    return {nlegs, MDCH1, MDCH2, bestdPhi, bestChi2, isOpp};
}

	
