//
//  fubar.cpp
//
//
//  Created by Siobhan Alden & Andrew Yong on 12/06/2017.
//
//

#include <stdio.h>
// #include <cmath.h>

#include <Nu_Fitter.hpp>
#include <Nu_Fitter.cpp>

int main(){


    TFile* nue = new TFile("/home/yong/Neutrinos/Prob3++.20121225/T2Kflux2016/t2kflux_2016_minus250kA.root");

    TH1D* t2k = (TH1D*)nue->Get("enu_sk_numu");// Read in data
    // TH1D* Osci = new TH1D("Neutrinos","-250 kA PMNS; Energy [GeV]; Counts", 220, 0.2, 3.0);
    TH1D* Osci = (TH1D*)nue->Get("enu_sk_numu");// Read in data

    Nu_Fitter Test = Nu_Fitter(t2k, Osci, 1);
    Test.make_Prediction();

    std::cout <<"LLH = " << Test.getLLH() << std::endl;



}
