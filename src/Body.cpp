//
// \author Rafa³ Galczak
// \date 14.01.18
//

#include "include/Body.h"

#include "include/ObjectsFactory.h"

namespace Objects {

	const unsigned int Body::BODY_SEGMENTS = 8;
	const float Body::BODY_FRICTION = Physics::DEFAULT_FRICTION * 100.0f;
	

    void Body::beforeBodySetUp() {
        calculateVertices();
    }

    void Body::calculateVertices() {
        assert(lengths_.size() == BODY_SEGMENTS);
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
            vertices_.emplace_back(normals[i] * lengths_[i]);
        }
    }

    void Body::createAndSetBody() {
        std::vector<b2Vec2> b2_vertices;
        for (const auto &item : vertices_) {
            b2_vertices.push_back(item.asb2Vec2());
        }
        body = Physics::ObjectsFactory::getInstance().createPolygon(b2_vertices, Physics::DEFAULT_DENSITY, BODY_FRICTION);
    }

    std::vector<Vector2> Body::getCurrentVertices() const {
		Vector2 position = getPosition();
        std::vector<Vector2> curr_vertices;
        for (const auto &v : vertices_) {
            curr_vertices.emplace_back(v + position);
        }
        return curr_vertices;
    }

}