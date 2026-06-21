set terminal pngcairo size 800,600
set output "B.png"

set title "10 nodes"
set xlabel "x"
set ylabel "y"
set yrange[-10:10]
set grid
  
plot 'plot.dat' using 1:2 with lines lw 2 title "NN prediction", \
     'plot.dat' using 1:3 with lines lw 2 title "NN derivative", \
     'plot.dat' using 1:4 with lines lw 2 title "NN second derivative", \
     'plot.dat' using 1:5 with lines lw 2 title "NN anti-derivative"