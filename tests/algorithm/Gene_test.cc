//
// \author Jakub Gajownik
// \date 14.03.18
//

#include <boost/test/unit_test.hpp>
#include <limits>

#include <algorithm/Gene.hpp>

BOOST_AUTO_TEST_SUITE(GeneTests);

BOOST_AUTO_TEST_CASE(gene_constructor_and_value)
{
	Algorithm2::Gene g(412441);
	BOOST_CHECK_EQUAL(g.value(), 412441);
}

BOOST_AUTO_TEST_SUITE_END();