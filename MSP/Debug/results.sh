withoutextension=$(basename $1 .cnf)



./MSP "$1" 1 >> "$withoutextension-RS.txt"
./MSP "$1" 4 >> "$withoutextension-SA.txt"
./MSP "$1" 5 >> "$withoutextension-TS.txt"
./MSP "$1" 6 >> "$withoutextension-IG.txt"
./MSP "$1" 7 >> "$withoutextension-GRASP.txt"
./MSP "$1" 8 >> "$withoutextension-GA.txt"
./MSP "$1" 2 >> "$withoutextension-LSFI.txt"
./MSP "$1" 3 >> "$withoutextension-LSBI.txt"

./gnuplot.sh $withoutextension
