#include <stdlib.h>
#include "running_mean.h"

// shifts the elements of an array left n times, padding with 0
void array_left_shift(float* a, int size, int n){
	for(int i = 0; i < n ; ++i){
		for(int j = 0; j < size-1; ++j){
			a[j] = a[j+1];
		}
		a[size-1] = 0;
	}
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
	for(int i = 0; i < s->blocksize; ++i){
		// get the lower_bound for samples to add from current input
		int lower_bound = i-s->M+1;
		lower_bound = (lower_bound < 0)?0:lower_bound;

		// find the sum of the current input values from lower_bound to i
		for(; lower_bound <= i; ++lower_bound){
			y[i] += x[lower_bound];
		}

		// add the sum from the previous samples
		for(int j = i; j <= s->M-1; ++j){
			y[i] += s->lastM[j];
		}
		// convert the sum into the average
		y[i] /= (float)s->M;
    }

	// shift s->lastM s->blocksize times to the left if needed
	if(s->M > s->blocksize){
		array_left_shift(s->lastM,s->M, s->blocksize);
	}

	// replace the end of s->lastM with the new samples
	// get the lowerbounds for both arrays
	int Mlowbound = s->M-s->blocksize;
	Mlowbound = (Mlowbound < 0)? 0:Mlowbound;

	int Xlowbound = s->blocksize-(s->M-1);
	Xlowbound = (Xlowbound < 0)? 0:Xlowbound;

	for(int i = 0; (i+Mlowbound) < s->M-1 && (i+Xlowbound) < s->blocksize; ++i){
		s->lastM[i+Mlowbound] = x[i+Xlowbound];
	}

	return y;
}

void terminate_running_mean(struct run_mean* s){
	free(s->lastM);
}
