CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

all: Plot

u.dat: main
	./main > u.dat

pendulum.dat: main
	./main > pendulum.dat

circular.dat: main
	./main > circular.dat

elliptic.dat: main
	./main > elliptic.dat

presession.dat: main
	./main > presession.dat

three_body.dat: main
	./main > three_body.dat

main: main.o
	$(CXX) main.o -o main $(LDLIBS)

main.o: main.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Plot: u.dat pendulum.dat circular.dat elliptic.dat presession.dat three_body.dat
	gnuplot u.gp
	gnuplot pendulum.gp
	gnuplot circular.gp
	gnuplot elliptic.gp
	gnuplot presession.gp
	gnuplot three_body.gp

clean:
	rm -f main *.o u.dat pendulum.dat circular.dat elliptic.dat presession.dat three_body.dat

.PHONY: all clean