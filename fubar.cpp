//
//  fubar.cpp
//
//
//  Created by Siobhan Alden & Andrew Yong on 12/06/2017.
//
//

#include <stdio.h>
#include <iostream>


#include "Nu_Fitter.hpp"
 #include "Nu_Fitter.cpp"
//#include "Appearance.h"
#include "Markov_Chain.hpp"
#include "Markov_Chain.cpp"
#include "Disappearance.cpp"
// #include "Appearance.cpp"

int main(){
    
    //Siobhan's Test
//    Nu_Fitter Test = Nu_Fitter(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub", "enu_sk_nue", "enu_sk_nueb");
//    // Andrew's Test
//    // Nu_Fitter Test = Nu_Fitter(1, "/home/yong/Neutrinos/Prob3++.20121225/T2Kflux2016/t2kflux_2016_minus250kA.root", "enu_sk_numu","enu_sk_numub","enu_sk_nue","enu_sk_nueb");
//    
//    Test.make_sum('d',true, true);// Data
//    
//    Test.make_sum('p',true, true);// Prediction
//    
//    std::cout << "LLH = " << Test.getLLH() << std::endl;
//    
//    std::vector<double> params = Test.return_param();
//
//    
//    Markov_Chain five = Markov_Chain(params, 10000, "osci_1_branch.root");
//    
//    five.set_pars(1);// theta23
//    five.set_pars(2);//dm23
//    
//    five.startMH(params, &Test);
////
//
    Disappearance TestA(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub","enu_sk_nue", "enu_sk_nueb", 2);
    
    TestA.make_Prediction('p', 1);
    
    TestA.make_sum('d', 1, true);
    
    std::cout << TestA.getLLH() << std::endl;
    
    std::vector<double> paramsA = TestA.return_param();
    
    Markov_Chain five_2 = Markov_Chain(paramsA, 10000, "expan_branch.root");
    
    five_2.set_pars(1);// theta23
    five_2.set_pars(2);//dm23
    
    five_2.startMH(paramsA, &TestA, true);
//
//
    
    
//    Disappearance TestB(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub","enu_sk_nue", "enu_sk_nueb", 2);
//    
//    TestB.make_Prediction('d', 1);
//    
//    TestB.make_sum('p', 1);
//    
//    std::cout << TestB.getLLH() << std::endl;
//    
//    std::vector<double> paramsB = TestB.return_param();
//    
//    Markov_Chain five_3 = Markov_Chain(paramsB, 10000, "approx_branch.root");
//    
//    five_3.set_pars(1);// theta23
//    five_3.set_pars(2);//dm23
//    
//    five_3.startMH(paramsA, &TestA , 0.01);
    


    

    
   //    std::cout << "LLH = " << Test.getLLH() << std::endl;
//    
//    std::vector<double> params = Test.return_param();
//    
//    Markov_Chain try1 = Markov_Chain(params, 100, "test.root");
//    
//    try1.set_pars(3);
//    
//    try1.startMH(params, &Test,0.01);
//    
//    try1.print();
    
    // LLH = 1.67389e+06
    
    
}
