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
	Expr ex = (x + y);
	//const Expr& str = ex.stretch();//ex.stretch() << std::endl;
	//Expr cex{ex.get_obj().stretch()};
	//std::cout << cex;
	//std::cout << 	&ex.get_obj().stretch();
	CompExpr cex = x + y;
	//CompExpr cex2 = cex;
	CompExpr* cex2 = new CompExpr{cex};
	std::cout << cex << std::endl;
	std::cout << *cex2 << std::endl;
	delete cex2;
	std::cout << cex<<std::endl;
}
