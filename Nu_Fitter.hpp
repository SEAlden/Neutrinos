//
//  Nu_Fitter.cpp
//  Neutrinos
//
//  Created by Siobhan Alden & Andrew Yong on 12/06/2017.
//  Copyright © 2017 Siobhan Alden & Andrew Yong. All rights reserved.
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

#include <string>

class Nu_Fitter{
    
public:
    
    Nu_Fitter(int kNuBarVar, std::string path, std::string filename);
    ~Nu_Fitter();
 
    void make_Prediction();
    void swap();
    void print_kNu();
    double getLLH();
    
protected:
    TH1D* _Data;
    TH1D* _Prediction;
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
    std::string _path;
    std::string _filename;

};


#endif /* Nu_Fitter_hpp */
