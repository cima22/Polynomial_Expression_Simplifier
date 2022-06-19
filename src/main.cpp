#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};
	
//	Expr ex = (x + y) * (x + z) + 3 + y;
//	Expr ex = 3 + x;
//	std::cout << ex << std::endl;
//	Expr ex1 = ex.extend();
//	std::cout << ex << " = " << ex1 << std::endl;
	CompExpr cex = (x + y);
	cex.stretch();

}
