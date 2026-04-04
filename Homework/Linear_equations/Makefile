CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

all: Out.txt Plot

Out.txt: main
	./main > Out.txt

main: main.o
	$(CXX) main.o -o main $(LDLIBS)

main.o: main.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

time: time.o
	$(CXX) time.o -o time $(LDLIBS)

time.o: time.cpp lin_eq.h
	$(CXX) $(CXXFLAGS) -c time.cpp -o time.o

out.times.data: time
	> $@
	for N in $$(seq 160 20 460); do \
		/usr/bin/time --format "$$N %e" --output $@ --append \
		./time $$N 1>out 2>err ;\
	done

Plot: out.times.data
	gnuplot plot.gp

clean:
	rm -f main *.o out.times.data out err Out.txt Runtime_fit.png time fit.log

.PHONY: all clean