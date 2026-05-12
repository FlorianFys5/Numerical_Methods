set terminal pngcairo size 800,600
set output "U_sine.png"

set title "u''=-u, with u(0)=0, u'(0)=1"
set xlabel "x"
set ylabel "y"
set grid

plot 'u.dat' using 1:2 with lines title "u(x)", \
     'u.dat' using 1:3 with lines title "u'(x)"