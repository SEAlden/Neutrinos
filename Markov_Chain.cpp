//
//  Markov_Chain.cpp
//
//
//  Created by Siobhan Alden & Andrew Yong on 16/06/2017.
//
//

#include "Markov_Chain.hpp"

Markov_Chain::Markov_Chain(std::vector<double> currentPars, int nstep, std::string filename){



    steps = nstep;
    file = new TFile(filename.c_str(),"RECREATE");
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

        pars.push_back(false);
        proposedPars.push_back(0); // populates the proposedPars vector

    }

    double width_factor = 10000; // default width factor

    rnd  = new TRandom3(0);

    //initialising width vector; can be fine-tuned with set_width
    width.push_back(0); // energy : 0
    width.push_back(2.4e-3/width_factor);//DM2 : 1
    width.push_back(0.5/width_factor); //theta23 : 2
    width.push_back(0.025/width_factor); //theta13 : 3
    width.push_back(7.6e-3/width_factor); //dm2 : 4
    width.push_back(0.312/width_factor); //theta12 : 5
    width.push_back(width_factor); // deltacp : 6
    width.push_back(10); // n : 7
    width.push_back(1/width_factor); // beta : 8




}

Markov_Chain::~Markov_Chain(){};

void Markov_Chain::startMH(std::vector<double> currentPars, Nu_Fitter* oscObject){



    currentLLH = oscObject->getLLH();

    for(int i=0; i<steps; i++){

        if(i%1000==0 || i==0){

          if(i==0){
            std::cout << "Initialising random walk..." << std::endl;
          }

          else{
            std::cout << "Running random walk..." << std::endl;
          }

        }

        for(int j=0; j<currentPars.size(); j++) {

            if(pars[j]){

                proposedPars[j]=rnd->Gaus(currentPars[j],width[j]);
                oscObject->set_paras(j, proposedPars[j],'p');

            }
            oscObject->make_sum('p','p',true);

        }
        proposedLLH = oscObject->getLLH();

        double accProb = TMath::Min(1.,TMath::Exp(currentLLH-proposedLLH));
        double fRandom = rnd->Rndm();
        //std::cout << "i " << i << " accprob " << accProb << " fRandom " << fRandom << " current LLH " << currentLLH << " proposed LLH " << proposedLLH <<  " parameter 1 current: " << currentPars[1] << " parameter 1 proposed:" << proposedPars[1] << std::endl;

        if ( fRandom <= accProb )
        {
            for(int k=0; k<currentPars.size(); k++)
            {
                if(pars[k]){
                    currentPars[k]=proposedPars[k];
                    //std::cout << "i " << i << " proposed " << proposedPars[k] <<std::endl;
                }

            }
            currentLLH=proposedLLH;

        }
        //std::cout << "i " << i << " Theta23 " << proposedPars[2] <<std::endl;

//        outputtree->Branch("Energy",&currentPars[0],"E/D");
//        outputtree->Branch("DM2",&currentPars[1],"DM2/D");
//        outputtree->Branch("Theta23",&currentPars[2],"Theta23/D");
//        outputtree->Branch("Theta13",&currentPars[3],"Theta13/D");
//        outputtree->Branch("dm2",&currentPars[4],"dm2/D");
//        outputtree->Branch("Theta12",&currentPars[5],"Theta12/D");
//        outputtree->Branch("Delta",&currentPars[6],"Delta/D");
//        outputtree->Branch("n_series",&currentPars[7],"n_series/D");
//        outputtree->Branch("Beta",&currentPars[8],"Beta/D");
//        outputtree->Branch("LLH",&currentLLH,"LLH/D");
        outputtree->Fill();

        if(i==steps-1){
          std::cout << "Metropolis-Hastings algorithm completed." << std::endl;
        }

    }

    outputtree->Write();
    file->Close();


}

void Markov_Chain::startMH(std::vector<double> currentPars, Disappearance* oscObject, bool object){



    currentLLH = oscObject->getLLH();

    for(int i=0; i<steps; i++){

      if(i==0){
        std::cout << "Initialising random walk..." << std::endl;
      }

      else{
        std::cout << "Running random walk..." << std::endl;
      }

        for(int j=0; j<currentPars.size(); j++) {

            if(pars[j]){

                proposedPars[j]=rnd->Gaus(currentPars[j],width[j]);//width has to be tuned
                //std::cout << " width " << width[j] << std::endl;
                oscObject->set_paras(j, proposedPars[j],'p');

            }
            oscObject->make_Prediction('p', 1);

        }
        proposedLLH = oscObject->getLLH();

        double accProb = TMath::Min(1.,TMath::Exp(currentLLH-proposedLLH));
        double fRandom = rnd->Rndm();
        //std::cout << "i " << i << " accprob " << accProb << " fRandom " << fRandom << " current LLH " << currentLLH << " proposed LLH " << proposedLLH <<  " parameter 1 current: " << currentPars[1] << " parameter 1 proposed:" << proposedPars[1] << std::endl;

        if ( fRandom <= accProb )
        {
            for(int k=0; k<currentPars.size(); k++)
            {
                if(pars[k]){
                    currentPars[k]=proposedPars[k];
                    //std::cout << "i " << i << " proposed " << proposedPars[k] <<std::endl;
                }

            }
            currentLLH=proposedLLH;

        }
        //std::cout << "i " << i << " Theta23 " << proposedPars[2] <<std::endl;

        //        outputtree->Branch("Energy",&currentPars[0],"E/D");
        //        outputtree->Branch("DM2",&currentPars[1],"DM2/D");
        //        outputtree->Branch("Theta23",&currentPars[2],"Theta23/D");
        //        outputtree->Branch("Theta13",&currentPars[3],"Theta13/D");
        //        outputtree->Branch("dm2",&currentPars[4],"dm2/D");
        //        outputtree->Branch("Theta12",&currentPars[5],"Theta12/D");
        //        outputtree->Branch("Delta",&currentPars[6],"Delta/D");
        //        outputtree->Branch("n_series",&currentPars[7],"n_series/D");
        //        outputtree->Branch("Beta",&currentPars[8],"Beta/D");
        //        outputtree->Branch("LLH",&currentLLH,"LLH/D");
        outputtree->Fill();

        if(i==steps-1){
          std::cout << "Metropolis-Hastings algorithm completed." << std::endl;
        }

    }

    outputtree->Write();
    file->Close();

}

void Markov_Chain::startMH(std::vector<double> fitPars, Appearance *dataObj, Appearance *fitObj){



    currentLLH = fitObj->getLLH(dataObj);

    for(int i=0; i<steps; i++){

        if(i%1000==0 || i==0){

          if(i==0){
            std::cout << "Initialising random walk..." << std::endl;
          }

          else{
            std::cout << "Running random walk..." << std::endl;
          }

        }

        for(int j=0; j<fitPars.size(); j++) {

            if(pars[j]){

                proposedPars[j]=rnd->Gaus(fitPars[j],width[j]);
                fitObj->set_paras(j, proposedPars[j],'p');

            }
            fitObj->make_sum('p','p',true);

        }

        proposedLLH = fitObj->getLLH(dataObj);
        //  std::cout << "Proposed: " << proposedLLH << "\tCurrent: " << currentLLH << std::endl;

        double accProb = TMath::Min(1.,TMath::Exp(currentLLH-proposedLLH));
        double fRandom = rnd->Rndm();
        // std::cout << "i " << i << " accprob " << accProb << " fRandom " << fRandom << " current LLH " << currentLLH << " proposed LLH " << proposedLLH <<  " parameter 8 current: " << fitPars[8] << " parameter 8 proposed:" << proposedPars[8] << std::endl;
        // std::cout << "i " << i  << "\tparameter 6 current: " << fitPars[6] << "\tparameter 6 proposed:" << proposedPars[6] << std::endl;

        if ( fRandom <= accProb )
        {
            for(int k=0; k<fitPars.size(); k++)
            {
                if(pars[k]){
                    fitPars[k]=proposedPars[k];
                    //std::cout << "i " << i << " proposed " << proposedPars[k] <<std::endl;
                }

            }
            currentLLH=proposedLLH;

        }

        outputtree->Fill();

        if(i==steps-1){
          std::cout << "Metropolis-Hastings algorithm completed." << std::endl;
        }

    }

    outputtree->Write();
    file->Close();


}


void Markov_Chain::set_pars(int index){

    pars[index] = true;

}

void Markov_Chain::set_width(int index, double value){

    width[index] = value;

}

void Markov_Chain::print(){

    std::cout << "Proposed parameters: " << std::endl
    << "Energy\t "   << proposedPars[0] << std::endl
    << "DM2\t "      << proposedPars[1] << std::endl
    << "Theta23\t "  << proposedPars[2] << std::endl
    << "Theta13\t "  << proposedPars[3] << std::endl
    << "dm2\t "      << proposedPars[4] << std::endl
    << "Theta12\t "  << proposedPars[5] << std::endl
    << "Delta\t "    << proposedPars[6] << std::endl
    << "n_series " << proposedPars[7] << std::endl
    << "Beta\t "     << proposedPars[8] << std::endl;

}
