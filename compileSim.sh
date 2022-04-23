#!/bin/sh
gcc -ansi -c queue.c -o queue.o
gcc -ansi -c runSimulations.c -o runSimulations.o
gcc -ansi runSimulations.o queue.o lights.o -lgsl -lgslcblas -o runSimulations
./runSimulations 40 80 39 23 2>err.lis
