//
//  Disappearance.cpp
//  
//
//  Created by Siobhan Alden on 13/06/2017.
//
//

#include "Disappearance.hpp"
#include <iostream>
#include <vector>

Disappearance::Disappearance(int kNuBarVar, std::string path, std::string filename, std::string filename2, std::string filename3, std::string filename4, int mass):Nu_Fitter(kNuBarVar, path, filename, filename2, filename3, filename4){
 
    if (mass == 1){
        dm_sq = currentPars[4];
    }
    
    else if (mass ==2){
        dm_sq = currentPars[1];
    }
    
    else{
        std::cout << "wrong input" << std::endl;
    }
    
    a = 1.27*L*dm_sq;
    
    currentPars.push_back(1.00043);
    currentPars.push_back(-0.00513335);
    currentPars.push_back(-0.81076);
    currentPars.push_back(-0.0217913);
    currentPars.push_back(0.223944);
    currentPars.push_back(0.0340821);
    currentPars.push_back(-0.0569585);
    currentPars.push_back(0.0133551);
    currentPars.push_back(-0.000970247);
    
   // std::cout << currentPars.size()<< std::endl;
    
    parsName.push_back("First");
    parsName.push_back("Second");
    parsName.push_back("Third");
    parsName.push_back("Fourth");
    parsName.push_back("Fifth");
    parsName.push_back("Sixth");
    parsName.push_back("Seventh");
    parsName.push_back("Eighth");
    parsName.push_back("Ninth");
    
   // std::cout << parsName.size() << std::endl;
    
    
    
    //std::cout << "tag A" << std::endl;
    
    for(int i =1; i<=_input1->GetNbinsX(); i++){
        
        Ene.push_back(_input1->GetXaxis()->GetBinCenter(i));
        
    }
    
    //std::cout << "tag B" << std::endl;
    
    for (int j =1; j <= Ene.size(); j++){
        
        bin1.push_back(_input1->GetBinContent(j));
        //std::cout << j <<  bin1[j-1] << std::endl;
        bin2.push_back(_input2->GetBinContent(j));
        bin3.push_back(_input3->GetBinContent(j));
        bin4.push_back(_input4->GetBinContent(j));
    }
    
    //std::cout << "tag C" << std::endl;
    
   // file = new TFile(root_file.c_str());
    
//    file2 = new TFile(root_name.c_str(),"RECREATE");
//    pick = new TTree("z","");
//    
//    pars.resize(9,0);
//    
    //outfile2d = new TFile("outfile2d.root","RECREATE");
    
    //hFunction =  new TH2D("hf","",200,0,2,200,-0.5,2.5);
    
    //tree = (TTree*)file->Get("t");
//    
//    tree->SetBranchAddress("First",&pars[0]);
//    tree->SetBranchAddress("Second",&pars[1]);
//    tree->SetBranchAddress("Third",&pars[2]);
//    tree->SetBranchAddress("Fourth",&pars[3]);
//    tree->SetBranchAddress("Fifth",&pars[4]);
//    tree->SetBranchAddress("Sixth",&pars[5]);
//    tree->SetBranchAddress("Seventh",&pars[6]);
//    tree->SetBranchAddress("Eighth",&pars[7]);
//    tree->SetBranchAddress("Ninth",&pars[8]);
//    
//    tree->GetEntry(0);
//
//    pick->Branch("First",&pars[0], "First/D");
//    pick->Branch("Second",&pars[1], "Second/D");
//    pick->Branch("Third",&pars[2], "Third/D");
//    pick->Branch("Fourth",&pars[3], "Fourth/D");
//    pick->Branch("Fifth",&pars[4], "Fifth/D");
//    pick->Branch("Sixth",&pars[5], "Sixth/D");
//    pick->Branch("Seventh",&pars[6], "Seventh/D");
//    pick->Branch("Eighth",&pars[7], "Eighth/D");
//    pick->Branch("Ninth",&pars[8], "Ninth/D");
//    
//    pick->Fill();
//    
}

Disappearance::~Disappearance(){}

void Disappearance::make_Prediction(char hist_type, int which){
    
    for(int i = 1; i <= nbin; i++){
        
        double Eng = _input1->GetBinCenter(i);
        double bin_content1 = _input1->GetBinContent(i);
        double bin_content2 = _input2->GetBinContent(i);
        double bin_content3 = _input3->GetBinContent(i);
        double bin_content4 = _input4->GetBinContent(i);
        
        double prob,weight;
        
        if(which == 1){
            prob = series(Eng);
            if(prob >=1){
                prob =0;
            }
            weight = prob*bin_content1 + prob*bin_content2 +prob*bin_content3 + prob*bin_content4;
            
            //std::cout << "weight " << weight << " Prob " << prob << " Eng " << Eng << std::endl;
            
            if(hist_type == 'd'){
                _Data->SetBinContent(i,weight);
            }
            else if(hist_type == 'p'){
                _Prediction->SetBinContent(i,weight);
            }
            else{std::cout << "Invalid Hist Type" << std::endl;}
            
        }
        
        else if(which == 2){
            
            prob = approx(Eng);
            weight = prob*bin_content1 + prob*bin_content2 + prob*bin_content3 + prob*bin_content4;
            if(hist_type == 'd'){
                _Data->SetBinContent(i,weight);
            }
            else if(hist_type == 'p'){
                _Prediction->SetBinContent(i,weight);
            }
            else{std::cout << "Invalid Hist Type" << std::endl;}
            
        }
        
        else if(which == 3){
            
            prob = osci_prob(Eng);
            weight = prob*bin_content1 + prob*bin_content2 + prob*bin_content3 + prob*bin_content4;
            if(hist_type == 'd'){
                _Data->SetBinContent(i,weight);
            }
            else if(hist_type == 'p'){
                _Prediction->SetBinContent(i,weight);
            }
            else{std::cout << "Invalid Hist Type" << std::endl;}
            
            
        }
        
        else{
            std::cout << "Incorrect series choice" << std::endl;
        }
        
    }
    
}

double Disappearance::series(double E){
    
    double tot = 0;
        
    for(int k = 1; k<=currentPars[7];k++){
            
        double series = (-1)*(pow((-1),k)*pow(2,(-1+2*k))*pow((a/E),2*k))/(fact(2*k));
        //std::cout << "a " << a << " fact " << fact(2*k) << " tot " << tot << std::endl;
        tot = tot + series;
            
    }
        
    double coef = sin(2.0*currentPars[2]);
        
    double coef_sq = coef*coef;
        
    return 1-coef_sq*tot;
    
    
}

double Disappearance::fact(int n){

    double f = 1;
    if(n >= 1){
        
        for(int j = 1; j <=n; j++){
            f = f*j;
        }
    }
    return f;

}

double Disappearance::approx( double E){
    
 
  
    double sin_E = sin(a/E);
    double sin_sq = sin_E*sin_E;
    
    double coef = sin(2.0*currentPars[2]);
    double coef_sq = coef*coef;
    
    return 1-coef_sq*sin_sq;

}

double Disappearance::osci_prob( double E){


    double sin_E = sin(a/E);
    double sin_sq = sin_E*sin_E;
    
    double coef = cos(currentPars[3])*cos(currentPars[3])*sin(currentPars[2])*sin(currentPars[2]);//complete expression
    
    return 1.0-(4.0*coef*sin_sq-coef*coef*sin_sq);
    

}

double Disappearance::taylorinv(double x, std::vector<double>& par)
{
    // for(int i=0; i<9; i++)
    //    printf("%f\n",par[i]);
    
    double sum = 0;
//    std::cout <<"In taylorinv" << par.size() << std::endl;
    
    for(int i=0; i<9; i++)
    {
     //   std::cout << par[i+9] << std::endl;
        sum+=par[i+9]*pow(1/x,i);
        
    }
//std::cout << "In taylorinv: " << "\t" << sum << std::endl;
    return sum;
}


void Disappearance::taylor(char hist_type,std::vector<double> &pars){

   
    for (int j =0; j < Ene.size(); j++){
        
        
       // std::cout << "In taylor" << currentPars.size() << std::endl;
        
        double prob = taylorinv(Ene[j], pars);
        
       // std::cout << Ene[j] << "," << prob << std::endl;
        
       // std::cout << "b1 " << bin1[j] << " b2 " << bin2[j] << std::endl;
        double  weight = prob*bin1[j]*sigma_cc(2,Ene[j]) + prob*bin2[j]*sigma_cc(-2, Ene[j]) + prob*bin3[j]*sigma_cc(2,Ene[j]) + prob*bin4[j]*sigma_cc(-2,Ene[j]);
        //std::cout << j <<  "\tweight " << weight << std::endl;
        
        if(weight<0)
            weight=1E-8;
        
        if(hist_type == 'd'){
            _Data->SetBinContent(j+1,weight);
        }
        else if(hist_type == 'p'){
            
            //if(j==0){
               // std::cout << "taylor is making a series probability for disappearance for prediction" << std::endl;}

            //std::cout<< " weight " << weight << std::endl;
            _Prediction->SetBinContent(j+1,weight);
    
        }
        else{std::cout << "Invalid Hist Type" << std::endl;}
    }
    


}

//std::vector<double> Disappearance::return_cparam(){
//
//    return currentPars;
//    
//}


//void Disappearance::make_2d(){
//    
//    
//    for(int i=0; i<tree->GetEntries(); i+=200)
//        //   for(int i=0; i<100; i++)
//    {
//        printf("N: %i\n",i);
//        tree->GetEntry(i);
//        
//        for(int j=1; j<=hFunction->GetNbinsX(); j++)
//        {
//            double E = hFunction->GetXaxis()->GetBinCenter(j);
//            double prob = function(pars,E);
//            if(prob<0&& E>0.4){
//                
//                std::cout << "maybe" << std::endl;
//                pick->Fill();
//            }
//            
//            
//            hFunction->Fill(E,prob);
//        }
//        
//    }
//    
//    pick->Write();
//    hFunction->Write();
//    file2->Close();
//    
//    //outfile2d->Close();
//    //hFunction->Draw("colz");
//    
//    
//}
//
//double Disappearance::function(std::vector<double> pars, double E)
//{
//    double val = 0;
//    //loop starts at 9 as first 9 elements of pars == pmns variables
//    for(int i=9; i<pars.size(); i++)
//    {
//        val+=pars[i]*pow(1/E,i);
//    }
//    
//    return val;
//}
