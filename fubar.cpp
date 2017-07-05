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


int main(){

    // Andrew's Test
  int a = 5;
   Appearance plus = Appearance(1, "/home/yong/Neutrinos/Prob3++.20121225/T2Kflux2016/t2kflux_2016_plus250kA.root", "enu_sk_numu","enu_sk_numub","enu_sk_nue","enu_sk_nueb");
   Appearance minus = Appearance(1, "/home/yong/Neutrinos/Prob3++.20121225/T2Kflux2016/t2kflux_2016_minus250kA.root", "enu_sk_numu","enu_sk_numub","enu_sk_nue","enu_sk_nueb");

   plus.scale_factor(6);
  //  plus.set_param(8,0.5,'c');
  //  plus.set_param(8,1.0,'p');
  //  minus.set_param(8,0.5,'c');
  //  minus.set_param(8,1.0,'p');
  //
  //  plus.make_sum('f','a', true);// Data
  //  plus.make_sum('p','a',true);
  //  minus.make_sum('f','a', true);// Data
  //  minus.make_sum('p','a',true);
  //
  //
  // //  plus.get_integral();
  // //  plus.get_integral(0,1.25);
  // //
  // //  minus.get_integral();
  // //  minus.get_integral(0,1.25);
  //
  //  std::vector<double> params = plus.return_cparam();
  //  std::vector<std::string> sparams = plus.return_sparam();
  //
  //  Markov_Chain t1 = Markov_Chain(params, sparams, 1000000, "tdb3.root");
  //
  // t1.set_param(3);//theta13
  // t1.set_width(3,5E-3);
  // t1.set_param(6);// delta
  // t1.set_width(6,8E-2);
  // t1.set_param(8); // beta
  // t1.set_width(8,8E-2);
  //
  //
  //  t1.startMH(params,&plus,&minus);


}
