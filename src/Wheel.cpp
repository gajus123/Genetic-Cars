//
// Created by igor on 13.01.18.
//

#include "include/Wheel.h"
#include "include/ObjectsFactory.h"

namespace Objects {
    Wheel::Wheel(Vector2 position, float radius):
        position(position),
        radius(radius),
        body(Physics::ObjectsFactory::getInstance().createCircle(radius, 0.3f, 1.0f)) {

        body->SetTransform(position.asb2Vec2(), 0.0f);
    }

}