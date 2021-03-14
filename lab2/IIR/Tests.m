%% Information
% The purpose of this script is to verify the results from the main.c
% program used to test the correctness of the IIR filter implementation
%
% Authors: Jason Halliday, Devin Hoskins, Ryan Kinney
% ECE 486 - Spring 2021
% March 14, 2021

%% Test 1

% This test mimics the final question on homework 2

% Initialize data.....
blocksize = 20;
gain = single(0.01388599);
b1 = single([1,1.6180,1]);
a1 = single([1,-1.5371,0.9025]);
b2 = single([1,-0.6180,1]);
a2 = single([1,0,-0.81]);
x = [3.0,1.5,-1.8,0.2,zeros(1,blocksize-4)];

% get filter output
y = filter(b1,a1,gain*x); % first stage with x multiplied by gain
y = filter(b2,a2,y); % second stage

% print the results
fprintf('--Test 1--\n')
fprintf('Homework 2 #5\n')
fprintf(' x[n] = {'),print_array(x),fprintf('}\n')
fprintf(' y[n] = {'),print_array(y),fprintf('}\n\n')

%% Test 2

% This test is where the input x[n] is a sin wave
% The filter is the same in the previous section except the gain is changed

% Initialize data
blocksize = 20;
gain = single(0.5);
b1 = single([1,1.6180,1]);
a1 = single([1,-1.5371,0.9025]);
b2 = single([1,-0.6180,1]);
a2 = single([1,0,-0.81]);
x = sin(0:blocksize-1);

% get filter output
y = filter(b1,a1,gain*x); % stage 1
y = filter(b2,a2,y); % second stage

% print output
fprintf('--Test 2--\n')
fprintf('Sin(n) Input - Compared with MATLAB script\n')
fprintf(' x[n] = {'),print_array(x),fprintf('}\n')
fprintf(' y[n] = {'),print_array(y),fprintf('}\n\n')


%% Local function for printing the output
function print_array(array)
for i = array(1:end-1)
    fprintf('%f, ',i)
end
fprintf('%f',array(end))
end