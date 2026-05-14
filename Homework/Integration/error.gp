set terminal pngcairo size 800,600
set output "Error.png"

set title "Error of erf(1) as a function of the absolute accurancy"
set xlabel "acc"
set ylabel "error"
set grid
set logscale xz

plot 'error.dat' using 1:2 with lines notitle 