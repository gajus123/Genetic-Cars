//
// Created by igor on 13.01.18.
//

#include "include/ObjectsFactory.h"

namespace Physics {

    ObjectsFactory ObjectsFactory::instance;

    ObjectsFactory &ObjectsFactory::init(Loop &p) {
        return instance = ObjectsFactory(p.getWorld());
    }

    ObjectsFactory &ObjectsFactory::getInstance() {
        return instance;
    }


    ObjectsFactory::ObjectsFactory(b2World* w) :
            world(w) {

    }

    ObjectsFactory &ObjectsFactory::operator=(ObjectsFactory const &other) {
        world = other.world;
        return *this;
    }


    b2Body * ObjectsFactory::createExampleBox() {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(0.0f, 4.0f);

        b2Body *body = world->CreateBody(&bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(1.0f, 1.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        body->CreateFixture(&fixtureDef);

        return body;
    }

    b2Body * ObjectsFactory::createExampleGround() {
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, -10.0f);

        b2Body* groundBody = world->CreateBody(&groundBodyDef);

        b2PolygonShape groundBox;
        groundBox.SetAsBox(50.0f, 10.0f);

        groundBody->CreateFixture(&groundBox, 0.0f);

        return groundBody;
    }

    b2Body * ObjectsFactory::createCircle(float32 radius, float32 density, float32 friction) {
        b2Body *body = world->CreateBody(getDefaultBodyDef().get());

        b2CircleShape shape;
        shape.m_p.Set(0.0f, 0.0f);
        shape.m_radius = radius;

        body->CreateFixture(getFixtureDef(shape).get());
        return body;
    }

    b2Body * ObjectsFactory::createPolygon(std::vector<b2Vec2> vertices, float32 density, float32 friction) {
        b2Body* body = world->CreateBody(getDefaultBodyDef().get());

        b2PolygonShape polygon;
        polygon.Set(&vertices[0], (int32)vertices.size());

        body->CreateFixture(getFixtureDef(polygon, density, friction).get());
        return body;
    }

    b2Body * ObjectsFactory::createGround(std::vector<b2Vec2> vertices) {
        b2ChainShape chain;
        chain.CreateChain(&vertices[0], (int32)vertices.size());

        b2BodyDef bodyDef;
        bodyDef.position.Set(0.0f, 0.0f);

        b2Body* body = world->CreateBody(&bodyDef);
        /*body->CreateFixture(&chain, 0.0f);
        return body;*/
		return nullptr;
    }


    std::shared_ptr<const b2BodyDef> ObjectsFactory::getDefaultBodyDef(){
        auto* bodyDef = new b2BodyDef();
        bodyDef->type = b2_dynamicBody;
        bodyDef->position.Set(0.0f, 0.0f);
        return std::shared_ptr<const b2BodyDef>(bodyDef);
    }

    std::shared_ptr<const b2FixtureDef> ObjectsFactory::getFixtureDef(b2Shape& shape, float32 density, float32 friction, int16 groupIndex){
        auto* fixtureDef = new b2FixtureDef();
        fixtureDef->shape = &shape;
        fixtureDef->density = density;
        fixtureDef->friction = friction;
        fixtureDef->filter.groupIndex = groupIndex;

        return std::shared_ptr<const b2FixtureDef>(fixtureDef);
    }


}