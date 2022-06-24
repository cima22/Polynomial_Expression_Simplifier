#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>
#include <map>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};
	
	Expr ex = x + 0 +0+0+0+0+0;
	std::cout << ex << " = " << ex.unroll() << std::endl;

}
