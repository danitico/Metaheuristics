#!/bin/bash
gnuplot -persist -e "set key right bottom; set output '$1_GA.eps' ; set logscale y 10; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness'; plot '$1' using 1 t 'Current' w l lw 1, '$1' using 2 t 'Best' w l lw 1"

gnuplot -persist -e "set key right bottom; set output '$1_ACO.eps' ; set logscale y 10; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness'; plot '$1' using 3 t 'Current' w l lw 1, '$1' using 4 t 'Best' w l lw 1"
