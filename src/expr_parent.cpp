#include "expr_parent.h"
#include <string>

ParentExpr::ParentExpr() = default;

ParentExpr::~ParentExpr(){};

ParentExpr::ParentExpr(const std::string& expr):
	expression{expr},vars{}{

	extract_vars();

	}

ParentExpr::ParentExpr(const std::string& expr, const std::vector<Var>& vars):
	expression{expr},vars{vars}{}

void ParentExpr::extract_vars(){
	
	std::string work = expression;
	std::vector<char> names;
	for(const char c : work){
		if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z')) // go to next character if 
				continue;
		if(std::find(names.begin(),names.end(),c) == names.end()) // check if it is a new variable
			names.push_back(c);
	}
	for(const char name : names)
		vars.push_back(Var{std::string(1,name)});

}

std::vector<Var> ParentExpr::get_variables() const { return vars; }

const std::string& ParentExpr::to_string() const { return expression; }

//------------------------- From now on, operators definition only ---------------------------------------------------

std::ostream& operator<<(std::ostream& os, const ParentExpr& expr){
	os << expr.expression;
	return os;
}
