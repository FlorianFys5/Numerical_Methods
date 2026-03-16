TIME = time --format "$$nthreads %e %U" --append --output $@
N = 1000000000

all: Plot.png
main: main.cpp
	g++ -O3 -std=c++23 -pthread main.cpp -o main
Out.times : main #Makefile
	>$@
	for nthreads in 1 2 3 4 5 6 7 8; do \
		$(TIME) ./main -threads $$nthreads -terms $(N); \
	done

Plot.png: Out.times plot_script.gp
	gnuplot plot_script.gp

clean:
	rm -f main log.main Out.times