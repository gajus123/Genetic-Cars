#include <boost/test/unit_test.hpp>

#include <physics/objects/Wheel.h>
#include <physics/World.h>
#include <physics/objects/ObjectsFactory.h>

using namespace Physics;
using namespace Objects;

struct WheelTestFixture {
	WheelTestFixture() :
		w(b2Vec2(0.0f, 9.8f), 4, 8),
		obj(ObjectsFactory::init(w.getWorld())) {
	}
	World w;
	ObjectsFactory& obj;
};

BOOST_FIXTURE_TEST_SUITE(WheelTests, WheelTestFixture);

BOOST_AUTO_TEST_CASE(upon_creation_position_is_set_correctly)
{
	Wheel w({2.1f, 3.5f}, 0.1f);
	BOOST_CHECK_EQUAL(w.getPosition().x, 2.1f);
	BOOST_CHECK_EQUAL(w.getPosition().y, 3.5f);
}

BOOST_AUTO_TEST_CASE(radius_is_set_correctly)
{
	Wheel w({ 2.1f, 3.5f }, 0.1f);
	BOOST_CHECK_EQUAL(w.getRadius(), 0.1f);
}

BOOST_AUTO_TEST_CASE(upon_creation_angle_is_zero)
{
	Wheel w({ 2.1f, 3.5f }, 0.1f);
	BOOST_CHECK_EQUAL(w.getAngle(), 0.0f);
}

BOOST_AUTO_TEST_SUITE_END();