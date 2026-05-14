#include<iostream>
#include "lin_eq.h"
#include<fstream>
#include<cmath>
double sqrtt(double x){
    return std::sqrt(x);
}
double sqrt_inv(double x){
    return 1.0/std::sqrt(x);
}
double func(double x){
    double arg = 1.0-x*x;
    return std::sqrt(arg);
}
double ln_sqrt(double x){
    return std::log(x)/std::sqrt(x);
}
double erf(double x, double eps=1e-8, double acc=1e-8){
    if (x<0){
        return -erf(-x,eps,acc);
    }
    else if (0.0 <= x && x <= 1.0){
        auto function = [](double x){
            return std::exp(-x*x);
        };
        int eval = 0;
        auto [Q,err] = linalg::integrate(function,0,x,eval,eps,acc);
        return 2.0/std::sqrt(std::numbers::pi)*Q;
    }
    else {
        auto function_2 = [x](double t){
            return std::exp(-(x+(1.0-t)/t)*(x+(1.0-t)/t))/t/t;
        };
        int eval = 0;
        auto [Q,err] = linalg::integrate(function_2,0,1,eval,eps,acc);
        return 1.0-2.0/std::sqrt(std::numbers::pi)*Q;
    }
}
double inf_func(double x){
    return 1/(x*x+1);
}
double inf_func_2(double x){
    return std::exp(-std::abs(x))*std::cos(x);
}
int main(){
    int eval_1=0;
    auto [q1,err1] = linalg::integrate(sqrtt,0,1,eval_1,1e-4,1e-4);
    int eval_2=0;
    auto [q2,err2] = linalg::integrate(sqrt_inv,0,1,eval_2,1e-8,1e-8);
    int eval_3=0;
    auto [q3,err3] = linalg::integrate(func,0,1,eval_3,1e-4,1e-4);
    int eval_4=0;
    auto [q4,err4] = linalg::integrate(ln_sqrt,0,1,eval_4,1e-6,1e-6);
    int eval_5=0;
    auto [q5,err5] = linalg::Clenshaw_Curtis(sqrt_inv,0,1,eval_5,1e-8,1e-8);
    int eval_6=0;
    auto [q6,err6] = linalg::Clenshaw_Curtis(ln_sqrt,0,1,eval_6,1e-6,1e-6);
    std::ofstream file1("Out.txt");
    file1<<"sqrt|1,0= "<<q1<<", Error= "<<err1<<", Actual Error= "<<2.0/3.0-q1<<"\n";
    file1<<"sqrt_inv|1,0= "<<q2<<", Error= "<<err2<<", Evals= "<<eval_2<<"\n";
    file1<<"sqrt_inv|1,0 (Clenshaw-Curtis)= "<<q5<<", Error= "<<err5<<", Evals= "<<eval_5<<"\n";
    file1<<"sqrt_inv|1,0 (Scipy quad)= "<<1.9999999999<<", Error= "<<5.77315972e-15<<", Evals= "<<231<<"\n"; //The scipy evaluations where AI generated
    file1<<"sqrt(1-x*x)|1,0= "<<q3<<", Error= "<<err3<<", Actual Error= "<<std::numbers::pi/4.0-q3<<"\n";
    file1<<"ln/sqrt|1,0= "<<q4<<", Error= "<<err4<<", Evals= "<<eval_4<<"\n";
    file1<<"ln/sqrt|1,0 (Clenshaw-Curtis)= "<<q6<<", Error= "<<err6<<", Evals= "<<eval_6<<"\n";
    file1<<"ln/sqrt|1,0 (Scipy quad)= "<<-4.000000000<<", Error= "<<1.3544720900e-13<<", Evals= "<<315<<"\n";
    std::ofstream file2("erf.dat");
    for (double z=-4;z<=4.0;z+=0.1){
        file2<<z<<" "<<erf(z, 1e-8, 1e-8)<<"\n";
    }
    std::ofstream file3("error.dat");
    for (double ac=0.1;ac>=1e-10;ac*=0.1){
        file3<<ac<<" "<<std::abs(erf(1,0,ac)-0.84270079294971486934)<<"\n";
    }
    int eval_7=0;
    auto [q7,err7] = linalg::inf_int(inf_func,eval_7,1e-8,1e-8);
    int eval_8=0;
    auto [q8,err8] = linalg::inf_int(inf_func_2,eval_8,1e-8,1e-8);
    file1<<"1/(x*x+1)|-inf to inf= "<<q7<<", Error= "<<err7<<", Evals= "<<eval_7<<"\n";
    file1<<"1/(x*x+1)|-inf to inf (Scipy quad)= "<<3.1415926<<", Error= "<<5.1555830e-10<<", Evals= "<<90<<"\n";
    file1<<"exp(-abs(x))*cos(x)|-inf to inf= "<<q8<<", Error= "<<err8<<", Evals= "<<eval_8<<"\n";
    file1<<"exp(-abs(x))*cos(x)|-inf to inf (Scipy quad)= "<<1.0<<", Error= "<<6.22950261e-9<<", Evals= "<<390<<"\n";
}