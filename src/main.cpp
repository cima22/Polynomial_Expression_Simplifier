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
	Expr ex_s = ex.get_obj().stretch();	
	std::cout << ex.get_obj().stretch() << std::endl;
}
