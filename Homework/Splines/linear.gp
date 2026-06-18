set terminal pngcairo size 800,600
set output "Linear.png"

set title "Linear interpolation cosine"
set xlabel "x"
set ylabel "y"
set grid

plot 'linear.dat' using 1:2 with lines title "Interpolant", \
     'linear.dat' using 1:3 with lines title "Interpolant anti-derivative", \
     "linear.txt" u 1:2 w p pt 7 ps 1.5 title "Interpolation points"
