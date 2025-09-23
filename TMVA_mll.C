#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TROOT.h>
#include <TMVA/Factory.h>
#include <TMVA/DataLoader.h>
#include <TMVA/Tools.h>

void TMVA_mll() {
    // Output file
    TFile* outputFile = TFile::Open("TMVA_output.root", "RECREATE");
	TDirectory* tau0Dir = outputFile->mkdir("0tau");
	TDirectory* tau1Dir = outputFile->mkdir("1tau");
	TDirectory* tau2Dir = outputFile->mkdir("2tau");
	TDirectory* tau3Dir = outputFile->mkdir("3tau");
	TDirectory* lep3tau0Dir = outputFile->mkdir("3lep0tau");
	TDirectory* lep3tau1Dir = outputFile->mkdir("3lep1tau");
	TDirectory* lep3tau2Dir = outputFile->mkdir("3lep2tau");   
    // Load your input tree
    TFile* input = TFile::Open("mergedTMVA_input.root"); // your input file
    for(auto rootDirName: {"0tau","1tau","2tau","3tau","3lep0tau","3lep1tau","3lep2tau"}){
    	std::string treeName = rootDirName;
	  	TDirectory *dir = (TDirectory*)input->Get(rootDirName);
		TTree* tree = (TTree*)dir->Get("Events");
		
		TDirectory* odir = (TDirectory*)outputFile->Get(rootDirName);
    	odir->cd();

		TMVA::Tools::Instance();
		// Factory
		TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outputFile,
		    "!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification");

		// DataLoader
		std::string dataset_name = rootDirName;
		dataset_name += "/dataset";
		TMVA::DataLoader *dataloader = new TMVA::DataLoader(dataset_name.c_str());

		// Add variables
		dataloader->AddVariable("mll1", 'D');
		dataloader->AddVariable("mll2", 'D');
		dataloader->AddVariable("dR1", 'D');
		dataloader->AddVariable("dR2", 'D');
		dataloader->SetWeightExpression("evtwt");
		// Add the tree to TMVA
		dataloader->AddSignalTree(tree, 1.0);      // signal = classID == 1
		dataloader->AddBackgroundTree(tree, 1.0);  // background = classID == 0
		 
		dataloader->PrepareTrainingAndTestTree("classID == 1","classID == 0",
		    "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V");

		// Train a Fisher Discriminant or BDT
		//factory->BookMethod(dataloader, TMVA::Types::kFisher, "Fisher", "");
		factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT", "NTrees=100:MinNodeSize=2.5%:BoostType=AdaBoost:SeparationType=GiniIndex");

		factory->TrainAllMethods();
		factory->TestAllMethods();
		factory->EvaluateAllMethods();
	}
    outputFile->Close();

    std::cout << "===> TMVA training complete!" << std::endl;
}
