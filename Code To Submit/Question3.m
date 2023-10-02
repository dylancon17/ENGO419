%{
--------------------------------Title--------------------------------------
File Question3.m for ENGO 419 - Geomatics Networks
    Lab 1 - Precision analysis of observations, data pre-processing and pre-adjustment screening
    Question 3 – Blunder detection for distance observations

    
    Dylan Conley, Titus Castillon, Nick Kennedy
    Written September 26, 2023 for Lab 1
    
    This file is used to load question 3 data and test the system and individual
    observations for blunders
%}
clc;
clear;

%Loads the data
obs = load("question3obs.txt");
a = 3;
b = 2;
significance = 0.10;

%Tests misclosure and indiviudal observations
TestMisclosure(obs,a,b,significance);
obsUpdated = TestIndividualObs(obs,a,b,significance);

%Retests misclosure and indiviudal observations after a blunder is removed
TestMisclosure(obsUpdated,a,b,significance);
obsUpdated = TestIndividualObs(obsUpdated,a,b,significance);


