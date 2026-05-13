#include "lin_eq.h"
#include<iostream>
#include<chrono>
std::mt19937 gen(20);
int main(int argc, char* argv[]){
    std::string mode = argv[1];

    if (mode == "benchmark") {
        if (argc < 3) {
            std::cerr << "Usage: ./bench benchmark n\n";
            return 1;
        }
    int n = std::stoi(argv[2]); 
    int repeats = 5;
    double total = 0.0;

    for (int i = 0; i < repeats; i++) { //The idea of averaging multiple run as well as the use of chrono::high_resolution_clock is AI
        auto A = linalg::random_symmetric(n, gen);
        auto start = std::chrono::high_resolution_clock::now();
        auto [w, V] = linalg::jacobi(A);
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<double>(end - start).count();
        }
    std::cout << n << " " << total/repeats << "\n";
    }
    return 0;
}
