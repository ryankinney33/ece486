#include <stdlib.h>
#include <stdio.h>
#include "running_mean.h"

int main(){
    int M = 5;
    int blocksize = 9;
    float x[] = {2.0f,4.0f,6.0f,8.0f,12.0f,14.0f,16.0f,18.0f,20.0f};
    float*y;

    struct run_mean s = init_running_mean(M, blocksize);

    y = calc_running_mean(x, &s);
    printf("printing y:\n");
    for(int i = 0; i < blocksize; i++){
    	printf("y[%d]=%lf\n",i,y[i]);
	}

	// free memory and close open files
    terminate_running_mean(&s);
    free(y);

    return 0;
}
