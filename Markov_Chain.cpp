//
//  Markov_Chain.cpp
//
//
//  Created by Siobhan Alden & Andrew Yong on 16/06/2017.
//
//

#include "Markov_Chain.hpp"

Markov_Chain::Markov_Chain(std::vector<double> &obj_pars, std::vector<std::string> &parsName, int nstep, std::string filename){

    steps = nstep;
    file = new TFile(filename.c_str(),"RECREATE");//
    tree = new TTree("tree","");

    double width_factor = 100; // default width factor

    for(int j = 0; j < parsName.size();j++){
      branchName.push_back(parsName[j]+"/D");
      std::cout << branchName[j] << std::endl;
    }

    for(int i = 0; i<obj_pars.size(); i++){
      //fills the branch
      // TString temp = Form("parsName[%i]/D",i);
      TString temp = branchName[i].c_str();
      // tree->Branch(parsName[i].c_str(), obj_pars[i], "hi/D");
      tree->Branch(parsName[i].c_str(), obj_pars[0],Form("parsName[%i]/D",i) ); // Siobhan: although doens't work, Form() might be useful for future
      //initialising width vector; can be fine-tuned with set_width
      // width.push_back(obj_pars[i]/width_factor);
    }

    // std::string bee = "Hi";
    // tree->Branch(parsName[0].c_str(), obj_pars[0] , bee.c_str());


    tree->Fill();

    for( int i = 0; i<=8; i++){
        pars.push_back(false);
        // coef_bool.push_back(true);
        proposedPars.push_back(0);
        // proposedcoef.push_back(0);
         // populates the proposedPars vector

    }

    rnd  = new TRandom3(0);

    //initialising width vector; can be fine-tuned with set_width
    for(int k = 0; k < obj_pars.size(); k++){
      width.push_back(obj_pars[k]/width_factor);
    }
   //E=0 : 0
  //DM2=2.4e-3 : 1
  //theta23=0.5 : 2
  //theta13=0.025 : 3
  //dm2=7.6e-3 : 4
  //theta12=0.312 : 5
  //deltacp=0 : 6
  //n=10 : 7
  //beta=1 : 8
  //coef1=1.00043 : 9
  //coef2=-0.00513335 : 10
  //coef3=-0.81076 : 11
  //coef4=-0.0217913 : 12
  //coef5=0.223944 : 13
  //coef6=0.0340821 : 14
  //coef7=-0.0569585 : 15
  //coef8=0.0133551 : 16
  //coef9=-0.000970247 : 17




}

Markov_Chain::~Markov_Chain(){};

void Markov_Chain::startMH(std::vector<double>& currentPars, Nu_Fitter* oscObject){



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

        tree->Fill();

        if(i==steps-1){
            std::cout << "Metropolis-Hastings algorithm completed." << std::endl;
        }

    }

    tree->Write();
    file->Close();


}

void Markov_Chain::startMH(std::vector<double> &currentPars, Disappearance* oscObject, bool dis){
    /*currentLLH = oscObject->getLLH();
    //int count =0;

    for(int i=0; i<steps; i++){
        if(i%1000==0 || i==0){

            if(i==0){std::cout << "Initialising random walk..." << std::endl;}
            else{std::cout << "i " << i << "Running random walk..." << std::endl;}
        }

        for(int k = 0; k<coef.size();k++){
            if(coef_bool[k]){
                proposedcoef[k]=rnd->Gaus(coef[k],width[k]);
                oscObject->set_paras_d(k, proposedcoef[k],'p');
            }

        }
        oscObject->taylor('p');
        proposedLLH = oscObject->getLLH();
        double accProb = TMath::Min(1.,TMath::Exp(currentLLH-proposedLLH));
        double fRandom = rnd->Rndm();
        //std::cout << "i " << i << " accprob " << accProb << " fRandom " << fRandom << " current LLH " << currentLLH << " proposed LLH " << proposedLLH <<  " parameter 1 current: " << coef[1] << " parameter 1 proposed:" << proposedcoef[1] << std::endl;
         if ( fRandom <= accProb )
        {

            for(int m=0; m<coef.size(); m++)
            {

                if(coef_bool[m]){
                    //count++;
                    std::cout << "coef " << m << " " << coef[m] << " proposed " << m << " " << proposedcoef[m] << std::endl;
                    coef[m]=proposedcoef[m];}

            }
            currentLLH=proposedLLH;
        }

        //std::cout << " 0 " << coef[0] << " 1 " << coef[1] << " 2 " << coef[2]  << std::endl;
        tree->Fill();


        if(i==steps-1){
            std::cout << "Metropolis-Hastings algorithm completed." << std::endl;

        }
    }

   // std::cout << count << std::endl;
    tree->Write();
    file->Close();*/

}
void Markov_Chain::startMH(std::vector<double> &currentPars, Appearance *plusObj, Appearance *minusObj){



    currentLLH = plusObj->getLLH() + minusObj->getLLH(); // add LLH from two files

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
                plusObj->set_paras(j, proposedPars[j],'p');
                minusObj->set_paras(j, proposedPars[j],'p');

            }
            plusObj->make_sum('p','p',true);
            minusObj->make_sum('p','p',true);

        }
        proposedLLH = plusObj->getLLH() + minusObj->getLLH();

        double accProb = TMath::Min(1.,TMath::Exp(currentLLH-proposedLLH));
        double fRandom = rnd->Rndm();


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

        tree->Fill();

        if(i==steps-1){
            std::cout << "Metropolis-Hastings algorithm completed." << std::endl;
        }

    }

    tree->Write();
    file->Close();


}



void Markov_Chain::set_pars(int index){

    pars[index] = true;

}

// void Markov_Chain::set_coef(int index){
//
//     coef_bool[index] = true;
//
// }

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
