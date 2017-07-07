//
//  Disappearance.hpp
//  
//
//  Created by Siobhan Alden on 13/06/2017.
//
//

#ifndef Disappearance_hpp
#define Disappearance_hpp


#include "BargerPropagator.h"

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
#include "TGraph.h"

#include <stdio.h>
#include "Nu_Fitter.hpp"
//#include "Nu_Fitter.cpp"
#include <iostream>
#include <vector>

class Disappearance : public Nu_Fitter {
    
public:
    
    Disappearance(int kNuBarVar, std::string path, std::string filename, std::string filename2, std::string filename3, std::string filename4, int mass);
    ~Disappearance();
    void make_Prediction(char hist_type, int which);
    double series( double E);
    double fact(int n);
    double approx( double E);
    double osci_prob( double E);
    double taylorinv(double x, std::vector<double>& par);
    void taylor(char hist_type, std::vector<double>& pars);
    //std::vector<double> return_cparam();
//    void make_2d();
//    double function(std::vector<double> pars, double E);
    

    
private:
    
    double L = 295;
    double dm_sq;
    double a;
    std::vector<double> Ene, invE, prob;
    //std::vector<std::string> parsName;
    //std::vector<double> coefs;
    std::vector<double> bin1;
    std::vector<double> bin2;
    std::vector<double> bin3;
    std::vector<double> bin4;
//    TFile* outfile2d;
//    TFile* file;
//    TFile* file2;
//    TTree* pick;
//    TH2D* hFunction;
//    TTree* tree;
    //std::vector<double> pars;

    
    
};

#endif /* Disappearance_hpp */
