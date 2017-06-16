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
    Nu_Fitter Test3 = Nu_Fitter(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub", "enu_sk_nue", "enu_sk_nueb");
    
    Test.make_sum('d',true);// Data
    
    Test.make_sum('p',true);// Prediction
    
    std::cout <<"LLH = " << Test.getLLH() << std::endl;
    
    Disappearance TestA(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub","enu_sk_nue", "enu_sk_nueb", 2);
    
    TestA.make_Prediction('d', 1);
    
    TestA.show_Prediction();
    
}
