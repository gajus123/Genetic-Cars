//
// \author Rafa³ Galczak
// \date 12.01.18
//

#ifndef GENETIC_CARS_BASE_H
#define GENETIC_CARS_BASE_H

#include "include/Vector2.h"
#include "include/ObjectsFactory.h"

namespace Physics {
	class ObjectsFactory;
}

/*!
	Objects contains simulation objects, 
	which are wrappers around one or multiple b2Bodies and b2Joints
*/
namespace Objects {

	/*!
		\class Base
		\brief Base class for every non composite object 

		Base implements simple wrappers around b2Body like
		getPosition and getRotation
	*/
    class Base {
    public:
		friend class Physics::ObjectsFactory;

		explicit Base(Vector2 position = { 0.0f, 0.0f }); //!< Brief: Creates b2Body and sets it's position to /param position
        virtual Vector2 getPosition() const; //!< /return b2Body position
		virtual float getAngle() const; //!< /return b2Body rotation

    protected:
        b2Body* body_;
        Vector2 start_position_;

		virtual void beforeBodySetUp() {}; //!< Brief: Called before creating a b2Body
		virtual void createAndSetBody() {}; //!< Brief: Body creation
		virtual void afterBodySetup(); //!< Brief: Called after b2Body was created. Sets it's position
    };

}
#endif //GENETIC_CARS_BASE_H
