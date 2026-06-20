CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

all: Out.txt Plot

Out.txt: main
	./main < higgs.data.txt > Out.txt

fit.dat: main
	./main < higgs.data.txt > fit.dat

main: main.o
	$(CXX) main.o -o main $(LDLIBS)

main.o: main.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Plot: fit.dat
	gnuplot fit.gp

clean:
	rm -f main *.o *.dat

.PHONY: all clean