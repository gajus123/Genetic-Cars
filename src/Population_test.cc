#include <boost/test/unit_test.hpp>

#include "Population.h"

using namespace Algorithm;

BOOST_AUTO_TEST_SUITE(PopulationTests);

BOOST_AUTO_TEST_CASE(check_empty_constructor_creates_empty_population)
{
	Population p;
	BOOST_CHECK_EQUAL(p.getGenotypes().size(), 0);
}

BOOST_AUTO_TEST_CASE(check_genotypes_constructor_copies_genotypes_vector_by_size)
{
	std::vector<Genotype> v(8);
	Population p(v);
	BOOST_CHECK_EQUAL(p.getGenotypes().size(), v.size());
}

BOOST_AUTO_TEST_CASE(check_setting_mutation_rate)
{
	Population p;
	p.setMutationRate(1.7f);
	BOOST_CHECK_EQUAL(p.getMutationRate(), 1.7f);
}

BOOST_AUTO_TEST_CASE(check_seting_elite_specimen)
{
	Population p;
	p.setEliteSpecimen(9);
	BOOST_CHECK_EQUAL(p.getEliteSpecimen(), 9);
}

BOOST_AUTO_TEST_CASE(check_seting_generation_size)
{
	Population p;
	p.setNextGenerationSize(29);
	BOOST_CHECK_EQUAL(p.getNextGenerationSize(), 29);
}

BOOST_AUTO_TEST_CASE(check_genotypes_vector_size_ater_inflate_random)
{
	Population p;
	p.setNextGenerationSize(12);
	p.inflateRandom();
	BOOST_CHECK_EQUAL(p.getGenotypes().size(), 12);
}

BOOST_AUTO_TEST_SUITE_END();


