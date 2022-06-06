#include <iostream>
#include "var.h"

int main(int argc, char* argv[]){

	Var v{"x",4};
	std::cout << v << std::endl;
	v.set_value(5.5);
	std::cout << "New v: " << v << std::endl;
	Var v2{"ciao"};
	std::cout << v2 << std::endl;
}
