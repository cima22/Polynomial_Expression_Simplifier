#include <iostream>
#include "var.h"
#include "expr.h"
#include "expr_child.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};

	Expr& ex = (x + y) * (2 + z);//((x + y) * (2 + z) + 3)*z;
	CompExpr& ex1 = dynamic_cast<CompExpr&>(ex.stretch().stretch().stretch().stretch());
	//Expr& ex2 = ex.stretch().stretch().stretch().stretch().stretch();
	//CompExpr& ex1 = dynamic_cast<CompExpr&>(ex);
		
	std::cout << ex << " = \n" << ex1 << "\n" << ex1.is_extended() << std::endl;//<< ex.extend() << "\n";// << ex2.get_sub_1() << "\t" << ex2.get_sub_2() << std::endl;
/*	std::cout << ex1.get_sub_1() << "\t" << ex1.get_sub_2() << std::endl;
	CompExpr& sub_2 = dynamic_cast<CompExpr&>(ex1.get_sub_2());
	std::cout << sub_2.get_sub_1() << "\t" << sub_2.get_sub_2() << std::endl;
	
	CompExpr& sub_2_2 = dynamic_cast<CompExpr&>(sub_2.get_sub_2());
	std::cout << sub_2_2.get_sub_1() << "\t" << sub_2_2.get_sub_2() << std::endl;
	
	
	CompExpr& sub_2_3 = dynamic_cast<CompExpr&>(sub_2_2.get_sub_2());
	std::cout << sub_2_3.get_sub_1() << "\t" << sub_2_3.get_sub_2() << std::endl;
	//std::cout << "Expr: " << ex << "\nStretch: " << ex.stretch() << std::endl;

	Expr& ex = (x * y) * (2 + x);
	CompExpr& ex1 = dynamic_cast<CompExpr&>(ex);
	std::cout << ex << " = " << ex1.compute_operation();*/
}
