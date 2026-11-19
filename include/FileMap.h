std::map<std::string, std::vector<std::string>> getFileMap(std::string year) {
    std::map<std::string, std::vector<std::string>> files;
    if (year == "2016preVFP") {
        files = {
            {"DY10_50", {"DYJetsToLLM10to50_2016preVFP.root"}},
            {"DY",      {"DYJetsToLLM50_2016preVFP.root"}},
            {"VV",      {"WW_2016preVFP.root", "WWTo2L2Nu_2016preVFP.root", "WZTo2Q2L_2016preVFP.root", "WZTo3LNu_2016preVFP.root"}},
            {"VVV",     {"WWW_2016preVFP.root", "WZZ_2016preVFP.root", "ZZZ_2016preVFP.root"}},
            {"ttV",     {"ttWJets_2016preVFP.root", "ttZJets_2016preVFP.root"}},
            {"WJ",      {"WJetsToLNu_NLO_part2_2016preVFP.root"}},
            {"ZZ",      {"ZZTo2L2Nu_2016preVFP.root", "ZZTo2Q2L_2016preVFP.root", "ZZTo4L_2016preVFP.root"}},
            {"ST",      {"ST_s-channel_2016preVFP.root", "ST_t-channel_antitop_2016preVFP.root", "ST_t-channel_top_2016preVFP.root", "ST_tW_antitop_2016preVFP.root", "ST_tW_top_2016preVFP.root"}},
            {"TTbar",   {"TTTo2L2Nu_2016preVFP.root", "TTToSemiLeptonic_2016preVFP.root", "TTToHadronic_2016preVFP.root"}},
            {"QCD",     {"QCD_HT50to100_2016preVFP.root", "QCD_HT100to200_2016preVFP.root", "QCD_HT200to300_2016preVFP.root", "QCD_HT300to500_2016preVFP.root", "QCD_HT500to700_2016preVFP.root", "QCD_HT700to1000_2016preVFP.root", "QCD_HT1000to1500_2016preVFP.root", "QCD_HT1500to2000_2016preVFP.root", "QCD_HT2000toInf_2016preVFP.root"}},
            {"other",   {"ttHToTauTau_2016preVFP.root", "ZHToMuMu_2016preVFP.root", "ZHToTauTau_2016preVFP.root", "GluGluZH_2016preVFP.root", "ttHToEE_2016preVFP.root", "ttHTo2L2Nu_2016preVFP.root", "ttHJetToNonbb_2016preVFP.root", "TWZToLL_2016preVFP.root", "HZJ_HToWWTo2L2Nu_ZTo2L_2016preVFP.root"}},
            {"data",    {"SingleElectronB_2016preVFP.root", "SingleElectronC_2016preVFP.root", "SingleElectronD_2016preVFP.root", "SingleElectronE_2016preVFP.root", "SingleElectronF_2016preVFP.root", "SingleMuonB_2016preVFP.root", "SingleMuonC_2016preVFP.root", "SingleMuonD_2016preVFP.root", "SingleMuonE_2016preVFP.root", "SingleMuonF_2016preVFP.root"}}
        };
    }
    else if (year == "2016postVFP") {
        files = {
            {"DY10_50", {"DYJetsToLLM10to50_2016postVFP.root"}},
            {"DY",      {"DYJetsToLLM50_2016postVFP.root"}},
            {"VV",      {"WW_2016postVFP.root", "WWTo2L2Nu_2016postVFP.root", "WZTo2Q2L_2016postVFP.root", "WZTo3LNu_2016postVFP.root"}},
            {"VVV",     {"WWW_2016postVFP.root", "WZZ_2016postVFP.root", "ZZZ_2016postVFP.root"}},
            {"ttV",     {"ttWJets_2016postVFP.root", "ttZJets_2016postVFP.root"}},
            {"WJ",      {"WJetsToLNu_NLO_2016postVFP.root"}},
            {"ZZ",      {"ZZTo2L2Nu_2016postVFP.root", "ZZTo2Q2L_2016postVFP.root", "ZZTo4L_2016postVFP.root"}},
            {"ST",      {"ST_s-channel_2016postVFP.root", "ST_t-channel_antitop_2016postVFP.root", "ST_t-channel_top_2016postVFP.root", "ST_tW_antitop_2016postVFP.root", "ST_tW_top_2016postVFP.root"}},
            {"TTbar",   {"TTTo2L2Nu_2016postVFP.root", "TTToSemiLeptonic_2016postVFP.root", "TTToHadronic_2016postVFP.root"}},
            {"QCD",     {"QCD_HT50to100_2016postVFP.root", "QCD_HT100to200_2016postVFP.root", "QCD_HT200to300_2016postVFP.root", "QCD_HT300to500_2016postVFP.root", "QCD_HT500to700_2016postVFP.root", "QCD_HT700to1000_2016postVFP.root", "QCD_HT1000to1500_2016postVFP.root", "QCD_HT1500to2000_2016postVFP.root", "QCD_HT2000toInf_2016postVFP.root"}},
            {"other",   {"ttHToTauTau_2016postVFP.root", "ZHToMuMu_2016postVFP.root", "ZHToTauTau_2016postVFP.root", "GluGluZH_2016postVFP.root", "ttHToEE_2016postVFP.root", "ttHTo2L2Nu_2016postVFP.root"}},
            {"data",    {"SingleElectronF_2016postVFP.root", "SingleElectronG_2016postVFP.root", "SingleElectronH_2016postVFP.root", "SingleMuonF_2016postVFP.root", "SingleMuonG_2016postVFP.root", "SingleMuonH_2016postVFP.root"}}
        };
    }
    else if (year == "2017") {
        files = {
            {"DY10_50", {"DYJetsToLLM10to50_2017.root"}},
            {"DY",      {"DYJetsToLLM50_2017.root"}},
            {"VV",      {"WW_2017.root", "WWTo2L2Nu_2017.root", "WZTo2Q2L_2017.root", "WZTo3LNu_2017.root"}},
            {"VVV",     {"WWW_2017.root", "WZZ_2017.root", "ZZZ_2017.root"}},
            {"ttV",     {"ttWJets_2017.root", "ttZJets_2017.root"}},
            {"WJ",      {"WJetsToLNu_NLO_2017.root"}},
            {"ZZ",      {"ZZTo2L2Nu_2017.root", "ZZTo2Q2L_2017.root", "ZZTo4L_2017.root"}},
            {"ST",      {"ST_s-channel_2017.root", "ST_t-channel_antitop_2017.root", "ST_t-channel_top_2017.root", "ST_tW_antitop_2017.root", "ST_tW_top_2017.root"}},
            {"TTbar",   {"TTTo2L2Nu_2017.root", "TTToSemiLeptonic_2017.root", "TTToHadronic_2017.root"}},
            {"QCD",     {"QCD_HT50to100_2017.root", "QCD_HT100to200_2017.root", "QCD_HT200to300_2017.root", "QCD_HT300to500_2017.root", "QCD_HT500to700_2017.root", "QCD_HT700to1000_2017.root", "QCD_HT1000to1500_2017.root", "QCD_HT1500to2000_2017.root", "QCD_HT2000toInf_2017.root"}},
            {"other",   {"ttHToTauTau_2017.root", "ZHToMuMu_2017.root", "ZHToTauTau_2017.root", "GluGluZH_2017.root", "ttHToEE_2017.root", "ttHTo2L2Nu_2017.root"}},
            {"data",    {"SingleElectronB_2017.root", "SingleElectronC_2017.root", "SingleElectronD_2017.root", "SingleElectronE_2017.root", "SingleElectronF_2017.root", "SingleMuonB_2017.root", "SingleMuonC_2017.root", "SingleMuonD_2017.root", "SingleMuonE_2017.root", "SingleMuonF_2017.root"}}
        };
    }
    else if (year == "2018") {
        files = {
            {"DY10_50", {"DYJetsToLLM10to50_2018.root"}},
            {"DY",      {"DYJetsToLLM50_2018.root"}},
            {"VV",      {"WW_2018.root", "WWTo2L2Nu_2018.root", "WZTo2Q2L_2018.root", "WZTo3LNu_2018.root"}},
            {"VVV",     {"WWW_2018.root", "WZZ_2018.root", "ZZZ_2018.root"}},
            {"ttV",     {"ttWJets_2018.root", "ttZJets_2018.root"}},
            {"WJ",      {"WJetsToLNu_NLO_2018.root"}},
            {"ZZ",      {"ZZTo2L2Nu_2018.root", "ZZTo2Q2L_2018.root", "ZZTo4L_2018.root"}},
            {"ST",      {"ST_s-channel_2018.root", "ST_t-channel_antitop_2018.root", "ST_t-channel_top_2018.root", "ST_tW_antitop_2018.root", "ST_tW_top_2018.root"}},
            {"TTbar",   {"TTTo2L2Nu_2018.root", "TTToSemiLeptonic_2018.root", "TTToHadronic_2018.root"}},
            {"QCD",     {"QCD_HT50to100_2018.root", "QCD_HT100to200_2018.root", "QCD_HT200to300_2018.root", "QCD_HT300to500_2018.root", "QCD_HT500to700_2018.root", "QCD_HT700to1000_2018.root", "QCD_HT1000to1500_2018.root", "QCD_HT1500to2000_2018.root", "QCD_HT2000toInf_2018.root"}},
            {"other",   {"ttHToTauTau_2018.root", "ZHToMuMu_2018.root", "ZHToTauTau_2018.root", "GluGluZH_2018.root", "ttHToEE_2018.root", "ttHTo2L2Nu_2018.root"}},
            {"data",    {"EGammaA_2018.root", "EGammaB_2018.root", "EGammaC_2018.root", "EGammaD_2018.root", "SingleMuonA_2018.root", "SingleMuonB_2018.root", "SingleMuonC_2018.root", "SingleMuonD_2018.root"}}
        };
    }
    else if (year == "Run2") {
        files = {
            {"DY",      {"DYJetsToLLM10to50_2016postVFP.root", "DYJetsToLLM10to50_2016preVFP.root", "DYJetsToLLM10to50_2017.root", "DYJetsToLLM10to50_2018.root","DYJetsToLLM50_2016postVFP.root", "DYJetsToLLM50_2016preVFP.root", "DYJetsToLLM50_2017.root", "DYJetsToLLM50_2018.root"}},
            {"VV",      {"WW_2016postVFP.root", "WWTo2L2Nu_2016postVFP.root", "WZTo2Q2L_2016postVFP.root", "WZTo3LNu_2016postVFP.root", "WW_2016preVFP.root", "WWTo2L2Nu_2016preVFP.root", "WZTo2Q2L_2016preVFP.root", "WZTo3LNu_2016preVFP.root", "WW_2017.root", "WWTo2L2Nu_2017.root", "WZTo2Q2L_2017.root", "WZTo3LNu_2017.root", "WW_2018.root", "WWTo2L2Nu_2018.root", "WZTo2Q2L_2018.root", "WZTo3LNu_2018.root"}},
            {"VVV",     {"WWW_2016postVFP.root", "WZZ_2016postVFP.root", "ZZZ_2016postVFP.root", "WWW_2016preVFP.root", "WZZ_2016preVFP.root", "ZZZ_2016preVFP.root", "WWW_2017.root", "WZZ_2017.root", "ZZZ_2017.root", "WWW_2018.root", "WZZ_2018.root", "ZZZ_2018.root"}},
            {"ttV",     {"ttWJets_2016postVFP.root", "ttZJets_2016postVFP.root", "ttWJets_2016preVFP.root", "ttZJets_2016preVFP.root", "ttWJets_2017.root", "ttZJets_2017.root", "ttWJets_2018.root", "ttZJets_2018.root"}},
            {"WJ",      {"WJetsToLNu_NLO_2016postVFP.root", "WJetsToLNu_NLO_part2_2016preVFP.root", "WJetsToLNu_NLO_2017.root", "WJetsToLNu_NLO_2018.root"}},
            {"ZZ",      {"ZZTo2L2Nu_2016postVFP.root", "ZZTo2Q2L_2016postVFP.root", "ZZTo4L_2016postVFP.root", "ZZTo2L2Nu_2016preVFP.root", "ZZTo2Q2L_2016preVFP.root", "ZZTo4L_2016preVFP.root", "ZZTo2L2Nu_2017.root", "ZZTo2Q2L_2017.root", "ZZTo4L_2017.root", "ZZTo2L2Nu_2018.root", "ZZTo2Q2L_2018.root", "ZZTo4L_2018.root"}},
            {"ST",      {"ST_s-channel_2016postVFP.root", "ST_t-channel_antitop_2016postVFP.root", "ST_t-channel_top_2016postVFP.root", "ST_tW_antitop_2016postVFP.root", "ST_tW_top_2016postVFP.root", "ST_s-channel_2016preVFP.root", "ST_t-channel_antitop_2016preVFP.root", "ST_t-channel_top_2016preVFP.root", "ST_tW_antitop_2016preVFP.root", "ST_tW_top_2016preVFP.root", "ST_s-channel_2017.root", "ST_t-channel_antitop_2017.root", "ST_t-channel_top_2017.root", "ST_tW_antitop_2017.root", "ST_tW_top_2017.root", "ST_s-channel_2018.root", "ST_t-channel_antitop_2018.root", "ST_t-channel_top_2018.root", "ST_tW_antitop_2018.root", "ST_tW_top_2018.root"}},
            {"TTbar",   {"TTTo2L2Nu_2016postVFP.root", "TTToSemiLeptonic_2016postVFP.root", "TTToHadronic_2016postVFP.root", "TTTo2L2Nu_2016preVFP.root", "TTToSemiLeptonic_2016preVFP.root", "TTToHadronic_2016preVFP.root", "TTTo2L2Nu_2017.root", "TTToSemiLeptonic_2017.root", "TTToHadronic_2017.root", "TTTo2L2Nu_2018.root", "TTToSemiLeptonic_2018.root", "TTToHadronic_2018.root"}},
	    {"other",     {"QCD_HT50to100_2016postVFP.root", "QCD_HT100to200_2016postVFP.root", "QCD_HT200to300_2016postVFP.root", "QCD_HT300to500_2016postVFP.root", "QCD_HT500to700_2016postVFP.root", "QCD_HT700to1000_2016postVFP.root", "QCD_HT1000to1500_2016postVFP.root", "QCD_HT1500to2000_2016postVFP.root", "QCD_HT2000toInf_2016postVFP.root", "QCD_HT50to100_2016preVFP.root", "QCD_HT100to200_2016preVFP.root", "QCD_HT200to300_2016preVFP.root", "QCD_HT300to500_2016preVFP.root", "QCD_HT500to700_2016preVFP.root", "QCD_HT700to1000_2016preVFP.root", "QCD_HT1000to1500_2016preVFP.root", "QCD_HT1500to2000_2016preVFP.root", "QCD_HT2000toInf_2016preVFP.root", "QCD_HT50to100_2017.root", "QCD_HT100to200_2017.root", "QCD_HT200to300_2017.root", "QCD_HT300to500_2017.root", "QCD_HT500to700_2017.root", "QCD_HT700to1000_2017.root", "QCD_HT1000to1500_2017.root", "QCD_HT1500to2000_2017.root", "QCD_HT2000toInf_2017.root", "QCD_HT50to100_2018.root", "QCD_HT100to200_2018.root", "QCD_HT200to300_2018.root", "QCD_HT300to500_2018.root", "QCD_HT500to700_2018.root", "QCD_HT700to1000_2018.root", "QCD_HT1000to1500_2018.root", "QCD_HT1500to2000_2018.root", "QCD_HT2000toInf_2018.root",
		"ttHToTauTau_2016postVFP.root", "ZHToMuMu_2016postVFP.root", "ZHToTauTau_2016postVFP.root", "GluGluZH_2016postVFP.root", "ttHToEE_2016postVFP.root", "ttHTo2L2Nu_2016postVFP.root", "ttHToTauTau_2016preVFP.root", "ZHToMuMu_2016preVFP.root", "ZHToTauTau_2016preVFP.root", "GluGluZH_2016preVFP.root", "ttHToEE_2016preVFP.root", "ttHTo2L2Nu_2016preVFP.root", "ttHJetToNonbb_2016preVFP.root", "TWZToLL_2016preVFP.root", "HZJ_HToWWTo2L2Nu_ZTo2L_2016preVFP.root", "ttHToTauTau_2017.root", "ZHToMuMu_2017.root", "ZHToTauTau_2017.root", "GluGluZH_2017.root", "ttHToTauTau_2018.root", "ZHToMuMu_2018.root", "ZHToTauTau_2018.root", "GluGluZH_2018.root", "ttHToEE_2017.root", "ttHToEE_2018.root", "ttHTo2L2Nu_2017.root", "ttHTo2L2Nu_2018.root", "ttHJetToNonbb_2016postVFP.root", "ttHJetToNonbb_2017.root", "ttHJetToNonbb_2018.root", "TWZToLL_2016postVFP.root", "TWZToLL_2017.root", "TWZToLL_2018.root", "HZJ_HToWWTo2L2Nu_ZTo2L_2016postVFP.root", "HZJ_HToWWTo2L2Nu_ZTo2L_2017.root", "HZJ_HToWWTo2L2Nu_ZTo2L_2018.root"}},
            {"data",    {"SingleElectronB_2016preVFP.root", "SingleElectronC_2016preVFP.root", "SingleElectronD_2016preVFP.root", "SingleElectronE_2016preVFP.root", "SingleElectronF_2016preVFP.root", "SingleElectronF_2016postVFP.root", "SingleElectronG_2016postVFP.root", "SingleElectronH_2016postVFP.root", "SingleMuonB_2016preVFP.root", "SingleMuonC_2016preVFP.root", "SingleMuonD_2016preVFP.root", "SingleMuonE_2016preVFP.root", "SingleMuonF_2016preVFP.root", "SingleMuonF_2016postVFP.root", "SingleMuonG_2016postVFP.root", "SingleMuonH_2016postVFP.root", "SingleElectronB_2017.root", "SingleElectronC_2017.root", "SingleElectronD_2017.root", "SingleElectronE_2017.root", "SingleElectronF_2017.root", "SingleMuonB_2017.root", "SingleMuonC_2017.root", "SingleMuonD_2017.root", "SingleMuonE_2017.root", "SingleMuonF_2017.root", "EGammaA_2018.root", "EGammaB_2018.root", "EGammaC_2018.root", "EGammaD_2018.root", "SingleMuonA_2018.root", "SingleMuonB_2018.root", "SingleMuonC_2018.root", "SingleMuonD_2018.root"}}
        };
    }
    return files;
}

