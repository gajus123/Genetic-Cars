//
// Created by igor on 13.01.18.
//

#include "include/Loop.h"

namespace Physics {

    Loop::Loop(b2Vec2 gravity, float32 time_step, int32 velocity_iterations, int32 position_iterations) :
            world(b2World(gravity)),
            time_step(time_step),
            velocity_iterations(velocity_iterations),
            position_iterations(position_iterations) {

    }

    void Loop::run() {
        stop_simulation = false;
        physics_t = std::thread(start_physics, std::ref(*this));
    }

    void Loop::start_physics(Loop& loop) {
        while (!loop.stop_simulation.load()) {
            loop.world.Step(loop.time_step,
                            loop.velocity_iterations,
                            loop.position_iterations);
        }
    }

    void Loop::stop() {
        stop_simulation = true;
        physics_t.join();
    }

    b2World &Loop::getWorld() {
        return world;
    }

}

