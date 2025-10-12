#pragma once

#include <vector>
#include "Model.h"
#include "Camera.h"

/**
 * ワールドクラス
 */
class World {
protected:
    
    // モデルのリスト
    std::vector<Model*> models;

    // カメラ
    Camera* camera;

public:
    World() {}
    ~World() {
        for (auto model : models) {
            delete model;
        }
        models.clear();
    }

    void addModel(Model* model) {
        models.push_back(model);
    }

    void setCamera(Camera* cam) {
        camera = cam;
    }

    const std::vector<Model*>& getModels() const { return models; }
    Camera* getCamera() const { return camera; }
};