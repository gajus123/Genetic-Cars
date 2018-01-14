//
// Created by igor on 13.01.18.
//

#include "include/Body.h"

#include "include/ObjectsFactory.h"

namespace Objects {

    void Body::beforeBodySetUp() {
        calculateVertices();
    }

    void Body::calculateVertices() {
        assert(lengths.size() == BODY_SEGMENTS);
        std::vector<Vector2> normals = {
                {0.0f, 1.0f},
                {-1.0f, 1.0f},
                {-1.0f, 0.0f},
                {-1.0f, -1.0f},
                { 0.0f, -1.0f},
                {1.0f, -1.0f},
                {1.0f, 0.0f},
                {1.0f, 1.0f},
        };
        for (int i = 0; i < normals.size(); ++i) {
            vertices.emplace_back(normals[i] * lengths[i]);
        }
    }

    void Body::createAndSetBody() {
        std::vector<b2Vec2> b2_vertices;
        for (const auto &item : vertices) {
            b2_vertices.push_back(item.asb2Vec2());
        }
        body = Physics::ObjectsFactory::getInstance().createPolygon(b2_vertices, 1.0f, 0.3f);
    }

    std::vector<Vector2> Body::getCurrentVertices() const {
		Vector2 position = getPosition();
        std::vector<Vector2> curr_vertices;
        for (const auto &v : vertices) {
            curr_vertices.emplace_back(v + position);
        }
        return curr_vertices;
    }

}