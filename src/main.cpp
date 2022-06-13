#include <iostream>
#include "var.h"
#include "expr.h"
#include "expr_child.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x",2};
	Var y{"y",3};
	Var z{"z",4};
	
	Expr& ex = x + 2;
	Expr& ex2 = 2 * y;
	Expr& ex3 = 10 - z;
	Expr& ex4 = x * z;
	std::cout << ex << "\n" << ex2 << "\n" << ex3 << "\n" << ex4 << std::endl;
}
