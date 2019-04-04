#!/bin/bash
gnuplot -persist -e "set key right bottom; set output '$1_SA.eps' ; set logscale y 10; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness'; plot '$1' using 1 t 'Current' w l lw 1, '$1' using 2 t 'Best' w l lw 1"

gnuplot -persist -e "set key right bottom; set output '$1_TS.eps' ; set logscale y 10; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness'; plot '$1' using 3 t 'Current' w l lw 1, '$1' using 4 t 'Best' w l lw 1"

gnuplot -persist -e "set key right bottom; set output '$1_Grasp.eps' ; set logscale y 10; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness'; plot '$1' using 5 t 'Current' w l lw 1, '$1' using 6 t 'Best' w l lw 1"

gnuplot -persist -e "set key right bottom; set output '$1_IG.eps' ; set logscale y 10; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness'; plot '$1' using 7 t 'Current' w l lw 1, '$1' using 8 t 'Best' w l lw 1"
