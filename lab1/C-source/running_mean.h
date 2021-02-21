#ifndef _ECE486_RUNNING_MEAN_H_
#define _ECE486_RUNNING_MEAN_H_

struct running_mean {
    int M;
    int blocksize;
    float* lastM;
};


struct running_mean init_running_mean(int M, int blocksize);
void calc_running_mean(float* x, struct running_mean* s, float* y);
void terminate_running_mean(struct running_mean* s);

#endif
