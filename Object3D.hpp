//
// Created by Cameron Day on 7/6/23.
//


#ifndef RENDERER_OBJECT3D_HPP
#define RENDERER_OBJECT3D_HPP

#endif //RENDERER_OBJECT3D_HPP

#include "Rect3D.hpp"
#include "Rect.hpp"

#pragma once

struct Object3D{
    Vector3f pos{0, 0, 0};
    Vector3f rotation{0, 0, 0};
    std::vector<Rect3D> rects;
private:


public:
};