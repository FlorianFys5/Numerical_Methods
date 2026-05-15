#include"lin_eq.h"
#include<iostream>
#include<fstream>
double circle(linalg::Vector<double> x){
    if(x[0]*x[0]+x[1]*x[1]<=1){
        return 1;
    }
    else{
        return 0;
    }
}
double ellipsoid(linalg::Vector<double> x){
    if (x[0]*x[0]+x[1]*x[1]/4.0+x[2]*x[2]/9.0<=1){
        return 1;
    }
    else {
        return 0;
    }
}
double func(linalg::Vector<double> x){
    return 1.0/std::numbers::pi/std::numbers::pi/std::numbers::pi
    *1.0/(1.0-std::cos(x[0])*std::cos(x[1])*std::cos(x[2]));
}
int main(){
    linalg::lcg rnd(20);
    auto a = linalg::Vector<double>{-3,-3,-3};
    auto b = linalg::Vector<double>{3,3,3};
    auto [Q,err]=linalg::plainMC(ellipsoid,a,b,10000,rnd);
    std::ofstream file1("Out.txt");
    file1<<"Ellipsoid area= "<<Q<<", Error= "<<err<<", Actual error="<<std::abs(8.0*std::numbers::pi-Q)<<"\n";
    auto a2 = linalg::Vector<double>{-1,-1};
    auto b2 = linalg::Vector<double>{1,1};
    std::ofstream file2("circle.dat");
    for(int N=10;N<=1e7;N*=10){
        linalg::lcg rnd_2(42);
        auto [q,error] = linalg::plainMC(circle,a2,b2,N,rnd_2);
        file2<<N<<" "<<q<<" "<<error<<" "<<std::abs(std::numbers::pi-q)<<"\n";
    }
    std::ofstream file3("circle_quasi.dat");
    for(int N=10;N<=1e7;N*=10){
        auto [q,error] = linalg::quasiMC(circle,a2,b2,N);
        file3<<N<<" "<<q<<" "<<error<<" "<<std::abs(std::numbers::pi-q)<<"\n";
    }
    auto a3 = linalg::Vector<double>{0,0,0};
    auto b3 = linalg::Vector<double>{std::numbers::pi,std::numbers::pi,std::numbers::pi};
    linalg::RNG c_rnd(42);
    auto [Q2,err2]=linalg::plainMC(func,a3,b3,10000,rnd);
    auto [Q3,err3]=linalg::plainMC(func,a3,b3,10000,c_rnd);
    auto [Q4,err4]=linalg::quasiMC(func,a3,b3,10000);
    file1<<"Cos product integral (lcg)= "<<Q2<<", Error= "<<err2<<", Actual error="<<std::abs(1.3932039296856768591842462603255-Q2)<<"\n";
    file1<<"Cos product integral (c++)= "<<Q3<<", Error= "<<err3<<", Actual error="<<std::abs(1.3932039296856768591842462603255-Q3)<<"\n";
    file1<<"Cos product integral (halton)= "<<Q4<<", Error= "<<err4<<", Actual error="<<std::abs(1.3932039296856768591842462603255-Q4)<<"\n";
}