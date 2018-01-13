//
// Created by igor on 13.01.18.
//

#include "PhysicsObjectsFactory.h"

std::shared_ptr<b2Body*> PhysicsObjectsFactory::createExampleBox() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);

    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
    return body;
}

std::shared_ptr<b2Body*> PhysicsObjectsFactory::createExampleGround() {
    return b2Body(nullptr, nullptr);
}

PhysicsObjectsFactory &PhysicsObjectsFactory::getInstance() {
    return instance;
}

PhysicsObjectsFactory::PhysicsObjectsFactory(b2World &w) :
    world(w) {

}

PhysicsObjectsFactory &PhysicsObjectsFactory::init(Physics &p) {
    return instance = PhysicsObjectsFactory(p.getWorld());
}

PhysicsObjectsFactory& PhysicsObjectsFactory::operator=(PhysicsObjectsFactory const &other) {
    world = other.world;
    return *this;
}

