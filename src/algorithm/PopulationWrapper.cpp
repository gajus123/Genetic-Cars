//
// Created by gajus123 on 16.10.18.
//

#include <algorithm/PopulationWrapper.h>

namespace Algorithm2 {
    PopulationWrapper::PopulationWrapper() {}

    PopulationWrapper::~PopulationWrapper() {}

    void PopulationWrapper::reset() {
        population_.reset();
        generateVehicles();
    }

    void PopulationWrapper::generateVehicles() {
        auto vehicles = population_.generateVehicles();
        emit newVehiclesGenerated(vehicles);
    }

    void PopulationWrapper::nextPopulation(std::vector<float> fitnesses) {
        population_.nextGeneration(fitnesses);
        generateVehicles();
    }

    std::size_t PopulationWrapper::generationSize() const {
        return population_.generationSize();
    }

    std::size_t PopulationWrapper::nextGenerationSize() const {
        return population_.nextGenerationSize();
    }

    std::size_t PopulationWrapper::eliteSpecimen() const {
        return population_.eliteSpecimen();
    }

    float PopulationWrapper::mutationRate() const {
        return population_.mutationRate();
    }

    void PopulationWrapper::setNextGenerationSize(std::size_t generation_size) {
        population_.setNextGenerationSize(generation_size);
    }

    void PopulationWrapper::setEliteSpecimen(std::size_t elite_specimen) {
        population_.setEliteSpecimen(elite_specimen);
    }

    void PopulationWrapper::setMutationRate(float mutation_rate) {
        population_.setMutationRate( mutation_rate);
    }

    void PopulationWrapper::saveToFile(std::string filename) const {
        population_.saveToFile(filename);
    }

    void PopulationWrapper::loadFromFile(std::string filename) {
        population_.loadFromFile(filename);
        generateVehicles();
    }
}