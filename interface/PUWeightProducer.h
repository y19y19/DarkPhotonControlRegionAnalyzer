#ifndef PUWeightProducer_h
#define PUWeightProducer_h

#include "TH1.h"
#include <string>


class PUWeightProducer {

public:
	PUWeightProducer();
	~PUWeightProducer();
	TH1* 	PUWeightHist(std::string era);
	float 	getWeight(TH1* ratiohist, float x);

private:
	TH1* 	loadHisto(std::string filename, std::string histname);
	void 	normHisto(TH1* hist);
	TH1* 	ratio(TH1* mc, TH1* data);

};

#endif
