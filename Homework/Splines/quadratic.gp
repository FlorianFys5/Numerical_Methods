set terminal pngcairo size 800,600
set output "Quadratic.png"

set title "Quadratic interpolation cosine"
set xlabel "x"
set ylabel "y"
set grid

plot 'quadratic.dat' using 1:2 with lines title "Interpolant", \
     'quadratic.dat' using 1:3 with lines title "Derivative", \
     'quadratic.dat' using 1:4 with lines title "Anti-Derivative"