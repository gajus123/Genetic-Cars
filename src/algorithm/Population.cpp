//
// Created by gajus123 on 16.10.18.
//

#include <algorithm/Population.h>

namespace Algorithm2 {
    Population::Population() :
        generation_size_(10),
        next_generation_size_(10),
        elite_specimen_(4),
        mutation_rate_(20.0f),
        genotypes_(generation_size_),
        rng_(rd_()) {}

    Population::~Population() {}

    std::vector<Objects::Vehicle> Population::generateVehicles() const {
        std::vector<Objects::Vehicle> result;
        for(auto& genotype : genotypes_) {
            const auto& values = genotype.values();
            float front_radius = cast(0.0f, 0.5f, values[0]);
            float back_radius = cast(0.0f, 0.5f, values[1]);
            std::vector<float> body;
            std::transform(values.begin()+2, values.end(), std::back_inserter(body), std::bind(&Algorithm2::Population::cast, std::ref(*this), 0.0f, 0.7f, std::placeholders::_1));
            result.emplace_back(Objects::Vector2{0.0f, 0.0f}, body, front_radius, back_radius);
        }
        return result;
    }

    std::size_t Population::generationSize() const {
        return generation_size_;
    }

    std::size_t Population::nextGenerationSize() const {
        return next_generation_size_;
    }

    std::size_t Population::eliteSpecimen() const {
        return elite_specimen_;
    }

    float Population::mutationRate() const {
        return mutation_rate_;
    }

    void Population::setNextGenerationSize(std::size_t generation_size) {
        next_generation_size_ = generation_size;
    }

    void Population::setEliteSpecimen(std::size_t elite_specimen) {
        elite_specimen_ = elite_specimen;
    }

    void Population::setMutationRate(float mutation_rate) {
        mutation_rate_ = mutation_rate;
    }

    void Population::reset() {
        generation_size_ = next_generation_size_;
        genotypes_.clear();
        genotypes_.resize(generation_size_);
    }

    void Population::nextGeneration(std::vector<float> fitnesses) {
        assert(fitnesses.size() == genotypes_.size());

        for (std::size_t i = 0; i < fitnesses.size(); ++i) {
            genotypes_[i].fitness = fitnesses[i];
        }

        sort();
        std::vector<Algorithm2::Genotype<10>> new_population;

        std::size_t num_of_elite_specimen = std::min(elite_specimen_, next_generation_size_);
        std::copy_n(genotypes_.begin(), num_of_elite_specimen, std::back_inserter(new_population));

        std::size_t population_left = next_generation_size_ - num_of_elite_specimen;
        for (std::size_t i = 0; i < (population_left + 1) / 2; ++i) {
            std::pair<Genotype<10>, Genotype<10>> children = getNewChildren();
            children.first.mutate(mutation_rate_);
            children.second.mutate(mutation_rate_);
            new_population.push_back(children.first);
            if (i * 2 + 1 != population_left)
                new_population.push_back(children.second);
        }
        genotypes_ = new_population;
    }

    float Population::cast(float minimum_value, float maximum_value, std::uint32_t value) const {
        std::uint32_t limit = 0;
        limit = ~limit;

        float numerator = static_cast<float>(value);
        float divisor = static_cast<float>(limit);

        float result = (numerator / divisor) * (maximum_value - minimum_value) + minimum_value;
        return result;
    }

    void Population::sort() {
        std::sort(genotypes_.begin(), genotypes_.end(), [](const Algorithm2::Genotype<10>& a, const Algorithm2::Genotype<10>& b) -> bool {
            return a.fitness > b.fitness;
        });
    }

    std::pair<Algorithm2::Genotype<10>, Algorithm2::Genotype<10>> Population::getNewChildren() {
        Algorithm2::Genotype<10> a = getRandomParent();
        Algorithm2::Genotype<10> b = getRandomParent();

        return std::make_pair(a.cross(b), b.cross(a));
    }

    Algorithm2::Genotype<10>& Population::getRandomParent() {
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

    void Population::saveToFile(std::string filename) const {
        std::ofstream output_file;
        output_file.open(filename);

        output_file << genotypes_.size() << "\n";
        for (const auto& genotype : genotypes_) {
            output_file << genotype << "\n";
        }

        output_file.close();
    }

    void Population::loadFromFile(std::string filename) {
        genotypes_.clear();

        std::ifstream input_file;
        input_file.open(filename);

        std::size_t genotypes_number;
        input_file >> genotypes_number;
        for (std::size_t i=0; i<genotypes_number; ++i) {
            Genotype<10> g;
            input_file >> g;
            genotypes_.emplace_back(std::move(g));
        }

        input_file.close();
    }
}