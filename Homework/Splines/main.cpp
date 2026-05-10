#include<iostream>
#include "lin_eq.h"
int main(){
    auto x = linalg::Vector<double>{0.0,0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0,8.5,9.0};
    auto y = linalg::Vector<double>(x.size());
    for(size_t i=0;i<y.size();i++){
        y[i]=std::cos(x[i]);
    }
    for(double z=0;z<=9;z+=0.005){
        std::cout<<z<<" "<<linalg::linterp(x,y,z)<<" "<<linalg::linterpInteg(x,y,z)<<"\n";
    }
}