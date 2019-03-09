#!/bin/bash
gnuplot -persist -e "set key right bottom; set output '3Knapsacks_200_Best_2.eps' ; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness';
		     plot '3Knapsacks_200_75density.txt' using 3 t 'Current average in step x' w l lw 3, '3Knapsacks_200_75density.txt' using 4 t 'Best average until iteration x' w l lw 3"
