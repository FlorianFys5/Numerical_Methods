CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

Out.txt: main
	./main > Out.txt

main: main.o 
	$(CXX) main.o -o main $(LDLIBS)

main.o: main.cpp vec.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm -f main *.o

.PHONY: all clean