#!/bin/bash
gnuplot -persist -e "set output '3Knapsacks_100_First_1.eps' ; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness';
		     plot '3Knapsacks_100_25density.txt' using 1 t 'Current average in step x' with linespoints pi 10000, '3Knapsacks_100_25density.txt' using 2 t 'Best average until iteration x' with linespoints pi 10000"
