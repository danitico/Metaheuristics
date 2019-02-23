#!/bin/bash
gnuplot -persist -e "set output '5Knapsacks_200_2.eps' ; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness';
		     plot '5Knapsacks.txt' using 11 t 'Best average in iteration x' with linespoints pi 10000, '5Knapsacks.txt' using 12 t 'Best average until iteration x'with linespoints pi 10000"
