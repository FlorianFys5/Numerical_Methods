set terminal pngcairo size 800,600
set output "Plot.png"

f(x)=A*exp(lambda*x)
fp(x)=Ap*exp(lp*x)
fm(x)=Am*exp(lm*x)

A=exp(4.95866)
lambda=-0.170624
Ap=exp(4.95866+0.0354019)
lp=-0.170624+0.00715662
Am=exp(4.95866-0.0354019)
lm=-0.170624-0.00715662

set title "Decay fit"
set xlabel "t[days]"
set ylabel "Activity"
set grid

plot \
    '-' using 1:2:3 with yerrorbars title "Data", \
    f(x) with lines title "Fit", \
    fp(x) with lines title "Fit upper bound", \
    fm(x) with lines title "Fit lower bound"

1   117.0   6.0
2   100.0   5.0
3    88.0   4.0
4    72.0   4.0
6    53.0   4.0
9    29.5   3.0
10   25.2   3.0
13   15.2   2.0
15   11.1   2.0
e