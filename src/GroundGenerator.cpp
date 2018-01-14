#include "include/GroundGenerator.h"
#include "..\include\GroundGenerator.h"


	GroundGenerator::GroundGenerator(int segments, float x_distance, float min_delta, float max_delta):
		segments_(segments),
		x_distance_(x_distance),
		min_delta_(min_delta),
		max_delta_(max_delta)
	{
		rng_ = std::mt19937(rd_());
		uni = std::uniform_int_distribution<int>(min_delta_, max_delta_);
	}

	Ground * GroundGenerator::genereteNew()
	{
		std::vector<float> heights;
	}
