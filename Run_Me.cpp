


#include "Run_Me.hpp"

Run_Me::Run_Me(std::string channel, std::string FD, std::string PD, std::string Theta23, int SF, std::string data_name){

  _channel = channel;
  _FD = FD;
  _PD = PD;
  _Theta23 = Theta23;
  _SF = SF;
  _data_name = data_name;
  ext = ".root";
  output = "output.root";
  mean = "mean.root";
  markov =_data_name+ext;
  plotter = _data_name+output;
  file_out = _data_name+mean;

  ////// CREATE DISAPPEARANCE OBJECT FOR +-250A stream "p" = +250, "m" = -250
  if(channel.compare("p") ==0){
    Nu = new Disappearance(1, "t2kflux_2016_plus250kA.root", "enu_sk_numu", "enu_sk_numub","enu_sk_nue", "enu_sk_nueb", 2, _SF);
    Nu->scale_factor(_SF);
    kNuBar = 1;
    std::cout << "Created +250A object. With scale factor " << SF << "." << std::endl;
  }

  else if (channel.compare("m") ==0){
    Nu = new Disappearance(-1, "t2kflux_2016_minus250kA.root", "enu_sk_numu", "enu_sk_numub","enu_sk_nue", "enu_sk_nueb", 2, SF);
    Nu->scale_factor(SF);
    kNuBar = -1;
    std::cout << "Created -250A object. With scale factor " << SF << "." << std::endl;
  }
  
  else{std::cout << "Incorrect channel character selected. No object constructed. Program exited." << std::endl; exit(1);}

  c_pars = Nu->return_cparam();
  par_name = Nu->return_sparam();

  //////// POPULATE PREDICTED DATA "p" for PMNS prob, "t" for series prob
  if( _PD.compare("p") ==0){
    Nu->make_sum('p','d',false);
    std::cout << "Predicted data populated with PMNS probability." << std::endl;
  }
  else if(_PD.compare("t") == 0){
    p_pars = Nu->return_cparam();
    Nu->taylor('p', p_pars);
    std::cout << "Predicted data populated with Taylor Probability." << std::endl;}
   else { std::cout << "Incorrect predicted data character selected" << std::endl;}


  ///////////// POPULATE FAKE DATA "P" for PMNS, "t" for taylor unphysical
  if (_FD.compare("p") == 0){
    if(_Theta23.compare("0.45") ==0){
      Nu->set_param(2,0.45, 'c');
      std::cout << "Theta23 = 0.45." << std::endl;
    }
    Nu->make_sum('f','d',false);
    std::cout << "Fake data created with PMNS probability." << std::endl;
  }
  else if (_FD.compare("t") == 0){
    // set unphysical parameters for taylor in intial
    Nu->set_param(9,0.994999,'c');                                                  Nu->set_param(10, -0.00621572,'c');
    Nu->set_param(11, -0.767751,'c');                                               Nu->set_param(12, -0.0256796,'c');
    Nu->set_param(13, 0.210259,'c');                                                Nu->set_param(14,0.0295561,'c');
    Nu->set_param(15, -0.0534232,'c');                                              Nu->set_param(16,0.0130089,'c');
    Nu->set_param(17,-0.000979787,'c');   
    t_pars =  Nu->return_cparam();
    Nu->taylor('d', t_pars);
    std::cout << "Fake data created with Taylor unphysical probability." << std::endl;
  }
  else{std::cout<< "Incorrect fake data character selected" << std::endl;}
  
  
}

Run_Me::~Run_Me(){}

void Run_Me::mcmc(std::vector<int> set, bool disa){

  MC = new Markov_Chain(c_pars,par_name,1000000,markov.c_str());
    
    for(int i =0; i<set.size(); i++){

      MC->set_param(set[i]);
      
    }
    
    MC->startMH(c_pars, Nu, disa);

  }

void Run_Me::plot(){

  P = new Plotter(markov.c_str(), plotter.c_str(), kNuBar);
  
  if(_PD=="p"){

   P->make_2d_pmns();

  }

  else if (_PD =="t"){

   P->make_2d_taylor();
    
  }

  else {std::cout << "Plotter not made." << std::endl;}
  
  A = new analysis(plotter.c_str(),file_out.c_str());

  A->make_mean();
  
}
