#include<iostream>
#include "vec.h"
#include<cmath>
namespace Vector{
    Vec operator+(Vec a, const Vec& b) {
    a += b;
    return a;
}

Vec operator-(Vec a, const Vec& b) {
    a -= b;
    return a;
}

Vec operator*(Vec a, double b){
    a*=b;
    return a;
}

Vec operator/(Vec a, double b){
    a/=b;
    return a;
}

double dot(const Vec& a, const Vec& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
Vec cross(const Vec& a, const Vec& b) {
    return Vec(a.y*b.z-a.z*b.y,
               a.z*b.x-a.x*b.z,
               a.x*b.y-a.y*b.x);
}
bool approx(double a, double b, double acc, double eps) {
    double diff = std::abs(a - b);
    if (diff <= acc) return true;  // absolute tolerance
    double max_ab = std::max(std::abs(a), std::abs(b));
    return diff <= eps * max_ab;   // relative tolerance
}

bool Approx(const Vec& a, const Vec& b){
	if(!approx(a.x,b.x))return false;
	if(!approx(a.y,b.y))return false;
	if(!approx(a.z,b.z))return false;
	return true;
}
}