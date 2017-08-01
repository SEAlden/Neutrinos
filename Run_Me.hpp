#ifndef Run_Me_hpp
#define Run_Me_hpp

#include <stdio.h>
#include <iostream>


#include "Nu_Fitter.hpp"
//#include "Nu_Fitter.cpp"
#include "Appearance.h"
#include "Markov_Chain.hpp"
#include "Disappearance.h"
//#include "Markov_Chain.cpp"
//#include "Disappearance.cpp"
//#include "Appearance.cpp"
#include "Plotter.hpp"
//#include "Plotter.cpp"
#include "analysis.hpp"
//#include "analysis.cpp"
//#include "Run_Me.cpp"

#include <string>
#include <vector>
#include <sstream>


class Run_Me{

public:
   Run_Me(std::string channel, std::string FD, std::string PD, std::string Theta23, int SF, std::string data_name);
  ~Run_Me();

  void mcmc(std::vector<int> set, bool disa);
  void plot();
  
private:

  // variables needed for constructor if statements
  std::string _channel;
  std::string _FD;
  std::string _PD;
  std::string _Theta23;
  int _SF;
  // variable needed for Markov_Chain object
  std::string _data_name;
  //objects needed
  Disappearance* Nu;
  Markov_Chain* MC;
  Plotter* P;
  analysis* A;
  // non constructor based variables
  std::string ext, output, mean, markov, plotter, file_out;
  std::vector<double> p_pars, t_pars, c_pars;
  std::vector<std::string> par_name;
  int kNuBar;
  
  

};





#endif /* Run_Me_hpp */
