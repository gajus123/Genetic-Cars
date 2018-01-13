//
// Created by igor on 13.01.18.
//

#include "include/Physics.h"

Physics::Physics(b2Vec2 gravity, float32 time_step, int32 velocity_iterations, int32 position_iterations) :
        world(b2World(gravity)),
        time_step(time_step),
        velocity_iterations(velocity_iterations),
        position_iterations(position_iterations) {

}

void Physics::run() {
    physics_t = std::thread(start_physics);
}

void Physics::start_physics() {
    while(!stop_simulation) {
        world.Step(time_step, velocity_iterations, position_iterations);
    }
}


void Physics::stop() {
    stop_simulation = true;
    physics_t.join();
}

b2World &Physics::getWorld() const {
    return world;
}



