//
// \author Rafa� Galczak
// \date 13.01.18
//

#ifndef GENETIC_CARS_VEHICLE_H
#define GENETIC_CARS_VEHICLE_H

#include <Box2D/Box2D.h>

#include <Body.h>
#include <Wheel.h>

namespace Objects {

	/*!
		\class Vehicle 
		\brief Body joined by beJoint with 2 Wheels

		Wehicle is a Body connected with two Wheels by
		constantly rotating b2RevoluteJoint at Body vertices
		at indexes WheelLocation::FRONT and WheelLocation::BACK
	*/
    class Vehicle {
    public:
		/*!
			Indexes of Body vertices at which Wheels should be
			connected to the Body.
			
			FRONT - front wheel connection index
			BACK - back wheel connection index
		*/
		enum WheelLocation {FRONT=1, BACK=7};

		/*!
			Creates Body, front and back Wheels and connects them by
			rotating b2RevoluteJoint
			\param postion - postion to spawn Vehicle in the worlds space
			\param body - \class Body - vector of body segments lenghts
			\param front_wheel_radius - radius of the front wheel 
			\param back_wheel_radius - radius of the back wheel
		*/
		Vehicle(Vector2 position,
			std::vector<float> body,
			float front_wheel_radius,
			float back_wheel_radius);

		Vector2 getPosition() const { return car_body.getPosition(); }
		const Body& getBody() const { return car_body; }
		const Wheel& getFrontWheel() const { return front; }
		const Wheel& getBackWheel() const { return back; }

		void destroy(); //! : calls Physics::ObjectsFactory to destroy each component
    private:
		Body car_body;
		Wheel front;
		Wheel back;

		b2RevoluteJoint* joint_front;
		b2RevoluteJoint* joint_back;
    };

}

#endif //GENETIC_CARS_VEHICLE_H
