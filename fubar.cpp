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
#include "Appearance.h"
#include "Markov_Chain.hpp"
#include "Disappearance.hpp"

//    //Siobhan's Test
//      Nu_Fitter Test = Nu_Fitter(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub", "enu_sk_nue", "enu_sk_nueb");
//
//     Test.make_sum('d','c', true);
//
//    Test.make_sum('p', 'c', true);
//
//
//     Test.show_Prediction();
//
////


//
//
//      std::cout << "LLH = " << Test1.getLLH(&Test2) << std::endl;
//
//      std::vector<double> params = Test1.return_cparam();
//     // //
//     // //
//     // // //  Markov_Chain five = Markov_Chain(params, 10000, "osci_1_branch.root");
//     Markov_Chain five = Markov_Chain(params, 10000, "test12.root");
//     // //
//     // // five.set_pars(1);// dm2
//     five.set_pars(2);//theta23
//     five.set_width(2,10e-6);
//     five.set_pars(6);// delta
//     five.set_width(6,10e-5);
//     five.set_pars(8); // beta
//     five.set_width(8,10e-6);
//
//     five.startMH(params, &Test1);

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////


    // Appearance TestB = Appearance(1, "/home/yong/Neutrinos/Prob3++.20121225/T2Kflux2016/t2kflux_2016_minus250kA.root", "enu_sk_numu","enu_sk_numub","enu_sk_nue","enu_sk_nueb");
    //
////    //
        //  Disappearance TestA = Disappearance(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub","enu_sk_nue", "enu_sk_nueb", 2);
        //
        //  TestA.taylor('p');
        //
        //  TestA.make_sum('d', 'c', true);
        //
        //  std::cout << TestA.getLLH() << std::endl;
        //
        //  //TestA.show_Prediction();
        //
        //  std::vector<double> paramsA = TestA.return_cparam();
        // //  std::vector<double> co = TestA.return_coef_pars();
        // std::vector<std::string> str = TestA.return_sparam();
        //
        //  Markov_Chain five_2 = Markov_Chain(paramsA, str, 10000, "wtf_branch.root");

int main(int argc, char** argv){

    // Andrew's Test
  
<<<<<<< HEAD
   Appearance plus = Appearance(1, "/home/yong/Neutrinos/Prob3++.20121225/T2Kflux2016/t2kflux_2016_plus250kA.root", "enu_sk_numu","enu_sk_numub","enu_sk_nue","enu_sk_nueb");
   Appearance minus = Appearance(1, "/home/yong/Neutrinos/Prob3++.20121225/T2Kflux2016/t2kflux_2016_minus250kA.root", "enu_sk_numu","enu_sk_numub","enu_sk_nue","enu_sk_nueb");
=======
  char phenom_mode;
  int scale;
  bool vary_beta=false;
  std::string filename;

  std::cout << "Please enter a response/value for the following variable:" << std::endl;
  std::cout << "Appearance or Disappearance? (a/d)";
  std::cin >> phenom_mode;
  std::cout << "Please enter a scale factor. (Enter 1 if scaling is not required)";
  std::cin >> scale;

   Appearance plus = Appearance(1, "t2kflux_2016_plus250kA.root", "enu_sk_numu","enu_sk_numub","enu_sk_nue","enu_sk_nueb");
   Appearance minus = Appearance(1, "t2kflux_2016_minus250kA.root", "enu_sk_numu","enu_sk_numub","enu_sk_nue","enu_sk_nueb");
>>>>>>> ayong

   plus.scale_factor(6);
   plus.set_param(8,0.5,'c');
   plus.set_param(8,1.0,'p');
   minus.set_param(8,0.5,'c');
   minus.set_param(8,1.0,'p');
 
   plus.make_sum('f','a', true);// Data
   plus.make_sum('p','a',true);
   minus.make_sum('f','a', true);// Data
   minus.make_sum('p','a',true);
 
 
  // //  plus.get_integral();
  // //  plus.get_integral(0,1.25);
  // //
  // //  minus.get_integral();
  // //  minus.get_integral(0,1.25);
  //
  std::vector<double> params = plus.return_cparam();
  std::vector<std::string> sparams = plus.return_sparam();
  //
  Markov_Chain t1 = Markov_Chain(params, sparams, 1000000, filename.c_str());
  //
  t1.set_param(3);//theta13
  t1.set_width(3,5E-3);
  t1.set_param(6);// delta
  t1.set_width(6,8E-2);
  t1.set_param(8); // beta
  t1.set_width(8,8E-2);
  
  
   t1.startMH(params,&plus,&minus);


}
