#include<iostream>
#include<limits>
#include<cmath>
#include<iomanip>
#include"approx.h"
int main(){
    float       f=1.0f; while((float)      (1.0f+f) != 1.0f){f/=2.0f;} f*=2.0f;
    double      d=1.0d; while((double)     (1.0d+d) != 1.0d){d/=2.0d;} d*=2.0d;
    long double l=1.0L; while((long double)(1.0L+l) != 1.0L){l/=2.0L;} l*=2.0L;
    std::cout<<"While loops:"<<"\n";
    std::printf("      float eps=%g\n",f);
    std::printf("     double eps=%g\n",d);
    std::printf("long double eps=%Lg\n",l);
    std::cout<<"System precision:"<<"\n";
    std::cout << "Float: "<<std::numeric_limits<float>::epsilon() << "\n";
    std::cout << "Double: "<<std::numeric_limits<double>::epsilon() << "\n";
    std::cout << "Long double: "<<std::numeric_limits<long double>::epsilon() << "\n";
    std::cout << "Float (std::pow(2,-23)): "<<std::pow(2,-23)<<"\n";
    std::cout << "Double (std::pow(2,-52)): "<<std::pow(2,-52)<<"\n";
    double epsilon=std::pow(2,-52);
    double tiny=epsilon/2;
    double a=1+tiny+tiny;
    double b=tiny+tiny+1;
    std::cout << "a==b ? " << (a==b ? "true":"false") << "\n";
    std::cout << "a>1  ? " << (a>1  ? "true":"false") << "\n";
    std::cout << "b>1  ? " << (b>1  ? "true":"false") << "\n";
    #include<iomanip>
    std::cout << std::fixed << std::setprecision(17);
    std::cout << "       tiny=" << tiny << "\n";
    std::cout << "1+tiny+tiny=" << a << "\n";
    std::cout << "tiny+tiny+1=" << b << "\n";
    std::cout << "1+tiny gets rounded to 1 and again, but tiny+tiny is large enough not to be rounded to 0 so you get something greater than 1"<<"\n";
    double d1 = 0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1;
    double d2 = 8*0.1;
    std::cout << "d1==d2? " << (d1==d2 ? "true":"false") << "\n"; 
    std::cout << std::fixed << std::setprecision(17);
    std::cout << "d1=" << d1 << "\n";
    std::cout << "d2=" << d2 << "\n";
    std::cout << std::boolalpha;
    std::cout << "Approx_func: "<< approx::approx(d1, d2)<<"\n";
}