#include "analysis.hpp"

analysis::analysis(std::string input_file, std::string output_file){


    file = new TFile(input_file.c_str());
    hfunc = (TH2D*)file->Get("hf");

    file2 = new TFile(output_file.c_str(), "RECREATE");
    points = new TTree("pts", "" );
    
    project = new TH1D("p", "", 200, 0, 2);

    points->Branch("Mean",& mean, "Mean/D");
    points->Branch("rms", &rms, "rms/D");
    points->Branch("energy", &energy, "energy/D");

    points->Fill();
}

void analysis::make_mean(){

  for (int i = 1; i <=hfunc->GetNbinsX(); i++){

      project = hfunc->ProjectionY("", i,i);
      energy = hfunc->GetXaxis()->GetBinCenter(i);
      mean = project->GetMean();
      rms = project->GetRMS();
      printf("%f %f %f\n", energy, mean, rms);
      points->Fill();

    }


   points->Write();
   file->Close();
   file2->Close();
       
	 
}
