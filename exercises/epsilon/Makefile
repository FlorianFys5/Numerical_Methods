CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

Out.txt: main
	./main > Out.txt

main: main.o approx.o
	$(CXX) main.o approx.o -o main $(LDLIBS)

main.o: main.cpp approx.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

approx.o: approx.cpp approx.h
	$(CXX) $(CXXFLAGS) -c approx.cpp -o approx.o

clean:
	rm -f main *.o

.PHONY: all clean