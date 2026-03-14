CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23 -O2

all: run

main_args: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main_args

main_pipe: main_2.cpp
	$(CXX) $(CXXFLAGS) main_2.cpp -o main_pipe

main_file: main_3.cpp
	$(CXX) $(CXXFLAGS) main_3.cpp -o main_file

run: main_args main_pipe main_file
	rm -f out.txt

	echo "Args input:" >> Out.txt
	echo "-n 1 -n 2 -n 3 -n 4 -n 5" > inputfile
	./main_args $$(cat inputfile) >> Out.txt

	echo "Pipe input:" >> Out.txt
	echo 1 2 3 4 5 | ./main_pipe >> Out.txt

	echo "File input:" >> Out.txt
	./main_file --input inputfile.txt --output temp.txt
	cat temp.txt >> Out.txt

clean:
	rm -f main_args main_pipe main_file Out.txt inputfile temp.txt