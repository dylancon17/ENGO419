%{
--------------------------------Title--------------------------------------
File TestIndividualObs.m for ENGO 419 - Geomatics Networks
    Lab 1 - Precision analysis of observations, data pre-processing and pre-adjustment screening
    Question 2 – Blunder detection for height differences
    Question 3 – Blunder detection for distance observations
    
    Dylan Conley, Titus Castillon, Nick Kennedy
    Written September 26, 2023 for Lab 1
    
    This function is used to test each observation against the observation
    means for each column in the data for either a levelling loop or
    triangular distance measurements
%}

% obs An m x n matrix of observations
% a IF levelling loop then the error per observation in m,
%   IF distance measurements then the fixed term in the error in mm
% b IF levelling loop then 0
%   IF distance measurements then the distace term in the error in ppm
% significance a value in range [0,1] of the level of significance to test
function [obs] = TestIndividualObs(obs,a,b,significance)

%Finds the mean of each column
means = mean(obs,1,"omitnan");

%n Counts the number of not NAN occurences in each column 
%Determines the residuals for each observation by residual = obs - obs_mean
n = height(obs) * ones(1,width(obs));
residuals = zeros(height(obs),width(obs));
for i = 1:height(obs)
    for j = 1:width(obs)
        if isnan(obs(i,j))
            n(1,j) = n(1,j) - 1;
            residuals(i,j) = NaN;
        else
            residuals(i,j) = obs(i,j) - means(1,j);
        end
    end
end

%Calcs obsSD for levelling loop per observation
if b==0
    obsSD = a.*ones(5,6);
%Calcs obsSD for distance measurements per observation
else
    %Finds the ppm error for each obs
    obsSDdistance = (obs .* b) ./ 1000000;
    %Finds the fixed distance for each obs (const across the data)
    obsSDfixed = a / 1000 * ones(5,3);
    %Squares the SD's and add's them to find combined variance and then
    %converts to SD
    %Squared then added to obey error propogation laws
    obsSD = sqrt(obsSDdistance.^2 + obsSDfixed.^2);
end

%Gets two-tailed Z value using statistics toolbox
alpha = (1- significance/2);
Z = icdf('Normal', alpha, 0, 1);

%The end result will display no blunders with 0's and blunders with 1's
blunderDetected = zeros(height(obs),width(obs));
yMatrix = zeros(height(obs),width(obs));


for i = 1:height(obs)
    for j = 1:width(obs)
        %Follows equation in method to calc test statistic
        nObs = n(1,j);
        temp = sqrt((nObs-1)/nObs)*obsSD(i,j);
        y = residuals(i,j) / temp;
        %Tests the test statistic
        if abs(y) > Z
            blunderDetected(i,j) = 1;
            %If a blunder updates the observations by removing the blunder
            %value
            obs(i,j) = NaN;
        end
        %Used for debugging
        yMatrix(i,j) = y;
    end
end
disp("Results of Testing Individual Observations")
residuals
obsSD
Z
yMatrix
blunderDetected
end