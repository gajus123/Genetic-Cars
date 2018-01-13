//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_VECTOR2_H
#define GENETIC_CARS_VECTOR2_H

#include "Box2D/Box2D.h"

namespace Objects {

    class Vector2 {
    public:
        float x, y;

        Vector2(float x, float y) : x(x), y(y) {};
        explicit Vector2(b2Vec2 other): x(other.x), y(other.y) {};

        b2Vec2 asb2Vec2() const {return {x, y};}

        Vector2 operator*(const float scalar) const { return {x*scalar, y*scalar}; }
        Vector2 operator+(const Vector2& other) const { return {x+other.x, y+other.y}; }
        Vector2 operator-(const Vector2& other) const { return {x-other.x, y-other.y}; }

        Vector2 operator+=(const Vector2& other) {x += other.x, y += other.y; return *this;}
        Vector2 operator-=(const Vector2& other) {x -= other.x, y -= other.y; return *this;}
        Vector2 operator-=(const float& scalar) {x *= scalar, scalar; return *this;}

    };

}

#endif //GENETIC_CARS_VECTOR2_H
