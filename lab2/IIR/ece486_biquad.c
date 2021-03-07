#include <stdio.h>
#include <stdlib.h>
#include "ece486_biquad.h"

// recursively create the biquad filter structure
BIQUAD_T *init_biquad(int sections, float g, float *biquad_coefs, int blocksize){





}

// recursively calculate the filter output
void calc_biquad(BIQUAD_T *s, float *x, float *y){



}


// free reserved memory
void destroy_biquad(BIQUAD_T *s){

}
