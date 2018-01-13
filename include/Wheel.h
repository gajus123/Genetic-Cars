//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_WHEEL_H
#define GENETIC_CARS_WHEEL_H

#include "Box2D/Box2D.h"

#include "include/Vector2.h"

namespace Objects {

    class Wheel {
    public:
        Wheel(Vector2 position, float radius);


        float getRadius() const {return radius;}
        Vector2 getPosition() const {return position;}
    private:
        b2Body *body;

        Vector2 position;
        float radius;


    };

}
#endif //GENETIC_CARS_WHEEL_H
