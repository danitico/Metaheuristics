#!/bin/bash
gnuplot -persist -e "set output 'prueba8.eps' ; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness'; plot 'fichero.txt' using 1 t 'Best average in iteration x' w l, 'fichero.txt' using 2 t 'Best average until iteration x'w l"
