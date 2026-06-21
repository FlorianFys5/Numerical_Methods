#include "lin_eq.h"
#include<iostream>
#include<fstream>
double func(double x){
    return std::cos(5.0*x-1.0)*std::exp(-x*x);
}
int main(){
    auto x = linalg::Vector<double>{};
    auto y = linalg::Vector<double>{};
    for (double z=-1.0;z<=1.0;z+=0.15){
        x.push_back(z);
        y.push_back(func(z));
    }
    std::ofstream file2("train.dat");
    for (size_t i=0;i<x.size();i++){
        file2<<x[i]<<" "<<y[i]<<"\n";
    }
    auto NN = linalg::ann(10);
    NN.train(x,y);
    std::ofstream file1("plot.dat");
    for(double x=-1.2;x<=1.2;x+=0.05){
        file1<<x<<" "<<NN.response(x)<<" "<<NN.rd(x)<<" "<<NN.rdd(x)<<" "<<NN.ri(x)<<"\n";
    }
}