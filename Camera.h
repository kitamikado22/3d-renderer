#pragma once

#include <SDL2/SDL.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "Vector3.h"
#include "Matrix4.h"
#include "Model.h"

/**
 * カメラクラス
 */
class Camera : public Model {
protected:

    int screenWidth;
    int screenHeight;

    float fov;
    float aspect;

    float nearPlane;
    float farPlane;

public:

    Camera(const Vector3& pos, const Rotator& rot, float fovDeg, int width, int height, float nearP = 0.1f, float farP = 100.0f) 
        : screenWidth(width), screenHeight(height), nearPlane(nearP), farPlane(farP) {
        setPosition(pos);
        setRotation(rot);
        fov = fovDeg * M_PI / 180.0f; // ラジアンに変換
        aspect = float(screenWidth) / screenHeight;
    }

    int getScreenWidth() const { return screenWidth; }
    int getScreenHeight() const { return screenHeight; }

    // ビュー行列を取得
    Matrix4 getViewMatrix() const;
    
    // 射影行列を取得
    Matrix4 getProjectionMatrix() const;

    // 3D座標をスクリーン座標に変換
    Vector3 worldToScreen(const Vector3& worldPos) const;
};
