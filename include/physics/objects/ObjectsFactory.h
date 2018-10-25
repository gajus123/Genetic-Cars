//
// \author Rafa� Galczak
// \date 14.01.18
//

#ifndef GENETIC_CARS_PHYSICSOBJECTSFACTORY_H
#define GENETIC_CARS_PHYSICSOBJECTSFACTORY_H

#include <QtMath>
#include <vector>

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Box2D.h>

#include <simulation/Loop.h>
#include <physics/objects/Base.h>


namespace Objects {
	class Base;
}

/*!
	\brief Physics namespace is a Box2D wrapper
*/
namespace Physics {

	const float MAX_MOTOR_TORQUE = 60.0f; //!  max Vehicle motor torque
	const float MOTOR_SPEED = 7.0 * M_PI; //!  radians per second
	const float DEFAULT_DENSITY = 10.0f; //!  evaluates to object mass
	const int DEFAULT_GROUP_INDEX = -1;  //!  default collision layer for dynamic objects
	const float DEFAULT_FRICTION = 3.0f; //!  default friction for all objects

	/*!
		\class ObjectsFactory
		\brief b2Bodies and b2Joints factory

		ObjectsFactory is a singleton pattern factory.
		It creates b2Bodies and b2Joints as well as adds them to the b2world upon creation.
		Destroys given objects if needed.

		It is a specialized delegation of b2World
	*/
    class ObjectsFactory {
    public:
        ObjectsFactory(ObjectsFactory const &) = delete;
        ObjectsFactory(ObjectsFactory &&) = delete;

		/*!
			init initializes factory instance with reference to physics Loop's b2World.
			It needs to be called before it's used
			\param p - physics loop
		*/
        static ObjectsFactory &init(b2World* w); 
        static ObjectsFactory &getInstance(); //!  returns ObjectsFactory instance

        b2Body* createCircle(float32 radius, float32 density, float32 friction); //!  Creates circle in the world space - see b2CircleShape
        b2Body* createPolygon(std::vector<b2Vec2> vertices, float32 density, float32 friction); //!  Creates b2PolygonShape from the given vertices
        b2Body* createGround(std::vector<b2Vec2> vertices); //!  Creates b2Chain from the given vertices
		b2RevoluteJoint* createJoint(Objects::Base& a, Objects::Base& b, b2Vec2 point); //!  Creates rotating b2RevoluteJoin between a and b at given position.

		void destroyBody(Objects::Base& body); //!  wraps b2World.DestroyBody()
		void destroyJoint(b2RevoluteJoint* joint); //!  wraps b2World.DestoryJoint() 

    private:
        static ObjectsFactory instance;

        b2World* world; //!  Initialized during init

        ObjectsFactory() : world(nullptr) {};
        explicit ObjectsFactory(b2World* w);
        ObjectsFactory &operator=(ObjectsFactory const &); //!  copies world pointer

        static std::shared_ptr<const b2BodyDef> getDefaultBodyDef(); //!  Creates dynamic_body b2BodyDef 
        static std::shared_ptr<const b2FixtureDef> getFixtureDef(	//!  Creates rigid b2BodyFixture
			b2Shape& shape,
			float32 density = DEFAULT_DENSITY,
			float32 friction = DEFAULT_FRICTION,
			int16 groupIndex = DEFAULT_GROUP_INDEX);
    };

}
#endif //GENETIC_CARS_PHYSICSOBJECTSFACTORY_H
