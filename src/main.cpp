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
	
	Expr ex =  2*x + 5 + (x + y) * (x*x -2) + 7;
	std::cout << ex << " = " << ex.unroll() << std::endl;
}
