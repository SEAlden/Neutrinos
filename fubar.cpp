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
// #include "Nu_Fitter.cpp"
#include "Appearance.h"
#include "Markov_Chain.hpp"
#include "Markov_Chain.cpp"
// #include "Appearance.cpp"

int main(){

    //Siobhan's Test
    Nu_Fitter Test = Nu_Fitter(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub", "enu_sk_nue", "enu_sk_nueb");
    // Andrew's Test
    // Nu_Fitter Test = Nu_Fitter(1, "/home/yong/Neutrinos/Prob3++.20121225/T2Kflux2016/t2kflux_2016_minus250kA.root", "enu_sk_numu","enu_sk_numub","enu_sk_nue","enu_sk_nueb");

    Test.make_sum('d',true);// Data

    Test.make_sum('p',true);// Prediction

    std::cout <<"LLH = " << Test.getLLH() << std::endl;

    // Disappearance TestA(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub","enu_sk_nue", "enu_sk_nueb", 2);

    // TestA.make_Prediction('d', 1);

    // TestA.make_sum('p', 1);
    //TestA.make_sum('p', true);

//    std::vector<double> values = TestA.return_param();
//    for (int i = 0; i<values.size(); i ++){
//        std::cout << values[i] << std::endl;

  //    }
    std::cout << "LLH = " << Test.getLLH() << std::endl;

    std::vector<double> params = Test.return_param();

    Markov_Chain try1 = Markov_Chain(params, 100);

    try1.set_pars(3);

    try1.startMH(params, &Test,0.01);

    try1.print();

    // LLH = 1.67389e+06


}
