#include <iostream>
#include "var.h"
#include "expr.h"
#include "expr_child.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x",2};
	Var y{"y",3};
	Var z{"z",4};
	
	VarExpr vx{x};
	VarExpr vy{y};
	CompExpr ex{vx,vy,operation::sum};

	std::cout << ex.to_string() << "\n" << std::endl;

	for(auto&v : ex.get_variables())
		std::cout << v.get_name() << "\n";
}
