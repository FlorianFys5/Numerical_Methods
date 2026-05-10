CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

all: Plot

linear.dat: main
	./main > linear.dat

main: main.o
	$(CXX) main.o -o main $(LDLIBS)

main.o: main.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

quadratic.dat: qspline
	./qspline > quadratic.dat

qspline: qspline.o
	$(CXX) qspline.o -o qspline $(LDLIBS)

qspline.o: qspline.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c qspline.cpp -o qspline.o

functional.dat: functional
	./functional > functional.dat

functional: functional.o
	$(CXX) functional.o -o functional $(LDLIBS)

functional.o: functional.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c functional.cpp -o functional.o

Plot: linear.dat quadratic.dat functional.dat
	gnuplot linear.gp
	gnuplot quadratic.gp
	gnuplot functional.gp
clean:
	rm -f main *.o linear.dat quadratic.dat functional.dat

.PHONY: all clean