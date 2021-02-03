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
TH1F* PUWeightProducer::loadHisto(std::string filename, std::string histname) {

	TFile* rootfile = new TFile(filename.c_str());
	TH1F* hist = (TH1F*)rootfile->Get(histname.c_str());
	rootfile->Close();
	return hist;

}

// Histogram normalization
void PUWeightProducer::normHisto(TH1F* hist) {

	hist->Scale(1.0/hist->Integral());

}

// Calculate ratio for two histograms. data_norm/mc_norm.
TH1F* PUWeightProducer::ratio(TH1F* mc, TH1F* data) {

	TH1F* ratiohist = (TH1F*)mc->Clone("hweights");
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
float PUWeightProducer::getWeight(TH1F* ratiohist, float x) {

	int bin = std::max(1, std::min(ratiohist->GetNbinsX(),ratiohist->GetXaxis()->FindBin(x)));
	return ratiohist->GetBinContent(bin);

}

// Get the PUWeight histogram for each year.
TH1F* PUWeightProducer::PUWeightHist(std::string era) {

	TH1F* datahist;
	TH1F* mchist;
	if (era == "2016") {
		datahist = (TH1F*)loadHisto("",""); // data root file and histo name
		mchist = (TH1F*)loadHisto("","");
	}

	if (era == "2017") {
		datahist = (TH1F*)loadHisto("",""); // data root file and histo name
		mchist = (TH1F*)loadHisto("","");
	}
	
	if (era == "2018") {
		datahist = (TH1F*)loadHisto("",""); // data root file and histo name
		mchist = (TH1F*)loadHisto("","");
	}
	else {
		std::cout << "Error: You are inputing an era that the analysis cannot cover" << std::endl;
		return 0;
	}
	normHisto(datahist);
	normHisto(mchist);

	TH1F* ratiohist = (TH1F*)ratio(mchist, datahist);
	return ratiohist;
}


// Read Pileup_nTrueInt from NanoAOD


// Put PUWeight into output tree
