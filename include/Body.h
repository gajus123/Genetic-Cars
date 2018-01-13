//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_BODY_H
#define GENETIC_CARS_BODY_H


#include "include/Vector2.h"
#include "include/Base.h"
#include <vector>

namespace Objects {

    class Body : public Base {
    public:
        Body(std::vector<float> lengths, Vector2 position) : position(position), lengths(std::move(lengths)), Base(position) {};

        Vector2 getPosition() const {return position;}
        std::vector<Vector2> getVertices() const {return vertices;}

    protected:
        b2Body* body;

        Vector2 position;
        std::vector<Vector2> vertices;
        std::vector<float> lengths;

        void beforeBodySetUp() override;
        void calculateVertices();

        void createAndSetBody() override;
    };

}
#endif //GENETIC_CARS_BODY_H
