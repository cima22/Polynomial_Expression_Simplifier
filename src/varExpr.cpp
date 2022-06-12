#include "expr_child.h"
#include <string>

VarExpr::VarExpr(const Var& v):
	Expr(v.get_name(),{v}){}

ConstExpr::ConstExpr(const int i):
	Expr(std::to_string(i)){}
