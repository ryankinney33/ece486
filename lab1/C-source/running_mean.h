#ifndef _ECE486_RUNNING_MEAN_H_
#define _ECE486_RUNNING_MEAN_H_

struct run_mean {
    int M;
    int blocksize;
    float* lastM;
};


struct run_mean init_running_mean(int M, int blocksize);
float* calc_running_mean(float* x, struct run_mean* s);
void terminate_running_mean(struct run_mean* s);

#endif
