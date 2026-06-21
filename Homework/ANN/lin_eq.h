#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <stdexcept>
#include <random>
#include <functional>
#include <limits>
#include<tuple>
#include <algorithm>

namespace linalg {// Vector and Matrix struct are AI generated for convenience

template<typename T>
T conj_if_needed(const T& x) {
    return x; // real case
}

template<>
std::complex<double> conj_if_needed(const std::complex<double>& x) {
    return std::conj(x);
}

template<typename T>
struct Vector {
    std::vector<T> data;

    Vector() = default;

    explicit Vector(size_t n) : data(n, T{}) {}

    Vector(std::initializer_list<T> init) : data(init) {}

    size_t size() const {
        return data.size();
    }

    T& operator[](size_t i) {
        return data[i];
    }

    const T& operator[](size_t i) const {
        return data[i];
    }

    void push_back(const T& value) {
    data.push_back(value);
    }

    Vector operator+(const Vector& other) const {
        if (size() != other.size())
            throw std::runtime_error("Size mismatch in addition");

        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
            result[i] = data[i] + other[i];

        return result;
    }

    Vector operator-(const Vector& other) const {
        if (size() != other.size())
            throw std::runtime_error("Size mismatch in subtraction");

        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
            result[i] = data[i] - other[i];

        return result;
    }

    Vector operator*(const T& scalar) const {
        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
            result[i] = data[i] * scalar;

        return result;
    }

    Vector operator/(const T& scalar) const {
        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
            result[i] = data[i] / scalar;

        return result;
    }

    T dot(const Vector<T>& other) const {
        T result = T{};

        for (size_t i = 0; i < size(); ++i) {
        result += conj_if_needed(data[i]) * other[i];
        }

        return result;
    }

    Vector cross(const Vector& other) const {
        if (size() != 3 || other.size() != 3)
            throw std::runtime_error("Cross product only defined for 3D vectors");

        return Vector{
            data[1]*other[2] - data[2]*other[1],
            data[2]*other[0] - data[0]*other[2],
            data[0]*other[1] - data[1]*other[0]
        };
    }

    double norm() const {
        double sum = 0.0;
        for (const auto& x : data)
            sum += std::norm(x);  // |x|^2 for both real & complex

        return std::sqrt(sum);
    }

    Vector normalized() const {
        double n = norm();
        if (n == 0.0)
            throw std::runtime_error("Cannot normalize zero vector");

        return (*this) / static_cast<T>(n);
    }

    void print(std::ostream& os = std::cout) const {
        os << "(";
        for (size_t i = 0; i < size(); ++i) {
            os << data[i];
            if (i != size() - 1)
                os << ", ";
        }
        os << ")";
    }

    Vector& operator+=(const Vector& other) {
        if (size() != other.size())
            throw std::runtime_error("Size mismatch in +=");

        for (size_t i = 0; i < size(); ++i)
            data[i] += other[i];

        return *this;
    }

    Vector& operator-=(const Vector& other) {
        if (size() != other.size())
            throw std::runtime_error("Size mismatch in -=");

        for (size_t i = 0; i < size(); ++i)
            data[i] -= other[i];

        return *this;
    }

    Vector& operator*=(const T& scalar) {
        for (auto& x : data)
            x *= scalar;

        return * this;
    }

    Vector& operator/=(const T& scalar) {
        for (auto& x : data)
            x /= scalar;

        return *this;
    }
};

template<typename T>
Vector<T> operator*(const T& scalar, const Vector<T>& v) {
    return v * scalar;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
    v.print(os);
    return os;
}

template<typename T>
Vector<T> random_vector(size_t n, std::mt19937& gen ,
                        double min = 0.0, double max = 1.0) {
    
    std::uniform_real_distribution<double> dist(min, max);
    Vector<T> v(n);

    for (size_t i = 0; i < n; ++i)
        v[i] = static_cast<T>(dist(gen));

    return v;
}

template<typename T>
struct Matrix {
    std::vector<Vector<T>> data;
    size_t rows_, cols_;

    Matrix() : rows_(0), cols_(0) {}

    Matrix(size_t rows, size_t cols)
        : data(cols, Vector<T>(rows)), rows_(rows), cols_(cols) {}

    Matrix(std::initializer_list<std::initializer_list<T>> init) {
        rows_ = init.size();
        cols_ = init.begin()->size();

        data.resize(cols_, Vector<T>(rows_));

        size_t i = 0;
        for (const auto& row : init) {
            if (row.size() != cols_)
                throw std::runtime_error("Inconsistent row sizes");

            size_t j = 0;
            for (const auto& val : row) {
                data[j][i] = val;
                ++j;
            }
            ++i;
        }
    }

    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }

    Vector<T>& operator[](size_t j) {
        return data[j];
    }

    const Vector<T>& operator[](size_t j) const {
        return data[j];
    }

    // Element access (i,j)
    T& operator()(size_t i, size_t j) {
        return data[j][i];
    }

    const T& operator()(size_t i, size_t j) const {
        return data[j][i];
    }

    Matrix operator+(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            throw std::runtime_error("Size mismatch");

        Matrix result(rows_, cols_);
        for (size_t j = 0; j < cols_; ++j)
            result[j] = data[j] + other[j];

        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            throw std::runtime_error("Size mismatch");

        Matrix result(rows_, cols_);
        for (size_t j = 0; j < cols_; ++j)
            result[j] = data[j] - other[j];

        return result;
    }

    Matrix operator*(const T& scalar) const {
        Matrix result(rows_, cols_);
        for (size_t j = 0; j < cols_; ++j)
            result[j] = data[j] * scalar;

        return result;
    }

    Matrix operator/(const T& scalar) const {
        Matrix result(rows_, cols_);
        for (size_t j = 0; j < cols_; ++j)
            result[j] = data[j] / scalar;

        return result;
    }

    Vector<T> operator*(const Vector<T>& x) const {
        if (cols_ != x.size())
            throw std::runtime_error("Size mismatch");

        Vector<T> result(rows_);

        for (size_t j = 0; j < cols_; ++j)
            result += data[j] * x[j];

        return result;
    }

    Matrix operator*(const Matrix& B) const {
        if (cols_ != B.rows_)
            throw std::runtime_error("Size mismatch");

        Matrix result(rows_, B.cols_);

        for (size_t j = 0; j < B.cols_; ++j)
            result[j] = (*this) * B[j];

        return result;
    }

    Matrix& operator+=(const Matrix& other) {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            throw std::runtime_error("Size mismatch");

        for (size_t j = 0; j < cols_; ++j)
            data[j] += other[j];

        return *this;
    }

    Matrix& operator-=(const Matrix& other) {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            throw std::runtime_error("Size mismatch");

        for (size_t j = 0; j < cols_; ++j)
            data[j] -= other[j];

        return *this;
    }

    Matrix& operator*=(const T& scalar) {
        for (auto& col : data)
            col *= scalar;
        return *this;
    }

    Matrix& operator/=(const T& scalar) {
        for (auto& col : data)
            col /= scalar;
        return *this;
    }

    Matrix transpose() const {
        Matrix result(cols_, rows_);

        for (size_t i = 0; i < rows_; ++i)
            for (size_t j = 0; j < cols_; ++j)
                result(j, i) = (*this)(i, j);

        return result;
    }

    Matrix<T> dagger() const {
        Matrix<T> result(cols(), rows());

        for (size_t i = 0; i < rows(); ++i)
            for (size_t j = 0; j < cols(); ++j)
                result(j, i) = conj_if_needed((*this)(i, j));

        return result;
    }

    static Matrix identity(size_t n) {
        Matrix I(n, n);
        for (size_t i = 0; i < n; ++i)
            I(i, i) = T{1};
        return I;
    }

    void print(std::ostream& os = std::cout) const {
        for (size_t i = 0; i < rows_; ++i) {
            os << "[ ";
            for (size_t j = 0; j < cols_; ++j)
                os << (*this)(i, j) << " ";
            os << "]\n";
        }
    }
};

template<typename T>
Matrix<T> operator*(const T& scalar, const Matrix<T>& M) {
    return M * scalar;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& M) {
    M.print(os);
    return os;
}

template<typename T>
Matrix<T> outer(const Vector<T>& u, const Vector<T>& v) {
    Matrix<T> result(u.size(), v.size());

    for (size_t i = 0; i < u.size(); ++i) {
        for (size_t j = 0; j < v.size(); ++j) {
            result(i, j) = u[i] * v[j];
        }
    }

    return result;
}

template<typename T>
Matrix<T> outer_hermitian(const Vector<T>& u, const Vector<T>& v) {
    Matrix<T> result(u.size(), v.size());

    for (size_t i = 0; i < u.size(); ++i) {
        for (size_t j = 0; j < v.size(); ++j) {
            result(i, j) = u[i] * std::conj(v[j]);
        }
    }

    return result;
}

template<typename T>
Vector<T> project_vector(const Vector<T>& v, const Vector<T>& u) {
    auto denom = u.dot(u);

    if (denom == T{})
        throw std::runtime_error("Projection onto zero vector");

    return u * (u.dot(v) / denom);
}

template<typename T>
Matrix<T> random_matrix(size_t rows, size_t cols,
                        std::mt19937& gen,
                        double min = 0.0, double max = 1.0) {
    
    std::uniform_real_distribution<double> dist(min, max);
    Matrix<T> M(rows, cols);

    for (size_t j = 0; j < cols; ++j)
        for (size_t i = 0; i < rows; ++i)
            M(i,j) = static_cast<T>(dist(gen));

    return M;
}

template<typename T>
struct QR{
    Matrix<T> Q;
    Matrix<T> R;

    QR(const Matrix<T>& A) {
        Q= A; 
        size_t m =A.cols();
        R= Matrix<T>(m,m) ;
        for (size_t i=0;i<m; i++){
        R(i,i)=Q[i].norm();
        Q[i]/=R(i,i);
        for (size_t j=i+1;j<m; j++){
            R(i,j)=Q[i].dot(Q[j]);
            Q[j]-=Q[i]*R(i,j); 
            } 
        }
    }


    Vector<T> solve(const Vector<T>& b){
        Vector<T> c=Q.dagger()*b;
        int n = R.cols();
        Vector<T> x(n);
        for(int i = n-1; i >= 0; i--){
            T sum=T{0};
            for(int k=i+1; k<n; k++)
                sum+=R(i,k)*x[k];
            x[i]=(c[i]-sum)/R(i,i);
        }
        return x;
    }

    T det(){
        T d=T{1};
        for(size_t i=0; i< R.rows();i++){
            d *= R(i,i);
        }
        return d;
    }

    Matrix<T> inverse(){
        size_t n =Q.rows();
        Matrix<T> inv(n,n);
        Matrix<T> I=Matrix<T>::identity(n);
        for(size_t i=0; i<n;i++){
            Vector<T> col = solve(I[i]);
            inv[i] = col;
        }
        return inv;
    }
};

struct ann{
   int n;
   std::function<double(double)> f;
   std::function<double(double)> dfdx;
   std::function<double(double)> d2fdx2;
   Vector<double> p;
   ann(int m){
    n = m;
    f = [](double x){return x*std::exp(-x*x);};
    dfdx = [](double x){return std::exp(-x*x)*(1.0-2.0*x*x);}; 
    d2fdx2 = [](double x){return std::exp(-x*x)*(4.0*x*x*x-6.0*x);};
    p = Vector<double>(3*n);
    for(size_t i=0;i<p.size();i++) p[i] = 1.0;
   }
   double response(double x){
    return response(x,p);
   }
   double response(double x,const Vector<double>& p){
      double sum = 0;
      for (int i=0;i<n;i++){
        sum += f((x-p[3*i])/p[3*i+1])*p[3*i+2];
      }
      return sum;
     }
    double rd(double x){
      double sum = 0;
      for (int i=0;i<n;i++){
        sum += dfdx((x-p[3*i])/p[3*i+1])*p[3*i+2]/p[3*i+1];
        }
      return sum;
      }
    double rdd(double x){
      double sum = 0;
      for (int i=0;i<n;i++){
        sum += d2fdx2((x-p[3*i])/p[3*i+1])*p[3*i+2]/p[3*i+1]/p[3*i+1];
      }
      return sum;
     }
     double ri(double x){
      double sum = 0;
      for (int i=0;i<n;i++){
        double u = (x-p[3*i])/p[3*i+1];
        sum -= p[3*i+1]*p[3*i+2]/2.0*std::exp(-u*u);
      }
      return sum;
     }
   void train(Vector<double> x,Vector<double> y){
    auto Loss = [this, &x, &y](Vector<double> ps){
        double sum = 0;
        for (size_t i=0;i<x.size();i++){
            double val = (response(x[i],ps)-y[i]);
            sum += val*val;
        }
        return sum/x.size();
    };
    auto Gauss_Newton = [this,&x,&y,Loss](Vector<double> ps){
        int dim = x.size();
        double Lp = Loss(ps);
        for (int iter=0;iter<1000;iter++){
        auto J = Matrix<double>(dim,3*n);
        auto r = Vector<double>(dim);
        for (int i=0;i<dim;i++){
            r[i] = response(x[i],ps)-y[i];
            for (int j=0;j<n;j++){
                double val = (x[i]-ps[3*j])/ps[3*j+1];
                double deriv = dfdx(val);
                J(i,3*j) = deriv*(-1.0*ps[3*j+2]/ps[3*j+1]);
                J(i,3*j+1) = deriv*(-1.0*ps[3*j+2]*val/ps[3*j+1]);
                J(i,3*j+2) = f(val);
            }
        }
        auto JT = J.transpose();
        if ((2.0*JT*r).norm()<1e-5) break;
        double alpha = 1e-3;
        auto Dp = QR(JT*J+alpha*Matrix<double>::identity(3*n)).solve(-1.0*JT*r);
        double λ = 1.0; 
        while (λ >= 1.0/1024.0){       
            if (Loss(ps+λ*Dp) < Lp) {
                alpha/=10.0;
                break;
            } 
            λ /= 2;
        }
        if(Loss(ps+λ*Dp) > Lp) alpha*=10.0;
        ps=ps+λ*Dp;
        Lp=Loss(ps);
        }
        return ps;
    };
    std::mt19937 gen(20);
    for (int i=0;i<10;i++){
        auto ps = random_vector<double>(3*n, gen, -1.0,1.0);
        for (int i=0;i<n;i++){
            if (ps[3*i+1]<0) p[3*i+1]*=-1.0;
            if (ps[3*i+1]<0.2) ps[3*i+1]+=0.2;
        }
        ps = Gauss_Newton(ps);
        if (Loss(ps)<Loss(p)) p=ps;
    }
   }
};

Vector<double> gradient(std::function<double(const Vector<double>&)> f, Vector<double> x, double fx){
    auto gf = Vector<double>(x.size());
    for (size_t i=0; i<x.size();i++){
        auto dxi = (1.0+std::abs(x[i]))*std::pow(2.0,-26.0);
        x[i]+=dxi;
        gf[i]=(f(x)-fx)/dxi;
        x[i]-=dxi;
    }
    return gf;
}

Matrix<double> hessian(std::function<double(const Vector<double>&)> f, Vector<double> x, double fx){
    size_t dim = x.size();
    auto H = Matrix<double>(dim,dim);
    Vector<double> gfx = gradient(f,x,fx);
    for (size_t j=0;j<dim;j++){
        auto dxj=(1.0+std::abs(x[j]))*std::pow(2.0,-13.0);
        x[j]+=dxj;
        double fxj = f(x);
        Vector<double> dgf=gradient(f,x,fxj)-gfx;
        for (size_t i=0;i<dim;i++) H(i,j)=dgf[i]/dxj;
        x[j]-=dxj;
    }
    return H;
}

Vector<double> newton(std::function<double(const Vector<double>&)> f, Vector<double> x, double acc=1e-4, size_t max_iter=1000){ 
    double fx = f(x);
    for(size_t i=0;i<max_iter;i++){              
        auto g = gradient(f,x,fx);
        if (g.norm() < acc) break;
        auto H = hessian(f,x,fx);
        for (size_t j=0;j<H.rows();j++) H(j,j)+=1e-6; // Levenberg regularization
        auto dx = QR(H).solve(-1.0*g);
        double λ = 1.0; 
        while (λ >= 1.0/1024.0){       
            if (f(x+λ*dx) < fx) break; 
            λ /= 2;
        }
        x=x+λ*dx;
        fx=f(x);
    }
    return x;
}

struct ann_func{
   int n;
   std::function<double(double)> f;
   std::function<double(double)> dfdx;
   std::function<double(double)> d2fdx2;
   Vector<double> p;
   ann_func(int m){
    n = m;
    f = [](double x){return x*std::exp(-x*x);};
    dfdx = [](double x){return std::exp(-x*x)*(1.0-2.0*x*x);}; 
    d2fdx2 = [](double x){return std::exp(-x*x)*(4.0*x*x*x-6.0*x);};
    p = Vector<double>(3*n);
    for(size_t i=0;i<p.size();i++) p[i] = 1.0;
   }
   double response(double x){
    return response(x,p);
   }
   double response(double x,const Vector<double>& ps){
      double sum = 0;
      for (int i=0;i<n;i++){
        sum += f((x-ps[3*i])/ps[3*i+1])*ps[3*i+2];
      }
      return sum;
     }
    double rd(double x){
        return rd(x,p);
    }
    double rd(double x, Vector<double> ps){
      double sum = 0;
      for (int i=0;i<n;i++){
        sum += dfdx((x-ps[3*i])/ps[3*i+1])*ps[3*i+2]/ps[3*i+1];
        }
      return sum;
      }
    double rdd(double x){
        return rdd(x,p);
    }
    double rdd(double x, Vector<double> ps){
      double sum = 0;
      for (int i=0;i<n;i++){
        sum += d2fdx2((x-ps[3*i])/ps[3*i+1])*ps[3*i+2]/ps[3*i+1]/ps[3*i+1];
      }
      return sum;
     }
   void train(std::function<double(double y, double yd, double ydd, double x)> phi, double a, double b, double c, double yc, double ydc, double alpha=1.0, double beta=1.0){
    auto x = Vector<double>{};
    double dx = (b-a)/20.0;
    for(double i=a;i<=b;i+=dx) x.push_back(i);
    auto Loss = [this, &x, phi, alpha, beta, c, yc, ydc](Vector<double> ps){
        double sum = 0;
        for (size_t i=0;i<x.size();i++){
            double val = phi(response(x[i],ps),rd(x[i],ps),rdd(x[i],ps),x[i]);
            sum += val*val;
        }
        double b1 = response(c,ps)-yc;
        double b2 = rd(c,ps)-ydc;
        sum += alpha*b1*b1;
        sum += beta*b2*b2;
        return sum;
    };
    std::mt19937 gen(20);
    for (int i=0;i<10;i++){
        auto ps = random_vector<double>(3*n, gen, -1.0,1.0);
        for (int i=0;i<n;i++){
            if (ps[3*i+1]<0) p[3*i+1]*=-1.0;
            if (ps[3*i+1]<0.2) ps[3*i+1]+=0.2;
        }
        ps = newton(Loss,ps);
        if (Loss(ps)<Loss(p)) p=ps;
    }
   }
};

}