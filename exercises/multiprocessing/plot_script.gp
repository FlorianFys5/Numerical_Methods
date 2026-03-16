set terminal pngcairo size 800,600 enhanced font 'Arial,14'
set output 'Plot.png'
set grid
set title "Computing time"
set xlabel "Number of threads"
set ylabel "Time [s]"
plot 'Out.times' using 1:2 w lp title "Data points" lw 2, \