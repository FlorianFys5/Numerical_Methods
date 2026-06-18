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
Vector<T> random_vector(size_t n, std::mt19937& gen,
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

std::tuple<Vector<double>,Vector<double>> rkstep23(
	std::function<Vector<double>(double,Vector<double>,double)> f /* the f from dy/dx=f(x,y) */
	,double x                    /* the current value of the variable */
	,Vector<double> y                    /* the current value y(x) of the sought function */
    ,double E
	,double h                     /* the step to be taken */
	)
{
	double alpha = 1.0/3.0;
    double beta = 2.0/3.0; 
    Vector<double> k0 = f(x,y,E);              
	Vector<double> k1 = f(x+alpha*h,y+k0*alpha*h,E); 
    Vector<double> k2 = f(x+beta*h,y+0.5*beta*beta/alpha*k1*h,E);
	Vector<double> yh = y+0.25*k0*h+0.75*k2*h;              /* y(x+h) estimate */
	Vector<double> δy = 0.75*(k0+k2)*h-1.5*k1*h;           /* error estimate */
	return std::make_tuple(yh,δy);
}

std::tuple<Vector<double>,std::vector<Vector<double>>> driver(
	std::function<Vector<double>(double,Vector<double>,double)> F,/* the f from dy/dx=f(x,y) */
	double a,double b,           /* initial-point,final-point */
	Vector<double> yinit,                /* y(initial-point) */
    double E,
	double h=0.125,              /* initial step-size */
	double acc=0.01,             /* absolute accuracy goal */
	double eps=0.01              /* relative accuracy goal */
){
double x=a; Vector<double> y(yinit);
Vector<double> xlist; xlist.push_back(x);
std::vector<Vector<double>> ylist; ylist.push_back(y);
do{
	if(x>=b) return std::make_tuple(xlist,ylist); /* job done */
	if(x+h>b) h=b-x;               /* last step should end at b */
	auto [yh,δy] = rkstep23(F,x,y,E,h);
	double tol = (acc+eps*yh.norm()) * std::sqrt(h/(b-a));
	double err = δy.norm();
	if(err<=tol){ // accept step
		x+=h; y=yh;
		xlist.push_back(x);
		ylist.push_back(y);
		}
	if(err>0) h *= std::min(std::pow(tol/err,0.25)*0.95 , 2.0); // readjust stepsize
	else h*=2;
	}while(true);
}//driver

Matrix<double> Jacobian(std::function<Vector<double>(const Vector<double>&,double,double,double,double)> f,Vector<double> x, Vector<double> fx, double r_min, double r_max, double acc_ode, double eps){
    int n = x.size();
	auto dx = Vector<double>(n); 
    for(int i=0;i<n;i++){
        dx[i]=std::max(std::abs(x[i]),1.0)*std::pow(2.0,-26.0);
    }
	auto J = Matrix<double>(n,n);
	for (int j=0;j<n;j++){
		x[j]+=dx[j];
		Vector<double> df=f(x,r_min,r_max, acc_ode, eps)-fx;
		for (int i=0;i<n;i++){
        J(i,j)=df[i]/dx[j];
        }
        x[j]-=dx[j];
    }
	return J;
}

Vector<double> newton(std::function<Vector<double>(const Vector<double>&,double,double,double,double)> f,Vector<double> x, double r_min, double r_max, double acc_ode, double eps, double acc=1e-2,double alpha_min=1e-3,int max_iter=100){
	Vector<double> fx=f(x, r_min, r_max, acc_ode, eps);
	for(int i=0;i<max_iter;i++){
		if (fx.norm() < acc)  break;
		auto J=Jacobian(f,x,fx,r_min,r_max, acc_ode, eps);
		auto QRJ = QR(J);
		Vector<double> Dx = QRJ.solve(-1.0*fx);
		double alpha=1.0;
		while (true){
			Vector<double> z=x+alpha*Dx;
			Vector<double> fz=f(z,r_min,r_max, acc_ode, eps);
			//if (fz.norm() < (1.0-alpha/2.0)*fx.norm()) break;
			if (fz.norm() < fx.norm()){
                x=z;
                fx=fz;
                break;
            }
			if (alpha < alpha_min){
                x=z;
                fx=fz;
                break;
            } // accept the bad step anyway
			alpha/=2;
        }
    }
	return x;
}

Vector<double> quasiNewton(std::function<Vector<double>(const Vector<double>&,double,double,double,double)> f,Vector<double> x, double r_min, double r_max, double acc_ode, double eps, double acc=1e-2,int max_iter=100){
    Vector<double> fx=f(x, r_min, r_max, acc_ode, eps);
    auto J=Jacobian(f,x,fx,r_min,r_max, acc_ode, eps);
	auto QRJ = QR(J);
    auto B = QRJ.inverse();
    for(int i=0;i<max_iter;i++){
		if (fx.norm() < acc)  break;
        auto Dx = -1.0*B*fx;
        double lambda = 1.0;
        while(f(x+lambda*Dx, r_min, r_max, acc_ode, eps).norm()>(1.0-lambda/2.0)*fx.norm() && lambda>=1.0/128.0) lambda/=2;
        x+=lambda*Dx;
        if (lambda>=1.0/128.0){
                auto Df = f(x, r_min, r_max, acc_ode, eps)-fx;
                Matrix<double> DB= (outer(Dx,Dx)-outer(B*Df,Dx))/(Dx.dot(B*Df))*B;
                B+=DB;
                fx=f(x, r_min, r_max, acc_ode, eps);
            }
        else {
            fx=f(x, r_min, r_max, acc_ode, eps);
            auto J = Jacobian(f,x,fx,r_min,r_max,acc_ode,eps);
            auto QRJ = QR(J);
            B = QRJ.inverse();
        }
    }
    return x;
}

Vector<double> linesearch(std::function<Vector<double>(const Vector<double>&,double,double,double,double)> f,Vector<double> x, double r_min, double r_max, double acc_ode, double eps, double acc=1e-2,double alpha_min=1e-3,int max_iter=100){
	Vector<double> fx=f(x, r_min, r_max, acc_ode, eps);
	for(int i=0;i<max_iter;i++){
		if (fx.norm() < acc)  break;
		auto J=Jacobian(f,x,fx,r_min,r_max, acc_ode, eps);
		auto QRJ = QR(J);
		Vector<double> Dx = QRJ.solve(-1.0*fx);
		double alpha=1.0;
		while (true){
			Vector<double> z=x+alpha*Dx;
			Vector<double> fz=f(z,r_min,r_max, acc_ode, eps);
			if (fz.norm() < (1.0-alpha/2.0)*fx.norm()){
                x=z;
                fx=fz;
                break;
            }
			if (alpha < alpha_min){
                x=z;
                fx=fz;
                break;
            } // accept the bad step anyway
			double c = (0.5*fz.dot(fz)-0.5*fx.dot(fx)+fx.dot(fx)*alpha)/alpha/alpha;
            alpha=fx.dot(fx)/2.0/c;
        }
    }
	return x;
}
}