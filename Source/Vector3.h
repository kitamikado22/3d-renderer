#pragma once

#include <cmath>

/**
 * 3次元ベクトルクラス
 */
struct Vector3 {
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 operator-(const Vector3& v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    Vector3 operator+(const Vector3& v) const {
        return {x + v.x, y + v.y, z + v.z};
    }
    
    // 内積
    float dot(const Vector3& v) const{
        return x*v.x + y*v.y + z*v.z;
    }
    float operator*(const Vector3& v) const {
        return dot(v);
    }

    // 外積
    Vector3 cross(const Vector3& v) const {
        return {y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x};
    }
    Vector3 operator^(const Vector3& v) const {
        return cross(v);
    }

    // 正規化(長さ1にする)
    Vector3 normalize() const {
        float len = std::sqrt(dot(*this));
        return {x / len, y / len, z / len};
    }

    // スカラー倍
    Vector3 operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }
};
