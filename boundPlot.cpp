#include <stdio.h>
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "TTree.h"
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
  TH1D* histcolour = new TH1D("hcopy",parameter,resolution,xmin,xmax);

  tree->Project(hname,parameter);
  hist->Draw();
  histcolour->SetFillColor(9);

  std::vector<double> bin_content, bin_number;

  for(int i =1; i <= resolution; i++){
    bin_content.push_back(hist->GetBinContent(i));
  }
  std::cout << "Size: " << bin_content.size() << std::endl;
  std::sort(bin_content.rbegin(),bin_content.rend()); // sort in descending order
  double total_integral=0;

  for(int j = 0; j < bin_content.size(); j++){
    total_integral += bin_content[j];
  }
  std::cout << "Total integral: " << total_integral << std::endl;
  //
  double percentage = 0;
  int j = 1;
  double integral = bin_content[0]; // first element


  while(percentage<90){
    integral += bin_content[j];
    percentage = 100*integral/total_integral;
    j++;
  }

  std::cout << "\%:" << percentage << "\tj: " << j <<  std::endl;
  double weight;
  for(int k =0; k < j; k++){ // k represents elements in bin content vector
    for(int l = 0; l < resolution; l++){ // l represents bin number
      weight = hist->GetBinContent(l);

      if(weight == bin_content[k]){
        bin_number.push_back(l);
        histcolour->SetBinContent(l,weight);
      }

    }
  }

  histcolour->DrawCopy("same");


  //   hist->GetXaxis()->SetRange(maxbin-i,maxbin+i);
  //   hist->DrawCopy("same");
  //
  //
  //
  //
  // // FILL BIN WITH COLOUR
  // //maxbin = GetMaximumBin() // gets the maximum weight in the histogram
  // //GetXaxis()->GetBinCenter(maxbin) // gets the bin number that has the maximum bin
  //
  // std::cout << "Distribution bound." << std::endl;
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
