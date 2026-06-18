set terminal pngcairo size 800,600
set output "Quadratic_functional.png"

set title "Quadratic (functional) interpolation cosine"
set xlabel "x"
set ylabel "y"
set grid

plot 'functional.dat' using 1:2 with lines title "Interpolant", \
     "linear.txt" u 1:2 w p pt 7 ps 1.5 title "Interpolation points"