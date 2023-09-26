function [misclosure,misclosureSD] = loopMisclosure(means,meanVar)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
misclosure = sum(means);
misclosureVar = sum(meanVar);
misclosureSD = sqrt(misclosureVar);
end