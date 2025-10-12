#pragma once

#include "Vector3.h"

/**
 * 回転を扱う構造体
 */
struct Rotator
{
    float pitch; // X軸回りの回転 (ラジアン)
    float yaw;   // Y軸回りの回転 (ラジアン)
    float roll;  // Z軸回りの回転 (ラジアン)

    Rotator() : pitch(0), yaw(0), roll(0) {}
    Rotator(float p, float y, float r) : pitch(p), yaw(y), roll(r) {}

    // この回転をベクトルに適用して新しいベクトルを返す
    Vector3 Rotate(const Vector3& v);
};