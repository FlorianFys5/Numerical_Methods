#include "funcs.h"
#include<iostream>
#include<fstream>
int main(){
    std::ofstream f("Out.txt");
    for(double x=-5; x<=5; x+=0.001) {
        f << x << " " << Functions::erf(x) << " " << Functions::sgamma(x) << " " << Functions::lngamma(x) << "\n";
    }
    return 0;
}