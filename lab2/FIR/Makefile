# Usage:
# make          Compile binaries
# make          Delete ALL binaries

CC=gcc

all: main.out

main.out: main.o ece486_fir.o
	$(CC) -o main.out main.o ece486_fir.o

%.o: %.c
	$(CC) -c $< -o $@

main.o: main.c ece486_fir.h
ece486_fir.o: ece486_fir.c ece486_fir.h

clean:
	rm -rf *.out *.o
