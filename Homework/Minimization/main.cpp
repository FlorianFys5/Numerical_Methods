#include "lin_eq.h"
#include<iostream>
#include<fstream>
double Rosenbrock(linalg::Vector<double> x){
    return (1.0-x[0])*(1.0-x[0])+100.0*(x[1]-x[0]*x[0])*(x[1]-x[0]*x[0]);
}
double Himmelblau(linalg::Vector<double> x){
    return (x[0]*x[0]+x[1]-11.0)*(x[0]*x[0]+x[1]-11.0)+(x[0]+x[1]*x[1]-7.0)*(x[0]+x[1]*x[1]-7.0);
}
linalg::Vector<double> energy, signal, error;
void readhiggsdata(){
double x,y,z;
while (std::cin >> x >> y >> z) {
  energy.push_back(x); signal.push_back(y); error.push_back(z);
}
}
double Higgs(linalg::Vector<double> x){
    double sum=0;
    for (size_t i=0;i<energy.size();i++){
        double val = ((std::exp(x[0])/((energy[i]-x[1])*(energy[i]-x[1])+std::exp(x[2])*std::exp(x[2])/4.0)-signal[i])/error[i]);
        sum+=val*val;
    }
    return sum;
}
double BreitWigner(double E, linalg::Vector<double> vals){
    return std::exp(vals[0])/((E-vals[1])*(E-vals[1])+std::exp(vals[2])*std::exp(vals[2])/4.0);
}
int main(){
    readhiggsdata();
    std::ofstream file1("Out.txt");
    auto g1 = linalg::Vector{2.0,2.0};
    auto [min,steps] = linalg::newton(Rosenbrock,g1);
    auto [min2,steps2] = linalg::newton(Himmelblau, g1);
    file1<<"Guess: "<<g1<<"\n";
    file1<<"Rosenbrock minimum: "<<min<<" Error: "<<(linalg::Vector<double>{1.0,1.0}-min).norm()<<" Steps: "<<steps<<"\n";
    file1<<"Himmelblau minimum: "<<min2<<" Error: "<<(linalg::Vector<double>{3.0,2.0}-min2).norm()<<" Steps: "<<steps2<<"\n";
    auto [min3, steps4] = linalg::newton_central(Rosenbrock,g1);
    auto [min4,steps5] = linalg::newton_central(Himmelblau, g1);
    file1<<"Rosenbrock minimum (central difference): "<<min3<<" Error: "<<(linalg::Vector<double>{1.0,1.0}-min3).norm()<<" Steps: "<<steps4<<"\n";
    file1<<"Himmelblau minimum (central difference): "<<min4<<" Error: "<<(linalg::Vector<double>{3.0,2.0}-min4).norm()<<" Steps: "<<steps5<<"\n";
    auto g2 = linalg::Vector{std::log(5.0),125.0,std::log(2.0)};
    auto [vals,steps3] = linalg::newton(Higgs,g2,1e-5,10000);
    file1<<"Guess Higgs: "<<g2<<"\n";
    file1<<"Values: A="<<std::exp(vals[0])<<" m="<<vals[1]<<" Width="<<std::exp(vals[2])<<" Steps: "<<steps3<<"\n";
    std::ofstream file2("fit.dat");
    for (double E=95.0;E<165.0;E+=0.5){
        file2<<E<<" "<<BreitWigner(E,vals)<<"\n";
    }
}