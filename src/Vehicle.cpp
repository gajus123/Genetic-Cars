//
// Created by igor on 13.01.18.
//

#include "include/Vehicle.h"
#include "include/ObjectsFactory.h"

namespace Objects {

	Vehicle::Vehicle(Body & body, float front_wheel_radius, float back_wheel_radius) :
		body(body),
		front(Objects::Wheel(body.getCurrentVertices()[6], front_wheel_radius)),
		back(Objects::Wheel(body.getCurrentVertices()[2], back_wheel_radius))
	{
		joint_front = Physics::ObjectsFactory::getInstance().createJoint(body, front, front.getPosition().asb2Vec2());
		joint_back = Physics::ObjectsFactory::getInstance().createJoint(body, back, back.getPosition().asb2Vec2());
	}

}