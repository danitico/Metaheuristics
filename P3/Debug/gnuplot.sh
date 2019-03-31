#!/bin/bash
gnuplot -persist -e "set key right bottom; set output 'pruebas.eps' ; set logscale xy; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness'; plot '3Knapsacks.txt' using 9 t 'Current SA' w l lw 1, '3Knapsacks.txt' using 10 t 'Best SA' w l lw 1"

