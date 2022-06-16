#include <iostream>
#include "var.h"
#include "expr.h"
#include "expr_child.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};
	
	Expr& ex = ((x + y) * (2 + z) + 3)*z;
	CompExpr& ex1 = dynamic_cast<CompExpr&>(ex.stretch().stretch().stretch().stretch());
	Expr& ex2 = ex.stretch().stretch().stretch().stretch().stretch();
	//CompExpr& ex2 = dynamic_cast<CompExpr&>(ex1.get_sub_2());
	
	std::cout << ex << " = \n" << ex1 << "\n" << ex2 << "\n";// << ex2.get_sub_1() << "\t" << ex2.get_sub_2() << std::endl;

	//std::cout << "Expr: " << ex << "\nStretch: " << ex.stretch() << std::endl;

}
