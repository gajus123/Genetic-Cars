#include "include/GroundGenerator.h"
#include <vector>


	GroundGenerator::GroundGenerator(int segments, float x_distance, float max_delta):
		segments_(segments),
		x_distance_(x_distance),
		max_delta_(max_delta)
	{
		rng_ = std::mt19937(rd_());
		uni = std::uniform_int_distribution<int>(-max_delta_, max_delta_);
	}

	Objects::Ground * GroundGenerator::genereteNew(Vector2 position) {
		std::vector<float> heights = {
				0.0f,
				0.0f,
				0.0f,
		};
		for (int i = heights.size(); i < segments_; ++i) {
			heights.push_back(heights[i-1] + (float)uni(rng_));
		}
		return new Objects::Ground(position, x_distance_, heights);
	}
