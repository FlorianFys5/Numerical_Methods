set terminal pngcairo size 800,600
set output "Acc.png"

set title "acc convergence (r_{max}=8, r_{min}=1e-3,eps=0.01)"
set xlabel "acc"
set ylabel "E0"
set xrange reverse
set logscale x
set grid

plot 'acc.dat' using 1:2 with lines