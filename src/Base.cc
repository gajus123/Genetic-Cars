//
// \author Rafa� Galczak
// \date 12.01.18
//

#include <Base.h>

namespace Objects {

	Base::Base(Vector2 position) : start_position_(position) {}

	Vector2 Base::getPosition() const { 
		return Vector2(body_->GetPosition()); 
	}

	float Base::getAngle() const { 
		return (float)body_->GetAngle(); 
	}

	void Base::afterBodySetup() { 
		body_->SetTransform(start_position_.asb2Vec2(), 0.0f);
	}

}