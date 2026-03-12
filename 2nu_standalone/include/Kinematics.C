#include "TLorentzVector.h"
#include "TVector3.h"
#include <TMinuit.h>
//#include <utility>
#include "Kinematics.h"
#include "cat.h" //cat sort funs

void print4Vec(TLorentzVector Vec){
	cout<< Vec.Pt()<<"\t"<<Vec.Eta()<<"\t"<<Vec.Phi()<<"\t"<<Vec.M()<<endl;
}

std::vector<double> SortPt(){
	double pt[] = {pt_1,pt_2,pt_3,pt_4};
	std::vector<double> sorted_pt;
	for (int j = 0; j < 4; j++){
		sorted_pt.push_back(pt[j]);
	}
	std::sort(sorted_pt.begin(), sorted_pt.end(), greater());//descending order
	return sorted_pt;
}

string applyHEMveto(string cat){
	if (cat[0]=='e' and eta_1 > -3.0 and eta_1 < -1.3 and phi_1 > -1.57 and phi_1 < -0.87 and pt_1 >15) return "yes";
	if (cat[1]=='e' and eta_2 > -3.0 and eta_2 < -1.3 and phi_2 > -1.57 and phi_2 < -0.87 and pt_2 >15) return "yes";
	if (cat[2]=='e' and eta_3 > -3.0 and eta_3 < -1.3 and phi_3 > -1.57 and phi_3 < -0.87 and pt_3 >15) return "yes";
	if (cat[3]=='e' and eta_4 > -3.0 and eta_4 < -1.3 and phi_4 > -1.57 and phi_4 < -0.87 and pt_4 >15) return "yes";
	else return "no";
}
	

void applyTauES(string cat){//need to add extra lines to apply on MET
	if (cat[0] == 't'){
		pt_1 *= TauES_1;
		m_1 *= TauES_1;
	}
	if (cat[1] == 't'){
		pt_2 *= TauES_2;
		m_2 *= TauES_2;
	}
	if (cat[2] == 't'){
		pt_3 *= TauES_3;
		m_3 *= TauES_3;
	}
	if (cat[3] == 't'){
		pt_4 *= TauES_4;
		m_4 *= TauES_4;
	}
}


double ST(string cat){//for only leptons
	double st = 0;
	if (cat.find("e")+1==1 or cat.find("m")+1==1)
		st += pt_1;
	if (cat.find("e")+1==2 or cat.find("m")+1==2)
		st += pt_2; 
	if (cat.find("e")+1==3 or cat.find("m")+1==3)
		st += pt_3;
	if (cat.find("e")+1==4 or cat.find("m")+1==4)
		st += pt_4; 
	return st;
}

int remaining_idx(vector<pair<int, int>>& pair, std::string cat_name){//finds idxs not in the pair list
	int catSize = cat_name.length();
    std::set<int> used_indices;

    for (const auto& p : pair) {
        used_indices.insert(p.first);
        used_indices.insert(p.second);
    }
    for (int i = 1; i <= catSize; ++i) {
        if (used_indices.find(i) == used_indices.end()) return i;
    }
}

double dPhi(double phi1, double phi2){
	double pi = TMath::Pi();
    double DPhi = fmin(fabs(phi2 - phi1), 2.0 * pi - fabs(phi2 - phi1));
    return DPhi;
}
double deltaPhi(const TLorentzVector& v1, const TLorentzVector& v2){
	return dPhi(v1.Phi(), v2.Phi());
}

double getDR(double eta1, double phi1, double eta2, double phi2) {   
    double DR = sqrt(pow(dPhi(phi1, phi2), 2) + pow(eta2 - eta1, 2));
    return DR;
}


double deltaR(const TLorentzVector& v1, const TLorentzVector& v2) {
    double eta1 = v1.Eta();
    double phi1 = v1.Phi();
    double eta2 = v2.Eta();
    double phi2 = v2.Phi();
    return getDR(eta1, phi1, eta2, phi2);
}

double calculateMT(const TLorentzVector& V, const TLorentzVector& MET) {
    //double delta_phi = deltaPhi(V, MET);
    //return std::sqrt(2 * V.Pt() * MET.Pt() * (1 - std::cos(delta_phi)));
    double pt_total = (V+MET).Pt();
    return std::sqrt(std::pow(V.Et() + MET.Et(), 2) - pt_total * pt_total);
}

double calculateMTtot(const TLorentzVector& l1, const TLorentzVector& l2) {
	TLorentzVector LLpair = l1+l2;
    // Get LLpairton transverse components
    double px_ll = LLpair.Px();
    double py_ll = LLpair.Py();

    // Calculate MET components
    double px_met = met * std::cos(metphi);
    double py_met = met * std::sin(metphi);

    // Total transverse momentum components
    double px_total = px_ll + px_met;
    double py_total = py_ll + py_met;

    // Magnitudes
    double Et_ll = LLpair.Et();
    double pt_total = std::sqrt(px_total * px_total + py_total * py_total);

    // Compute total transverse mass
    double mt_tot = std::sqrt(std::pow(Et_ll + met, 2) - pt_total * pt_total);

    return mt_tot;
}

// Function to compute DCH masses with boost strategy
std::pair<double, double> ComputeDCHMasses(
    const TLorentzVector& lep1, 
    const TLorentzVector& lep2, 
    const TLorentzVector& lep3, 
    const TLorentzVector& lep4,
    const TLorentzVector& MET)
{

    //Visible 4-vector (sum of leptons)
    TLorentzVector vis = lep1 + lep2 + lep3 + lep4;

    //Compute boost to pz_visible = 0
    double beta_z = -vis.Pz() / vis.E();
    TVector3 boostVec(0, 0, beta_z);

    //Boost leptons to new frame
    TLorentzVector l1 = lep1;
    TLorentzVector l2 = lep2;
    TLorentzVector l3 = lep3;
    TLorentzVector l4 = lep4;

    l1.Boost(boostVec);
    l2.Boost(boostVec);
    l3.Boost(boostVec);
    l4.Boost(boostVec);

    //MET doesn't change as it's all in azimuthal plane
    TLorentzVector met4 = MET;
	met4.Boost(boostVec);
	
    /*//Build visible leg vectors
    TLorentzVector p12 = l1 + l2;
    TLorentzVector p34 = l3 + l4;

    //Missing for each DCH leg
    TLorentzVector p12_miss = 0.5 * (p34 + met4 - p12);
    TLorentzVector p34_miss = 0.5 * (p12 + met4 - p34);

    //Reconstruct DCH candidates
    TLorentzVector dch1 = p12 + p12_miss;
    TLorentzVector dch2 = p34 + p34_miss;
	cout<<dch1.Pt()<<"\t"<<dch2.Pt()<<"\t"<<dch1.E()<<"\t"<<dch2.E()<<endl;
	cout<<dch1.M()<<"\t"<<dch2.M()<<endl;*/
	
	// Step 3: Visible legs
    TLorentzVector leg1_vis = l1 + l2; // DCH++
    TLorentzVector leg2_vis = l3 + l4; // DCH−−
	// Step 4: Assign missing momenta in transverse plane (symmetric)
    TVector3 pT_leg1_miss = 0.5 * (met4.Vect() + (leg2_vis.Vect() - leg1_vis.Vect()));
    pT_leg1_miss.SetZ(0); // in this frame, start with pz=0

    TVector3 pT_leg2_miss = met4.Vect() - pT_leg1_miss;
    pT_leg2_miss.SetZ(0);
	
    // Step 5: Solve pz for equal mass constraint
    // Let pz1 = a, pz2 = -a (equal mass & total pz=0 in this frame)
    // Solve (E1vis+sqrt(|pT1miss|^2+a^2))^2 - |pT1vis+pT1miss|^2 - a^2
    //      = (E2vis+sqrt(|pT2miss|^2+a^2))^2 - |pT2vis+pT2miss|^2 - a^2

    double a_guess = 0;
    auto mass_diff = [&](double a){
        TLorentzVector miss1(pT_leg1_miss.X(), pT_leg1_miss.Y(), a, sqrt(pT_leg1_miss.Mag2() + a*a));
        TLorentzVector miss2(pT_leg2_miss.X(), pT_leg2_miss.Y(), -a, sqrt(pT_leg2_miss.Mag2() + a*a));
        double m1 = (leg1_vis + miss1).M();
        double m2 = (leg2_vis + miss2).M();
        return m1 - m2;
    };

    // Simple bisection to solve mass_diff(a)=0
    double lo = -2000, hi = 2000;
    for (int i=0; i<100; i++) {
        double mid = 0.5*(lo+hi);
        if (mass_diff(lo)*mass_diff(mid) <= 0) hi = mid;
        else lo = mid;
    }
    double a_sol = 0.5*(lo+hi);

    // Step 6: Build full legs with solved pz
    TLorentzVector miss1(pT_leg1_miss.X(), pT_leg1_miss.Y(), a_sol, sqrt(pT_leg1_miss.Mag2() + a_sol*a_sol));
    TLorentzVector miss2(pT_leg2_miss.X(), pT_leg2_miss.Y(), -a_sol, sqrt(pT_leg2_miss.Mag2() + a_sol*a_sol));

    TLorentzVector dch1 = leg1_vis + miss1;
    TLorentzVector dch2 = leg2_vis + miss2;
	
	//cout<<(leg1_vis.Vect()+leg2_vis.Vect()+met4.Vect()).X()<<endl;
    //Return the two invariant masses
    return std::make_pair(dch1.M(), dch2.M());
}

struct InputData {
    TLorentzVector l1, l2, l3, l4;
    TVector2 MET;
};

static TLorentzVector VA, VB;     // visible sides
static TVector2 METvec;           // MET
static double minMass = 1e9;      // best mass found
static double best_pzA = 0, best_pzB = 0;

// Minimization function for TMinuit
void fcn(int &npar, double *gin, double &f, double *par, int iflag) {
    // par[0] = pz_invisible_A
    // par[1] = pz_invisible_B
    // par[2] = px_invisible_A
    // par[3] = py_invisible_A

    double pzA = par[0];
    double pzB = par[1];
    double pxA = par[2];
    double pyA = par[3];

    // MET constraint
    double pxB = METvec.X() - pxA;
    double pyB = METvec.Y() - pyA;

    // Assume invisible massless neutrinos
    double pA_E = sqrt(pxA*pxA + pyA*pyA + pzA*pzA);
    double pB_E = sqrt(pxB*pxB + pyB*pyB + pzB*pzB);

    TLorentzVector IA(pxA, pyA, pzA, pA_E);
    TLorentzVector IB(pxB, pyB, pzB, pB_E);

    double MA = (VA + IA).M();
    double MB = (VB + IB).M();

    // Equal mass constraint by minimizing max(MA, MB)
    //f = fabs(MA - MB) + 0.01 * (MA + MB);
	f = std::max(MA, MB);
	
    // Keep track of best solution
    if (f < minMass) {
        minMass = f;
        best_pzA = pzA;
        best_pzB = pzB;
    }
}

std::pair<double, double>ReconstructMass(const InputData &in) {    // Partition leptons into two sides
    VA = in.l1 + in.l2;
    VB = in.l3 + in.l4;
    METvec = in.MET;

    // Setup Minuit
    TMinuit minuit(4);
    minuit.SetPrintLevel(-1);
    minuit.SetFCN(fcn);

    double step[4] = {1., 1., 1., 1.};
    double start[4] = {0., 0., 0., METvec.X()/2.};
    double bound[4] = {0.};

    for (int i = 0; i < 4; i++) {
        minuit.DefineParameter(i, Form("par%d", i), start[i], step[i], 0, 0);
    }

    minuit.Migrad();

    // After minimization, reconstruct equal mass
    double pxA = start[3];
    double pyA = start[3];
    double pzA = best_pzA;

    double pxB = METvec.X() - pxA;
    double pyB = METvec.Y() - pyA;
    double pzB = best_pzB;

    TLorentzVector IA(pxA, pyA, pzA, sqrt(pxA*pxA + pyA*pyA + pzA*pzA));
    TLorentzVector IB(pxB, pyB, pzB, sqrt(pxB*pxB + pyB*pyB + pzB*pzB));
    
    return std::make_pair((VA + IA).M(), (VB + IB).M());
}

// Structure to represent a lepton
struct Lepton{
    double pt;      
    double eta;
    double phi;
    double mass; 
    int charge;
 	double d0;
 	double dZ;
 	double iso;
    // Constructor for convenience
    Lepton(double pt, double eta, double phi, double mass, int charge, double d0, double dZ, double iso)
        : pt(pt), eta(eta), phi(phi), mass(mass), charge(charge), d0(d0), dZ(dZ), iso(iso) {}
};

bool isDuplicate(const Lepton &lepton1, const Lepton &lepton2){
	 if ( getDR(lepton1.eta, lepton1.phi, lepton2.eta, lepton2.phi) <= 0.4)
	 	return true;
	 else return false;
}

string pairFunc(int m, int n, string cat, double Zwindow){//checks if a pair is Z, Z-veto or DCH
	TLorentzVector lep1, lep2;
	int c1, c2;
	if (m==1){
		lep1 = LepV(1);
		c1 = q_1;
	}
	else if (m==2){
		lep1 = LepV(2);
		c1 = q_2;
	}
	else if (m==3){
		lep1 = LepV(3);
		c1 = q_3;
	}
	else if (m==4){
		lep1 = LepV(4);
		c1 = q_4;
	}
	if (n==1){
		lep2 = LepV(1);
		c2 = q_1;
	}
	else if (n==2){
		lep2 = LepV(2);
		c2 = q_2;
	}
	else if (n==3){
		lep2 = LepV(3);
		c2 = q_3;
	}
	else if (n==4){
		lep2 = LepV(4);
		c2 = q_4;
	}
	if (c1 == c2 ) return "DCH";
	else if (c1 == -c2){//doing Z window only for light leptons for now
		if ( (cat[m-1] == 'e' or cat[m-1] == 'm' ) and cat[m-1] == cat[n-1] and abs((lep1+lep2).M()-91.2) < Zwindow) return "Zwindow";
		else if ( (cat[m-1] == 'e' or cat[m-1] == 'm' ) and cat[m-1] == cat[n-1] and abs((lep1+lep2).M()-91.2) >= Zwindow) return "Zv";
		else if (cat[m-1] == 't' and cat[m-1] == cat[n-1]) return "ZttPair" ;
		else if (cat[m-1] != cat[n-1]) return "oppPair";
		else return "found nothing";
	}
	else "messed up";
}


TLorentzVector LepV(int n){
	TLorentzVector lepV;// make leptons massless
	if (n==1)
		lepV.SetPtEtaPhiM(pt_1, eta_1, phi_1, 0);
	if (n==2)
		lepV.SetPtEtaPhiM(pt_2, eta_2, phi_2, 0);
	if (n==3)
		lepV.SetPtEtaPhiM(pt_3, eta_3, phi_3, 0);
	if (n==4)
		lepV.SetPtEtaPhiM(pt_4, eta_4, phi_4, 0);
	return lepV;
}	

TLorentzVector NuV(int n){
	TLorentzVector nuV;
	if (n==1)
		nuV.SetPtEtaPhiM(nupt_1, nueta_1, nuphi_1, nuM_1);
	if (n==2)
		nuV.SetPtEtaPhiM(nupt_2, nueta_2, nuphi_2, nuM_2);
	if (n==3)
		nuV.SetPtEtaPhiM(nupt_3, nueta_3, nuphi_3, nuM_3);
	if (n==4)
		nuV.SetPtEtaPhiM(nupt_4, nueta_4, nuphi_4, nuM_4);
	return nuV;
}

std::vector<int> ZCandMaker(string cat, double Zwindow){
//make sure the there's no more than 2 lep with same charge before calling this fn.
//no need to sort cat in order of leptons before calling this fn.
//returns opposite-sign same-flav pairs
//First 2 leptons form the best Z pair and are pt sorted.
	double mZ = 91.2;
	TLorentzVector l1 = LepV(1), l2 = LepV(2), l3 = LepV(3), l4 = LepV(4);
	std::vector<int> arr = {1,2,3,4};
	auto swap_lep_array = [](std::vector<int>& arr, int m, int n){
		int temp = arr[m-1];
		arr[m-1] = arr[n-1];
		arr[n-1] = temp; 
	};
	auto swap_pair = [](std::vector<int>& arr){
		int tmp1 = arr[0];
		int tmp2 = arr[1];
		arr[0] = arr[2];
		arr[1] = arr[3];
		arr[2] = tmp1;
		arr[3] = tmp2;
	};
	if(cat.length() == 3){
		if( cat[0]==cat[1] and q_1 == -q_2 and abs((l1+l2).M()-mZ) < Zwindow){
			if (l1.Pt() < l2.Pt()) swap_lep_array(arr, 1, 2);
		}
		else if( cat[1]==cat[2] and q_2 == -q_3 and abs((l2+l3).M()-mZ) < Zwindow){
			if (l2.Pt() < l3.Pt()) arr = {3,2,1,4};
			else arr = {2,3,1,4};
		}
		else if( cat[0]==cat[2] and q_1 == -q_3 and abs((l1+l3).M()-mZ) < Zwindow ){
			if (l1.Pt() < l3.Pt()) arr = {3,1,2,4};
			else arr = {1,3,2,4};
		}
		return arr;
	}
	/*else if(cat.length() == 4){//needs fixing!!
		if( q_1 == -q_2 and q_3 == -q_4){
			if(cat[0] == cat[1]){
				if (l1.Pt() < l2.Pt()) swap_lep_array(arr, 1, 2);
			}	
			if(cat[2] == cat[3]){
				if (l3.Pt() < l4.Pt()) swap_lep_array(arr, 3, 4);
				if (abs((l3+l4).M()-mZ) < Zwindow) swap_pair(arr);
			}
			else if(cat[0] == cat[1] and cat[2] == cat[3] and abs((l1+l2).M()-mZ) < Zwindow and abs((l3+l4).M()-mZ) < Zwindow and  (l1+l2).Pt() < (l3+l4).Pt()) swap_pair(arr);
		}
		else if( q_1 == -q_3 and q_2 == -q_4){
			if(cat[0] == cat[2]){
				if (l1.Pt() < l3.Pt()) swap_lep_array(arr, 1, 3);
			}	
			if(cat[1] == cat[3]){
				if (l2.Pt() < l4.Pt()) swap_lep_array(arr, 2, 4);
			} 
			if(cat[0] == cat[2] and cat[1] == cat[3] and abs((l1+l3).M()-mZ) < Zwindow and abs((l2+l4).M()-mZ) < Zwindow and (l1+l3).Pt() < (l2+l4).Pt()) swap_pair(arr);
		}
		else if( q_1 == -q_4 and q_2 == -q_3){
			if(cat[0] == cat[3] and abs((l1+l4).M()-mZ) < Zwindow){
				if (l1.Pt() < l4.Pt()) swap_lep_array(arr, 1, 4);
			}	
			if(cat[1] == cat[2] and abs((l2+l3).M()-mZ) < Zwindow){
				if (l2.Pt() < l3.Pt()) swap_lep_array(arr, 2, 3);
			} 
			if(cat[0] == cat[3] and cat[1] == cat[2] and abs((l1+l4).M()-mZ) < Zwindow and abs((l2+l3).M()-mZ) < Zwindow and (l1+l4).Pt() < (l2+l3).Pt()) swap_pair(arr);			
		}
		return arr;*/
	else if(cat.length() == 4){//needs fixing!!
		if(cat[0] == cat[1] and q_1 == -q_2){
			if (l1.Pt() < l2.Pt()) swap_lep_array(arr, 1, 2);
		}	
		if(cat[2] == cat[3] and q_3 == -q_4){
			if (l3.Pt() < l4.Pt()) swap_lep_array(arr, 3, 4);
		}
		if(cat[0] == cat[1] and cat[2] == cat[3] and q_1 == -q_2 and q_3 == -q_4){
			if((l1+l2).Pt() < (l3+l4).Pt()) swap_pair(arr);
		}
		if(cat[0] == cat[2] and q_1 == -q_3){
			if (l1.Pt() < l3.Pt()) swap_lep_array(arr, 1, 3);
		}
		if(cat[0] == cat[3]){
			if (l1.Pt() < l4.Pt()) swap_lep_array(arr, 1, 4);
		}
		if(cat[1] == cat[2]){
			if (l2.Pt() < l3.Pt()) swap_lep_array(arr, 2, 3);
		}
		if(cat[1] == cat[3]){
			if (l2.Pt() < l4.Pt()) swap_lep_array(arr, 2, 4);
		}	
		return arr;
	}
}		


std::vector<int> ZVetoMaker(string cat, double Zwindow){
	double mZ = 91.2;
	//static int Zveto_arr[4] ;
	TLorentzVector l1 = LepV(1), l2 = LepV(2), l3 = LepV(3), l4 = LepV(4);
	std::vector<int> arr = {1,2,3,4};
	auto swap_lep_array = [](std::vector<int>& arr, int m, int n){
		int temp = arr[m-1];
		arr[m-1] = arr[n-1];
		arr[n-1] = temp; 
	};
	auto swap_pair = [](std::vector<int>& arr){
		int tmp1 = arr[0];
		int tmp2 = arr[1];
		arr[0] = arr[2];
		arr[1] = arr[3];
		arr[2] = tmp1;
		arr[3] = tmp2;
	};
		
	if(cat.length() == 3){
		if( cat[0]==cat[1] and q_1 == -q_2 and abs((l1+l2).M()-mZ) >= Zwindow){
			if (l1.Pt() < l2.Pt()) swap_lep_array(arr, 1, 2);
		}
		else if( cat[1]==cat[2] and q_2 == -q_3 and abs((l2+l3).M()-mZ) >= Zwindow){
			if (l2.Pt() < l3.Pt()) arr = {3,2,1,4};
			else arr = {2,3,1,4};
		}
		else if( cat[0]==cat[2] and q_1 == -q_3 and abs((l1+l3).M()-mZ) >= Zwindow){
			if (l1.Pt() < l3.Pt()) arr = {3,1,2,4};
			else arr = {1,3,2,4};
		}
		return arr;
	}
	else if(cat.length() == 4){//needs fixing!!
		if( q_1 == -q_2 and q_3 == -q_4){
			if(cat[0] == cat[1]){
				if (l1.Pt() < l2.Pt()) swap_lep_array(arr, 1, 2);
			}	
			if(cat[2] == cat[3]){
				if (l3.Pt() < l4.Pt()) swap_lep_array(arr, 3, 4); 
			}
			if(cat[0] == cat[1] and cat[2] == cat[3] and (l1+l2).Pt() < (l3+l4).Pt()) swap_pair(arr);
		}
		else if( q_1 == -q_3 and q_2 == -q_4){
			if(cat[0] == cat[2]){
				if (l1.Pt() < l3.Pt()) swap_lep_array(arr, 1, 3);
			}	
			if(cat[1] == cat[3]){
				if (l2.Pt() < l4.Pt()) swap_lep_array(arr, 2, 4);
			} 
			if(cat[0] == cat[2] and cat[1] == cat[3] and (l1+l3).Pt() < (l2+l4).Pt()) swap_pair(arr);
		}
		else if( q_1 == -q_4 and q_2 == -q_3){
			if(cat[0] == cat[3]){
				if (l1.Pt() < l4.Pt()) swap_lep_array(arr, 1, 4);
			}	
			if(cat[1] == cat[2]){
				if (l2.Pt() < l3.Pt()) swap_lep_array(arr, 2, 3);
			} 
			if(cat[0] == cat[3] and cat[1] == cat[2] and (l1+l4).Pt() < (l2+l3).Pt()) swap_pair(arr);			
		}
		return arr;
	}
}

TLorentzVector *ZCandMaker_pair(string cat, TLorentzVector l1, TLorentzVector l2, TLorentzVector l3, TLorentzVector l4, double Zwindow){
	double mZ = 91.2;
	TLorentzVector *Zpaired_lep = new TLorentzVector[4] ;
	TLorentzVector L1, L2, L3, L4;
	
	if(cat.length() == 3){
		if( cat[0]==cat[2] and abs((l1+l3).M()-mZ) < Zwindow){
			if(l1.Pt() >= l3.Pt()){
				L1 = l1; L2 = l3;
				L3 = l2; L4 = l4;
			}
			else{
				L1 = l3; L2 = l1;
				L3 = l2; L4 = l4;
			}
		}
		else if( cat[1]==cat[2] and abs((l2+l3).M()-mZ) < Zwindow){
			if(l2.Pt() >= l3.Pt()){
				L1 = l2; L2 = l3;
				L3 = l1; L4 = l4;
			}
			else{
				L1 = l3; L2 = l2;
				L3 = l1; L4 = l4;	
			}
		}
		if( cat[0]==cat[2] and cat[1]==cat[2] and abs((l1+l3).M()-mZ) < Zwindow and abs((l2+l3).M()-mZ) < Zwindow){
			if( l1.Pt() >= l3.Pt() and l3.Pt() >= l2.Pt()){
				L1 = l1; L2 = l3;
				L3 = l2; L4 = l4;
			}
			else if( l2.Pt() >= l3.Pt() and l3.Pt() >= l1.Pt()){
				L1 = l2; L2 = l3;
				L3 = l1; L4 = l4;	
			}
			else if( l3.Pt() >= l1.Pt() and l1.Pt() >= l1.Pt()){
				L1 = l3; L2 = l1;
				L3 = l2; L4 = l4;	
			}
			else if( l3.Pt() >= l2.Pt() and l2.Pt() >= l1.Pt()){
				L1 = l3; L2 = l2;
				L3 = l1; L4 = l4;	
			}
		}
	}
	else if(cat.length() == 4){//needs fixing!!
		if( cat[0]==cat[2] /*and abs((l1+l3).M()-mZ) < Zwindow*/){
			if(l1.Pt() >= l3.Pt()){
				L1 = l1; L2 = l3;
				L3 = l2; L4 = l4;
			}
			else{
				L1 = l3; L2 = l1;
				L3 = l2; L4 = l4;
			}
		}
		else if( cat[0]==cat[3] /*and abs((l1+l4).M()-mZ) < Zwindow*/){
			if(l1.Pt() >= l4.Pt()){
				L1 = l1; L2 = l4;
				L3 = l2; L4 = l3;
			}
			else{
				L1 = l4; L2 = l1;
				L3 = l2; L4 = l3;
			}
		}
		else if( cat[1]==cat[2] /*and abs((l2+l3).M()-mZ) < Zwindow*/){
			if(l2.Pt() >= l3.Pt()){
				L1 = l2; L2 = l3;
				L3 = l1; L4 = l4;
			}
			else{
				L1 = l3; L2 = l2;
				L3 = l1; L4 = l4;	
			}
		}
		else if( cat[1]==cat[3] /*and abs((l2+l4).M()-mZ) < Zwindow*/){
			if(l2.Pt() >= l4.Pt()){
				L1 = l2; L2 = l4;
				L3 = l1; L4 = l3;
			}
			else{
				L1 = l4; L2 = l2;
				L3 = l1; L4 = l3;	
			}
		}
	}
	Zpaired_lep[0] = L1;
	Zpaired_lep[1] = L2;
	Zpaired_lep[2] = L3;
	Zpaired_lep[3] = L4;
	return Zpaired_lep;
}		


TLorentzVector *ZVetoMaker_pair(string cat, TLorentzVector l1, TLorentzVector l2, TLorentzVector l3, TLorentzVector l4, double Zwindow){
	double mZ = 91.2;
	TLorentzVector *Zveto_lep = new TLorentzVector[4] ;
	TLorentzVector L1, L2, L3, L4;
	
	if(cat.length() == 3){
		if( cat[0]==cat[2] and abs((l1+l3).M()-mZ) > Zwindow){
			if(l1.Pt() >= l3.Pt()){
				L1 = l1; L2 = l3;
				L3 = l2; L4 = l4;
			}
			else{
				L1 = l3; L2 = l1;
				L3 = l2; L4 = l4;
			}
		}
		else if( cat[1]==cat[2] and abs((l2+l3).M()-mZ) > Zwindow){
			if(l2.Pt() >= l3.Pt()){
				L1 = l2; L2 = l3;
				L3 = l1; L4 = l4;
			}
			else{
				L1 = l3; L2 = l2;
				L3 = l1; L4 = l4;	
			}
		}
		if( cat[0]==cat[2] and cat[1]==cat[2] and abs((l1+l3).M()-mZ) > Zwindow and abs((l2+l3).M()-mZ) > Zwindow){
			if( l1.Pt() >= l3.Pt() and l3.Pt() >= l2.Pt()){
				L1 = l1; L2 = l3;
				L3 = l2; L4 = l4;
			}
			else if( l2.Pt() >= l3.Pt() and l3.Pt() >= l1.Pt()){
				L1 = l2; L2 = l3;
				L3 = l1; L4 = l4;	
			}
			else if( l3.Pt() >= l1.Pt() and l1.Pt() >= l1.Pt()){
				L1 = l3; L2 = l1;
				L3 = l2; L4 = l4;	
			}
			else if( l3.Pt() >= l2.Pt() and l2.Pt() >= l1.Pt()){
				L1 = l3; L2 = l2;
				L3 = l1; L4 = l4;	
			}
		}
	}
	//else if(cat.length() == 4){
	
	Zveto_lep[0] = L1;
	Zveto_lep[1] = L2;
	Zveto_lep[2] = L3;
	Zveto_lep[3] = L4;
	return Zveto_lep;
}