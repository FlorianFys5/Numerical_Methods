CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

all: Out.txt Plot

Out.txt: main
	./main > Out.txt

Wavefunction_E0.dat: main
	./main > Wavefunction_E0.dat

r_min.dat: main
	./main > r_min.dat

r_max.dat: main
	./main > r_max.dat

acc.dat: main
	./main > acc.dat

eps.dat: main
	./main > eps.dat

main: main.o
	$(CXX) main.o -o main $(LDLIBS)

main.o: main.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Plot: Wavefunction_E0.dat r_max.dat r_min.dat acc.dat eps.dat
	gnuplot Wavefunction.gp
	gnuplot r_max.gp
	gnuplot r_min.gp
	gnuplot acc.gp
	gnuplot eps.gp

clean:
	rm -f main *.o *.dat

.PHONY: all clean