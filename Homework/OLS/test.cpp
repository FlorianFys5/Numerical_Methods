#include "lin_eq.h"
#include <iostream>
#include<cmath>
std::mt19937 gen(20);
int main(){
    auto A = linalg::random_matrix<double>(20,8,gen);
    linalg::QR<double> qr(A);
    auto Q = qr.Q;
    auto R = qr.R;
    std::cout<<"R: "<<R<<"\n";
    linalg::Matrix<double> I_check = Q.transpose()*Q;
    std::cout<<"QT*Q: "<<I_check<<"\n";
    return 0;
}