#!/bin/bash
gnuplot -persist -e "set output '$1-RS.eps' ; set terminal postscript eps color;set xlabel 'Execution step'; set ylabel 'Fitness'; plot '$1-RS.txt' using 1 t 'Current Fitness' w l, '$1-RS.txt' using 2 t 'Best fitness' w l"

gnuplot -persist -e "set output '$1-LSFI.eps' ; set terminal postscript eps color;set xlabel 'Execution step'; set ylabel 'Fitness'; plot '$1-LSFI.txt' using 1 t 'Current Fitness' w l, '$1-LSFI.txt' using 2 t 'Best fitness' w l"

gnuplot -persist -e "set output '$1-LSBI.eps' ; set terminal postscript eps color;set xlabel 'Execution step'; set ylabel 'Fitness'; plot '$1-LSBI.txt' using 1 t 'Current Fitness' w l, '$1-LSBI.txt' using 2 t 'Best fitness' w l"

gnuplot -persist -e "set output '$1-SA.eps' ; set terminal postscript eps color;set xlabel 'Execution step'; set ylabel 'Fitness'; plot '$1-SA.txt' using 1 t 'Current Fitness' w l, '$1-SA.txt' using 2 t 'Best fitness' w l"

gnuplot -persist -e "set output '$1-TS.eps' ; set terminal postscript eps color;set xlabel 'Execution step'; set ylabel 'Fitness'; plot '$1-TS.txt' using 1 t 'Current Fitness' w l, '$1-TS.txt' using 2 t 'Best fitness' w l"

gnuplot -persist -e "set output '$1-IG.eps' ; set terminal postscript eps color;set xlabel 'Execution step'; set ylabel 'Fitness'; plot '$1-IG.txt' using 1 t 'Current Fitness' w l, '$1-IG.txt' using 2 t 'Best fitness' w l"

gnuplot -persist -e "set output '$1-GRASP.eps' ; set terminal postscript eps color;set xlabel 'Execution step'; set ylabel 'Fitness'; plot '$1-GRASP.txt' using 1 t 'Current Fitness' w l, '$1-GRASP.txt' using 2 t 'Best fitness' w l"

gnuplot -persist -e "set output '$1-GA.eps' ; set terminal postscript eps color;set xlabel 'Execution step'; set ylabel 'Fitness'; plot '$1-GA.txt' using 1 t 'Current Fitness' w l, '$1-GA.txt' using 2 t 'Best fitness' w l"
