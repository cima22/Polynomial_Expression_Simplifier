#include <iostream>
#include "var.h"
#include "expr.h"
#include <new>
#include <string>
#include <map>

int main(int argc, char* argv[]){

	Var x{"x"};
	Var y{"y"};
	Var z{"z"};

	Expr ex = (x + y) * (z * 2);
	{
	Expr ex2 = ex;
}	

std::cout << ex << std::endl;

}
