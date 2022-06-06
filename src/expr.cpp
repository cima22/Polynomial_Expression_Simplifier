#include <iostream>
#include <vector>
#include "expr.h"

Expr::Expr(const std::string& expression):
	expression{expression}
	{}

std::ostream& operator<< (std::ostream& os, const Expr& expr){
	os << expr.expression;
	return os;
}
