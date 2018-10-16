//
// Created by gajus123 on 16.10.18.
//

#pragma once
#include <vector>
#include <QObject>

#include <algorithm/Population.h>

namespace Algorithm2 {
    class PopulationWrapper : public QObject {
        Q_OBJECT
    public:
        PopulationWrapper();
        ~PopulationWrapper();

        void reset();
        void generateVehicles();

        std::size_t generationSize() const;
        std::size_t nextGenerationSize() const;
        std::size_t eliteSpecimen() const;
        float mutationRate() const;

        void setNextGenerationSize(std::size_t generation_size);
        void setEliteSpecimen(std::size_t elite_specimen);
        void setMutationRate(float mutation_rate);

        void saveToFile(std::string filename) const;
        void loadFromFile(std::string filename);
    public slots:
        void nextPopulation(std::vector<float> fitnesses); //!  Creates next population of genotypes based on fitness of the current one
    signals:
        void newVehiclesGenerated(std::vector<Objects::Vehicle> vehicles);
    private:
        Population population_;
    };
}