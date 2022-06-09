#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>
/*
Expr operator+(const Var& v, int c){
	std::vector<Var> vars{v};
	std::string expr = v.get_name() + " + " + std::to_string(c);
	return Expr{expr,vars};
}*/

int main(int argc, char* argv[]){

	Expr ex1{"x + z"};
	Expr ex2{"23 + z + p"};

	Var x{"x",2};
	Var y{"y",3};
	Var z{"z",4};
		
	Expr ex{"x + y * 2"};
	std::cout << ex << std::endl;

	for(auto& v : ex.get_variables())
		std::cout << v.get_name() << "\n";
}
