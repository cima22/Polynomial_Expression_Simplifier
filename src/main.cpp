#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};

	Expr ex = (2 * x) + 3;		
	std::cout << ex << std::endl;

	while(1){}
	
}
