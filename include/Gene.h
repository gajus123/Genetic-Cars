//
// \author Jakub Gajownik
// \date 13.03.18
//

#ifndef _GENETIC_CARS_GENE_H_
#define _GENETIC_CARS_GENE_H_

#include <cstdint>
#include <random>

template<typename T>
class Gene {
	const unsigned int INT_NUM_BITS = 32; //!  number of bits in unsigned value type to hold gene into
	const float MAX_RAND_VALUE = 100.0f; //!  maximum value rng reacheas in probability tests
public:
	Gene(T value, T minimum_value, T maximum_value) :
			minimum_value_(minimum_value),
			maximum_value_(maximum_value),
			rng_(rd_()) {

		T divide = (value - minimum_value) / (maximum_value - minimum_value);
		
		std::uint32_t limit = 0;
		limit = ~limit;
		T divisor = static_cast<T>(limit);

		T numerator = divide * divisor;
		data_ = NKB2Grey(static_cast<std::uint32_t>(numerator));
	};

	~Gene() {
	};

	Gene(const Gene& other) :
			rng_(rd_()) {
		minimum_value_ = other.minimum_value_;
		maximum_value_ = other.maximum_value_;
		data_ = other.data_;
		rng_ = std::mt19937(rd_());
	}

	Gene& operator=(const Gene& other) {
		minimum_value_ = other.minimum_value_;
		maximum_value_ = other.maximum_value_;
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

	T value() const {
		std::uint32_t limit = 0;
		limit = ~limit;

		T numerator = static_cast<T>(nkb());
		T divisor = static_cast<T>(limit);

		T result = (numerator / divisor) * (maximum_value_ - minimum_value_) + minimum_value_;

		return result;
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
		//return (data_ & mask) | (other.data_ & (~mask));
		return result;
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

	T minimum_value_;
	T maximum_value_;
	std::uint32_t data_;

	std::random_device rd_;
	std::mt19937 rng_;
};

#endif