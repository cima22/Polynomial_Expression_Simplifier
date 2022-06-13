#include <iostream>
#include "var.h"
#include "expr.h"
#include "expr_child.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x",2};
	Var y{"y",3};
	Var z{"z",4};
	
	Expr& ex = x + 1 + 2;
	Expr& ex1 = 2 * (y + z);
	std::cout << ex << "\n" << ex1 << std::endl;
}
