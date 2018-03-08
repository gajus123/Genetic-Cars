//
// \author Rafa³ Galczak
// \date 13.01.18
//

#include "Loop.h"

namespace Physics {

    Loop::Loop() :
			QObject(),
			interval_(PHYSICS_FRAME_TIME) {
		timer_.setInterval(PHYSICS_FRAME_TIME);
		timer_.start();
		connect(&timer_, SIGNAL(timeout()), this, SLOT(update()));
    }

    void Loop::stop() {
		timer_.stop();
    }

	void Loop::update() {
		emit step(interval_);
	}

	void Loop::start() {
		timer_.start();
	}
	void Loop::setTimeSpeed(float time_speed) {
		float new_interval = static_cast<float>(PHYSICS_FRAME_TIME) * time_speed;
		interval_ = static_cast<unsigned int>(new_interval);
	}

}