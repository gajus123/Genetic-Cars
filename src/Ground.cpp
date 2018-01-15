//
// Created by igor on 13.01.18.
//

#include "include/Ground.h"
#include "include/ObjectsFactory.h"


namespace Objects {

	Ground::Ground(Vector2 position, float x_distance, std::vector<float> heights) :
		x_distance_(x_distance),
		heights_(std::move(heights)),
		Base(position) {

		beforeBodySetUp();
		createAndSetBody();
		afterBodySetup();
	}

    void Ground::beforeBodySetUp() {
        for (int i = 0; i < heights_.size(); ++i) {
            vertices_.emplace_back(std::move(Vector2(x_distance_*i, heights_[i])));
        }
    }

    void Ground::createAndSetBody() {
        std::vector<b2Vec2> b2_vertices;
        for (const auto &v : vertices_) {
            b2_vertices.emplace_back(v.asb2Vec2());
        }
        body = Physics::ObjectsFactory::getInstance().createGround(b2_vertices);
    }
}