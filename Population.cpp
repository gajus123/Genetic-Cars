//
// \author Rafa³ Galczak
// \date 15.01.18
//

#include "Population.h"

#include <algorithm>

namespace Algorithm {
	
	Population::Population() :
		mutation_rate_(DEFAULT_MUTATION_RATE),
		next_population_size_(DEFAULT_POPULATION_SIZE) {

		elite_specimen_ = std::min(DEFAULT_ELITE_SPECIMEN, DEFAULT_POPULATION_SIZE);
		rng_ = std::mt19937(rd_());
	}

	Population::Population(std::vector<Genotype> genotypes) : 
		Population() {
		genotypes_ = genotypes;
	}

	void Population::reset() {
		inflateRandom();
	}

	void Population::inflateRandom() {
		genotypes_.clear();
		
		for (unsigned int i = 0; i < next_population_size_; ++i) {
			Genotype g;
			g.inflateWithRandom();
			genotypes_.emplace_back(g);
		}

		generateVehicles();
	}

	std::vector<Genotype>& Population::getGenotypes() {
		return genotypes_;
	}

	void Population::setMutationRate(float rate)
	{
		if (rate > MAX_MUTATION_RATE)
			rate = MAX_MUTATION_RATE;
		if (rate < MIN_MUTATION_RATE)
			rate = MIN_MUTATION_RATE;
		mutation_rate_ = rate;
	}

	void Population::nextPopulation(std::vector<float> fitnesses) {
		assert(fitnesses.size() == genotypes_.size());

		for (std::size_t i = 0; i < fitnesses.size(); ++i) {
			genotypes_[i].fitness = fitnesses[i];
		}

		sort();
		std::vector<Genotype> new_population;

		for (int i = 0; i < elite_specimen_; ++i) {
			new_population.push_back(genotypes_[i]);
		}
		std::size_t population_left = next_population_size_ - elite_specimen_;
		for (int i = 0; i < (population_left + 1) / 2; ++i) {
			std::pair<Genotype, Genotype> children = getNewChildren();
			children.first.mutate(mutation_rate_);
			children.second.mutate(mutation_rate_);
			new_population.push_back(children.first);
			if (i * 2 + 1 != population_left)
				new_population.push_back(children.second);
		}

		genotypes_ = new_population;

		generateVehicles();
	}

	void Population::generateVehicles() {
		std::vector<Objects::Vehicle> vehicles;
		for (const auto& genotype : genotypes_) {
			vehicles.push_back(genotype.generate());
		}

		emit newVehiclesGenerated(vehicles);
	}

	std::pair<Genotype, Genotype> Population::getNewChildren() {
		Genotype a = getRandomParent();
		Genotype b = getRandomParent();

		return std::make_pair(a.cross(b), b.cross(a));
	}

	Genotype& Population::getRandomParent() {	
		float limit = 0.0f;
		for (const auto& g : genotypes_) {
			limit += g.fitness;
		}
		std::uniform_real_distribution<float> random(0.0f, limit);
		float rulette = random(rng_);
		for (auto& g : genotypes_) {
			if (g.fitness >= rulette) {
				return g;
			}
			rulette -= g.fitness;
		}
		throw std::runtime_error("No parent found!");
	}
	std::size_t Population::getNextGenerationSize() const {
		return next_population_size_;
	}
	float Population::getMutationRate() const {
		return mutation_rate_;
	}
	void Population::setNextGenerationSize(std::size_t population_size) {
		next_population_size_ = std::min(MAX_POPULATION_SIZE, population_size);
	}
	void Population::setEliteSpecimen(std::size_t elite_specimen) {
		if (elite_specimen > next_population_size_)
			elite_specimen = next_population_size_;
		if (elite_specimen < MIN_ELITE_SPECIMEN)
			elite_specimen = MIN_ELITE_SPECIMEN;
		elite_specimen_ = elite_specimen;
	}
	std::size_t Population::getEliteSpecimen() const {
		return elite_specimen_;
	}

	void Population::sort() {
		std::sort(genotypes_.begin(), genotypes_.end(),
			[](const Genotype& a, const Genotype& b) {
				return a.fitness > b.fitness;
		});
	}
	void Population::saveToFile(std::string filename) const {
		std::ofstream output_file;
		output_file.open(filename);

		output_file << genotypes_.size() << "\n";
		for (const auto& genotype : genotypes_) {
			output_file << genotype << "\n";
		}

		output_file.close();
	}

	void Population::loadFromFile(std::string filename)
	{
		genotypes_.clear();

		std::ifstream input_file;
		input_file.open(filename);

		std::size_t genotypes_number;
		input_file >> genotypes_number;
		for (auto i=0; i<genotypes_number; ++i) {
			printf("1\n");
			Genotype g;
			input_file >> g;
			genotypes_.emplace_back(g);
		}

		input_file.close();

		generateVehicles();
	}
}