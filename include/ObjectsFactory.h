//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_PHYSICSOBJECTSFACTORY_H
#define GENETIC_CARS_PHYSICSOBJECTSFACTORY_H

#include <QtMath>

#include <Box2D/Dynamics/b2World.h>
#include "Box2D/Box2D.h"
#include <vector>
#include "Loop.h"
#include "include/Base.h"

namespace Objects {
	class Base;
}


namespace Physics {

	const float MAX_MOTOR_TORQUE = 20.0f;
	const float MOTOR_SPEED = 2 * M_PI; //1 turn per second clockwise
	const float DEFAULT_DENSITY = 1.0f;
	const int DEFAULT_GROUP_INDEX = -1;
	const float DEFAULT_FRICTION = 0.3f;

    class ObjectsFactory {
    public:
        ObjectsFactory(ObjectsFactory const &) = delete;
        ObjectsFactory(ObjectsFactory &&) = delete;


        static ObjectsFactory &init(Loop &p);
        static ObjectsFactory &getInstance();


        b2Body* createExampleBox();
        b2Body* createExampleGround();
        b2Body* createCircle(float32 radius, float32 density, float32 friction);
        b2Body* createPolygon(std::vector<b2Vec2> vertices, float32 density, float32 friction);
        b2Body* createGround(std::vector<b2Vec2> vertices);
		b2RevoluteJoint* createJoint(Objects::Base& a, Objects::Base& b, b2Vec2 point);

		void destroyBody(Objects::Base& body);
		void destroyJoint(b2RevoluteJoint* joint);

    private:
        static ObjectsFactory instance;

        b2World* world;

        ObjectsFactory() : world(nullptr) {};
        explicit ObjectsFactory(b2World* w);
        ObjectsFactory &operator=(ObjectsFactory const &);

        static std::shared_ptr<const b2BodyDef> getDefaultBodyDef();
        static std::shared_ptr<const b2FixtureDef> getFixtureDef(
			b2Shape& shape,
			float32 density = DEFAULT_DENSITY,
			float32 friction = DEFAULT_FRICTION,
			int16 groupIndex = DEFAULT_GROUP_INDEX);
    };

}
#endif //GENETIC_CARS_PHYSICSOBJECTSFACTORY_H
