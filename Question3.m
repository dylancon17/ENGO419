clc;
clear;

obs = load("question3obs.txt");
a = 3;
b = 2;
significance = 0.10;

TestMisclosure(obs,a,b,significance);
obsUpdated = TestIndividualObs(obs,a,b,significance);

TestMisclosure(obsUpdated,a,b,significance);
obsUpdated = TestIndividualObs(obsUpdated,a,b,significance);


