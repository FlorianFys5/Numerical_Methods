#include "lin_eq.h"
#include <iostream>
#include<cmath>
int main(){
    auto t = linalg::Vector<double>{1.0, 2.0, 3.0, 4.0, 6.0, 9.0, 10.0, 13.0, 15.0};
    auto y = linalg::Vector<double>{117.0, 100.0, 88.0, 72.0, 53.0, 29.5, 25.2, 15.2, 11.1};
    auto dy = linalg::Vector<double>{6.0, 5.0, 4.0, 4.0, 4.0, 3.0, 3.0, 2.0, 2.0};
    std::vector<std::function<double(double)>> fs {
	[](double) { return 1.0; },
	[](double z) { return z; },
	};
    for(size_t i=0; i<t.size();i++){
        dy[i]=dy[i]/y[i]; //error propagation dln(y)/dy*delta_y=1/y*dy
        y[i]=std::log(y[i]);
    }
    auto [c,S] = linalg::lsfit(fs,t,y,dy);
    double t_half=std::log(2)/(-c[1]);
    auto dc = linalg::Vector<double>(c.size());
    for(size_t j=0; j<dc.size();j++){
        dc[j]=std::sqrt(S(j,j));
    }
    double dt=std::log(2)/c[1]/c[1]*dc[1];
    std::cout<<"c: "<<c<<"\n";
    std::cout<<"S: "<<S<<"\n";
    std::cout<<"dc: "<<dc<<"\n";
    std::cout<<"t_half="<<t_half<<" +- "<<dt<<"days"<<"\n";
    return 0;
}