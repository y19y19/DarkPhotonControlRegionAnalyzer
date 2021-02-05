#include "HEPMathTools.h"
#include "TMath.h"
#include <cmath>
#include <iostream>
// Function definition

Float_t deltaPhi(float phi0, float phi1) {
    //std::cout << "break point MT 1"<< std::endl;
    float result = phi0 - phi1;
    while (result > TMath::Pi()) result -= 2*TMath::Pi();
    while (result <= -TMath::Pi()) result += 2*TMath::Pi();
    return result;
}

Float_t deltaR(float phi0, float phi1, float eta0, float eta1) {
    //std::cout << "break point MT 2"<< std::endl;
    float deta = eta0 - eta1;
    float dphi = deltaPhi(phi0,phi1);
    return TMath::Sqrt(pow(deta,2)+pow(dphi,2));
}
