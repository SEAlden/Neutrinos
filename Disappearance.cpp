//
//  Disappearance.cpp
//  
//
//  Created by Siobhan Alden on 13/06/2017.
//
//

#include "Disappearance.hpp"

#include <iostream>
Disappearance::Disappearance(int kNuBarVar, std::string path, std::string filename, std::string filename2, int mass):Nu_Fitter(kNuBarVar, path, filename, filename2){
 
    if (mass == 1){
        mass = dm2;
    }
    
    else if (mass ==2){
        mass=DM2;
    }
    
    else{
        std::cout << "wrong input" << std::endl;
    }
    
    a = 1.27*L*mass;
    

}

Disappearance::~Disappearance(){}

void Disappearance::make_Prediction(int n,int which, int heirachy){

    for(int j = 1; j <= nbin; j++){
            
        double Eng = _Data->GetBinCenter(j);
        double bincon = _Data->GetBinContent(j);
        double bincon2 = _Data2->GetBinContent(j);
        double prob,weight;
        
        if(which == 1){
            prob = series(n, Eng, dm_sq);
            weight = prob*bincon + prob*bincon2;
            _Prediction->SetBinContent(j,weight);
        }
        
        else if(which == 2){
        
            prob = approx(Eng, dm_sq);
            weight = prob*bincon + prob*bincon2;
            _Prediction->SetBinContent(j,weight);

        }
        
        else if(which == 3){
        
            prob = osci_prob(Eng, dm_sq);
            weight = prob*bincon + prob*bincon2;
            _Prediction->SetBinContent(j,weight);
        
        }
        
        else{
            std::cout << "Incorrect series choice" << std::endl;
        }
        
    }
  
}

double Disappearance::series(int n, double E, int heirachy){
    

    
    double tot = 0;
        
    for(int k = 1; k<=n;k++){
            
        double series = (-1)*(pow((-1),k)*pow(2,(-1+2*k))*pow((a/E),2*k))/(fact(2*k));
            
        tot = tot + series;
            
    }
        
    double coef = sin(2.0*Theta23);
        
    double coef_sq = coef*coef;
        
    return 1-coef_sq*tot;
    
    
}

double Disappearance::fact(int n){

    double f = 1;
    if(n >= 1){
        
        for(int j = 1; j <=n; j++){
            f = f*j;
        }
    }
    return f;

}

double Disappearance::approx(double E, int heirachy){
    
 
  
    double sin_E = sin(a/E);
    double sin_sq = sin_E*sin_E;
    
    double coef = sin(2.0*Theta23);
    double coef_sq = coef*coef;
    
    return 1-coef_sq*sin_sq;

}
/*
void Disappearance::mass(int heirachy){
    
    if (heirachy == 1){
        dm_sq = dm2;
    }
    
    else if (heirachy == 2){
        dm_sq = DM2;
    }
    
    else{
        std::cout << "Incorrect Mass difference chosen." << std::endl;
    }

}
*/
double Disappearance::osci_prob(double E, int heirachy){


    double sin_E = sin(a/E);
    double sin_sq = sin_E*sin_E;
    
    double coef = cos(Theta13)*cos(Theta13)*sin(Theta23)*sin(Theta23);//complete expression
    
    return 1.0-(4.0*coef*sin_sq-coef*coef*sin_sq);
    

}
