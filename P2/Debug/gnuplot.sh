#!/bin/bash
gnuplot -persist -e "set key right bottom; set output '3Knapsacks_100_25.eps' ; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness';
		     plot '3KnapSacks.txt' using 1 t 'Fist Current in iteration x' w l lw 3, '3KnapSacks.txt' using 2 t 'Fist Best until iteration x' w l lw 3,
			  '3KnapSacks.txt' using 3 t 'Best Current in iteration x' w l lw 3, '3KnapSacks.txt' using 4 t 'Best Best until iteration x' w l lw 3"
gnuplot -persist -e "set key right bottom; set output '3Knapsacks_100_75.eps' ; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness';
		     plot '3KnapSacks.txt' using 5 t 'Fist Current in iteration x' w l lw 3, '3KnapSacks.txt' using 6 t 'Fist Best until iteration x' w l lw 3,
			  '3KnapSacks.txt' using 7 t 'Best Current in iteration x' w l lw 3, '3KnapSacks.txt' using 8 t 'Best Best until iteration x' w l lw 3"
gnuplot -persist -e "set key right bottom; set output '3Knapsacks_200_25.eps' ; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness';
		     plot '3KnapSacks.txt' using 9 t 'Fist Current in iteration x' w l lw 3, '3KnapSacks.txt' using 10 t 'Fist Best until iteration x' w l lw 3,
			  '3KnapSacks.txt' using 11 t 'Best Current in iteration x' w l lw 3, '3KnapSacks.txt' using 12 t 'Best Best until iteration x' w l lw 3"
gnuplot -persist -e "set key right bottom; set output '3Knapsacks_200_75.eps' ; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness';
		     plot '3KnapSacks.txt' using 13 t 'Fist Current in iteration x' w l lw 3, '3KnapSacks.txt' using 14 t 'Fist Best until iteration x' w l lw 3,
			  '3KnapSacks.txt' using 15 t 'Best Current in iteration x' w l lw 3, '3KnapSacks.txt' using 16 t 'Best Best until iteration x' w l lw 3"



gnuplot -persist -e "set key right bottom; set output '5Knapsacks_100_25.eps' ; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness';
		     plot '5KnapSacks.txt' using 1 t 'Fist Current in iteration x' w l lw 3, '5KnapSacks.txt' using 2 t 'Fist Best until iteration x' w l lw 3,
			  '5KnapSacks.txt' using 3 t 'Best Current in iteration x' w l lw 3, '5KnapSacks.txt' using 4 t 'Best Best until iteration x' w l lw 3"
gnuplot -persist -e "set key right bottom; set output '5Knapsacks_100_75.eps' ; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness';
		     plot '5KnapSacks.txt' using 5 t 'Fist Current in iteration x' w l lw 3, '5KnapSacks.txt' using 6 t 'Fist Best until iteration x' w l lw 3,
			  '5KnapSacks.txt' using 7 t 'Best Current in iteration x' w l lw 3, '5KnapSacks.txt' using 8 t 'Best Best until iteration x' w l lw 3"
gnuplot -persist -e "set key right bottom; set output '5Knapsacks_200_25.eps' ; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness';
		     plot '5KnapSacks.txt' using 9 t 'Fist Current in iteration x' w l lw 3, '5KnapSacks.txt' using 10 t 'Fist Best until iteration x' w l lw 3,
			  '5KnapSacks.txt' using 11 t 'Best Current in iteration x' w l lw 3, '5KnapSacks.txt' using 12 t 'Best Best until iteration x' w l lw 3"
gnuplot -persist -e "set key right bottom; set output '5Knapsacks_200_75.eps' ; set terminal postscript eps color; set xlabel 'Execution step'; set ylabel 'Fitness';
		     plot '5KnapSacks.txt' using 13 t 'Fist Current in iteration x' w l lw 3, '5KnapSacks.txt' using 14 t 'Fist Best until iteration x' w l lw 3,
			  '5KnapSacks.txt' using 15 t 'Best Current in iteration x' w l lw 3, '5KnapSacks.txt' using 16 t 'Best Best until iteration x' w l lw 3"
