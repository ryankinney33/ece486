/*
 * Real time implementation of FIR filters
 *
 * Uses the ECE486 interface and the C FIR
 * filter implementation to filter an input
 * on the primary ADC. The filter output is
 * streamed to the primary DAC output. The
 * input is also copied to the secondary DAC.
 *
 * Authors: Ryan Kinney, Jason Halliday, Devin Hoskins
 * ECE 486 - Lab 2
 * March 13, 2021
 *
 */

#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"

#include "ece486.h"
#include "ece486_fir.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void){
	int nsamp, ncoef;
	float *input, *output, *filtcoef;
	FIR_T* filt;
	// Set up ADCs, DACs, GPIO, Clocks, DMSa, and Timer
	// Uses the MSI (Medium Speed internal) reference (the on-chip oscillator)
	initialize_ece486(FS_48K, MONO_IN, STEREO_OUT, MSI_INTERNAL_RC);

	// Allocate Required Memory
	nsamp = getblocksize();
	ncoef = 20;
	input = (float*)malloc(nsamp*sizeof(float));
	output = (float*)malloc(nsamp*sizeof(float));
	filtcoef = (float*)calloc(ncoef,sizeof(float));

	if(input == NULL || output == NULL || filtcoef == NULL){
		flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	// Set the filter coefficients
	filtcoef[0] = 1.0f; // If h[n] = 1 only at n = 0, then the input and output should be the same

	// Create the filter structure
	filt = init_fir(filtcoef, ncoef, nsamp);

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
		calc_fir(filt, input, output);
		DIGITAL_IO_RESET(); // falling edge; done processing data

		// send the data to the output DAC
		putblockstereo(output,input);
	}
}
