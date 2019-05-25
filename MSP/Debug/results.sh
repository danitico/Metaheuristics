withoutextension=$(basename $1 .cnf)

rm -rf *.txt *.eps

./MSP "$1" 1 >> "$withoutextension-RS.txt"
./MSP "$1" 2 >> "$withoutextension-LSFI.txt"
./MSP "$1" 3 >> "$withoutextension-LSBI.txt"
./MSP "$1" 4 >> "$withoutextension-SA.txt"
./MSP "$1" 5 >> "$withoutextension-TS.txt"
./MSP "$1" 6 >> "$withoutextension-IG.txt"
./MSP "$1" 7 >> "$withoutextension-GRASP.txt"
./MSP "$1" 8 >> "$withoutextension-GA.txt"

./gnuplot.sh $withoutextension
