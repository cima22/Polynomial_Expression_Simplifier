#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>
#include <map>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};
	
	Expr ex = (y + x + 2) * y + 45 + z;
	std::map<unsigned int,Expr> m{};
	std::cout << ex << "\n";
	m = ex.get_coeffs(y);
	for(auto& e : m)
		std::cout << e.first << " : " << e.second << "\n";

}
