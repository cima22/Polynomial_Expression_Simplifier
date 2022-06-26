#define BOOST_TEST_MODULE polynomial_algebraic_expression
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include <iostream>
using boost::test_tools::output_test_stream;

BOOST_AUTO_TEST_CASE(print){
	output_test_stream output;
	output << "cxiao";
	BOOST_TEST_MESSAGE("Test");
	BOOST_TEST(output.is_equal("ciao"),"cai");
}
