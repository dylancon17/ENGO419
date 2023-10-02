%{
--------------------------------Title--------------------------------------
File Question2.m for ENGO 419 - Geomatics Networks
    Lab 1 - Precision analysis of observations, data pre-processing and pre-adjustment screening
    Question 2 – Blunder detection for height differences
    
    Dylan Conley, Titus Castillon, Nick Kennedy
    Written September 26, 2023 for Lab 1
    
    This file is used to load question 2 data and test the system and individual
    observations for blunders 
%}

clc;
clear;

%Loads the data
obs = load("question2obs.txt");
obsSD = 0.002;
significance = 0.05;

%Tests misclosure and indiviudal observations
TestMisclosure(obs,obsSD,0,significance);
obsUpdated = TestIndividualObs(obs,obsSD,0,significance);

%Retests misclosure and indiviudal observations after a blunder is removed
TestMisclosure(obsUpdated,obsSD,0,significance);
TestIndividualObs(obsUpdated,obsSD,0,significance);





