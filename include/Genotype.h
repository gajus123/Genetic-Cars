#ifndef _GENETIC_CARS_GENOTYPE_H_
#define _GENETIC_CARS_GENOTYPE_H_

//
// \author Rafa³ Galczak
// \date 15.01.18
//


#include <vector>
#include <random>
#include <cstdint>
#include <cstdio>
#include <ostream>
#include <istream>

#include "include/Vehicle.h"


namespace Algorithm {

	const float MAX_RAND_VALUE= 100.0f; //!< Brief: maximum value rng reacheas in probability tests
	const unsigned int INT_NUM_BITS = 32; //!< Brief: number of bits in unsigned value type to hold genotype into

	const float MAX_RADIUS_LIMIT = 0.5f; //!< Brief: maximum possible radius of a wheel
	const float MAX_HEIGHT_LIMIT = 2.0f; //!< Brief: maximum possible length of one Body segment
	
	/*!
		\class Genotype
		\brief Genotype of Vehicle

		Genotype defines interface to make mutation operation on him.
		Such as cross with other genotype, mutatution etc.

		Can create it's phenotype from itself.
		Each has it's own rng.
	*/
	class Genotype
	{
	public:
		float fitness; //!< Brief: Nonegative mark of how good phenotype of this genotype is

		Genotype(); //!< Inits rng
		Genotype(const Genotype& other); //!< Inits own RNG, copies wheels radiuses and bodys segments heights
		
		Genotype& operator=(const Genotype& other); //!< Inits own RNG, copies wheels radiuses and bodys segments heights

		void inflateWithRandom(); //!< Inits wheels radiuses and bodys segments heights with random values 
		void mutate(float mutation_rate); //!< Test each bit of genotype against mutation rate and flips it if passed
		Genotype cross(Genotype& other) const;//!< Takes lower half bits if this genotype and upper half from other, combines them to create new Genetype

		Objects::Vehicle generate(Objects::Vector2 position = {0.0f, 0.0f}) const; //!< Creates Vehicle corresponding to this Genotype
		
		friend std::ostream& operator<< (std::ostream &stream, const Genotype& genotype);
		friend std::istream& operator>> (std::istream & stream, Genotype& genotype);
	private:
		std::random_device rd_;
		std::mt19937 rng_;
		std::uniform_real_distribution<float> random_;

		std::uint32_t front_radius;
		std::uint32_t back_radius;
		std::vector<std::uint32_t> heights;

		std::uint32_t grey2NKB(std::uint32_t grey) const;
		std::uint32_t NKB2Gray(std::uint32_t nkb) const;

		std::uint32_t mutate_value(std::uint32_t value, float mutation_rate);//!< Test each bit of value against mutation rate and flips it if passed


		std::uint32_t crossValues(std::uint32_t a, std::uint32_t b) const; //!< Creates new value from half lower bits of a and half high bits of b
		float castSignedValue(std::uint32_t grey, float maximum_value = 1.0f) const; //!< Casts number in grey code to unsigned float lower than maximum 
		float castUnsignedValue(std::uint32_t grey, float maximum_value = 1.0f) const; //!< Brief: Casts number to float lower than maximum and greater than -maximum
	};
}
#endif // !_GENETIC_CARS_GENOTYPE_H_