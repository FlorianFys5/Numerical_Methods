#include "lin_eq.h"
#include <iostream>
std::mt19937 gen(20);
int main(){
    auto A=linalg::random_matrix<double>(6,4,gen);
    std::cout<<"A: "<<A<<"\n";
    linalg::QR<double> qr(A);
    auto Q = qr.Q;
    auto R = qr.R;
    std::cout<<"R: "<<R<<"\n";
    linalg::Matrix<double> I_check = Q.transpose()*Q;
    std::cout<<"QT*Q: "<<I_check<<"\n";
    linalg::Matrix<double> A_check = Q*R;
    std::cout<<"Q*R: "<<A_check<<"\n";
    auto B = linalg::random_matrix<double>(5,5,gen);
    auto c = linalg::random_vector<double>(5, gen);
    std::cout<<"B: "<<B<<"\n";
    std::cout<<"c: "<<c<<"\n";
    linalg::QR<double> qr_2(B);
    auto x = qr_2.solve(c);
    std::cout<<"x: "<<x<<"\n";
    linalg::Vector<double> c_check = B*x;
    std::cout<<"B*x: "<<c_check<<"\n";
    double determinant = qr_2.det();
    std::cout<<"det(B): "<<determinant<<"\n";
    linalg::Matrix<double> Inverse = qr_2.inverse();
    std::cout<<"Inverse: "<<Inverse<<"\n";
    auto I = B*Inverse;
    std::cout<<"B*B**(-1): "<<I<<"\n";
}