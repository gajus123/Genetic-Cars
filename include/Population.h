//
// \authors Rafa� Galczak, Jakub Gajownik
// \date 15.01.18
//

#ifndef _GENETIC_CARS_POPULATION_H_
#define _GENETIC_CARS_POPULATION_H_

#include <vector>
#include <random>
#include <fstream>
#include <QObject>

#include <Genotype.h>

/*!
	Algrothim defines basic classes for genetetic evolution of Vehicles
*/
namespace Algorithm {

	const std::size_t DEFAULT_ELITE_SPECIMEN = 4; //!  Default of how any best genotypes are copied to new generation
	const float DEFAULT_MUTATION_RATE = 20.0f; //!  Percentes of a chance for a bit flip during mutation
	const std::size_t DEFAULT_POPULATION_SIZE = 10; //!  Default number of genotypes in the population
	const std::size_t MIN_ELITE_SPECIMEN = 1; 
	const std::size_t MAX_POPULATION_SIZE = 30;
	const float MAX_MUTATION_RATE = 100.0f;
	const float MIN_MUTATION_RATE = 0.0f;

	/*!
		\class Population
		\brief One generation of genotypes

		Population is a wrapper around the container of genotypes.
		
		Defines basic interface to control genotype's generation such as:
			inflateRandom - generetes random genotypes. Useful for starting generation
			nextGeneration - which sorts genotypes by its fitness and creates children
			...
	*/
	class Population : public QObject
	{
		Q_OBJECT
	public:

		Population(); //!  Initializes rng and empty population
		explicit Population(std::vector<Genotype> genotypes); //!  Creates population based on genotypes vector

		void generateVehicles();
		void reset();
		std::vector<Genotype>& getGenotypes(); //!  Returns reference to Genotype's container

		void setMutationRate(float rate); //!  Sets mutatios rate while creating children for the next generation
		void setEliteSpecimen(std::size_t elite_specimen);
		void setNextGenerationSize(std::size_t population_size); //!  Sets number of genotypes in the next generation

		float getMutationRate() const;
		std::size_t getEliteSpecimen() const;
		std::size_t getNextGenerationSize() const;

		void saveToFile(std::string filename) const;
		void loadFromFile(std::string filename);
	public slots:
		void nextPopulation(std::vector<float> fitnesses); //!  Creates next population of genotypes based on fitness of the current one
	signals:
		void newVehiclesGenerated(std::vector<Objects::Vehicle> vehicles);
	private:
		std::random_device rd_;
		std::mt19937 rng_;

		unsigned int elite_specimen_;
		std::vector<Genotype> genotypes_;
		float mutation_rate_; //!  \class Genotype.mutate()
		unsigned int next_population_size_; //!  number of genotypes in the next population

		std::pair<Genotype, Genotype> getNewChildren(); //!  Returns children of two genotypes choosen by getRandomParent()
		Genotype& getRandomParent(); //!  Rerurns Genotype using roulette selection
		void sort(); //!  sorts genotypes in place based in their fitness

	};


}
#endif // !_GENETIC_CARS_POPULATION_H_