set terminal pngcairo size 800,600
set output "Erf.png"

set title "Error function"
set xlabel "x"
set ylabel "y"
set grid

plot 'erf.dat' using 1:2 with lines title "erf(x)", \
    "erf_table.txt" using 1:2 w p pt 7 ps 1.5 title "erf table"