//
// Created by gajus123 on 16.10.18.
//

#pragma once
#include <vector>
#include <fstream>

#include <algorithm/Genotype.hpp>
#include <Vehicle.h>

namespace Algorithm2 {
    class Population {
    public:
        Population();
        ~Population();

        std::vector<Objects::Vehicle> generateVehicles() const;
        std::size_t generationSize() const;
        std::size_t nextGenerationSize() const;
        std::size_t eliteSpecimen() const;
        float mutationRate() const;

        void setNextGenerationSize(std::size_t generation_size);
        void setEliteSpecimen(std::size_t elite_specimen);
        void setMutationRate(float mutation_rate);

        void reset();
        void nextGeneration(std::vector<float> fitnesses);

        void saveToFile(std::string filename) const;
        void loadFromFile(std::string filename);
    private:
        float cast(float minimum_value, float maximum_value, std::uint32_t value) const;

        std::pair<Algorithm2::Genotype<10>, Algorithm2::Genotype<10>> getNewChildren(); //!  Returns children of two genotypes choosen by getRandomParent()
        Algorithm2::Genotype<10>& getRandomParent(); //!  Rerurns Genotype using roulette selection
        void sort(); //!  sorts genotypes in place based in their fitness

        std::size_t generation_size_;
        std::size_t next_generation_size_;
        std::size_t elite_specimen_;
        float mutation_rate_;

        std::vector<Algorithm2::Genotype<10>> genotypes_;

        std::random_device rd_;
        std::mt19937 rng_;
    };
}