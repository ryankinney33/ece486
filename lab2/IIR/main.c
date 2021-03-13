/*
 * Test script for ece486_biquad
 *
 * Contains some test conditions to test if the
 * interface and implementation of biquad filters
 * in ece486_biquad.c and ece486_biquad.h works correctly
 *
 * Authors: Devin Hoskins, Ryan Kinney, Jason Halliday
 * ECE 486 - Lab 2
 * March 8, 2021
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ece486_biquad.h"


// prints an array on one line, each element separated by ', '
void print_array(float* arr, int size);

// Runs through the test cases
int main(){
	// Test 1
	// this one is basically the final question on homework 2

	// Initialize data.....
	int blocksize = 20;
	int sections = 2;
	float gain = 0.01388599;
	float filter_coef[] = {1,1.6180,1,-1.5371,0.9025,1,-0.6180,1,0,-0.81};

	BIQUAD_T* filter = init_biquad(sections,gain,filter_coef,blocksize);
	if(filter == NULL){ // check for a memory allocation error
		printf("Error: Could not reserve memory for filter\n");
		exit(1);
	}

	// make the input and output data
	float* x = (float*)calloc(blocksize,sizeof(float));
	if(x == NULL){
		printf("Error: Could not reserve memory for x\n");
		exit(1);
	}
	float* y = (float*)malloc(blocksize*sizeof(float));
	if(y == NULL){
		printf("Error: Could not reserve memory for y\n");
		exit(1);
	}
	x[0] = 3.0f;
	x[1] = 1.5f;
	x[2] = -1.8f;
	x[3] = 0.2f;

	calc_biquad(filter,x,y);

	printf("--TEST 1--\n");
	printf("HW2 #5 - Comparing values with MATLAB script\n");
	printf("  x[n] = {"); print_array(x,blocksize); printf("}\n");
	printf("  y[n] = {"); print_array(y,blocksize); printf("}\n\n");

	// cleanup
	//free(x); // x and y are reused
	//free(y);
	destroy_biquad(filter);

	//Test 2 - Sine wave input
	//Initialize test conditions
	// blocksize, and sections are the same as in the previous test
	gain = 0.5f;
	BIQUAD_T* filter2 = init_biquad(sections,gain,filter_coef,blocksize);
	if(filter2 == NULL){
		printf("Error: Could not reserve memory for filter2\n");
		exit(1);
	}

	//Define input x[n] = sin[n]
	for(int i = 0; i < blocksize; i++) {
		x[i] = sin(i);
	}

	calc_biquad(filter2,x,y);

	printf("--TEST 2--\n");
	printf("Sin(n) Input - Compared with MATLAB script\n");
	printf("  x[n] = {"); print_array(x,blocksize); printf("}\n");
	printf("  y[n] = {"); print_array(y,blocksize); printf("}\n\n");


	// cleanup
	free(x);
	free(y);
	destroy_biquad(filter2);

	//Test 3 - Testing filter function over multiple calls
	//Initialize test conditions
	
//	BIQUAD_T* filter3 = init_biquad(sections,gain,filter_coef,blocksize);
	
//	blocksize = 10;
//	sections = 2;
//	gain = 1;
	
//	for(int i = 0; i < 20; i++) {
//		x[i] = sin(i);
//	}

//	calc_biquad(filter3,x,y);

//	printf("--TEST 3--\n");
//	printf("Sin(n) Input - Compared with MATLAB script\n");
//	printf("  x[n] = {"); print_array(x,blocksize); printf("}\n");
//	printf("  y[n] = {"); print_array(y,blocksize); printf("}\n\n");


	// cleanup
//	free(x);
//	free(y);
//	destroy_biquad(filter3);


}

// prints an array on one line, each element separated by ', '
void print_array(float* arr, int size){
	if(size > 0){
	int i;
	for(i = 0; i < size-1; ++i)
		printf("%0.5lf, ",arr[i]);
		printf("%0.5lf",arr[i]);
	}
}
