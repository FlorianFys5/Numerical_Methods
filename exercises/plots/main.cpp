#include "funcs.h"
#include<iostream>
#include<fstream>
int main(){
    std::ofstream f("Out.txt");
    for(double x=0; x<=4; x+=0.1) {
        f << x << " " << Functions::erf(x) << " " << Functions::sgamma(x) << " " << Functions::lngamma(x) << "\n";
    }
    return 0;
}