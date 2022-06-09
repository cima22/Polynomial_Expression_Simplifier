#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x",2};
	Var y{"y",3};
	Var z{"z",4};
		
	Expr ex1 = (x - 4 * y + 3) * x - 2;
	std::cout << ex1 << std::endl;
}
