//
//  Nu_Fitter.hpp
//  Neutrinos
//
//  Created by Siobhan Alden on 12/06/2017.
//  Copyright © 2017 Siobhan Alden. All rights reserved.
//

#ifndef Nu_Fitter_hpp
#define Nu_Fitter_hpp

#include <math.h>
#include <iostream>
#include <fstream>

#include "BargerPropagator.h"

#include "TFile.h"
#include "TH1D.h"

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

#include <stdio.h>

class Nu_Fitter{

public:
    
    Nu_Fitter(TH1D* Data, TH1* Prediction, int kNuBarVar);
    ~Nu_Fitter();
    // get data & get prediction === copy constructor for existing objects
    TH1* make_Prediction();
    void swap();
    void print_kNu();
    double getLLH();
    
protected:
    TH1D* _Data;
    TH1* _Prediction;
    bool kSquared;   // using sin^2(x) variables?
    double DM2;
    double Theta23;
    double Theta13;
    double dm2;
    double Theta12;
    double delta   =  0 * (3.1415926/180.0); //convert to radians
    int kNuBar; // positive for neutrino, negative for antineutrino
    double BasePath; //km
    double Density;
    int nbin;
   
};


#endif /* Nu_Fitter_hpp */

