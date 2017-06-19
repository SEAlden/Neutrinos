//
//  fubar.cpp
//
//
//  Created by Siobhan Alden & Andrew Yong on 12/06/2017.
//
//

#include <stdio.h>
// #include <cmath.h>

#include "Nu_Fitter.cpp"
#include "Disappearance.cpp"
#include "TRandom3.h"
#include "Markov_Chain.cpp"



int main(){
    
    Nu_Fitter Test = Nu_Fitter(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub", "enu_sk_nue", "enu_sk_nueb");
   
    Test.make_sum('d',true);// Data
    
    Test.make_sum('p',true);// Prediction

    std::cout <<"LLH = " << Test.getLLH() << std::endl;
    
    Disappearance TestA(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub","enu_sk_nue", "enu_sk_nueb", 2);
    
    TestA.make_Prediction('d', 1);
    
    TestA.make_sum('p', 1);
    //TestA.make_sum('p', true);
    
//    std::vector<double> values = TestA.return_param();
//    for (int i = 0; i<values.size(); i ++){
//        std::cout << values[i] << std::endl;
    
  //    }
    std::cout << "LLH = " << TestA.getLLH() << std::endl;
    
    std::vector<double> params = TestA.return_param();

    Markov_Chain try1 = Markov_Chain(params, 100);
 
    try1.set_varied(3);
    
    try1.startMH(params, &TestA);
   
    try1.print();
    
    //TestA.show_Prediction();

    
    //TestA.show_Prediction();
    
}
