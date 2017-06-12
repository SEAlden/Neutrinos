//
//  Nu_Fitter.cpp
//  Neutrinos
//
//  Created by Siobhan Alden on 12/06/2017.
//  Copyright © 2017 Siobhan Alden. All rights reserved.
//

#include "Nu_Fitter.hpp"
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

Nu_Fitter::Nu_Fitter(TH1D* Data, TH1* Prediction, int kNuBarVar){



    _Data = (TH1D*)Data->Clone("Oscillation");
    _Prediction = (TH1*)Prediction->Clone("Prob");
    kSquared  = true; // hard coded for now
    DM2     =  2.4e-3;
    Theta23 =  0.5   ;
    Theta13 =  0.025  ;
    dm2     =  7.6e-5;
    Theta12 =  0.312;
    BasePath = 295; //km
    Density = 2.3;
    kNuBar = kNuBarVar;// switch between neutrino and anti
    nbin  = _Data->GetNbinsX();
    

    

}

Nu_Fitter::~Nu_Fitter(){}

TH1*   Nu_Fitter::make_Prediction(){

    BargerPropagator   * bNu;
    
    bNu = new BargerPropagator( );
    bNu->UseMassEigenstates( false );
    
    int count = 0;
    for ( int i = 1; i<=nbin; i++){
        count++;
        double E = _Data->GetXaxis()->GetBinCenter(i);
        //std::cout << "i " << i  << std::endl;
        
//        std::cout <<Theta12 << " " <<  Theta13 << " " << Theta23 << " " << dm2 << " " << DM2 << " " << delta << " " << E << " " <<  kSquared << " " <<  kNuBar << std::endl;
        bNu->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, delta , E, kSquared, kNuBar );
        
        bNu->propagateLinear( 1*kNuBar, BasePath, Density );
   
        double osci_prob = bNu->GetProb(2,2);// hard coding flavour for now;
        
        double bin_content = _Data->GetBinContent(i);
  
        double weight = osci_prob*bin_content;
              std::cout << "i " << i << " E " << E << " bin cont " << bin_content  << " osci prob " << osci_prob << " weight " << weight  << std::endl;
        _Prediction->Fill(E,weight);
        std::cout << _Prediction->GetBinContent(i) << std::endl;
        
        
    }
    std::cout << " count " << count << std::endl;
    return _Prediction;
 
}

void Nu_Fitter::swap(){

    kNuBar = -1*kNuBar;
}

void Nu_Fitter::print_kNu(){
    
    if(kNuBar ==1){
        std::cout << "Neutrino" << std::endl;
    }
    else if(kNuBar == -1){
    
        std::cout << "Anti-neutrino" << std::endl;
    }
}

double Nu_Fitter::getLLH(){
    
    double LLH = 0;
    //make_Prediction();

    for(int j = 1; j<=nbin; j++){
    
        
        double lambda = _Prediction->GetBinContent(j);
        double N = _Data->GetBinContent(j);
        //std::cout << j << " " << lambda <<  " " << N << std::endl;
        LLH+= lambda-N - N*log(lambda/N);
    
        //std::cout << j << " " << LLH <<std::endl;
    }
    
    return LLH;
    
}





