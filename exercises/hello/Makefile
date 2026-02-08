CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm 
Out.txt : hello             # Out.txt depends on hello.exe
	./hello > Out.txt        # run hello.exe, send output to Out.txt
hello: hello.cpp                 # hello depends on hello.cpp
	c++ -o hello hello.cpp  # compile-and-link hello.cpp, save executable in hello
clean:
	rm -f Out.txt hello