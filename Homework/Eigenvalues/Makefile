CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

all: Out.txt bench Plot

Out.txt: main
	./main testing 20 0.1 > Out.txt

main: main.o
	$(CXX) main.o -o main $(LDLIBS)

main.o: main.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

bench: bench.o
	$(CXX) bench.o -o bench $(LDLIBS)

bench.o: bench.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c bench.cpp -o bench.o

analytic: analytic.o
	$(CXX) analytic.o -o analytic $(LDLIBS)

analytic.o: analytic_wave.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c analytic_wave.cpp -o analytic.o

rmax.dat: main
	for r in 2 5 7 10 15 20; do \
		./main energy $$r 0.1 >> rmax.dat; \
	done

dr.dat: main
	for d in 0.05 0.1 0.2 0.5; do \
		./main energy 20 $$d >> dr.dat; \
	done

wave.dat: main
	./main wave 50 0.1 > wave.dat

timing.dat: bench
	for n in 10 20 30 40 50 75 100 150; do \
		./bench benchmark $$n >> timing.dat; \
	done

analytic_wave.dat: analytic
	./analytic 50 0.1 > analytic_wave.dat

Plot: rmax.dat dr.dat wave.dat timing.dat analytic_wave.dat
	gnuplot r_max.gp
	gnuplot dr.gp
	gnuplot wave.gp
	gnuplot timing.gp

clean:
	rm -f main *.o rmax.dat dr.dat wave.dat timing.dat r_max.png dr.png Wavefunction.png Runtime_fit.png Out.txt bench analytic

.PHONY: all clean