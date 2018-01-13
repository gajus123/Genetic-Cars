//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_GROUND_H
#define GENETIC_CARS_GROUND_H

#include "include/Base.h"

namespace Objects {

    class Ground : public Base {
    public:
        Ground(Vector2 position, float x_distance, std::vector<float> heights) :
                start_position(position),
                x_distance(x_distance),
                heights(std::move(heights)),
                Base(position) {}

        std::vector<Vector2> getVertices() { return vertices; }
        std::vector<float> getHeights() { return heights; }
        float getXDistance() { return x_distance; }
    protected:
        std::vector<Vector2> vertices;

        std::vector<float> heights;
        float x_distance;

        void beforeBodySetUp() override;

        void createAndSetBody() override;
    };

}
#endif //GENETIC_CARS_GROUND_H
