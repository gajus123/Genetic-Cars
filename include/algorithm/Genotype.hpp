//
// \author Jakub Gajownik
// \date 16.10.18
//

#pragma once
#include <array>
#include <algorithm>
#include <experimental/iterator>

#include <algorithm/Gene.hpp>

namespace Algorithm {
    template<std::size_t N>
    class Genotype {
    public:
        Genotype() {}

        ~Genotype() {}

        void mutate(float mutation_rate) {
            std::for_each(genes_.begin(), genes_.end(), std::bind(&Gene::mutate, std::placeholders::_1, mutation_rate));
        }

        Genotype cross(const Genotype& other) const {
            Genotype child;
            std::transform(genes_.begin(), genes_.end(), other.genes_.begin(), child.genes_.begin(), std::bind(&Gene::cross, std::placeholders::_1, std::placeholders::_2));
            return child;
        }

        std::array<std::uint32_t, N> values() const {
            std::array<std::uint32_t, N> result;
            std::transform(genes_.begin(), genes_.end(), result.begin(), std::bind(&Gene::value, std::placeholders::_1));
            return result;
        };

        friend std::ostream& operator<< (std::ostream &stream, const Genotype<N>& genotype) {
            std::copy(genes_.begin(), genes_.end(), std::experimental::make_ostream_joiner(stream, " "));
        }

        friend std::istream& operator>> (std::istream & stream, Genotype<N>& genotype) {
            std::for_each(genes_.begin(), genes_.end(), std::bind(&operator>>, stream, std::placeholders::_1));
        }
    private:
        std::array<Gene, N> genes_;
    };
}