#ifndef _GENETIC_CARS_POPULATION_H_
#define _GENETIC_CARS_POPULATION_H_


#include <vector>
#include <random>
#include <cstdio>
#include "include/Genotype.h"


namespace Algorithm {
	const int DEFAULT_ELITE_SPECIMEN = 4;

	class Population
	{
	public:
		unsigned int elite_specimen = DEFAULT_ELITE_SPECIMEN;

		Population() = delete;
		Population(float mutation_rate);
		Population(const Population& other);
		explicit Population(std::vector<Genotype> genotypes, float mutation_rate);

		void inflateRandom(unsigned int size);
		std::vector<Genotype>& getGenotypes();
		
		float getMutationRate() { return mutation_rate_; }
		void setMutationRate(float rate);

		void nextPopulation();
	private:
		std::random_device rd_;
		std::mt19937 rng_;

		std::vector<Genotype> genotypes;
		float mutation_rate_;

		std::pair<Genotype, Genotype> getNewChildren();
		Genotype& getRandomParent();
		void sort();

	};


}
#endif // !_GENETIC_CARS_POPULATION_H_