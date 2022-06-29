#include<iostream>
#include<string>

struct NotMonomial { // Exception that is thrown whenever a CompExpr that is not a monomial tries to use a method which is only for monomials

	std::string message;

	NotMonomial();
	NotMonomial(std::string message);

};
