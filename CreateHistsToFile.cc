//CreateHistsToFile.C
//M.L. Miller (MIT)
//1/07

/*
 
 This is sample macro 1 of our lightning review of root.  
 This macro performs the following:
 
 1) Open an output TFile
 2) Create histograms, fill them, and save to a file
 3) Write file and close
 
 All root classes are documented online at:
 http://root.cern.ch/root/html/ClassIndex.html
 
 example usage 1 (run as a root macro):
 root -l CreateHistsToFile.C'("firstHistograms.root")'
 
 example usage 2 (w/o graphics -b, quit on finish -q):
 root -b -q CreateHistsToFile.C'("firstHistograms.root")'
 
 example usage 3 (compiled "on the fly and w/o graphics"): 
 root -b -q CreateHistsToFile.C+'("firstHistograms.root")'
 
 */


//NOTE: you only have to include header files for a macro (.C file) if you plan to compile it.

//ansi-std c++ includes
#include <iostream>
#include <string>
using namespace std;

//ROOT includes
#include "TROOT.h"
#include "TStyle.h"
#include "TString.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TF1.h"
#include "TF2.h"
#include "TMath.h"

int main()
{
        const char* ofname = "firstHistograms.root";
	int nSample = 10000;
	cout <<"--------- Executing:\t CreateHistsToFile\t ------------"<<endl;
	
	//first create the TFile object.  A general rule of thumb is to open the 
	//file first, then create histograms and nutple
	cout <<"open file:\t"<<ofname<<"\tfor writing"<<endl;
	TFile* outfile = new TFile(ofname,"RECREATE");
	
	//And we'll manipulate the filename for an output .eps picture
	TString psname(ofname);
	psname.ReplaceAll("root","eps");
	cout <<"write picture file:\t"<<psname.Data()<<endl;
	cout << psname << endl;
	
	//Now let's create some 1d and 2d histograms:
	TH1* sinHist = new TH1D("sinHist","Histogram of sin function; x [au]; Counts", 40, 0., 2.*TMath::Pi());
	
	//Now we'll create a TF1 object from which to randomly sample:
	TF1* sinFunc = new TF1("sinFunc","sin(x) + 2.", 0., 2.*TMath::Pi());
	
	//now we'll randomly sample the TF1 'n' times
	for (int i=0; i<nSample; ++i) {
		
		//This is a very convenient way to randomly sample a distribution
		//The same method also exists to randomly sample an arbitrary distriubtion
		//saved in a TH1, see TH1::GetRandom()
		double x = sinFunc->GetRandom();
		
		//Now we fill the histogram with a count
		sinHist->Fill(x);
	}
	
	//Some style options for drawing
	gStyle->SetPadColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetPalette(1,0);
	
	
	//Now that we're done filling, we'll create a canvas and draw the results
	TCanvas* c = new TCanvas("c","First Canvas",100,100, 600, 600);
	
	//Divide the canvas into 4 zones
	c->Divide(2,2);
	
	//switch to the first zone.
	//they're numbered top to bottom, left to right
	c->cd(1);
	sinFunc->SetLineColor(2);
	sinFunc->SetLineWidth(2);
	sinFunc->DrawCopy();
	
	//And plot our 1d histogram
	c->cd(2);
	sinHist->SetMarkerStyle(20);
	sinHist->SetMarkerSize(0.3);
	sinHist->SetMarkerColor(2);
	sinHist->SetLineColor(2);
	sinHist->DrawCopy("pe");
	
	//And here we save the canvas as an eps file
	c->SaveAs(psname.Data());
	
	//Now we close the outfile
	outfile->Write();
	outfile->Close();
	

}
