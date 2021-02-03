#include "Events.h"
#include <chrono>

int main(int argc, char** argv) 
{
    auto start = std::chrono::high_resolution_clock::now();

    TFile *inputFile = new TFile(argv[1]);
    TTree *inputTree = (TTree*)inputFile->Get("Events");
    Events e(inputTree);

    TFile *outputFile = new TFile(argv[2], "RECREATE");
    TTree *outputTree = new TTree("AnalysisTree","a simple Tree with simple variables");
    e.Begin(outputTree);
    e.Loop(outputTree);
    outputTree->Write();
    outputFile->Close();
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    std::cout << "Execution time : " << duration.count()  << " seconds" << std::endl;
}
