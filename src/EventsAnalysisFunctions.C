
#include "HEPMathTools.h"
#include "Events.h"
#include "TLorentzVector.h"
#include "TH2.h"
#include "TStyle.h"
#include <iostream>
#include <fstream>
#include <cmath>


std::pair<bool,std::array<int,2>> Events::FindMuonPair(Long64_t entry) {
 
    double mp_pt = -1;
    int mp_index = -1;
    double mm_pt = -1;
    int mm_index = -1;
 
    for (unsigned int i = 0; i < *nMuon; i++) {
        if (Muon_tightId[i] && Muon_charge[i] == +1 && Muon_pt[i] > mp_pt) {
            mp_pt = Muon_pt[i];
            mp_index = i;
        }
        else if (Muon_tightId[i] && Muon_charge[i] == -1 && Muon_pt[i] > mm_pt) {
            mm_pt = Muon_pt[i];
            mm_index = i;
        }
    }

    int leading_muon_index = -1;
    int subleading_muon_index = -1;
 
    if (mp_pt > mm_pt) {
        leading_muon_index = mp_index;
        subleading_muon_index = mm_index;
    }
    else {
        leading_muon_index = mm_index;
        subleading_muon_index = mp_index;
    }

    std::array<int,2> indexArray;
    indexArray[0] = leading_muon_index;
    indexArray[1] = subleading_muon_index;

    if (mm_index == -1 || mp_index == -1) return {false, indexArray};
    else return {true, indexArray};

}


std::pair<bool,int> Events::FindCRJet(Long64_t entry, TLorentzVector m1, TLorentzVector m2) {

    fReader.SetEntry(entry);

    bool FSRJetExist = false;
    bool CRJetExist = false;
    int Jet_index_CR = 0;
    float CRJet_MaxPt = 0;
    for (unsigned int i = 0; i < *nJet; i++) {
        TLorentzVector jet_p4;
        jet_p4.SetPtEtaPhiM(Jet_pt[i],Jet_eta[i],Jet_phi[i],Jet_mass[i]);
        float MuMuMass = (m1 + m2).M();
        float MuMuJetMass = (m1 + m2 + jet_p4).M();
        float deltaR_leadingMu_jet = m1.DeltaR(jet_p4);
        float deltaR_subleadingMu_jet = m2.DeltaR(jet_p4);
        if (deltaR_leadingMu_jet > 0.4 && deltaR_subleadingMu_jet > 0.4 && abs(Jet_eta[i]) < 2.5) {
            if (JetInFSRRegion(MuMuMass, MuMuJetMass)) {
                FSRJetExist = true;
                break; // Event will be discarded as long as a FSR Jet exist.
            }
            if (JetInCRRegion(MuMuMass, MuMuJetMass)) {
                CRJetExist = true;
                if (Jet_pt[i] > CRJet_MaxPt) {
                    Jet_index_CR = i;
                    CRJet_MaxPt = Jet_pt[i];
                }
            }
        }
    }
    if (FSRJetExist == false && CRJetExist == true) return {true, Jet_index_CR};
    else return {false, -1};
}


bool Events::JetInFSRRegion(float MuMuMass, float MuMuJetMass) {
    if (MuMuMass < 85.19 && MuMuMass > 0 && MuMuJetMass < 120 && MuMuJetMass > 85) return true;
    else return false;
}


bool Events::JetInCRRegion(float MuMuMass, float MuMuJetMass) {
    if (MuMuMass > 10 && MuMuMass < 80 && MuMuJetMass > 140) return true;
    else return false;
}
