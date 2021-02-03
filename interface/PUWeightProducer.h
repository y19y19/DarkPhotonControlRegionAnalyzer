#ifndef PUWeightProducer_h
#define PUWeightProducer_h

#include "TH1.h"
#include <string>


class PUWeightProducer {

public:
	PUWeightProducer();
	~PUWeightProducer();
	TH1F* 	PUWeightHist(std::string era);
	float 	getWeight(TH1F* ratiohist, float x);

private:
	TH1F* 	loadHisto(std::string filename, std::string histname);
	void 	normHisto(TH1F* hist);
	TH1F* 	ratio(TH1F* mc, TH1F* data);

};

#endif
