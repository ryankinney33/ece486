/*
 * Real time implementation of IIR filters
 *
 * Uses the ECE486 interface and the C biquad
 * filter implementation to filter an input
 * on the primary ADC. The filter output is
 * streamed to the primary DAC output. The
 * input is also copied to the secondary DAC.
 *
 * Authors: Ryan Kinney, Jason Halliday, Devin Hoskins
 * ECE 486 - Lab 2
 * March 14, 2021
 *
 */

#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"

#include "ece486.h"
#include "ece486_biquad.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void){
	int nsamp, sections;
	float *input, *output, *filtcoef, gain;
	BIQUAD_T* filt;
	// Set up ADCs, DACs, GPIO, Clocks, DMSa, and Timer
	// Uses the MSI (Medium Speed internal) reference (the on-chip oscillator)
	initialize_ece486(FS_48K, MONO_IN, STEREO_OUT, MSI_INTERNAL_RC);

	// Allocate Required Memory
	nsamp = getblocksize();
	sections = 3;
	gain = 1.0f;
	input = (float*)malloc(nsamp*sizeof(float));
	output = (float*)malloc(nsamp*sizeof(float));
	filtcoef = (float*)calloc(5*sections,sizeof(float));

	// Check for errors
	if(input == NULL || output == NULL || filtcoef == NULL){
		flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	// Set the filter coefficients
	for(int i = 0; i < sections; ++i){
		filtcoef[i*5] = 1.0f;
	}
	// Now, for the filter coefficients, b0 for each section should be 1
	// all other coefficients should be 0, causing y[n] = x[n]

	// Create the filter structure
	filt = init_biquad(sections, gain, filtcoef, nsamp);

	// Check for errors
	if(filt == NULL){
		flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	// print information about the program
	printf("Starting execution using %d samples per input block.\r\n",nsamp);

	// Infinite loop to process the data stream, "nsamp" samples at a time
	while(1){
		// get a block of input samples
		getblock(input);

		// process the input
		DIGITAL_IO_SET(); // use a scope on PD0 to measure execution time
		calc_biquad(filt, input, output);
		DIGITAL_IO_RESET(); // falling edge; done processing data

		// send the data to the output DAC
		putblockstereo(output,input);
	}
}
