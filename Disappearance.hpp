//
//  Disappearance.hpp
//  
//
//  Created by Siobhan Alden on 13/06/2017.
//
//

#ifndef Disappearance_hpp
#define Disappearance_hpp

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
    
private:
    
    double L = 295;
    double dm_sq;
    double a;
    
    
};

#endif /* Disappearance_hpp */
