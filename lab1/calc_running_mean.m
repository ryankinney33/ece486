function [y,s] = calc_running_mean(x,s)
%CALC_RUNNING_MEAN Running average of input samples
%   [y,s] = calc_running_mean(x,s) takes a vector x of blocksize input
%   samples and calculates the running average over s.M input samples.
%   Structure s contains the information needed for the calculations.

% Author: Ryan Kinney
% ECE 486 - Lab 1
% February 15, 2021

% start by initializing the output block
y = zeros(1,s.blocksize);

% field s.lastM contains the previous M-1 samples used for the running mean
for i = 1:s.blocksize
    % get the lower_bound for samples to add from the current input
    lower_bound = i - s.M+1;
    if lower_bound < 1
        lower_bound = 1;
    end
    
    % add and average the samples from the current input and past inputs
    y(i) = sum(x(lower_bound:i));
    y(i) = (y(i)+sum(s.lastM(i:end)))/s.M;
end

% save the current input samples in s.lastM
if (s.M > s.blocksize)
    % need to shift the elements of s.lastM blocksize times to the left
    s.lastM = circshift(s.lastM,[0,-s.blocksize]);
end

% bound checking
Mlowbound = s.M-s.blocksize;
if(Mlowbound < 1)
   Mlowbound = 1; 
end
Xlowbound = s.blocksize-(s.M-1)+1;
if(Xlowbound < 1)
   Xlowbound = 1; 
end

% add the new samples to s.lastM
s.lastM(Mlowbound:end) = x(Xlowbound:end);
end