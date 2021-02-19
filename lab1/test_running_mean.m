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

% calculate the running mean over input x a couple times
[y,s] = calc_running_mean(x,s);
disp("First iteration of calc_running_mean:");
display(y);
disp("");
% y should gradually approach 1 and then stay 1 as the sample number increases
[y,s] = calc_running_mean(x,s); %#ok<ASGLU> <- suppresses a warning
disp("Second iteration of calc_running_mean:");
display(y);
disp("");
% at this point, y should be all 1's

%% Test 2
%
% Two sine waves of different frequencies
% x1[n] = sin(x)
% x2[n] = sin(100*x)
%
%
% This test is to evaluate the low-pass characteristics of the
% calc_running_mean function. This will be done by comparing a low
% frequency sine wave with a high frequency sine wave

% initialize data
blocksize = 1000;
M = 10;
s = init_running_mean(M,blocksize);

% establish high and low frequency sine functions
n = linspace(0,6*pi,blocksize);
x1 = sin(2*pi*1*n);
x2 = sin(2*pi*100*n); 

% calculate the running mean over inputs x1 and x2
[y1,s] = calc_running_mean(x1,s);
[y2,s] = calc_running_mean(x2,s);
t = 1:blocksize;

% Low frequency comparison
% Unfiltered input
figure(1)
tiledlayout(2,1)
nexttile
plot(t,x1);
title('Unfiltered Input: Freq = 1Hz')

% Filtered output
nexttile
plot(t,y1);
title('Filtered Output: Freq = 1Hz')

% High frequency comparison
% Unfiltered input
figure(2)   
tiledlayout(2,1)
nexttile
plot(t(100:end),x2(100:end));
title('Unfiltered Input: Freq = 100Hz')

% filtered output
nexttile
plot(t(100:end),y2(100:end));
set(gca, 'ylim', [-1 1]);
title('Filtered Output: Freq = 100Hz')

