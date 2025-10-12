#pragma once

#include <cmath>
#include "Vector3.h"

/**
 * 4x4行列クラス
 */
struct Matrix4 {

    float m[4][4] = {0};

    // 単位行列を作成
    static Matrix4 identity() {
        Matrix4 mat;
        for (int i = 0; i < 4; i++)
            mat.m[i][i] = 1.0f;
        return mat;
    }

    // 行列の乗算
    Matrix4 operator*(const Matrix4& other) const {
        Matrix4 result = {0};
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    result.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return result;
    }

    //4x4行列とベクトルの乗算
    static Vector3 multiply(const Matrix4& mat, const Vector3& v) {
        float x = v.x * mat.m[0][0] + v.y * mat.m[1][0] + v.z * mat.m[2][0] + mat.m[3][0];
        float y = v.x * mat.m[0][1] + v.y * mat.m[1][1] + v.z * mat.m[2][1] + mat.m[3][1];
        float z = v.x * mat.m[0][2] + v.y * mat.m[1][2] + v.z * mat.m[2][2] + mat.m[3][2];
        float w = v.x * mat.m[0][3] + v.y * mat.m[1][3] + v.z * mat.m[2][3] + mat.m[3][3];
        if (w != 0.0f) {
            x /= w;
            y /= w;
            z /= w;
        }
        return {x, y, z};
    }
};