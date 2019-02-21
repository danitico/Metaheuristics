#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "jeu1.eps"
set key right bottom
set xlabel "Etiqueta eje X"
set ylabel "Etiqueta Eje Y"
plot 'Soluciones.txt' using 1:3 t "Tiempo real" w l
_end_
