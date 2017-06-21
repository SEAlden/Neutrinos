// #include "Nu_Fitter.hpp"
#include "Appearance.h"


Appearance::Appearance(int kNuBarVar, std::string path, std::string filename, std::string filename2, std::string filename3, std::string filename4):Nu_Fitter(kNuBarVar, path, filename,filename2,filename3,filename4){

  beta = 1; // by default beta is equal to 1
}

Appearance::~Appearance(){

}

double Appearance::getLLH(Appearance* dataObj){

  double LLH = 0;
  double lambda,N;

  for(int j = 1; j <=nbin; j++){
    lambda = _Prediction->GetBinContent(j); // treat the object calling the function as the fitter (varying) object and the argument as the data (to be fitted)
    N = dataObj->getBinVal(j);

    if(N!=0&&lambda!=0){ // to prevent nan at later bins(higher energies) with 0 entries
        LLH += lambda-N - N*log(lambda/N);
        //std::cout << " lambda " << lambda << " Data " << N << " total LLH " << LLH << " LLH " << lambda-N - N*log(lambda/N) << std::endl;

    }
  }

  return LLH;

}

double Appearance::getBinVal(int i){

  return _Data->GetBinContent(i);

}
