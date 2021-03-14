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
blocksize = 10;
M = 5;
b = single([1,zeros(1,M-1)]);
x = single(0:blocksize-1);

% get the output from the filter
y = filter(b,1,x);

% print output
fprintf('Test 1: h[n] = unit impulse\n');
fprintf(' Discrete convolution results: h*x:\n');

fprintf('  x = {'),print_array(x),fprintf('}\n')
fprintf('  y = {'),print_array(y),fprintf('}\n\n')

%% Test 2

% h[n] is 0 before n = 0, 1 for n = 0,1,2, and 0 afterwards
% x[n] = u[n], the unit step function

blocksize = 10;
M = 10;
b = single([ones(1,3),zeros(1,M-3)]);
x = ones(1,blocksize);

% calculate the output
y = filter(b,1,x);

% print results
fprintf('Test 2: x[n] = u[n]\n');
fprintf('h[n] = {'),print_array(b),fprintf('}\n')
fprintf(' Discrete convolution results: h*x:\n');
fprintf('  x = {'),print_array(x),fprintf('}\n')
fprintf('  y = {'),print_array(y),fprintf('}\n\n')

%% Local function for printing the output
function print_array(array)
for i = array(1:end-1)
    fprintf('%f, ',i)
end
fprintf('%f',array(end))
end