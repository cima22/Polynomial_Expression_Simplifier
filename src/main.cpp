#include <iostream>
#include "expr.h"

int main(int argc, char* argv[]){

	Var v{"x",4};
	std::cout << v << std::endl;
	v.set_value(5.5);
	std::cout << "New v: " << v << std::endl;
	Var v2{"ciao", 4.5};
	std::cout << v2 << std::endl;
	Var z = v + v2;
	z.set_name("z");
	std::cout << z << std::endl;

	std::cout << v * z << std::endl << z - v << std::endl;

	Expr ex1{"x + y - 4"};
	std::cout << ex1;
}
