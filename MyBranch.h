//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Dec  4 18:17:27 2025 by ROOT version 6.26/10
// from TTree Events/Output tree
// found on file: skim_500_test.root
//////////////////////////////////////////////////////////

#ifndef MyBranch_h
#define MyBranch_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class MyBranch {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   ULong64_t       run;
   ULong64_t       nElectron;
   ULong64_t       nMuon;
   ULong64_t       nTau;
   Int_t           lumi;
   ULong64_t       evt;
   Int_t           nPU;
   Int_t           nPUEOOT;
   Int_t           nPULOOT;
   Double_t        nPUtrue;
   Int_t           nPV;
   Int_t           nPVGood;
   Int_t           cat;
   Int_t           gen_cat;
   Double_t        brWeight;
   Double_t        weight;
   Double_t        weightPU;
   Double_t        weightPUtrue;
   Double_t        weightPUtruejson;
   Double_t        weightPUtruejson_up;
   Double_t        weightPUtruejson_down;
   Double_t        LHEweight;
   Int_t           LHE_Njets;
   Double_t        LHEScaleWeights[9];
   Double_t        Generator_weight;
   Int_t           electronTriggerWord;
   Int_t           muonTriggerWord;
   Int_t           whichTriggerWord;
   Int_t           whichTriggerWordSubL;
   Double_t        IDSF_1;
   Double_t        ISOSF_1;
   Double_t        TrigSF_1;
   Double_t        IDSF_2;
   Double_t        ISOSF_2;
   Double_t        TrigSF_2;
   Double_t        IDSF_3;
   Double_t        ISOSF_3;
   Double_t        TrigSF_3;
   Double_t        IDSF_4;
   Double_t        ISOSF_4;
   Double_t        TrigSF_4;
   Double_t        EleID_1;
   Double_t        EleID_2;
   Double_t        EleID_3;
   Double_t        EleID_4;
   Int_t           MuID_1;
   Int_t           MuID_2;
   Int_t           MuID_3;
   Int_t           MuID_4;
   Double_t        TauVsEleIDSF_1;
   Double_t        TauVsEleIDSF_2;
   Double_t        TauVsEleIDSF_3;
   Double_t        TauVsEleIDSF_4;
   Double_t        TauVsMuIDSF_1;
   Double_t        TauVsMuIDSF_2;
   Double_t        TauVsMuIDSF_3;
   Double_t        TauVsMuIDSF_4;
   Double_t        TauVsJetIDSF_1;
   Double_t        TauVsJetIDSF_2;
   Double_t        TauVsJetIDSF_3;
   Double_t        TauVsJetIDSF_4;
   Double_t        TauES_1;
   Double_t        TauES_2;
   Double_t        TauES_3;
   Double_t        TauES_4;
   Int_t           nGoodElectron;
   Int_t           nGoodMuon;
   Int_t           nGoodTau;
   Int_t           GenPart_statusFlags_1;
   Int_t           GenPart_statusFlags_2;
   Int_t           GenPart_statusFlags_3;
   Int_t           GenPart_statusFlags_4;
   Int_t           GenPart_status_1;
   Int_t           GenPart_status_2;
   Int_t           GenPart_status_3;
   Int_t           GenPart_status_4;
   Double_t        pt_uncor_1;
   Double_t        pt_uncor_2;
   Double_t        pt_uncor_3;
   Double_t        pt_uncor_4;
   Double_t        m_uncor_1;
   Double_t        m_uncor_2;
   Double_t        m_uncor_3;
   Double_t        m_uncor_4;
   Double_t        pt_3;
   Double_t        pt_3_tr;
   Double_t        phi_3;
   Double_t        phi_3_tr;
   Double_t        eta_3;
   Double_t        eta_3_tr;
   Double_t        m_3;
   Double_t        q_3;
   Double_t        d0_3;
   Double_t        dZ_3;
   Double_t        mt_3;
   Double_t        pfmt_3;
   Double_t        iso_3;
   ULong64_t       gen_match_1;
   ULong64_t       gen_match_2;
   ULong64_t       gen_match_3;
   Double_t        isGlobal_3;
   Double_t        isTracker_3;
   Double_t        ip3d_3;
   Int_t           decayMode_3;
   Int_t           decayMode_4;
   Double_t        pt_4;
   Double_t        pt_4_tr;
   Double_t        phi_4;
   Double_t        phi_4_tr;
   Double_t        eta_4;
   Double_t        eta_4_tr;
   Double_t        m_4;
   Double_t        q_4;
   Double_t        d0_4;
   Double_t        dZ_4;
   Double_t        mt_4;
   Double_t        pfmt_4;
   Double_t        iso_4;
   ULong64_t       gen_match_4;
   Double_t        isGlobal_4;
   Double_t        isTracker_4;
   Double_t        ip3d_4;
   Int_t           decayMode_1;
   Int_t           decayMode_2;
   Double_t        pt_tt;
   Double_t        mt_tot;
   Double_t        m_vis;
   Double_t        mDCH1_sv;
   Double_t        mtDCH1_sv;
   Double_t        mDCH2_sv;
   Double_t        mtDCH2_sv;
   Double_t        mDCH1_sv4;
   Double_t        mtDCH1_sv4;
   Double_t        mDCH2_sv4;
   Double_t        mtDCH2_sv4;
   Double_t        H_DR;
   Double_t        AMass;
   Double_t        H_LT;
   Double_t        dRl1H;
   Double_t        dRl2H;
   Double_t        dRlH;
   Double_t        dPhil1H;
   Double_t        dPhil2H;
   Double_t        dPhilH;
   Double_t        mll;
   Double_t        mll2;
   Double_t        Z_Pt;
   Double_t        Z_DR;
   Double_t        Z_SS;
   Double_t        pt_1;
   Double_t        m_1;
   Double_t        m_1_tr;
   Double_t        pt_1_tr;
   Double_t        phi_1;
   Double_t        phi_1_tr;
   Double_t        eta_1;
   Double_t        eta_1_tr;
   Double_t        pt_2;
   Double_t        m_2;
   Double_t        m_2_tr;
   Double_t        pt_2_tr;
   Double_t        phi_2;
   Double_t        phi_2_tr;
   Double_t        eta_2;
   Double_t        eta_2_tr;
   Double_t        iso_1;
   Double_t        iso_2;
   Double_t        q_1;
   Double_t        q_2;
   Double_t        L1PreFiringWeight_Nom;
   Double_t        L1PreFiringWeight_Up;
   Double_t        L1PreFiringWeight_Down;
   Double_t        d0_1;
   Double_t        dZ_1;
   Double_t        d0_2;
   Double_t        dZ_2;
   Double_t        isGlobal_1;
   Double_t        isGlobal_2;
   Double_t        isTracker_1;
   Double_t        isTracker_2;
   Double_t        MET_pt_UnclUp;
   Double_t        MET_phi_UnclUp;
   Double_t        MET_pt_UnclDown;
   Double_t        MET_phi_UnclDown;
   Double_t        met_UnclX;
   Double_t        met_UnclY;
   Double_t        MET_T1Smear_pt;
   Double_t        MET_T1Smear_phi;
   Double_t        met;
   Double_t        metphi;
   Double_t        metNoCor;
   Double_t        metphiNoCor;
   Double_t        metNoTauES;
   Double_t        metphiNoTauES;
   Double_t        metcov00;
   Double_t        metcov01;
   Double_t        metcov10;
   Double_t        metcov11;
   Double_t        isTrig_2;
   Double_t        isTrig_1;
   Double_t        isDoubleTrig;
   Double_t        njets;
   Double_t        nbtagL;
   Double_t        nbtagM;
   Double_t        nbtagT;
   ULong64_t       HTXS_Higgs_cat;
   Double_t        HTXS_Higgs_pt;
   Double_t        jflavour[12];
   Double_t        jeta[12];
   Double_t        jpt[12];
   Double_t        btagDeep[12];
   Double_t        nupt_1;
   Double_t        nupt_2;
   Double_t        nupt_3;
   Double_t        nupt_4;
   Double_t        nueta_1;
   Double_t        nueta_2;
   Double_t        nueta_3;
   Double_t        nueta_4;
   Double_t        nuphi_1;
   Double_t        nuphi_2;
   Double_t        nuphi_3;
   Double_t        nuphi_4;
   Double_t        nuM_1;
   Double_t        nuM_2;
   Double_t        nuM_3;
   Double_t        nuM_4;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_nElectron;   //!
   TBranch        *b_nMuon;   //!
   TBranch        *b_nTau;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_evt;   //!
   TBranch        *b_nPU;   //!
   TBranch        *b_nPUEOOT;   //!
   TBranch        *b_nPULOOT;   //!
   TBranch        *b_nPUtrue;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_nPVGood;   //!
   TBranch        *b_cat;   //!
   TBranch        *b_gen_cat;   //!
   TBranch        *b_brWeight;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_weightPU;   //!
   TBranch        *b_weightPUtrue;   //!
   TBranch        *b_weightPUtruejson;   //!
   TBranch        *b_weightPUtruejson_up;   //!
   TBranch        *b_weightPUtruejson_down;   //!
   TBranch        *b_LHEweight;   //!
   TBranch        *b_LHE_Njets;   //!
   TBranch        *b_LHEScaleWeights;   //!
   TBranch        *b_Generator_weight;   //!
   TBranch        *b_electronTriggerWord;   //!
   TBranch        *b_muonTriggerWord;   //!
   TBranch        *b_whichTriggerWord;   //!
   TBranch        *b_whichTriggerWordSubL;   //!
   TBranch        *b_IDSF_1;   //!
   TBranch        *b_ISOSF_1;   //!
   TBranch        *b_TrigSF_1;   //!
   TBranch        *b_IDSF_2;   //!
   TBranch        *b_ISOSF_2;   //!
   TBranch        *b_TrigSF_2;   //!
   TBranch        *b_IDSF_3;   //!
   TBranch        *b_ISOSF_3;   //!
   TBranch        *b_TrigSF_3;   //!
   TBranch        *b_IDSF_4;   //!
   TBranch        *b_ISOSF_4;   //!
   TBranch        *b_TrigSF_4;   //!
   TBranch        *b_EleID_1;   //!
   TBranch        *b_EleID_2;   //!
   TBranch        *b_EleID_3;   //!
   TBranch        *b_EleID_4;   //!
   TBranch        *b_MuID_1;   //!
   TBranch        *b_MuID_2;   //!
   TBranch        *b_MuID_3;   //!
   TBranch        *b_MuID_4;   //!
   TBranch        *b_TauVsEleIDSF_1;   //!
   TBranch        *b_TauVsEleIDSF_2;   //!
   TBranch        *b_TauVsEleIDSF_3;   //!
   TBranch        *b_TauVsEleIDSF_4;   //!
   TBranch        *b_TauVsMuIDSF_1;   //!
   TBranch        *b_TauVsMuIDSF_2;   //!
   TBranch        *b_TauVsMuIDSF_3;   //!
   TBranch        *b_TauVsMuIDSF_4;   //!
   TBranch        *b_TauVsJetIDSF_1;   //!
   TBranch        *b_TauVsJetIDSF_2;   //!
   TBranch        *b_TauVsJetIDSF_3;   //!
   TBranch        *b_TauVsJetIDSF_4;   //!
   TBranch        *b_TauES_1;   //!
   TBranch        *b_TauES_2;   //!
   TBranch        *b_TauES_3;   //!
   TBranch        *b_TauES_4;   //!
   TBranch        *b_nGoodElectron;   //!
   TBranch        *b_nGoodMuon;   //!
   TBranch        *b_nGoodTau;   //!
   TBranch        *b_GenPart_statusFlags_1;   //!
   TBranch        *b_GenPart_statusFlags_2;   //!
   TBranch        *b_GenPart_statusFlags_3;   //!
   TBranch        *b_GenPart_statusFlags_4;   //!
   TBranch        *b_GenPart_status_1;   //!
   TBranch        *b_GenPart_status_2;   //!
   TBranch        *b_GenPart_status_3;   //!
   TBranch        *b_GenPart_status_4;   //!
   TBranch        *b_pt_uncor_1;   //!
   TBranch        *b_pt_uncor_2;   //!
   TBranch        *b_pt_uncor_3;   //!
   TBranch        *b_pt_uncor_4;   //!
   TBranch        *b_m_uncor_1;   //!
   TBranch        *b_m_uncor_2;   //!
   TBranch        *b_m_uncor_3;   //!
   TBranch        *b_m_uncor_4;   //!
   TBranch        *b_pt_3;   //!
   TBranch        *b_pt_3_tr;   //!
   TBranch        *b_phi_3;   //!
   TBranch        *b_phi_3_tr;   //!
   TBranch        *b_eta_3;   //!
   TBranch        *b_eta_3_tr;   //!
   TBranch        *b_m_3;   //!
   TBranch        *b_q_3;   //!
   TBranch        *b_d0_3;   //!
   TBranch        *b_dZ_3;   //!
   TBranch        *b_mt_3;   //!
   TBranch        *b_pfmt_3;   //!
   TBranch        *b_iso_3;   //!
   TBranch        *b_gen_match_1;   //!
   TBranch        *b_gen_match_2;   //!
   TBranch        *b_gen_match_3;   //!
   TBranch        *b_isGlobal_3;   //!
   TBranch        *b_isTracker_3;   //!
   TBranch        *b_ip3d_3;   //!
   TBranch        *b_decayMode_3;   //!
   TBranch        *b_decayMode_4;   //!
   TBranch        *b_pt_4;   //!
   TBranch        *b_pt_4_tr;   //!
   TBranch        *b_phi_4;   //!
   TBranch        *b_phi_4_tr;   //!
   TBranch        *b_eta_4;   //!
   TBranch        *b_eta_4_tr;   //!
   TBranch        *b_m_4;   //!
   TBranch        *b_q_4;   //!
   TBranch        *b_d0_4;   //!
   TBranch        *b_dZ_4;   //!
   TBranch        *b_mt_4;   //!
   TBranch        *b_pfmt_4;   //!
   TBranch        *b_iso_4;   //!
   TBranch        *b_gen_match_4;   //!
   TBranch        *b_isGlobal_4;   //!
   TBranch        *b_isTracker_4;   //!
   TBranch        *b_ip3d_4;   //!
   TBranch        *b_decayMode_1;   //!
   TBranch        *b_decayMode_2;   //!
   TBranch        *b_pt_tt;   //!
   TBranch        *b_mt_tot;   //!
   TBranch        *b_m_vis;   //!
   TBranch        *b_mDCH1_sv;   //!
   TBranch        *b_mtDCH1_sv;   //!
   TBranch        *b_mDCH2_sv;   //!
   TBranch        *b_mtDCH2_sv;   //!
   TBranch        *b_mDCH1_sv4;   //!
   TBranch        *b_mtDCH1_sv4;   //!
   TBranch        *b_mDCH2_sv4;   //!
   TBranch        *b_mtDCH2_sv4;   //!
   TBranch        *b_H_DR;   //!
   TBranch        *b_AMass;   //!
   TBranch        *b_H_LT;   //!
   TBranch        *b_dRl1H;   //!
   TBranch        *b_dRl2H;   //!
   TBranch        *b_dRlH;   //!
   TBranch        *b_dPhil1H;   //!
   TBranch        *b_dPhil2H;   //!
   TBranch        *b_dPhilH;   //!
   TBranch        *b_mll;   //!
   TBranch        *b_mll2;   //!
   TBranch        *b_Z_Pt;   //!
   TBranch        *b_Z_DR;   //!
   TBranch        *b_Z_SS;   //!
   TBranch        *b_pt_1;   //!
   TBranch        *b_m_1;   //!
   TBranch        *b_m_1_tr;   //!
   TBranch        *b_pt_1_tr;   //!
   TBranch        *b_phi_1;   //!
   TBranch        *b_phi_1_tr;   //!
   TBranch        *b_eta_1;   //!
   TBranch        *b_eta_1_tr;   //!
   TBranch        *b_pt_2;   //!
   TBranch        *b_m_2;   //!
   TBranch        *b_m_2_tr;   //!
   TBranch        *b_pt_2_tr;   //!
   TBranch        *b_phi_2;   //!
   TBranch        *b_phi_2_tr;   //!
   TBranch        *b_eta_2;   //!
   TBranch        *b_eta_2_tr;   //!
   TBranch        *b_iso_1;   //!
   TBranch        *b_iso_2;   //!
   TBranch        *b_q_1;   //!
   TBranch        *b_q_2;   //!
   TBranch        *b_L1PreFiringWeight_Nom;   //!
   TBranch        *b_L1PreFiringWeight_Up;   //!
   TBranch        *b_L1PreFiringWeight_Down;   //!
   TBranch        *b_d0_1;   //!
   TBranch        *b_dZ_1;   //!
   TBranch        *b_d0_2;   //!
   TBranch        *b_dZ_2;   //!
   TBranch        *b_isGlobal_1;   //!
   TBranch        *b_isGlobal_2;   //!
   TBranch        *b_isTracker_1;   //!
   TBranch        *b_isTracker_2;   //!
   TBranch        *b_MET_pt_UnclUp;   //!
   TBranch        *b_MET_phi_UnclUp;   //!
   TBranch        *b_MET_pt_UnclDown;   //!
   TBranch        *b_MET_phi_UnclDown;   //!
   TBranch        *b_met_UnclX;   //!
   TBranch        *b_met_UnclY;   //!
   TBranch        *b_MET_T1Smear_pt;   //!
   TBranch        *b_MET_T1Smear_phi;   //!
   TBranch        *b_met;   //!
   TBranch        *b_metphi;   //!
   TBranch        *b_metNoCor;   //!
   TBranch        *b_metphiNoCor;   //!
   TBranch        *b_metNoTauES;   //!
   TBranch        *b_metphiNoTauES;   //!
   TBranch        *b_metcov00;   //!
   TBranch        *b_metcov01;   //!
   TBranch        *b_metcov10;   //!
   TBranch        *b_metcov11;   //!
   TBranch        *b_isTrig_2;   //!
   TBranch        *b_isTrig_1;   //!
   TBranch        *b_isDoubleTrig;   //!
   TBranch        *b_njets;   //!
   TBranch        *b_nbtagL;   //!
   TBranch        *b_nbtagM;   //!
   TBranch        *b_nbtagT;   //!
   TBranch        *b_HTXS_Higgs_cat;   //!
   TBranch        *b_HTXS_Higgs_pt;   //!
   TBranch        *b_jflavour;   //!
   TBranch        *b_jeta;   //!
   TBranch        *b_jpt;   //!
   TBranch        *b_btagDeep;   //!
   TBranch        *b_nupt_1;   //!
   TBranch        *b_nupt_3;   //!
   TBranch        *b_nupt_2;   //!
   TBranch        *b_nupt_4;   //!
   TBranch        *b_nueta_1;   //!
   TBranch        *b_nueta_3;   //!
   TBranch        *b_nueta_2;   //!
   TBranch        *b_nueta_4;   //!
   TBranch        *b_nuphi_1;   //!
   TBranch        *b_nuphi_3;   //!
   TBranch        *b_nuphi_2;   //!
   TBranch        *b_nuphi_4;   //!
   TBranch        *b_nuM_1;   //!
   TBranch        *b_nuM_3;   //!
   TBranch        *b_nuM_2;   //!
   TBranch        *b_nuM_4;   //!

   MyBranch(TTree *tree=0);
   virtual ~MyBranch();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MyBranch_cxx
MyBranch::MyBranch(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("skim_500_test.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("skim_500_test.root");
      }
      f->GetObject("Events",tree);

   }
   Init(tree);
}

MyBranch::~MyBranch()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MyBranch::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MyBranch::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MyBranch::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("nElectron", &nElectron, &b_nElectron);
   fChain->SetBranchAddress("nMuon", &nMuon, &b_nMuon);
   fChain->SetBranchAddress("nTau", &nTau, &b_nTau);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("evt", &evt, &b_evt);
   fChain->SetBranchAddress("nPU", &nPU, &b_nPU);
   fChain->SetBranchAddress("nPUEOOT", &nPUEOOT, &b_nPUEOOT);
   fChain->SetBranchAddress("nPULOOT", &nPULOOT, &b_nPULOOT);
   fChain->SetBranchAddress("nPUtrue", &nPUtrue, &b_nPUtrue);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("nPVGood", &nPVGood, &b_nPVGood);
   fChain->SetBranchAddress("cat", &cat, &b_cat);
   fChain->SetBranchAddress("gen_cat", &gen_cat, &b_gen_cat);
   fChain->SetBranchAddress("brWeight", &brWeight, &b_brWeight);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("weightPU", &weightPU, &b_weightPU);
   fChain->SetBranchAddress("weightPUtrue", &weightPUtrue, &b_weightPUtrue);
   fChain->SetBranchAddress("weightPUtruejson", &weightPUtruejson, &b_weightPUtruejson);
   fChain->SetBranchAddress("weightPUtruejson_up", &weightPUtruejson_up, &b_weightPUtruejson_up);
   fChain->SetBranchAddress("weightPUtruejson_down", &weightPUtruejson_down, &b_weightPUtruejson_down);
   fChain->SetBranchAddress("LHEweight", &LHEweight, &b_LHEweight);
   fChain->SetBranchAddress("LHE_Njets", &LHE_Njets, &b_LHE_Njets);
   fChain->SetBranchAddress("LHEScaleWeights", LHEScaleWeights, &b_LHEScaleWeights);
   fChain->SetBranchAddress("Generator_weight", &Generator_weight, &b_Generator_weight);
   fChain->SetBranchAddress("electronTriggerWord", &electronTriggerWord, &b_electronTriggerWord);
   fChain->SetBranchAddress("muonTriggerWord", &muonTriggerWord, &b_muonTriggerWord);
   fChain->SetBranchAddress("whichTriggerWord", &whichTriggerWord, &b_whichTriggerWord);
   fChain->SetBranchAddress("whichTriggerWordSubL", &whichTriggerWordSubL, &b_whichTriggerWordSubL);
   fChain->SetBranchAddress("IDSF_1", &IDSF_1, &b_IDSF_1);
   fChain->SetBranchAddress("ISOSF_1", &ISOSF_1, &b_ISOSF_1);
   fChain->SetBranchAddress("TrigSF_1", &TrigSF_1, &b_TrigSF_1);
   fChain->SetBranchAddress("IDSF_2", &IDSF_2, &b_IDSF_2);
   fChain->SetBranchAddress("ISOSF_2", &ISOSF_2, &b_ISOSF_2);
   fChain->SetBranchAddress("TrigSF_2", &TrigSF_2, &b_TrigSF_2);
   fChain->SetBranchAddress("IDSF_3", &IDSF_3, &b_IDSF_3);
   fChain->SetBranchAddress("ISOSF_3", &ISOSF_3, &b_ISOSF_3);
   fChain->SetBranchAddress("TrigSF_3", &TrigSF_3, &b_TrigSF_3);
   fChain->SetBranchAddress("IDSF_4", &IDSF_4, &b_IDSF_4);
   fChain->SetBranchAddress("ISOSF_4", &ISOSF_4, &b_ISOSF_4);
   fChain->SetBranchAddress("TrigSF_4", &TrigSF_4, &b_TrigSF_4);
   fChain->SetBranchAddress("EleID_1", &EleID_1, &b_EleID_1);
   fChain->SetBranchAddress("EleID_2", &EleID_2, &b_EleID_2);
   fChain->SetBranchAddress("EleID_3", &EleID_3, &b_EleID_3);
   fChain->SetBranchAddress("EleID_4", &EleID_4, &b_EleID_4);
   fChain->SetBranchAddress("MuID_1", &MuID_1, &b_MuID_1);
   fChain->SetBranchAddress("MuID_2", &MuID_2, &b_MuID_2);
   fChain->SetBranchAddress("MuID_3", &MuID_3, &b_MuID_3);
   fChain->SetBranchAddress("MuID_4", &MuID_4, &b_MuID_4);
   fChain->SetBranchAddress("TauVsEleIDSF_1", &TauVsEleIDSF_1, &b_TauVsEleIDSF_1);
   fChain->SetBranchAddress("TauVsEleIDSF_2", &TauVsEleIDSF_2, &b_TauVsEleIDSF_2);
   fChain->SetBranchAddress("TauVsEleIDSF_3", &TauVsEleIDSF_3, &b_TauVsEleIDSF_3);
   fChain->SetBranchAddress("TauVsEleIDSF_4", &TauVsEleIDSF_4, &b_TauVsEleIDSF_4);
   fChain->SetBranchAddress("TauVsMuIDSF_1", &TauVsMuIDSF_1, &b_TauVsMuIDSF_1);
   fChain->SetBranchAddress("TauVsMuIDSF_2", &TauVsMuIDSF_2, &b_TauVsMuIDSF_2);
   fChain->SetBranchAddress("TauVsMuIDSF_3", &TauVsMuIDSF_3, &b_TauVsMuIDSF_3);
   fChain->SetBranchAddress("TauVsMuIDSF_4", &TauVsMuIDSF_4, &b_TauVsMuIDSF_4);
   fChain->SetBranchAddress("TauVsJetIDSF_1", &TauVsJetIDSF_1, &b_TauVsJetIDSF_1);
   fChain->SetBranchAddress("TauVsJetIDSF_2", &TauVsJetIDSF_2, &b_TauVsJetIDSF_2);
   fChain->SetBranchAddress("TauVsJetIDSF_3", &TauVsJetIDSF_3, &b_TauVsJetIDSF_3);
   fChain->SetBranchAddress("TauVsJetIDSF_4", &TauVsJetIDSF_4, &b_TauVsJetIDSF_4);
   fChain->SetBranchAddress("TauES_1", &TauES_1, &b_TauES_1);
   fChain->SetBranchAddress("TauES_2", &TauES_2, &b_TauES_2);
   fChain->SetBranchAddress("TauES_3", &TauES_3, &b_TauES_3);
   fChain->SetBranchAddress("TauES_4", &TauES_4, &b_TauES_4);
   fChain->SetBranchAddress("nGoodElectron", &nGoodElectron, &b_nGoodElectron);
   fChain->SetBranchAddress("nGoodMuon", &nGoodMuon, &b_nGoodMuon);
   fChain->SetBranchAddress("nGoodTau", &nGoodTau, &b_nGoodTau);
   fChain->SetBranchAddress("GenPart_statusFlags_1", &GenPart_statusFlags_1, &b_GenPart_statusFlags_1);
   fChain->SetBranchAddress("GenPart_statusFlags_2", &GenPart_statusFlags_2, &b_GenPart_statusFlags_2);
   fChain->SetBranchAddress("GenPart_statusFlags_3", &GenPart_statusFlags_3, &b_GenPart_statusFlags_3);
   fChain->SetBranchAddress("GenPart_statusFlags_4", &GenPart_statusFlags_4, &b_GenPart_statusFlags_4);
   fChain->SetBranchAddress("GenPart_status_1", &GenPart_status_1, &b_GenPart_status_1);
   fChain->SetBranchAddress("GenPart_status_2", &GenPart_status_2, &b_GenPart_status_2);
   fChain->SetBranchAddress("GenPart_status_3", &GenPart_status_3, &b_GenPart_status_3);
   fChain->SetBranchAddress("GenPart_status_4", &GenPart_status_4, &b_GenPart_status_4);
   fChain->SetBranchAddress("pt_uncor_1", &pt_uncor_1, &b_pt_uncor_1);
   fChain->SetBranchAddress("pt_uncor_2", &pt_uncor_2, &b_pt_uncor_2);
   fChain->SetBranchAddress("pt_uncor_3", &pt_uncor_3, &b_pt_uncor_3);
   fChain->SetBranchAddress("pt_uncor_4", &pt_uncor_4, &b_pt_uncor_4);
   fChain->SetBranchAddress("m_uncor_1", &m_uncor_1, &b_m_uncor_1);
   fChain->SetBranchAddress("m_uncor_2", &m_uncor_2, &b_m_uncor_2);
   fChain->SetBranchAddress("m_uncor_3", &m_uncor_3, &b_m_uncor_3);
   fChain->SetBranchAddress("m_uncor_4", &m_uncor_4, &b_m_uncor_4);
   fChain->SetBranchAddress("pt_3", &pt_3, &b_pt_3);
   fChain->SetBranchAddress("pt_3_tr", &pt_3_tr, &b_pt_3_tr);
   fChain->SetBranchAddress("phi_3", &phi_3, &b_phi_3);
   fChain->SetBranchAddress("phi_3_tr", &phi_3_tr, &b_phi_3_tr);
   fChain->SetBranchAddress("eta_3", &eta_3, &b_eta_3);
   fChain->SetBranchAddress("eta_3_tr", &eta_3_tr, &b_eta_3_tr);
   fChain->SetBranchAddress("m_3", &m_3, &b_m_3);
   fChain->SetBranchAddress("q_3", &q_3, &b_q_3);
   fChain->SetBranchAddress("d0_3", &d0_3, &b_d0_3);
   fChain->SetBranchAddress("dZ_3", &dZ_3, &b_dZ_3);
   fChain->SetBranchAddress("mt_3", &mt_3, &b_mt_3);
   fChain->SetBranchAddress("pfmt_3", &pfmt_3, &b_pfmt_3);
   fChain->SetBranchAddress("iso_3", &iso_3, &b_iso_3);
   fChain->SetBranchAddress("gen_match_1", &gen_match_1, &b_gen_match_1);
   fChain->SetBranchAddress("gen_match_2", &gen_match_2, &b_gen_match_2);
   fChain->SetBranchAddress("gen_match_3", &gen_match_3, &b_gen_match_3);
   fChain->SetBranchAddress("isGlobal_3", &isGlobal_3, &b_isGlobal_3);
   fChain->SetBranchAddress("isTracker_3", &isTracker_3, &b_isTracker_3);
   fChain->SetBranchAddress("ip3d_3", &ip3d_3, &b_ip3d_3);
   fChain->SetBranchAddress("decayMode_3", &decayMode_3, &b_decayMode_3);
   fChain->SetBranchAddress("decayMode_4", &decayMode_4, &b_decayMode_4);
   fChain->SetBranchAddress("pt_4", &pt_4, &b_pt_4);
   fChain->SetBranchAddress("pt_4_tr", &pt_4_tr, &b_pt_4_tr);
   fChain->SetBranchAddress("phi_4", &phi_4, &b_phi_4);
   fChain->SetBranchAddress("phi_4_tr", &phi_4_tr, &b_phi_4_tr);
   fChain->SetBranchAddress("eta_4", &eta_4, &b_eta_4);
   fChain->SetBranchAddress("eta_4_tr", &eta_4_tr, &b_eta_4_tr);
   fChain->SetBranchAddress("m_4", &m_4, &b_m_4);
   fChain->SetBranchAddress("q_4", &q_4, &b_q_4);
   fChain->SetBranchAddress("d0_4", &d0_4, &b_d0_4);
   fChain->SetBranchAddress("dZ_4", &dZ_4, &b_dZ_4);
   fChain->SetBranchAddress("mt_4", &mt_4, &b_mt_4);
   fChain->SetBranchAddress("pfmt_4", &pfmt_4, &b_pfmt_4);
   fChain->SetBranchAddress("iso_4", &iso_4, &b_iso_4);
   fChain->SetBranchAddress("gen_match_4", &gen_match_4, &b_gen_match_4);
   fChain->SetBranchAddress("isGlobal_4", &isGlobal_4, &b_isGlobal_4);
   fChain->SetBranchAddress("isTracker_4", &isTracker_4, &b_isTracker_4);
   fChain->SetBranchAddress("ip3d_4", &ip3d_4, &b_ip3d_4);
   fChain->SetBranchAddress("decayMode_1", &decayMode_1, &b_decayMode_1);
   fChain->SetBranchAddress("decayMode_2", &decayMode_2, &b_decayMode_2);
   fChain->SetBranchAddress("pt_tt", &pt_tt, &b_pt_tt);
   fChain->SetBranchAddress("mt_tot", &mt_tot, &b_mt_tot);
   fChain->SetBranchAddress("m_vis", &m_vis, &b_m_vis);
   fChain->SetBranchAddress("mDCH1_sv", &mDCH1_sv, &b_mDCH1_sv);
   fChain->SetBranchAddress("mtDCH1_sv", &mtDCH1_sv, &b_mtDCH1_sv);
   fChain->SetBranchAddress("mDCH2_sv", &mDCH2_sv, &b_mDCH2_sv);
   fChain->SetBranchAddress("mtDCH2_sv", &mtDCH2_sv, &b_mtDCH2_sv);
   fChain->SetBranchAddress("mDCH1_sv4", &mDCH1_sv4, &b_mDCH1_sv4);
   fChain->SetBranchAddress("mtDCH1_sv4", &mtDCH1_sv4, &b_mtDCH1_sv4);
   fChain->SetBranchAddress("mDCH2_sv4", &mDCH2_sv4, &b_mDCH2_sv4);
   fChain->SetBranchAddress("mtDCH2_sv4", &mtDCH2_sv4, &b_mtDCH2_sv4);
   fChain->SetBranchAddress("H_DR", &H_DR, &b_H_DR);
   fChain->SetBranchAddress("AMass", &AMass, &b_AMass);
   fChain->SetBranchAddress("H_LT", &H_LT, &b_H_LT);
   fChain->SetBranchAddress("dRl1H", &dRl1H, &b_dRl1H);
   fChain->SetBranchAddress("dRl2H", &dRl2H, &b_dRl2H);
   fChain->SetBranchAddress("dRlH", &dRlH, &b_dRlH);
   fChain->SetBranchAddress("dPhil1H", &dPhil1H, &b_dPhil1H);
   fChain->SetBranchAddress("dPhil2H", &dPhil2H, &b_dPhil2H);
   fChain->SetBranchAddress("dPhilH", &dPhilH, &b_dPhilH);
   fChain->SetBranchAddress("mll", &mll, &b_mll);
   fChain->SetBranchAddress("mll2", &mll2, &b_mll2);
   fChain->SetBranchAddress("Z_Pt", &Z_Pt, &b_Z_Pt);
   fChain->SetBranchAddress("Z_DR", &Z_DR, &b_Z_DR);
   fChain->SetBranchAddress("Z_SS", &Z_SS, &b_Z_SS);
   fChain->SetBranchAddress("pt_1", &pt_1, &b_pt_1);
   fChain->SetBranchAddress("m_1", &m_1, &b_m_1);
   fChain->SetBranchAddress("m_1_tr", &m_1_tr, &b_m_1_tr);
   fChain->SetBranchAddress("pt_1_tr", &pt_1_tr, &b_pt_1_tr);
   fChain->SetBranchAddress("phi_1", &phi_1, &b_phi_1);
   fChain->SetBranchAddress("phi_1_tr", &phi_1_tr, &b_phi_1_tr);
   fChain->SetBranchAddress("eta_1", &eta_1, &b_eta_1);
   fChain->SetBranchAddress("eta_1_tr", &eta_1_tr, &b_eta_1_tr);
   fChain->SetBranchAddress("pt_2", &pt_2, &b_pt_2);
   fChain->SetBranchAddress("m_2", &m_2, &b_m_2);
   fChain->SetBranchAddress("m_2_tr", &m_2_tr, &b_m_2_tr);
   fChain->SetBranchAddress("pt_2_tr", &pt_2_tr, &b_pt_2_tr);
   fChain->SetBranchAddress("phi_2", &phi_2, &b_phi_2);
   fChain->SetBranchAddress("phi_2_tr", &phi_2_tr, &b_phi_2_tr);
   fChain->SetBranchAddress("eta_2", &eta_2, &b_eta_2);
   fChain->SetBranchAddress("eta_2_tr", &eta_2_tr, &b_eta_2_tr);
   fChain->SetBranchAddress("iso_1", &iso_1, &b_iso_1);
   fChain->SetBranchAddress("iso_2", &iso_2, &b_iso_2);
   fChain->SetBranchAddress("q_1", &q_1, &b_q_1);
   fChain->SetBranchAddress("q_2", &q_2, &b_q_2);
   fChain->SetBranchAddress("L1PreFiringWeight_Nom", &L1PreFiringWeight_Nom, &b_L1PreFiringWeight_Nom);
   fChain->SetBranchAddress("L1PreFiringWeight_Up", &L1PreFiringWeight_Up, &b_L1PreFiringWeight_Up);
   fChain->SetBranchAddress("L1PreFiringWeight_Down", &L1PreFiringWeight_Down, &b_L1PreFiringWeight_Down);
   fChain->SetBranchAddress("d0_1", &d0_1, &b_d0_1);
   fChain->SetBranchAddress("dZ_1", &dZ_1, &b_dZ_1);
   fChain->SetBranchAddress("d0_2", &d0_2, &b_d0_2);
   fChain->SetBranchAddress("dZ_2", &dZ_2, &b_dZ_2);
   fChain->SetBranchAddress("isGlobal_1", &isGlobal_1, &b_isGlobal_1);
   fChain->SetBranchAddress("isGlobal_2", &isGlobal_2, &b_isGlobal_2);
   fChain->SetBranchAddress("isTracker_1", &isTracker_1, &b_isTracker_1);
   fChain->SetBranchAddress("isTracker_2", &isTracker_2, &b_isTracker_2);
   fChain->SetBranchAddress("MET_pt_UnclUp", &MET_pt_UnclUp, &b_MET_pt_UnclUp);
   fChain->SetBranchAddress("MET_phi_UnclUp", &MET_phi_UnclUp, &b_MET_phi_UnclUp);
   fChain->SetBranchAddress("MET_pt_UnclDown", &MET_pt_UnclDown, &b_MET_pt_UnclDown);
   fChain->SetBranchAddress("MET_phi_UnclDown", &MET_phi_UnclDown, &b_MET_phi_UnclDown);
   fChain->SetBranchAddress("met_UnclX", &met_UnclX, &b_met_UnclX);
   fChain->SetBranchAddress("met_UnclY", &met_UnclY, &b_met_UnclY);
   fChain->SetBranchAddress("MET_T1Smear_pt", &MET_T1Smear_pt, &b_MET_T1Smear_pt);
   fChain->SetBranchAddress("MET_T1Smear_phi", &MET_T1Smear_phi, &b_MET_T1Smear_phi);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("metphi", &metphi, &b_metphi);
   fChain->SetBranchAddress("metNoCor", &metNoCor, &b_metNoCor);
   fChain->SetBranchAddress("metphiNoCor", &metphiNoCor, &b_metphiNoCor);
   fChain->SetBranchAddress("metNoTauES", &metNoTauES, &b_metNoTauES);
   fChain->SetBranchAddress("metphiNoTauES", &metphiNoTauES, &b_metphiNoTauES);
   fChain->SetBranchAddress("metcov00", &metcov00, &b_metcov00);
   fChain->SetBranchAddress("metcov01", &metcov01, &b_metcov01);
   fChain->SetBranchAddress("metcov10", &metcov10, &b_metcov10);
   fChain->SetBranchAddress("metcov11", &metcov11, &b_metcov11);
   fChain->SetBranchAddress("isTrig_2", &isTrig_2, &b_isTrig_2);
   fChain->SetBranchAddress("isTrig_1", &isTrig_1, &b_isTrig_1);
   fChain->SetBranchAddress("isDoubleTrig", &isDoubleTrig, &b_isDoubleTrig);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("nbtagL", &nbtagL, &b_nbtagL);
   fChain->SetBranchAddress("nbtagM", &nbtagM, &b_nbtagM);
   fChain->SetBranchAddress("nbtagT", &nbtagT, &b_nbtagT);
   fChain->SetBranchAddress("HTXS_Higgs_cat", &HTXS_Higgs_cat, &b_HTXS_Higgs_cat);
   fChain->SetBranchAddress("HTXS_Higgs_pt", &HTXS_Higgs_pt, &b_HTXS_Higgs_pt);
   fChain->SetBranchAddress("jflavour", jflavour, &b_jflavour);
   fChain->SetBranchAddress("jeta", jeta, &b_jeta);
   fChain->SetBranchAddress("jpt", jpt, &b_jpt);
   fChain->SetBranchAddress("btagDeep", btagDeep, &b_btagDeep);
   fChain->SetBranchAddress("nupt_1", &nupt_1, &b_nupt_1);
   fChain->SetBranchAddress("nupt_2", &nupt_2, &b_nupt_3);
   fChain->SetBranchAddress("nupt_3", &nupt_3, &b_nupt_2);
   fChain->SetBranchAddress("nupt_4", &nupt_4, &b_nupt_4);
   fChain->SetBranchAddress("nueta_1", &nueta_1, &b_nueta_1);
   fChain->SetBranchAddress("nueta_2", &nueta_2, &b_nueta_3);
   fChain->SetBranchAddress("nueta_3", &nueta_3, &b_nueta_2);
   fChain->SetBranchAddress("nueta_4", &nueta_4, &b_nueta_4);
   fChain->SetBranchAddress("nuphi_1", &nuphi_1, &b_nuphi_1);
   fChain->SetBranchAddress("nuphi_2", &nuphi_2, &b_nuphi_3);
   fChain->SetBranchAddress("nuphi_3", &nuphi_3, &b_nuphi_2);
   fChain->SetBranchAddress("nuphi_4", &nuphi_4, &b_nuphi_4);
   fChain->SetBranchAddress("nuM_1", &nuM_1, &b_nuM_1);
   fChain->SetBranchAddress("nuM_2", &nuM_2, &b_nuM_3);
   fChain->SetBranchAddress("nuM_3", &nuM_3, &b_nuM_2);
   fChain->SetBranchAddress("nuM_4", &nuM_4, &b_nuM_4);
   Notify();
}

Bool_t MyBranch::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MyBranch::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MyBranch::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MyBranch_cxx
