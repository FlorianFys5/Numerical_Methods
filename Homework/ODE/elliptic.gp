set terminal pngcairo size 800,600
set output "Elliptic.png"

set title "Planet"
set xlabel "x"
set ylabel "y"
set grid

plot "elliptic.dat" using (1/$2)*cos($1):(1/$2)*sin($1) with lines notitle 