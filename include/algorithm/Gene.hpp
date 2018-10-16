//
// \author Jakub Gajownik
// \date 16.10.18
//

#pragma once
#include <random>

namespace Algorithm2 {
    class Gene {
        const unsigned int INT_NUM_BITS = 32; //!  number of bits in unsigned value type to hold gene into
        const float MAX_RAND_VALUE = 100.0f; //!  maximum value rng reacheas in probability tests
    public:
        Gene() :
            rng_(rd_()) {
            data_ = std::uniform_int_distribution<std::uint32_t>(std::numeric_limits<std::uint32_t>::lowest(), std::numeric_limits<std::uint32_t>::max())(rng_);
        }

        Gene(std::uint32_t value) :
            rng_(rd_()) {
            data_ = NKB2Grey(value);
        };

        ~Gene() {};

        Gene(const Gene& other) :
            rng_(rd_()) {
            data_ = other.data_;
        }

        Gene& operator=(const Gene& other) {
            data_ = other.data_;
            return *this;
        }

        void mutate(float mutation_rate) {
            std::uniform_real_distribution<float> random(0.0f, MAX_RAND_VALUE);

            std::uint32_t mask = 0;
            for (unsigned int i = 0; i < INT_NUM_BITS; ++i) {
                if (random(rng_) < mutation_rate) {
                    mask |= uint32_t(1);
                }
                mask <<= 1;
            }
            data_ = data_ ^ mask;
        }

        std::uint32_t value() const {
            return nkb();
        }

        std::uint32_t nkb() const {
            return grey2NKB(data_);
        }

        std::uint32_t grey() const {
            return data_;
        }

        Gene cross(const Gene& other) const {
            Gene result(*this);

            uint32_t mask = 0;
            mask = ~mask;
            mask >>= INT_NUM_BITS / 2;

            result.data_ = (data_ & mask) | (other.data_ & (~mask));
            return result;
        }

        friend std::ostream& operator<< (std::ostream &stream, const Gene& gene) {
            stream << gene.data_;
            return stream;
        }

        friend std::istream& operator>> (std::istream & stream, Gene& gene) {
            stream >> gene.data_;
            return stream;
        }
    private:
        std::uint32_t NKB2Grey(std::uint32_t nkb) const {
            return nkb ^ (nkb >> 1);
        }

        std::uint32_t grey2NKB(std::uint32_t grey) const {
            std::uint32_t res = 0;
            std::uint32_t mask = 1;
            while (grey != 0) {
                res = (grey & 1) == 1 ? (mask ^ res) : res;
                grey = grey >> 1;
                mask = (mask << 1) | 1;
            }
            return res;
        }

        std::uint32_t data_;

        std::random_device rd_;
        std::mt19937 rng_;
    };
}