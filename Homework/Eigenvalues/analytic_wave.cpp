#include "lin_eq.h"
#include<iostream>
double R_1(double& r) {
    return r*2.0*std::exp(-r);
}
double R_2(double& r) {
    return r*1.0/std::sqrt(2.0)*(1.0-0.5*r)*std::exp(-r/2.0);
}
double R_3(double& r) {
    return r*2.0/(std::sqrt(3.0)*3.0)*(1.0-2.0/3.0*r+2.0/27.0*std::pow(r,2))*std::exp(-r/3.0);
}
double R_4(double& r) {
    return r*1.0/4.0*(1.0-3.0/4.0*r+1.0/8.0*std::pow(r,2)-1.0/192.0*std::pow(r,3))*std::exp(-r/4.0);
}
int main(int argc, char* argv[]){
    if (argc < 3) {
        std::cerr << "Usage:\n";
        std::cerr << "./analytic rmax dr\n";
        return 1;
    }
    double rmax = std::stod(argv[1]);
    double dr   = std::stod(argv[2]);

    int npoints = (int)(rmax/dr)-1;
    linalg::Vector<double> r(npoints);
    for(int i=0;i<npoints;i++)r[i]=dr*(i+1);
    for(int i = 0; i < npoints; i++) {
            std::cout << r[i]<<" "<<R_1(r[i])<<" "<<R_2(r[i])<<" "<<R_3(r[i])<<" "<<R_4(r[i])<<"\n";
    }
    return 0;
}