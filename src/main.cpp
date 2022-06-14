#include <iostream>
#include "var.h"
#include "expr.h"
#include "expr_child.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x",2};
	Var y{"y",3};
	Var z{"z",4};
	
	Expr& ex = x + 2 + 3;
	std::cout << ex;
	//std::cout << "Expr: " << ex << "\nStretch: " << ex.stretch() << std::endl;

}
