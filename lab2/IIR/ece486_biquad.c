/*
 * This file contains the definitions for the functions
 * to implement IIR filters for blocks of input data.
 *
 * Contains the definition of the function for
 * initializing the structure, the function for using the
 * structure and an input array to calculate the filter
 * output, and a function for freeing the memory used
 * by the structure.
 *
 * Authors: Ryan Kinney, Jason Halliday, Devin Hoskins
 * ECE 486 - Spring 2021
 * March 14, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "ece486_biquad.h"

/*
 * Recursively initializes the cascaded biquad filter structure.
 * Arguments:
 *	int sections	// The number of biquad filters in the sequence
 *	float g		// The gain constant to multiply the input by (first section only)
 *	float *biquad_coefs
 *		// This is the array of biquad coefficients. It must be allocated by the caller
 *		// And has the form of {b10, b11, b12, a11, a12, b20, b21, b22, a21, a22, . . . bs0, bs1, bs2, as1, as2}
 *		// The size of this array should be 5*sections
 *	int blocksize	// The number of sample for input and output
 */
BIQUAD_T *init_biquad(int sections, float g, float *biquad_coefs, int blocksize){
	if(sections < 1){ // if there are no sections in the filter, then what are you doing?
		return NULL;
	}

	// start by creating the structure
	BIQUAD_T* s;
	s = (BIQUAD_T*)malloc(sizeof(BIQUAD_T));
	if(s == NULL){
		printf("Error: Unable to initialize BIQUAD_T\n");
		return NULL;
	}

	// assign the necessary values
	s->blocksize = blocksize;
	s->g = g;
	s->v1 = 0;
	s->v2 = 0;

	// allocate memory for the arrays
	s->a = (float*)malloc(2*sizeof(float));
	if(s->a == NULL){
		printf("Error: Unable to initialize BIQUAD_T.a\n");
		destroy_biquad(s);
		return NULL;
	}

	s->b = (float*)malloc(3*sizeof(float));
	if(s->b == NULL){
		printf("Error: Unable to initialize BIQUAD_T.b\n");
		destroy_biquad(s);
		return NULL;
	}

	// now set the coefficients in s->a and s->b with biquad_coefs array
	// biquad_coefs looks like the following....
	// biquad_coefs =
	//   {b10, b11, b12, a11, a12, b20, b21, b22, a21, a22, . . . bs0, bs1, bs2, as1, as2}
	s->b[0]=biquad_coefs[0];
	s->b[1]=biquad_coefs[1];
	s->b[2]=biquad_coefs[2];

	s->a[0]=biquad_coefs[3];
	s->a[1]=biquad_coefs[4];

	// only thing left is to create the next section (if applicable)
	if(sections > 1){
		s->next_section = init_biquad(sections-1,1.0f,biquad_coefs+5,blocksize);
		if(s->next_section == NULL){ // there was a memory allocation error
			destroy_biquad(s);
			return NULL;
		}
	}else{
		// this is the final section, next_section should be null
		s->next_section = NULL;
	}
	return s;
}

/*
 * Calculate a block of output samples from a block of input samples
 * Works recursively to call itself on the next filter in the sequence
 * Arguments:
 *	BIQUAD_T *s	// Pointer to the filter structure created by init_biquad or modified by this function
 *	float *x	// Input data block (must be allocated by caller)
 *	float *y	// Output data block (must be allocated by caller)
 */
void calc_biquad(BIQUAD_T *s, float *x, float *y){
	// check if this is a valid structure (the exit condition for recursion)
	if(s == NULL){
		return;
	}

	// uses the Transposed Direct-Form II structure
	//  (1) - y[n] = v1[n-1]+b0*x[n]
	//  (2) - v1[n] = v2[n-1]-a1*y[n]+b1*x[n]
	//  (3) - v2[n] = b2*x[n]-a2*y[n]

	// output and input are s->blocksize large, so iterate over that first

	// note: x and y could point to the same place
	for(int i = 0; i < s->blocksize; ++i){
		// multiply by the gain
		float t_x = s->g*x[i]; // also saves x[i] in a temp variable in case x==y

		// evaluate equation (1)
		y[i] = s->v1+ s->b[0]*t_x;

		// evaluate equation (2)
		s->v1 = s->v2- s->a[0]*y[i]+ s->b[1]*t_x;

		// evaluate equation (3)
		s->v2 = s->b[2]*t_x - s->a[1]*y[i];
	}

	// evaluate the output for the next filter
	// the input for the next filter is the output from this filter
	// the output from the filters should all go into y
	calc_biquad(s->next_section,y,y);
}


/*
 * Frees the memory reserved by the BIQUAD_T structure
 * Recursively frees the memory of all the subsequent biquad
 * filters in the sequence
 * Arguments:
 *	BIQUAD_T *s	// Pointer to the filter structure to be "destroyed"
 */
void destroy_biquad(BIQUAD_T *s){
	if(s){ // same as s != NULL
		// start by freeing the arrays
		if(s->a)
			free(s->a);
		if(s->b)
			free(s->b);

		// destroy the next section
		destroy_biquad(s->next_section);

		// all the next sections are gone, s can be freed now
		free(s);
	}
}
