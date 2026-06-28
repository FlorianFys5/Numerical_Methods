set terminal pngcairo size 800,600
set output "Blur.png"

set title "Effect of blurring matrix B on the deconvolution (B_{ij}=exp(-(i-j)**2/2*sigma**2))"
set xlabel "sigma"
set ylabel "y"
set xrange reverse
set logscale y
set yrange [-1:10000]
set grid
set key top left
  
plot 'blurring.dat' using 1:2 with lines lw 2 title "error", \
     'blurring.dat' using 1:3 with lines lw 2 title "alpha", \
     'blurring.dat' using 1:4 with lines lw 2 title "condition number_{Frobenius}", \
     'blurring.dat' using 1:5 with lines lw 2 title "|D*y_{recovered}|"