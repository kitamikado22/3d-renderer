#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <algorithm>
#include "GeometricModel.h"
#include "Camera.h"
#include "Renderer.h"
#include "World.h"
#include "Rotator.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const float FOV = 90.0f;    // 視野角（度）
const float Z_NEAR = 0.1f;
const float Z_FAR = 1000.0f;

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("3D Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    // カメラを作成
    Camera camera({0,0,0}, {0,0,0}, FOV, WIDTH, HEIGHT);

    // モデルを作成
    GeometricModel* model;
    model = GeometricModel::createCube();   // 立方体を作成
    model->setPosition({-2,0,5}); // カメラの前に配置
    // モデルを作成
    GeometricModel* model2;
    model2 = GeometricModel::createTetrahedron();   // 四面体を作成
    model2->setPosition({2,0,5}); // カメラの前に配置

    // ワールド作成
    World world;
    world.setCamera(&camera);
    world.addModel(model);
    world.addModel(model2);

    // レンダラー作成
    Renderer renderer3D(world);

    bool running = true;

    // メインループ
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        
        // 画面クリア
        renderer3D.clearBuffers(0xFF000000, Z_FAR);

        // 世界をレンダリング
        renderer3D.render(world);

        // スクリーンバッファの先頭アドレスを取得
        Uint32* screenPixels = const_cast<Uint32*>(renderer3D.getScreenBuffer().data());

        // 描画
        SDL_UpdateTexture(texture, nullptr, screenPixels, WIDTH * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // 約60FPS

        // モデルを回転
        model->setRotation({
            model->getRotation().pitch + 0.01f,
            model->getRotation().yaw + 0.02f,
            model->getRotation().roll
        });
        model2->setRotation({
            model2->getRotation().pitch + 0.02f,
            model2->getRotation().yaw,
            model2->getRotation().roll
        });
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}