function [misclosure,misclosureSD] = triangleMisclosure(means,meansVar)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
AB_CALC = sqrt(means(1,1)^2+means(1,2)^2);
misclosure = AB_CALC - means(1,3);

term1 = meansVar(1,1) * means(1,1)^2 / AB_CALC^2
term2 = meansVar(1,2) * means(1,2)^2 / AB_CALC^2
term3 = meansVar(1,3)

disp(meansVar(1,1))
disp(meansVar(1,2))
disp(meansVar(1,3))

misclosureSD = sqrt(term1 + term2 + term3);
end