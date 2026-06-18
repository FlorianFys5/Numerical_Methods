set terminal pngcairo size 800,600
set output "Eps.png"

set title "eps convergence (r_{max}=8, r_{min}=1e-3,acc=0.01)"
set xlabel "eps"
set ylabel "E0"
set xrange reverse
set logscale x
set grid

plot 'eps.dat' using 1:2 with lines