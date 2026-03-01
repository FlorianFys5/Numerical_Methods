#pragma once
#include<iostream>
#include<limits>
#include<cmath>
namespace Vector{
    template <typename T>
    struct Vec {
        T x{};
        T y{};
        T z{};

        constexpr Vec() = default;

        constexpr Vec(T x_, T y_, T z_)
        : x(x_), y(y_), z(z_) {}

        constexpr T norm2() const {
            return x*x + y*y + z*z;
        }
        T norm() const {
            return std::sqrt(norm2());
        }
        void print(std::string s) const {
            std::cout<<s<<" ("<<x<<","<<y<<","<<z<<")"<<std::endl;
        }
        constexpr Vec<T>& operator+=(const Vec<T>& b) {
            x += b.x; y += b.y; z += b.z;
            return *this;
        }
        constexpr Vec<T>& operator-=(const Vec<T>& b) {
             x -= b.x; y -= b.y; z -= b.z;
            return *this;
        }
        constexpr Vec<T>& operator*=(T s) {
            x *= s; y *= s; z *= s;
            return *this;
        }
        constexpr Vec& operator/=(T s) {
            x /= s; y /= s; z /= s;
            return *this;
        }
    };
    template <typename T>
constexpr Vec<T> operator+(Vec<T> a, const Vec<T>& b) {
    return a += b;
}

template <typename T>
constexpr Vec<T> operator-(Vec<T> a, const Vec<T>& b) {
    return a -= b;
}

template <typename T>
constexpr Vec<T> operator*(Vec<T> a, T s) {
    return a *= s;
}

template <typename T>
constexpr Vec<T> operator/(Vec<T> a, T s) {
    return a /= s;
}

template <typename T>
constexpr T dot(const Vec<T>& a, const Vec<T>& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

template <typename T>
constexpr Vec<T> cross(const Vec<T>& a, const Vec<T>& b) {
    return Vec<T>(
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    );
}
template<typename T>
bool approx(T a, T b, T acc = static_cast<T>(1e-9),T eps = static_cast<T>(1e-9)) {
    T diff = std::abs(a - b);
    if (diff <= acc) return true;  // absolute tolerance
    T max_ab = std::max(std::abs(a), std::abs(b));
    return diff <= eps * max_ab;   // relative tolerance
}
template<typename T>
bool Approx(const Vec<T>& a, const Vec<T>& b){
	if(!approx(a.x,b.x)) return false;
	if(!approx(a.y,b.y)) return false;
	if(!approx(a.z,b.z)) return false;
	return true;
}
}
    