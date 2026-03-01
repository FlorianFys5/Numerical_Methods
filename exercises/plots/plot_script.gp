set terminal pngcairo size 800,600 enhanced font 'Arial,14'
set output 'Plot.png'
set title "Functions"
set xlabel "x"
set ylabel "y"
plot 'Out.txt' using 1:2 title "erf(x)" lw 2, \
     'Out.txt' using 1:3 title "sgamma(x)" lw 2, \
     'Out.txt' using 1:4 title "lngamma(x)" lw 2