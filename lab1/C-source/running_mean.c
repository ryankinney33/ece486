#include <stdlib.h>
#include "running_mean.h"

// shifts the elements of an array left once and inserts val at the end
void shift_insert(float* arr, int size, float val){
	// shifts the elements left by 1
	for(int i = 0; i < size-1; ++i){
		arr[i] = arr[i+1];
	}
	// insert the new value in the open spot at the end
	arr[size-1] = val;
}

struct run_mean init_running_mean(int M, int blocksize){
	struct run_mean s;
	s.M = M;
	s.blocksize = blocksize;
	s.lastM = (float*)calloc(M-1, sizeof(float));
	return s;
}

float* calc_running_mean(float* x, struct run_mean* s){
	// initialize the output
	float* y = (float*)calloc(s->blocksize, sizeof(float));
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

		// finally, save the current input in s->lastM for future need
		shift_insert(s->lastM, s->M-1, x[i]);
	}
	return y;
}

void terminate_running_mean(struct run_mean* s){
	free(s->lastM);
}
