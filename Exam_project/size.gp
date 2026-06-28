set terminal pngcairo size 800,600
set output "Size.png"

set title "Effect of the data size"
set xlabel "dim"
set ylabel "y"
set logscale y
set grid
set key bottom right
  
plot 'size.dat' using 1:2 with lines lw 2 title "error_{var}", \
     'sizegcv.dat' using 1:2 with lines lw 2 title "error_{GCV}"