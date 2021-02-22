/*
 * The purpose of this program is to calculate the running average
 * of an array.
 *
 * Contains the function definitions for initializing the running_mean structure,
 * calculating the running mean, and clearing memory reserved by the structure
 *
 * Authors: Ryan Kinney, Devin Hoskins, Jason Halliday
 * ECE 486 - Lab 1
 * February 21, 2021
 */

#include <stdlib.h>
#include <stdio.h>

#include "running_mean.h"


// Initializes the structure for calculating the running mean
// Argument M is the number of samples to calculate the average over
// Argument blocksize is the size of the input and output
struct running_mean init_running_mean(int M, int blocksize){
	struct running_mean s;
	s.M = M;
	s.blocksize = blocksize;

	// reserve the memory for s.lastM...
	// s.lastM is of size M-1 and is initialized to zeros
	s.lastM = (float*)calloc(M-1, sizeof(float));

	// check for error
	if(s.lastM == NULL){
		perror("Not enough memory to initialize running_mean.");
		while(1);
	}
	return s;
}

// Using the running_mean structure initialized above, calculates the running mean
// of parameter x of s->M samples, and stores it in parameter y.
// x is the input array and y is the output array
// x and y should be of size s->blocksize, which is set when init_running_mean() is called.
void calc_running_mean(float* x, struct running_mean* s,float* y){
	// initialize the output
	float prevSum = 0.0f;

	// get the sum of s->lastM
	for(int i=0; i < s->M-1; ++i){
		prevSum += s->lastM[i];
	}

	// iterate over the input samples
	for(int i=0; i < s->blocksize; ++i){
		// add the current input to prevSum to get the total sum
		// also saves that sum in prevSum
		prevSum = y[i] = prevSum + x[i];

		// average y[i] and remove the oldest sample from prevSum
		y[i] /= (float)s->M;
		prevSum -= s->lastM[0];

		// finally, save the current input in s->lastM for future use

		// shift the elements left by 1 and insert the current input at the end
		for(int j = 0; j < s->M-2; ++j){
			s->lastM[j] = s->lastM[j+1];
		}
		s->lastM[s->M-2] = x[i];
	}
}

// Frees the memory reserved by the running_mean structure
// Parameter s is a pointer to the structure to "terminate"
void terminate_running_mean(struct running_mean* s){
	free(s->lastM);
}
