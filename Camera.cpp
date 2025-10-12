#include "Camera.h"

// ビュー行列を取得
Matrix4 Camera::getViewMatrix() const {
    Vector3 zaxis = forward.normalize(); // カメラの向き
    Vector3 xaxis = up.cross(zaxis).normalize(); // 右方向
    Vector3 yaxis = zaxis.cross(xaxis); // 上方向

    Matrix4 view = Matrix4::identity();
    view.m[0][0] = xaxis.x; view.m[1][0] = xaxis.y; view.m[2][0] = xaxis.z; view.m[3][0] = -xaxis.dot(position);
    view.m[0][1] = yaxis.x; view.m[1][1] = yaxis.y; view.m[2][1] = yaxis.z; view.m[3][1] = -yaxis.dot(position);
    view.m[0][2] = zaxis.x; view.m[1][2] = zaxis.y; view.m[2][2] = zaxis.z; view.m[3][2] = -zaxis.dot(position);
    return view;
}

// 射影行列を取得
Matrix4 Camera::getProjectionMatrix() const {
    Matrix4 proj = {0};
    float f = 1.0f / tan(fov / 2);
    proj.m[0][0] = f / aspect;
    proj.m[1][1] = f;
    proj.m[2][2] = (farPlane + nearPlane) / (nearPlane - farPlane);
    proj.m[2][3] = -1.0f;
    proj.m[3][2] = (2 * farPlane * nearPlane) / (nearPlane - farPlane);
    return proj;
}

// 3D座標をスクリーン座標に変換
Vector3 Camera::worldToScreen(const Vector3& worldPos) const {
    Matrix4 view = getViewMatrix();
    Matrix4 proj = getProjectionMatrix();
    Matrix4 vp = proj * view;
    
    Vector3 clipSpacePos = Matrix4::multiply(vp, worldPos);

    // NDCに変換
    Vector3 ndcPos = {clipSpacePos.x, clipSpacePos.y, clipSpacePos.z};

    // スクリーン座標に変換
    return {
        (ndcPos.x + 1) * 0.5f * screenWidth,
        (1 - (ndcPos.y + 1) * 0.5f) * screenHeight,
        ndcPos.z
    };
}