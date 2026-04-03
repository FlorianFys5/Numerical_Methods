#include "Lin_eq.h"
#include <iostream>
#include <random>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./time N\n";
        return 1;
    }

    size_t N = std::stoul(argv[1]);

    std::mt19937 gen(20);
    auto A = linalg::random_matrix<double>(N, N, gen);

    linalg::QR<double> qr(A);

    return 0;
}