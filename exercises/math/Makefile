CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

Out.txt: main
	./main > Out.txt

main: main.o sfunc.o
	$(CXX) main.o sfunc.o -o main $(LDLIBS)

main.o: main.cpp sfunc.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

sfunc.o: sfunc.cpp sfunc.h
	$(CXX) $(CXXFLAGS) -c sfunc.cpp -o sfunc.o

clean:
	rm -f main *.o

.PHONY: all clean