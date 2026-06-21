set terminal pngcairo size 800,600
set output "NN_interploation.png"

f(x)=cos(5*x-1)*exp(-x*x)

set title "10 nodes"
set xlabel "x"
set ylabel "y"
set xrange [-1.2:1.2]
set grid

plot 'plot.dat' using 1:2 with lines lw 2 title "NN prediction", \
     f(x) with lines dashtype 2 lw 2 title "Function", \
     "train.dat" u 1:2 w p pt 7 ps 1.5 title "Training points"