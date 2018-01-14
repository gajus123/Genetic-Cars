//
// Created by igor on 13.01.18.
//

#include "Loop.h"

namespace Physics {

    Loop::Loop(b2Vec2 gravity, float32 time_step, int32 velocity_iterations, int32 position_iterations) :
			QObject(),
            world(new b2World(gravity)),
            time_step(time_step),
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
			time_step,
			velocity_iterations,
			position_iterations
		);
	}

	void Loop::start() {
		timer_.start();
	}

}