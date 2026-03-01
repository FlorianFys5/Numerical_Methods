CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

all: Plot.png

Out.txt: main
	./main > Out.txt

main: main.o funcs.o
	$(CXX) main.o funcs.o -o main $(LDLIBS)

main.o: main.cpp funcs.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

funcs.o: funcs.cpp funcs.h
	$(CXX) $(CXXFLAGS) -c funcs.cpp -o funcs.o

Plot.png: Out.txt plot_script.gp
	gnuplot plot_script.gp

clean:
	rm -f main *.o

.PHONY: all clean