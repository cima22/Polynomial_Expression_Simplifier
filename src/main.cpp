#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>
#include <map>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};
	
	VarExpr ex = x;
	//std::cout << ex.get_degree(x) << std::endl;
	std::map<unsigned int, const ParentExpr*> m = ex.get_coeffs(x);
	for(auto& e : m)
		std::cout << e.first << ":" << e.second->to_string() << std::endl;
	

}
