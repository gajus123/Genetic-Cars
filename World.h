//
// \author Jakub Gajownik
// \date 15.01.18
//

#ifndef _GENETIC_CARS_WORLD_H_
#define _GENETIC_CARS_WORLD_H_

#include "Box2D/Box2D.h"

const b2Vec2 DEFAULT_GRAVITY = b2Vec2(0.0f, 9.8f); //!  Default world gravity
const float32 TIME_STEP = 1.0f / 60.0f; //!  Physics simulation world step
const int32 VELOCITY_ITERATIONS = 8; //!  b2World param - affects simulation accuracy, more better, but works slower
const int32 POSITION_ITERATIONS = 8; //!  b2Wordl param - affects simulation accuracy, more better. but works slower

class World {
public:
	/*!
		\param gravity - b2World gravity param
		\param time_step - b2World.Step time step param
		\param velocity_iterations - b2World.Step velocity_iterations param
		\param position_iterations - b2World.Step position_iterations param
	*/
	explicit World(b2Vec2 gravity = DEFAULT_GRAVITY,
		int32 velocity_iterations = VELOCITY_ITERATIONS,
		int32 position_iterations = POSITION_ITERATIONS,
		float32 time_step = TIME_STEP);
	~World();

	World(const World&) = delete;
	World& operator=(const World&) = delete;

	void step();
	void step(unsigned int time);
	b2World* getWorld();
private:
	b2World* world_;
	float32 time_step_;
	int32 velocity_iterations_;
	int32 position_iterations_;
};

#endif
