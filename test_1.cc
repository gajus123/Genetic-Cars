#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestApplicationFramework)

BOOST_AUTO_TEST_CASE(OneIsLessThanTwo)
{
	BOOST_CHECK(2<1);
}

BOOST_AUTO_TEST_SUITE_END()