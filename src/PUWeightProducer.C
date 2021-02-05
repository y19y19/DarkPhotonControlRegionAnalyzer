#include "PUWeightProducer.h"
#include "TH1.h"
#include "TFile.h"
#include "TStyle.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

// Note the pile up reweighting is only applied on the MC samples

PUWeightProducer::PUWeightProducer() {};
PUWeightProducer::~PUWeightProducer() {};

// Load histogram
TH1* PUWeightProducer::loadHisto(std::string filename, std::string histname) {

    //std::cout << "break point PU 1"<< std::endl;
	TFile* rootfile = new TFile(filename.c_str());
	TH1* hist = (TH1*)rootfile->Get(histname.c_str());
    hist->SetDirectory(0);
	rootfile->Close();
	return hist;

}

// Histogram normalization
void PUWeightProducer::normHisto(TH1* hist) {
    //std::cout << "break point PU 2"<< std::endl;
    //if (hist) std::cout << "hist exists" << std::endl;
    int nbins=hist->GetNcells();
    //std::cout << "break point PU p " << std::endl;
    Double_t weight = hist->Integral();
	//std::cout << "break point PU s" << std::endl;
    hist->Scale(1.0/weight);

}

// Calculate ratio for two histograms. data_norm/mc_norm.
TH1* PUWeightProducer::ratio(TH1* mc, TH1* data) {
    //std::cout << "break point PU 3"<< std::endl;
	TH1* ratiohist = (TH1*)mc->Clone("hweights");
	int nbinsMC = mc->GetNbinsX();
	int nbinsData = data->GetNbinsX();

	if (nbinsData != nbinsMC) {
		std::cout << "ERROR:" << '\n' << "PUWeightProducer: Data and MC profile have different number of bins" << '\n' << "Program exit" << std::endl;
		return 0;
	}

	int nbins = nbinsMC;
	for (unsigned int i = 0; i < nbins; i++) {
		float weight = mc->GetBinContent(i+1) != 0 ? data->GetBinContent(i+1)/mc->GetBinContent(i+1) : 1;
		ratiohist->SetBinContent(i+1, weight);
	}

	return ratiohist;
}

// Get the corresponding weight from the PUWeight histogram, based on x(numbebr of vertex) value.
float PUWeightProducer::getWeight(TH1* ratiohist, float x) {
    //std::cout << "break point PU 4"<< std::endl;
	int bin = std::max(1, std::min(ratiohist->GetNbinsX(),ratiohist->GetXaxis()->FindBin(x)));
	return ratiohist->GetBinContent(bin);

}

// Get the PUWeight histogram for each year.
TH1* PUWeightProducer::PUWeightHist(std::string era) {
    //std::cout << "break point PU 5"<< std::endl;
    // Root files and histograms used here are directly copied from NanoAOD Tools.
	if (era == "2016") {
		TH1* datahist = (TH1*)loadHisto("/uscms/home/yyao/nobackup/DarkPhoton_2/condor/CMSSW_10_2_24_patch1/src/ControlRegion/2016/scripts_mc/DarkPhotonControlRegionAnalyzer/data/PileUpHistograms/PileupData_GoldenJSON_Full2016.root","pileup"); // data root file and histo name
		TH1* mchist = (TH1*)loadHisto("/uscms/home/yyao/nobackup/DarkPhoton_2/condor/CMSSW_10_2_24_patch1/src/ControlRegion/2016/scripts_mc/DarkPhotonControlRegionAnalyzer/data/PileUpHistograms/pileup_profile_Summer16.root","pu_mc");
        
        normHisto(datahist);
        normHisto(mchist);

        TH1* ratiohist = (TH1*)ratio(mchist, datahist);
        return ratiohist;

	}

	else if (era == "2017") {
		TH1* datahist = (TH1*)loadHisto("../data/PileupHistogram-goldenJSON-13tev-2017-99bins_withVar.root",""); // data root file and histo name
		TH1* mchist = (TH1*)loadHisto("../data/mcPileup2017.root","");

        normHisto(datahist);
        normHisto(mchist);

        TH1* ratiohist = (TH1*)ratio(mchist, datahist);
        return ratiohist;
	}
	
	else if (era == "2018") {
		TH1* datahist = (TH1*)loadHisto("../data/PileupHistogram-goldenJSON-13tev-2018-100bins_withVar.root",""); // data root file and histo name
		TH1* mchist = (TH1*)loadHisto("../data/mcPileup2018.root","");

        normHisto(datahist);
        normHisto(mchist);

        TH1* ratiohist = (TH1*)ratio(mchist, datahist);
        return ratiohist;
	}
	else {
		std::cout << "Error: You are inputing an era that the analysis cannot cover" << std::endl;
		return 0;
	}
}


// Read Pileup_nTrueInt from NanoAOD


// Put PUWeight into output tree
