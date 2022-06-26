#include <iostream>
#include "expr_parent.h"
#include "var.h"
#include "expr.h"
#include <new>
#include <string>
#include <map>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};

	Expr ex = -x + (x + z) * (z + 2) - z*z;
	std::cout << ex << " = " << ex.unroll() << std::endl;

}
