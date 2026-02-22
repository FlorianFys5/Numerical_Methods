#pragma once
#include<iostream>
#include<limits>
namespace Vector{
    struct Vec {
        double x{}, y{}, z{};

        constexpr Vec() = default;

        constexpr Vec(double x_, double y_, double z_)
        : x(x_), y(y_), z(z_) {}

        constexpr double norm() const {
            return x*x + y*y + z*z;
        }
        void print(std::string s) const {
            std::cout<<s<<" ("<<x<<","<<y<<","<<z<<")"<<std::endl;
        }
        constexpr Vec& operator+=(const Vec& b) {
            x += b.x; y += b.y; z += b.z;
            return *this;
        }
        constexpr Vec& operator-=(const Vec& b) {
             x -= b.x; y -= b.y; z -= b.z;
            return *this;
        }
        constexpr Vec& operator*=(double s) {
            x *= s; y *= s; z *= s;
            return *this;
        }
        constexpr Vec& operator/=(double s) {
            x /= s; y /= s; z /= s;
            return *this;
        }
    };
    Vec operator+(Vec a, const Vec& b);
    Vec operator-(Vec a, const Vec& b);
    Vec operator*(Vec a, double b);
    Vec operator/(Vec a, double b);
    double dot(const Vec& a, const Vec& b);
    Vec cross(const Vec& a, const Vec& b);
    bool approx(double a, double b, double acc = 1e-9, double eps = 1e-9);
    bool Approx(const Vec& a, const Vec& b);
}
    