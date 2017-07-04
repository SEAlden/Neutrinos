#include "BargerPropagator.h"

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>

#include "TString.h"
#include "TFile.h"
#include "TMath.h"
#include "TH1D.h"

void boundPlot(TString filename, TString parameter,int resolution, double xmin, double xmax){

  TFile* file = new TFile(filename);
  TTree* tree = (TTree*)file->Get("t");

  TString hname = "h";
  hname+=parameter;
  TH1D* hist = new TH1D(hname,parameter,resolution,xmin,xmax); // 400 gives about the same resolution as in the TTree plot

  tree->Project(hname,parameter);
  hist->DrawCopy();

  double percentage = 0;
  int i = 1;
  int maxbin = hist->GetMaximumBin();

  while(percentage<90){

    if(maxbin-i > 0){
      percentage = 100*(hist->Integral(maxbin-i,maxbin+i))/(hist->Integral());
    }

    else{
      percentage = 100*(hist->Integral(0,maxbin+i))/(hist->Integral());
    }

    i++;

  }

    hist->SetFillColor(9);
    hist->GetXaxis()->SetRange(maxbin-i,maxbin+i);
    hist->DrawCopy("same");




  // FILL BIN WITH COLOUR
  //maxbin = GetMaximumBin() // gets the maximum weight in the histogram
  //GetXaxis()->GetBinCenter(maxbin) // gets the bin number that has the maximum bin

  std::cout << "Distribution bound." << std::endl;
}

// void boundPlot() {
//    TH1F *h = new TH1F("h","a colored plot",100,0,3);
//    h->FillRandom("gaus",10000);
//    h->DrawCopy();
//    for (Int_t i=1;i<100;i+=5) {
//       h->SetFillColor((i+4)/5);
//       h->GetXaxis()->SetRange(i,i+4);
//       h->DrawCopy("same");
//    }
// }
