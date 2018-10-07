#include <boost/test/unit_test.hpp>
#include <vector>

#include <Vehicle.h>
#include <World.h>
#include <ObjectsFactory.h>

using namespace Physics;
using namespace Objects;

struct VehicleTestFixture {
	VehicleTestFixture() :
		w(b2Vec2(0.0f, 9.8f), 4, 8),
		obj(ObjectsFactory::init(w.getWorld())),
		heights(8, 1.0f){
	}
	World w;
	ObjectsFactory& obj;
	std::vector<float> heights;
};


BOOST_FIXTURE_TEST_SUITE(VehicleTests, VehicleTestFixture);

BOOST_AUTO_TEST_CASE(check_creation_position) 
{
	Vehicle v(Vector2(1.1f, 2.1f), heights, 0.1f, 0.1f);
	BOOST_CHECK_EQUAL(v.getPosition().x, 1.1f);
	BOOST_CHECK_EQUAL(v.getPosition().y, 2.1f);
}

BOOST_AUTO_TEST_CASE(check_wheels_radius)
{
	Vehicle v(Vector2(1.1f, 2.1f), heights, 1.1f, 2.1f);
	BOOST_CHECK_EQUAL(v.getFrontWheel().getRadius(), 1.1f);
	BOOST_CHECK_EQUAL(v.getBackWheel().getRadius(), 2.1f);
}

BOOST_AUTO_TEST_CASE(check_body_vertices)
{
	Vehicle v(Vector2(1.1f, 2.1f), heights, 1.1f, 2.1f);
	auto& vert = v.getBody().getVertices();

	BOOST_CHECK_EQUAL(vert[0].x, 0.0f);
	BOOST_CHECK_EQUAL(vert[0].y, 1.0f);

	BOOST_CHECK_EQUAL(vert[1].x, -1.0f);
	BOOST_CHECK_EQUAL(vert[1].y, 1.0f);

	BOOST_CHECK_EQUAL(vert[2].x, -1.0f);
	BOOST_CHECK_EQUAL(vert[2].y, 0.0f);

	BOOST_CHECK_EQUAL(vert[3].x, -1.0f);
	BOOST_CHECK_EQUAL(vert[3].y, -1.0f);

	BOOST_CHECK_EQUAL(vert[4].x, 0.0f);
	BOOST_CHECK_EQUAL(vert[4].y, -1.0f);

	BOOST_CHECK_EQUAL(vert[5].x, 1.0f);
	BOOST_CHECK_EQUAL(vert[5].y, -1.0f);

	BOOST_CHECK_EQUAL(vert[6].x, 1.0f);
	BOOST_CHECK_EQUAL(vert[6].y, 0.0f);

	BOOST_CHECK_EQUAL(vert[7].x, 1.0f);
	BOOST_CHECK_EQUAL(vert[7].y, 1.0f);
}

BOOST_AUTO_TEST_SUITE_END();
