#include "vec.h"
#include<iostream>
int main(){
    Vector::Vec a(1,2,3);
    Vector::Vec b(2,5,7);
    a.print("a=");
    b.print("b=");
    a+=b;
    std::cout<<"a+b: "<<std::endl;
    a.print("a=");
    std::cout<<"norm(a): "<< a.norm()<<std::endl;
    double d = Vector::dot(a,b);
    std::cout<<"a*b: "<< d<< std::endl;
    Vector::Vec c=Vector::cross(a,b);
    std::cout<<"a x b=c "<<std::endl;
    c.print("c=");
    c-=a;
    std::cout<<"c-a: "<<std::endl;
    c.print("c=");
    b*=5;
    std::cout<<"b*5: "<<std::endl;
    b.print("b=");
    std::cout<<"approx(c,b): "<<Vector::Approx(c,b)<<std::endl;
    std::cout<<"Operator overload print:"<<std::endl;
    std::cout<<b;
}