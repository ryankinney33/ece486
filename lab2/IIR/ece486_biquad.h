/*
 * This file contains the declarations for the functions
 * and the structure to implement IIR filters for blocks
 * of input data.
 *
 * Contains the definition of the structure holding the
 * necessary information. There is a function for
 * initializing the structure, a function for using the
 * structure and an input array to calculate the filter
 * output, and a function for freeing the memory used
 * by the structure.
 *
 * Authors: Ryan Kinney, Jason Halliday, Devin Hoskins
 * ECE 486 - Spring 2021
 * March 14, 2021
 */

#ifndef _ECE486_BIQUAD_H_
#define _ECE486_BIQUAD_H_

/*
 * The typedef for the structure to implement IIR filters
 * as cascaded  biquadratic filters using the Transposed-
 * Direct-Form II structure. Contains information about
 * the number of samples for the input and output data,
 * a gain constant to multiply the input by, arrays for
 * the filter coefficients, and two variables to hold
 * necessary previous information. Also contains a pointer
 * to the next biquad filter in the cascaded sequence
 */
typedef struct BIQUAD_T{
	int blocksize;	// Number of samples for the input and output
	float g;		// Filter gain (the input is multiplied by this
	float v1;		// An intermediate value used for the output
	float v2;		// Another intermediate value used for the output

	float* a;		// The a-coefficients of the difference equation
	float* b;		// The b-coefficients of the difference equation

	struct BIQUAD_T* next_section; // The next filter in the sequence
} BIQUAD_T;

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
BIQUAD_T *init_biquad(int sections, float g, float *biquad_coefs, int blocksize);

/*
 * Calculate a block of output samples from a block of input samples
 * Works recursively to call itself on the next filter in the sequence
 * Arguments:
 *	BIQUAD_T *s	// Pointer to the filter structure created by init_biquad or modified by this function
 *	float *x	// Input data block (must be allocated by caller)
 *	float *y	// Output data block (must be allocated by caller)
 */
void calc_biquad(BIQUAD_T *s, float *x, float *y);

/*
 * Frees the memory reserved by the BIQUAD_T structure
 * Recursively frees the memory of all the subsequent biquad
 * filters in the sequence
 * Arguments:
 *	BIQUAD_T *s	// Pointer to the filter structure to be "destroyed"
 */
void destroy_biquad(BIQUAD_T *s);

#endif
