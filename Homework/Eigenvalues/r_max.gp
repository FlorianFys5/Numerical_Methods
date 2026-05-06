set terminal pngcairo size 800,600
set output "R-max.png"

set title "Effect of r_{max} on the ground state energy"
set xlabel "r_{max}"
set ylabel "E0"
set grid

plot 'rmax.dat' using 1:3 with linespoints title "data"