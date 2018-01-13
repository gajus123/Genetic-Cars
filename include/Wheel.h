//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_WHEEL_H
#define GENETIC_CARS_WHEEL_H

#include "Box2D/Box2D.h"

#include "include/Vector2.h"
#include "include/Base.h"

namespace Objects {

    class Wheel : public Base {
    public:
        Wheel(Vector2 position, float radius) : position(position), radius(radius), Base(position) {};


        float getRadius() const {return radius;}
        Vector2 getPosition() const {return position;}

    protected:
        b2Body *body;

        Vector2 position;
        float radius;

        void createAndSetBody() override;
    };

}
#endif //GENETIC_CARS_WHEEL_H
