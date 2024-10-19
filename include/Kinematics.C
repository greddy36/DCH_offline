#include "Kinematics.h"
#include "cat.h" //cat sort funs

float* SortPt(string cat, string tau){
	float pt[] = {pt_1,pt_2,pt_3,pt_4};
	int n = cat_lepCount(cat, 'e','m');
	std::vector<float> sort_pt;
	if (tau=="t"){
		for (int j = 0; j < cat.length(); j++){
			if (cat[j] == 't')
				sort_pt.push_back(pt[j]);
		}
	}	
	else{
		for (int j = 0; j < cat.length(); j++){
			if (cat[j] != 't')
				sort_pt.push_back(pt[j]);
		}
	}	
	float *pt_arr = new float[0]; //any number to initialize it.
	std::sort(sort_pt.begin(), sort_pt.end(), greater());//descending order
	std::copy(sort_pt.begin(), sort_pt.begin()+n, pt_arr);//vector->array	
	return pt_arr;
}

float ST(string cat){//for only leptons
	float st = 0;
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

float getDR(float eta1, float phi1, float eta2, float phi2) {
    float pi = TMath::Pi();
    float dPhi = fmin(fabs(phi2 - phi1), 2.0 * pi - fabs(phi2 - phi1));
    float DR = sqrt(pow(dPhi, 2) + pow(eta2 - eta1, 2));
    return DR;
}

// Structure to represent a lepton
struct Lepton{
    double pt;      
    double eta;
    double phi;
    double mass; 
    int charge;
 	float d0;
 	float dZ;
 	float iso;
    // Constructor for convenience
    Lepton(double pt, double eta, double phi, double mass, int charge, float d0, float dZ, float iso)
        : pt(pt), eta(eta), phi(phi), mass(mass), charge(charge), d0(d0), dZ(dZ), iso(iso) {}
};

bool isDuplicate(const Lepton &lepton1, const Lepton &lepton2){
	 if ( lepton1.charge == lepton2.charge and getDR(lepton1.eta, lepton1.phi, lepton2.eta, lepton2.phi) <= 0.2)
	 	return true;
	 else return false;
}

string pairFunc(int m, int n, string cat, float Zwindow){//checks if a pair is Z, Z-veto or DCH
	TLorentzVector lep1, lep2;
	int c1, c2;
	if (m==1){
		lep1 = LepV(1);
		c1 = q_1;
	}
	else if (m==2){
		lep1 = LepV(2);
		c1 = q_3;
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
		c2 = q_3;
	}
	else if (n==3){
		lep2 = LepV(3);
		c2 = q_3;
	}
	else if (n==4){
		lep2 = LepV(4);
		c2 = q_4;
	}
	
	if (cat[m] == cat[n] and c1 == -c2 and abs((lep1+lep2).M()-91.2) < Zwindow) return "Z";
	else if (cat[m] == cat[n] and c1 == -c2 and abs((lep1+lep2).M()-91.2) >= Zwindow) return "Zv";
	else if (c1 == c2 ) return "DCH";
	else return "found nothing";
}


TLorentzVector LepV(int n){
	TLorentzVector lepV;
	if (n==1)
		lepV.SetPtEtaPhiM(pt_1, eta_1, phi_1, m_1);
	if (n==2)
		lepV.SetPtEtaPhiM(pt_2, eta_2, phi_2, m_2);
	if (n==3)
		lepV.SetPtEtaPhiM(pt_3, eta_3, phi_3, m_3);
	if (n==4)
		lepV.SetPtEtaPhiM(pt_4, eta_4, phi_4, m_4);
	return lepV;
}	

std::vector<int> ZCandMaker(string cat, float Zwindow){
//make sure the there's no more than 2 lep with same charge before calling this fn.
//no need to sort cat in order of leptons before calling this fn.
//returns opposite-sign same-flav pairs
//First 2 leptons form the best Z pair and are pt sorted.
	float mZ = 91.2;
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


std::vector<int> ZVetoMaker(string cat, float Zwindow){
	float mZ = 91.2;
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

TLorentzVector *ZCandMaker_pair(string cat, TLorentzVector l1, TLorentzVector l2, TLorentzVector l3, TLorentzVector l4, float Zwindow){
	float mZ = 91.2;
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


TLorentzVector *ZVetoMaker_pair(string cat, TLorentzVector l1, TLorentzVector l2, TLorentzVector l3, TLorentzVector l4, float Zwindow){
	float mZ = 91.2;
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