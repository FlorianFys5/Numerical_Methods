#include "lin_eq.h"
#include<iostream>
#include<fstream>
double Gauss(double x, double magnitude = 10.0, double center = 6.0, double var = 2.0){
    return magnitude*std::exp(-(x-center)*(x-center)/2.0/var/var);
}
double step_function(double x, double y=3.0){
    if(x<y) return -1.0;
    else return 1.0;
}
double linear(double x, double y0 = 2.0, double h = 1.8){
    return x*h+y0;
}
double cos_amp(double x, double A = 2.0){
    return A*std::cos(x);
}
double condition_number(linalg::Matrix<double> A){
    auto AI = linalg::QR(A).inverse();
    double sum1 = 0;
    double sum2 = 0;
    for (size_t i=0; i<A.rows();i++){// I use the Frobenius norm to make a quick estimate of the condition number
        for (size_t j=0; j<A.cols();j++){
            sum1+=A(i,j)*A(i,j);
            sum2+=AI(i,j)*AI(i,j);
        }
    }
    return std::sqrt(sum1)*std::sqrt(sum2); 
}
std::mt19937 gen(42);
int main(){
    auto x = linalg::Vector<double>{};
    auto y_gauss = linalg::Vector<double>{};
    auto y_step = linalg::Vector<double>{};
    auto y_linear = linalg::Vector<double>{};
    auto y_cos = linalg::Vector<double>{};
    for (double p=-5.0;p<=5.0;p+=0.1){
        x.push_back(p);
        y_gauss.push_back(Gauss(p, 10.0, 0.0));
        y_step.push_back(step_function(p));
        y_linear.push_back(linear(p));
        y_cos.push_back(cos_amp(p));
    }
    size_t dim = x.size();
    auto B = linalg::Matrix<double>(dim,dim);
    B(0,0)=0.8;
    B(0,1)=0.2;
    B(dim-1,dim-1)=0.8;
    B(dim-1,dim-2)=0.2;
    for (size_t i = 1; i<dim-1;i++){
        B(i,i)=0.6;
        B(i,i-1)=0.2;
        B(i,i+1)=0.2;
    }
    double sigma = 0.1;
    auto noise = linalg::random_vector<double>(dim, gen, 0.0, sigma);
    auto y = B*y_gauss+noise;
    //I use |y_found-y_unlurred| as an estimate for the error
    std::ofstream file1("Out.txt");
    file1<<"Original data: "<<y_gauss<<"\n";
    file1<<"Blurred data: "<<y<<"\n";
    auto [y1,alpha1] = linalg::regularized_deconvolution(B, y, linalg::Regularization::Identity, sigma*sigma);
    auto [y4,alpha4] = linalg::regularized_deconvolution(B, y, linalg::Regularization::Identity);
    auto [y7,alpha7] = linalg::regularized_deconvolution(B, y, linalg::Regularization::Identity, std::nullopt, y_gauss);
    auto [y2,alpha2] = linalg::regularized_deconvolution(B, y, linalg::Regularization::First_derivative, sigma*sigma);
    auto [y5,alpha5] = linalg::regularized_deconvolution(B, y, linalg::Regularization::First_derivative);
    auto [y8,alpha8] = linalg::regularized_deconvolution(B, y, linalg::Regularization::First_derivative, std::nullopt, y_gauss);
    auto [y3,alpha3] = linalg::regularized_deconvolution(B, y, linalg::Regularization::Second_derivative, sigma*sigma);
    auto [y6,alpha6] = linalg::regularized_deconvolution(B, y, linalg::Regularization::Second_derivative);
    auto [y9,alpha9] = linalg::regularized_deconvolution(B, y, linalg::Regularization::Second_derivative, std::nullopt, y_gauss);
    file1<<"No regularization error: "<<(linalg::QR(B).solve(y)-y_gauss).norm()<<"\n";
    file1<<"Deconvoluted data error (Identity/with variance): "<<(y1-y_gauss).norm()<<" |B*y_found-y|= "<<(B*y1-y).norm()<<" sqrt(dim*var)= "<<std::sqrt(dim*sigma*sigma)<<" alpha: "<<alpha1<<"\n";
    file1<<"Deconvoluted data error (Identity/GCV): "<<(y4-y_gauss).norm()<<" |B*y_found-y|= "<<(B*y4-y).norm()<<" alpha: "<<alpha4<<"\n";
    file1<<"Deconvoluted data error (Identity/Exact): "<<(y7-y_gauss).norm()<<" |B*y_found-y|= "<<(B*y7-y).norm()<<" alpha: "<<alpha7<<"\n";
    file1<<"Deconvoluted data error (First/with variance): "<<(y2-y_gauss).norm()<<" |B*y_found-y|= "<<(B*y2-y).norm()<<" alpha: "<<alpha2<<"\n";
    file1<<"Deconvoluted data error (First/GCV): "<<(y5-y_gauss).norm()<<" |B*y_found-y|= "<<(B*y5-y).norm()<<" alpha: "<<alpha5<<"\n";
    file1<<"Deconvoluted data error (First/Exact): "<<(y8-y_gauss).norm()<<" |B*y_found-y|= "<<(B*y8-y).norm()<<" alpha: "<<alpha8<<"\n";
    file1<<"Deconvoluted data error (Second/with variance): "<<(y3-y_gauss).norm()<<" |B*y_found-y|= "<<(B*y3-y).norm()<<" alpha: "<<alpha3<<"\n";
    file1<<"Deconvoluted data error (Second/GCV): "<<(y6-y_gauss).norm()<<" |B*y_found-y|= "<<(B*y6-y).norm()<<" alpha: "<<alpha6<<"\n";
    file1<<"Deconvoluted data error (Second/Exact): "<<(y9-y_gauss).norm()<<" |B*y_found-y|= "<<(B*y9-y).norm()<<" alpha: "<<alpha9<<"\n";
    //Now I investigate how it performs for different data
    auto y_s = B*y_step+noise;
    auto y_l = B*y_linear+noise;
    auto y_c = B*y_cos+noise;
    auto [y_lin,alpha_lin] = linalg::regularized_deconvolution(B, y_l, linalg::Regularization::Identity);
    auto [y_lin_2,alpha_lin_2] = linalg::regularized_deconvolution(B, y_l, linalg::Regularization::First_derivative);
    auto [y_lin_3,alpha_lin_3] = linalg::regularized_deconvolution(B, y_l, linalg::Regularization::Second_derivative);
    auto [y_st,alpha_st] = linalg::regularized_deconvolution(B, y_s, linalg::Regularization::Identity);
    auto [y_st_2,alpha_st_2] = linalg::regularized_deconvolution(B, y_s, linalg::Regularization::First_derivative);
    auto [y_st_3,alpha_st_3] = linalg::regularized_deconvolution(B, y_s, linalg::Regularization::Second_derivative);
    auto [y_co,alpha_co] = linalg::regularized_deconvolution(B, y_c, linalg::Regularization::Identity);
    auto [y_co_2,alpha_co_2] = linalg::regularized_deconvolution(B, y_c, linalg::Regularization::First_derivative);
    auto [y_co_3,alpha_co_3] = linalg::regularized_deconvolution(B, y_c, linalg::Regularization::Second_derivative);
    file1<<"Linear data error (Identity/GCV): "<<(y_lin-y_linear).norm()<<" |B*y_found-y|= "<<(B*y_lin-y_l).norm()<<" alpha: "<<alpha_lin<<"\n";
    file1<<"Linear data error (First/GCV): "<<(y_lin_2-y_linear).norm()<<" |B*y_found-y|= "<<(B*y_lin_2-y_l).norm()<<" alpha: "<<alpha_lin_2<<"\n";
    file1<<"Linear data error (Second/GCV): "<<(y_lin_3-y_linear).norm()<<" |B*y_found-y|= "<<(B*y_lin_3-y_l).norm()<<" alpha: "<<alpha_lin_3<<"\n";
    file1<<"Step data error (Identity/GCV): "<<(y_st-y_step).norm()<<" |B*y_found-y|= "<<(B*y_st-y_s).norm()<<" alpha: "<<alpha_st<<"\n";
    file1<<"Step data error (First/GCV): "<<(y_st_2-y_step).norm()<<" |B*y_found-y|= "<<(B*y_st_2-y_s).norm()<<" alpha: "<<alpha_st_2<<"\n";
    file1<<"Step data error (Second/GCV): "<<(y_st_3-y_step).norm()<<" |B*y_found-y|= "<<(B*y_st_3-y_s).norm()<<" alpha: "<<alpha_st_3<<"\n";
    file1<<"Cosine data error (Identity/GCV): "<<(y_co-y_cos).norm()<<" |B*y_found-y|= "<<(B*y_co-y_c).norm()<<" alpha: "<<alpha_co<<"\n";
    file1<<"Cosine data error (First/GCV): "<<(y_co_2-y_cos).norm()<<" |B*y_found-y|= "<<(B*y_co_2-y_c).norm()<<" alpha: "<<alpha_co_2<<"\n";
    file1<<"Cosine data error (Second/GCV): "<<(y_co_3-y_cos).norm()<<" |B*y_found-y|= "<<(B*y_co_3-y_c).norm()<<" alpha: "<<alpha_co_3<<"\n";
    //Now I investigate the effects of B
    std::ofstream file2("blurring.dat");
    auto B1 = linalg::Matrix<double>(dim,dim);
    auto D = linalg::Matrix<double>(dim-2,dim);
        for (size_t i=0;i<D.rows();i++){//Assumes equal spacing of points
            D(i,i) = 1.0;
            D(i,i+1) = -2.0;
            D(i,i+2) = 1.0;
        }
    for (double s = 0.1; s<5.0;s+=0.3){
        for (size_t i = 0;i<dim;i++){
            double sum = 0;
            for (size_t j = 0;j<dim;j++){
                double d = static_cast<double>(i)-static_cast<double>(j);
                B1(i,j)=std::exp(-d*d/2.0/s/s);
                sum += B1(i,j);
            }
            for (size_t j = 0;j<dim;j++) B1(i,j)/=sum;
        }
        auto [y_g, alpha] = linalg::regularized_deconvolution(B1,y,linalg::Regularization::Second_derivative);
        double cn = condition_number(B1);
        file2<<s<<" "<<(y_g-y_gauss).norm()<<" "<<alpha<<" "<<cn<<" "<<(D*y_g).norm()<<"\n";
    }
    //Now I investigate the effects of the noise
    std::ofstream file3("noise.dat");
    for (double sigma=0.001; sigma<8.0;sigma*=2){
        std::mt19937 gen(42);
        auto noise = linalg::random_vector<double>(dim, gen, 0.0, sigma);
        auto y = B*y_gauss+noise;
        auto [y_g, alpha] = linalg::regularized_deconvolution(B,y,linalg::Regularization::Second_derivative);
        file3<<sigma<<" "<<(y_g-y_gauss).norm()<<" "<<alpha<<"\n";
    }
    //Lastly I compare how the two different applications perform for the second derivative and varying datasize
    std::ofstream file4("size.dat");
    std::ofstream file5("sizegcv.dat");
    for (double size = 10; size <=320;size*=2.0){
        double xmin = -6.0;
        double xmax = 6.0;
        auto x = linalg::Vector<double>{};
        auto y0 = linalg::Vector<double>{};
        for (double pos = xmin; pos < xmax; pos+=(xmax-xmin)/size){
            x.push_back(pos);
            y0.push_back(cos_amp(pos));
        }
        size_t dim = x.size();
        std::mt19937 gen(42);
        auto noise = linalg::random_vector<double>(dim, gen, 0.0, 0.05);
        auto B = linalg::Matrix<double>(dim,dim);
        for (size_t i = 0; i<dim; i++){
            double sum = 0;
            for (size_t j = 0; j<dim; j++){
                double d = static_cast<double>(i)-static_cast<double>(j);
                B(i,j)=std::exp(-d*d/(2.0*0.1*0.1));
                sum += B(i,j);
            }
            for (size_t j = 0; j<dim; j++) B(i,j)/=sum;
        }
        auto y = B*y0+noise;
        auto [y_GCV, alpha_GCV] = linalg::regularized_deconvolution(B,y,linalg::Regularization::Second_derivative);
        auto [y_var, alpha_var] = linalg::regularized_deconvolution(B,y,linalg::Regularization::Second_derivative, 0.05*0.05);
        file4<<size<<" "<<(y_var-y).norm()<<" "<<alpha_var<<"\n";
        file5<<size<<" "<<(y_GCV-y).norm()<<" "<<alpha_GCV<<"\n";
    }
}