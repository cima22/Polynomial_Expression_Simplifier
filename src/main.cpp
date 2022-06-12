#include <iostream>
#include "var.h"
#include "expr.h"
#include "varExpr.h"
#include "constExpr.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x",2};
	Var y{"y",3};
	Var z{"z",4};
		
	Expr ex = (x + y) * (z + 2);
	std::cout << ex << std::endl;

	VarExpr v_x{x};
	for(auto& v : v_x.get_variables())
		std::cout << v.get_name() << "\n";

	ConstExpr c{1};

	std::cout << v_x << "\n" << c << std::endl;
}
