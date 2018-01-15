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
*/
namespace Objects {

	/*!
	*/
    class Base {
    public:
		friend class Physics::ObjectsFactory;

		explicit Base(Vector2 position = { 0.0f, 0.0f });
        virtual Vector2 getPosition() const;
		virtual float getAngle() const;

    protected:
        b2Body* body;
        Vector2 start_position;

		virtual void beforeBodySetUp() {};
		virtual void createAndSetBody() {};
		virtual void afterBodySetup();
    };

}
#endif //GENETIC_CARS_BASE_H
