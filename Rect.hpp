//
// Created by Cameron Day on 7/4/23.
//

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Util.hpp"

#ifndef RENDERER_SQUARE_HPP
#define RENDERER_SQUARE_HPP

#endif //RENDERER_SQUARE_HPP

#pragma once

using sf::Vector2f;
using sf::Vector3f;

struct Rect{
private:
    sf::Vertex points[4];

    void applyColor(){
        for(auto & point : points){
            point.color = color;
        }
    }
public:
    Vector3f pos{0, 0, 0};
    sf::Color color{sf::Color::White};

    Rect() = default;
    Rect(Vector2f pos_, Vector2f size_, float z = 0){
        pos = {pos_.x, pos_.y, z};
        points[0].position = pos_ + Vector2f(-size_.x/2, -size_.y/2);
        points[1].position = pos_ + Vector2f(size_.x/2, -size_.y/2);
        points[2].position = pos_ + Vector2f(size_.x/2, size_.y/2);
        points[3].position = pos_ + Vector2f(-size_.x/2, size_.y/2);
        applyColor();
    }

    Rect(Vector2f pos_, Vector2f points_[4], float z = 0){
        pos = {pos_.x, pos_.y, z};
        for(int i = 0; i < 4; i++){
            points[i].position = points_[i];
        }
        applyColor();
    }

    void setPointColor(int index, sf::Color newColor){
        points[index].color = newColor;
    }

    void setColor(sf::Color newColor){
        color = newColor;
        applyColor();
    }

    void setPointPos(int index, sf::Vector2f newPos){
        points[index].position = newPos;
    }

    void setPos(sf::Vector2f newPos){
        points[0].position += newPos - points[0].position;
        points[1].position += newPos - points[1].position;
        points[2].position += newPos - points[2].position;
        points[3].position += newPos - points[3].position;
        pos = {newPos.x, newPos.y, pos.z};
    }

    void setZ(float newZ){
        pos.z = newZ;
    }

    void draw(sf::RenderWindow& window, Vector2f cameraPos){
        sf::VertexArray cameraPoints(sf::Quads, 4);
        for(int i = 0; i < 4; i++){
            cameraPoints[i] = points[i];
            cameraPoints[i].position -= cameraPos;
            cameraPoints[i].color = points[i].color;
        }
        window.draw(cameraPoints);
    }

    void draw(sf::RenderWindow& window){
//        color.a = 123;
        applyColor();
        window.draw(points, 4, sf::Quads);
    }

    sf::Vertex operator[](int index){
        return points[index];
    }

    bool operator<(const Rect& other) const{
        return pos.z < other.pos.z;
    }

    bool operator>(const Rect& other) const{
        return pos.z > other.pos.z;
    }
};