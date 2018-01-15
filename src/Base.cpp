//
// \author Rafa³ Galczak
// \date 12.01.18
//

#include "include/Base.h"
#include "..\include\Base.h"


namespace Objects {

	Base::Base(Vector2 position) : start_position(position) {}

	Vector2 Base::getPosition() const { 
		return Vector2(body->GetPosition()); 
	}

	float Base::getAngle() const { 
		return (float)body->GetAngle(); 
	}

	void Base::afterBodySetup() { 
		body->SetTransform(start_position.asb2Vec2(), 0.0f);
	}

}