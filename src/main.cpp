#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>
#include <map>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};
	
	VarExpr vx = x;
	ConstExpr c = 2;
	CompExpr ex = (2 * x * y * 3 * x) + x ;//+ 4 + x * x;
	std::map<unsigned int,const ParentExpr*> m{};
	m = ex.get_coeffs(y);
	for(auto& e : m)
		std::cout << e.first << " : " << *e.second << "\n";

}
