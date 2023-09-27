//
// Created by Cameron Day on 7/4/23.
//


#ifndef RENDERER_RECT3D_HPP
#define RENDERER_RECT3D_HPP

#endif //RENDERER_RECT3D_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector3.hpp>
#include <cmath>
#include "Rect.hpp"

#pragma once


struct Vertex3{
    Vector3f position;
    sf::Color color{sf::Color::White};
    Vertex3() = default;
    explicit Vertex3(Vector3f pos_){
        position = pos_;
    }
    Vertex3(Vector3f pos_, sf::Color color_){
        position = pos_;
        color = color_;
    }
};


struct Rect3D{

private:

    void applyColor(){
        for(auto & point : points){
            point.color = color;
        }
    }

public:
    Vertex3 points[4];
    Vertex3 drawPoints[4] {};
    Vector3f pos{0, 0, 0};
    sf::Color color{sf::Color::Transparent};
    Vector3f rotation{0, 0, 0};
    const static int pointCount = 4;

    Rect3D() = default;
    Rect3D(Vector3f pos_, Vector2f size_){
        pos = pos_;
        points[0].position = pos_ + Vector3f(-size_.x/2, -size_.y/2, pos_.z);
        points[1].position = pos_ + Vector3f(size_.x/2, -size_.y/2, pos_.z);
        points[2].position = pos_ + Vector3f(size_.x/2, size_.y/2, pos_.z);
        points[3].position = pos_ + Vector3f(-size_.x/2, size_.y/2, pos_.z);
        applyColor();
        rotateAround(pos, rotation);
    }
    Rect3D(Vector3f pos_, Vector3f points_[4]){
        pos = pos_;
        for(int i = 0; i < 4; i++){
            points[i].position = points_[i];
        }
        applyColor();
        rotateAround(pos, rotation);
    }

    void setColor(sf::Color newColor){
        color = newColor;
        applyColor();
    }

    void move(Vector3f delta){
        pos += delta;
        for(auto & point : points){
            point.position += delta;
        }
        for(auto & point : drawPoints){
            point.position += delta;
        }
//        rotateAround(pos, rotation);
    }

    void setPointColor(int index, sf::Color newColor){
        points[index].color = newColor;
    }

    void setPointPos(int index, sf::Vector3f newPos){
        points[index].position = newPos;
    }

    void setPos(sf::Vector3f newPos){
        points[0].position += newPos - pos;
        points[1].position += newPos - pos;
        points[2].position += newPos - pos;
        points[3].position += newPos - pos;
        pos = newPos;
    }

    void setRotation(Vector3f newRotation){
        rotation = newRotation;
        rotateAround(pos, newRotation);
    }

    void rotate(Vector3f radians){
        rotation += radians;
        rotateAround(pos, rotation);
    }

    void rotateAround(Vector3f point, Vector3f rotations){
        for(int i = 0; i < 4; i++){
//            v.position.x = cosf(rotation.x) * v.position.x + pos.x;
//            v.position.y = -cosf(rotation.y) * v.position.y + pos.y;
//            v.position.z = sqrtf(1-powf(cosf(rotation.x), 2)-powf(cosf(rotation.y), 2)) + pos.z;
//            drawPoints[i].position.x = point.x + points[i].position.x * cosf(rotations.x);
//            drawPoints[i].position.z = point.z + points[i].position.z * cosf(rotations.y) * sinf(rotations.x);
//            drawPoints[i].position.y = point.y + points[i].position.y * cosf(rotations.y);

            // NOW USING ROTATION MATRIX

            float m1 [] {points[i].position.x-point.x, points[i].position.y-point.y, points[i].position.z-point.z, 1};
            float x = rotations.z;
            float y = -rotations.x;
            float z = -rotations.y;
            float m2 [] {cosf(x) * cosf(y), cosf(x)*sinf(y)*sinf(z) - sinf(x)*cosf(z), cosf(x)*sinf(y)*cosf(z) + sinf(x)*sinf(z),
                         sinf(x) * cosf(y), sinf(x)*sinf(y)*sinf(z) + cosf(x)*cosf(z), sinf(x)*sinf(y)*cosf(z) - cosf(x)*sinf(z),
                         -sinf(y), cosf(y)*sinf(z), cosf(y)*cosf(z)};
            float* matrix = nullptr;
            matMul(m1, 3, 3, m2, 3, 3, matrix);

            drawPoints[i].position = Vector3f{matrix[0], matrix[1], matrix[2]} + point;
//            std::cout << drawPoints[i].position.x << ", " << drawPoints[i].position.y << ", " << drawPoints[i].position.z << std::endl;
        }
    }

//    Rect render(sf::RenderWindow& window, Vector3f cameraPos){
////        sf::VertexArray orthographicCameraPoints(sf::Quads, 4);
////        sf::VertexArray perspectiveCameraPoints(sf::Quads, 4);
//        Rect orthographicCameraPoints{};
//        Rect perspectiveCameraPoints{};
//        const int orthographicScale = 10;
//        const int perspectiveScale = 100;
//        float z = 0;
//        float closestPoint2 = std::numeric_limits<float>::max();
//        for(int i = 0; i < 4; i++){
//
//            // ORTHOGRAPHIC CAMERA
//            orthographicCameraPoints.setPointPos(i, {(drawPoints[i].position.x - cameraPos.x) * orthographicScale, (drawPoints[i].position.y - cameraPos.y) * orthographicScale});
//            orthographicCameraPoints.setPointPos(i, orthographicCameraPoints[i].position + Vector2f{window.getSize().x / 2.0f, window.getSize().y / 2.0f});
//            orthographicCameraPoints.setPointColor(i, points[i].color);
//
//            // PERSPECTIVE CAMERA
//            float m1 [] {drawPoints[i].position.x - cameraPos.x, -(drawPoints[i].position.y - cameraPos.y), (drawPoints[i].position.z - cameraPos.z), 1};
////            float m1 [] {drawPoints[i].position.x, -drawPoints[i].position.y, -drawPoints[i].position.z, 1};
////            float n = sqrt((drawPoints[i].position.x-cameraPos.x) * (drawPoints[i].position.x-cameraPos.x) + (drawPoints[i].position.y-cameraPos.y) * (drawPoints[i].position.y-cameraPos.y) + (drawPoints[i].position.z-cameraPos.z) * (drawPoints[i].position.z-cameraPos.z));
//            float n = 0; //near
//            float f = 100; //far
////            float m2 [] {n, 0, 0, 0,
////                         0, n, 0, 0,
////                         0, 0, pos.z+n, -n*pos.z,
////                         0, 0, 1, 0};
//            float theta = (180 - 60) * 3.14159265358979323846 / 180;
//            float ratio = float(window.getSize().x) / float(window.getSize().y);
//            float focalLength = 1 / tan(theta/2);
//            float x = focalLength / ratio;
//            float y = -focalLength;
//            float A = n / (f-n);
//            float B = f * A;
//            float w = drawPoints[i].position.z;
//            float m2 [] {
//                                        x,    0.0f,  0.0f, 0.0f,
//                                        0.0f,    -y,  0.0f, 0.0f,
//                                        0.0f, 0.0f,     A,    B,
//                                        0.0f, 0.0f, w, 0.0f,};
//            float m2 [] {1/x, 0, 0, 0,
//                         0, 1/y, 0, 0,
//                         0, 0, 0, -w,
//                         0, 0, 1/A, 1/B};
//            float* matrix1 = nullptr;
////            matMul(m1, 1, 4, m2, 4, 4, matrix1);
//            matMul(m2, 4, 4, m1, 4, 1, matrix1);
////            std::cout << matrix1 << std::endl;
////            for(int k = 0; i < 4; i++){
////                std::cout << matrix1[k] << ", ";
////            }
////            n = matrix1[3];
//            perspectiveCameraPoints.setPointPos(i, {matrix1[0] / w * perspectiveScale, matrix1[1] / w * perspectiveScale});
//            perspectiveCameraPoints.setPointPos(i, perspectiveCameraPoints[i].position + Vector2f{window.getSize().x / 2.0f, window.getSize().y / 2.0f});
//            if(color != sf::Color::Transparent) {
//                orthographicCameraPoints[i].color = color;
//                orthographicCameraPoints.setColor(color);
//                perspectiveCameraPoints[i].color = color;
//                perspectiveCameraPoints.setColor(color);
//            }
//            else {
//                orthographicCameraPoints[i].color = points[i].color;
//                orthographicCameraPoints.setColor(points[i].color);
//                perspectiveCameraPoints[i].color = points[i].color;
//                perspectiveCameraPoints.setColor(points[i].color);
//            }
//            z += matrix1[2] / w;
//            if(matrix1[2] < closestPoint2){
//                closestPoint2 = matrix1[2];
//            }
//            delete [] matrix1;
////            std::cout << perspectiveCameraPoints[i].position.x << ", " << perspectiveCameraPoints[i].position.y << std::endl;
//        }
//        float closestPoint = std::numeric_limits<float>::max();
//        for(auto & drawPoint : drawPoints){
//            if(drawPoint.position.z < closestPoint){
//                closestPoint = drawPoint.position.z;
//            }
//        }
//        orthographicCameraPoints.pos = {(orthographicCameraPoints[0].position.x + orthographicCameraPoints[1].position.x + orthographicCameraPoints[2].position.x + orthographicCameraPoints[3].position.x) / 4.0f,
//                                        (orthographicCameraPoints[0].position.y + orthographicCameraPoints[1].position.y + orthographicCameraPoints[2].position.y + orthographicCameraPoints[3].position.y) / 4.0f,
//                                        closestPoint};
////        return orthographicCameraPoints;
//        perspectiveCameraPoints.pos = {(perspectiveCameraPoints[0].position.x + perspectiveCameraPoints[1].position.x + perspectiveCameraPoints[2].position.x + perspectiveCameraPoints[3].position.x) / 4,
//                                       (perspectiveCameraPoints[0].position.y + perspectiveCameraPoints[1].position.y + perspectiveCameraPoints[2].position.y + perspectiveCameraPoints[3].position.y) / 4,
//                                       closestPoint2};
//        return perspectiveCameraPoints;
//    }
};