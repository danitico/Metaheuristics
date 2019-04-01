#!/bin/bash
gnuplot -persist -e "set key right bottom; set output 'prueba.eps' ; set logscale xy 10; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness'; plot 'prueba.txt' using 1 t 'Current SA' w l lw 1, 'prueba.txt' using 2 t 'Best SA' w l lw 1"

gnuplot -persist -e "set key right bottom; set output 'prueba1.eps' ; set logscale xy 10; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness'; plot 'prueba1.txt' using 1 t 'Current SA' w l lw 1, 'prueba1.txt' using 2 t 'Best SA' w l lw 1"

gnuplot -persist -e "set key right bottom; set output 'pruebaIG.eps' ; set logscale xy 10; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness'; plot 'prueba.txt' using 7 t 'Current IG' w l lw 1, 'prueba.txt' using 8 t 'Best IG' w l lw 1"

gnuplot -persist -e "set key right bottom; set output 'pruebaIG1.eps' ; set logscale xy 10; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness'; plot 'prueba1.txt' using 7 t 'Current IG' w l lw 1, 'prueba1.txt' using 8 t 'Best IG' w l lw 1"
