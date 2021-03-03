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
#include <stdio.h>
 
 
 // Initializes the structure for the FIR filter
FIR_T* init_fir(float* fir_coefs, int n_coef, int blocksize){
	// first, create the required structure
	FIR_T* s;
	s = (FIR_T*)malloc(sizeof(FIR_T));
	if(s == NULL){
		printf("ERROR: Not enough memory to initialize FIR_T\n");
		while(1); // busy loop (used for STM microcontoller)
	}

	if(n_coef < 1){
		printf("ERROR: n_coef must be a positive integer\n");
	}
	// set the members of filter to the necessary values
	s->blocksize = blocksize;
	s->M = n_coef;
	
	// lastM holds past values of the input, newer samples have lower indices
	s->lastM = (float*)calloc(n_coef-1, sizeof(float));
	if(s->lastM == NULL){
		printf("ERROR: Could not initialize FIR_T.lastM\n");
		while(1); // busy loop (used for STM microcontoller)
	}

	// copy fir_coefs into filter.h
	for(int i = 0; i < s->M; ++i)
		s->h[i] = fir_coefs[i];
	
	return s;
}

// Calculate a block of output samples of the FIR from the input sample block
void calc_fir(FIR_T* s, float* x, float* y){
	// output y and output x have already been allocated and could point to the same location
	
	// iterates for each input sample
	for(int i = 0; i < s->blocksize; ++i){
		float tempY = x[i]*s->h[0]; // holds the temporary value for the output

		// iterates for each of the M impulse response terms
		for(int j = 1; j < s->M && s->M-1 > 0 ; ++j){
			tempY += s->lastM[j-1]*s->h[j]; 
		}
		
		// shift s->lastM to the right and insert x[i] at lastM[0]
		for(int k = s->M-2; i >= 1; --i){
			s->lastM[i] = s->lastM[i-1];
		}
		s->lastM[0] = x[i];
		
		// finally, save the output
		y[i] = tempY;
	}
	
}

// Frees the reserved memory from the FIR_T
void destroy_fir(FIR_T* s){
	free(s->h);
	free(s->lastM);
	free(s);
}