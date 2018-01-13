//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_PHYSICS_H
#define GENETIC_CARS_PHYSICS_H

#include <thread>
#include <atomic>

#import "Box2D/Box2D.h"


class Physics {
public:
    explicit Physics(b2Vec2 gravity = b2Vec2(0.0f, 9.8f), float32 time_step=1f/60f, int32 velocity_iterations=8, int32 position_iterations=3);
    Physics(const Physics&) = delete;
    Physics(Physics&&) = delete;

    void run();
    void stop();

    b2World& getWorld() const;
private:
    std::atomic_bool stop_simulation = false;

    b2World world;
    b2Vec2 gravity;
    float32 time_step;
    int32 velocity_iterations;
    int32 position_iterations;

    std::thread physics_t;


    void start_physics();

};


#endif //GENETIC_CARS_PHYSICS_H
