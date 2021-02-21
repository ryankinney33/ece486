#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "running_mean.h"

// Used for a test case
#define _PI 3.14159265358979323846

// This function iterates through a float array
// and prints each value on one line with a space
// and comma between them
void print_array(float* arr, int size);

// Runs through the test cases to check the validity of
// the running mean filter.
int main(){
	//  Test 1
	//
	//  Unit Step
	//	x[n] = u[n]
	//
	//  This first test makes sure calc_running_mean stays within array bounds.
	//  First, let blocksize be larger than M. Also makes sure that s can be used
	//  in subsequent calculations.

	// initializing data...
	int blocksize = 15;
	int M = 10;

	float x[blocksize];
	float y[blocksize];
	for(int i = 0; i < blocksize; ++i) {
		x[i] = 1.0f;
	}
	struct running_mean s = init_running_mean(M,blocksize);

	// print some info about the test
	printf("Test 1: x[n] = u[n]; M = %d; blocksize = %d\n",M,blocksize);

	// calculate the running mean over input x a couple times

	// first iteration
	calc_running_mean(x,&s,y);
	printf("First iteration of calc_running_mean...\ny = [");
	print_array(y,blocksize);
	printf("]\n");
	// y should gradually approach 1 and then stay 1 as the sample number increases

	// second iteration
	calc_running_mean(x,&s,y);
	printf("Second iteration of calc_running_mean...\ny = [");
	print_array(y,blocksize);
	printf("]\n\n");
	// at this point, y should be 1 at every index

	// clean up
	terminate_running_mean(&s);
	// end Test 1

	//////////////////////////////////////////////////////
	//  Test 2
	//
	//  Unit Step (again)
	//  x[n] = u[n]
	//
	//  Another test to make sure that calc_running_mean stays within array bounds.
	//  Tests if M can be larger than blocksize

	// initializing data...
	// blocksize = 15 already
	M = 20;
	// reusing x and y arrays
	s = init_running_mean(M,blocksize);

	printf("Test 2: x[n] = u[n]; M = %d; blocksize = %d\n",M,blocksize);

	// calculate the running mean over input x a couple times

	// first iteration
	calc_running_mean(x,&s,y);
	printf("First iteration of calc_running_mean...\ny = [");
	print_array(y,blocksize);
	printf("]\n");
	// y should gradually approach 1 then stay 1 as teh sample number increases

	// second iteration
	calc_running_mean(x,&s,y);
	printf("Second iteration of calc_running_mean...\ny = [");
	print_array(y,blocksize);
	printf("]\n\n");
	// at this point, y should be 1 at every index

	// clean up
	terminate_running_mean(&s);
	// end Test 2

	//////////////////////////////////////////////////////
	//  Test 3
	//
	//  Two sin waves of different frequencies
	//  x1[n] is a 1 Hz sin wave
	//  x2[n] is a 100 Hz sin wave
	//
	//  This test is to evaluate the low-pass characteristic
	//  of the running mean filter. This will be done by
	//  comparing a low frequency sin wave and a high
	//  frequency one

	// initializing data
	blocksize = 1000;
	M = 10;
	struct running_mean s1 = init_running_mean(M,blocksize);
	struct running_mean s2 = init_running_mean(M,blocksize);
	float y1[blocksize], y2[blocksize], x1[blocksize], x2[blocksize];

	// build the sine waves
	for(int i = 0; i < blocksize; ++i){
		float sampleN = 6*_PI*(float)i/(float)blocksize;
		x1[i] = sin(2*_PI*sampleN);
		x2[i] = sin(200*_PI*sampleN);
	}

	// run the inputs through the filters
	calc_running_mean(x1,&s1,y1);
	calc_running_mean(x2,&s2,y2);

	// get the results
	float max1 = y1[0], max2 = y2[0]; // find the maximum values for y1 and y2
	for(int i = 1; i < blocksize; ++i){
		if(y1[i] > max1)
			max1 = y1[i];

		if(y2[i] > max2)
			max2 = y2[i];
	}

	// finally, print the results
	printf("Test 3: Two different frequency sine waves.\n");
	printf("x1[n] is a 1 Hz sine wave\nx2[n] is a 100 Hz sine wave.\n");
	printf("M = %d and blocksize = %d\n",M,blocksize);

	printf("The maximum value of the unfiltered input is 1.\n");
	printf("Maximum of y1[n] is %lf\n", max1);
	printf("Maximum of y2[n] is %lf\n", max2);
	printf("The maximum of y2 should be much less than that of y1.\n");

	// cleaning up...
	terminate_running_mean(&s1);
	terminate_running_mean(&s2);
	// end Test 3

	return 0;
}

// This function iterates through a float array
// and prints each value on one line with a space
// and comma between them
void print_array(float* arr, int size){
	for(int i = 0; i < size-1; ++i){
		printf("%0.3lf, ",arr[i]);
	}
	// don't put a comma after the last value
	printf("%0.3lf",arr[size-1]);
}
