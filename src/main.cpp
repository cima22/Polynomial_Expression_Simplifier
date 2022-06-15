#include <iostream>
#include "var.h"
#include "expr.h"
#include "expr_child.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x",2};
	Var y{"y",3};
	Var z{"z",4};
	
	Expr& ex = (x + z) * (y * 2);
	//Expr& ex2 = (x + y) * 3;
	CompExpr& ex1 = dynamic_cast<CompExpr&>(ex);
	//CompExpr& ex3= dynamic_cast<CompExpr&>(ex2);
	std::cout << ex << " = " << ex1.mult(); //<< "\n" << ex2 << " = " << ex3.distr_law().stretch() << std::endl;

	//std::cout << "Expr: " << ex << "\nStretch: " << ex.stretch() << std::endl;

}
