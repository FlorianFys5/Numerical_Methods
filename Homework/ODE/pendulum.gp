set terminal pngcairo size 800,600
set output "Pendulum.png"

set title "theta(0)=pi-1, omega(0)=0"
set xlabel "x"
set ylabel "y"
set grid

plot 'pendulum.dat' using 1:2 with lines title "theta(t)", \
     'pendulum.dat' using 1:3 with lines title "omega(t)"