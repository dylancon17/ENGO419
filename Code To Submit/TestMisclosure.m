%{
--------------------------------Title--------------------------------------
File TestMisclosure.m for ENGO 419 - Geomatics Networks
    Lab 1 - Precision analysis of observations, data pre-processing and pre-adjustment screening
    Question 2 – Blunder detection for height differences
    Question 3 – Blunder detection for distance observations
    
    Dylan Conley, Titus Castillon, Nick Kennedy
    Written September 26, 2023 for Lab 1
    
    This function is used to test the system misclosure against a Z
    distribution at a given confidence
%}

% obs An m x n matrix of observations
% a IF levelling loop then the error per observation in m,
%   IF distance measurements then the fixed term in the error in mm
% b IF levelling loop then 0
%   IF distance measurements then the distace term in the error in ppm
% significance a value in range [0,1] of the level of significance to test
function TestMisclosure(obs,a,b,significance)

%Finds the mean of each column
means = mean(obs,1,"omitnan");

%n Counts the number of not NAN occurences in each column 
n = height(obs) * ones(1,width(obs));
for i = 1:height(obs)
    for j = 1:width(obs)
        if isnan(obs(i,j))
            n(1,j) = n(1,j) - 1;
        end
    end
end

%Calcs misclosure and misclosure SD for levelling loop
if b==0
    meanVar = loopMeanVar(a,n);
    [misclosure, misclosureSD] = loopMisclosure(means,meanVar);
%Calcs misclosure and misclosure SD for triangle measurements
else
    meanVar = triangleMeanVar(obs,a,b,n);
    [misclosure, misclosureSD] = triangleMisclosure(means,meanVar);
end

%Test statistic
y = misclosure / misclosureSD;

%Gets two-tailed Z value using statistics toolbox
alpha = (1- significance/2);
Z = icdf('Normal', alpha, 0, 1);

disp("Results of Testing Misclosure")
means
meanVar
misclosure
misclosureSD
y
Z

%Tests test statistic against the bounds
if abs(y) < Z
    disp("Misclosure Test Passed");
else
    disp("Misclosure Test Failed");
end

end