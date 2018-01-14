//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_VEHICLE_H
#define GENETIC_CARS_VEHICLE_H

#include "include/Wheel.h"
#include "include/Body.h"
#include "Box2D/Box2D.h"


namespace Objects {

    class Vehicle {
    public:

		Vehicle(Vector2 position,
			std::vector<float> body,
			float front_wheel_radius,
			float back_wheel_radius);
		
		Vector2 getPosition() const { return car_body.getPosition(); }
		const Body& getBody() const { return car_body; }
		const Wheel& getFrontWheel() const { return front; }
		const Wheel& getBackWheel() const { return back; }

		void destroy();
    private:
		Body car_body;
		Wheel front;
		Wheel back;

		b2RevoluteJoint* joint_front;
		b2RevoluteJoint* joint_back;
    };

}

#endif //GENETIC_CARS_VEHICLE_H
