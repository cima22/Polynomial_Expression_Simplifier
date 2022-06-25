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

	CompExpr ex = 2 * (x + y) * z;
	std::cout << ex << " = " << ex.extend() << std::endl;

}
