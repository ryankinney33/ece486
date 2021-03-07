#include <stdio.h>
#include <stdlib.h>
#include "ece486_biquad.h"

// recursively create the biquad filter structure
BIQUAD_T *init_biquad(int sections, float g, float *biquad_coefs, int blocksize){
	if(sections < 1){ // if there are no sections in the filter, then what are you doing?
		return NULL;
	}

	// start by creating the structure
	BIQUAD_T* s = (BIQUAD_T*)malloc(sizeof(BIQUAD_T*));
	if(s == NULL){
		printf("Error: Unable to initialize BIQUAD_T\n");
		while(1); // used for STM32 microcontroller
	}

	// assign the necessary values
	s->blocksize = blocksize;
	s->g = g;

	// allocate memory for the arrays
	s->a = (float*)malloc(2*sizeof(float));
	if(s->a == NULL){
		printf("Error: Unable to initialize BIQUAD_T.a\n");
		while(1); // used for STM32 microcontroller
	}

	s->b = (float*)malloc(3*sizeof(float));
	if(s->b == NULL){
		printf("Error: Unable to initialize BIQUAD_T.b\n");
		while(1); // used for STM32 microcontroller
	}

	s->v1 = (float*)calloc(blocksize,sizeof(float));
	if(s->v1 == NULL){
		printf("Error: Unable to initialize BIQUAD_T.v1\n");
		while(1); // used for STM32 microcontroller
	}

	s->v2 = (float*)calloc(blocksize,sizeof(float));
	if(s->v2 == NULL){
		printf("Error: Unable to initialize BIQUAD_T.v2\n");
		while(1); // used for STM32 microcontroller
	}

	// now set the coefficients in s->a and s->b with biquad_coefs array
	// biquad_coefs looks like the following....
	// biqaud_coefs =
	//   {b10, b11, b12, a11, a12, b20, b21, b22, a21, a22, . . . bs0, bs1, bs2, as1, as2}
	s->b[0]=biquad_coefs[0];
	s->b[1]=biquad_coefs[1];
	s->b[2]=biquad_coefs[2];

	s->a[0]=biquad_coefs[3];
	s->a[1]=biquad_coefs[4];

	// only thing left is to create the next section (if applicable)
	if(sections > 1){
		s->next_section = init_biquad(sections-1,1.0f,biquad_coefs+5,blocksize);
	}else{
		// this is the final section, next_section should be null
		s->next_section = NULL;
	}

	return s;
}

// recursively calculate the filter output
void calc_biquad(BIQUAD_T *s, float *x, float *y){



}


// free reserved memory
void destroy_biquad(BIQUAD_T *s){
	if(s != NULL){
		// start by freeing the arrays
		free(s->a);
		free(s->b);
		free(s->v1);
		free(s->v2);

		// destroy the next section
		destroy_biquad(s->next_section);

		// all the next sections are gone, s can be freed now
		free(s);
	}
}
