#include "include/Population.h"
#include "..\include\Population.h"


namespace Algorithm {

	void Population::inflateRandom(unsigned int size)
	{
		for (unsigned int i = 0; i < size; ++i) {
			Genotype g;
			g.inflateWithRandom();
			genotypes.emplace_back(g);
		}
	}

	std::vector<Genotype>& Population::getGenotypes() {
		return genotypes;
	}

	//Population Population::newPopulation()
	//{
	//	sort();
	//}

	void Population::sort() {
		std::sort(genotypes.begin(), genotypes.end(),
			[](const Genotype& a, const Genotype& b) -> bool {
				return a.fitness > b.fitness;
		});
	}
}