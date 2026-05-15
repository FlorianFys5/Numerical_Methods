g(x) = alpha + x*beta
f(x)= theta + x*omega

fit g(x) "circle.dat" using (log($1)):(log($4)) via alpha, beta
fit f(x) "circle_quasi.dat" using (log($1)):(log($4)) via theta, omega

c = exp(alpha)
d = exp(theta)

set terminal pngcairo size 800,600
set output "Error_fit.png"

set title "Area of unit circle error"
set xlabel "N"
set ylabel "Area"
set grid
set logscale x
set yrange [-0.1:0.5]

plot "circle.dat" using 1:4 with points title "data", \
     c*x**beta with lines title sprintf("fit: N^{%.2f}", beta), \
     "circle_quasi.dat" using 1:4 with points title "data (quasi)", \
     d*x**omega with lines title sprintf("fit (quasi): N^{%.2f}", omega)