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
	//  This first test makes sure calc_running_mean stays within array bounds
	//  First, let blocksize be larger than M. Also makes sure that s can be used
	//  in subsequent calculations.

	// initializing data...
	int blocksize = 15;
	int M = 10;

	float x1[blocksize];
	float y1[blocksize];
	for(int i = 0; i < blocksize; ++i) {
		x1[i] = 1.0f;
	}
	struct run_mean s1 = init_running_mean(M,blocksize);

	// print some info about the test
	printf("Test 1: x[n] = u[n]; M = %d; blocksize = %d\n",M,blocksize);

	// calculate the running mean over input x1 a couple times

	// first iteration
	calc_running_mean(x1,&s1,y1);
	printf("First iteration of calc_running_mean...\ny = [");
	print_array(y1,blocksize);
	printf("]\n");
	// y1 should gradually approach 1 and then stay 1 as the sample number increases

	// second iteration
	calc_running_mean(x1,&s1,y1);
	printf("Second iteration of calc_running_mean...\ny = [");
	print_array(y1,blocksize);
	printf("]\n\n");
	// at this point, y1 should be all 1's

	// clean up
	terminate_running_mean(&s1);

	return 0;
}

void print_array(float* arr, int size){
	for(int i = 0; i < size-1; ++i){
		printf("%lf, ",arr[i]);
	}
	printf("%lf",arr[size-1]);
}
