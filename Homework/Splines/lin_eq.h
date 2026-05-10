#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <stdexcept>
#include <random>
#include <functional>
#include <cstddef>
#include <cassert>

namespace linalg {

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
struct QR {
    Matrix<T> Q;
    Matrix<T> R;

    QR(const Matrix<T>& A) {
        //size_t m = A.rows();
        size_t n = A.cols();

        Q = A;
        R = Matrix<T>(n, n);
        for (size_t i =0;i<n; i++){
            for (size_t j=0;j<i; j++){
                R(j,i) = Q[j].dot(Q[i]);
                Q[i] -= Q[j] * R(j,i); 
            } 
            auto norm = Q[i].norm();
            if (norm == 0.0)
                throw std::runtime_error("Matrix is rank deficient");

            R(i,i) = static_cast<T>(norm);
            Q[i] /= R(i,i);
        }

    }

    Vector<T> solve(const Vector<T>& b){
        Vector<T> c=Q.dagger()*b;
        int n = R.cols();
        Vector<T> x(n);
        for(int i = static_cast<int>(n)-1; i >= 0; i--){
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

std::tuple<Vector<double>,Matrix<double>> lsfit(
    std::vector<std::function<double(double)>>& fs, 
    Vector<double>& x, 
    Vector<double>& y, 
    Vector<double>& dy){
    size_t n = x.size();
    size_t m = fs.size();
    auto A = Matrix<double>(n,m);
    auto b = Vector<double>(n);
    for(size_t i=0; i<n;i++){
        b[i]=y[i]/dy[i];
        for(size_t k=0; k<m; k++){
            A(i,k)=fs[k](x[i])/dy[i];
        }
    }
    QR<double> qr(A);
    auto c = qr.solve(b);
    auto B = A.transpose()*A;
    QR<double> qr_2(B);
    auto Sigma = qr_2.inverse();
    return std::make_tuple(c,Sigma);
}

int binsearch(const Vector<double>& x, double& z)
	{/* locates the interval for z by bisection */ 
	assert( z>=x[0] && z<=x[x.size()-1] );
	int i=0, j=x.size()-1;
	while(j-i>1){
		int mid=(i+j)/2;
		if(z>x[mid]) i=mid; else j=mid;
		}
	return i;
	}

double linterp(Vector<double>& x, Vector<double>& y, double& z){
	int i=binsearch(x,z);
  	double dx=x[i+1]-x[i];
  	assert(dx>0);
  	double dy=y[i+1]-y[i];
  	return y[i]+dy/dx*(z-x[i]);
  	}

double linterpInteg(Vector<double>& x, Vector<double>& y, double& z){
    size_t n = x.size();
    if (z<=x[0]) return 0;
    if (z>=x[n-1]) z=x[n-1];
    double sum=0;
    for(size_t i=0;i<n-1;i++){
        double dx = x[i+1]-x[i];
        double dy = y[i+1]-y[i];
        if(z>x[i+1]){
            sum += y[i]*dx+1.0/2.0*dy*dx;
        }
        else {
            sum += y[i]*(z-x[i])+1.0/2.0*dy/dx*(z-x[i])*(z-x[i]);
            break;
        }
    }
    return sum;
}

using vec=std::vector<double>;
struct qspline{
	const int n;
	vec x,y,b,c;
	qspline(const vec& x, const vec& y)
		: n(x.size()), x(x), y(y), b(n-1), c(n-1)
	{ c[0]=0;
      for(int i=0;i<n-2;i++){
        double dx1=x[i+2]-x[i+1];
        double dx=x[i+1]-x[i];
        double dy1=y[i+2]-y[i+1];
        double dy=y[i+1]-y[i];
        c[i+1]=(dy1/dx1-dy/dx-c[i]*dx)/dx1;
      }
      double ci1=0;
      for(int j=n-3;j>=0;j--){
        double dx1=x[j+2]-x[j+1];
        double dx=x[j+1]-x[j];
        double dy1=y[j+2]-y[j+1];
        double dy=y[j+1]-y[j];
        double ci = (dy1/dx1-dy/dx-ci1*dx1)/dx;
        c[j] = 0.5*(c[j]+ci);
        ci1=ci;
      }
      for(int k=0;k<n-1;k++){
        double dx=x[k+1]-x[k];
        double dy=y[k+1]-y[k];
        b[k]=dy/dx-c[k]*dx;
      }
	}
	int binsearch(double& z){/* locates the interval for z by bisection */ 
	assert( z>=x[0] && z<=x[x.size()-1] );
	int i=0, j=x.size()-1;
	while(j-i>1){
		int mid=(i+j)/2;
		if(z>x[mid]) i=mid; else j=mid;
		}
	return i;
	}
	double eval(double& z){
        int i=binsearch(z);
        return y[i]+b[i]*(z-x[i])+c[i]*(z-x[i])*(z-x[i]);
    }
	double deriv(double& z){
        int i=binsearch(z);
        return b[i]+2.0*c[i]*(z-x[i]);
    }
	double integ(double& z){
        if (z<=x[0]) return 0;
        if (z>=x[n-1]) z=x[n-1];
        double sum=0;
        for(int i=0;i<n-1;i++){
        double dx = x[i+1]-x[i];
        if(z>x[i+1]){
            sum += y[i]*dx+0.5*b[i]*dx*dx+1.0/3.0*c[i]*dx*dx*dx;
        }
        else {
            sum += y[i]*(z-x[i])+0.5*b[i]*(z-x[i])*(z-x[i])+1.0/3.0*c[i]*(z-x[i])*(z-x[i])*(z-x[i]);
            break;
        }
    }
    return sum;
    }
};

int binsearch_2(const vec& x, double& z)
	{/* locates the interval for z by bisection */ 
	assert( z>=x[0] && z<=x[x.size()-1] );
	int i=0, j=x.size()-1;
	while(j-i>1){
		int mid=(i+j)/2;
		if(z>x[mid]) i=mid; else j=mid;
		}
	return i;
	}


std::function<double(double)> make_qspline(vec x,vec y){// x, y are copies
    int n = x.size();
    vec b = vec(n-1);
    vec c = vec(n-1);
	c[0]=0;
    for(int i=0;i<n-2;i++){
        double dx1=x[i+2]-x[i+1];
        double dx=x[i+1]-x[i];
        double dy1=y[i+2]-y[i+1];
        double dy=y[i+1]-y[i];
        c[i+1]=(dy1/dx1-dy/dx-c[i]*dx)/dx1;
    }
    double ci1=0;
    for(int j=n-3;j>=0;j--){
        double dx1=x[j+2]-x[j+1];
        double dx=x[j+1]-x[j];
        double dy1=y[j+2]-y[j+1];
        double dy=y[j+1]-y[j];
        double ci = (dy1/dx1-dy/dx-ci1*dx1)/dx;
        c[j] = 0.5*(c[j]+ci);
        ci1=ci;
    }
    for(int k=0;k<n-1;k++){
        double dx=x[k+1]-x[k];
        double dy=y[k+1]-y[k];
        b[k]=dy/dx-c[k]*dx;
    }
	return [x = std::move(x), y = std::move(y), b = std::move(b), c = std::move(c)]
	(double z){int i=binsearch_2(x,z);
        return y[i]+b[i]*(z-x[i])+c[i]*(z-x[i])*(z-x[i]);};
}
}