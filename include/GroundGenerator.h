#ifndef _GROUND_GENERATOR_H_
#define _GROUND_GENERATOR_H_

#include <random>

#include "include/Ground.h"


class GroundGenerator
{
public:
	GroundGenerator(int segments, float x_distance, float max_delta = 10.0f);
	Objects::Ground* genereteNew();
	
private:
	int segments_;
	float x_distance_;
	float max_delta_;

	std::random_device rd_;
	std::mt19937 rng_;
	std::uniform_int_distribution<int> uni;

};

#endif