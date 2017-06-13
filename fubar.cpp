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
    
    
    Nu_Fitter Test = Nu_Fitter(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu");

    Test.make_Prediction();
    
    std::cout <<"LLH = " << Test.getLLH() << std::endl;
    
    
    
}
