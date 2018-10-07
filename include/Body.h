//
// \author Rafa� Galczak
// \date 14.01.18
//

#ifndef GENETIC_CARS_BODY_H
#define GENETIC_CARS_BODY_H


#include <vector>
#include <cstdio>

#include <Vector2.h>
#include <Base.h>

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
		static const unsigned int BODY_SEGMENTS; //!  Number of vertices wich body is created from
		static const float BODY_FRICTION; //!  Default body friction

		/*!
			\param lenghts - length of 8 vectors creating body, going counter-clockwise,
							 starting at upper one	
			\param position - position in the world space to spawn body on
		*/
        Body(std::vector<float> lengths, Vector2 position) :
			Base(position),
			lengths_(std::move(lengths)) {
			beforeBodySetUp();
			createAndSetBody();	
			afterBodySetup();
		};

        const std::vector<Vector2> getVertices() const;
        const std::vector<Vector2> getCurrentVertices() const; //!  returns vertices shifted by current position

    protected:
        std::vector<Vector2> vertices_;
        std::vector<float> lengths_;

        void beforeBodySetUp() override; //!  Calculates and setus up vertives
        void calculateVertices(); //!  Calculates b2PolygonShape vertices 

        void createAndSetBody() override; //!  Creates b2PolygonShape based on vertices
    };

}
#endif //GENETIC_CARS_BODY_H
