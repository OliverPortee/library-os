#ifndef __vec3_h__
#define __vec3_h__

#include "object/o_stream.h"

struct Vec3 {
    double x, y, z;

    Vec3(double x, double y, double z);
    Vec3() = default;
    Vec3(const Vec3&) = default;

    double length() const;
    double length_squared() const;
    Vec3 normalized() const;
    Vec3 operator-() const;
    Vec3& operator+=(const Vec3& v);
    Vec3& operator-=(const Vec3& v);
    Vec3& operator*=(double d);
    Vec3& operator/=(double d);
    void normalize();
    bool near_zero() const;
    Vec3 reflect(const Vec3& normal) const;
    Vec3 refract(const Vec3& normal, double etai_over_etat);

    static Vec3 random_length_smaller_1();
    inline static Vec3 random_unit_vec() {
        return random_length_smaller_1().normalized();
    }
};

Vec3 operator+(const Vec3& a, const Vec3& b);
Vec3 operator-(const Vec3& a, const Vec3& b);
Vec3 operator*(const Vec3& a, double d);
Vec3 operator*(double d, const Vec3& a);
Vec3 operator*(const Vec3& a, const Vec3& b);
Vec3 operator/(const Vec3& a, double d);
bool operator==(const Vec3& a, const Vec3& b);
Vec3 cross(const Vec3& a, const Vec3& b);
double dot(const Vec3& a, const Vec3& b);

double sqrt(double d);

using Point3 = Vec3;

// RGB Color with components normalized to [0,1]
using Color = Vec3;

#endif