# Lab 2
## Task 1
*FIR Filters*: Write and test your C-code implementations of discrete-time convolution using a predefined function interface as provided on the lab web site (Don's site).
Use file names of ece486_fir.c and ece486_fir.h to provide your implementation of the described interface. 

You are not allowed to change the format or name of any of the function calls, or the file names containing your implementation.
Develop a separate routine to test your code, and document your test results.

## Task 2
*IIR Filters*: Write and test a C-code implementation of IIR filters through cascaded biquadratic filters. Each biquad filter is implemented using the *Transposed Direct Form II*.

## Task 3
*Real-Time Implementation* Write a program that uses the above FIR and Biquad functions to demonstrate discrete-time filters in real-time using the ECE486 ARM development board, using a sampling rate of 48 ksps. Use a function generator to drive an ADC input on the development board, calculate a filter output, and deliver the output waveform to a DAC output for measurement using an oscilloscope.
