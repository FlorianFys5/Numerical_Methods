set terminal pngcairo size 800,600
set output "R_min.png"

set title "r_{min} convergence (r_{max}=8)"
set xlabel "r_{min}"
set ylabel "E0"
set xrange reverse
set logscale x
set grid

plot 'r_min.dat' using 1:2 with lines