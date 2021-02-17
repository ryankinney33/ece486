%% Test script for calc_running_mean.m
%
% Contains various test conditions to test the "correctness" of
% calc_running_mean.
%
% Authors: Ryan Kinney, Jason Halliday, Devin Hoskins
% ECE 486 - Lab 1
% February 17, 2021

%% Test 1
%
% A unit impulse function
% x[n] = u[n]
%
% This test is one test to make sure that calc_running_mean stays within
% vector bounds. First, let blocksize be larger than M. Also makes sure
% that s can be used in subsequent calculations.

% initialize data
blocksize = 15;
M = 10;
x = ones(1,blocksize);
s = init_running_mean(M,blocksize);

% calculate the running mean over input x a couple times times
[y,s] = calc_running_mean(x,s);
disp("First iteration of calc_running_mean:");
display(y);
disp("");
% y should gradually approach 1 and then stay 1 as the sample number increases
[y,s] = calc_running_mean(x,s);
disp("Second iteration of calc_running_mean:");
display(y);
disp("");
% at this point, y should be all 1's