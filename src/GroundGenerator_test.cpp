#include <boost/test/unit_test.hpp>

#include "include/GroundGenerator.h"

using namespace Physics;
using namespace Objects;

struct GroundGeneratorTestFixture {
	GroundGeneratorTestFixture() :
		l(b2Vec2(0.0f, 9.8f), 4, 8),
		obj(ObjectsFactory::init(l.getWorld())) {
	}
	Loop l;
	ObjectsFactory& obj;
};


BOOST_FIXTURE_TEST_SUITE(GroundGeneratorTests, GroundGeneratorTestFixture);

BOOST_AUTO_TEST_CASE(check_ground_creates_right_amount_of_segments) 
{
	GroundGenerator gg(100, 1.1f);
	Ground* g = gg.genereteNew(Vector2(0.0f, 0.0f));
	BOOST_CHECK_EQUAL(g->getVertices()[g->getVertices().size() - 1].x, 110.0f);
}

BOOST_AUTO_TEST_SUITE_END();
