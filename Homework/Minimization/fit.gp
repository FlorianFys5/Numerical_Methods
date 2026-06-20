set terminal pngcairo size 800,600
set output "Fit.png"

set title "Higgs fit"
set xlabel "E [GeV]"
set ylabel "\sigma(E)"
set grid

plot 'fit.dat' using 1:2 with lines title "Fit", \
     "higgs.data.txt" with errorbars title "Data points"