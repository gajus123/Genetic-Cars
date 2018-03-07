#include <boost/test/unit_test.hpp>

#include "include/Ground.h"

using namespace Physics;
using namespace Objects;

struct GroundTestFixture {
	GroundTestFixture() :
		l(b2Vec2(0.0f, 9.8f), 4, 8),
		obj(ObjectsFactory::init(l.getWorld())) {
	}
	Loop l;
	ObjectsFactory& obj;
	std::vector<float> heights = { 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f };
};


BOOST_FIXTURE_TEST_SUITE(GroundTests, GroundTestFixture);

BOOST_AUTO_TEST_CASE(check_returs_valid_x_distance)
{
	Ground g(Vector2(0.0f, 0.0f), 1.1f, heights);
	BOOST_CHECK_EQUAL(g.getXDistance(), 1.1f);
}

BOOST_AUTO_TEST_CASE(check_returs_valid_heights)
{
	Ground g(Vector2(0.0f, 0.0f), 1.0f, heights);
	for (int i = 0; i < heights.size(); ++i) {
		BOOST_CHECK_EQUAL(g.getHeights()[i], heights[i]);
	}
}

BOOST_AUTO_TEST_CASE(check_returs_valid_vertices)
{
	Ground g(Vector2(0.0f, 0.0f), 1.1f, heights);
	for (int i = 0; i < heights.size(); ++i) {
		BOOST_CHECK_EQUAL(g.getVertices()[i].x, 1.1f*i);
		BOOST_CHECK_EQUAL(g.getVertices()[i].y, heights[i]);
	}
}

BOOST_AUTO_TEST_SUITE_END();