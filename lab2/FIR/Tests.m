%% Information
% The purpose of this script is to verify the results from the main.c
% program used to test the correctness of the FIR filter implementation
%
% Authors: Jason Halliday, Devin Hoskins, Ryan Kinney
% ECE 486 - Spring 2021
% March 14, 2021
%% Test 1

% Test 1 is when h[n] is the unit impulse
% This test is used to verify the validity of the C program

% first, create the data
blocksize1 = 10;
M1 = 5;
b1 = single([1,zeros(1,M1-1)]);
x1 = single(0:blocksize1-1);

% get the output from the filter
y1 = filter(b1,1,x1);

% print output
fprintf('Test 1: h[n] = unit impulse\n');
fprintf(' Discrete convolution results: h*x:\n');

fprintf('  x = {') % x1
for i = x1(1:end-1)
    fprintf('%f, ',i)
end
fprintf('%f}\n',x1(end))

fprintf('  y = {') % y1
for i = y1(1:end-1)
    fprintf('%f, ',i)
end
fprintf('%f}\n\n',y1(end))

%% Test 2

% h[n] is 0 before n = 0, 1 for n = 0,1,2, and 0 afterwards
% x[n] = u[n], the unit step function

blocksize2 = 10;
M2 = 10;
b2 = single([ones(1,3),zeros(1,M2-3)]);
x2 = ones(1,blocksize2);

% calculate the output
y2 = filter(b2,1,x2);

% print results
fprintf('Test 2: x[n] = u[n]\n');
fprintf('h[n] = {'); % b2
for i = b2(1:end-1)
    fprintf('%f, ',i)
end
fprintf('%f}\n',b2(end));
fprintf(' Discrete convolution results: h*x:\n');
fprintf('  x = {') % x2
for i = x2(1:end-1)
    fprintf('%f, ',i)
end
fprintf('%f}\n',x2(end))

fprintf('  y = {') % y2
for i = y2(1:end-1)
    fprintf('%f, ',i)
end
fprintf('%f}\n\n',y2(end))