#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <stdexcept>
#include <random>

namespace linalg { //most of the Vector and Matrix struct is AI for convenience

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

Matrix<double> random_symmetric(size_t n, std::mt19937& gen,
                                double min = -1.0,
                                double max = 1.0)
{
    Matrix<double> A(n, n);

    std::uniform_real_distribution<double> dist(min, max);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i; j < n; ++j) {
            double val = dist(gen);
            A(i, j) = val;
            A(j, i) = val;
        }
    }

    return A;
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

static void timesJ(Matrix<double>& A, int p, int q, double theta){
	double c=std::cos(theta), s=std::sin(theta);
	for(size_t i=0;i<A.rows();i++){
		double aip=A(i,p),aiq=A(i,q);
		A(i,p)=c*aip-s*aiq;
		A(i,q)=s*aip+c*aiq;
		}
}

static void Jtimes(Matrix<double>& A, int p, int q, double theta){
	double c=std::cos(theta),s=std::sin(theta);
	for(size_t j=0;j<A.rows();j++){
		double apj=A(p,j),aqj=A(q,j);
		A(p,j)= c*apj+s*aqj;
		A(q,j)=-s*apj+c*aqj;
		}
}

std::tuple<Vector<double>,Matrix<double>> jacobi(Matrix<double> A){// "A" is a copy
	int n=A.rows();
	Matrix<double> V=Matrix<double>::identity(n); Vector<double> w(n);
	bool changed;
        do{
	        changed=false;
	        for(int p=0;p<n-1;p++)
	        for(int q=p+1;q<n;q++){
		        double apq=A(p,q), app=A(p,p), aqq=A(q,q);
		        double theta=0.5*std::atan2(2*apq,aqq-app);
		        double c=std::cos(theta),s=std::sin(theta);
		        double new_app=c*c*app-2*s*c*apq+s*s*aqq;
		        double new_aqq=s*s*app+2*s*c*apq+c*c*aqq;
		        if(new_app!=app || new_aqq!=aqq) // do rotation
			    {
			    changed=true;
			    timesJ(A,p,q, theta); // A←A*J 
			    Jtimes(A,p,q,-theta); // A←JT*A 
			    timesJ(V,p,q, theta); // V←V*J
			    }
	        }
        }while(changed);
    for(size_t i=0; i<A.rows(); i++){
        w[i]=A(i,i);
    }
	return std::make_tuple(w,V);
	}//jacobi
}