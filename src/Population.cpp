#include "include/Population.h"
#include "..\include\Population.h"


#include <algorithm>

namespace Algorithm {
	
	Population::Population() {
		rng_ = std::mt19937(rd_());
	}

	Population::Population(const Population & other) : Population() {
		genotypes = other.genotypes;
	}

	Population::Population(std::vector<Genotype> genotypes) : Population() {
		this->genotypes = genotypes;
	}

	void Population::inflateRandom(unsigned int size) {
		for (unsigned int i = 0; i < size; ++i) {
			Genotype g;
			g.inflateWithRandom();
			genotypes.emplace_back(g);
		}
	}

	std::vector<Genotype>& Population::getGenotypes() {
		return genotypes;
	}

	void Population::nextPopulation() {
		sort();
		std::vector<Genotype> new_population;

		for (int i = 0; i < elite_specimen; ++i) {
			new_population.push_back(genotypes[i]);
		}
		for (int i = 0; i < (genotypes.size() - elite_specimen) / 2; ++i) {
			std::pair<Genotype, Genotype> children = getNewChildren();
			new_population.push_back(children.first);
			new_population.push_back(children.second);
		}

		genotypes = new_population;
	}

	std::pair<Genotype, Genotype> Population::getNewChildren() {
		Genotype a = getRandomParent();
		Genotype b = getRandomParent();

		return std::make_pair(a.cross(b), b.cross(a));
	}

	Genotype& Population::getRandomParent() {
		printf("Test1\n");
		float limit = 0.0f;
		for (const auto& g : genotypes) {
			limit += g.fitness;
		}
		printf("%f\n", limit);
		std::uniform_real_distribution<float> random(0.0f, limit);
		float rulette = random(rng_);
		printf("Test2\n");
		for (auto& g : genotypes) {
			if (g.fitness <= rulette) {
				return g;
			}
			rulette -= g.fitness;
		}
		throw std::runtime_error("No parent found!");
	}

	void Population::sort() {
		std::sort(genotypes.begin(), genotypes.end(),
			[](const Genotype& a, const Genotype& b) {
				return a.fitness > b.fitness;
		});
	}
}