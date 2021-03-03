/*
 * The purpose of this program is to implement
 * discrete time convolution for the FIR filter
 * interface described in ece486_fir.h
 * 
 * Contains the function defitions for initializing
 * the structure, calculating the convolution, and
 * freeing memory reserved by the structure.
 * 
 * Authors: Ryan Kinney, Devin Hoskins, Jason Halliday
 * ECE 486 - Lab 2
 * March 3, 2021
 */
 
#include "ece486_fir.h"
#include <stdlib.h>
 
 
 // Initializes the structure for the FIR filter
FIR_T* init_fir(float* fir_coefs, int n_coef, int blocksize){
	// first, create the required structure
	FIR_T* filter;
	filter = (FIR_T*)malloc(sizeof(FIR_T));
	if(filter == NULL){
		printf("ERROR: Not enough memory to initialize FIR_T\n");
		while(1); // busy loop (used for STM microcontoller)
	}
	
	// set the members of filter to the necessary values
	filter->blocksize = blocksize;
	filter->M = n_coef;
	
	filter->lastM = (float*)calloc(n_coef-1, sizeof(float));
	if(filter->lastM == NULL){
		printf("ERROR: Not enough memory to initialize FIR_T.lastM\n");
		while(1); // busy loop (used for STM microcontoller)
	}

	// copy fir_coefs into filter.h
	memcpy(filter->h, fir_coefs, n_coef);
	
	return filter;
}

// Calculate a block of output samples of the FIR from the input sample block
void calc_fir(FIR_T* s, float* x, float* y){
	
	
	
	
}

// Frees the reserved memory from the FIR_T
void destroy_fir(FIR_T* s){
	free(s->h);
	free(s->lastM);
	free(s);
}