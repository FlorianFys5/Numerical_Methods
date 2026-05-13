#include "lin_eq.h"
#include<iostream>
#include<chrono>
std::mt19937 gen(20);
int main(int argc, char* argv[]){ //I used AI to account for all the different "modes", which was quite cumbersome, so I used fstream afterwards
    if (argc < 4) {
        std::cerr << "Usage:\n";
        std::cerr << "./main mode rmax dr\n";
        return 1;
    }
    std::string mode = argv[1];
    double rmax = std::stod(argv[2]);
    double dr   = std::stod(argv[3]);

    int npoints = (int)(rmax/dr)-1;
    linalg::Vector<double> r(npoints);
    for(int i=0;i<npoints;i++)r[i]=dr*(i+1);
    linalg::Matrix<double> H(npoints,npoints);
    for(int i=0;i<npoints-1;i++){
        H(i,i)  =-2*(-0.5/dr/dr);
        H(i,i+1)= 1*(-0.5/dr/dr);
        H(i+1,i)= 1*(-0.5/dr/dr);
    }
    H(npoints-1,npoints-1)=-2*(-0.5/dr/dr);
    for(int i=0;i<npoints;i++)H(i,i)+=-1/r[i];
    auto [Energies, Eigenfunctions] = linalg::jacobi(H);

    if (mode == "testing") {
    auto A=linalg::random_symmetric(5,gen);
    std::cout<<"A: "<<A<<"\n";
    auto [w,V] = linalg::jacobi(A);
    std::cout<<"w: "<<w<<"\n";
    std::cout<<"V: "<<V<<"\n";
    std::cout<<"V**T*V: "<<V.transpose()*V<<"\n";
    std::cout<<"V*V**T: "<<V*V.transpose()<<"\n";
    auto D=V.transpose()*A*V;
    std::cout<<"D: "<<D<<"\n";
    auto A_test=V*D*V.transpose();
    std::cout<<"A_test: "<<A_test<<"\n";
    }

    else if (mode == "energy") {
        std::cout << rmax << " " << dr << " " << Energies[0] << "\n";
    }

    else if (mode == "wave") {
        auto Norm_eig_func=Eigenfunctions;
        for(size_t i=0;i<Eigenfunctions.rows();i++)
            Norm_eig_func[i]=Eigenfunctions[i].normalized()/std::sqrt(dr);
        for(int i = 0; i < npoints; i++) {
            if (Norm_eig_func(i,i)<0){
                Norm_eig_func[i] *=-1;
            }
            std::cout << r[i];
            for(size_t j = 0; j < Norm_eig_func.cols(); j++)
                std::cout << " " << Norm_eig_func(i,j);
            std::cout << "\n";
        }
    }
    return 0;
}