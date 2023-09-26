function TestMisclosure(obs,a,b,significance)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
means = mean(obs,1,"omitnan");

n = height(obs) * ones(1,width(obs));
for i = 1:height(obs)
    for j = 1:width(obs)
        if isnan(obs(i,j))
            n(1,j) = n(1,j) - 1;
        end
    end
end

if b==0
    meanVar = loopMeanVar(a,n);
    [misclosure, misclosureSD] = loopMisclosure(means,meanVar);
else
    meanVar = triangleMeanVar(obs,a,b,n);
    [misclosure, misclosureSD] = triangleMisclosure(means,meanVar);
end

y_pop = misclosure / misclosureSD;

alpha = (1- significance/2);
Z = icdf('Normal', alpha, 0, 1);

disp("Results of Testing Misclosure")
means
meanVar
misclosure
misclosureSD
y_pop
Z

if abs(y_pop) < Z
    disp("Misclosure Test Passed");
else
    disp("Misclosure Test Failed");
end

end