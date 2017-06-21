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
// #include "Markov_Chain.cpp"
// #include "Disappearance.cpp"
// #include "Appearance.cpp"

int main(){

    //Siobhan's Test
  //  Nu_Fitter Test = Nu_Fitter(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub", "enu_sk_nue", "enu_sk_nueb");


  //  std::cout << "LLH = " << Test1.getLLH(&Test2) << std::endl;
  //
  //  std::vector<double> params = Test1.return_cparam();
  // // //
  // // //
  // // // //  Markov_Chain five = Markov_Chain(params, 10000, "osci_1_branch.root");
  // Markov_Chain five = Markov_Chain(params, 10000, "test12.root");
  // // //
  // // // five.set_pars(1);// dm2
  // five.set_pars(2);//theta23
  // five.set_width(2,10e-6);
  // five.set_pars(6);// delta
  // five.set_width(6,10e-5);
  // five.set_pars(8); // beta
  // five.set_width(8,10e-6);
  //
  // five.startMH(params, &Test1);

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


  // Appearance TestB = Appearance(1, "/home/yong/Neutrinos/Prob3++.20121225/T2Kflux2016/t2kflux_2016_minus250kA.root", "enu_sk_numu","enu_sk_numub","enu_sk_nue","enu_sk_nueb");
//
//
//     Disappearance TestA(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub","enu_sk_nue", "enu_sk_nueb", 2);
//
//     TestA.make_Prediction('p', 1);
//
//     TestA.make_sum('d', 1, true);
//
//     std::cout << TestA.getLLH() << std::endl;
//
//     std::vector<double> paramsA = TestA.return_param();
//
//     Markov_Chain five_2 = Markov_Chain(paramsA, 10000, "expan_branch.root");
//
//     five_2.set_pars(1);// theta23
//     five_2.set_pars(2);//dm23
//
//     five_2.startMH(paramsA, &TestA, true);
// //
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

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Andrew's Test
//  Nu_Fitter Test1 = Nu_Fitter(1, "/home/yong/Neutrinos/Prob3++.20121225/T2Kflux2016/t2kflux_2016_minus250kA.root", "enu_sk_numu","enu_sk_numub","enu_sk_nue","enu_sk_nueb");
//  Nu_Fitter Test2 = Nu_Fitter(1, "/home/yong/Neutrinos/Prob3++.20121225/T2Kflux2016/t2kflux_2016_plus250kA.root", "enu_sk_numu","enu_sk_numub","enu_sk_nue","enu_sk_nueb");
Appearance data = Appearance(1, "/home/yong/Neutrinos/Prob3++.20121225/T2Kflux2016/t2kflux_2016_plus250kA.root", "enu_sk_numu","enu_sk_numub","enu_sk_nue","enu_sk_nueb");
Appearance fit = Appearance(1, "/home/yong/Neutrinos/Prob3++.20121225/T2Kflux2016/t2kflux_2016_minus250kA.root", "enu_sk_numu","enu_sk_numub","enu_sk_nue","enu_sk_nueb");
//
//  Test1.set_paras(8,0.5,'c'); // change currentPars index 8
//  Test1.set_paras(8,1,'p'); // change proposedPars index 8

// let Test2 be the one to fit Test1

data.make_sum('d','c', true);// Data

// Test2.make_sum('d','c', true);//
fit.make_sum('p','c', true);// Prediction

std::cout << "LLH = " << fit.getLLH(&data) << std::endl;

std::vector<double> params = fit.return_cparam();

for(int i = 0; i < params.size(); i++){
  std::cout << "i: " << i << "\tparam: " << params[i] << std::endl;
}

// // //  Markov_Chain five = Markov_Chain(params, 10000, "osci_1_branch.root");
Markov_Chain five = Markov_Chain(params, 10000, "test12.root");
// //
// // five.set_pars(1);// dm2
five.set_pars(2);//theta23
// five.set_width(2,10e-6);
five.set_pars(6);// delta
// five.set_width(6,10e-6);
five.set_pars(8); // beta
// five.set_width(8,10e-8);

five.startMH(params, &data, &fit);

return 0;


}
