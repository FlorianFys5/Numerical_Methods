CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

all: Plot

train.dat: main
	./main > train.dat

plot.dat: main
	./main > plot.dat

main: main.o
	$(CXX) main.o -o main $(LDLIBS)

main.o: main.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Plot: plot.dat train.dat
	gnuplot plot.gp
	gnuplot plotb.gp

clean:
	rm -f main *.o *.dat

.PHONY: all clean