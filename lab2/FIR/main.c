/*
 * Test script for ece486_fir
 *
 * Contains some test conditions to test if
 * the interface and implementation of FIR filters
 * in ece486_fir.h and ece486_fir.c works correctly
 *
 * Authors: Jason Halliday, Ryan Kinney, Devin Hoskins
 * ECE 486 - Lab 2
 * March 6, 2021
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "ece486_fir.h"




// Runs through the test cases
int main(){
	// Test Condition 1
	//
	// Unit Impulse
	//	h[n] = delta(n), where delta = 1 at n = 0, and delta = 0 otherwise
	//
	// This test makes sure that the functions stay within array bounds
	//
	// A simple test to make sure the convolution works correctly.
	// Basically, if a signal is convolved with the unit impulse, or dirac delta function
	// the resultant signal should be identical to the input signal
	//	y[n] = x[n]*delta[n] = x[n]

	// Initializing the data...

	// Things needed for the structure are blocksize and the number of terms in the FIR
	int blocksize = 10;
	int M = 5;

	// Now supply the filter coefficients (AKA, the impulse response terms)
	float* b = (float*)calloc(M,sizeof(float));
	if(b==NULL){
		printf("Error: Could not reserve memory for b\n");
		exit(1);
	}
	b[0] = 1; // b should be zero at all points except at n = 0

	// Create the filter structure
	FIR_T* filt = init_fir(b,M,blocksize);

	// Now create the input and output arrays
	float* x = (float*)malloc(blocksize*sizeof(float));
	if(x==NULL){
		printf("Error: Could not reserve memory for x\n");
		exit(1);
	}
	float* y = (float*)malloc(blocksize*sizeof(float));
	if(y==NULL){
		printf("Error: Could not reserve memory for y\n");
		exit(1);
	}

	// Make up some data for x, suppose x[n] = n
	for(int i = 0; i<blocksize; ++i)
		x[i] = i;

	// Calculate output and print test results.
	calc_fir(filt,x,y);

	for(int i=0; i<blocksize; ++i){
		printf("x[%d] = %lf\ty[%d]=%lf\n",i,x[i],i,y[i]);
	}

	// finally, free the reserved memory
	free(b);
	free(x);
	free(y);
	destroy_fir(filt);

	exit(0);
}
