//
//  Nu_Fitter.cpp
//  Neutrinos
//
//  Created by Siobhan Alden & Andrew Yong on 12/06/2017.
//  Copyright © 2017 Siobhan Alden & Andrew Yong. All rights reserved.
//

#include "Nu_Fitter.hpp"
// #include <stdlib.h>



Nu_Fitter::Nu_Fitter(int kNuBarVar, std::string path, std::string filename, std::string filename2, std::string filename3, std::string filename4){
    
    _path = path;
    _filename = filename;
    _filename2 = filename2;
    _filename3 = filename3;
    _filename4 = filename4;
    TFile* nue = new TFile(_path.c_str());
    TH1D* t2k = (TH1D*)nue->Get(_filename.c_str());
    TH1D* t2k2 = (TH1D*)nue->Get(_filename2.c_str());
    TH1D* t2k3 = (TH1D*)nue->Get(_filename3.c_str());
    TH1D* t2k4 = (TH1D*)nue->Get(_filename4.c_str());
    
    _input = (TH1D*)t2k->Clone("Oscillation");
    _input2 = (TH1D*)t2k2->Clone("Oscillation");
    _input3 = (TH1D*)t2k3->Clone("Oscillation");
    _input4 = (TH1D*)t2k4->Clone("Oscillation");
    _Data  = (TH1D*)t2k->Clone("Prob");// overwrite with oscillation
    _Prediction = (TH1D*)t2k->Clone("Prob");// overwrite with markov chain
    kSquared  = true; // hard coded for now
    DM2     =  2.4e-3;
    Theta23 =  0.5   ;
    Theta13 =  0.025  ;
    dm2     =  7.6e-5;
    Theta12 =  0.312;
    BasePath = 295; //km
    Density = 2.3;
    kNuBar = kNuBarVar;// switch between neutrino and anti
    nbin  = _input->GetNbinsX();
    
    currentPars.push_back(0);
    proposedPars.push_back();
    
}


Nu_Fitter::~Nu_Fitter(){}


void Nu_Fitter::make_sum(TH1D* hist, bool oscillate){
    
    // if statement for probability for oscillation or probability of no oscillation
    int in_nu, out_nu, in_nu2, out_nu2;
    if(oscillate){
        in_nu = 2;
        out_nu = 1;
        in_nu2 = 1;
        out_nu2 = 2;
    }
    else{
        in_nu = 2;
        out_nu = 2;
        in_nu2 = 1;
        out_nu2 = 1;
    }
    
    BargerPropagator   * bNu;
    BargerPropagator   * bNu2;
    
    bNu = new BargerPropagator( );
    bNu->UseMassEigenstates( false );
    bNu2 = new BargerPropagator( );
    bNu2->UseMassEigenstates( false );
    
    double E,osci_prob,bin_content,bin_content2 ,weight;
    
    //if(abs(in_nu) >=3 || abs(out_nu) >=3){ // basic error handling
        //std::cout << "Error: neutrino must be labelled with 1,2,3. \nPrediction histogram not created." << std::endl;
   // }
    
    //else{
        
        int count = 0;
        for ( int i = 1; i<=nbin; i++){
            
            count++;
            E = _input->GetXaxis()->GetBinCenter(i);
            
            bNu->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, delta , E, kSquared, kNuBar );
            
            bNu->propagateLinear( 1*kNuBar, BasePath, Density );
            
            bNu2->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, delta , E, kSquared, -1*kNuBar );
            
            bNu2->propagateLinear( -1*kNuBar, BasePath, Density);
            // individual probabilities for each file
            osci_prob = bNu->GetProb(in_nu,out_nu);
            osci_prob2 = bNu2->GetProb(in_nu,out_nu);
            osci_prob3 = bNu2->GetProb(in_nu2,out_nu2);
            osci_prob4 = bNu2->GetProb(in_nu2,out_nu2);
            bin_content = _input->GetBinContent(i);
            bin_content2 = _input2->GetBinContent(i);
            bin_content3 = _input3->GetBinContent(i);
            bin_content4 = _input4->GetBinContent(i);

            // sum the files
            weight = osci_prob*bin_content +osci_prob2*bin_content2 + osci_prob3*bin_content3 + osci_prob4*bin_content4;
            
            hist->SetBinContent(i,weight);
            
        }
   // }
    
}



void Nu_Fitter::print_kNu(){
    
    if(kNuBar ==1){
        std::cout << "Neutrino" << std::endl;
    }
    
    else if(kNuBar == -1){
        
        std::cout << "Anti-neutrino" << std::endl;
    }
    
}

double Nu_Fitter::getLLH(TH1D* hist){
    
    double LLH = 0;
    double lambda,N;
    
    for(int j = 1; j<=nbin; j++){
        
        lambda = hist->GetBinContent(j);
        N = _input->GetBinContent(j) +_input2->GetBinContent(j) +_input3->GetBinContent(j)+_input4->GetBinContent(j);
        
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
