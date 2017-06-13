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
#include "Nu_Fitter.cpp"
#include <iostream>

class Disappearance : public Nu_Fitter {
    
public:
    
    Disappearance(int kNuBarVar, std::string path, std::string filename, std::string filename2, int mass);
    ~Disappearance();
    void make_Prediction(int n, int which, int heirachy);
    double series(int n, double E, int heirachy);
    double fact(int n);
    double approx(double E, int heirachy);
    //void mass(int heirachy);
    double osci_prob(double E, int heirachy);
    
private:
    
    double L = 295;
    double dm_sq;
    double a;
    
    
};

#endif /* Disappearance_hpp */
