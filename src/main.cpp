#include <iostream>
#include "var.h"
#include "expr.h"
#include "expr_child.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x",2};
	Var y{"y",3};
	Var z{"z",4};
	
	Expr& ex = (x + y) * (z * 2);//(x + 2) * (y * z) + 2 * z;
	std::cout << ex << " = " << ex.stretch() << std::endl;

	for(auto&v : ex.stretch().get_variables()){
		std::cout << v.get_name() << "\n";
	}
	

	//std::cout << "Expr: " << ex << "\nStretch: " << ex.stretch() << std::endl;

}
