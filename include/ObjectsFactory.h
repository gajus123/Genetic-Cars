//
// Created by igor on 13.01.18.
//

#ifndef GENETIC_CARS_PHYSICSOBJECTSFACTORY_H
#define GENETIC_CARS_PHYSICSOBJECTSFACTORY_H


#include <Box2D/Dynamics/b2World.h>

#include "Loop.h"

namespace Physics {

    class ObjectsFactory {
    public:
        ObjectsFactory(ObjectsFactory const &) = delete;

        ObjectsFactory(ObjectsFactory &&) = delete;

        static ObjectsFactory &init(Loop &p);

        static ObjectsFactory &getInstance();

        std::shared_ptr<b2Body> createExampleBox();

        std::shared_ptr<b2Body> createExampleGround();

        std::shared_ptr<b2Body> createCircle(float32 radius, float32 density, float32 friction);

        std::shared_ptr<b2Body> createPolygon(std::vector<b2Vec2> vertices, float32 density, float32 friction);

        std::shared_ptr<b2Body> createGround(std::vector<b2Vec2> vertices);

    private:
        static ObjectsFactory instance;

        b2World &world;

        explicit ObjectsFactory(b2World &w);
        ObjectsFactory &operator=(ObjectsFactory const &);

        static std::shared_ptr<const b2BodyDef> getDefaultBodyDef() const;
        static std::shared_ptr<const b2FixtureDef> getFixtureDef(b2Shape& shape, float32 density = 1.0f, float32 friction = 0.3f, int16 groupIndex = -1) const;
    };

}
#endif //GENETIC_CARS_PHYSICSOBJECTSFACTORY_H
