//
//  Nu_Fitter.cpp
//  Neutrinos
//
//  Created by Siobhan Alden & Andrew Yong on 12/06/2017.
//  Copyright © 2017 Siobhan Alden & Andrew Yong. All rights reserved.
//

#include "Nu_Fitter.hpp"


Nu_Fitter::Nu_Fitter(int kNuBarVar, std::string path, std::string filename1, std::string filename2, std::string filename3, std::string filename4){
    
    _path = path; // inputs the file directory
    _filename1 = filename1; // within the .root file, get each of the flux files
    _filename2 = filename2;
    _filename3 = filename3;
    _filename4 = filename4;
    
    // each _input file takes the raw histogram made from the flux files
    TFile* nu_file = new TFile(_path.c_str());
    _input1 = (TH1D*)nu_file->Get(_filename1.c_str());
    _input2 = (TH1D*)nu_file->Get(_filename2.c_str());
    _input3 = (TH1D*)nu_file->Get(_filename3.c_str());
    _input4 = (TH1D*)nu_file->Get(_filename4.c_str());
    
    _Data  = (TH1D*)_input1->Clone("Prob");// overwrite with oscillation
    _Prediction = (TH1D*)_input1->Clone("Prob");// overwrite with markov chain
    kSquared  = true; // hard coded for now
    BasePath = 295; //km
    Density = 2.3;
    kNuBar = kNuBarVar;// switch between neutrino and anti
    nbin  = _input1->GetNbinsX();
    
    //Storing oscillation parameters in vector
    currentPars.push_back(0); // energy : 0
    currentPars.push_back(2.4e-3);//DM2 : 1
    currentPars.push_back(0.5); //theta23 : 2
    currentPars.push_back(0.025); //theta13 : 3
    currentPars.push_back(7.6e-3); //dm2 : 4
    currentPars.push_back(0.312); //theta12 : 5
    currentPars.push_back(0); // deltacp : 6
    currentPars.push_back(10); // n : 7
    currentPars.push_back(1); // beta : 8
    
    proposedPars.push_back(0); // energy : 0
    proposedPars.push_back(2.4e-3);//DM2 : 1
    proposedPars.push_back(0.5); //theta23 : 2
    proposedPars.push_back(0.025); //theta13 : 3
    proposedPars.push_back(7.6e-3); //dm2 : 4
    proposedPars.push_back(0.312); //theta12 : 5
    proposedPars.push_back(0); // deltacp : 6
    proposedPars.push_back(10); // n : 7
    proposedPars.push_back(1); // beta : 8
    
    
    
    
    
}


Nu_Fitter::~Nu_Fitter(){}


void Nu_Fitter::make_sum(char hist_type, char vector_type, bool oscillate){
    
    // if statement for probability for oscillation or probability of no oscillation
    int in_nu1, out_nu1, in_nu2, out_nu2;
    
    if(oscillate){ // considers neutrino oscillation
        
        in_nu1 = 2;
        out_nu1 = 1;
        in_nu2 = 1;
        out_nu2 = 2;
        
    }
    
    else if(!oscillate){ // ensures it oscillates to itself (eg numu->numu)
        
        in_nu1 = 2;
        out_nu1 = 2;
        in_nu2 = 1;
        out_nu2 = 1;
        
    }
    
    BargerPropagator   * bNu;
    BargerPropagator   * bNu2;
    
    bNu = new BargerPropagator( );
    bNu->UseMassEigenstates( false );
    bNu2 = new BargerPropagator( );
    bNu2->UseMassEigenstates( false );
    
    double E,osci_prob1,osci_prob2,osci_prob3,osci_prob4,bin_content1,bin_content2,bin_content3,bin_content4,weight;
    
    int count = 0;
    for ( int i = 1; i<=nbin; i++){
        
        count++;
        
        E = _input1->GetXaxis()->GetBinCenter(i);
        
        if(vector_type=='c'){
            
            bNu->SetMNS( currentPars[5], currentPars[3], currentPars[2], currentPars[4], currentPars[1], currentPars[6] , E, kSquared, kNuBar );
            
            
            bNu2->SetMNS( currentPars[5], currentPars[3], currentPars[2], currentPars[4], currentPars[1], currentPars[6] , E, kSquared, -1*kNuBar );
        }
        
        else if(vector_type=='p'){
            
            bNu->SetMNS( proposedPars[5], proposedPars[3], proposedPars[2], proposedPars[4], proposedPars[1], proposedPars[6] , E, kSquared, kNuBar );
            
            
            bNu2->SetMNS( proposedPars[5], proposedPars[3], proposedPars[2], proposedPars[4], proposedPars[1], proposedPars[6] , E, kSquared, -1*kNuBar );
            
        }
        bNu->propagateLinear( 1*kNuBar, BasePath, Density );
        
        bNu2->propagateLinear( -1*kNuBar, BasePath, Density);
        
        // individual probabilities for each file
        osci_prob1 = bNu->GetProb(in_nu1,out_nu1);
        osci_prob2 = bNu2->GetProb(in_nu1,out_nu1);
        osci_prob3 = bNu2->GetProb(in_nu2,out_nu2);
        osci_prob4 = bNu2->GetProb(in_nu2,out_nu2);
        bin_content1 = _input1->GetBinContent(i);
        bin_content2 = _input2->GetBinContent(i);
        bin_content3 = _input3->GetBinContent(i);
        bin_content4 = _input4->GetBinContent(i);
        
        
        
        if(hist_type == 'd'){ // applies changes to the _Data histogram
            
            // sum the files
            weight = (1./currentPars[8])*osci_prob1*bin_content1 + currentPars[8]*osci_prob2*bin_content2 + (1./currentPars[8])*osci_prob3*bin_content3 + currentPars[8]*osci_prob4*bin_content4;
            _Data->SetBinContent(i,weight);
            
        }
        
        else if(hist_type == 'p'){ // applies changes to the _Prediction histogram
            
            // sum the files
            weight = (1./proposedPars[8])*osci_prob1*bin_content1 + proposedPars[8]*osci_prob2*bin_content2 + (1./proposedPars[8])*osci_prob3*bin_content3 + proposedPars[8]*osci_prob4*bin_content4;
            _Prediction->SetBinContent(i,weight);
            
        }
        
        else{
            
            std::cout << "Invalid Hist Type" << std::endl;
            
        }
        
        // std::cout << "Data: " << _Data->GetBinContent(i) << "\tPrediciton: " << _Prediction->GetBinContent(i) <<  std::endl;
        
    }
    
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
        
        
        if(N!=0&&lambda!=0){ // to prevent nan at later bins(higher energies) with 0 entries
            LLH += lambda-N - N*log(lambda/N);
            // std::cout << " lambda " << lambda << " Data " << N << " total LLH " << LLH << " LLH " << lambda-N - N*log(lambda/N) << std::endl;
            
        }
        
    }
    
    
    return LLH;
    
}

void Nu_Fitter::show_Prediction(){
    
    //allows Canvas to open in
    TApplication *app = new TApplication("app",0,0);
    
    //PLOTTING
    TCanvas *c1 = new TCanvas("c1","Canvas",2000,1000);
    
    _Prediction->Draw("e");
    c1->Update();
    app->Run(); // need this to give options for saving and zoom etc
    
}

std::vector<double> Nu_Fitter::return_cparam(){
    
    return currentPars;
    
}

void Nu_Fitter::set_paras(int index, double val, char vector_type){
    if(vector_type=='c'){
        currentPars[index] = val;
    }
    
    else if(vector_type == 'p'){
        proposedPars[index] = val;
    }
    
    else{
        std::cout << "Invalid command for vector_type. Please choose either 'c' or 'p'." << std::endl;
    }
    
}
