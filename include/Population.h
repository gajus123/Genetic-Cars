//
// \author Rafa³ Galczak
// \date 15.01.18
//

#ifndef _GENETIC_CARS_POPULATION_H_
#define _GENETIC_CARS_POPULATION_H_

#include <vector>
#include <random>
#include <cstdio>
#include "include/Genotype.h"


namespace Algorithm {
	const std::size_t DEFAULT_ELITE_SPECIMEN = 4;
	const std::size_t MIN_ELITE_SPECIMEN = 1;
	const float DEFAULT_MUTATION_RATE = 20.0f;
	const std::size_t DEFAULT_POPULATION_SIZE = 10;
	const std::size_t MAX_POPULATION_SIZE = 30;
	const float MAX_MUTATION_RATE = 100.0f;
	const float MIN_MUTATION_RATE = 0.0f;

	class Population
	{
	public:

		Population();
		Population(const Population& other) = delete;
		explicit Population(std::vector<Genotype> genotypes);

		void reset();
		void inflateRandom();
		void nextPopulation();
		std::vector<Genotype>& getGenotypes();

		void setMutationRate(float rate);
		void setEliteSpecimen(std::size_t elite_specimen);
		void setNextGenerationSize(std::size_t population_size);

		float getMutationRate() const;
		std::size_t getEliteSpecimen() const;
		std::size_t getNextGenerationSize() const;
	private:
		std::random_device rd_;
		std::mt19937 rng_;

		float mutation_rate_;
		unsigned int elite_specimen_;
		std::vector<Genotype> genotypes_;
		std::size_t next_population_size_;

		std::pair<Genotype, Genotype> getNewChildren();
		Genotype& getRandomParent();
		void sort();

	};


}
#endif // !_GENETIC_CARS_POPULATION_H_