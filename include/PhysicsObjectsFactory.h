//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_PHYSICSOBJECTSFACTORY_H
#define GENETIC_CARS_PHYSICSOBJECTSFACTORY_H


#include <Box2D/Dynamics/b2World.h>

#include "Physics.h"

class PhysicsObjectsFactory {
public:
    PhysicsObjectsFactory(PhysicsObjectsFactory const&) = delete;
    PhysicsObjectsFactory(PhysicsObjectsFactory&&) = delete;

    static PhysicsObjectsFactory& init(Physics& p);
    static PhysicsObjectsFactory& getInstance();

    std::shared_ptr<b2Body*> createExampleBox();
    std::shared_ptr<b2Body*> createExampleGround();

private:
    static PhysicsObjectsFactory instance;

    b2World& world;

    explicit PhysicsObjectsFactory(b2World& w);
    PhysicsObjectsFactory& operator=(PhysicsObjectsFactory const&);


};


#endif //GENETIC_CARS_PHYSICSOBJECTSFACTORY_H
