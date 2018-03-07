//
// \author Rafa³ Galczak
// \date 13.01.18
//

#include "Loop.h"

namespace Physics {

    Loop::Loop(b2Vec2 gravity, int32 velocity_iterations, int32 position_iterations) :
			QObject(),
            world(new b2World(gravity)),
			normal_time_step_(TIME_STEP),
            time_step_(TIME_STEP),
            velocity_iterations(velocity_iterations),
            position_iterations(position_iterations) {
		timer_.setInterval(PHYSICS_FRAME_TIME);
		timer_.start();
		connect(&timer_, SIGNAL(timeout()), this, SLOT(update()));
    }

    void Loop::stop() {
		timer_.stop();
    }

    b2World* Loop::getWorld() {
        return world;
    }

	void Loop::update() {
		world->Step(
			time_step_,
			velocity_iterations,
			position_iterations
		);
	}

	void Loop::start() {
		timer_.start();
	}
	void Loop::setTimeSpeed(float time_speed) {
		time_step_ = normal_time_step_ * time_speed;
	}

}