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
% A unit step function
% x1[n] = u[n]
%
% This test is one test to make sure that calc_running_mean stays within
% vector bounds. First, let blocksize be larger than M. Also makes sure
% that s can be used in subsequent calculations.

disp("Test 1: x[n] = u[n]; M = 10; blocksize = 15")

% initialize data
blocksize = 15;
M = 10;
x1 = ones(1,blocksize);
s1 = init_running_mean(M,blocksize);

% calculate the running mean over input x1 a couple times
[y1,s1] = calc_running_mean(x1,s1);
disp("First iteration of calc_running_mean:");
display(y1);
fprintf("\n");
% y should gradually approach 1 and then stay 1 as the sample number increases
[y1,s1] = calc_running_mean(x1,s1);
disp("Second iteration of calc_running_mean:");
display(y1);
fprintf("\n")
% at this point, y should be all 1's

%% Test 2
%
% Two sine waves of different frequencies
% x2a[n] = sin(x)
% x2b[n] = sin(100*x)
%
% This test is to evaluate the low-pass characteristics of the
% calc_running_mean function. This will be done by comparing a low
% frequency sine wave with a high frequency sine wave

% initialize data
blocksize = 1000;
M = 10;
s2a = init_running_mean(M,blocksize);
s2b = init_running_mean(M,blocksize);

% establish high and low frequency sine functions
n = linspace(0,6*pi,blocksize);
x2a = sin(2*pi*1*n);
x2b = sin(2*pi*100*n); 

% calculate the running mean over inputs x2a and x2b
[y2a,s2a] = calc_running_mean(x2a,s2a);
[y2b,s2b] = calc_running_mean(x2b,s2b);
t = 1:blocksize;

% Low frequency comparison
% Unfiltered input
figure(1)
tiledlayout(2,1)
nexttile
plot(t,x2a);
title('Unfiltered Input: Freq = 1Hz')

% Filtered output
nexttile
plot(t,y2a);
title('Filtered Output: Freq = 1Hz')

% High frequency comparison
% Unfiltered input
figure(2)   
tiledlayout(2,1)
nexttile
plot(t(100:end),x2b(100:end));
title('Unfiltered Input: Freq = 100Hz')

% filtered output
nexttile
plot(t(100:end),y2b(100:end));
set(gca, 'ylim', [-1 1]);
title('Filtered Output: Freq = 100Hz')

%% Test 3
%
% Another unit step 
% x3[n] = u[n]
%
% Another test to make sure that calc_running_mean stays within vector
% bounds. Tests if M can be larger than blocksize

disp("Test 3: x[n] = u[n]; M = 20; blocksize = 15")

M = 20;
blocksize = 15;
x3 = ones(1,blocksize);
s3 = init_running_mean(M,blocksize);

% calculate the running mean over input x3 a few times
[y3,s3] = calc_running_mean(x3,s3);
disp("First iteration of calc_running_mean:");
display(y3);
fprintf("\n");
% y should gradually approach 1 and then stay 1 as the sample number increases
[y3,s3] = calc_running_mean(x3,s3);
disp("Second iteration of calc_running_mean:");
display(y3);
fprintf("\n")
% at this point, y should be all 1's











