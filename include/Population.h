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

/*!
	Algrothim defines basic classes for genetetic evolution of Vehicles
*/
namespace Algorithm {
	
	const int DEFAULT_ELITE_SPECIMEN = 4; //!< Brief: Default of how any best genotypes are copied to new generation
	const float DEFAULT_MUTATION_RATE = 20; //!< Brief: Percentes of a chance for a bit flip during mutation
	const std::size_t DEFAULT_GENERATION_SIZE = 10; //!< Brief: Default number of genotypes in the population


	/*!
		\class Population
		\brief One generation of genotypes

		Population is a wrapper around the container of genotypes.
		
		Defines basic interface to control genotype's generation such as:
			inflateRandom - generetes random genotypes. Useful for starting generation
			nextGeneration - which sorts genotypes by its fitness and creates children
			...

	*/
	class Population
	{
	public:
		const unsigned int elite_specimen = DEFAULT_ELITE_SPECIMEN; //!< Brief: How many best genotypes of the generetion should be copied to the next one

		Population(); //!< Brief: Initializes rng and empty population
		Population(const Population& other) = delete; 
		explicit Population(std::vector<Genotype> genotypes); //!< Brief: Creates population based on genotypes vector

		void inflateRandom(); //!< Brief: Fills population with random genotypes. Size as set in setNextGenerationSize
		void nextPopulation(); //!< Brief: Creates next population of genotypes based on fitness of the current one
		std::vector<Genotype>& getGenotypes(); //!< Brief: Returns reference to Genotype's container

		void setMutationRate(float rate); //!< Brief: Sets mutatios rate while creating children for the next generation
		void setNextGenerationSize(std::size_t population_size); //!< Brief: Sets number of genotypes in the next generation

		float getMutationRate() const;
		std::size_t getNextGenerationSize() const;
	private:
		std::random_device rd_;
		std::mt19937 rng_;

		std::vector<Genotype> genotypes_;
		float mutation_rate_; //!< Brief: /see /class Genotype.mutate()
		std::size_t next_population_size_; //!< Brief: number of genotypes in the next population

		std::pair<Genotype, Genotype> getNewChildren(); //!< Brief: Returns children of two genotypes choosen by getRandomParent()
		Genotype& getRandomParent(); //!< Brief: Rerurns Genotype using roulette selection 
		void sort(); //!< Brief: sorts genotypes in place based in their fitness

	};


}
#endif // !_GENETIC_CARS_POPULATION_H_