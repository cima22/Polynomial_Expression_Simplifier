#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};

	Expr ex = 2 * x;		
	std::cout << ex << std::endl;
	
}
