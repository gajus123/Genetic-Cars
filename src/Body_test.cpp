#include <boost/test/unit_test.hpp>

#include "include/Body.h"

using namespace Physics;
using namespace Objects;

struct BodyTestFixture {
	BodyTestFixture() :
		l(b2Vec2(0.0f, 9.8f), 4, 8),
		obj(ObjectsFactory::init(l.getWorld())) {
	}
	Loop l;
	ObjectsFactory& obj;
	std::vector<float> lenghts = { 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f };
};

BOOST_FIXTURE_TEST_SUITE(ObjectsFactoryTests, BodyTestFixture);

BOOST_AUTO_TEST_CASE(check_there_are_8_vertices)
{
	Body b(lenghts, Vector2(0.0f, 0.0f));
	BOOST_CHECK_EQUAL(b.getVertices().size(), 8);
}

BOOST_AUTO_TEST_CASE(check_body_vertices_are_calculated_propertly)
{
	Body b(lenghts, Vector2(0.0f, 0.0f));
	auto v = b.getVertices();
	
	BOOST_CHECK_EQUAL(v[0].x, 0.0f);
	BOOST_CHECK_EQUAL(v[0].y, 0.1f);
	
	BOOST_CHECK_EQUAL(v[1].x, -0.2f);
	BOOST_CHECK_EQUAL(v[1].y, 0.2f);

	BOOST_CHECK_EQUAL(v[2].x, -0.3f);
	BOOST_CHECK_EQUAL(v[2].y, 0.0f);

	BOOST_CHECK_EQUAL(v[3].x, -0.4f);
	BOOST_CHECK_EQUAL(v[3].y, -0.4f);

	BOOST_CHECK_EQUAL(v[4].x, 0.0f);
	BOOST_CHECK_EQUAL(v[4].y, -0.5f);

	BOOST_CHECK_EQUAL(v[5].x, 0.6f);
	BOOST_CHECK_EQUAL(v[5].y, -0.6f);

	BOOST_CHECK_EQUAL(v[6].x, 0.7f);
	BOOST_CHECK_EQUAL(v[6].y, 0.0f);

	BOOST_CHECK_EQUAL(v[7].x, 0.8f);
	BOOST_CHECK_EQUAL(v[7].y, 0.8f);
}

BOOST_AUTO_TEST_CASE(check_body_current_vertices_are_calculated_propertly)
{
	Body b(lenghts, Vector2(1.0f, 2.0f));
	auto v = b.getCurrentVertices();

	BOOST_CHECK_EQUAL(v[0].x, 1.0f);
	BOOST_CHECK_EQUAL(v[0].y, 2.1f);

	BOOST_CHECK_EQUAL(v[1].x, 0.8f);
	BOOST_CHECK_EQUAL(v[1].y, 2.2f);

	BOOST_CHECK_EQUAL(v[2].x, 0.7f);
	BOOST_CHECK_EQUAL(v[2].y, 2.0f);

	BOOST_CHECK_EQUAL(v[3].x, 0.6f);
	BOOST_CHECK_EQUAL(v[3].y, 1.6f);

	BOOST_CHECK_EQUAL(v[4].x, 1.0f);
	BOOST_CHECK_EQUAL(v[4].y, 1.5f);

	BOOST_CHECK_EQUAL(v[5].x, 1.6f);
	BOOST_CHECK_EQUAL(v[5].y, 1.4f);

	BOOST_CHECK_EQUAL(v[6].x, 1.7f);
	BOOST_CHECK_EQUAL(v[6].y, 2.0f);

	BOOST_CHECK_EQUAL(v[7].x, 1.8f);
	BOOST_CHECK_EQUAL(v[7].y, 2.8f);

}

BOOST_AUTO_TEST_SUITE_END();
