#include <math.h>
#include <iostream>
#include <fstream>

#include "BargerPropagator.h"

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TApplication.h"
#include "TPave.h"

#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

// void plotEllipse(double energy, double beta)
int main(int argc, char * argv[] )
{

  //allows Canvas to open in
  TApplication *app = new TApplication("app",0,0);

   //set parameters
   bool kSquared  = true;   // using sin^2(x) variables?
   double DM2     =  2.4e-3; // delta m squared for mu <->tau
   double Theta23 =  0.5   ;
   double Theta13 =  0.025  ;
   double dm2     =  7.6e-5; // delta m squared for e <-> mu
   double Theta12 =  0.312;
   double delta   =  0 * (3.1415926/180.0); //convert to radians

   std::cout << "Using          " << std::endl
	     << "      DM2      " <<  DM2      << std::endl //delta mass squared
	     << "      Theta23  " <<  Theta23  << std::endl
	     << "      Theta13  " <<  Theta13  << std::endl
	     << "      dm2      " <<  dm2      << std::endl //delta mass squared
	     << "      Theta12  " <<  Theta12  << std::endl
	     << "      dcp      " <<  delta    << std::endl; // delta for CP violation


   //make propagator
   BargerPropagator   * bNu;

   bNu = new BargerPropagator( );
   bNu->UseMassEigenstates( false );

   double energy = 0.6; //GeV
   int kNuBar = 1.0; // positive for neutrino, negative for antineutrino
   double BasePath = 295; //km
   double Density = 2.3; //g/cm^3

   //introduce pre-factor beta:
   double beta=0.5; // where 0<beta<2

   //Initialise containers for neutrino probability and antineutrino probability
   double step = 0.01;
   int size = (2*M_PI/step) +1;
   Double_t p[size], pbar[size];
   int counter=0;

   for(delta = 0; delta < 2*M_PI; delta += step){ // iterate through different values of delta cp

     double prob;
     //neutrino probability:
     bNu->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, delta , energy, kSquared, kNuBar ); //creates the MNS matrix given a particular set of parameters (eg values of mixing angle, CPviolating phase factor etc)
     bNu->propagateLinear( 1*kNuBar, BasePath, Density );
     //oscilate mu to electron (or the anti version)
     prob = bNu->GetProb(2, 1);// 1 for electron, 2 for mu, 3 for tau // gets the MNS matrix element for a particular flavour oscillation given parameters set by setMNS
     p[counter] = (1./beta)*prob;

     //antineutrino probability:
     bNu->SetMNS( Theta12,  Theta13, Theta23, dm2, DM2, delta , energy, kSquared, -1*kNuBar ); //creates the MNS matrix given a particular set of parameters (eg values of mixing angle, CPviolating phase factor etc)
     bNu->propagateLinear(-1*kNuBar, BasePath, Density );
     prob = bNu->GetProb(-2,-1);
     pbar[counter] = beta*prob;

     counter++;

   }


  //  std::cout << "Probability: " <<  prob << std::endl;


  //PLOTTING
   TCanvas *c1 = new TCanvas("c1","Canvas for P-PBar ",200,10,700,500);

   TGraph* gr = new TGraph(size,p,pbar); // TGraph only takes in pointers/array
   gr->SetTitle("P vs #bar{P} at E = 0.6GeV, #beta = 0.5;P(#mu^{-} #rightarrow e^{-});#bar{P}(#mu^{+} #rightarrow e^{+})");
   gr->Draw();
   c1->Update();

   cout << "Application running..." << endl;
   app->SetReturnFromRun(true);
   app->Run(); // need this to give options for saving and zoom etc
   app->Terminate();

  // TPave *pv = new TPave(0.7,0.9,0.9,0.7); // make it top right corner
  // pv->("Oscillation Parameters");
  // pv->AddEntry("gr","#delta m^{2}: ", "");
  // pv->AddEntry("gr","#delta m^{2}: ", "");
  // pv->Draw();

  // bool end;
  // cout << "End? 1/0";
  // cin>> end;
  // app->Connect("TCanvas", "Closed()", "TApplication", app, "Terminate()");

  cout << endl<<"Done Cowboy!" << endl;

  return 0;
}

// int main(int argc, char * argv[] ){
//
//   //allows Canvas to open in
//   TApplication *app = new TApplication("app",0,0);
//
//   plotEllipse(0.6,1);
//   plotEllipse(0.1,1);
//
//   cout << "Application running..." << endl;
//   app->SetReturnFromRun(true);
//   app->Run(); // need this to give options for saving and zoom etc
//   app->Terminate();
// }
