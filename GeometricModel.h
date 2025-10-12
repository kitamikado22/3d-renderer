#pragma once

#include "MeshModel.h"

/**
 * 幾何モデルクラス
 */
class GeometricModel : public MeshModel {
public:

    // 簡易的に立方体モデルを作成する
    static GeometricModel* createCube() {
        GeometricModel* model = new GeometricModel();
        std::vector<Vector3> cubeVerts = {
            {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1}, // 手前
            {-1,-1, 1}, {1,-1, 1}, {1,1, 1}, {-1,1, 1}  // 奥
        };

        std::vector<Triangle> triangles = {
            // 前面 (-Z)
            {cubeVerts[0], cubeVerts[1], cubeVerts[2], 0xFF0000FF},
            {cubeVerts[0], cubeVerts[2], cubeVerts[3], 0xFF0000FF},
            // 背面 (+Z)
            {cubeVerts[5], cubeVerts[4], cubeVerts[7], 0xFFFF0000},
            {cubeVerts[5], cubeVerts[7], cubeVerts[6], 0xFFFF0000},
            // 左
            {cubeVerts[4], cubeVerts[0], cubeVerts[3], 0xFF00FF00},
            {cubeVerts[4], cubeVerts[3], cubeVerts[7], 0xFF00FF00},
            // 右
            {cubeVerts[1], cubeVerts[5], cubeVerts[6], 0xFFFFFF00},
            {cubeVerts[1], cubeVerts[6], cubeVerts[2], 0xFFFFFF00},
            // 上
            {cubeVerts[3], cubeVerts[2], cubeVerts[6], 0xFFFF00FF},
            {cubeVerts[3], cubeVerts[6], cubeVerts[7], 0xFFFF00FF},
            // 下
            {cubeVerts[4], cubeVerts[5], cubeVerts[1], 0xFF00FFFF},
            {cubeVerts[4], cubeVerts[1], cubeVerts[0], 0xFF00FFFF},
        };

        model->getMesh().setTriangles(triangles);
        return model;
    }

    // 簡易的に四面体モデルを作成する
    static GeometricModel* createTetrahedron() {
        GeometricModel* model = new GeometricModel();
        std::vector<Vector3> verts = {
            {1, 1, 1}, {-1, -1, 1}, {-1, 1, -1}, {1, -1, -1}
        };

        std::vector<Triangle> triangles = {
            {verts[0], verts[1], verts[2], 0xFF0000FF},
            {verts[0], verts[3], verts[1], 0xFFFF0000},
            {verts[0], verts[2], verts[3], 0xFF00FF00},
            {verts[1], verts[3], verts[2], 0xFFFFFF00},
        };

        model->getMesh().setTriangles(triangles);
        return model;
    }
};