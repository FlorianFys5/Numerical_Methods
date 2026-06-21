CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23 -O2
LDLIBS = -lm

all: Plot

cos.dat: main
	./main > cos.dat

train.dat: main
	./main > train.dat

plot.dat: main
	./main > plot.dat

main: main.o
	$(CXX) main.o -o main $(LDLIBS)

main.o: main.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Plot: plot.dat train.dat cos.dat
	gnuplot plot.gp
	gnuplot plotb.gp
	gnuplot cos.gp

clean:
	rm -f main *.o *.dat

.PHONY: all clean