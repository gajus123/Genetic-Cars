//
// Created by igor on 13.01.18.
//

#include <physics/objects/ObjectsFactory.h>

namespace Physics {

    ObjectsFactory ObjectsFactory::instance;

    ObjectsFactory &ObjectsFactory::init(b2World* w) {
        return instance = ObjectsFactory(w);
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
        body->CreateFixture(&chain, DEFAULT_FRICTION);
        return body;
    }

	b2RevoluteJoint * ObjectsFactory::createJoint(Objects::Base& a, Objects::Base& b, b2Vec2 point)
	{
		b2RevoluteJointDef jointDef;
		jointDef.Initialize(a.body_, b.body_, point);
		jointDef.enableMotor = true;
		jointDef.maxMotorTorque = MAX_MOTOR_TORQUE;
		jointDef.motorSpeed = MOTOR_SPEED;
		b2RevoluteJoint * joint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
		return joint;
	}

	void ObjectsFactory::destroyBody(Objects::Base & body)
	{
		world->DestroyBody(body.body_);
	}

	void ObjectsFactory::destroyJoint(b2RevoluteJoint * joint)
	{
		world->DestroyJoint(joint);
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