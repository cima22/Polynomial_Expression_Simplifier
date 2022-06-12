#include "constExpr.h"
#include <string>

ConstExpr::ConstExpr(const int i):
	Expr(std::to_string(i)){}
