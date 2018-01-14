//
// Created by igor on 13.01.18.
//

#include "include/Vehicle.h"
#include "include/ObjectsFactory.h"

namespace Objects {

	Vehicle::Vehicle(Vector2 position, std::vector<float> body, float front_wheel_radius, float back_wheel_radius) :
		car_body(body, position),
		front(car_body.getCurrentVertices()[6], front_wheel_radius),
		back(car_body.getCurrentVertices()[2], back_wheel_radius)
	{
		joint_front = Physics::ObjectsFactory::getInstance().createJoint(car_body, front, front.getPosition().asb2Vec2());
		joint_back = Physics::ObjectsFactory::getInstance().createJoint(car_body, back, back.getPosition().asb2Vec2());
	}

	void Vehicle::destroy()
	{

		Physics::ObjectsFactory::getInstance().destroyBody(car_body);
		Physics::ObjectsFactory::getInstance().destroyBody(front);
		Physics::ObjectsFactory::getInstance().destroyBody(back);
	}

}