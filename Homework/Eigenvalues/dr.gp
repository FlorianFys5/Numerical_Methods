set terminal pngcairo size 800,600
set output "Dr.png"

set title "Effect of dr on the ground state energy"
set xlabel "dr"
set ylabel "E0"
set grid

plot 'dr.dat' using 2:3 with linespoints title "data"