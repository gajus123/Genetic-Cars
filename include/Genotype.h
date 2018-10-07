//
// \author Rafa� Galczak
// \date 15.01.18
//

#ifndef _GENETIC_CARS_GENOTYPE_H_
#define _GENETIC_CARS_GENOTYPE_H_

#include <vector>
#include <random>
#include <cstdint>
#include <cstdio>
#include <ostream>
#include <istream>

#include <Vehicle.h>
#include <Gene.h>


namespace Algorithm {

	const float MAX_RAND_VALUE= 100.0f; //!  maximum value rng reacheas in probability tests
	const unsigned int INT_NUM_BITS = 32; //!  number of bits in unsigned value type to hold genotype into

	const float MAX_RADIUS_LIMIT = 0.5f; //!  maximum possible radius of a wheel
	const float MAX_HEIGHT_LIMIT = 0.7f; //!  maximum possible length of one Body segment
	
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
		float fitness; //!  Nonegative mark of how good phenotype of this genotype is

		Genotype(); //!< Inits rng
		Genotype(const Genotype& other); //!< Inits own RNG, copies wheels radiuses and bodys segments heights
		
		Genotype& operator=(const Genotype& other); //!< Inits own RNG, copies wheels radiuses and bodys segments heights

		void mutate(float mutation_rate); //!< Test each bit of genotype against mutation rate and flips it if passed
		Genotype cross(const Genotype& other) const;//!< Takes lower half bits if this genotype and upper half from other, combines them to create new Genetype

		Objects::Vehicle generate(Objects::Vector2 position = {0.0f, 0.0f}) const; //!< Creates Vehicle corresponding to this Genotype
		
		friend std::ostream& operator<< (std::ostream &stream, const Genotype& genotype);
		friend std::istream& operator>> (std::istream & stream, Genotype& genotype);
	private:
		std::random_device rd_;
		std::mt19937 rng_;

		Gene<float> front_radius_;
		Gene<float> back_radius_;
		std::vector<Gene<float>> heights_;

		float randFloat(float min_value, float max_value);
	};
}
#endif // !_GENETIC_CARS_GENOTYPE_H_