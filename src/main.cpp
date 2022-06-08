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
	//std::cout << "x+3 = " << x + 3 << "\n" << "5*y = " << 5*y << "\n" << "x-y = " << x-y << "\n" <<"y*y = " << y * y << std::endl;
	/*
	std::vector<Var> vars = (y + x).get_variables();
	for(auto& v : vars)
		std::cout << v.get_name() << "\n";

	int a = 2 + 3 * 4;
	std::cout << a << std::endl;
	*/
	Expr ex = (x + 2 + y) * (y * (x - 10));
	std::cout << ex << std::endl;
	for(auto& v : ex.get_variables())
		std::cout << v.get_name() << "\n";
}
