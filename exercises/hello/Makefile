CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2
LDLIBS = -lm

TARGET = main

all: Out.txt

Out.txt: $(TARGET)
	./$(TARGET) > Out.txt

$(TARGET): hello.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f Out.txt $(TARGET)

.PHONY: all clean
