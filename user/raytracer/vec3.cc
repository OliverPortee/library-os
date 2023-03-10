#include "user/raytracer/vec3.h"

#ifndef ISOLATE
#include "library/random.h"
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

// source: https://stackoverflow.com/a/49991852
double sqrt(double d) {
    assert(d >= 0, "sqrt of a negative number");
    double a = 1.0;
    for (unsigned int i = 1; i <= 11; ++i) {
        a -= (a * a - d) / (2 * a);
    }
    return a;
}

double power(double base, int exp) {
    double result = base;
    for (int i = 0; i < exp; i++)
    {
        result *= base;
    }
    return result;   
}

#define ABS(x) ((x) < 0 ? -(x) : (x))

Vec3::Vec3(double x, double y, double z) : x{x}, y{y}, z{z} {}

double Vec3::length() const { return sqrt(length_squared()); }

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

bool Vec3::near_zero() const {
    const double s = 1e-8;
    return ABS(x) < s && ABS(y) < s && ABS(z) < s;
}

Vec3 Vec3::reflect(const Vec3& normal) const {
    return (*this) - 2 * dot(*this, normal) * normal;
}

Vec3 Vec3::refract(const Vec3& normal, double etai_over_etat) {
    Vec3 uv = *this;
    auto cosine_theta = 1.0;
    double dotp = dot(-uv, normal);
    // assign cosine_theta the minimum of 1.0 and dot(-uv, normal)
    if (dotp < cosine_theta) cosine_theta = dotp; 

    // parts of the refracted ray (ray prime) that are perpendicular to the normal (n prime) 
    Vec3 refrac_ray_perpendicular = etai_over_etat * (uv + cosine_theta * normal);
    // parts of the refracted ray (ray prime) that are parallel to the normal (n prime) 
    Vec3 refrac_ray_parallel = -sqrt(ABS(1.0 - refrac_ray_perpendicular.length_squared())) * normal;

    return refrac_ray_parallel + refrac_ray_perpendicular;
}

Vec3 random_vec(double min, double max) {
    return Vec3{random.random_double(min, max), random.random_double(min, max),
                random.random_double(min, max)};
}

Vec3 Vec3::random_length_smaller_1() {
    Vec3 result;
    do {
        result = random_vec(-1, 1);
    } while (result.length_squared() >= 1.0);
    return result;
}

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

Vec3 operator*(const Vec3& a, const Vec3& b) {
    return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

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