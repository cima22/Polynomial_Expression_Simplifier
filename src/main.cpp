#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>
#include <map>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};
	
	Expr ex = x + y;
	VarExpr vx = x;
	VarExpr vy = y;
	ConstExpr c1 = 2;
	ConstExpr c2 = 3;
	CompExpr ex1 = 20 + (z + y) * (2 * x) + 3 + 3*x*y;
	std::cout << ex1 << " = " << ex1.unroll() << std::endl;
	CompExpr ex2 = 16 + 2 * (y + z) * x + y * 3 * x + 7;
	std::cout << ex2 << " = " << ex2.unroll() << std::endl;

}
