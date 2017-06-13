//
//  Nu_Fitter.cpp
//  Neutrinos
//
//  Created by Siobhan Alden & Andrew Yong on 12/06/2017.
//  Copyright © 2017 Siobhan Alden & Andrew Yong. All rights reserved.
//

#include "Nu_Fitter.hpp"
// #include <stdlib.h>

Nu_Fitter::Nu_Fitter(int kNuBarVar, std::string path, std::string filename){

    _path = path;
    _filename = filename;
    TFile* nue = new TFile(_path.c_str());
    TH1D* t2k = (TH1D*)nue->Get(_filename.c_str());
    _Data = (TH1D*)t2k->Clone("Oscillation");
    _Prediction = (TH1D*)t2k->Clone("Prob");
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

Nu_Fitter::Nu_Fitter(int kNuBarVar, std::string path, std::string filename, std::string filename2){

    _path = path;
    _filename = filename;
    _filename2 = filename2;
    TFile* nue = new TFile(_path.c_str());
    TH1D* t2k = (TH1D*)nue->Get(_filename.c_str());
    TH1D* t2k2 = (TH1D*)nue->Get(_filename2.c_str());


    _Data = (TH1D*)t2k->Clone("Oscillation");
    _Data2 = (TH1D*)t2k2->Clone("Oscillation");
    _Prediction = (TH1D*)t2k->Clone("Prob");
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

void Nu_Fitter::make_Prediction(int in_nu, int out_nu){

    BargerPropagator   * bNu;

    bNu = new BargerPropagator( );
    bNu->UseMassEigenstates( false );

    double E,osci_prob,bin_content,weight;

    if(abs(in_nu) >=3 || abs(out_nu) >=3){ // basic error handling
        std::cout << "Error: neutrino must be labelled with 1,2,3. \nPrediction histogram not created." << std::endl;
    }

    else{
        int count = 0;
        for ( int i = 1; i<=nbin; i++){

          count++;
          E = _Data->GetXaxis()->GetBinCenter(i);

          bNu->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, delta , E, kSquared, kNuBar );

          bNu->propagateLinear( 1*kNuBar, BasePath, Density );

          osci_prob = bNu->GetProb(in_nu,out_nu);// hard coding flavour for now;
          bin_content = _Data->GetBinContent(i);
          weight = osci_prob*bin_content;

          _Prediction->SetBinContent(i,weight);

        }

    }

}


void Nu_Fitter::make_sum(int in_nu, int out_nu){

    BargerPropagator   * bNu;

    bNu = new BargerPropagator( );
    bNu->UseMassEigenstates( false );

    double E,osci_prob,bin_content,bin_content2 ,weight;

    if(abs(in_nu) >=3 || abs(out_nu) >=3){ // basic error handling
      std::cout << "Error: neutrino must be labelled with 1,2,3. \nPrediction histogram not created." << std::endl;
    }

    else{

      int count = 0;
      for ( int i = 1; i<=nbin; i++){

          count++;
          E = _Data->GetXaxis()->GetBinCenter(i);

          bNu->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, delta , E, kSquared, kNuBar );

          bNu->propagateLinear( 1*kNuBar, BasePath, Density );

          osci_prob = bNu->GetProb(in_nu,out_nu);
          bin_content = _Data->GetBinContent(i);
          bin_content2 = _Data2->GetBinContent(i);
          weight = osci_prob*bin_content + osci_prob*bin_content2;

          _Prediction->SetBinContent(i,weight);
          
      }
    }

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
    double lambda,N;

    for(int j = 1; j<=nbin; j++){

      lambda = _Prediction->GetBinContent(j);
      N = _Data->GetBinContent(j);

      if(N!=0){ // to prevent nan at later bins(higher energies) with 0 entries
          LLH += lambda-N - N*log(lambda/N);
      }

    }

    return LLH;

}

void Nu_Fitter::show_Prediction(){

  //allows Canvas to open in
  TApplication *app = new TApplication("app",0,0);

  //PLOTTING
  TCanvas *c1 = new TCanvas("c1","Canvas",2000,1000);

  _Prediction->Draw("Hist");
  c1->Update();
  app->Run(); // need this to give options for saving and zoom etc

}
