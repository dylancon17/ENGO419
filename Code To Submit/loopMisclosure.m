%{
--------------------------------Title--------------------------------------
File loopMisclosure.m for ENGO 419 - Geomatics Networks
    Lab 1 - Precision analysis of observations, data pre-processing and pre-adjustment screening
    Question 2 – Blunder detection for height differences
    
    Dylan Conley, Titus Castillon, Nick Kennedy
    Written September 26, 2023 for Lab 1
    
    This function is used to determine the misclosure in a levelling loop
    and the associated standard deviation
%}

%means the average observation of each observation
%meanVar the variance of each mean observation
function [misclosure,misclosureSD] = loopMisclosure(means,meanVar)
%adds all of the observation means
misclosure = sum(means);
%adds all of the observation variances
misclosureVar = sum(meanVar);
misclosureSD = sqrt(misclosureVar);
end