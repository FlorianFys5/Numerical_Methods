CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

all: Out.txt Plot

Out.txt: main
	./main > Out.txt

erf.dat: main
	./main > erf.dat

error.dat: main
	./main > error.dat

main: main.o
	$(CXX) main.o -o main $(LDLIBS)

main.o: main.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Plot: erf.dat error.dat
	gnuplot erf.gp
	gnuplot error.gp

clean:
	rm -f main *.o *.dat

.PHONY: all clean