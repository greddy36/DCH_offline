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

// Solve H x = b for 2x2 H using inv2
inline bool solve2(const mat2 &H, const vec2 &b, vec2 &x) {
    bool ok;
    mat2 Hi = inv2(H, ok);
    if (!ok) return false;
    x = mat2_vec(Hi, b);
    return true;
}
//==========================================================================
vec2 Pxy(TLorentzVector &V){
	return vec2{V.Px(), V.Py()};
}

double vec2_vec(const vec2 &v1, const vec2 &v2){//v1^T.v2
	return v1[0]*v2[0]+v1[1]*v2[1];
}


std::tuple<double, double, double> category3(double &R, TLorentzVector &P1, TLorentzVector &P2, TLorentzVector &MET, const mat2 &metcov, double mll1, double mll2){
	vec2 kTp = Pxy(P1);
	vec2 kTm = Pxy(P2);
	vec2 met = Pxy(MET);
	vec2 q = vec2_add(kTp, scalar_vec(R,kTm));
	vec2 b = vec2_add(met, scalar_vec(1-R,kTm));
	double A = vec2_vec(q, mat2_vec(metcov, q));
	double alpha1_hat = vec2_vec(q, mat2_vec(metcov, b))/A;
	double alpha1_fit = 0;
	if (A > 0) {
		alpha1_fit = std::max(alpha1_hat, std::max(0.0, 1/R-1));
		cout<<alpha1_fit<<endl;
	}
	double alpha2_fit = R*(1+alpha1_fit)-1;
	
	double mH1 = mll1*sqrt(1+alpha1_fit);
	double mH2 = mll2*sqrt(1+alpha2_fit);
	
	vec2 g = vec2_sub(b, scalar_vec(alpha1_fit, q));
	double chi2min = vec2_vec(g, mat2_vec(metcov, g));
	return {mH1, mH2, chi2min};
}

std::tuple<double, double> getDCHmass( std::array<TLorentzVector,4> &Lep_lab, TLorentzVector &MET_lab, const mat2 &metcov){

	double mll1 = (Lep_lab[0]+Lep_lab[1]).M();
	double mll2 = (Lep_lab[2]+Lep_lab[3]).M();
	double dMvis = abs(mll1-mll2);
	double dM = 0.1*mll1;////the Brite Wigner width is 10% of signal mass. Checked for mll1 shapes.
	double R = 0;
	cout<<endl;
	cout<<"mll1: "<<mll1<<"\t"<<"mll2: "<<mll2<<endl;
	
	double mass1, mass2, chi2min = 1e10;
	if (dMvis < dM and MET_lab.Pt() < 50 ) { 
		cout<<"best mH: "<<(mll1+mll2)/2 <<endl; 
		mass1 = mll1;//(mll1+mll2)/2;
		mass2 = mass1;
	}
	else {
		double min1 = 999;
		double min2 = 999;
		int idx1 = -9, idx2 = -9;
		for (int i=0;i<4;i++) {
			double dPhi1 = deltaPhi(MET_lab, Lep_lab[i]);
		    if (dPhi1 < min1) {
		        min2 = min1; idx2 = idx1;
		        min1 = dPhi1; idx1 = i;
		    } 
		    else if (dPhi1 < min2){
		    	min2 = dPhi1; idx2 = i;
		    }
		}

		TVector3 METxy = MET_lab.Vect(); 
		for (int i=0;i<4;i++){
		for (int j=i+1;j<4;j++){
			double dPhi1 = deltaPhi(MET_lab, Lep_lab[i]);
			double dPhi2 = deltaPhi(MET_lab, Lep_lab[j]);
			if (idx1 != i and idx1 != j ) continue; 
			if (idx2 != i and idx2 != j ) continue; 	
				 
			
			TVector3 Lxy1 = Lep_lab[i].Vect();	
			TVector3 Lxy2 = Lep_lab[j].Vect(); 	
			
			double alpha1 = METxy.Cross(Lxy2)*Lxy1.Cross(Lxy2) / Lxy1.Cross(Lxy2).Mag2();
			double alpha2 = -METxy.Cross(Lxy1)*Lxy1.Cross(Lxy2) / Lxy1.Cross(Lxy2).Mag2();		
			//if (alpha1 < 0 or alpha2 < 0) continue;
			//surprisingly the below method is working well for 1 neutrino case. For 2 nu, the met Cov method is still supreme.
			if ((i==0 and j==1) or (i==2 and j==3)) {//neutrinos come from SS pair (this means one higgs is already better)
				mass1 = max(mll1, mll2); mass2 = mass1;
				cout<<"MH1: "<<mass1<<"\t"<<"MH2: "<<mass2<<"\t"<<i<<j<<"\t"<<dPhi1<<"\t"<<dPhi2<<endl;
			}
    		else if ((i==0 and j==2) or (i==0 and j==3) or (i==1 and j==2) or (i==1 and j==3)){//neutrinos come from OS pair
    			R = mll1*mll1/(mll2*mll2);
    			auto [m1, m2, chi] = category3(R, Lep_lab[i], Lep_lab[j], MET_lab, metcov, mll1,mll2);	
    			cout<<"MH1: "<<m1<<"\t"<<"MH2: "<<m2<<"\t"<<"chi2: "<<chi<<"\t"<<i<<j<<"\t"<<dPhi1<<"\t"<<dPhi2<<endl;
    			if (chi < chi2min){
    				chi2min=chi;
    				mass1 = m1;
    				mass2 = m2;
    			}
    		}
    	}}
	}
	return {mass1,mass2};
	
		
}
