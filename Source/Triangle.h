#pragma once

#include <SDL2/SDL.h>
#include "Vector3.h"

/** 
 * 三角形
 */
struct Triangle {
    Vector3 v0, v1, v2;
    Uint32 color;
};