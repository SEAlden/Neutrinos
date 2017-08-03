# Neutrinos
####################################
Neutrino Oscillation Fitting Program
####################################
Created by A. Kaboth, S. Alden, A. Yong

Welcome!

This README is designed to explain how one can use the classes developed to analyse neutrino flux data from long baseline experiments. Please note that this serves as merely a qualitative guide to using the program. For documentations regarding the member function and variables, please refer to the header (.h or .hpp) files.

#########################
INTRODUCTION & MOTIVATION
#########################

The set of classes are developed with two main objectives:

1) From long baseline experiments in the near future, the value for various PMNS parameters may be further constrained. This is done by minimising the log likelihood (LLH) between the measured neutrino (and antineutrino) flux and the fit based on current (August 2017) values of PMNS parameters.

2) Based on previous simulations, there is a clear distinction between the neutrino and antineutrino flux values, indicating the possibility of CPT and Lorentz symmetry violation. New flux measurements of fluxes will provide grounds for measuring the delta CP phase factor. Further, we propose an additional parameter, beta, that feeds into oscillation probability in attempt to help account for this asymmetry.

The improvement on standard PMNS parameters and the determination of the beta parameter are done iteratively using a Markov Chain Monte Carlo. The code is written using a combination of C++ and ROOT and can be compiled using the Makefile provided.

To analyse Appearance phenomenon, enter the following command in the terminal:
make appmain; ./appmain scale_factor beta1 beta2 filename yes_no
where,
scale_factor: converts the flux/P.O.T data into purely flux data,
beta1: is the beta value of the data (enter 1 by default),
beta2: is the initial seed of the fit's beta value,
filename: is the name the MCMC will be saved as,
yes_no: is a Boolean to vary the fit's beta value.

To analyse Disappearance phenomenon, enter the following command in the terminal:


#######
CLASSES
#######

#########
Nu_Fitter
#########

This is the base class in which Appearance and Disappearance objects inherit mutual member variables and functions from.

##CONSTRUCTOR##

The class constructor takes in an integer, kNuBarVar, which takes the value 1 by default, the filepath to the .root file and the four flux files for each neutrino and antineutrino beam. The specific names of the four flux files can be obtained by accessing the .root file via a TBrowser in the ROOT interactive environment.


##########
Appearance
##########

The Appearance class simply exists for nomenclature reasons. This class only uses member variable and function of the base class, but its class type allows the Monte Carlo class to select the appropriate Markov Chain for the appearance phenomenon in neutrino oscillation.

##CONSTRUCTOR##

Just as a Nu_Fitter constructor, the Appearance constructor takes an integer value for the kNuBarVar variable, the filepath to the .root file and the four flux files within the .root file.


#############
Disappearance
#############

##CONSTRUCTOR##



############
Markov_Chain
############

This class is designed to run Markov Chain Monte Carlo (MCMC) simulations. Using the Metropolis-Hastings algorithm, the MCMC simulation will produce a distribution of values that minimises the LLH between the fit and data. The constraint on the parameter values improve with higher number of iterations but at the cost of longer runtime.

##CONSTRUCTOR##

The Markov_Chain constructor takes four arguments:

1) a vector containing the value of all neutrino oscillation parameters(PMNS and additionally proposed). This can be accessed using the return_cparam() member function of Nu_Fitter class.

2) a vector containing the name of all neutrino oscillation parameters(PMNS and additionally proposed). This can be accessed using the return_sparam() member function of Nu_Fitter class.

3) the number of iterations for the simulation.

4) filename to be saved in the directory.

##OTHER DETAILS##

The width (which is responsible for adjusting the parameter value within the neighbourhood of the Gaussian) can be manually tuned by using the set_with() function. Note that we have already tuned the width of each default parameter provided. From experience, the quality of the distribution of values depends sensitively to minor changes in the width, so proceed with caution.

The member function apply_constraint() is a neat method of preventing the Metropolis-Hastings algorithm from choosing 'unphysical' values. If the user wishes to add an additional physical parameter, please ensure include a constraint in the member function in a similar fashion to pre-existing ones.

#############
boundPlot.cpp
#############

Once a .root file containing the distribution of all MCMC-varied parameters has been saved, one can bound the distribution to determine where 90% of the values have minimum LLH. This is done by calling the compiled code in the ROOT interactive shell.

The function takes the .root filename, the parameter that underwent MCMC simulation and the usual parameters for constructing a ROOT histogram (number of bins between the lower and upper bound).



###############
CONTACT DETAILS
###############

Andrew Yong
ayzn95@gmail.com

Siobhan Alden
siobhanalden@hotmail.com

Asher Kaboth
a.kaboth@rhul.ac.uk
