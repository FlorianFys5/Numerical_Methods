g(x) = alpha + beta*x

fit g(x) "timing.dat" using (log($1)):(log($2)) via alpha,beta

c = exp(alpha)

set terminal pngcairo size 800,600
set output "Runtime_fit.png"

set title "EVD Runtime Fit"
set xlabel "N"
set ylabel "time (s)"
set grid

plot "timing.dat" using 1:2 with points title "data", \
     c*x**beta with lines title sprintf("fit: N^{%.2f}", beta)