function [meanVar] = loopMeanVar(obsSD,n)
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
meanSD = obsSD ./ sqrt(n);
meanVar = meanSD.^2;
end