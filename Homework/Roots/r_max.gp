set terminal pngcairo size 800,600
set output "R_max.png"

set title "r_{max} convergence (r_{min}=1e-3)"
set xlabel "r_{max}"
set ylabel "E0"
set grid

plot 'r_max.dat' using 1:2 with lines