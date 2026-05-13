#include<iostream>
#include "lin_eq.h"
int main(){
    std::vector<double> x, y;  

    for (double xi = 0; xi <= 9; xi += 0.2) { //vector construction AI
        x.push_back(xi);
        y.push_back(std::cos(xi));
    }
    auto qspline = linalg::make_qspline(x,y);
    for(double z=0;z<=9;z+=0.005){
        std::cout<<z<<" "<<qspline(z)<<"\n";
    }
}