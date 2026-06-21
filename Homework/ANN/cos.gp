set terminal pngcairo size 800,600
set output "Cos.png"

set title "y''+y=0, y(0)=1, y*(0)=0, 10 Nodes"
set xlabel "x"
set ylabel "y"
set grid
  
plot 'cos.dat' using 1:2 with lines lw 2 title "NN prediction", \
     'cos.dat' using 1:3 with lines lw 2 title "NN derivative",