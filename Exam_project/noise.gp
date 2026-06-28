set terminal pngcairo size 800,600
set output "Noise.png"

set title "Effect of adding a gaussian noise to the data"
set xlabel "sigma"
set ylabel "y"
set xrange reverse
set logscale y
set grid
  
plot 'noise.dat' using 1:2 with lines lw 2 title "error", \
     'noise.dat' using 1:3 with lines lw 2 title "alpha"