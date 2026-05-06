set terminal pngcairo size 800,600
set output "Wavefunction.png"

set title "Reduced radial wavefunction"
set xlabel "r"
set ylabel "f(r)"
set grid

plot for [i=2:5] 'wave.dat' using 1:i with lines linewidth 2 title sprintf("psi_%d", i-2), \
     for [i=2:5] 'analytic_wave.dat' using 1:i with lines dashtype 2 lw 2 title sprintf("R_%d", i-2)