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
The class constructor takes in an integer, kNuBarVar, which 

##OTHER DETAILS##



###############
CONTACT DETAILS
###############

Andrew Yong
ayzn95@gmail.com

Siobhan Alden
siobhanalden@hotmail.com
