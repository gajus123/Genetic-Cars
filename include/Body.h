//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_BODY_H
#define GENETIC_CARS_BODY_H


#include "include/Vector2.h"
#include <vector>

namespace Objects {

    class Body {
    public:
        Body(std::vector<float> lenghts, Vector2 position);

        Vector2 getPosition() const {return position;}
        std::vector<Vector2> getVertices() const {return vertices;}
    private:
        b2Body* body;

        Vector2 position;
        std::vector<Vector2> vertices;
    };

}
#endif //GENETIC_CARS_BODY_H
