//
// \author Rafa³ Galczak
// \date 14.01.18
//

#ifndef GENETIC_CARS_GROUND_H
#define GENETIC_CARS_GROUND_H

#include "include/Base.h"
#include <vector>

namespace Objects {

	/*!
		\class Ground
		\brief b2Chain wrapper 

		Ground is a static b2Chain body
	*/
    class Ground : public Base {
    public:
		/*!
			/param position - position in the world space at which chain should start
			/param x_distance - distance on x axis between neighbouring vertices
			/param heights - vector of y coordinates of vertice
		*/
		Ground(Vector2 position, float x_distance, std::vector<float> heights);

        std::vector<Vector2> getVertices() const { return vertices_; }
        std::vector<float> getHeights() const { return heights_; }
        float getXDistance() const { return x_distance_; }
    protected:
        std::vector<Vector2> vertices_;

        std::vector<float> heights_;
        float x_distance_;

        void beforeBodySetUp() override; //!< Brief: sets up chain vertices from x_distance and heights
        void createAndSetBody() override; //!< Brief: Creates b2Chain static b2Body using Physics::ObjectFactory
    };

}
#endif //GENETIC_CARS_GROUND_H
