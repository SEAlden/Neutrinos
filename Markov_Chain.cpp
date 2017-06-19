//
//  Markov_Chain.cpp
//  
//
//  Created by Siobhan Alden & Andrew Yong on 16/06/2017.
//
//

#include "Markov_Chain.hpp"

Markov_Chain::Markov_Chain(std::vector<double> currentPars, int nstep){

    
    steps = nstep;
    file = new TFile("mcmc.root","RECREATE");
    outputtree = new TTree("outputtree","");
    outputtree->Branch("Energy", &currentPars[0], "Energy/D");
    outputtree->Branch("DM2",&currentPars[1],"DM2/D");
    outputtree->Branch("Theta23",&currentPars[2],"Theta23/D");
    outputtree->Branch("Theta13",&currentPars[3],"Theta13/D");
    outputtree->Branch("dm2",&currentPars[4],"dm2/D");
    outputtree->Branch("Theta12",&currentPars[5],"Theta12/D");
    outputtree->Branch("Delta",&currentPars[6],"Delta/D");
    outputtree->Branch("n_series",&currentPars[7],"n_series/D");
    outputtree->Branch("Beta",&currentPars[8],"Beta/D");
    
    outputtree->Branch("LLH",&currentLLH,"LLH/D");
    
    outputtree->Fill();

    for( int i = 0; i<=8; i++){
    
        varied.push_back(false);
        proposedPars.push_back(0);
    
    }
    
    

}

Markov_Chain::~Markov_Chain(){};

void Markov_Chain::startMH(std::vector<double> currentPars, Nu_Fitter* oscObject){

    TRandom3* rnd = new TRandom3(0);

    //int count = 0;
    for(int i=0; i<steps; i++)
        
    {
      
        for(int j=0; j<currentPars.size(); j++) {
                        if(varied[j]){
                            
                proposedPars[j]=rnd->Gaus(currentPars[j],0.1);//width has to be tuned

                       }
        }
        
        proposedLLH = oscObject->getLLH();
        
        double accProb = TMath::Min(1.,TMath::Exp(currentLLH-proposedLLH));
        double fRandom = rnd->Rndm();
        
        if ( fRandom <= accProb )
        {
//            count++;
//            std::cout << count << std::endl;
            for(int k=0; k<currentPars.size(); k++)
            {
                if(varied[k]){
                currentPars[k]=proposedPars[k];
                }
            }
            currentLLH=proposedLLH;
        }
        
        outputtree->Branch("Energy",&currentPars[0],"E/D");
        outputtree->Branch("DM2",&currentPars[1],"DM2/D");
        outputtree->Branch("Theta23",&currentPars[2],"Theta23/D");
        outputtree->Branch("Theta13",&currentPars[3],"Theta13/D");
        outputtree->Branch("dm2",&currentPars[4],"dm2/D");
        outputtree->Branch("Theta12",&currentPars[5],"Theta12/D");
        outputtree->Branch("Delta",&currentPars[6],"Delta/D");
        outputtree->Branch("n_series",&currentPars[7],"n_series/D");
        outputtree->Branch("Beta",&currentPars[8],"Beta/D");
        outputtree->Branch("LLH",&currentLLH,"LLH/D");

        outputtree->Fill();
        
    }
    
    outputtree->Write();
    file->Close();

}

void Markov_Chain::set_varied(int element){

    varied[element] = true;

}

void Markov_Chain::print(){


    std::cout << "Parameters  "  << " Proposed" << std::endl
    << "Energy "   << proposedPars[0] << std::endl
    << "DM2 "      << proposedPars[1] << std::endl
    << "Theta23 "  << proposedPars[2] << std::endl
    << "Theta13 "  << proposedPars[3] << std::endl
    << "dm2 "      << proposedPars[4] << std::endl
    << "Theta12 "  << proposedPars[5] << std::endl
    << "Delta "    << proposedPars[6] << std::endl
    << "n_series " << proposedPars[7] << std::endl
    << "Beta "     << proposedPars[8] << std::endl;
    

}
