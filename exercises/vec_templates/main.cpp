#include "vec.h"
#include<iostream>
int main(){
    std::cout<<"Floats"<<std::endl;
    Vector::Vec<float> a(1.f,2.f,3.f);
    Vector::Vec<float> b(2.f,5.f,7.f);
    a.print("a=");
    b.print("b=");
    a+=b;
    std::cout<<"a+b: "<<std::endl;
    a.print("a=");
    std::cout<<"norm(a): "<< a.norm()<<std::endl;
    float d = Vector::dot(a,b);
    std::cout<<"a*b: "<< d<< std::endl;
    Vector::Vec<float> c = Vector::cross(a,b);
    std::cout<<"a x b=c "<<std::endl;
    c.print("c=");
    c-=a;
    std::cout<<"c-a: "<<std::endl;
    c.print("c=");
    b*=5;
    std::cout<<"b*5: "<<std::endl;
    b.print("b=");
    std::cout<<"approx(c,b): "<<Vector::Approx(c,b)<<std::endl;
    std::cout<<"Double"<<std::endl;
    Vector::Vec<double> e(1, 2, 3);
    Vector::Vec<double> f(2, 5, 7);
    e.print("e=");
    f.print("f=");
    e+=f;
    std::cout<<"e+f: "<<std::endl;
    e.print("e=");
    std::cout<<"norm(e): "<< e.norm()<<std::endl;
    double g = Vector::dot(e,f);
    std::cout<<"e*f: "<< g<< std::endl;
    Vector::Vec<double> h = Vector::cross(e,f);
    std::cout<<"e x f=h "<<std::endl;
    h.print("h=");
    h-=e;
    std::cout<<"h-e: "<<std::endl;
    h.print("h=");
    f*=5;
    std::cout<<"f*5: "<<std::endl;
    f.print("f=");
    std::cout<<"approx(h,f): "<<Vector::Approx(h,f)<<std::endl;
}