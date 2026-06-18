#include "lin_eq.h"
#include <iostream>
#include<fstream>
#include<chrono>
linalg::Vector<double> RosenbrockGrad(linalg::Vector<double> x, double r_min, double r_max, double acc_ode, double eps){
    r_min=r_min;
    r_max=r_max;
    acc_ode=acc_ode;
    eps=eps;
    auto Grad = linalg::Vector<double>(2);
    Grad[0]=-2.0*(1.0-x[0])-400.0*x[0]*(x[1]-x[0]*x[0]);
    Grad[1]=200.0*(x[1]-x[0]*x[0]);
    return Grad;
}
linalg::Vector<double> Himmelblau_Grad(linalg::Vector<double> x, double r_min, double r_max, double acc_ode, double eps){
    r_min=r_min;
    r_max=r_max;
    acc_ode=acc_ode;
    eps=eps;
    auto Grad = linalg::Vector<double>(2);
    Grad[0] = 4.0*x[0]*(x[0]*x[0]+x[1]-11.0)+2.0*(x[0]+x[1]*x[1]-7.0);
    Grad[1] = 2.0*(x[0]*x[0]+x[1]-11.0)+4.0*x[1]*(x[0]+x[1]*x[1]-7.0);
    return Grad;
}
linalg::Vector<double> Radial(double r, linalg::Vector<double> y, double E){
    auto dydx = linalg::Vector<double>(2);
    dydx[0]=y[1];
    dydx[1]=-2.0*(E+1.0/r)*y[0];
    return dydx;
}
linalg::Vector<double> M(linalg::Vector<double> E, double r_min,double r_max, double acc_ode, double eps){
    auto y_init = linalg::Vector<double>{r_min-r_min*r_min,1.0-2.0*r_min};
    auto [xs,ys] = linalg::driver(Radial,r_min,r_max,y_init,E[0], 0.125, acc_ode, eps);
    return linalg::Vector<double>{ys[ys.size()-1][0]};
}
double Ground(double r){
    return r*std::exp(-r);
}
int main(){
    auto g1 = linalg::Vector{0.5,1.5};
    auto r1 = linalg::newton(RosenbrockGrad,g1,1,1,1,1,1e-8);
    auto g2 = linalg::Vector{2.5,3.0};
    auto g3 = linalg::Vector{3.0,-2.0};
    auto g4 = linalg::Vector{-3.0,-3.0};
    auto g5 = linalg::Vector{-3.0,3.0};
    auto r2 = linalg::newton(Himmelblau_Grad,g2,1,1,1,1);
    auto r3 = linalg::newton(Himmelblau_Grad,g3,1,1,1,1);
    auto r4 = linalg::newton(Himmelblau_Grad,g4,1,1,1,1);
    auto r5 = linalg::newton(Himmelblau_Grad,g5,1,1,1,1);
    std::ofstream file1("Out.txt");
    file1<<"Real roots Rosenbrock: "<<r1<<"\n";
    file1<<"Guessed: "<<g1<<"\n";
    file1<<"Real roots Himmelblau: "<<r2<<r3<<r4<<r5<<"\n";
    file1<<"Guessed: "<<g1<<g2<<g3<<g4<<g5<<"\n";
    double r_min=1e-3;
    double r_max=8;
    auto y_init = linalg::Vector<double>{r_min-r_min*r_min,1.0-2.0*r_min};
    auto g6 = linalg::Vector{-1.0};
    auto g7 = linalg::Vector{-0.0};
    auto start = std::chrono::high_resolution_clock::now();
    auto r6 = linalg::newton(M,g6,r_min,r_max,0.01,0.01,1e-6);
    auto r7 = linalg::newton(M,g7,r_min,r_max,0.01,0.01,1e-6);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    auto [xs,ys] = linalg::driver(Radial,r_min,r_max,y_init,r6[0]);
    file1<<"Guessed energies: "<<g6<<g7<<"\n";
    file1<<"Energies: "<<r6<<r7<<" Time: "<<duration.count()<<"\n";
    std::ofstream file2("Wavefunction_E0.dat");
    for(size_t i=0;i<xs.size();i++){
        file2<<xs[i]<<" "<<ys[i][0]<<" "<<Ground(xs[i])<<"\n";
    }
    std::ofstream file3("r_min.dat");
    for (double r_min=1.0;r_min>1e-3;r_min/=1.5){
        auto y_init = linalg::Vector<double>{r_min-r_min*r_min,1.0-2.0*r_min};
        auto r6 = linalg::newton(M,g6,r_min,r_max,0.01,0.01,1e-6);
        file3<<r_min<<" "<<r6[0]<<"\n";
    }
    std::ofstream file4("r_max.dat");
    for (double r_max=1.0;r_max<10;r_max*=1.5){
        double r_min=1e-3;
        auto y_init = linalg::Vector<double>{r_min-r_min*r_min,1.0-2.0*r_min};
        auto r6 = linalg::newton(M,g6,r_min,r_max,0.01,0.01,1e-6);
        file4<<r_max<<" "<<r6[0]<<"\n";
    }
    std::ofstream file5("acc.dat");
    for (double acc=1.0;acc>0.0001;acc/=1.5){
        double r_max=8;
        auto y_init = linalg::Vector<double>{r_min-r_min*r_min,1.0-2.0*r_min};
        auto r6 = linalg::newton(M,g6,r_min,r_max,acc,0.01,1e-6);
        file5<<acc<<" "<<r6[0]<<"\n";
    }
    std::ofstream file6("eps.dat");
    for (double eps=1.0;eps>0.0001;eps/=1.5){
        auto y_init = linalg::Vector<double>{r_min-r_min*r_min,1.0-2.0*r_min};
        auto r6 = linalg::newton(M,g6,r_min,r_max,0.01,eps,1e-6);
        file6<<eps<<" "<<r6[0]<<"\n";
    }
    auto start_2 = std::chrono::high_resolution_clock::now();
    auto r8 = linalg::quasiNewton(M,g6,r_min,r_max,0.01,0.01,1e-6);
    auto r10 = linalg::quasiNewton(M,g7,r_min,r_max,0.01,0.01,1e-6);
    auto end_2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_2 = end_2 - start_2;
    file1<<"Quasi-Newton: "<<r8<<r10<<" Time: "<<duration_2.count()<<"\n";
    auto start_3 = std::chrono::high_resolution_clock::now();
    auto r9 = linalg::linesearch(M,g6,r_min,r_max,0.01,0.01,1e-6);
    auto r11 = linalg::newton(M,g7,r_min,r_max,0.01,0.01,1e-6);
    auto end_3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_3 = end_3 - start_3;
    file1<<"Interpolation line search: "<<r9<<r11<<" Time: "<<duration_3.count()<<"\n";
    file1<<"For this small problem the jacobian is not that expensive and a larger number of function evaluations in the quasi newton method could be the resaon for a larger time."<<"\n";
}