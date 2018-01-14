#include "..\include\Genotype.h"

namespace Algorithm {

	Genotype::Genotype()
	{
		rng_ = std::mt19937(rd_());
		random_ = std::uniform_real_distribution<float>(0.0f, MAX_RAND_VALUE);
	}

	Genotype::Genotype(const Genotype & other) : Genotype()
	{
		front_radius = other.front_radius;
		back_radius = other.back_radius;
		heights = other.heights;
	}

	void Genotype::inflateWithRandom()
	{
		std::random_device rd;
		std::mt19937 rng;
		
		std::uint32_t limit = 0;
		limit = ~limit;
		std::uniform_int_distribution<std::uint32_t> uni(0, limit);

		front_radius = uni(rng);
		back_radius = uni(rng);
		for (std::uint32_t i = 0; i < Objects::BODY_SEGMENTS; ++i) {
			heights.push_back(uni(rng));
		}

	}

	void Genotype::mutate(float mutation_rate)
	{
		uint32_t mask = 0;
		for (unsigned int i = 0; i < INT_NUM_BITS; ++i) {
			if (random_(rng_) < MAX_RAND_VALUE) {
				mask |= uint32_t(1);
			}
			mask <<= 1;
		}
		front_radius ^= mask;
	
		mask = 0;
		for (unsigned int i = 0; i < INT_NUM_BITS; ++i) {
			if (random_(rng_) < MAX_RAND_VALUE) {
				mask |= uint32_t(1);
			}
			mask <<= 1;
		}
		back_radius ^= mask;

		for (unsigned int i = 0; i < heights.size(); ++i) {
			mask = 0;
			for (unsigned int i = 0; i < INT_NUM_BITS; ++i) {
				if (random_(rng_) < MAX_RAND_VALUE) {
					mask |= uint32_t(1);
				}
				mask <<= 1;
			}
			heights[i] ^= mask;
		}
	}

	Genotype Genotype::cross(Genotype & other)
	{
		Genotype child;
		child.front_radius = crossValues(this->front_radius, other.front_radius);
		child.back_radius = crossValues(this->back_radius, other.back_radius);
		for (unsigned int i = 0; i < heights.size(); ++i) {
			child.heights[i] = crossValues(this->heights[i], other.heights[i]);
		}
		return child;
	}




	std::uint32_t Genotype::grey2NKB(std::uint32_t grey)
	{
		std::uint32_t res = 0;
		std::uint32_t mask = 1;
		while (grey != 0) {
			res = (grey & 1) == 1 ? (mask ^ res) : res;
			grey = grey >> 1;
			mask = (mask << 1) | 1;
		}
		return res;
	}

	std::uint32_t Genotype::NKB2Gray(std::uint32_t nkb)
	{
		return nkb ^ (nkb >> 1);
	}

	std::uint32_t Genotype::crossValues(std::uint32_t a, std::uint32_t b)
	{
		uint32_t mask = 0;
		mask = ~mask;
		mask >>= INT_NUM_BITS / 2;

		return (a & mask) | (b & (~mask));
	}

	float Genotype::castSignedValue(std::uint32_t grey, float maximum_value)
	{
		std::uint32_t half_limit = 0;
		half_limit = ~half_limit;
		half_limit = half_limit >> 1;
		
		std::uint32_t nkb = grey2NKB(grey);
		float res = (float)nkb - half_limit;
		
		return  (res/half_limit) * maximum_value;
	}

	float Genotype::castUnsignedValue(std::uint32_t grey, float maximum_value)
	{
		std::uint32_t limit = 0;
		limit = ~limit;
		
		float denominal = limit / maximum_value;
		return (float)grey2NKB(grey) / denominal;
	}

	Objects::Vehicle Genotype::generate(Objects::Vector2 position)
	{
		float front_wheel_r = castUnsignedValue(front_radius, MAX_RADIUS_LIMIT);
		float back_wheel_r = castUnsignedValue(back_radius, MAX_RADIUS_LIMIT);
		std::vector<float> heights_r;
		for (auto& h : heights) {
			heights_r.push_back(castUnsignedValue(h, MAX_HEIGHT_LIMIT));
		}
		return Objects::Vehicle(position, heights_r, front_wheel_r, back_wheel_r);
	}

}