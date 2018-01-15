//
// \author Rafa³ Galczak
// \date 14.01.18
//

#ifndef GENETIC_CARS_BODY_H
#define GENETIC_CARS_BODY_H


#include "include/Vector2.h"
#include "include/Base.h"
#include <vector>
#include <cstdio>

namespace Objects {

	/*!
		\class Body
		\brief Vehicle body

		Body is a b2PolygonShape. Shape is build on 8 vertices.
		They can be treated as vectors with directions as compass rose.
		Bodies differ from one other based on lenght of theese vectors, which
		are later translated into points in the b2Body local coordinate space.
	*/
    class Body : public Base {
    public:
		static const unsigned int BODY_SEGMENTS; //!< Brief: Number of vertices wich body is created from
		static const float BODY_FRICTION; //!< Brief: Default body friction

		/*!
			/param lenghts - length of 8 vectors creating body, going counter-clockwise,
							 starting at upper one	
			/param position - position in the world space to spawn body on
		*/
        Body(std::vector<float> lengths, Vector2 position) : lengths(std::move(lengths)), Base(position) {
			beforeBodySetUp();
			createAndSetBody();	
			afterBodySetup();
		};

        std::vector<Vector2> getVertices() const { return vertices; };
        std::vector<Vector2> getCurrentVertices() const; //!< Brief: returns vertices shifted by current position

    protected:
        std::vector<Vector2> vertices;
        std::vector<float> lengths;

        void beforeBodySetUp() override; //!< Brief: Calculates and setus up vertives
        void calculateVertices(); //!< Brief: Calculates b2PolygonShape vertices 

        void createAndSetBody() override; //!< Brief: Creates b2PolygonShape based on vertices
    };

}
#endif //GENETIC_CARS_BODY_H
