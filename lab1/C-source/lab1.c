#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "running_mean.h"

void print_array(float* arr, int size);

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
	struct run_mean s = init_running_mean(M,blocksize);

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

	return 0;
}

void print_array(float* arr, int size){
	for(int i = 0; i < size-1; ++i){
		printf("%0.3lf, ",arr[i]);
	}
	printf("%0.3lf",arr[size-1]);
}
