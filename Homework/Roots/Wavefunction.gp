set terminal pngcairo size 800,600
set output "Ground_state_radial_wavefunction.png"

set title "Radial wavefunction for E0"
set xlabel "r"
set ylabel "f(r)"
set grid

plot 'Wavefunction_E0.dat' using 1:2 with lines lw 2 title "Calculated", \
     'Wavefunction_E0.dat' using 1:3 with lines dashtype 2 lw 2 title "Correct"