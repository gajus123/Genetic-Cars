#ifndef _GENETIC_CARS_GENOTYPE_H_
#define _GENETIC_CARS_GENOTYPE_H_

#include <vector>
#include <random>
#include <cstdint>
#include <cstdio>

#include "include/Vehicle.h"


namespace Algorithm {

	const float MAX_RAND_VALUE= 100.0f;
	const unsigned int INT_NUM_BITS = 32;

	const float MAX_RADIUS_LIMIT = 0.5f;
	const float MAX_HEIGHT_LIMIT = 2.0f;
	

	class Genotype
	{
	public:
		float fitness;

		Genotype();
		Genotype(const Genotype& other);
		
		Genotype& operator=(const Genotype& other);

		void inflateWithRandom();
		void mutate(float mutation_rate);
		Genotype cross(Genotype& other) const;

		Objects::Vehicle generate(Objects::Vector2 position = {0.0f, 0.0f}) const;
	private:
		std::random_device rd_;
		std::mt19937 rng_;
		std::uniform_real_distribution<float> random_;

		std::uint32_t front_radius;
		std::uint32_t back_radius;
		std::vector<std::uint32_t> heights;

		std::uint32_t grey2NKB(std::uint32_t grey) const;
		std::uint32_t NKB2Gray(std::uint32_t nkb) const;

		std::uint32_t mutate_value(std::uint32_t value, float mutation_rate);


		std::uint32_t crossValues(std::uint32_t a, std::uint32_t b) const;
		float castSignedValue(std::uint32_t grey, float maximum_value = 1.0f) const;
		float castUnsignedValue(std::uint32_t grey, float maximum_value = 1.0f) const;
	};
}
#endif // !_GENETIC_CARS_GENOTYPE_H_