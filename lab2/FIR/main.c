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

// prints an array on one line, each element separated by ', '
void print_array(float* arr, int size);

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
	int blocksize1 = 10;
	int M1 = 5;

	// Now supply the filter coefficients (AKA, the impulse response terms)
	float* b1 = (float*)calloc(M1,sizeof(float));
	if(b1==NULL){
		printf("Error: Could not reserve memory for b1\n");
		exit(1);
	}
	b1[0] = 1; // b1 should be zero at all points except at n = 0

	// Create the filter structure
	FIR_T* filt1 = init_fir(b1,M1,blocksize1);

	// Now create the input and output arrays
	float* x1 = (float*)malloc(blocksize1*sizeof(float));
	if(x1==NULL){
		printf("Error: Could not reserve memory for x1\n");
		exit(1);
	}
	float* y1 = (float*)malloc(blocksize1*sizeof(float));
	if(y1==NULL){
		printf("Error: Could not reserve memory for y1\n");
		exit(1);
	}

	// Make up some data for x1, suppose x1[n] = n
	for(int i = 0; i<blocksize1; ++i)
		x1[i] = i;

	// Calculate output and print test results.
	calc_fir(filt1,x1,y1);

	printf("Test 1: h[n] = unit impulse; x[n] = n; M = %d; blocksize = %d\n",M1,blocksize1);
	printf(" First iteration of calc_fir, which performs discrete convolution, h*x:\n");
	printf("  x[n] = {"); print_array(x1,blocksize1); printf("}\n");
	printf("  y[n] = {"); print_array(y1,blocksize1); printf("}\n\n");

	// finally, free the reserved memory
	free(b1);
	free(x1);
	free(y1);
	destroy_fir(filt1);
	// end Test 1

	/////////////////////////////////////////////////////////////////////////////
	// Test Condition 2
	//
	// 	h[n] is 0 before n = 0, 1 for n = 0,1,2, and 0 afterwards
	//	x[n] = u[n], the unit step function
	//
	// This test verifies that M can be less than blocksize and that the convolution
	// is correctly calculated. Also makes sure that the interface can be used in
	// subsequent calculations
	//
	// Another simple test to make sure the convolution works correctly.
	// With the current combination of x and h, output y should start at 1 and
	// increase by 1 until it is 3, and then it will stay at 3
	//

	// Initializing the data...

	// Things needed for the structure are blocksize and the number of terms in the FIR
	int blocksize2 = 5;
	int M2 = 10;

	// Now supply the filter coefficients (AKA, the impulse response terms)
	float* b2 = (float*)calloc(M2,sizeof(float));
	if(b2==NULL){
		printf("Error: Could not reserve memory for b2\n");
		exit(1);
	}
	b2[0] = 1; // b2 should be zero at all points except at n = 0,1,2
	b2[1] = 1; // b2 should be zero at all points except at n = 0,1,2
	b2[2] = 1; // b2 should be zero at all points except at n = 0,1,2

	// Create the filter structure
	FIR_T* filt2 = init_fir(b2,M2,blocksize2);

	// Now create the input and output arrays
	float* x2 = (float*)malloc(blocksize2*sizeof(float));
	if(x2==NULL){
		printf("Error: Could not reserve memory for x2\n");
		exit(1);
	}
	float* y2 = (float*)malloc(blocksize2*sizeof(float));
	if(y2==NULL){
		printf("Error: Could not reserve memory for y2\n");
		exit(1);
	}

	// Create the unit step for x2
	for(int i = 0; i<blocksize2; ++i)
		x2[i] = 1;

	// Calculate output and print test results.
	calc_fir(filt2,x2,y2);

	printf("Test 2: x[n] = u[n]; M = %d; blocksize = %d\n",M2,blocksize2);
	printf("h[n] = {"); print_array(b2,M2); printf("}\n");
	printf(" First iteration of calc_fir, which performs discrete convolution, h*x:\n");
	printf("  x[n] = {"); print_array(x2,blocksize2); printf("}\n");
	printf("  y[n] = {"); print_array(y2,blocksize2); printf("}\n");

	// run the convolution again
	calc_fir(filt2,x2,y2);
	printf(" Second iteration of calc_fir, which performs discrete convolution, h*x:\n");
	printf("  x[n] = {"); print_array(x2,blocksize2); printf("}\n");
	printf("  y[n] = {"); print_array(y2,blocksize2); printf("}\n\n");

	// finally, free the reserved memory
	free(b2);
	free(x2);
	free(y2);
	destroy_fir(filt2);


	exit(0);
}

// prints an array on one line, each element separated by ', '
void print_array(float* arr, int size){
	if(size > 0){
		int i;
		for(i = 0; i < size-1; ++i)
			printf("%lf, ",arr[i]);
		printf("%lf",arr[i]);
	}
}
