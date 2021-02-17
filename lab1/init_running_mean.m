function s = init_running_mean(M,blocksize)
%INIT_RUNNING_MEAN Initializes the structure for calculating the running average of a signal.
%   s = init_running_mean(M,blocksize) takes sample size M and a value for
%   the blocksize to initialize a structure for calculating the running
%   mean of the input signal. The structure contains the necessary
%   information to perform the calculations.

% Author: Ryan Kinney, Jason Halliday, and Devin Hoskins
% ECE 486 - Lab 1
% February 17, 2021

% Initialize the structure
s = struct('M',M,'blocksize',blocksize,'lastM', zeros(1,M-1));
end