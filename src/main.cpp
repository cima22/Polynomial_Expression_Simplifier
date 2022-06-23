#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>
#include <map>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};
	
	Expr ex = 2*(x + y)*(z*z) + 48;
	Expr ex2 = 40 + (x*2*z + y*z*2)*z + 8;
	if(equivalent(ex,ex2))
		std::cout << ex << " = " << ex2 << std::endl;

}
