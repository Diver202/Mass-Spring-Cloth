#pragma once
#include <cmath>

struct Vec3{
    float x, y, z;

    Vec3 operator+(const Vec3& other) const {
        return {x + other.x, y + other.y, z + other.z };
    }

    Vec3 operator-(const Vec3& other) const {
        return {x - other.x, y - other.y, z - other.z };
    }

    Vec3 operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    float magnitude() const{
        return sqrt((x*x + y*y + z*z));
    }

    float dot(const Vec3& other) const{
        return (x * other.x, y * other.y , z * other.z);
    }
};