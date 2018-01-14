//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_BODY_H
#define GENETIC_CARS_BODY_H


#include "include/Vector2.h"
#include "include/Base.h"
#include <vector>
#include <cstdio>

namespace Objects {

    class Body : public Base {
    public:
        Body(std::vector<float> lengths, Vector2 position) : lengths(std::move(lengths)), Base(position) {
			beforeBodySetUp();
			createAndSetBody();
			afterBodySetup();
		};

        std::vector<Vector2> getVertices() const { return vertices; };
        std::vector<Vector2> getCurrentVertices() const;

    protected:
        std::vector<Vector2> vertices;
        std::vector<float> lengths;

        void beforeBodySetUp() override;
        void calculateVertices();

        void createAndSetBody() override;
    };

}
#endif //GENETIC_CARS_BODY_H
