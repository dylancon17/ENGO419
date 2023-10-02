%{
--------------------------------Title--------------------------------------
File triangleMisclosure.m for ENGO 419 - Geomatics Networks
    Lab 1 - Precision analysis of observations, data pre-processing and pre-adjustment screening
    Question 3 – Blunder detection for distance observations
    
    Dylan Conley, Titus Castillon, Nick Kennedy
    Written September 26, 2023 for Lab 1
    
    This function is used to determine the misclosure and the associated 
    standard deviation of a right-sided triangle with three measured 
    distances
%}

%means the average observation of each observation
%meanVar the variance of each mean observation
function [misclosure,misclosureSD] = triangleMisclosure(means,meansVar)

%Calcs the hypoteneuse and compares it to the measured hypoteneuse
AB_CALC = sqrt(means(1,1)^2+means(1,2)^2);
misclosure = AB_CALC - means(1,3);

%Follows the error propogation formula set out in the procedure
term1 = meansVar(1,1) * means(1,1)^2 / AB_CALC^2;
term2 = meansVar(1,2) * means(1,2)^2 / AB_CALC^2;
term3 = meansVar(1,3);

misclosureSD = sqrt(term1 + term2 + term3);
end