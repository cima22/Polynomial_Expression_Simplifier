#include <iostream>
#include "var.h"
#include "expr.h"
#include "expr_child.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};

	Expr& ex = 2 + 3 + x * (z + y * (2 + z));		
	std::cout << ex << " = \n" << ex.extend() << std::endl;
	
}
