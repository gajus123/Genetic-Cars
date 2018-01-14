//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_PHYSICS_H
#define GENETIC_CARS_PHYSICS_H

#include <thread>
#include <atomic>
#include <QTimer>
#include <QDebug>
#include <QObject>

#include "Box2D/Box2D.h"


namespace Physics {

	const b2Vec2 DEFAULT_GRAVITY = b2Vec2(0.0f, 90.8f);
	const float32 TIME_STEP = 1.0f / 60.0f;
	const int32 VELOCITY_ITERATIONS = 8;
	const int32 POSITION_ITERATIONS = 3;

    class Loop : public QObject {
		Q_OBJECT

    public:
        explicit Loop(b2Vec2 gravity = DEFAULT_GRAVITY,
                      float32 time_step = TIME_STEP,
                      int32 velocity_iterations = VELOCITY_ITERATIONS,
                      int32 position_iterations = POSITION_ITERATIONS);
        Loop(const Loop &) = delete;
        Loop(Loop &&) = delete;

		void start();
        void stop();

        b2World* getWorld();
	private slots:
		void update();
    private:
		int PHYSICS_FRAME_TIME = 16;
		QTimer timer_;

        b2World* world;
        b2Vec2 gravity;
        float32 time_step;
        int32 velocity_iterations;
        int32 position_iterations;
    };

}
#endif //GENETIC_CARS_PHYSICS_H
