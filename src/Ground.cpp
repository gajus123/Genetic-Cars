//
// Created by igor on 13.01.18.
//

#include "include/Ground.h"
#include "include/ObjectsFactory.h"


namespace Objects {

    void Ground::beforeBodySetUp() {
        for (const auto &h : heights) {
            vertices.emplace_back(std::move(Vector2(x_distance, h)));
        }
    }

    void Ground::createAndSetBody() {
        std::vector<b2Vec2> b2_vertices;
        for (const auto &v : vertices) {
            b2_vertices.emplace_back(v.asb2Vec2());
        }
        body = Physics::ObjectsFactory::getInstance().createGround(b2_vertices);
    }
}