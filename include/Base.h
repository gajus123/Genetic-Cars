//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_BASE_H
#define GENETIC_CARS_BASE_H

#include "include/Vector2.h"
#include "include/ObjectsFactory.h"

namespace Physics {
	class ObjectsFactory;
}


namespace Objects {

    class Base {
    public:
		friend class Physics::ObjectsFactory;

		explicit Base(Vector2 position = { 0.0f, 0.0f }) : start_position(position) {};
        virtual Vector2 getPosition() const { return Vector2(body->GetPosition()); }
		virtual float getAngle() const { return (float)body->GetAngle();  }

    protected:
        b2Body* body;
        Vector2 start_position;

		virtual void beforeBodySetUp() {};
		virtual void createAndSetBody() {};
        virtual void afterBodySetup() { body->SetTransform(start_position.asb2Vec2(), 0.0f); }
    };

}
#endif //GENETIC_CARS_BASE_H
