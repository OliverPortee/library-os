#include "user/raytracer/vec3.h"

#ifndef ISOLATE
#include "object/assert.h"
#else
#include <iostream>

void assert(bool b, const char* c) {
    if (!b) {
        std::cerr << c << std::endl;
        std::exit(1);
    }
}
#endif

namespace details {
// source: https://stackoverflow.com/a/49991852
double sqrt(double d) {
    assert(d >= 0, "sqrt of a negative number");
    double a = 1.0;
    for (unsigned int i = 1; i <= 11; ++i) {
        a -= (a * a - d) / (2 * a);
    }
    return a;
}
}  // namespace details

Vec3::Vec3(double x, double y, double z) : x{x}, y{y}, z{z} {}

double Vec3::length() const { return details::sqrt(length_squared()); }

double Vec3::length_squared() const { return x * x + y * y + z * z; }

Vec3 Vec3::normalized() const { return (*this) / length(); }

Vec3 Vec3::operator-() const { return Vec3{-x, -y, -z}; }

Vec3& Vec3::operator+=(const Vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vec3& Vec3::operator*=(double d) {
    x *= d;
    y *= d;
    z *= d;
    return *this;
}

Vec3& Vec3::operator/=(double d) {
    assert(d != 0, "Vec::operator/=: trying to divide by 0");
    x /= d;
    y /= d;
    z /= d;
    return *this;
}

void Vec3::normalize() { operator/=(length()); }

Vec3 operator+(const Vec3& a, const Vec3& b) {
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator*(const Vec3& a, double d) {
    return Vec3(a.x * d, a.y * d, a.z * d);
}

Vec3 operator*(double d, const Vec3& a) { return a * d; }

Vec3 operator/(const Vec3& a, double d) {
    assert(d != 0, "operator/: trying to divide by 0");
    return Vec3(a.x / d, a.y / d, a.z / d);
}

bool operator==(const Vec3& a, const Vec3& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
}

double dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}