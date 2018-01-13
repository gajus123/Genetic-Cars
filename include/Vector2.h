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

        b2Vec2 asb2Vec2() const {return {x, y};}
    };

}

#endif //GENETIC_CARS_VECTOR2_H
