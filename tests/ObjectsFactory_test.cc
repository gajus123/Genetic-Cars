#include <vector>
#include <boost/test/unit_test.hpp>

#include <physics/World.h>
#include <physics/objects/ObjectsFactory.h>

using namespace Physics;

struct ObjectsFactoryTestFixture {
	ObjectsFactoryTestFixture() : 
		w(b2Vec2(0.0f, 9.8f), 4, 8),
		obj(ObjectsFactory::init(w.getWorld())){
	}
	World w;
	ObjectsFactory& obj;
};

BOOST_FIXTURE_TEST_SUITE(ObjectsFactoryTests, ObjectsFactoryTestFixture);

BOOST_AUTO_TEST_CASE( Check_createCircleBody_world_equals_to_loops_world) 
{
	b2Body* b = obj.createCircle(5.0f, 4.5f, 3.5f);
	BOOST_CHECK_EQUAL(b->GetWorld(), w.getWorld());
}

BOOST_AUTO_TEST_CASE(Check_circle_position_is_zero) 
{
	b2Body* b = obj.createCircle(5.0f, 4.5f, 3.5f);
	BOOST_CHECK_EQUAL(b->GetPosition().x, 0.0f);
	BOOST_CHECK_EQUAL(b->GetPosition().y, 0.0f);
}

BOOST_AUTO_TEST_CASE(Check_createPolygon_body_world_equals_to_loops_world)
{
	b2Body* b = obj.createPolygon({ 
			{1.0f, 1.0f},
			{0.0f, 0.0f},
			{1.0f, -1.0f}
		},
		4.5f,
		3.5f);
	BOOST_CHECK_EQUAL(b->GetWorld(), w.getWorld());
}

BOOST_AUTO_TEST_CASE(Check_polygon_position_is_zero)
{
	b2Body* b = obj.createPolygon({
		{ 1.0f, 1.0f },
		{ 0.0f, 0.0f },
		{ 1.0f, -1.0f }
	},
		4.5f,
		3.5f);
	BOOST_CHECK_EQUAL(b->GetPosition().x, 0.0f);
	BOOST_CHECK_EQUAL(b->GetPosition().y, 0.0f);
}

BOOST_AUTO_TEST_CASE(Check_createGround_world_equals_to_loops_world)
{
	b2Body* b = obj.createGround({
		{0.0f, 0.0f},
		{1.0f, 1.0f}
	});
	BOOST_CHECK_EQUAL(b->GetWorld(), w.getWorld());
}

BOOST_AUTO_TEST_CASE(Check_ground_position_is_zero)
{
	b2Body* b = obj.createGround({
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f }
	});
	BOOST_CHECK_EQUAL(b->GetPosition().x, 0.0f);
	BOOST_CHECK_EQUAL(b->GetPosition().y, 0.0f);
}


BOOST_AUTO_TEST_SUITE_END();

