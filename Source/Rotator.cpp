#include "Rotator.h"

// この回転をベクトルに適用して新しいベクトルを返す
Vector3 Rotator::Rotate(const Vector3& v)
{
    // 回転行列を順に適用する
    // Roll（Z軸回転）
    float cz = std::cos(roll);
    float sz = std::sin(roll);
    float x1 = v.x * cz - v.y * sz;
    float y1 = v.x * sz + v.y * cz;
    float z1 = v.z;

    // Pitch（X軸回転）
    float cx = std::cos(pitch);
    float sx = std::sin(pitch);
    float x2 = x1;
    float y2 = y1 * cx - z1 * sx;
    float z2 = y1 * sx + z1 * cx;

    // Yaw（Y軸回転）
    float cy = std::cos(yaw);
    float sy = std::sin(yaw);
    float x3 = x2 * cy + z2 * sy;
    float y3 = y2;
    float z3 = -x2 * sy + z2 * cy;

    return Vector3(x3, y3, z3);
}