#ifndef _GROUND_GENERATOR_H_
#define _GROUND_GENERATOR_H_

/**
*	@author Rafa³ Galczak
*   @date 13.01.17
*/

#include <random>

#include "include/Ground.h"
#include "include/Vector2.h"


/**
* GrounfGenerator generatees random groud, constrained by given parameters.
* One ground generator can construct many grounds.
*/
class GroundGenerator
{
public:
	//
	GroundGenerator(int segments, float x_distance, float max_delta = 10.0f);
	Objects::Ground* genereteNew(Objects::Vector2 position);
	
private:
	int segments_;
	float x_distance_;
	float max_delta_;

	std::random_device rd_;
	std::mt19937 rng_;
	std::uniform_real_distribution<float> uni;

};

#endif