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

	// iterate over the input samples
	for(int i=0; i < s->blocksize; ++i){
		// get the sum of s->lastM
		for(int j=0; j < s->M-1; ++j){
			y[i] += s->lastM[j];
		}

		// add the current input and find the average of the sum
		y[i] = (y[i]+x[i])/(float)s->M;

		// finally, save the current input
		shift_insert(s->lastM, s->M-1, x[i]);
	}
	return y;
}

void terminate_running_mean(struct run_mean* s){
	free(s->lastM);
}
