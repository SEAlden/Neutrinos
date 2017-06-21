//
//  Markov_Chain.cpp
//
//
//  Created by Siobhan Alden & Andrew Yong on 16/06/2017.
//
//

#include "Markov_Chain.hpp"

Markov_Chain::Markov_Chain(std::vector<double> currentPars, std::vector<double> coef, int nstep, std::string filename){
    
    
    
    steps = nstep;
    file = new TFile(filename.c_str(),"RECREATE");
    outputtree = new TTree("outputtree","");
//    outputtree->Branch("Energy", &currentPars[0], "Energy/D");//0
//    outputtree->Branch("DM2",&currentPars[1],"DM2/D");//1
//    outputtree->Branch("Theta23",&currentPars[2],"Theta23/D");//2
//    outputtree->Branch("Theta13",&currentPars[3],"Theta13/D");//3
//    outputtree->Branch("dm2",&currentPars[4],"dm2/D");//4
//    outputtree->Branch("Theta12",&currentPars[5],"Theta12/D");//5
//    outputtree->Branch("Delta",&currentPars[6],"Delta/D");//6
//    outputtree->Branch("n_series",&currentPars[7],"n_series/D");//7
//    outputtree->Branch("Beta",&currentPars[8],"Beta/D");//8
    outputtree->Branch("first",&coef[0],"first/D");//9
    outputtree->Branch("second",&coef[1],"second/D");//10
    outputtree->Branch("third",&coef[2],"third/D");//11
    outputtree->Branch("fourth",&coef[3],"fourth/D");//12
    outputtree->Branch("fifth",&coef[4],"fifth/D");//13
    outputtree->Branch("sixth",&coef[5],"sixth/D");//14
    outputtree->Branch("seventh",&coef[6],"seventh/D");//15
    outputtree->Branch("eigth",&coef[7],"eigth/D");//16
    outputtree->Branch("ninth",&coef[8],"ninth/D");//179
    
    
    outputtree->Branch("LLH",&currentLLH,"LLH/D");
    
    outputtree->Fill();
    
    for( int i = 0; i<=8; i++){
        
        pars.push_back(false);
        coef_bool.push_back(true);
        proposedPars.push_back(0);
        proposedcoef.push_back(0);
         // populates the proposedPars vector
        
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
    width.push_back(1.00043);
    width.push_back(-0.00513335);
    width.push_back(-0.81076);
    width.push_back(-0.0217913);
    width.push_back(0.223944);
    width.push_back(0.0340821);
    width.push_back(-0.0569585);
    width.push_back(0.0133551);
    width.push_back(-0.000970247);
    
    
    
    
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

void Markov_Chain::startMH(std::vector<double> currentPars, std::vector<double> coef, Disappearance* oscObject ){
    currentLLH = oscObject->getLLH();
    
    for(int i=0; i<steps; i++){
       
        
        // std::cout << "tag a" << std::endl;
        
        if(i%100==0 || i==0){
            
            if(i==0){
                std::cout << "Initialising random walk..." << std::endl;
            }
            
            else{
                std::cout << "i " << i << "Running random walk..." << std::endl;
            }
            
        }
        //std::cout << "tag b" << std::endl;
        
        for(int j=0; j<currentPars.size(); j++) {
            
            if(pars[j]){
                
                proposedPars[j]=rnd->Gaus(currentPars[j],width[j]);//width has to be tuned
                oscObject->set_paras(j, proposedPars[j],'p');
            }
        
        }
       // std::cout << "tag c" << std::endl;

        for(int k = 0; k<coef.size();k++){
            
            if(coef_bool[k]){
                
                proposedcoef[k]=rnd->Gaus(coef[k],width[k]);
                oscObject->set_paras_d(k, proposedcoef[k],'p');

            }
            
            oscObject->taylor('p');
            
        }
       // std::cout << "tag d" << std::endl;

        proposedLLH = oscObject->getLLH();
        
        double accProb = TMath::Min(1.,TMath::Exp(currentLLH-proposedLLH));
        double fRandom = rnd->Rndm();
        
        
        //std::cout << "tag e" << std::endl;

        if ( fRandom <= accProb )
        {
            for(int n=0; n<currentPars.size(); n++)
            {
                if(pars[n]){
                    currentPars[n]=proposedPars[n];
                }
            }
            for(int m=0; m<coef.size(); m++)
            {
                if(pars[m]){
                    coef[m]=proposedcoef[m];}
            }
            currentLLH=proposedLLH;
        }
       // std::cout << "tag f" << std::endl;

       // std::cout<< "check" << std::endl;
        outputtree->Fill();
        if(i==steps-1){
            std::cout << "Metropolis-Hastings algorithm completed." << std::endl;
        
        }
    }
    outputtree->Write();
    file->Close();
    
}
void Markov_Chain::startMH(std::vector<double> currentPars, Appearance *plusObj, Appearance *minusObj){
    
    
    
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



void Markov_Chain::set_pars(int index){
    
    pars[index] = true;
    
}

void Markov_Chain::set_coef(int index){
    
    coef_bool[index] = true;
    
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

