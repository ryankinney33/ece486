# Usage:
# make          Compile binaries
# make          Delete ALL binaries

CC=gcc

all: main.out

main.out: main.o ece486_biquad.o
	$(CC) -o main.out main.o ece486_biquad.o

%.o: %.c
	$(CC) -c $< -o $@

main.o: main.c ece486_biquad.h
ece486_biquad.o: ece486_fir.c ece486_biquad.h

clean:
	rm -rf *.out *.o
