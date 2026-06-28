CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

all: Out.txt Plot

Out.txt: main
	./main > Out.txt

blurring.dat: main
	./main > blurring.dat

blurring2.dat: main
	./main > blurring2.dat

noise.dat: main
	./main > noise.dat

size.dat: main
	./main > size.dat

sizegcv.dat: main
	./main > sizegcv.dat

main: main.o
	$(CXX) main.o -o main $(LDLIBS)

main.o: main.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Plot: blurring.dat noise.dat size.dat sizegcv.dat
	gnuplot blur.gp
	gnuplot noise.gp
	gnuplot size.gp

clean:
	rm -f main *.o *.dat

.PHONY: all clean