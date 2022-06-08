#include "expr.h"

Expr::Expr(const std::string& expr):
	expression{expr},vars{}{

//	extract_vars();

	}

Expr::Expr(const std::string& expr, const std::vector<Var>& vars):
	expression{expr},vars{vars}{}

void Expr::extract_vars(){
	
	std::string work = expression;
	std::vector<char> names;
	for(const char c : work){
		if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z')) // go to next character if 
				continue;
		if(std::find(names.begin(),names.end(),c) == names.end()){ // check if it is a new variable
			std::cout << c << std::endl;
			names.push_back(c);
		}	
	}
}

std::ostream& operator<<(std::ostream& os, const Expr& expr){
	os << expr.expression;
	return os;
}

Expr operator+(const Expr& e1, const Expr& e2){
	std::string sum = e1.expression + " + " + e2.expression;
	return Expr{sum};
}

Expr operator+(const Expr& e1, int i){
	std::string sum = e1.expression + " + " + std::to_string(i);
	return Expr{sum};
}
