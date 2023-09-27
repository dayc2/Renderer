//
// Created by Cameron Day on 7/6/23.
//
#pragma once

#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP

#endif //RENDERER_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "Rect3D.hpp"
#include "Rect.hpp"
#include "Object3D.hpp"

struct Rect3D;

using sf::Vector2f;
using sf::Vector3f;

struct Renderer{
private:
    sf::RenderWindow & window;
    std::vector<Rect> rects{};
    std::vector<Object3D*> objects;
public:
    Vector3f cameraPos{0, 0, 0};
    const static int ORTHOGRAPHIC = 0;
    const static int PERSPECTIVE = 1;
    int mode = PERSPECTIVE;
    //TODO camera rotation
    //TODO FOV

    Renderer() = delete;
    explicit Renderer(sf::RenderWindow &window_) : window(window_) {
    }

    void addObject(Object3D & object){
        objects.push_back(&object);
    }

    void setCameraPos(Vector3f pos){
        cameraPos = pos;
    }

    void render(){
        window.clear();
        rects.clear();
        if(mode == ORTHOGRAPHIC) {
            for (auto &obj: objects) {
                for(auto & rect : obj->rects){
                    rects.push_back(renderOrthographic(rect));
                }
            }
        }
        else if(mode == PERSPECTIVE) {
            for (auto &obj: objects) {
//                auto objs = obj->render(window, cameraPos);
//                rects.insert(rects.end(), objs.begin(), objs.end());
                for(auto & rect : obj->rects) {
                    rects.push_back(renderPerspective(rect));
                }
            }
        }
        if(mode==ORTHOGRAPHIC){
            std::sort(rects.begin(), rects.end(), std::less<>());
            for(auto & rect : rects){
                if(rect.pos.z > cameraPos.z)
                    rect.draw(window);
            }
        }
        else if(mode == PERSPECTIVE){
            std::sort(rects.begin(), rects.end(), std::less<>());
            for(auto & rect : rects){
//                if(rect.pos.z > 0)
                    rect.draw(window);
            }
        }
//        std::sort(rects.begin(), rects.end(), std::greater<>());
//        for(auto & rect : rects){
//            if(mode==PERSPECTIVE)
//                rect.draw(window);
//        }
//        window.display();
    }

    Rect renderOrthographic(Rect3D & rect){
        Vertex3 points[Rect3D::pointCount];
        for(int i = 0; i < Rect3D::pointCount; i++){
            points[i] = rect.drawPoints[i];
        }
        Vector3f center = (points[0].position + points[2].position) / 2.0f;
        if(center.z < cameraPos.z) {
            Vector2f invalidPoints [] {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
            return Rect{{0, 0}, invalidPoints, -1};
        }

        Rect orthographicCameraPoints;
        const float orthographicScale = 10.0f;
        for(int i = 0; i < Rect3D::pointCount; i++){
            orthographicCameraPoints.setPointPos(i, {(points[i].position.x - cameraPos.x) * orthographicScale, -(points[i].position.y - cameraPos.y) * orthographicScale});
            orthographicCameraPoints.setPointPos(i, orthographicCameraPoints[i].position + Vector2f{window.getSize().x / 2.0f, window.getSize().y / 2.0f});
            orthographicCameraPoints.setPointColor(i, points[i].color);
            if(rect.color != sf::Color::Transparent) {
                orthographicCameraPoints[i].color = rect.color;
                orthographicCameraPoints.setColor(rect.color);
            }
            else {
                orthographicCameraPoints[i].color = points[i].color;
                orthographicCameraPoints.setColor(points[i].color);
            }
        }

        float closestPoint = std::numeric_limits<float>::max();
        for(auto & drawPoint : points){
            if(drawPoint.position.z < closestPoint){
                closestPoint = drawPoint.position.z;
            }
        }
        orthographicCameraPoints.pos = center;
//        orthographicCameraPoints.pos = {(orthographicCameraPoints[0].position.x + orthographicCameraPoints[1].position.x + orthographicCameraPoints[2].position.x + orthographicCameraPoints[3].position.x) / 4.0f,
//                                        (orthographicCameraPoints[0].position.y + orthographicCameraPoints[1].position.y + orthographicCameraPoints[2].position.y + orthographicCameraPoints[3].position.y) / 4.0f,
//                                        closestPoint};
        return orthographicCameraPoints;
    }

    Vector3f applyPerspective(Vector3f point, Vector3f objPos){
        float m1 [] {(point.x - cameraPos.x), (point.y - cameraPos.y), (point.z - cameraPos.z), 1};
        float n = 0; //near
        float f = 1; //far
        float theta = 1 * 3.14159265358979323846 / 180;
        float ratio = float(window.getSize().x) / float(window.getSize().y);
        float focalLength = 1 / tanf(theta/2.0f);
        float x = focalLength / ratio;
        float y = -focalLength;
        float A = n / (f-n);
        float B = f * A;
//        float w = point.z;
//        float m2 [] {
//                                    x,    0.0f,  0.0f, 0.0f,
//                                    0.0f,    -y,  0.0f, 0.0f,
//                                    0.0f, 0.0f,     A,    B,
//                                    0.0f, 0.0f, 1, 0.0f,};
        float m2 [] {1/x, 0, 0, 0,
                     0, 1/y, 0, 0,
                     0, 0, 0, point.z,
                     0, 0, 1/A, 1/B};
        float* matrix1 = nullptr;
        matMul(m2, 4, 4, m1, 4, 1, matrix1);
        Vector3f newPoint = {matrix1[0], matrix1[1], matrix1[3]};
        newPoint /= matrix1[2];
        delete [] matrix1;
        return newPoint;
    }

    Rect renderPerspective(Rect3D & rect){
        Vertex3 points[Rect3D::pointCount];
        for(int i = 0; i < Rect3D::pointCount; i++){
            points[i] = rect.drawPoints[i];
        }
        Rect perspectiveCameraPoints{};
        const float perspectiveScale = 100.0f;
        for(int i = 0; i < Rect3D::pointCount; i++){
            points[i].position = applyPerspective(points[i].position, rect.pos) * perspectiveScale;
            perspectiveCameraPoints.setPointPos(i, {points[i].position.x + window.getSize().x / 2.0f, points[i].position.y + window.getSize().y / 2.0f});
            if(rect.color != sf::Color::Transparent) {
                perspectiveCameraPoints[i].color = rect.color;
                perspectiveCameraPoints.setColor(rect.color);
            }
            else {
                perspectiveCameraPoints[i].color = points[i].color;
                perspectiveCameraPoints.setColor(points[i].color);
            }
        }
        perspectiveCameraPoints.pos = (points[0].position + points[2].position) / 2.0f;
        return perspectiveCameraPoints;
    }
};