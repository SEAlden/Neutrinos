//
//  Plotter.hpp
//  
//
//  Created by Siobhan Alden on 05/07/2017.
//
//

#ifndef Plotter_hpp
#define Plotter_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "BargerPropagator.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"



class Plotter{
    
public:
    Plotter(std::string root_file, std::string root_name, int kNuBarVar);
    
    void make_2d_taylor();
    double taylor_func(std::vector<double> &pars, double E);
    void make_2d_pmns();
    void make_mean();
    
    
    
private:
    
   // TFile* outfile2d;
    TFile* file;
    TFile* file2;
    TTree* pick;
    TH2D* hFunction;
    TTree* tree;
    std::vector<double> pars;
    BargerPropagator   * bNu;
    BargerPropagator   * bNu2;
    
    bool kSquared;   // using sin^2(x) variables?
    int kNuBar; // positive for neutrino, negative for antineutrino
    double BasePath; //km
    double Density;

};

#endif /* Plotter_hpp */
