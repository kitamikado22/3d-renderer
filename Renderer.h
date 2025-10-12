#pragma once

#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Camera.h"
#include "Model.h"
#include "World.h"
#include "MeshComponent.h"
#include "MeshModel.h"

/**
 * 3Dレンダリングの処理をするクラス
 */
class Renderer {
protected:

    int screenWidth;
    int screenHeight;

    std::vector<Uint32> screenBuffer;
    std::vector<float> zBuffer;

public:
    Renderer(const World& world) {
        // ワールドのカメラ情報から画面サイズを取得
        Camera* camera = world.getCamera();
        if (camera) {
            screenBuffer.resize(camera->getScreenWidth() * camera->getScreenHeight(), 0x00000000);
            zBuffer.resize(camera->getScreenWidth() * camera->getScreenHeight(), 1000.0f);
            screenWidth = camera->getScreenWidth();
            screenHeight = camera->getScreenHeight();
        }
    }

    const std::vector<Uint32>& getScreenBuffer() const { return screenBuffer; }
    const std::vector<float>& getZBuffer() const { return zBuffer; }

    void clearBuffers(Uint32 clearColor = 0x00000000, float clearDepth = 1000.0f) {
        std::fill(screenBuffer.begin(), screenBuffer.end(), clearColor);
        std::fill(zBuffer.begin(), zBuffer.end(), clearDepth);
    }

    // ワールドをレンダリング
    void render(const World& world);
};