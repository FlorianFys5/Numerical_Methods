#include "lin_eq.h"
#include<iostream>
#include<fstream>
#include<numbers>
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
    auto NN_func = linalg::ann_func(10);
    NN_func.train([](double y, double yd, double ydd, double x){return ydd+y;},0.0,2.0*std::numbers::pi, 0.0, 1.0, 0.0);
    std::ofstream file3("cos.dat");
    for(double x=-0.2;x<=2.1*std::numbers::pi;x+=0.05){
        file3<<x<<" "<<NN_func.response(x)<<" "<<NN_func.rd(x)<<"\n";
    }
    //The Hessian is quite expensive so the code takes around 5 minutes
}