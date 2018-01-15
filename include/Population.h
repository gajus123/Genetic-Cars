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
	const int DEFAULT_ELITE_SPECIMEN = 4;
	const float DEFAULT_MUTATION_RATE = 20;
	const std::size_t DEFAULT_GENERATION_SIZE = 10;

	class Population
	{
	public:
		const unsigned int elite_specimen = DEFAULT_ELITE_SPECIMEN;

		Population();
		Population(const Population& other) = delete;
		explicit Population(std::vector<Genotype> genotypes);

		void inflateRandom();
		void nextPopulation();
		std::vector<Genotype>& getGenotypes();

		void setMutationRate(float rate);
		void setNextGenerationSize(std::size_t population_size);

		float getMutationRate() const;
		std::size_t getNextGenerationSize() const;
	private:
		std::random_device rd_;
		std::mt19937 rng_;

		std::vector<Genotype> genotypes_;
		float mutation_rate_;
		std::size_t next_population_size_;

		std::pair<Genotype, Genotype> getNewChildren();
		Genotype& getRandomParent();
		void sort();

	};


}
#endif // !_GENETIC_CARS_POPULATION_H_