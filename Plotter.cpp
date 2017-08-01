//A
//  Plotter.cpp
//  
//
//  Created by Siobhan Alden on 05/07/2017.
//
//

#include "Plotter.hpp"

Plotter::Plotter(std::string root_file, std::string root_name, int kNuBarVar){
    
    
    bNu = new BargerPropagator( );
    bNu->UseMassEigenstates( false );
    bNu2 = new BargerPropagator( );
    bNu2->UseMassEigenstates( false );
    
    
    kSquared  = true; // hard coded for now
    BasePath = 295; //km
    Density = 2.3;
    kNuBar = kNuBarVar;// switch between neutrino

    // open root file from disappearance/nu_fitter
    file = new TFile(root_file.c_str());
    
    // create new root file for output so that you can select specific entries from the other root file, theres probably a more efficient way to do this
    file2 = new TFile(root_name.c_str(),"RECREATE");
    
    // new treeeeeeeee to be filled with stuff from the other root file as per your choice, such as when the probability is less than 0 at energy greater than 0.3GeV (unphysical area)
    pick = new TTree("z","");
    
    
    // preserve size for vector
    pars.resize(18,0);
    
    // create 2d hist
    hFunction =  new TH2D("hf","",200,0,2,25000,-0.5,25);
    
    // get values from tree
    tree = (TTree*)file->Get("t");
   
    tree->GetEntry(0);
    
    pick->Branch("First",&pars[9], "First/D");
    pick->Branch("Second",&pars[10], "Second/D");
    pick->Branch("Third",&pars[11], "Third/D");
    pick->Branch("Fourth",&pars[12], "Fourth/D");
    pick->Branch("Fifth",&pars[13], "Fifth/D");
    pick->Branch("Sixth",&pars[14], "Sixth/D");
    pick->Branch("Seventh",&pars[15], "Seventh/D");
    pick->Branch("Eighth",&pars[16], "Eighth/D");
    pick->Branch("Ninth",&pars[17], "Ninth/D");
    pick->Fill();

 
    
    
}

void Plotter::make_2d_taylor(){

    tree->SetBranchAddress("First",&pars[9]);
    tree->SetBranchAddress("Second",&pars[10]);
    tree->SetBranchAddress("Third",&pars[11]);
    tree->SetBranchAddress("Fourth",&pars[12]);
    tree->SetBranchAddress("Fifth",&pars[13]);
    tree->SetBranchAddress("Sixth",&pars[14]);
    tree->SetBranchAddress("Seventh",&pars[15]);
    tree->SetBranchAddress("Eighth",&pars[16]);
    tree->SetBranchAddress("Ninth",&pars[17]);

    for(int i=0; i<tree->GetEntries(); i+=200)
        //   for(int i=0; i<100; i++)
    {
        printf("N: %i\n",i);
        tree->GetEntry(i);

        for(int j=1; j<=hFunction->GetNbinsX(); j++)
        {
            double E = hFunction->GetXaxis()->GetBinCenter(j);
            double prob = taylor_func(pars,E);
            if(prob<0&& E>0.4){

                //std::cout << "maybe" << std::endl;
                pick->Fill();
            }


            hFunction->Fill(E,prob);
        }

    }

    pick->Write();
    hFunction->Write();
    file2->Close();
    file->Close();

    //hFunction->Draw("colz");


}

double Plotter::taylor_func(std::vector<double> &pars, double E)
{
    double val = 0;
    //loop starts at 9 as first 9 elements of pars == pmns variables
    for(int i=0; i<=9; i++)
    {
        val+=pars[i+9]*pow(1/E,i);
    }

    return val;
}

void Plotter::make_2d_pmns(){

    tree->SetBranchAddress("Energy",&pars[0]);
    tree->SetBranchAddress("DM2",&pars[1]);
    tree->SetBranchAddress("Theta23",&pars[2]);
    tree->SetBranchAddress("Theta13",&pars[3]);
    tree->SetBranchAddress("dm2",&pars[4]);
    tree->SetBranchAddress("Theta12",&pars[5]);
    tree->SetBranchAddress("Delta",&pars[6]);
    tree->SetBranchAddress("n",&pars[7]);
    tree->SetBranchAddress("Beta",&pars[8]);



    for(int i=0; i<tree->GetEntries(); i+=200)
    {
        printf("N: %i\n",i);
        tree->GetEntry(i);

        for(int j=1; j<=hFunction->GetNbinsX(); j++)
        {
            double E = hFunction->GetXaxis()->GetBinCenter(j);
            bNu->SetMNS( pars[5],  pars[3], pars[2], pars[4], pars[1], pars[6] , E, kSquared, kNuBar );
            bNu->propagateLinear( 1*kNuBar, BasePath, Density );
            double prob = bNu->GetProb(2,2);
            hFunction->Fill(E,prob);
        }

    }

    hFunction->Write();
    file2->Close();
    file->Close();
    //hFunction->Draw("colz");


}
