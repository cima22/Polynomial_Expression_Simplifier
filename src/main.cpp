#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};
	
	Expr ex = ((x + y)* 2 + 3) * (z + y);
	std::cout << ex << " = " << ex.extend() << std::endl;
}
