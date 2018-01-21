//
// \author Rafa� Galczak
// \date 13.01.17
//

#ifndef _GROUND_GENERATOR_H_
#define _GROUND_GENERATOR_H_


#include <random>

#include "include/Ground.h"
#include "include/Vector2.h"


/*!
  \class GroundGenerator
  \brief generates random ground

  GrounfGenerator generatees random groud, constrained by given parameters.
  One ground generator can construct many grounds.
*/
class GroundGenerator
{
public:
	static const float DEFAULT_MAX_DELTA; //!  Max delta designated for optimal track generation

	/*!
		\param segments - number of road segments
		\param x_distance - distance on x axis between two neighboring vertices
		\param max_delta - maximum y distance between two neighboring vertices
							defaults to DEFAULT_MAX_DELTA
	*/
	GroundGenerator(int segments, float x_distance, float max_delta = DEFAULT_MAX_DELTA);

	Objects::Ground* genereteNew(Objects::Vector2 position); //!  creates new random ground starting at \param position
	
private:
	int segments_;
	float x_distance_;
	float max_delta_;

	std::random_device rd_;
	std::mt19937 rng_;
	std::uniform_real_distribution<float> uni;

};

#endif