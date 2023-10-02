%{
--------------------------------Title--------------------------------------
File loopMeanVar.m for ENGO 419 - Geomatics Networks
    Lab 1 - Precision analysis of observations, data pre-processing and pre-adjustment screening
    Question 2 – Blunder detection for height differences
    
    Dylan Conley, Titus Castillon, Nick Kennedy
    Written September 26, 2023 for Lab 1
    
    This function is used to determine the mean variance of each column in
    a given matrix of standard deviations with n observations in each colum
%}

% obsSD a m x o matrix of SD's
% n a 1 x n vector of the number of non NaN values in each column
function [meanVar] = loopMeanVar(obsSD,n)
meanSD = obsSD ./ sqrt(n);
meanVar = meanSD.^2;
end