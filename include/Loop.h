//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_PHYSICS_H
#define GENETIC_CARS_PHYSICS_H

#include <thread>
#include <atomic>

#include "Box2D/Box2D.h"


namespace Physics {

    class Loop {
    public:
        explicit Loop(b2Vec2 gravity = b2Vec2(0.0f, 9.8f),
                      float32 time_step = 1.0f / 60.0f,
                      int32 velocity_iterations = 8,
                      int32 position_iterations = 3);
        Loop(const Loop &) = delete;
        Loop(Loop &&) = delete;

        void run();
        void stop();

        b2World* getWorld();

    private:
        std::atomic_bool stop_simulation;

        b2World* world;
        b2Vec2 gravity;
        float32 time_step;
        int32 velocity_iterations;
        int32 position_iterations;

        std::thread physics_t;


        static void start_physics(Loop& loop);

    };

}
#endif //GENETIC_CARS_PHYSICS_H
