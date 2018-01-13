//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_BASE_H
#define GENETIC_CARS_BASE_H

#include "Vector2.h"

namespace Objects {

    class Base {
    public:
        explicit Base(Vector2 position = {0.0f, 0.0f}) : start_position(position) {};
        virtual Vector2 getPosition() {return {body->GetPosition()}; }
    protected:
        b2Body* body;
        Vector2 start_position;

        virtual void beforeBodySetUp() = 0;
        virtual void createAndSetBody() = 0;
        virtual void afterBodySetup() {body->SetTransform(start_position.asb2Vec2(), 0.0f);}
    };

}
#endif //GENETIC_CARS_BASE_H
