#ifndef _APPEARANCE_
#define _APPEARANCE_

#include "Nu_Fitter.hpp"

class Appearance:public Nu_Fitter{

public:

  Appearance(int kNuBarVar, std::string path, std::string filename, std::string filename2, std::string filename3, std::string filename4);
  ~Appearance();

  double getLLH(Appearance* dataObj); // function argument is always the 'fixed' data
  double getBinVal(int i);


private:

  double beta;
};

#endif
