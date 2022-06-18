#include <iostream>
#include "var.h"
#include "expr.h"
#include <string>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};
	
	VarExpr vx{x};
	VarExpr vy{y};
	//Expr ex = (2 * x) + 3;		
	//std::cout << ex << std::endl;
	CompExpr& ce = * new CompExpr{vx,vy,operation::sum};
	Expr ex;
	ex = ce;
	
}
