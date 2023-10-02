%{
--------------------------------Title--------------------------------------
File triangleMeanVar.m for ENGO 419 - Geomatics Networks
    Lab 1 - Precision analysis of observations, data pre-processing and pre-adjustment screening
    Question 3 – Blunder detection for distance observations
    
    Dylan Conley, Titus Castillon, Nick Kennedy
    Written September 26, 2023 for Lab 1
    
    This function is used to determine the mean variance of each column in
    a given matrix of standard deviations with n observations in each
    column for observations of a triangle
%}

% obs a m x o matrix of the initial observations
% a the fixed error per measurement in mm
% b the ppm in per measurement in ppm
% n a 1 x n vector of the number of non NaN values in each column
function [meanVar] = triangleMeanVar(obs,a,b,n)

%Finds the ppm error for each obs
obsSDdistance = (obs .* b) ./ 1000000;
%Finds the fixed distance for each obs (const across the data)
obsSDfixed = a / 1000 * ones(5,3);
%Squares the SD's and add's them to find combined variance
%An alternative method is to add the SD's together but that does not follow
%proper techniques of error propogation in adding variances
obsVar = obsSDdistance.^2 + obsSDfixed.^2;
%Finds the meanVariance of the row by taking the average variance and then
%dividing by the number of measurements
obsVarMean = mean(obsVar,1,"omitnan");
meanVar = obsVarMean ./ n;
end