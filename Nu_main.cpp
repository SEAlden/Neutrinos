//
//  fubar.cpp
//
//
//  Created by Siobhan Alden & Andrew Yong on 12/06/2017.
//
//

#include <stdio.h>
#include <iostream>

/*
#include "Nu_Fitter.hpp"
#include "Nu_Fitter.cpp"
#include "Appearance.h"
#include "Markov_Chain.hpp"
#include "Disappearance.hpp"
#include "Markov_Chain.cpp"
#include "Disappearance.cpp"
#include "Appearance.cpp"
#include "Plotter.hpp"
#include "Plotter.cpp"
#include "analysis.hpp"
#include "analysis.cpp"
*/
#include "Run_Me.hpp"
//#include "Run_Me.cpp"

#include <string>
#include <vector>
#include <sstream>


int main(){

  Nu_Fitter testing = Nu_Fitter(1,"t2kflux_2016_plus250kA.root", "enu_sk_numu", "enu_sk_numub","enu_sk_nue", "enu_sk_nueb");

  testing.make_sum('m','d', false);

  testing.show_hist('f');

  /*
  std::string minus = "m_";
  std::string SF = "10";
  int scale = 10;
  
  ////// PP plus  //////////////

  std::string PP = "PP";
  
  Run_Me p_PP1 = Run_Me("p", "p", "p", "0.5", scale , PP+SF);

  std::cout << PP+SF << std::endl;

  std::vector<int> PP_var;

  PP_var.push_back(2);
  
  p_PP1.mcmc(PP_var, false);

  p_PP1.plot();

  /////////// PT_5 plus ///////////////////////

  std::string PT = "5_PT";
  Run_Me p_PT1 = Run_Me("p", "p", "t", "0.5", scale , PT+SF);
  
  std::vector<int> PT_var;

  for( int i = 9; i <=17 ; i++){
    PT_var.push_back(i);
  }
  
  p_PT1.mcmc(PT_var, true);

  p_PT1.plot();

 //////////// PT_45 plus //////////////////// 
 
  std::string PT45 = "45_PT";
  
  Run_Me p_PT1_45 = Run_Me("p", "p", "t", "0.45", scale , PT45+SF);
  
  p_PT1_45.mcmc(PT_var, true);

  p_PT1_45.plot();


  //////////////// TT plus /////////////

  std::string TT = "TT";
  
  Run_Me p_TT1 = Run_Me("p","t","t","0.5",scale,TT+SF);

  p_TT1.mcmc(PT_var, true);

  p_TT1.plot();
  
  
  ////////// TP plus //////////////////

  std::string TP = "TP";
  
  Run_Me p_TP1 = Run_Me("p","t","p","0.5",scale,TP+SF);

  p_TP1.mcmc(PP_var, false);

  p_TP1.plot();


  
  ////// PP minus  //////////////
  
  Run_Me m_PP1 = Run_Me("m", "p", "p", "0.5", scale , minus+PP+SF);
  
  m_PP1.mcmc(PP_var, false);

  m_PP1.plot();

  /////////// PT_5 plus ///////////////////////

  Run_Me m_PT1 = Run_Me("m", "p", "t", "0.5", scale , minus+PT+SF);

  m_PT1.mcmc(PT_var, true);

  m_PT1.plot();
  
  //////////// PT_45 plus /////////////////////

  Run_Me m_PT1_45 = Run_Me("m", "p", "t", "0.45",scale , minus+PT45+SF);
  
  m_PT1_45.mcmc(PT_var, true);

  m_PT1_45.plot();

  
  //////////////// TT plus /////////////
  
  Run_Me m_TT1 = Run_Me("m","t","t","0.5",scale,minus+TT+SF);

  m_TT1.mcmc(PT_var, true);

  m_TT1.plot();
  
  
  ////////// TP plus //////////////////

  
  Run_Me m_TP1 = Run_Me("m","t","p","0.5",scale,minus+TP+SF);

  m_TP1.mcmc(PP_var, false);

  m_TP1.plot();
  
  */
}
