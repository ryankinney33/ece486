function [y,s] = calc_running_mean(x,s)
%CALC_RUNNING_MEAN Running average of input samples
%   [y,s] = calc_running_mean(x,s) takes a vector x of blocksize input
%   samples and calculates the running average over s.M input samples.
%   Structure s contains the information needed for the calculations.
%   Returns the output signal y, which holds blocksize samples, and also
%   returns the structure s for future calculations of the running mean.

% Author: Ryan Kinney, Jason Halliday, and Devin Hoskins
% ECE 486 - Lab 1
% February 17, 2021

% start by initializing the output block
y = zeros(1,s.blocksize);

% field s.lastM contains the previous M-1 samples used for the running mean
for i = 1:s.blocksize
    % find the average of the previous M-1 samples and the current input
    y(i) = (sum(s.lastM)+x(i))/s.M;
    
    % shift the values in s.lastM one to the left and put the current input
    % at the end
    s.lastM = circshift(s.lastM,[0,-1]);
    s.lastM(end) = x(i);
end