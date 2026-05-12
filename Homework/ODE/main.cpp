#include"lin_eq.h"
#include<iostream>
#include<fstream>
double norm_cubic(double& x1, double& y1, double& x2, double& y2){
    auto vec1 = linalg::Vector<double>{x1,y1};
    auto vec2 = linalg::Vector<double>{x2,y2};
    auto diff = vec1-vec2;
    double norm = diff.norm();
    return norm*(diff[0]*diff[0]+diff[1]*diff[1]);
}
double inv_r3(double x1, double y1,
              double x2, double y2)
{
    double dx = x1 - x2;
    double dy = y1 - y2;

    double r2 = dx*dx + dy*dy + 1e-6;

    return 1.0 / (r2 * std::sqrt(r2));
}
linalg::Vector<double> F(double x, linalg::Vector<double> y){
        x=x;
        auto dydx = linalg::Vector<double>(2);
        dydx[0]=y[1];
        dydx[1]=-y[0];
        return dydx;
    }
linalg::Vector<double> Pendulum(double x, linalg::Vector<double> y){
    double b = 0.25;
    double c = 5.0;
    x=x;
    auto dydx = linalg::Vector<double>(2);
    dydx[0]=y[1];
    dydx[1]=-b*y[1]-c*std::sin(y[0]);
    return dydx;
}
linalg::Vector<double> Planet(double x, linalg::Vector<double> y){
    x=x;
    auto dydx = linalg::Vector<double>(2);
    dydx[0]=y[1];
    dydx[1]=1-y[0];
    return dydx;
}
linalg::Vector<double> Precession(double x, linalg::Vector<double> y){
    x=x;
    auto dydx = linalg::Vector<double>(2);
    dydx[0]=y[1];
    dydx[1]=1+0.01*y[0]*y[0]-y[0];
    return dydx;
}
linalg::Vector<double> three_body(double x, linalg::Vector<double> y){
    x=x;
    auto dydx = linalg::Vector<double>(12);
    double r12 = inv_r3(y[8],y[9],y[6],y[7]);
    double r13 = inv_r3(y[10],y[11],y[6],y[7]);
    double r23 = inv_r3(y[10],y[11],y[8],y[9]);
    dydx[0] = (y[8]-y[6])*r12+(y[10]-y[6])*r13;
    dydx[1] = (y[9]-y[7])*r12+(y[11]-y[7])*r13;
    dydx[2] = (y[6]-y[8])*r12+(y[10]-y[8])*r23;
    dydx[3] = (y[7]-y[9])*r12+(y[11]-y[9])*r23;
    dydx[4] = (y[6]-y[10])*r13+(y[8]-y[10])*r23;
    dydx[5] = (y[7]-y[11])*r13+(y[9]-y[11])*r23;
    dydx[6]=y[0];
    dydx[7]=y[1];
    dydx[8]=y[2];
    dydx[9]=y[3];
    dydx[10]=y[4];
    dydx[11]=y[5];
    return dydx;
}
int main(){
    std::ofstream file1("u.dat");
    std::ofstream file2("pendulum.dat");
    auto y_init = linalg::Vector<double>{0,1};
    auto [xs,ys] = linalg::driver(F,0,7,y_init);
    for(size_t i=0;i<xs.size();i++){
        file1<<xs[i]<<" "<<ys[i][0]<<" "<<ys[i][1]<<"\n";
    }
    auto y_init_pend = linalg::Vector<double>{std::numbers::pi-0.1,0.0};
    auto [xs2,ys2] = linalg::driver(Pendulum,0,10,y_init_pend);
    for(size_t i=0;i<xs2.size();i++){
        file2<<xs2[i]<<" "<<ys2[i][0]<<" "<<ys2[i][1]<<"\n";
    }
    auto u_1 = linalg::Vector<double>{1,1e-3};
    auto u_2 = linalg::Vector<double>{1,-0.5};
    std::ofstream file3("circular.dat");
    std::ofstream file4("elliptic.dat");
    std::ofstream file5("precession.dat");
    auto [xs3,ys3] = linalg::driver(Planet,0,20,u_1,0.125,1e-6,1e-6);
    for(size_t i=0;i<xs3.size();i++){
        file3<<xs3[i]<<" "<<ys3[i][0]<<"\n";
    }
    auto [xs4,ys4] = linalg::driver(Planet,0,20,u_2,0.125,1e-6,1e-6);
    for(size_t i=0;i<xs4.size();i++){
        file4<<xs4[i]<<" "<<ys4[i][0]<<"\n";
    }
    auto [xs5,ys5] = linalg::driver(Precession,0,20,u_2,0.125,1e-6,1e-6);
    for(size_t i=0;i<xs5.size();i++){
        file5<<xs5[i]<<" "<<ys5[i][0]<<"\n";
    }
    std::ofstream file6("three_body.dat");
    auto y3_0 = linalg::Vector<double>{0.466203685,0.43236573,0.466203685,0.43236573,-0.93240737,-0.86473146,-0.97000436,-0.24308753,0.97000436,0.24308753,0.0,0.0};
    auto [xs6,ys6] = linalg::driver(three_body,0,40,y3_0,0.01);
    for(size_t i=0;i<xs6.size();i++){
        file6<<xs6[i]<<" "<<ys6[i][6]<<" "<<ys6[i][7]<<" "<<ys6[i][8]<<" "<<ys6[i][9]<<" "<<ys6[i][10]<<" "<<ys6[i][11]<<"\n";
    }
}