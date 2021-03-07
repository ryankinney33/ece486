#ifndef _ECE486_BIQUAD_H_
#define _ECE486_BIQUAD_H_


// stucture for the biquad filter
typedef struct BIQUAD_T{
	int blocksize
	float g;

	float* a;
	float* b;

	float* v1;
	float* v2;

	struct BIQUAD_T* next_section;
} BIQUAD_T;

// functions for initializing and using the biquad filter
BIQUAD_T *init_biquad(int sections, float g, float *biquad_coefs, int blocksize);
void calc_biquad(BIQUAD_T *s, float *x, float *y);
void destroy_biquad(BIQUAD_T *s);



#endif
