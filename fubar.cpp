//
//  fubar.cpp
//
//
//  Created by Siobhan Alden & Andrew Yong on 12/06/2017.
//
//

#include <stdio.h>
// #include <cmath.h>

#include "Disappearance.cpp"





int main(){
    
    
    Nu_Fitter Test = Nu_Fitter(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub", "enu_sk_nue", "enu_sk_nueb");

    Test.make_Prediction(2,2);
    
    std::cout <<"LLH = " << Test.getLLH() << std::endl;
    
    Disappearance TestA(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub","enu_sk_nue", "enu_sk_nueb", 2);
    
    TestA.make_Prediction(10, 1);
    
    TestA.show_Prediction();
    
}
