//
// \author Rafa³ Galczak
// \date 12.01.18
//

#ifndef GENETIC_CARS_WHEEL_H
#define GENETIC_CARS_WHEEL_H

#include "Box2D/Box2D.h"

#include "include/Base.h"
#include "include/Vector2.h"

namespace Objects {
	/*!
		\class Wheel
		\brief b2CircleShape wrapper	
	*/
    class Wheel : public Base {
    public:
		Wheel(Vector2 position, float radius); //!  Creates circle with radius at given postion in the world space

        float getRadius() const {return radius_;}
    protected:
        float radius_;

        void createAndSetBody() override; //!  Creates b2Body with b2CircleShape 
    };

}
#endif //GENETIC_CARS_WHEEL_H
