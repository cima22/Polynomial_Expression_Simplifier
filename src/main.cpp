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
	//Expr ex = x + 3;
	//std::cout << ex;
	//std::cout << ex1 + ex2;
	std::cout << x + 3 << "\n" << 2 - x << "\n" << y * 2.5 << std::endl;
	
}
