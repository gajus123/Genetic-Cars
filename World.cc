#include "World.h"

World::World(b2Vec2 gravity, int32 velocity_iterations, int32 position_iterations, float32 time_step) :
		world_(new b2World(gravity)),
		velocity_iterations_(velocity_iterations),
		position_iterations_(position_iterations),
		time_step_(time_step) {
}

void World::step(unsigned int time) {
	float sim_time = static_cast<float>(time) / 1000;
	accumulator_ += sim_time;

	while (accumulator_ > time_step_) {
		world_->Step(
			time_step_,
			velocity_iterations_,
			position_iterations_
		);
		accumulator_ -= time_step_;
	}
}

void World::step() {
	world_->Step(
		time_step_,
		velocity_iterations_,
		position_iterations_
	);
}

b2World* World::getWorld() {
	return world_;
}

World::~World() {
	delete world_;
}