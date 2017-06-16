//
//  Markov.hpp
//  
//
//  Created by Siobhan Alden & Andrew Yong on 16/06/2017.
//
//

#ifndef Markov_Chain_hpp
#define Markov_Chain_hpp

#include <stdio.h>
#include "Nu_Fitter"



class Markov_Chain{

public:
    Markov_Chain(std::vector<double>* currentPars);
    ~Markov_Chain();
    void startMH(std::vector<double>* currentPars, Nu_Fitter* oscObject);
    void set_varied(int element);
    
    
private:
    
    int steps;
    std::vector<double> proposedPars;
    std::vector<bool> varied;
    double currentLLH;
    double proposedLLH;



};


#endif /* Markov_Chain_hpp */
