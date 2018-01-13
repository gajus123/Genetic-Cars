//
// Created by igor on 13.01.18.
//

#include "include/Wheel.h"
#include "include/ObjectsFactory.h"

namespace Objects {

    void Wheel::createAndSetBody() {
        body = Physics::ObjectsFactory::getInstance().createCircle(radius, 1.0f, 0.3f);
    }

}