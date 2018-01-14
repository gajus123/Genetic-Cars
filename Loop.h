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

    class Loop : public QObject {
		Q_OBJECT

    public:
        explicit Loop(b2Vec2 gravity = b2Vec2(0.0f, 98.0f),
                      float32 time_step = 1.0f / 60.0f,
                      int32 velocity_iterations = 8,
                      int32 position_iterations = 3);
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
