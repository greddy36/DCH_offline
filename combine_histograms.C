//Combine histograms from the files listed in filemap to make a single file for COMBINE. 
//Don't mess with it unless you plan on changing the make_datacard.py script. -Guru

#include <TFile.h>
#include <TH1.h>
#include <TKey.h>
#include <TDirectory.h>
#include <TClass.h>
#include <TSystem.h>

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;


map<string, vector<string>> samples = {
	{"M500", {"HppM500_2016preVFP.root","HppM500_2016postVFP.root","HppM500_2017.root","HppM500_2018.root"}},
	{"M600", {"HppM600_2016preVFP.root","HppM600_2016postVFP.root","HppM600_2017.root","HppM600_2018.root"}},
	{"M700", {"HppM700_2016preVFP.root","HppM700_2016postVFP.root","HppM700_2017.root","HppM700_2018.root"}},
	{"M800", {"HppM800_2016preVFP.root","HppM800_2016postVFP.root","HppM800_2017.root","HppM800_2018.root"}},
	{"M900", {"HppM900_2016preVFP.root","HppM900_2016postVFP.root","HppM900_2017.root","HppM900_2018.root"}},
	{"M1000", {"HppM1000_2016preVFP.root","HppM1000_2016postVFP.root","HppM1000_2017.root","HppM1000_2018.root"}},
	{"M1100", {"HppM1100_2016preVFP.root","HppM1100_2016postVFP.root","HppM1100_2017.root","HppM1100_2018.root"}},
	{"M1200", {"HppM1200_2016preVFP.root","HppM1200_2016postVFP.root","HppM1200_2017.root","HppM1200_2018.root"}},
	{"M1300", {"HppM1300_2016preVFP.root","HppM1300_2016postVFP.root","HppM1300_2017.root","HppM1300_2018.root"}},
	{"M1400", {"HppM1400_2016preVFP.root","HppM1400_2016postVFP.root","HppM1400_2017.root","HppM1400_2018.root"}},
	{"M1500", {"HppM1500_2016preVFP.root","HppM1500_2016postVFP.root","HppM1500_2017.root","HppM1500_2018.root"}},
    {"DY", {"DYJetsToLLM10to50_2016postVFP.root","DYJetsToLLM10to50_2016preVFP.root","DYJetsToLLM10to50_2017.root","DYJetsToLLM10to50_2018.root","DYJetsToLLM50_2016postVFP.root","DYJetsToLLM50_2016preVFP.root","DYJetsToLLM50_2017.root","DYJetsToLLM50_2018.root"
    }},

    {"VV", {"WW_2016postVFP.root","WWTo2L2Nu_2016postVFP.root","WZTo2Q2L_2016postVFP.root","WW_2016preVFP.root","WWTo2L2Nu_2016preVFP.root","WZTo2Q2L_2016preVFP.root","WW_2017.root","WWTo2L2Nu_2017.root","WZTo2Q2L_2017.root","WW_2018.root","WWTo2L2Nu_2018.root","WZTo2Q2L_2018.root","WZTo3LNu_2016postVFP.root","WZTo3LNu_2016preVFP.root","WZTo3LNu_2017.root","WZTo3LNu_2018.root"
    }},

    {"VVV", {"WWW_2016postVFP.root","WZZ_2016postVFP.root","ZZZ_2016postVFP.root","WWW_2016preVFP.root","WZZ_2016preVFP.root","ZZZ_2016preVFP.root","WWW_2017.root","WZZ_2017.root","ZZZ_2017.root","WWW_2018.root","WZZ_2018.root","ZZZ_2018.root"
    }},

    {"ttV", {"ttWJets_2016postVFP.root","ttWJets_2016preVFP.root","ttWJets_2017.root","ttWJets_2018.root","ttZJets_2016postVFP.root","ttZJets_2016preVFP.root","ttZJets_2017.root","ttZJets_2018.root"
    }},

    {"WJ", {"WJetsToLNu_NLO_2016postVFP.root","WJetsToLNu_NLO_part2_2016preVFP.root","WJetsToLNu_NLO_2017.root","WJetsToLNu_NLO_2018.root"
    }},

    {"ZZ", {"ZZTo2L2Nu_2016postVFP.root","ZZTo2Q2L_2016postVFP.root","ZZTo4L_2016postVFP.root","ZZTo2L2Nu_2016preVFP.root","ZZTo2Q2L_2016preVFP.root","ZZTo4L_2016preVFP.root","ZZTo2L2Nu_2017.root","ZZTo2Q2L_2017.root","ZZTo4L_2017.root","ZZTo2L2Nu_2018.root","ZZTo2Q2L_2018.root","ZZTo4L_2018.root"
    }},

    {"ST", {"ST_s-channel_2016postVFP.root","ST_t-channel_antitop_2016postVFP.root","ST_t-channel_top_2016postVFP.root","ST_tW_antitop_2016postVFP.root","ST_tW_top_2016postVFP.root","ST_s-channel_2016preVFP.root","ST_t-channel_antitop_2016preVFP.root","ST_t-channel_top_2016preVFP.root","ST_tW_antitop_2016preVFP.root","ST_tW_top_2016preVFP.root","ST_s-channel_2017.root","ST_t-channel_antitop_2017.root","ST_t-channel_top_2017.root","ST_tW_antitop_2017.root","ST_tW_top_2017.root","ST_s-channel_2018.root","ST_t-channel_antitop_2018.root","ST_t-channel_top_2018.root","ST_tW_antitop_2018.root","ST_tW_top_2018.root"
    }},

    {"TTbar", {"TTTo2L2Nu_2016postVFP.root","TTToSemiLeptonic_2016postVFP.root","TTToHadronic_2016postVFP.root","TTTo2L2Nu_2016preVFP.root","TTToSemiLeptonic_2016preVFP.root","TTToHadronic_2016preVFP.root","TTTo2L2Nu_2017.root","TTToSemiLeptonic_2017.root","TTToHadronic_2017.root","TTTo2L2Nu_2018.root","TTToSemiLeptonic_2018.root","TTToHadronic_2018.root"
    }},

    {"QCD", {"QCD_HT50to100_2016postVFP.root","QCD_HT100to200_2016postVFP.root","QCD_HT200to300_2016postVFP.root","QCD_HT300to500_2016postVFP.root","QCD_HT500to700_2016postVFP.root","QCD_HT700to1000_2016postVFP.root","QCD_HT1000to1500_2016postVFP.root","QCD_HT1500to2000_2016postVFP.root","QCD_HT2000toInf_2016postVFP.root","QCD_HT50to100_2016preVFP.root","QCD_HT100to200_2016preVFP.root","QCD_HT200to300_2016preVFP.root","QCD_HT300to500_2016preVFP.root","QCD_HT500to700_2016preVFP.root","QCD_HT700to1000_2016preVFP.root","QCD_HT1000to1500_2016preVFP.root","QCD_HT1500to2000_2016preVFP.root","QCD_HT2000toInf_2016preVFP.root","QCD_HT50to100_2017.root","QCD_HT100to200_2017.root","QCD_HT200to300_2017.root","QCD_HT300to500_2017.root","QCD_HT500to700_2017.root","QCD_HT700to1000_2017.root","QCD_HT1000to1500_2017.root","QCD_HT1500to2000_2017.root","QCD_HT2000toInf_2017.root","QCD_HT50to100_2018.root","QCD_HT100to200_2018.root","QCD_HT200to300_2018.root","QCD_HT300to500_2018.root","QCD_HT500to700_2018.root","QCD_HT700to1000_2018.root","QCD_HT1000to1500_2018.root","QCD_HT1500to2000_2018.root","QCD_HT2000toInf_2018.root"
    }},

    {"ZH", {
"ZHToMuMu_2016postVFP.root","ZHToTauTau_2016postVFP.root","GluGluZH_2016postVFP.root","ZHToMuMu_2016preVFP.root","ZHToTauTau_2016preVFP.root","GluGluZH_2016preVFP.root","ZHToMuMu_2017.root","ZHToTauTau_2017.root","GluGluZH_2017.root","ZHToMuMu_2018.root","ZHToTauTau_2018.root","GluGluZH_2018.root"
    }},

    {"other", {
"ttHToTauTau_2016postVFP.root","ttHToEE_2016postVFP.root","ttHTo2L2Nu_2016postVFP.root",
"ttHToTauTau_2016preVFP.root","ttHToEE_2016preVFP.root","ttHTo2L2Nu_2016preVFP.root","ttHJetToNonbb_2016preVFP.root","TWZToLL_2016preVFP.root","HZJ_HToWWTo2L2Nu_ZTo2L_2016preVFP.root","ttHToTauTau_2017.root","ttHToEE_2017.root","ttHTo2L2Nu_2017.root","ttHJetToNonbb_2017.root","TWZToLL_2017.root","HZJ_HToWWTo2L2Nu_ZTo2L_2017.root","ttHToTauTau_2018.root","ttHToEE_2018.root","ttHTo2L2Nu_2018.root","ttHJetToNonbb_2018.root","TWZToLL_2018.root","HZJ_HToWWTo2L2Nu_ZTo2L_2018.root","ttHJetToNonbb_2016postVFP.root","TWZToLL_2016postVFP.root","HZJ_HToWWTo2L2Nu_ZTo2L_2016postVFP.root"
    }},

    {"data_obs", {"SingleElectronB_2016preVFP.root","SingleElectronC_2016preVFP.root","SingleElectronD_2016preVFP.root","SingleElectronE_2016preVFP.root","SingleElectronF_2016preVFP.root","SingleElectronF_2016postVFP.root","SingleElectronG_2016postVFP.root","SingleElectronH_2016postVFP.root",
"SingleMuonB_2016preVFP.root","SingleMuonC_2016preVFP.root","SingleMuonD_2016preVFP.root","SingleMuonE_2016preVFP.root","SingleMuonF_2016preVFP.root","SingleMuonF_2016postVFP.root","SingleMuonG_2016postVFP.root","SingleMuonH_2016postVFP.root",

"SingleElectronB_2017.root","SingleElectronC_2017.root","SingleElectronD_2017.root","SingleElectronE_2017.root","SingleElectronF_2017.root",

"SingleMuonB_2017.root","SingleMuonC_2017.root","SingleMuonD_2017.root","SingleMuonE_2017.root","SingleMuonF_2017.root",

"EGammaA_2018.root","EGammaB_2018.root","EGammaC_2018.root","EGammaD_2018.root",
"SingleMuonA_2018.root","SingleMuonB_2018.root","SingleMuonC_2018.root","SingleMuonD_2018.root"
    }}
};


map<string, TH1*> accumulated;// Accumulated histograms for ONE sample

void processDirectory(TDirectory* dir){// Recursively read all histograms in a directory
    if (!dir)
        return;

    TIter nextKey(dir->GetListOfKeys());
    TKey* key;

    while ((key = (TKey*)nextKey())) {
        TObject* obj = key->ReadObj();

        if (obj->InheritsFrom(TDirectory::Class())) {
            processDirectory((TDirectory*)obj);
            delete obj;
            continue;
        }


        if (!obj->InheritsFrom(TH1::Class())) {
            delete obj;
            continue;
        }

        TH1* h = dynamic_cast<TH1*>(obj);

        if (!h) {
            delete obj;
            continue;
        }

        string fullName;
        fullName =  h->GetName();
        if (fullName.find("h_m") == string::npos) {//mass histograms only
			delete obj;
			continue;
		}


        if (accumulated.find(fullName) == accumulated.end()) {// First histogram encountered
            TH1* clone = dynamic_cast<TH1*>(h->Clone());
            clone->SetDirectory(nullptr);
            //clone->Sumw2();
            accumulated[fullName] = clone;
        }

        else {// Add histogram
            TH1* existing = accumulated[fullName];
            if (existing->GetNbinsX() != h->GetNbinsX()) {
                cerr << "WARNING: binning mismatch for " << fullName << endl;
                delete obj;
                continue;
            }
            existing->Add(h);
        }
        delete obj;
    }
}


// ================================================================
// Write histogram to output file with sample appended
//
// Example:
//
//   input:
//       h_Mll_SR_3tau
//
//   output:
//       h_Mll_SR_3tau_DY
//
// ================================================================

void writeHistogram(
    TFile* outfile,
    TH1* h,
    const string& sample
){
    string histName = h->GetName();
    std::regex re("(\\d+)tau"); 
    histName = std::regex_replace(histName, re, "tau$1");
    std::regex re1("(\\d+)lep");
    histName = std::regex_replace(histName, re1, "lep$1");
	cout<<histName<<endl;
    histName += "_" + sample; // Append sample name
	
    TDirectory* current = outfile;
    current->cd();
    
	h->SetName(histName.c_str());
	h->Write();
	delete h;
	if (!outfile->Get(histName.c_str()))
		cerr << "FAILED TO WRITE: " << histName << endl;
}

void combineSample(// Combine ONE sample
    const string& sample,
    const vector<string>& files,
    const string& inputDir,
    TFile* outfile
)
{
    cout << endl;
    cout << "================================================" << endl;
    cout << "Processing sample: " << sample << endl;
    cout << "================================================" << endl;


    accumulated.clear();


    // ------------------------------------------------------------
    // Loop over all ROOT files belonging to sample
    // ------------------------------------------------------------

    for (const string& filename : files) {

        string filepath =
            inputDir + "/hist_" + filename;

        cout << "  Opening: "
             << filepath << endl;


        TFile* file =
            TFile::Open(filepath.c_str(), "READ");


        if (!file || file->IsZombie()) {

            cerr << "ERROR: cannot open "
                 << filepath << endl;

            if (file)
                delete file;

            continue;
        }


        // Read all histograms
        processDirectory(file);


        file->Close();

        delete file;
    }


    // ------------------------------------------------------------
    // Write all combined histograms
    // ------------------------------------------------------------

    cout << "  Histograms found: "
         << accumulated.size() << endl;


    for (auto& entry : accumulated) {

        writeHistogram(
            outfile,
            entry.second,
            sample
        );

        //delete entry.second;
    }


    accumulated.clear();


    cout << "Finished sample: "
         << sample << endl;
}

void combine_histograms(// MAIN
    string inputDir = "run2_noFR_metphi_zpt_recoil_roccor_toppt_syst_signal_updated",
    string outputFile = "combined_hist.root"
)
{
    cout << endl;
    cout << "================================================" << endl;
    cout << "COMBINING HISTOGRAMS" << endl;
    cout << "Input directory : " << inputDir << endl;
    cout << "Output file     : " << outputFile << endl;
    cout << "================================================" << endl;

    TFile* outfile = TFile::Open(outputFile.c_str(),"RECREATE");


    if (!outfile || outfile->IsZombie()) {
        cerr << "ERROR: cannot create output file: "<< outputFile << endl;
        return;
    }

    for (const auto& sample : samples) {
		// Process every sample category
        combineSample(
            sample.first,
            sample.second,
            inputDir,
            outfile
        );
    }
    outfile->Write(); 
    outfile->Flush();
    outfile->Close();
    delete outfile;

    cout << endl;
    cout << "================================================" << endl;
    cout << "DONE" << endl;
    cout << "Output: " << outputFile << endl;
    cout << "================================================" << endl;
}
