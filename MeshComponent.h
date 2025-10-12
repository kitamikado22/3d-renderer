#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Vector3.h"
#include "Triangle.h"

/**
 * 3Dモデルの見える部分を扱うコンポーネント
 */
class MeshComponent {
protected:

    std::vector<Triangle> triangles;

public:

    void setTriangles(const std::vector<Triangle>& tris) {
        triangles = tris;
    }

    const std::vector<Triangle>& getTriangles() const { return triangles; }

};