#pragma once

#include "Vector3.h"
#include "Rotator.h"

/**
 * 3D空間上に配置できる基底クラス
 */
class Model {
protected:

    Vector3 position;
    Rotator rotation; // オイラー角 (ラジアン)

    Vector3 forward;    // 前方向：正規化されていること
    Vector3 up;     // 上方向：正規化されていること
    Vector3 right;  // 右方向：正規化されていること

public:
    Model() : position(0,0,0), rotation(0,0,0), forward(0,0,1), up(0,1,0), right(-1,0,0) {}
    virtual ~Model() {}

    void setPosition(const Vector3& pos) { position = pos; }
    Vector3 getPosition() const { return position; }

    void setRotation(const Rotator& rot) { 
        rotation = rot;
        // 回転に基づき方向ベクトルを更新
        forward = rotation.Rotate(Vector3(0,0,1)).normalize();
        up = rotation.Rotate(Vector3(0,1,0)).normalize();
        right = up.cross(forward).normalize();
    }
    Rotator getRotation() const { return rotation; }
    Vector3 getForward() const { return forward; }
    Vector3 getUp() const { return up; }
    Vector3 getRight() const { return right; }
};
