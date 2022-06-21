#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>
#include <map>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};
	
	Expr ex = x + y;
	std::map<Var,Expr> m;
	Expr ex1 = y;
	Expr ex2 = 2 * z;
	m.insert({x,ex1});
	m.insert({y,ex2});
	std::cout << ex << " --> " << ex.replace(m) << "\n";
}
