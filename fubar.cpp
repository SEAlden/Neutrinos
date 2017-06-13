//
//  fubar.cpp
//  
//
//  Created by Siobhan Alden on 12/06/2017.
//
//

#include <stdio.h>

#include <Nu_Fitter.hpp>
#include <Nu_Fitter.cpp>

int main(){


    TFile* nue = TFile::Open("t2kflux_2016_minus250kA.root");
    TH1D* t2k = (TH1D*)nue->Get("enu_sk_numu");// Read in data
    
    TH1D* Osci = (TH1D*)nue->Get("enu_sk_numu");

    Nu_Fitter Test(t2k, Osci, 1);
    Test.make_Prediction();
    
    std::cout << Test.getLLH() << std::endl;
    
    
    

}
