set terminal pngcairo size 800,600
set output "Three_body.png"

set title "Three-body solution"
set xlabel "x"
set ylabel "y"
set grid

plot "three_body.dat" using 2:3 with lines title "Body 1", \
     "three_body.dat" using 4:5 with lines title "Body 2", \
     "three_body.dat" using 6:7 with lines title "Body 3"