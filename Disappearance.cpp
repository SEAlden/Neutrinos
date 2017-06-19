//
//  Disappearance.cpp
//  
//
//  Created by Siobhan Alden on 13/06/2017.
//
//

#include "Disappearance.hpp"
#include <iostream>
#include <vector>

Disappearance::Disappearance(int kNuBarVar, std::string path, std::string filename, std::string filename2, std::string filename3, std::string filename4, int mass):Nu_Fitter(kNuBarVar, path, filename, filename2, filename3, filename4){
 
    if (mass == 1){
        dm_sq = currentPars[4];
    }
    
    else if (mass ==2){
        dm_sq = currentPars[1];
    }
    
    else{
        std::cout << "wrong input" << std::endl;
    }
    
    a = 1.27*L*dm_sq;
    

}

Disappearance::~Disappearance(){}

void Disappearance::make_Prediction(char hist_type, int which){

    for(int i = 1; i <= nbin; i++){
            
        double Eng = _input1->GetBinCenter(i);
        double bin_content1 = _input1->GetBinContent(i);
        double bin_content2 = _input2->GetBinContent(i);
        double bin_content3 = _input3->GetBinContent(i);
        double bin_content4 = _input4->GetBinContent(i);
        
        double prob,weight;
        
        if(which == 1){
            prob = series(Eng);
                        if(prob >=1){
                prob =0;
            }
            weight = prob*bin_content1 + prob*bin_content2 +prob*bin_content3 + prob*bin_content4;

            //std::cout << "weight " << weight << " Prob " << prob << " Eng " << Eng << std::endl;
            
            if(hist_type == 'd'){
                _Data->SetBinContent(i,weight);
            }
            else if(hist_type == 'p'){
                _Prediction->SetBinContent(i,weight);
            }
            else{std::cout << "Invalid Hist Type" << std::endl;}
            
        }
        
        else if(which == 2){
        
            prob = approx(Eng);
            weight = prob*bin_content1 + prob*bin_content2 + prob*bin_content3 + prob*bin_content4;
            if(hist_type == 'd'){
                _Data->SetBinContent(i,weight);
            }
            else if(hist_type == 'p'){
                _Prediction->SetBinContent(i,weight);
            }
            else{std::cout << "Invalid Hist Type" << std::endl;}
            
        }
        
        else if(which == 3){
        
            prob = osci_prob(Eng);
            weight = prob*bin_content1 + prob*bin_content2 + prob*bin_content3 + prob*bin_content4;
            if(hist_type == 'd'){
                _Data->SetBinContent(i,weight);
            }
            else if(hist_type == 'p'){
                _Prediction->SetBinContent(i,weight);
            }
            else{std::cout << "Invalid Hist Type" << std::endl;}
            
        
        }
        
        else{
            std::cout << "Incorrect series choice" << std::endl;
        }
        
    }
  
}

double Disappearance::series(double E){
    
    double tot = 0;
        
    for(int k = 1; k<=currentPars[7];k++){
            
        double series = (-1)*(pow((-1),k)*pow(2,(-1+2*k))*pow((a/E),2*k))/(fact(2*k));
        //std::cout << "a " << a << " fact " << fact(2*k) << " tot " << tot << std::endl;
        tot = tot + series;
            
    }
        
    double coef = sin(2.0*currentPars[2]);
        
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

double Disappearance::approx( double E){
    
 
  
    double sin_E = sin(a/E);
    double sin_sq = sin_E*sin_E;
    
    double coef = sin(2.0*currentPars[2]);
    double coef_sq = coef*coef;
    
    return 1-coef_sq*sin_sq;

}

double Disappearance::osci_prob( double E){


    double sin_E = sin(a/E);
    double sin_sq = sin_E*sin_E;
    
    double coef = cos(currentPars[3])*cos(currentPars[3])*sin(currentPars[2])*sin(currentPars[2]);//complete expression
    
    return 1.0-(4.0*coef*sin_sq-coef*coef*sin_sq);
    

}
