
#include "user/raytracer/vec3.h"

#include <cassert>
#include <iostream>
#include <cmath>

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

bool close(double is, double should) {
    return std::abs(should - is) < 0.00001;
}

int main() {
    assert(close(details::sqrt(7676), std::sqrt(7676)));
    Vec3 v1{3, 4, 5};
    Vec3 v2{8, -7, -1};
    assert(v1.length_squared() == 50);
    assert(close(v1.length(), std::sqrt(v1.length_squared())));
    v1.normalize();
    assert(close(v1.length(), 1));
    v2 += Vec3{-1, 1, -1};
    assert(v2 == Vec3(7, -6, -2));
    v2 -= Vec3{-1, 1, -1};
    assert(v2 == Vec3(8, -7, -1));
    v2 *= 2;
    assert(v2 == Vec3(16, -14, -2));
    v2 /= 2;
    assert(v2 == Vec3(8, -7, -1));
    auto v3 = -v2;
    assert(v3.x == -v2.x && v3.y == -v2.y && v3.z == -v2.z);
    assert(v2 + v3 == Vec3{});
    assert(v2 - v3 == Vec3(16, -14, -2));
    assert(v2 * 2 == Vec3(16, -14, -2));
    assert(2 * v2 == Vec3(16, -14, -2));
    assert(v2 / 2 == Vec3(4, -3.5, -0.5));

    Vec3 v4{-4, 2, -5};
    assert(cross(v2, v4) == Vec3(37, 44, -12));
    assert(dot(v2, v4) == -41);
}