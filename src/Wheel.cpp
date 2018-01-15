//
// \author Rafa³ Galczak
// \date 12.01.18
//

#include "include/ObjectsFactory.h"
#include "include/Wheel.h"

namespace Objects {

	Wheel::Wheel(Vector2 position, float radius) : radius_(radius), Base(position) {
		beforeBodySetUp();
		createAndSetBody();
		afterBodySetup();
	};

    void Wheel::createAndSetBody() {
        body = Physics::ObjectsFactory::getInstance().createCircle(radius_, Physics::DEFAULT_DENSITY, Physics::DEFAULT_FRICTION);
    }

}