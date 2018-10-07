//
// \author Rafa� Galczak
// \date 12.01.18
//

#include <ObjectsFactory.h>
#include <Wheel.h>

namespace Objects {

	Wheel::Wheel(Vector2 position, float radius) :
		Base(position),
		radius_(radius) {
		beforeBodySetUp();
		createAndSetBody();
		afterBodySetup();
	};

    void Wheel::createAndSetBody() {
        body_ = Physics::ObjectsFactory::getInstance().createCircle(radius_, Physics::DEFAULT_DENSITY, Physics::DEFAULT_FRICTION);
    }

}