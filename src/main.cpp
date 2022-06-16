#include <iostream>
#include "var.h"
#include "expr.h"
#include "expr_child.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};
	
	Expr& ex = (x + y) + (z + 2);//((x + y) * (2 + z) + 3)*z;
	CompExpr& ex1 = dynamic_cast<CompExpr&>(ex);
	std::cout << ex << " = \n" << ex1.sum() << "\n" << ex1.sum().get_sub_1() << "\t" << ex1.sum().get_sub_2() << std::endl;

	

	//std::cout << "Expr: " << ex << "\nStretch: " << ex.stretch() << std::endl;

}
