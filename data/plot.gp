set term push
reset
set term svg background rgb "white" size 16*60, 9*60

set datafile separator ","
set yrange [0:100]
set ylabel "time (ms)"
set xlabel "array size"
set o "svg/2-200000-1.svg"
set title "Classic solution vs Cirilo's algorithm\nn = m\nmax(arr)-min(arr) = 20000"

p "2-200000-1.csv" u 1:2 t "classic" smooth csplines ls 1 lw 3, "" u 1:3 t "cirilo" smooth csplines ls 7 lw 3

set term pop
