def Fill2L(self, entry, SVFit, cat,gen_cat,br_weight, idx_DCH1, isMC, era, doUncertainties=False ,  met_pt=-99, met_phi=-99, systIndex=0, tMass=[], tPt=[], eMass=[], ePt=[], mMass=[], mPt=[], proc="EOY") :

        ''' - jl3 and jl4 point to the selected tau candidates according to the table below.
            - if e.g., dch_2 = 'et', the jl3 points to the electron list and jl4 points to the tau list.
            - Lep1 and Lep2 are TLorentz vectors for the members of the dilepton pair
        '''
        SystIndex = int(systIndex)

        dch_1 = cat
        
        if SystIndex ==0 : 

            is_trig_1, is_trig_2, is_Dtrig_1 = 0., 0., 0.
            TrigListLep_1 = []
            TrigListTau_1 = []
            hltListLep_1  = []
            hltListLepSubL_1  = []

            TrigListLep_1, hltListLep_1, hltListLepSubL_1  = GF.findSingleLeptTriggerDCH(idx_DCH1, entry, dch_1, era)

            TrigListLep_1 = list(dict.fromkeys(TrigListLep_1))
            #if len(hltListLep) > 0 or len(hltListLepSubL)>0 :     print GF.printEvent(entry), SystIndex


            if len(hltListLep_1) > 0 and  len(hltListLepSubL_1) == 0 :
                is_trig_1 = 1
            if len(hltListLep_1) == 0 and len(hltListLepSubL_1) > 0 :
                is_trig_1 = -1
            if len(hltListLep_1) > 0 and len(hltListLepSubL_1)>0 :
                is_trig_1 = 2

            self.whichTriggerWord[0]=0
            self.whichTriggerWordSubL[0]=0

            #if len(TrigListLep) >0 : print 'TrigerList ===========>', TrigListLep, idx_DCH1, hltListLep, dch_1, 'istrig_1', is_trig_1, 'istrig_2', is_trig_2, 'lenTrigList', len(TrigListLep),  'lenLept', len(idx_DCH1), 'idx_DCH1_0', idx_DCH1[0], 'TrigList_0', TrigListLep[0], hltListLep
            
            for i,bit in enumerate(hltListLep_1):
                    
                if bit : 
                    self.whichTriggerWord[0] += 2**i

            for j,bitt in enumerate(hltListLepSubL_1):
                if bitt : self.whichTriggerWordSubL[0] += 2**j


            #if dch_1=='ee' and entry.luminosityBlock==90 and entry.event==8904: print self.whichTriggerWord[0], 'hlt', hltListLep, 'hltsub', hltListLepSubL
            #print cat, self.whichTriggerWord
            # dch_2 = 'mt', 'et', 'tt', or 'em'
            
            self.entries += 1

            self.run[0]  = entry.run
            self.nElectron[0]  = entry.nElectron
            self.nMuon[0]  = entry.nMuon
            self.nTau[0]  = entry.nTau
            self.lumi[0] = entry.luminosityBlock 
            self.evt[0]  = entry.event
            self.iso_1[0]  = -99
            self.iso_2[0]  = -99
            self.q_1[0]  = -99
            self.q_2[0]  = -99
            self.isGlobal_1[0]  = -99
            self.isGlobal_2[0]  = -99
            try:
                self.L1PreFiringWeight_Nom[0] = entry.L1PreFiringWeight_Nom
                self.L1PreFiringWeight_Up[0] = entry.L1PreFiringWeight_Up
                self.L1PreFiringWeight_Down[0] = entry.L1PreFiringWeight_Dn
            except AttributeError : 
                self.L1PreFiringWeight_Nom[0] = 1
                self.L1PreFiringWeight_Up[0] = 1
                self.L1PreFiringWeight_Down[0] = 1

                
            '''self.tightId_1[0]       = -1 
            self.mediumId_1[0]       = -1 
            self.mediumPromptId_1[0]   = -1
            self.looseId_1[0]       = -1
            '''
            self.isGlobal_1[0]      = -1
            self.isTracker_1[0]     = -1

            '''self.tightId_2[0]       = -1 
            self.mediumId_2[0]       = -1 
            self.mediumPromptId_2[0]   = -1
            self.looseId_2[0]       = -1
            '''
            self.isGlobal_2[0]      = -1
            self.isTracker_2[0]     = -1

            self.decayMode_3[0]        = -1
            '''self.idDecayModeNewDMs_3[0]= -1
            self.idDeepTau2017v2p1VSe_3[0] = -1
            self.idDeepTau2017v2p1VSjet_3[0] = -1
            self.idDeepTau2017v2p1VSmu_3[0] = -1
            self.idMVAnewDM2017v2_3[0] = -1
            self.rawMVAnewDM2017v2_3[0] = -1
            '''
            '''self.mediumId_3[0]       = -1 
            self.mediumPromptId_3[0]   = -1
            self.looseId_3[0]       = -1
            '''
            self.isGlobal_3[0]      = -1
            self.isTracker_3[0]     = -1
            self.ip3d_3[0]          = -1

            self.decayMode_4[0]      = -1
            '''self.idDecayModeNewDMs_4[0] = -1
            self.idDeepTau2017v2p1VSe_4[0] = -1
            self.idDeepTau2017v2p1VSjet_4[0] = -1
            self.idDeepTau2017v2p1VSmu_4[0] = -1
            self.idMVAnewDM2017v2_4[0] = -1
            self.rawMVAnewDM2017v2_4[0] = -1
            '''
            '''self.mediumId_4[0]       = -1 
            self.mediumPromptId_4[0]   = -1
            self.looseId_4[0]       = -1
            '''
            self.isGlobal_4[0]      = -1
            self.isTracker_4[0]     = -1
            self.ip3d_4[0]          = -1
            self.GenPart_statusFlags_1[0]    = -1
            self.GenPart_status_1[0]    = -1
            self.GenPart_statusFlags_2[0]    = -1
            self.GenPart_status_2[0]    = -1
            self.GenPart_statusFlags_3[0]    = -1
            self.GenPart_status_3[0]    = -1
            self.GenPart_statusFlags_4[0]    = -1
            self.GenPart_status_4[0]    = -1
            self.gen_match_1[0] = -1
            self.gen_match_2[0] = -1
            self.gen_match_3[0] = -1
            self.gen_match_4[0] = -1
            #self.gen_match_5[0] = -1


            try :
                self.weight[0]           = entry.genWeight
                self.LHEweight[0]        = entry.LHEWeight_originalXWGTUP
                self.Generator_weight[0] = entry.Generator_weight
                self.LHE_Njets[0]        = ord(entry.LHE_Njets)
                if SystIndex == 0 : 
                    for i in range(0, int(entry.nLHEScaleWeight)) : 
                        self.LHEScaleWeights[i] = entry.LHEScaleWeight[i]

                self.nPU[0]  = entry.Pileup_nPU
                self.nPUEOOT[0]  = entry.Pileup_sumEOOT
                self.nPULOOT[0]  = entry.Pileup_sumLOOT
                self.nPUtrue[0]  = entry.Pileup_nTrueInt
                self.nPV[0]  = entry.PV_npvs
                self.nPVGood[0]  = entry.PV_npvsGood
                            
            except AttributeError :
                self.weight[0]           = 1. 
                self.weightPU[0]         = -1
                self.weightPUtrue[0]     = -1
                self.LHEweight[0]        = 1. 
                self.Generator_weight[0] = 1.
                self.LHE_Njets[0] = -1
                self.nPU[0]  = -1
                self.nPUEOOT[0]  = -1
                self.nPULOOT[0]  = -1
                self.nPUtrue[0]  = -1
                self.nPV[0]  = -1
                self.nPVGood[0]  = -1

        goodElectronList = tauFunDCH.makeGoodElectronList(entry)
        goodMuonList = tauFunDCH.makeGoodMuonList(entry)
        #goodTauList = tauFunDCH.makeGoodTauList(entry)
        self.nGoodElectron[0] = len(goodElectronList)
        self.nGoodMuon[0]     = len(goodMuonList)
        #self.nGoodTau[0]      = len(goodTauList)
        # pack trigger bits into integer word

        e = entry

        '''
        List from Cecile 
        single ele 2016: HLT Ele25 eta2p1 WPTight Gsf v and cut pt(ele)>26, eta(ele)<2.1
        single ele 2017: HLT Ele27 WPTight Gsf v, HLT Ele32 WPTight Gsf v, HLT Ele35 WPTight Gsf v and cut pt(ele)>28, eta(ele)<2.1
        single ele 2018: HLT Ele32 WPTight Gsf v, HLT Ele35 WPTight Gsf v and cut pt(ele)>33, eta(ele)<2.1
        '''
        
        if int(SystIndex) ==0 : 
            bits=[]
            try : bits.append(e.HLT_Ele25_eta2p1_WPTight_Gsf)
            except AttributeError : bits.append(False)
            try : bits.append(e.HLT_Ele27_WPTight_Gsf)
            except AttributeError : bits.append(False)
            try : bits.append(e.HLT_Ele32_WPTight_Gsf)
            except AttributeError : bits.append(False)
            try : bits.append(e.HLT_Ele35_WPTight_Gsf)
            except AttributeError : bits.append(False)
            # pad upper bits in this byte with zeros (False) 
            #for i in range(4) :
            #    bits.append(False)
                
            try : bits.append(e.HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL)
            except AttributeError : bits.append(False)
            try : bits.append(e.HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ)
            except AttributeError : bits.append(False) 

            self.electronTriggerWord[0] = 0
            for i, bit in enumerate(bits) :
                if bit : self.electronTriggerWord[0] += 2**i

            '''
            List from Cecile 
            single mu 2016: HLT IsoMu22 v, HLT IsoMu22 eta2p1 v, HLT IsoTkMu22 v, HLT IsoTkMu22 eta2p1 v and cut pt(mu)>23, eta(mu)<2.1
            single mu 2017: HLT IsoMu24 v, HLT IsoMu27 v and cut pt(mu)>25, eta(mu)<2.4
            single mu 2018: HLT IsoMu24 v, HLT IsoMu27 v and cut pt(mu)>25, eta(mu)<2.4
            '''
            bits=[]
            try : bits.append(e.HLT_IsoMu22)
            except AttributeError : bits.append(False)
            try : bits.append(e.HLT_IsoMu22_eta2p1)
            except AttributeError : bits.append(False)
            try : bits.append(e.HLT_IsoTkMu22)
            except AttributeError : bits.append(False)
            try : bits.append(e.HLT_IsoTkMu22_eta2p1)
            except AttributeError : bits.append(False)
            try : bits.append(e.HLT_IsoMu24)
            except AttributeError : bits.append(False) 
            try : bits.append(e.HLT_IsoMu27)
            except AttributeError : bits.append(False) 

            #for i in range(2) :
            #    bits.append(False)                             # pad remaining bit in this bit 
           
            try : bits.append(e.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ)
            except AttributeError : bits.append(False) 
            try : bits.append(e.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8)
            except AttributeError : bits.append(False)
            try : bits.append(e.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)
            except AttributeError : bits.append(False)
            try : bits.append(e.HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ)
            except AttributeError : bits.append(False) 
            try : bits.append(e.HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_Mass8)
            except AttributeError : bits.append(False) 

            self.muonTriggerWord[0] = 0
            for i, bit in enumerate(bits) :
                if bit : self.muonTriggerWord[0] += 2**i

        yearin = era
        if isMC :
        	hlt_pu = "Collisions18_UltraLegacy_goldenJSON"
        	if '2016' in era : hlt_pu='Collisions16_UltraLegacy_goldenJSON'
        	if '2017' in era : hlt_pu='Collisions17_UltraLegacy_goldenJSON'
        	self.weightPUtruejson[0] = self.evaluatorPU[hlt_pu].evaluate(entry.Pileup_nTrueInt, "nominal" )
        	self.weightPUtruejson_up[0] = self.evaluatorPU[hlt_pu].evaluate(entry.Pileup_nTrueInt, "up" )
        	self.weightPUtruejson_down[0] = self.evaluatorPU[hlt_pu].evaluate(entry.Pileup_nTrueInt, "down" )

        	if '2016' in era and 'pre' in era : yearin='2016preVFP'
        	if '2016' in era and 'pre' not in era : yearin='2016postVFP'
                
                
        jl1 = idx_DCH1[0]
        jl2 = idx_DCH1[1]
        Lep1, Lep2 = TLorentzVector(), TLorentzVector()
        #relIso 
        if dch_1 == 'ee' :
            self.iso_1[0]  = entry.Electron_pfRelIso03_all[jl1]
            self.iso_2[0]  = entry.Electron_pfRelIso03_all[jl2]
            self.q_1[0]  = entry.Electron_charge[jl1]
            self.q_2[0]  = entry.Electron_charge[jl2]
            self.d0_1[0]   = entry.Electron_dxy[jl1]
            self.dZ_1[0]   = entry.Electron_dz[jl1]
            self.d0_2[0]   = entry.Electron_dxy[jl2]
            self.dZ_2[0]   = entry.Electron_dz[jl2]
            #self.Electron_mvaFall17V2noIso_WP90_1[0]  = entry.Electron_mvaFall17V2noIso_WP90[jl1]
            #self.Electron_mvaFall17V2noIso_WP90_2[0]  = entry.Electron_mvaFall17V2noIso_WP90[jl2]                     
            if SystIndex ==0 and  isMC:
                self.pt_uncor_1[0] = ePt[jl1]
                self.m_uncor_1[0] = eMass[jl1]
                self.pt_uncor_2[0] = ePt[jl2]
                self.m_uncor_2[0] = eMass[jl2]

               # fill genMatch for tau(ele)
            if isMC:
                idx_genEle = entry.Electron_genPartIdx[jl1]

                # if idx_genEle = -1, no match was found
                if idx_genEle >= 0:
                    idx_genEle_mom      = entry.GenPart_genPartIdxMother[idx_genEle]
                    self.pt_1_tr[0]     = entry.GenPart_pt[idx_genEle]
                    self.phi_1_tr[0]    = entry.GenPart_phi[idx_genEle]
                    self.eta_1_tr[0]    = entry.GenPart_eta[idx_genEle]
                    self.GenPart_statusFlags_1[0]    = entry.GenPart_statusFlags[idx_genEle]
                    self.GenPart_status_1[0]    = entry.GenPart_status[idx_genEle]

                try : self.gen_match_1[0] = ord(chr(entry.Electron_genPartFlav[jl1]))
                except AttributeError : self.gen_match_1[0] = -1
            Lep1.SetPtEtaPhiM(entry.Electron_pt[jl1], entry.Electron_eta[jl1], entry.Electron_phi[jl1], entry.Electron_mass[jl1])

               # fill genMatch for tau(ele)
            if isMC:
                idx_genEle = entry.Electron_genPartIdx[jl2]

                # if idx_genEle = -1, no match was found
                if idx_genEle >= 0:
                    idx_genEle_mom      = entry.GenPart_genPartIdxMother[idx_genEle]
                    self.pt_2_tr[0]     = entry.GenPart_pt[idx_genEle]
                    self.phi_2_tr[0]    = entry.GenPart_phi[idx_genEle]
                    self.eta_2_tr[0]    = entry.GenPart_eta[idx_genEle]
                    self.GenPart_statusFlags_2[0]    = entry.GenPart_statusFlags[idx_genEle]
                    self.GenPart_status_2[0]    = entry.GenPart_status[idx_genEle]

                try : self.gen_match_2[0] = ord(chr(entry.Electron_genPartFlav[jl2]))
                except AttributeError : self.gen_match_2[0] = -1
            Lep2.SetPtEtaPhiM(entry.Electron_pt[jl2], entry.Electron_eta[jl2], entry.Electron_phi[jl2], entry.Electron_mass[jl2])

        # Fill variables for Leg3 and Leg4, where 3->tau(ele) and 4->tau(mu)
        elif dch_1 == 'em' :
            self.iso_1[0]  = entry.Electron_pfRelIso03_all[jl1]
            self.iso_2[0]  = entry.Muon_pfRelIso03_all[jl2]
            self.q_1[0]  = entry.Electron_charge[jl1]
            self.q_2[0]  = entry.Muon_charge[jl2]
            self.d0_1[0]   = entry.Electron_dxy[jl1]
            self.dZ_1[0]   = entry.Electron_dz[jl1]
            self.d0_2[0]   = entry.Muon_dxy[jl2]
            self.dZ_2[0]   = entry.Muon_dz[jl2]
            #self.Electron_mvaFall17V2noIso_WP90_1[0]  = entry.Electron_mvaFall17V2noIso_WP90[jl1]
            ''' 
            self.looseId_2[0]   = entry.Muon_looseId[jl2] 
            self.tightId_2[0]      = entry.Muon_tightId[jl2] 
            self.mediumId_2[0]   = entry.Muon_mediumId[jl2]
            self.mediumPromptId_2[0]   = entry.Muon_mediumPromptId[jl2] 
            '''

            self.isGlobal_2[0]      = entry.Muon_isGlobal[jl2]
            self.isTracker_2[0]     = entry.Muon_isTracker[jl2]
            #self.ip3d_2[0]       = entry.Muon_ip3d[jl2]
            
            if SystIndex ==0 and  isMC: 
                self.pt_uncor_1[0] = ePt[jl1]
                self.m_uncor_1[0] = eMass[jl1]
                self.pt_uncor_2[0] = mPt[jl2]
                self.m_uncor_2[0] = mMass[jl2]
            
            # fill genMatch for tau(ele)
            if isMC:
                idx_genEle = entry.Electron_genPartIdx[jl1]

                # if idx_genEle = -1, no match was found
                if idx_genEle >= 0:
                        idx_genEle_mom      = entry.GenPart_genPartIdxMother[idx_genEle]
                        self.pt_1_tr[0]     = entry.GenPart_pt[idx_genEle]
                        self.phi_1_tr[0]    = entry.GenPart_phi[idx_genEle]
                        self.eta_1_tr[0]    = entry.GenPart_eta[idx_genEle]
                        self.GenPart_statusFlags_1[0]    = entry.GenPart_statusFlags[idx_genEle]
                        self.GenPart_status_1[0]    = entry.GenPart_status[idx_genEle]

                try : self.gen_match_1[0] = ord(chr(entry.Electron_genPartFlav[jl1]))
                except AttributeError : self.gen_match_1[0] = -1

            Lep1.SetPtEtaPhiM(entry.Electron_pt[jl1], entry.Electron_eta[jl1], entry.Electron_phi[jl1], entry.Electron_mass[jl1])

            # fill genMatch for tau(mu)
            if isMC:
                idx_genMu = entry.Muon_genPartIdx[jl2]
            
                # if idx_genMu = -1, no match was found
                if idx_genMu >= 0:
                    idx_genMu_mom       = entry.GenPart_genPartIdxMother[idx_genMu]
                    self.pt_2_tr[0]     = entry.GenPart_pt[idx_genMu]
                    self.phi_2_tr[0]    = entry.GenPart_phi[idx_genMu]
                    self.eta_2_tr[0]    = entry.GenPart_eta[idx_genMu]
                    self.GenPart_statusFlags_2[0]    = entry.GenPart_statusFlags[idx_genMu]
                    self.GenPart_status_2[0]    = entry.GenPart_status[idx_genMu]
                try : self.gen_match_2[0] = ord(chr(entry.Muon_genPartFlav[jl2]))
                except AttributeError : self.gen_match_2[0] = -1

            Lep2.SetPtEtaPhiM(entry.Muon_pt[jl2], entry.Muon_eta[jl2], entry.Muon_phi[jl2], entry.Muon_mass[jl2])

        # Fill variables for Leg3, where 3->tau(ele) and 4->tau(had)
        elif dch_1 == 'et' :
            self.iso_1[0]  = entry.Electron_pfRelIso03_all[jl1]
            self.q_1[0]  = entry.Electron_charge[jl1]
            self.q_2[0]  = entry.Tau_charge[jl2]
            self.d0_1[0]   = entry.Electron_dxy[jl1]
            self.dZ_1[0]   = entry.Electron_dz[jl1]
            self.d0_2[0]   = entry.Tau_dxy[jl2]
            self.dZ_2[0]   = entry.Tau_dz[jl2]
            #self.Electron_mvaFall17V2noIso_WP90_1[0]  = entry.Electron_mvaFall17V2noIso_WP90[jl1]    

            if SystIndex ==0 and  isMC: 
                    self.pt_uncor_1[0] = ePt[jl1]
                    self.m_uncor_1[0] = eMass[jl1]
                    self.pt_uncor_2[0] = tPt[jl2]
                    self.m_uncor_2[0] = tMass[jl2]
            
            # Fill genMatch variables for tau(ele)
            if isMC:
                idx_genEle = entry.Electron_genPartIdx[jl1]

                # if idx_genMu = -1, no match was found
                if idx_genEle >= 0:
                    idx_genEle_mom      = entry.GenPart_genPartIdxMother[idx_genEle]
                    self.pt_1_tr[0]     = entry.GenPart_pt[idx_genEle]
                    self.phi_1_tr[0]    = entry.GenPart_phi[idx_genEle]
                    self.eta_1_tr[0]    = entry.GenPart_eta[idx_genEle]
                    self.GenPart_statusFlags_1[0]    = entry.GenPart_statusFlags[idx_genEle]
                    self.GenPart_status_1[0]    = entry.GenPart_status[idx_genEle]

                try: self.gen_match_1[0] = ord(chr(entry.Electron_genPartFlav[jl1]))
                except AttributeError: self.gen_match_1[0] = -1
            
            #print '---------------------------->', self.pt_1[0], ePt[jl1], entry.Tau_pt[jl2], tPt[jl2] , jl1, jl2, cat, entry.event, SystIndex
            Lep1.SetPtEtaPhiM(entry.Electron_pt[jl1],entry.Electron_eta[jl1], entry.Electron_phi[jl1], entry.Electron_mass[jl1])
            tmass= self.tauMass
            if entry.Tau_decayMode[jl2] == 0 : tmass= 0.13957 #pion mass
            else: tmass = entry.Tau_mass[jl2]
            Lep2.SetPtEtaPhiM(entry.Tau_pt[jl2],entry.Tau_eta[jl2],entry.Tau_phi[jl2],tmass)

        # Fill variables for Leg3 and Leg4, where 3->tau(mu) and 4->tau(mu)
        elif dch_1 == 'mm' :
            self.iso_1[0]  = entry.Muon_pfRelIso04_all[jl1]
            self.iso_2[0]  = entry.Muon_pfRelIso04_all[jl2]
            self.q_1[0]  = entry.Muon_charge[jl1]
            self.q_2[0]  = entry.Muon_charge[jl2]
            self.d0_1[0]   = entry.Muon_dxy[jl1]
            self.dZ_1[0]   = entry.Muon_dz[jl1]
            self.d0_2[0]   = entry.Muon_dxy[jl2]
            self.dZ_2[0]   = entry.Muon_dz[jl2]
            '''self.looseId_1[0]   = entry.Muon_looseId[jl1] 
            self.looseId_2[0]   = entry.Muon_looseId[jl2] 
            self.tightId_1[0]        = entry.Muon_tightId[jl1]
            self.tightId_2[0]        = entry.Muon_tightId[jl2]
            self.mediumId_1[0]   = entry.Muon_mediumId[jl1] 
            self.mediumId_2[0]   = entry.Muon_mediumId[jl2] 
            self.mediumPromptId_1[0]   = entry.Muon_mediumPromptId[jl1] 
            self.mediumPromptId_2[0]   = entry.Muon_mediumPromptId[jl2] 
            '''
            self.isGlobal_1[0]      = entry.Muon_isGlobal[jl1]
            self.isTracker_1[0]     = entry.Muon_isTracker[jl1]
            #self.ip3d_1[0]       = entry.Muon_ip3d[jl1]
            self.isGlobal_2[0]      = entry.Muon_isGlobal[jl2]
            self.isTracker_2[0]     = entry.Muon_isTracker[jl2]
            #self.ip3d_2[0]       = entry.Muon_ip3d[jl2]
            
            if SystIndex ==0 and  isMC: 
                self.pt_uncor_1[0] = mPt[jl1]
                self.m_uncor_1[0] = mMass[jl1]
                self.pt_uncor_2[0] = mPt[jl2]
                self.m_uncor_2[0] = mMass[jl2]
        
            # fill genMatch for tau(mu)
            if isMC:
                    idx_genMu = entry.Muon_genPartIdx[jl1]
            
                    # if idx_genMu = -1, no match was found
                    if idx_genMu >= 0:
                        idx_genMu_mom       = entry.GenPart_genPartIdxMother[idx_genMu]
                        self.pt_1_tr[0]     = entry.GenPart_pt[idx_genMu]
                        self.phi_1_tr[0]    = entry.GenPart_phi[idx_genMu]
                        self.eta_1_tr[0]    = entry.GenPart_eta[idx_genMu]
                        self.GenPart_statusFlags_1[0]    = entry.GenPart_statusFlags[idx_genMu]
                        self.GenPart_status_1[0]    = entry.GenPart_status[idx_genMu]
                    try : self.gen_match_1[0] = ord(chr(entry.Muon_genPartFlav[jl1]))
                    except AttributeError : self.gen_match_1[0] = -1

            Lep1.SetPtEtaPhiM(entry.Muon_pt[jl1], entry.Muon_eta[jl1], entry.Muon_phi[jl1], entry.Muon_mass[jl1])

            # fill genMatch for tau(mu)
            if isMC:
                idx_genMu = entry.Muon_genPartIdx[jl2]
        
                # if idx_genMu = -1, no match was found
                if idx_genMu >= 0:
                    idx_genMu_mom       = entry.GenPart_genPartIdxMother[idx_genMu]
                    self.pt_2_tr[0]     = entry.GenPart_pt[idx_genMu]
                    self.phi_2_tr[0]    = entry.GenPart_phi[idx_genMu]
                    self.eta_2_tr[0]    = entry.GenPart_eta[idx_genMu]
                    self.GenPart_statusFlags_2[0]    = entry.GenPart_statusFlags[idx_genMu]
                    self.GenPart_status_2[0]    = entry.GenPart_status[idx_genMu]
                try : self.gen_match_2[0] = ord(chr(entry.Muon_genPartFlav[jl2]))
                except AttributeError : self.gen_match_2[0] = -1

            Lep2.SetPtEtaPhiM(entry.Muon_pt[jl2], entry.Muon_eta[jl2], entry.Muon_phi[jl2], entry.Muon_mass[jl2])
           
        # Fill variables for Leg3, where 3->tau(mu) and 4->tau(had)
        elif dch_1 == 'mt' :
            self.iso_1[0]  = entry.Muon_pfRelIso04_all[jl1]
            self.q_1[0]  = entry.Muon_charge[jl1]
            self.q_2[0]  = entry.Tau_charge[jl2]
            self.d0_1[0]   = entry.Muon_dxy[jl1]
            self.dZ_1[0]   = entry.Muon_dz[jl1]
            self.d0_2[0]   = entry.Tau_dxy[jl2]
            self.dZ_2[0]   = entry.Tau_dz[jl2]
            '''self.tightId_1[0]      = entry.Muon_tightId[jl1]
            self.mediumId_1[0]       = entry.Muon_mediumId[jl1]
            self.mediumPromptId_1[0]   = entry.Muon_mediumPromptId[jl1]
            self.looseId_1[0]       = entry.Muon_looseId[jl1]
            '''
            self.isGlobal_1[0]      = entry.Muon_isGlobal[jl1]
            self.isTracker_1[0]     = entry.Muon_isTracker[jl1]
            #self.ip3d_1[0]       = entry.Muon_ip3d[jl1]
            if SystIndex ==0 and isMC : 
                    self.pt_uncor_1[0] = mPt[jl1]
                    self.m_uncor_1[0] = mMass[jl1]
                    self.pt_uncor_2[0] = tPt[jl2]
                    self.m_uncor_2[0] = tMass[jl2]
            
            # fill genMatch for tau(mu)
            if isMC:
                idx_genMu = entry.Muon_genPartIdx[jl1]
        
               # if idx_genMu = -1, no match was found
                if idx_genMu >= 0:
                    idx_genMu_mom       = entry.GenPart_genPartIdxMother[idx_genMu]
                    self.pt_1_tr[0]     = entry.GenPart_pt[idx_genMu]
                    self.phi_1_tr[0]    = entry.GenPart_phi[idx_genMu]
                    self.eta_1_tr[0]    = entry.GenPart_eta[idx_genMu]
                    self.GenPart_statusFlags_1[0]    = entry.GenPart_statusFlags[idx_genMu]
                    self.GenPart_status_1[0]    = entry.GenPart_status[idx_genMu]

            try : self.gen_match_1[0] = ord(chr(entry.Muon_genPartFlav[jl1]))
            except AttributeError : self.gen_match_1[0] = -1

            Lep1.SetPtEtaPhiM(entry.Muon_pt[jl1], entry.Muon_eta[jl1], entry.Muon_phi[jl1], entry.Muon_mass[jl1])
            tmass= self.tauMass
            if entry.Tau_decayMode[jl2] == 0 : tmass= 0.13957 #pion mass
            else: tmass = entry.Tau_mass[jl2]
            Lep2.SetPtEtaPhiM(entry.Tau_pt[jl2],  entry.Tau_eta[jl2],  entry.Tau_phi[jl2], tmass)

        
        # Fill variables for Leg3 and Leg4, where 3->tau(had) and 4->tau(had)
        elif dch_1 == 'tt' :
            self.q_1[0]  = entry.Tau_charge[jl1]
            self.q_2[0]  = entry.Tau_charge[jl2]
            self.d0_1[0]   = entry.Tau_dxy[jl1]
            self.dZ_1[0]   = entry.Tau_dz[jl1]
            self.d0_2[0]   = entry.Tau_dxy[jl2]
            self.dZ_2[0]   = entry.Tau_dz[jl2]
            '''self.idDecayModeNewDMs_1[0] = entry.Tau_idDecayModeNewDMs[jl1]
            self.idDeepTau2017v2p1VSe_1[0] = ord(chr(entry.Tau_idDeepTau2017v2p1VSe[jl1]))
            self.idDeepTau2017v2p1VSjet_1[0] = ord(chr(entry.Tau_idDeepTau2017v2p1VSjet[jl1]))
            self.idDeepTau2017v2p1VSmu_1[0] = ord(chr(entry.Tau_idDeepTau2017v2p1VSmu[jl1]))
            self.idMVAnewDM2017v2_1[0] = ord(chr(entry.Tau_idMVAnewDM2017v2[jl1]))
            self.rawMVAnewDM2017v2_1[0] = entry.Tau_rawMVAnewDM2017v2[jl1]
            '''
            if SystIndex ==0 and isMC: 
                    self.pt_uncor_1[0] = tPt[jl1]
                    self.m_uncor_1[0] = tMass[jl1]
                    self.pt_uncor_2[0] = tPt[jl2]
                    self.m_uncor_2[0] = tMass[jl2]
            #print '=========================================--------------------------------> inside', entry.Tau_mass[jl1] , entry.Tau_pt[jl1], jl1, int(entry.Tau_decayMode[jl1])
        
            # genMatch the hadronic tau candidate
            if isMC:
                    idx_t1_gen = GF.genMatchTau(entry, jl1, 'had')
                    if idx_t1_gen >= 0:
                        self.pt_1_tr[0]  = entry.GenVisTau_pt[idx_t1_gen]
                        self.phi_1_tr[0] = entry.GenVisTau_phi[idx_t1_gen]
                        self.eta_1_tr[0] = entry.GenVisTau_eta[idx_t1_gen]
                        self.GenPart_statusFlags_1[0]    = entry.GenPart_statusFlags[idx_t1_gen]
                        self.GenPart_status_1[0]    = entry.GenPart_status[idx_t1_gen]
                    else:
                        self.pt_1_tr[0]  = 1.2*entry.Tau_pt[jl1]
                        self.phi_1_tr[0] = 1.2*entry.Tau_phi[jl1]
                        self.eta_1_tr[0] = 1.2*entry.Tau_eta[jl1]

                    try : self.gen_match_1[0] = ord(chr(entry.Tau_genPartFlav[jl1]))
                    except AttributeError : self.gen_match_1[0] = -1

            try : self.decayMode_1[0] = int(entry.Tau_decayMode[jl1])
            except AttributeError : self.decayMode_1[0] = -1

            tmass= self.tauMass
            if entry.Tau_decayMode[jl1] == 0 : tmass= 0.13957 #pion mass
            else: tmass = entry.Tau_mass[jl1]
            Lep1.SetPtEtaPhiM(entry.Tau_pt[jl1], entry.Tau_eta[jl1], entry.Tau_phi[jl1], tmass)
            tmass= self.tauMass
            if entry.Tau_decayMode[jl2] == 0 : tmass= 0.13957 #pion mass
            else: tmass = entry.Tau_mass[jl2]
            Lep2.SetPtEtaPhiM(entry.Tau_pt[jl2], entry.Tau_eta[jl2], entry.Tau_phi[jl2], tmass)
            
        else :
            print(("Invalid channel={0:s} in outTuple(). Exiting.".format(cat)))
            exit()
            
        #self.mt_1[0]      = self.get_mt('MVAMet',   entry,Lep1)
        #self.pfmt_1[0]    = self.get_mt('PFMet',    entry,Lep1)
        #self.puppimt_1[0] = self.get_mt('PUPPIMet', entry,Lep1)

        
        # Fill variables for Leg4, where 4->tau(had)
        if dch_1 == 'et' or dch_1 == 'mt' or dch_1 == 'tt':
            '''self.idDecayModeNewDMs_2[0] = entry.Tau_idDecayModeNewDMs[jl2]
            self.idDeepTau2017v2p1VSe_2[0] = ord(chr(entry.Tau_idDeepTau2017v2p1VSe[jl2]))
            self.idDeepTau2017v2p1VSjet_2[0] = ord(chr(entry.Tau_idDeepTau2017v2p1VSjet[jl2]))
            self.idDeepTau2017v2p1VSmu_2[0] = ord(chr(entry.Tau_idDeepTau2017v2p1VSmu[jl2]))
            self.idMVAnewDM2017v2_2[0] = ord(chr(entry.Tau_idMVAnewDM2017v2[jl2]))
            self.rawMVAnewDM2017v2_2[0] = entry.Tau_rawMVAnewDM2017v2[jl2]
            '''
            phi, pt = entry.Tau_phi[jl2], entry.Tau_pt[jl2]
            
            #self.mt_2[0]      = self.get_mt('MVAMet',   entry, Lep2) 
            #self.pfmt_2[0]    = self.get_mt('PFMet',    entry, Lep2)
            #self.puppimt_2[0] = self.get_mt('PUPPIMet', entry, Lep2) 

            # genMatch the hadronic tau candidate
            if isMC:
                    idx_t2_gen = GF.genMatchTau(entry, jl2, 'had')
                    if idx_t2_gen >= 0:
                        self.pt_2_tr[0]  = entry.GenVisTau_pt[idx_t2_gen]
                        self.phi_2_tr[0] = entry.GenVisTau_phi[idx_t2_gen]
                        self.eta_2_tr[0] = entry.GenVisTau_eta[idx_t2_gen]
                        self.GenPart_statusFlags_2[0]    = entry.GenPart_statusFlags[idx_t2_gen]
                        self.GenPart_status_2[0]    = entry.GenPart_status[idx_t2_gen]
                    else:
                        self.pt_2_tr[0]  = 1.2*entry.Tau_pt[jl2]
                        self.phi_2_tr[0] = 1.2*entry.Tau_phi[jl2]
                        self.eta_2_tr[0] = 1.2*entry.Tau_eta[jl2]

                    try : self.gen_match_2[0] = ord(chr(entry.Tau_genPartFlav[jl2]))
                    except AttributeError: self.gen_match_2[0] = -1

            try : self.decayMode_2[0] = int(entry.Tau_decayMode[jl2])
            except AttributeError: self.decayMode_2[0] = -1            


        '''# di-tau variables
        self.pt_tt[0]  = self.getPt_tt( entry, Lep1, Lep2)
        self.H_DR[0] = self.getDR(entry,Lep1,Lep2)
        self.mt_tot[0] = self.getMt_tot(entry, Lep1, Lep2)
        self.m_vis[0]  = self.getM_vis( entry, Lep1, Lep2)
        '''        
        if SVFit :
            fastMTTmass, fastMTTtransverseMass = self.runSVFit(entry, dch_1, jl1, jl2, Lep1, Lep2,met_pt,met_phi) 
        else :
            fastMTTmass, fastMTTtransverseMass = -999., -999.
            
        self.mDCH1_sv[0] = fastMTTmass 
        self.mtDCH1_sv[0] = fastMTTtransverseMass  
        
        '''# genMatch the di-lepton variables
        if isMC :
            idx_Lep1, idx_Lep2 = -1, -1
            idx_Lep1_tr, idx_Lep2_tr = -1, -1
            if (Lep1.M() > 0.05 and Lep2.M() > 0.05): # muon mass 
                idx_Lep1 = GF.getLepIdxFrom4Vec(entry, Lep1, 'm')
                idx_Lep2 = GF.getLepIdxFrom4Vec(entry, Lep2, 'm')
                try :
                    idx_Lep1_tr = entry.Muon_genPartIdx[idx_Lep1]
                    idx_Lep2_tr = entry.Muon_genPartIdx[idx_Lep2]
                except IndexError : pass 
                    
            elif (Lep1.M() < 0.05 and Lep2.M() < 0.05): # electron mass
                idx_Lep1 = GF.getLepIdxFrom4Vec(entry, Lep1, 'e')
                idx_Lep2 = GF.getLepIdxFrom4Vec(entry, Lep2, 'e')
                try :
                    idx_Lep1_tr = entry.Electron_genPartIdx[idx_Lep1]
                    idx_Lep2_tr = entry.Electron_genPartIdx[idx_Lep2]
                except IndexError : pass 
                    
            if idx_Lep1_tr >= 0 and idx_Lep2_tr >= 0:
                self.m_1_tr[0]  = entry.GenPart_mass[idx_Lep1_tr]
                self.pt_1_tr[0]  = entry.GenPart_pt[idx_Lep1_tr]
                self.m_2_tr[0]  = entry.GenPart_mass[idx_Lep2_tr]
                self.pt_2_tr[0]  = entry.GenPart_pt[idx_Lep2_tr]
                self.eta_1_tr[0] = entry.GenPart_eta[idx_Lep1_tr]
                self.eta_2_tr[0] = entry.GenPart_eta[idx_Lep2_tr]
                self.phi_1_tr[0] = entry.GenPart_phi[idx_Lep1_tr]
                self.phi_2_tr[0] = entry.GenPart_phi[idx_Lep2_tr]
                self.GenPart_statusFlags_1[0]    = entry.GenPart_statusFlags[idx_Lep1_tr]
                self.GenPart_status_1[0]    = entry.GenPart_status[idx_Lep1_tr]
                self.GenPart_statusFlags_2[0]    = entry.GenPart_statusFlags[idx_Lep2_tr]
                self.GenPart_status_2[0]    = entry.GenPart_status[idx_Lep2_tr]
        '''
        
        self.pt_1[0]   = Lep1.Pt()
        self.pt_2[0]   = Lep2.Pt()
        self.phi_2[0]  = Lep2.Phi()
        self.phi_1[0]  = Lep1.Phi()
        self.eta_1[0]  = Lep1.Eta()
        self.eta_2[0]  = Lep2.Eta()
        self.m_1[0]    = Lep1.M()
        self.m_2[0]    = Lep2.M()

		self.pt_3[0]   = -1
        self.phi_3[0]  = -9
        self.eta_3[0]  = -9
        self.m_3[0]    = -1
        self.pt_4[0]   = -1
        self.phi_4[0]  = -9
        self.eta_4[0]  = -9
        self.m_4[0]    = -1


        self.mll[0]       = (Lep1 + Lep2).M()
        self.mll2[0]      = -1
        '''
        self.Z_DR[0]       = self.getDR(entry,Lep1,Lep2)
       
        self.H_LT[0]       = Lep1.Pt() + Lep2.Pt()
        self.dRl1H[0]  = self.getDR(entry,Lep1,Lep3+Lep4)
        self.dRl2H[0]  = self.getDR(entry,Lep2,Lep3+Lep4)
        self.dRlH[0]  = self.getDR(entry,Lep1+Lep2,Lep3+Lep4)

        self.dPhil1H[0]  = self.getdPhi(entry,Lep1,Lep3+Lep4)
        self.dPhil2H[0]  = self.getdPhi(entry,Lep2,Lep3+Lep4)
        self.dPhilH[0]  = self.getdPhi(entry,Lep1+Lep2,Lep3+Lep4)
        '''
        
        #self.btagWeightDeepCSVB[0]  = entry.btagWeight_DeepCSVB
        #print 'inside after filling----------------------->', entry.MET_pt,  self.met[0], met_pt
        #self.puppimet[0]    = entry.PuppiMET_pt
        #self.puppimetphi[0] = entry.PuppiMET_phi

        
        if isMC :
            self.HTXS_Higgs_cat[0]         = entry.HTXS_stage1_1_cat_pTjet30GeV
            self.HTXS_Higgs_pt[0]         = entry.HTXS_Higgs_pt
        
        
        # MET variables  at this point this is the TauES corrected MET

        #print 'let see', dch_2, self.pt_uncor_3[0], self.pt_3[0], self.pt_uncor_4[0], self.pt_4[0], entry.event, SystIndex

        if str(era) != '2017' : 
            self.metNoCor[0]= entry.MET_pt
            self.metphiNoCor[0]= entry.MET_phi
        if str(era) == '2017' :
            if proc=='EOY':
                try : 
                    self.metNoCor[0]= entry.METFixEE2017_pt
                    self.metphiNoCor[0]= entry.METFixEE2017_phi
                except AttributeError:
                    self.metNoCor[0]= entry.MET_pt
                    self.metphiNoCor[0]= entry.MET_phi

            if proc=='UL':
                try : 
                    self.metNoCor[0]= entry.MET_pt
                    self.metphiNoCor[0]= entry.MET_phi
                except AttributeError:
                    self.metNoCor[0]= -1
                    self.metphiNoCor[0]= -1

        #print 'inside', met_pt, entry.MET_pt, entry.MET_T1_pt, entry.event, entry.luminosityBlock, entry.run

        if met_pt != -99 : 
            self.met[0]         = met_pt 
            self.metphi[0]      = met_phi
            #if SystIndex==0 : print 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAa------------------------------>met corrected TES inside', met_pt, 'noTES corr', entry.MET_T1_pt, entry.event, entry.luminosityBlock, entry.run
          
        else : 
            if not doUncertainties : 
                if str(era) != '2017' : 
                    self.met[0]= entry.MET_pt
                    self.metphi[0]= entry.MET_phi
                if str(era) == '2017' : 
                    if proc=='EOY':
                        try :
                            self.met[0]= entry.METFixEE2017_pt
                            self.metphi[0]= entry.METFixEE2017_phi
                        except AttributeError:
                            self.met[0]= entry.MET_pt
                            self.metphi[0]= entry.MET_phi
                    if proc=='UL':
                        try :
                            self.met[0]= entry.MET_pt
                            self.metphi[0]= entry.MET_phi
                        except AttributeError:
                            self.met[0]= -1
                            self.metphi[0]= -1

            if  doUncertainties : 

                if str(era) != '2017' : 
                    try : 
                        self.met[0]= entry.MET_T1_pt
                        self.metphi[0]= entry.MET_T1_phi
                    except AttributeError : 
                        self.met[0]= entry.MET_pt
                        self.metphi[0]= entry.MET_phi

                if str(era) == '2017' : 
                    if proc=='EOY':
                        try : 
                            self.met[0]= entry.METFixEE2017_T1_pt
                            self.metphi[0]= entry.METFixEE2017_T1_phi
                        except AttributeError : 
                            self.met[0]= entry.METFixEE2017_pt
                            self.metphi[0]= entry.METFixEE2017_phi
                    if proc=='UL':
                        try : 
                            self.met[0]= entry.MET_T1_pt
                            self.metphi[0]= entry.MET_T1_phi
                        except AttributeError : 
                            self.met[0]= entry.MET_pt
                            self.metphi[0]= entry.MET_phi

        #metNoTauES holds the uncorrected TauES MET - if not doUncerta -> holds the default ucorrected MET, if doUncert the T1_corrected

        if str(era) != '2017' : 
            self.metNoTauES[0]         = entry.MET_pt
            self.metphiNoTauES[0]         = entry.MET_phi

            if doUncertainties : 
                try : 
                    self.metNoTauES[0]         = entry.MET_T1_pt
                    self.metphiNoTauES[0]         = entry.MET_T1_phi
                except AttributeError : 
                    self.metNoTauES[0]         = entry.MET_pt
                    self.metphiNoTauES[0]         = entry.MET_phi

                if isMC :
                    try : 
                        self.MET_T1Smear_pt[0]         = entry.MET_T1Smear_pt
                        self.MET_T1Smear_phi[0]         = entry.MET_T1Smear_phi
                    except AttributeError : 
                        self.MET_T1Smear_pt[0]         = -99
                        self.MET_T1Smear_phi[0]         = -99

        if str(era) == '2017' : 
            if proc=="EOY" :
                self.metNoTauES[0]         = entry.METFixEE2017_pt
                self.metphiNoTauES[0]         = entry.METFixEE2017_phi

                if doUncertainties : 
                    try :
                        self.metNoTauES[0]         = entry.METFixEE2017_T1_pt
                        self.metphiNoTauES[0]         = entry.METFixEE2017_T1_phi
                    except AttributeError : 
                        self.metNoTauES[0]         = entry.METFixEE2017_pt_nom
                        self.metphiNoTauES[0]         = entry.METFixEE2017_phi_nom
                    if isMC :
                        try :
                            self.MET_T1Smear_pt[0]         = entry.METFixEE2017_T1Smear_pt
                            self.MET_T1Smear_phi[0]         = entry.METFixEE2017_T1Smear_phi
                        except AttributeError : 
                            self.MET_T1Smear_pt[0]         = -1
                            self.MET_T1Smear_phi[0]         = -1

            if proc=="UL" :
                self.metNoTauES[0]         = entry.MET_pt
                self.metphiNoTauES[0]         = entry.MET_phi

                if doUncertainties : 
                    try :
                        self.metNoTauES[0]         = entry.MET_T1_pt
                        self.metphiNoTauES[0]         = entry.MET_T1_phi
                    except AttributeError : 
                        self.metNoTauES[0]         = entry.MET_pt_nom
                        self.metphiNoTauES[0]         = entry.MET_phi_nom
                    if isMC :
                        try :
                            self.MET_T1Smear_pt[0]         = entry.MET_T1Smear_pt
                            self.MET_T1Smear_phi[0]         = entry.MET_T1Smear_phi
                        except AttributeError : 
                            self.MET_T1Smear_pt[0]         = -1
                            self.MET_T1Smear_phi[0]         = -1

        #print 'in NTUPLE ============================== met_pt', met_pt, 'met', self.met[0], 'metnoTauES', self.metNoTauES[0], 'met_T1', entry.MET_T1_pt, 'met_T1Smear', entry.MET_T1Smear_pt, 'doUncert ?', doUncertainties

        if str(era) != '2017' : 

            self.metcov00[0] = entry.MET_covXX
            self.metcov01[0] = entry.MET_covXY
            self.metcov10[0] = entry.MET_covXY
            self.metcov11[0] = entry.MET_covYY
            self.met_UnclX = entry.MET_MetUnclustEnUpDeltaX
            self.met_UnclY = entry.MET_MetUnclustEnUpDeltaY

            if doUncertainties : 
                if isMC : 
                    self.MET_pt_UnclUp[0] = entry.MET_pt_unclustEnUp
                    self.MET_phi_UnclUp[0] = entry.MET_phi_unclustEnUp
                    self.MET_pt_UnclDown[0] = entry.MET_pt_unclustEnDown
                    self.MET_phi_UnclDown[0] = entry.MET_phi_unclustEnDown



        else :
            if proc=='EOY' :  
                self.metcov00[0] = entry.METFixEE2017_covXX
                self.metcov01[0] = entry.METFixEE2017_covXY
                self.metcov10[0] = entry.METFixEE2017_covXY
                self.metcov11[0] = entry.METFixEE2017_covYY
                self.met_UnclX = entry.METFixEE2017_MetUnclustEnUpDeltaX
                self.met_UnclY = entry.METFixEE2017_MetUnclustEnUpDeltaY

                if doUncertainties : 
                    if isMC : 
                        self.MET_pt_UnclUp[0] = entry.METFixEE2017_pt_unclustEnUp
                        self.MET_phi_UnclUp[0] = entry.METFixEE2017_phi_unclustEnUp
                        self.MET_pt_UnclDown[0] = entry.METFixEE2017_pt_unclustEnDown
                        self.MET_phi_UnclDown[0] = entry.METFixEE2017_phi_unclustEnDown
            if proc=='UL' :  
                self.metcov00[0] = entry.MET_covXX
                self.metcov01[0] = entry.MET_covXY
                self.metcov10[0] = entry.MET_covXY
                self.metcov11[0] = entry.MET_covYY
                self.met_UnclX = entry.MET_MetUnclustEnUpDeltaX
                self.met_UnclY = entry.MET_MetUnclustEnUpDeltaY

                if doUncertainties : 
                    if isMC : 
                        self.MET_pt_UnclUp[0] = entry.MET_pt_unclustEnUp
                        self.MET_phi_UnclUp[0] = entry.MET_phi_unclustEnUp
                        self.MET_pt_UnclDown[0] = entry.MET_pt_unclustEnDown
                        self.MET_phi_UnclDown[0] = entry.MET_phi_unclustEnDown

        # trig
        if SystIndex ==0 : 
            self.isTrig_1[0]   = is_trig_1
            self.isTrig_2[0]   = is_trig_2
            self.isDoubleTrig[0]   = is_Dtrig_1

        leplist=[]
        leplist.append(Lep1)
        leplist.append(Lep2)
        '''if jl3>-1 and jl4>-1 :  
            leplist.append(Lep3)
            leplist.append(Lep4)
        '''

        if doUncertainties: 
                ## this is not done from within ZH and the correctallMET function
                for i, v in enumerate(self.allsystMET) : 

                    if str(era)=='2017' :
                        #i_ should be the righ-hand of the branch and should retain the METFixEE2017 if y=2017 
                        #iMET should appear always at the branch name...
                        v = v.replace('MET','METFixEE2017')
                    iMET= v.replace('METFixEE2017','MET')

                    try : j = getattr(entry, "{0:s}".format(str(v)))
                    except AttributeError : j = -9.99
                    self.list_of_arrays_noES[i][0] = j
                    #if '_pt_jerUp' in v  : print '=====================================while filling-----------------',j, self.list_of_arrays[i][0], i, v, entry.event 

                for i, v in enumerate(self.allsystJets) : 
                #njets_sys, nbtag_sys
                    jetList, jetListFlav, jetListEta, jetListPt, bTagListDeep, bJetListL,bJetListM, bJetListT, bJetListFlav = self.getJetsJMEMV(entry,leplist,era,v) 
                    #print 'jessyst', systematic, len(jetList), cat

                    self.list_of_arraysJetsNjets[i][0] = len(jetList)
                    self.list_of_arraysJetsNbtagL[i][0] = len(bJetListL)
                    self.list_of_arraysJetsNbtagM[i][0] = len(bJetListM)
                    self.list_of_arraysJetsNbtagT[i][0] = len(bJetListT)
                    for ifl in range(len(jetList)) :
                        self.list_of_arraysJetsPt[i][ifl] = jetListPt[ifl]
                        self.list_of_arraysJetsEta[i][ifl] = jetListEta[ifl]
                        self.list_of_arraysJetsFlavour[i][ifl] = jetListFlav[ifl]
                        self.list_of_arraysJetsNbtagDeep[i][ifl] = bTagListDeep[ifl]


        #fill the un-corrected or just in the case you dont care to doUncertainties       
        nom_=''
        jetList, jetListFlav, jetListEta, jetListPt, bTagListDeep, bJetListL, bJetListM, bJetListT, bJetListFlav = self.getJetsJMEMV(entry,leplist,era,'') 
        self.njets[0] = len(jetList)
        self.nbtagL[0] = len(bJetListL)
        self.nbtagM[0] = len(bJetListM)
        self.nbtagT[0] = len(bJetListT)
        for ifl in range(len(jetListPt)) :
            self.jflavour[ifl]  = jetListFlav[ifl]
            self.jeta[ifl]  = jetListEta[ifl]
            self.jpt[ifl]  = jetListPt[ifl]
            self.btagDeep[ifl] = bTagListDeep[ifl]


        '''
            if len(jetList) > 0 :
                jpt1 = getattr(entry, "Jet_pt{0:s}".format(str(isys)), None)
                jj1 = jetList[0]
                self.jpt_1[ic]  = jpt1[jj1]
                self.jeta_1[ic] = entry.Jet_eta[jj1]
                self.jphi_1[ic] = entry.Jet_phi[jj1]
                self.jcsv_1[ic] = entry.Jet_btagDeepB[jj1]
                self.jcsvfv_1[ic] = entry.Jet_btagDeepFlavB[jj1]
                #print 'will use', ic, len(jetList), jetList, self.jpt_1[ic], self.njets[ic]
                
                # genMatch jet1
                if isMC:
                    idx_genJet = entry.Jet_genJetIdx[jj1]
                    if idx_genJet >= 0:
                        try :
                            self.jpt_1_tr[ic]  = entry.GenJet_pt[idx_genJet]
                            self.jeta_1_tr[ic] = entry.GenJet_eta[idx_genJet]
                            self.jphi_1_tr[ic] = entry.GenJet_phi[idx_genJet]
                        except IndexError : pass

            self.jpt_2[ic], self.jeta_2[ic], self.jphi_2[ic], self.jcsv_2[ic],self.jcsvfv_2[ic] = -9.99, -9.99, -9.99, -9.99, -9.99
            if len(jetList) > 1 :
                jpt2 = getattr(entry, "Jet_pt{0:s}".format(str(isys)), None)
                jj2 = jetList[1] 
                self.jpt_2[ic]  = jpt2[jj2]
                self.jeta_2[ic] = entry.Jet_eta[jj2]
                self.jphi_2[ic] = entry.Jet_phi[jj2]
                self.jcsv_2[ic] = entry.Jet_btagDeepB[jj2]
                self.jcsvfv_2[ic] = entry.Jet_btagDeepFlavB[jj2]
                
                # genMatch jet2
                if isMC:
                    idx_genJet = entry.Jet_genJetIdx[jj2]
                    if idx_genJet >= 0:
                        try: 
                           self.jpt_2_tr[ic]  = entry.GenJet_pt[idx_genJet]
                           self.jeta_2_tr[ic] = entry.GenJet_eta[idx_genJet]
                           self.jphi_2_tr[ic] = entry.GenJet_phi[idx_genJet]
                        except IndexError : pass 

            self.bpt_1[ic], self.beta_1[ic], self.bphi_1[ic], self.bcsv_1[ic], self.bcsvfv_1[ic] = -9.99, -9.99, -9.99, -9.99, -9.99
            if len(bJetList) > 0 :
                jpt1 = getattr(entry, "Jet_pt{0:s}".format(str(isys)), None)
                jbj1 = bJetList[0]
                self.bpt_1[ic] = jpt1[jbj1]
                self.beta_1[ic] = entry.Jet_eta[jbj1]
                self.bphi_1[ic] = entry.Jet_phi[jbj1]
                self.bcsv_1[ic] = entry.Jet_btagDeepB[jbj1] 
                self.bcsvfv_1[ic] = entry.Jet_btagDeepFlavB[jbj1]
                
            self.bpt_2[ic], self.beta_2[ic], self.bphi_2[ic], self.bcsv_2[ic], self.bcsvfv_2[ic] = -9.99, -9.99, -9.99, -9.99, -9.99
            if len(bJetList) > 1 :
                jpt2 = getattr(entry, "Jet_pt{0:s}".format(str(isys)), None)
                jbj2 = bJetList[1] 
                self.bpt_2[ic] = jpt2[jbj2]
                self.beta_2[ic] = entry.Jet_eta[jbj2]
                self.bphi_2[ic] = entry.Jet_phi[jbj2]
                self.bcsv_2[ic] = entry.Jet_btagDeepB[jbj2]
                self.bcsvfv_2[ic] = entry.Jet_btagDeepFlavB[jbj2]

                # genMatch bjet1
                if isMC:
                    idx_genJet = entry.Jet_genJetIdx[jbj2]
                    if idx_genJet >= 0:
                        try :
                            self.bpt_2_tr[ic]  = entry.GenJet_pt[idx_genJet]
                            self.beta_2_tr[ic] = entry.GenJet_eta[idx_genJet]
                            self.bphi_2_tr[ic] = entry.GenJet_phi[idx_genJet]
                        except IndexError : pass

        '''

        #if  self.nbtag[0] == 0 : 
        if SystIndex == 0 : 
            self.t.Fill()
        else : 
            self.tN[SystIndex-1].Fill()

        self.IDSF_1[0], self.ISOSF_1[0], self.TrigSF_1[0] = self.getIDISOTrigSF(era, yearin, cat[0], Lep1.Pt(), Lep1.Eta(), Lep1.Phi(),  isMC)
        self.IDSF_2[0], self.ISOSF_2[0], self.TrigSF_2[0] = self.getIDISOTrigSF(era, yearin, cat[1], Lep2.Pt(), Lep2.Eta(), Lep2.Phi(),  isMC)
        self.IDSF_3[0], self.ISOSF_3[0], self.TrigSF_3[0] = self.getIDISOTrigSF(era, yearin, cat[2], Lep3.Pt(), Lep3.Eta(), Lep3.Phi(),  isMC)
        #self.IDSF_4[0], self.ISOSF_4[0], self.TrigSF_4[0] = self.getIDISOTrigSF(era, yearin, cat[3], Lep4.Pt(), Lep4.Eta(), Lep4.Phi(),  isMC)

        return
