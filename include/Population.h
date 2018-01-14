#ifndef _GENETIC_CARS_POPULATION_H_
#define _GENETIC_CARS_POPULATION_H_

#include <algorithm>
#include <vector>
#include "include/Genotype.h"


namespace Algorithm {

	const int DEFAULT_ELITE_SPECIMEN = 5;

	class Population
	{
	public:
		unsigned int elite_specimen = DEFAULT_ELITE_SPECIMEN;

		void inflateRandom(unsigned int size);
		std::vector<Genotype>& getGenotypes();

		//Population newPopulation();
	private:
		std::vector<Genotype> genotypes;
		
		void sort();

	};


}
#endif // !_GENETIC_CARS_POPULATION_H_