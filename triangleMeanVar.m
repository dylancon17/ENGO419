function [meanVar] = triangleMeanVar(obs,a,b,n)
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here
obsSDdistance = (obs .* b) ./ 1000000
obsSDfixed = a / 1000 * ones(5,3)
obsSD = obsSDdistance + obsSDfixed
obsVar = obsSD.^2
obsVarMean = mean(obsVar,1,"omitnan")
meanVar = obsVarMean ./ n
end