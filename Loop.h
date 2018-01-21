//
// \author Rafa³ Galczak
// \date 13.01.18
//

#ifndef GENETIC_CARS_PHYSICS_H
#define GENETIC_CARS_PHYSICS_H

#include <QTimer>
#include <QDebug>
#include <QObject>

#include "Box2D/Box2D.h"


namespace Physics {

	const b2Vec2 DEFAULT_GRAVITY = b2Vec2(0.0f, 9.8f); //!< Brief: Default world gravity
	const float32 TIME_STEP = 1.0f / 60.0f; //!< Brief: Physics simulation world step
	const int32 VELOCITY_ITERATIONS = 8; //!< Brief: b2World param - affects simulation accuracy, more better, but works slower
	const int32 POSITION_ITERATIONS = 8; //!< Brief: b2Wordl param - affects simulation accuracy, more better. but works slower

	/*!
		\class Loop
		\brief Physics loop objec

		Loop wraps Box2D world creation and simulation computing.
		It is advised that all constructor parameters should remain default.
		
		After creation call start() to start simulation.
		Call stop() to pause, a simulation.
	*/
    class Loop : public QObject {
		Q_OBJECT

    public:
		/*!
			/param gravity - b2World gravity param
			/param time_step - b2World.Step time step param
			/param velocity_iterations - b2World.Step velocity_iterations param
			/param position_iterations - b2World.Step position_iterations param
		*/
        explicit Loop(b2Vec2 gravity = DEFAULT_GRAVITY,
                      int32 velocity_iterations = VELOCITY_ITERATIONS,
                      int32 position_iterations = POSITION_ITERATIONS);
        Loop(const Loop &) = delete;
        Loop(Loop &&) = delete;

		void start(); //!< Brief: Starts a physics simulation
        void stop(); //!< Breif: Pauses a physisc simulation
		void setTimeSpeed(float time_speed);

        b2World* getWorld();
	private slots:
		void update(); 
    private:
		int PHYSICS_FRAME_TIME = 16;
		QTimer timer_;

        b2World* world;
        b2Vec2 gravity;
        float32 time_step_;
		float32 normal_time_step_;
        int32 velocity_iterations;
        int32 position_iterations;
    };

}
#endif //GENETIC_CARS_PHYSICS_H
