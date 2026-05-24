#pragma once

#include "Model.h"
#include "MeshComponent.h"

/**
 * 3Dモデルクラス
 */
class MeshModel : public Model {
protected:

    // 見える部分を扱うコンポーネント
    MeshComponent mesh;

public: 

    MeshComponent& getMesh() { return mesh; }

};