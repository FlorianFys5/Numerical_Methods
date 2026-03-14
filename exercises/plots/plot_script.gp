set terminal pngcairo size 800,600 enhanced font 'Arial,14'
set output 'Plot.png'
set xrange [-5:5]
set yrange [-5:5]
set grid
set key bottom right
set title "Functions"
set xlabel "x"
set ylabel "y"
plot 'Out.txt' using 1:2 w l title "Erf(x)" lw 4, \
     "erf_table.txt" u 1:2 w p pt 7 ps 1.5 title "Erf table", \
     'Out.txt' using 1:3 w l title "Gamma(x)" lw 2, \
     "gamma_table.txt" u 1:2 w p pt 7 ps 1.5 title "Gamma table", \
     'Out.txt' using 1:4 w l title "lngamma(x)" lw 2, \
     "lngamma_table.txt" u 1:2 w p pt 7 ps 1.5 title "lngamma table"