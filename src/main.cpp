#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x",2};
	Var y{"y",3};
	Var z{"z",4};
		
	Expr ex = x + y + z;
	std::cout << ex << "\n" << ex.stretch() << std::endl;
}
