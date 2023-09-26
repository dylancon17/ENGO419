clc;
clear;

obs = load("question2obs.txt");
obsSD = 0.002;
significance = 0.05;

TestMisclosure(obs,obsSD,0,significance);
obsUpdated = TestIndividualObs(obs,obsSD,0,significance);


TestMisclosure(obsUpdated,obsSD,0,significance);
TestIndividualObs(obsUpdated,obsSD,0,significance);





