#define BOOST_TEST_MODULE polynomial_algebraic_expression
#define BOOST_TEST_LOG_LEVEL = all
#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include <boost/test/unit_test_log.hpp>
#include <iostream>
#include "expr.h"
using boost::test_tools::output_test_stream;

Var x{"x"};
Var y{"y"};
Var z{"z"};

Expr ex = (x + y) * (2 - z);

BOOST_AUTO_TEST_CASE(print){
	BOOST_TEST_MESSAGE("Unit testing to show classes features...\n");
	BOOST_TEST_MESSAGE("Testing overload operator <<:");
	BOOST_TEST_MESSAGE("Expression is: " << ex);
	output_test_stream output;
	output << ex;
	BOOST_TEST_REQUIRE(output.is_equal("(x + y) * (2 + -z)"));
}

BOOST_AUTO_TEST_CASE(equal){
	BOOST_TEST_MESSAGE("\nTesting equal(), which compares two expressions:");
	Expr ex2 = 2*y + z*(-y - x) + 2*x;
	BOOST_TEST_MESSAGE(ex << " == " << ex2);
	BOOST_TEST_REQUIRE(equivalent(ex,ex2));
}

BOOST_AUTO_TEST_CASE(unroll){
	BOOST_TEST_MESSAGE("\nTesting unroll(), which returns the expression in the form of sum of monomials");
	Expr unrolled = 2*x + 2*y -z*x -z*y;
	BOOST_TEST_REQUIRE(equivalent(ex,ex.unroll()));
	BOOST_TEST_MESSAGE(ex << " = " << ex.unroll());
}

BOOST_AUTO_TEST_CASE(get_variables){
	BOOST_TEST_MESSAGE("\nTesting get_variables(), which returns a vector containing all the variables in the expression");
	std::vector<Var> vec = {x,y,z};
	std::vector<Var> vec_check = ex.get_variables();
	BOOST_TEST_REQUIRE(std::is_permutation(vec.begin(),vec.end(),vec_check.begin()));
	BOOST_TEST_MESSAGE("Variables in the expression:");
	for(auto& e : vec_check)
		BOOST_TEST_MESSAGE(e);
}

BOOST_AUTO_TEST_CASE(get_coeffs){
	BOOST_TEST_MESSAGE("\nTesting get_coeffs(), which returns a map<unsigned int,Expr> that maps every coefficient with its degree associated with a given variable");
	Expr degree_1 = 2 - z;
	Expr degree_0 = y*(2 - z); 
	std::map<unsigned int, Expr> true_map = {{1,degree_1},{0,degree_0}};
	BOOST_TEST_REQUIRE(true_map == ex.get_coeffs(x));
	BOOST_TEST_MESSAGE("Coefficients related to variable x:");
	for(auto& e : ex.get_coeffs(x))
		BOOST_TEST_MESSAGE("degree : " << e.first << " - coeff : " << e.second);
}

BOOST_AUTO_TEST_CASE(replace){
	BOOST_TEST_MESSAGE("\nTesting replace(), which replaces every occurrence of a variable by a specified expression");
	Expr repl_x = 3*z;
	Expr repl_z = x*y;
	std::map<Var,Expr> repl = {{x,repl_x},{z,repl_z}};
	Expr replaced = ex.replace(repl);
	Expr true_replaced = (3*z + y) * (2 - x*y);
	BOOST_TEST_REQUIRE(equivalent(replaced,true_replaced));
	BOOST_TEST_MESSAGE("Replace x with " << repl_x << " and z with " << repl_z << " => " << replaced);
}
