#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <stdexcept>
#include <random>
#include <functional>
#include <limits>
#include<tuple>

namespace linalg {// Vector and Matrix struct are AI generated

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

std::tuple<double,double> integrate(std::function<double(double)> f, double a, double b, int& evals, double acc=0.001,double eps=0.001, double f2 = std::numeric_limits<double>::quiet_NaN(), double f3 = std::numeric_limits<double>::quiet_NaN()){
    double h = b-a;
    if (std::isnan(f2)){
        f2=f(a+h/3.0); evals++;
        f3=f(a+2.0*h/3.0); evals++;
    }
    double f1 = f(a+h/6.0); evals++;
    double f4 = f(a+5.0*h/6.0); evals++;
    double Q = (2.0*f1+f2+f3+2.0*f4)/6.0*(b-a);
    double q = (f1+f2+f3+f4)/4.0*(b-a);
    double err = std::abs(Q-q);
    double tol = acc+eps*std::abs(Q);
    if (err<tol){
        return std::make_tuple(Q,err);
    }
    else {
        double midt = (a+b)/2.0;
        if (midt == a || midt == b){ //This recursion safety net is AI
            return std::make_tuple(Q,err);
        }
        auto [Q1,err1] = integrate(f, a, midt, evals, acc/std::sqrt(2),eps, f1, f2);
        auto [Q2,err2] = integrate(f, midt, b, evals, acc/std::sqrt(2),eps, f3, f4);
        return std::make_tuple(Q1+Q2,std::sqrt(err1*err1+err2*err2));
    }
}

std::tuple<double,double> Clenshaw_Curtis(std::function<double(double)> f, double a, double b,int& evals, double acc=0.001,double eps=0.001, double f2 = std::numeric_limits<double>::quiet_NaN(), double f3 = std::numeric_limits<double>::quiet_NaN()){
    auto func = [a,b,f] (double x){
        double t = (a+b)/2.0+(b-a)/2.0*std::cos(x);
        if (std::abs(t) < 1e-15) // This safety not to get to close to the singularities is AI
            t = 1e-15;
        return f(t)*std::sin(x)*(b-a)/2.0;
    };
    return integrate(func,0,std::numbers::pi,evals,acc,eps,f2,f3);
}

std::tuple<double,double> inf_int(std::function<double(double)> f,int& evals, double acc=0.001,double eps=0.001, double f2 = std::numeric_limits<double>::quiet_NaN(), double f3 = std::numeric_limits<double>::quiet_NaN()){
    auto func = [f] (double x){
        return f(x/(1-x*x))*(1+x*x)/(1-x*x)/(1-x*x);
    };
    return Clenshaw_Curtis(func,-1,1,evals,acc,eps,f2,f3);
}

struct lcg{
    double a;
    double c;
    double m;
    double seed;
    lcg (double seeds, double as=1664525, double cs=1013904223, double ms=std::pow(2,32)){
        a=as;
        c=cs;
        m=ms;
        seed=seeds;
    }

    double operator()(){
        seed=std::fmod(a*seed+c,m);
        return (seed+1)/(m+1);
    }
};

struct RNG{ //This RNG standard C++ randomizer is AI generated

    std::mt19937 engine;
    std::uniform_real_distribution<double> dist;

    RNG(unsigned seed = 42)
        : engine(seed), dist(0.0,1.0)
    {}

    double operator()(){
        return dist(engine);
    }
};

template<typename Random>
std::tuple<double,double> plainMC(std::function<double(Vector<double>)> f, Vector<double> a, Vector<double> b, int N, Random& random_double){
    int dim = a.size();
    double V = 1;
    for (int i=0;i<dim;i++){
        V*=b[i]-a[i];
    }
    double sum = 0;
    double sum2 = 0;
    for (int j=0;j<N;j++){
        auto x = Vector<double>(dim);
        for (int i=0;i<dim;i++){
            x[i]=a[i]+random_double()*(b[i]-a[i]);
        }
        double fx = f(x);
        sum+=fx;
        sum2+=fx*fx;
    }
    double mean = sum/N;
    double sigma = std::sqrt(sum2/N-mean*mean);
    return std::make_tuple(mean*V,sigma*V/std::sqrt(N));
}

Vector<int> prime_numbers(size_t n){
    auto primes = Vector<int>{};
    int candidate = 2;
    while (primes.size()<n){
        bool candidate_is_prime=true;
        for(size_t i=0;i<primes.size();i++){
            if (primes[i]*primes[i]>candidate){
                break;
            }
            else if (candidate%primes[i]==0){
                candidate_is_prime=false;
                break;
            }
        }
        if (candidate_is_prime){
                primes.push_back(candidate);
            }
        candidate+=1;
    }
    return primes;
}

double corput(int n, int b=2){
    double q=0;
    double bk=1.0/b;
    while (n>0){
        q+=(n%b)*bk;
        n/=b;
        bk/=b;
    }
    return q;
}

struct Halton{
    Vector<int> bases;
    Halton(int dim){
        bases=prime_numbers(dim);
    }
    Vector<double> x(int n){
        auto Vec=Vector<double>(bases.size());
        for(size_t i=0;i<Vec.size();i++){
            Vec[i]=corput(n,bases[i]);
        }
        return Vec;
    }
};

std::tuple<double,double> quasiMC(std::function<double(Vector<double>)> f, Vector<double> a, Vector<double> b, int N){
    int dim = a.size();
    double V = 1;
    for (int i=0;i<dim;i++){
        V*=b[i]-a[i];
    }
    double sum1 = 0;
    double sum2 = 0;
    Halton h(dim);
    for (int j=1;j<N;j++){
        auto x1 = Vector<double>(dim);
        auto x2 = Vector<double>(dim);
        auto rnd1 = h.x(j);
        auto rnd2 = h.x(j+N);
        for (int i=0;i<dim;i++){
            x1[i]=a[i]+rnd1[i]*(b[i]-a[i]);
            x2[i]=a[i]+rnd2[i]*(b[i]-a[i]);
        }
        sum1+=f(x1);
        sum2+=f(x2);
    }
    double q1 = sum1*V/N;
    double q2 = sum2*V/N;
    return std::make_tuple(q1,std::abs(q1-q2));
}

template<typename Random>
std::tuple<double,double> strata(std::function<double(const Vector<double>&)> f, Vector<double> a, Vector<double> b, int N, Random& random_double, int nmin){
    if (N<nmin) return plainMC(f, a, b, N, random_double);
    int dim = a.size();
    auto n_left = Vector<int>(dim);
    auto n_right = Vector<int>(dim);
    auto x = Vector<double>(dim);
    auto mean_left = Vector<double>(dim);
    auto mean_right = Vector<double>(dim);
    auto sum_left = Vector<double>(dim);
    auto sum_right = Vector<double>(dim);
    for(int i=0;i<N;i++){
        for(int j=0;j<dim;j++){
            x[j]=a[j]+random_double()*(b[j]-a[j]);
        }
        double fx = f(x);
        for(int j=0;j<dim;j++){
            if (x[j]>(a[j]+b[j])/2){
                n_right[j]++;
                mean_right[j]+=fx;
                sum_right[j]+=fx*fx;
            }
            else {
                n_left[j]++;
                mean_left[j]+=fx;
                sum_left[j]+=fx*fx;
            }
        }
    }
    for(int i=0;i<dim;i++){
        if(n_left[i]>0) mean_left[i]/=n_left[i];
        if(n_right[i]>0) mean_right[i]/=n_right[i];
    }
    int kdiv=0;
    double maxvar=0;
    for(int i=0;i<dim;i++){
        double var = std::fabs(mean_right[i]-mean_left[i]);
        if (var>maxvar){
            maxvar=var; 
            kdiv=i;
        }
    }
    auto a2 = a;
    auto b2 = b;
    a2[kdiv]=(a[kdiv]+b[kdiv])/2.0;
    b2[kdiv]=(a[kdiv]+b[kdiv])/2.0;
    int N_left;
    int N_right;
    if (n_left[kdiv]==0 || n_right[kdiv]==0){
        N_left = N/2;
        N_right = N-N_left;
    }
    else {
        double sigma_left = std::sqrt(sum_left[kdiv]/n_left[kdiv]-mean_left[kdiv]*mean_left[kdiv]);
        double sigma_right = std::sqrt(sum_right[kdiv]/n_right[kdiv]-mean_right[kdiv]*mean_right[kdiv]);
        double sigma = sigma_left+sigma_right;
        N_left=N/sigma*sigma_left;
        N_right=N-N_left;
        N_left = std::max(1,N_left);
        N_right = std::max(1,N_right);
    }
    auto [Q1, err1] = strata (f,a,b2,N_left,random_double,nmin);
    auto [Q2, err2] = strata(f,a2,b,N_right,random_double,nmin);
    return std::make_tuple(Q1+Q2,std::sqrt(err1*err1+err2*err2));
}
}