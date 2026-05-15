CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

all: Out.txt Plot

Out.txt: main
	./main > Out.txt

cirlce.dat: main	
	.\main > circle.dat

circle_quasi.dat: main
	.\main > circle_quasi.dat

main: main.o
	$(CXX) main.o -o main $(LDLIBS)

main.o: main.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Plot: circle.dat circle_quasi.dat
	gnuplot circle.gp

clean:
	rm -f main *.o *.dat

.PHONY: all clean