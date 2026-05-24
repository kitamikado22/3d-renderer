#include "Renderer.h"

 // ワールドをレンダリング
void Renderer::render(const World& world) {
    Camera* camera = world.getCamera();
    if (!camera) return;

    // モデルごとに処理
    const auto& models = world.getModels();
    for (const auto model : models) {
        // ModelをMeshModelにキャスト
        MeshModel* meshModel = dynamic_cast<MeshModel*>(model);
        if (!meshModel) continue;

        // メッシュの三角形を取得して描画
        const auto& triangles = meshModel->getMesh().getTriangles();
        for (const auto& tri : triangles) {
            // 回転
            Vector3 v0 = model->getRotation().Rotate(tri.v0);
            Vector3 v1 = model->getRotation().Rotate(tri.v1);
            Vector3 v2 = model->getRotation().Rotate(tri.v2);

            // 平行移動
            v0 = v0 + model->getPosition();
            v1 = v1 + model->getPosition();
            v2 = v2 + model->getPosition();
            
            // バックフェイスカリング
            Vector3 u = v1 - v0;
            Vector3 v = v2 - v0;
            Vector3 normal = (u ^ v).normalize();
            Vector3 viewDir = (camera->getPosition() - v0).normalize();
            if (normal * viewDir > 0) continue; // 裏面は描かない

            // スクリーン座標に変換
            Vector3 p0 = camera->worldToScreen(v0);
            Vector3 p1 = camera->worldToScreen(v1);
            Vector3 p2 = camera->worldToScreen(v2);

            int minX = std::max(0, (int)std::floor(std::min({p0.x, p1.x, p2.x})));
            int maxX = std::min(screenWidth - 1, (int)std::ceil(std::max({p0.x, p1.x, p2.x})));
            int minY = std::max(0, (int)std::floor(std::min({p0.y, p1.y, p2.y})));
            int maxY = std::min(screenHeight - 1, (int)std::ceil(std::max({p0.y, p1.y, p2.y})));

            auto edge = [](int x0, int y0, int x1, int y1, int x, int y) {
                return (x - x0)*(y1 - y0) - (y - y0)*(x1 - x0);
            };
            float area = edge((int)p0.x, (int)p0.y, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
            if (area == 0) continue; // 面積0はスキップ 

            for (int y = minY; y <= maxY; ++y) {
                for (int x = minX; x <= maxX; ++x) {
                    float w0 = edge((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, x, y);
                    float w1 = edge((int)p2.x, (int)p2.y, (int)p0.x, (int)p0.y, x, y);
                    float w2 = edge((int)p0.x, (int)p0.y, (int)p1.x, (int)p1.y, x, y);

                    if (w0 >= 0 && w1 >= 0 && w2 >= 0) { // 内部にある
                        w0 /= area;
                        w1 /= area;
                        w2 /= area;

                        // 深度補間
                        float z = 1.0f / (w0 / v0.z + w1 / v1.z + w2 / v2.z);

                        int idx = y * screenWidth + x;
                        if (z < zBuffer[idx]) {
                            zBuffer[idx] = z;
                            screenBuffer[idx] = tri.color;
                        }
                    }
                }
            }
        }
    }
}