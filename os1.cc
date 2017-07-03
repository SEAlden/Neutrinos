#include <math.h>
#include <iostream>
#include <fstream>

#include "BargerPropagator.h"

#include "TFile.h"
#include "TH1D.h"

#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;
int main(int argc, char * argv[] )
{
   //set parameters
   bool kSquared  = true;   // using sin^2(x) variables?
   double DM2     =  2.4e-3;
   double Theta23 =  0.5   ;
   double Theta13 =  0.025  ;
   double dm2     =  7.6e-5;
   double Theta12 =  0.312;
   double delta   =  0 * (3.1415926/180.0); //convert to radians 
   
   std::cout << "Using          " << std::endl
	     << "      DM2      " <<  DM2      << std::endl
	     << "      Theta23  " <<  Theta23  << std::endl
	     << "      Theta13  " <<  Theta13  << std::endl
	     << "      dm2      " <<  dm2      << std::endl
	     << "      Theta12  " <<  Theta12  << std::endl
	     << "      dcp      " <<  delta    << std::endl;


   //make propagator
   BargerPropagator   * bNu; 
   
   bNu = new BargerPropagator( );
   bNu->UseMassEigenstates( false );

   double energy = 0.6; //GeV
   int kNuBar = 1.0; // positive for neutrino, negative for antineutrino
   double BasePath = 295; //km
   double Density = 2.3; //g/cm^3
   
   bNu->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, delta , energy, kSquared, kNuBar ); 
   bNu->propagateLinear( 1*kNuBar, BasePath, Density );
   //oscilate mu to mu
   double prob = bNu->GetProb(2, 2);

   std::cout << prob << std::endl;

  cout << endl<<"Done Cowboy!" << endl;
  return 0;
}

