#include "Events.h"
#include <chrono>
#include <iostream>

int main(int argc, char** argv) 
{
    auto start = std::chrono::high_resolution_clock::now();

    TFile *inputFile = new TFile(argv[1]);
    TTree *inputTree = (TTree*)inputFile->Get("Events");

    //std::cout << "break point main 1" << std::endl;
    Events e(inputTree);
    //std::cout << "break point main 2" << std::endl;
    TFile *outputFile = new TFile(argv[2], "RECREATE");
    TTree *outputTree = new TTree("AnalysisTree","a simple Tree with simple variables");
    //std::cout << "break point main 3" << std::endl;
    e.Begin(outputTree);
    //std::cout << "break point main 4" << std::endl;
    e.Loop(outputTree);
    //std::cout << "break point main 5" << std::endl;
    outputTree->Write();
    outputFile->Close();
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    std::cout << "Execution time : " << duration.count()  << " seconds" << std::endl;
}
