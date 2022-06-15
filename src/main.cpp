#include <iostream>
#include "var.h"
#include "expr.h"
#include "expr_child.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x",2};
	Var y{"y",3};
	Var z{"z",4};
	
	Expr& ex = ((x + y) * (2 + z) + 3)*z;
	//CompExpr& ex1 = dynamic_cast<CompExpr&>(ex);
	std::cout << ex << " = \n" << ex.stretch() << std::endl;

	

	//std::cout << "Expr: " << ex << "\nStretch: " << ex.stretch() << std::endl;

}
