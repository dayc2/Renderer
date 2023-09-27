//
// Created by Cameron Day on 7/5/23.
//

#ifndef RENDERER_CUBE_HPP
#define RENDERER_CUBE_HPP

#endif //RENDERER_CUBE_HPP

#include "Rect3D.hpp"
#include "Object3D.hpp"

#pragma once

using sf::Vector3f;
using sf::Vector2f;

struct Cube : Object3D{
private:
//    std::vector<Rect3D> rects{6};
    Vector3f points[8];
//    Vector3f rotation{0, 0, 0};

    void initPoints(){
        points[0] = Vector3f{-.5, .5, .5};
        points[1] = Vector3f{.5, .5, .5};
        points[2] = Vector3f{.5, -.5, .5};
        points[3] = Vector3f{-.5, -.5, .5};
        points[4] = Vector3f{-.5, .5, -.5};
        points[5] = Vector3f{.5, .5, -.5};
        points[6] = Vector3f{.5, -.5, -.5};
        points[7] = Vector3f{-.5, -.5, -.5};
    }
public:
//    Vector3f pos{0, 0, 0};

    Cube() = default;
    Cube(Vector3f pos_, float size_) {
        rects.resize(6);
        initPoints();
        for(auto & point : points){
            point *= size_;
        }
        Vector3f squarePoints0[4] = {points[0], points[1], points[2], points[3]};
        rects[0] = {pos, squarePoints0};
        Vector3f squarePoints1[4] = {points[1], points[2], points[6], points[5]};
        rects[1] = {pos, squarePoints1};
        Vector3f squarePoints2[4] = {points[4], points[5], points[6], points[7]};
        rects[2] = {pos, squarePoints2};
        Vector3f squarePoints3[4] = {points[0], points[3], points[7], points[4]};
        rects[3] = {pos, squarePoints3};
        Vector3f squarePoints4[4] = {points[2], points[3], points[7], points[6]};
        rects[4] = {pos, squarePoints4};
        Vector3f squarePoints5[4] = {points[0], points[1], points[5], points[4]};
        rects[5] = {pos, squarePoints5};


//        for(auto & f : points){
//            std::cout << f.x << ", " << f.y << ", " << f.z << std::endl;
//        }

        move(pos_);
    }

    void setFaceColor(int index, sf::Color newColor){
        rects[index].color = newColor;
    }

    void rotate(Vector3f radians){
        rotation += radians;
        for(auto & rect : rects){
            rect.rotateAround(pos, rotation);
        }
    }

    void move(Vector3f delta){
        pos += delta;
        for(auto & rect : rects){
            rect.move(delta);
        }
    }
};