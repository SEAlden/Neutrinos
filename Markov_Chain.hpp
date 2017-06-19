//
//  Markov.hpp
//
//
//  Created by Siobhan Alden & Andrew Yong on 16/06/2017.
//
//

#ifndef Markov_Chain_hpp
#define Markov_Chain_hpp



#include <stdio.h>
#include "Nu_Fitter.hpp"
#include "TFile.h"
#include "TH1D.h"
#include "TApplication.h"

#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

#include "TROOT.h"
#include "TStyle.h"
#include "TString.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TF1.h"
#include "TF2.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TTree.h"



class Markov_Chain{

public:
    Markov_Chain(std::vector<double> currentPars, int nstep);
    ~Markov_Chain();
    void startMH(std::vector<double> currentPars, Nu_Fitter* oscObject, double width); // starts the Metropolis-Hastings algorithm
    void set_pars(int element); // if element is true, the parameter associated with the true element is varied in the Markov chain.
    void print(); // prints the proposed parameters

private:

    int steps;
    std::vector<double> proposedPars;
    double currentLLH;
    double proposedLLH;
    std::vector<bool> pars;
    TFile* file;
    TTree* outputtree;



};


#endif /* Markov_Chain_hpp */
