// The class definition in Events.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("Events.C")
// root> T->Process("Events.C","some options")
// root> T->Process("Events.C+")
//

#include "Events.h"
#include "HEPMathTools.h"
#include "PUWeightProducer.h"
#include "TLorentzVector.h"
#include <iostream>
#include <fstream>
#include <cmath>


Events::Events(TTree *tree) 
{
    Init(tree);
}

Events::~Events()
{
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

void Events::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).
   fChain = tree;
   fReader.SetTree(tree);
}

Bool_t Events::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Events::Begin(TTree *outputTree) {
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   //TString option = GetOption()

    //std::cout << "break point EM 1"<< std::endl;
    // Set Output tree branches
    outputTree->Branch("cut0",&cut0,"cut0/O");
    outputTree->Branch("cut1",&cut1,"cut1/O");
    outputTree->Branch("cut2",&cut2,"cut2/O");
    outputTree->Branch("cut3",&cut3,"cut3/O");
    outputTree->Branch("cut4",&cut4,"cut4/O");
    outputTree->Branch("cut5",&cut5,"cut5/O");
    outputTree->Branch("HBHENoiseFilter",&HBHENoiseFilter,"HBHENoiseFilter/O");
    outputTree->Branch("HBHENoiseIsoFilter",&HBHENoiseIsoFilter,"HBHENoiseIsoFilter/O");
    outputTree->Branch("puWeight",&puWeight,"puWeight/F");
    outputTree->Branch("genWeight",&Weight,"genWeight/F"); // this is already undated every time when load outputTree
    outputTree->Branch("leadingMuPt",&leadingMuPt,"leadingMuPt/F");
    outputTree->Branch("leadingMuEta",&leadingMuEta,"leadingMuEta/F");
    outputTree->Branch("leadingMuPhi",&leadingMuPhi,"leadingMuPhi/F");
    outputTree->Branch("leadingMuMass",&leadingMuMass,"leadingMuMass/F");
    outputTree->Branch("subleadingMuPt",&subleadingMuPt,"subleadingMuPt/F");
    outputTree->Branch("subleadingMuEta",&subleadingMuEta,"subleadingMuEta/F");
    outputTree->Branch("subleadingMuPhi",&subleadingMuPhi,"subleadingMuPhi/F");
    outputTree->Branch("subleadingMuMass",&subleadingMuMass,"subleadingMuMass/F");
    outputTree->Branch("MuMuMass",&MuMuMass,"MuMuMass/F");
    outputTree->Branch("MuMuJetMass",&MuMuJetMass,"MuMuJetMass/F");
    outputTree->Branch("deltaR_MuMu",&deltaR_MuMu,"deltaR_MuMu/F");
    outputTree->Branch("deltaR_leadingMu_jet",&deltaR_leadingMu_jet,"deltaR_leadingMu_jet/F");
    outputTree->Branch("deltaR_subleadingMu_jet",&deltaR_subleadingMu_jet,"deltaR_subleadingMu_jet/F");
    outputTree->Branch("jet_electronEnergyFraction",&jet_electronEnergyFraction,"jet_electronEnergyFraction/F");
    outputTree->Branch("jet_muonEnergyFraction",&jet_muonEnergyFraction,"jet_muonEnergyFraction/F");
    outputTree->Branch("jet_n90",&jet_n90,"jet_n90/F");
    outputTree->Branch("jet_chargedHadronMultiplicity",&jet_chargedHadronMultiplicity,"jet_chargedHadronMultiplicity/F");
    outputTree->Branch("jet_chargedMultiplicity",&jet_chargedMultiplicity,"jet_chargedMultiplicity/F");
    outputTree->Branch("jet_n60",&jet_n60,"jet_n60/F");
    outputTree->Branch("jet_neutralHadronMultiplicity",&jet_neutralHadronMultiplicity,"jet_neutralHadronMultiplicity/F");
    outputTree->Branch("jet_neutralMultiplicity",&jet_neutralMultiplicity,"jet_neutralMultiplicity/F");
    outputTree->Branch("jet_nConstituents",&jet_nConstituents,"jet_nConstituents/F");
    outputTree->Branch("jet_pt",&jet_pt,"jet_pt/F");
    outputTree->Branch("jet_chargedEmEnergyFraction",&jet_chargedEmEnergyFraction,"jet_chargedEmEnergyFraction/F");
    outputTree->Branch("jet_chargedHadronEnergyFraction",&jet_chargedHadronEnergyFraction,"jet_chargedHadronEnergyFraction/F");
    outputTree->Branch("jet_neutralEmEnergyFraction",&jet_neutralEmEnergyFraction,"jet_neutralEmEnergyFraction/F");
    outputTree->Branch("jet_neutralHadronEnergyFraction",&jet_neutralHadronEnergyFraction,"jet_neutralHadronEnergyFraction/F");
    outputTree->Branch("jet_et",&jet_et,"jet_et/F");
    outputTree->Branch("jet_eta",&jet_eta,"jet_eta/F");
    outputTree->Branch("jet_phi",&jet_phi,"jet_phi/F");
    outputTree->Branch("jet_PtSumOfNeutralHadron",&jet_PtSumOfNeutralHadron,"jet_PtSumOfNeutralHadron/F");
    outputTree->Branch("jet_PtSumOfChargedHadron",&jet_PtSumOfChargedHadron,"jet_PtSumOfChargedHadron/F");
    outputTree->Branch("jet_puId",&jet_puId,"jet_puId/I");
    outputTree->Branch("jet_Id",&jet_Id,"jet_Id/I");
}

/*
void Events::SlaveBegin(TTree * tree)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}
*/


Bool_t Events::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

    //std::cout << "break point EM 2"<< std::endl;
    fReader.SetEntry(entry);
    //std::cout << "break point EM s" << std::endl;
    // Initialize essential booleans

    bool EnergyFractionCutPass = false;
 
    // Copy the basic branches from input tree to output tree 
    Weight = *genWeight;
    HBHENoiseIsoFilter = *Flag_HBHENoiseIsoFilter;
    HBHENoiseFilter = *Flag_HBHENoiseFilter;
    //std::cout << "break point EM q" << std::endl;
    // Get PUWeight
    int nvtx = *Pileup_nTrueInt;
    puWeight = pup.getWeight(puWeight2016,nvtx);
    //std::cout << "break point EM p" << std::endl;
    // Find a pair of muons with opposite charges
    std::pair<bool,std::array<int,2>> findMuonPairIndex = FindMuonPair(entry); 

    // Initialize the findCRJetIndex
    std::pair<bool,int> findCRJetIndex = {false,0};

    if (findMuonPairIndex.first == true) {
        std::array<int,2> muonPairIndex = findMuonPairIndex.second;
        int leading_muon_index = muonPairIndex[0];
        int subleading_muon_index = muonPairIndex[1];

        TLorentzVector m1;
        TLorentzVector m2;
        
        m1.SetPtEtaPhiM(Muon_pt[leading_muon_index],Muon_eta[leading_muon_index],Muon_phi[leading_muon_index],Muon_mass[leading_muon_index]);
        m2.SetPtEtaPhiM(Muon_pt[subleading_muon_index],Muon_eta[subleading_muon_index],Muon_phi[subleading_muon_index],Muon_mass[subleading_muon_index]);

        findCRJetIndex = FindCRJet(entry, m1, m2);

        if (findCRJetIndex.first) {
            TLorentzVector mumu = m1 + m2;
            TLorentzVector jet_p4;
            int Jet_index_CR = findCRJetIndex.second;
            jet_p4.SetPtEtaPhiM(Jet_pt[Jet_index_CR],Jet_eta[Jet_index_CR],Jet_phi[Jet_index_CR],Jet_mass[Jet_index_CR]);

            MuMuMass = mumu.M();
            leadingMuPt = Muon_pt[leading_muon_index];
            leadingMuEta = Muon_eta[leading_muon_index];
            leadingMuPhi = Muon_phi[leading_muon_index];
            leadingMuMass = Muon_mass[leading_muon_index];
            subleadingMuPt = Muon_pt[subleading_muon_index];
            subleadingMuEta = Muon_eta[subleading_muon_index];
            subleadingMuPhi = Muon_phi[subleading_muon_index];
            subleadingMuMass = Muon_mass[subleading_muon_index];
            deltaR_MuMu =  deltaR(Muon_phi[leading_muon_index], Muon_phi[subleading_muon_index], Muon_eta[leading_muon_index], Muon_eta[subleading_muon_index]);
            MuMuJetMass = (m1 + m2 + jet_p4).M();
            deltaR_leadingMu_jet = deltaR(Muon_phi[leading_muon_index], Jet_phi[Jet_index_CR], Muon_eta[leading_muon_index], Jet_eta[Jet_index_CR]);
            deltaR_subleadingMu_jet = deltaR(Jet_phi[Jet_index_CR], Muon_phi[subleading_muon_index], Jet_eta[Jet_index_CR], Muon_eta[subleading_muon_index]);
            EnergyFractionCutPass = Jet_neEmEF[Jet_index_CR] < 0.2 && Jet_neHEF[Jet_index_CR] > 0.6 && Jet_chHEF[Jet_index_CR] < 0.3 && Jet_chHEF[Jet_index_CR] > 0.02;
            jet_electronEnergyFraction = Jet_electronEF[Jet_index_CR];
            jet_muonEnergyFraction = Jet_muonEF[Jet_index_CR];
            jet_n90 = static_cast<float>(Jet_n90[Jet_index_CR]);
            jet_chargedHadronMultiplicity = static_cast<float>(Jet_chHMP[Jet_index_CR]);
            jet_chargedMultiplicity = static_cast<float>(Jet_chMP[Jet_index_CR]);
            jet_n60 = static_cast<float>(Jet_n60[Jet_index_CR]);
            jet_neutralHadronMultiplicity = static_cast<float>(Jet_neHMP[Jet_index_CR]);
            jet_neutralMultiplicity = static_cast<float>(Jet_neMP[Jet_index_CR]);
            jet_nConstituents = static_cast<float>(Jet_nConstituents[Jet_index_CR]);
            jet_pt = Jet_pt[Jet_index_CR];
            jet_chargedEmEnergyFraction = Jet_chEmEF[Jet_index_CR];
            jet_chargedHadronEnergyFraction = Jet_chHEF[Jet_index_CR];
            jet_neutralEmEnergyFraction = Jet_neEmEF[Jet_index_CR];
            jet_neutralHadronEnergyFraction = Jet_neHEF[Jet_index_CR];
            jet_et = pow(pow(Jet_pt[Jet_index_CR],2)+pow(Jet_mass[Jet_index_CR],2),0.5);
            jet_eta = Jet_eta[Jet_index_CR];
            jet_phi = Jet_phi[Jet_index_CR];
            jet_PtSumOfNeutralHadron = Jet_PtSumOfNeutralHadrons[Jet_index_CR];
            jet_PtSumOfChargedHadron = Jet_PtSumOfChargedHadrons[Jet_index_CR];
            jet_Id = Jet_jetId[Jet_index_CR];
            jet_puId = Jet_puId[Jet_index_CR];
        }
    }


    // Fill the tree with the pass/fail info for each cut 
    cut0 = false;
    cut1 = false;
    cut2 = false;
    cut3 = false;
    cut4 = false;
    if (findCRJetIndex.first && MuMuMass > 10) cut0 = true;
    if (cut0 == true && (*HLT_IsoMu24 || *HLT_IsoTkMu24)) cut1 = true;
    if (cut1 == true && (leadingMuPt > 24 && subleadingMuPt > 10)) cut2 = true;
    if (cut2 == true && deltaR_MuMu > 0.4) cut3 = true;
    if (cut3 == true && EnergyFractionCutPass) cut4 = true;
    
    return cut0;
}


void Events::Loop(TTree *outputTree) {
    //std::cout << "break point EM 3"<< std::endl;
    if (fChain == 0) return;
    Long64_t nentries = fChain->GetEntriesFast();
    //std::cout << "Number of events: " << nentries << std::endl;
    // Only the events pass cut0 will be recorded 
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Bool_t cut0 = Process(jentry);
        if (cut0) outputTree->Fill();
    }
}

/*
void Events::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Events::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
*/

