CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

all: Out.txt test.txt Plot

Out.txt: main
	./main > Out.txt

main: main.o
	$(CXX) main.o -o main $(LDLIBS)

main.o: main.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

test.txt: test
	./test > test.txt

test: test.o
	$(CXX) test.o -o test $(LDLIBS)

test.o: test.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o

Plot: 
	gnuplot plot.gp

clean:
	rm -f main *.o test

.PHONY: all clean