#ifndef analysis_hpp
#define analysis_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

class analysis{

public:
  analysis(std::string input_file,std::string output_file);
  void make_mean();

private:
  TFile* file;
  TFile* file2;
  TTree* points;
  TH2D* hfunc;
  TH1D* project;
  double mean, rms, energy;
  

};

#endif /* analysis_hpp */
