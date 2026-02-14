#include<cmath>
#include<complex>
#include<iostream>
#include"sfunc.h"
using complex=std::complex<double>;
constexpr double  π = 3.14159265358979324;
constexpr double  E = 2.71828182845904523;
constexpr complex I = complex(0,1);
int main(){
    std::cout << "log(I)=" << std::log(I)   <<"\n";
    std::cout << "   I^I=" << std::pow(I,I) <<"\n";
    std::cout << "   π^I=" << std::pow(π,I) <<"\n";
    std::cout << "   E^I=" << std::pow(E,I) <<"\n";
    std::cout << "   π^E=" << std::pow(π,E) <<"\n";
    std::cout << "   E^π=" << std::pow(E,π) <<"\n";
    std::cout << "   2^1/5=" << std::pow(2,0.2) <<"\n";
    std::cout << "   sqrt(2)=" << std::sqrt(2) <<"\n";
    std::cout << "x\tstd::tgamma(x)\tstirling approximation\n";
    for (int i = 1; i <= 10; ++i) {
        double x = static_cast<double>(i);
        std::cout << x
                  << "\t" << std::tgamma(x)
                  << "\t" << sfunc::fgamma(x)
                  << "\n";
    }
}