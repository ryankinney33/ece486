/*
 * This file contains the declarations for the functions and
 * a structure to calculate the running mean of an array.
 *
 * Contains the definition of the structure holding the information
 * for calculating the running mean. A function for initializing
 * the structure, a function for using the structure and an input
 * to calculate the running mean, and a function to free memory
 * reserved by the structure.
 *
 * Authors: Ryan Kinney, Devin Hoskin, Jason Halliday
 * ECE 486 - Lab 1
 * February 21, 2021
 */

#ifndef _ECE486_RUNNING_MEAN_H_
#define _ECE486_RUNNING_MEAN_H_


// The typedef for the structure ro calculate the running mean.
// Contains the information necessary to calculate running means.
// Holds the previous M-1 samples of the input, the size of the input,
// and the number of samples to run the average over
struct running_mean {
    int M; // the number of samples to average over.
    int blocksize; // the number of samples (size) of the input and output
    float* lastM; // contains the previous M-1 samples of the input (used for subsequent calculations)
};

// Initializes the structure for calculating the running mean
// Argument M is the number of samples to calculate the average over
// Argument blocksize is the size of the input and output
struct running_mean init_running_mean(int M, int blocksize);

// Using the running_mean structure initialized above, calculates the running mean
// of parameter x of s->M samples, and stores it in parameter y.
// x is the input array and y is the output array
// x and y should be of size s->blocksize, which is set when init_running_mean() is called.
void calc_running_mean(float* x, struct running_mean* s, float* y);

// Frees the memory reserved by the running_mean structure
void terminate_running_mean(struct running_mean* s);

#endif
