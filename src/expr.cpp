#include "expr.h"
#include <string>

Expr::Expr() = default;

Expr::Expr(const std::string& expr):
	expression{expr},vars{}{

	extract_vars();

	}

Expr::Expr(const std::string& expr, const std::vector<Var>& vars):
	expression{expr},vars{vars}{}

void Expr::extract_vars(){
	
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

std::vector<Var> Expr::get_variables() const { return vars; }

const std::string& Expr::to_string() const { return expression; }

//------------------------- From now on, operators definition only ---------------------------------------------------
/*
std::ostream& operator<<(std::ostream& os, const Expr& expr){
	os << expr.expression;
	return os;
}

Expr operator+ (const Var& v, int c){
	std::vector<Var> vars{v};
	std::string expr = v.get_name() + " + " + std::to_string(c);
	return Expr{expr,vars};
}

Expr operator+ (int c, const Var& v){
	std::vector<Var> vars{v};
	std::string expr = std::to_string(c) + " + " +  v.get_name();
	return Expr{expr,vars};
}

Expr operator- (const Var& v, int c){
	std::vector<Var> vars{v};
	std::string expr = v.get_name() + " - " + std::to_string(c);
	return Expr{expr,vars};
}

Expr operator- (int c, const Var& v){
	std::vector<Var> vars{v};
	std::string expr = std::to_string(c) + " - " + v.get_name();
	return Expr{expr,vars};
}

Expr operator* (const Var& v, int c){
	std::vector<Var> vars{v};
	std::string expr = v.get_name() + " * " + std::to_string(c);
	return Expr{expr,vars};
}

Expr operator* (int c, const Var& v){
	std::vector<Var> vars{v};
	std::string expr = std::to_string(c) + " * " + v.get_name();
	return Expr{expr,vars};
}

Expr operator+ (const Var& v1, const Var& v2){
	std::vector<Var> vars{v1};
	if(v1.get_name().compare(v2.get_name()) != 0)
		vars.push_back(v2);
	std::string expr = v1.get_name() + " + " + v2.get_name();
	return Expr{expr,vars};
}

Expr operator- (const Var& v1, const Var& v2){
	std::vector<Var> vars{v1};
	if(v1.get_name().compare(v2.get_name()) != 0)
		vars.push_back(v2);
	std::string expr = v1.get_name() + " - " + v2.get_name();
	return Expr{expr,vars};
}

Expr operator* (const Var& v1, const Var& v2){
	std::vector<Var> vars{v1};
	if(v1.get_name().compare(v2.get_name()) != 0)
		vars.push_back(v2);
	std::string expr = v1.get_name() + " * " + v2.get_name();
	return Expr{expr,vars};
}

Expr operator+ (const Expr& e1, int i){
	std::string expr = "(" + e1.expression + ") + " + std::to_string(i);
	return Expr{expr,e1.get_variables()};
}

Expr operator+(int i, const Expr& e1){
	std::string expr = std::to_string(i) + " + (" + e1.expression + ")";
	return Expr{expr,e1.get_variables()};
}

Expr operator- (const Expr& e1, int i){
	std::string expr = "(" + e1.expression + ") - " + std::to_string(i);
	return Expr{expr,e1.get_variables()};
}

Expr operator-(int i, const Expr& e1){
	std::string expr = std::to_string(i) + " - (" + e1.expression + ")";
	return Expr{expr,e1.get_variables()};
}

Expr operator* (const Expr& e1, int i){
	std::string expr = "(" + e1.expression + ") * " + std::to_string(i);
	return Expr{expr,e1.get_variables()};
}

Expr operator*(int i, const Expr& e1){
	std::string expr = std::to_string(i) + " * (" + e1.expression + ")";
	return Expr{expr,e1.get_variables()};
}

Expr operator+ (const Expr& e1, const Var& v1){
	std::string expr = "(" + e1.expression + ") + " + v1.get_name();
	std::vector<Var> vars{e1.get_variables()};
	bool already_present = false;
	for(auto& v : e1.get_variables())
		if(!v.get_name().compare(v1.get_name())){
			already_present = true;
			break;
		}
	if(!already_present)
		vars.push_back(v1);
	return Expr{expr,vars};
}

Expr operator+(const Var& v1, const Expr& e1){
	std::string expr =  v1.get_name() + " + (" + e1.expression + ")";
	std::vector<Var> vars{e1.get_variables()};
	bool already_present = false;
	for(auto& v : e1.get_variables())
		if(!v.get_name().compare(v1.get_name())){
			already_present = true;
			break;
		}
	if(!already_present)
		vars.push_back(v1);
	return Expr{expr,vars};
}

Expr operator- (const Expr& e1, const Var& v1){
	std::string expr = "(" + e1.expression + ") - " + v1.get_name();
	std::vector<Var> vars{e1.get_variables()};
	bool already_present = false;
	for(auto& v : e1.get_variables())
		if(!v.get_name().compare(v1.get_name())){
			already_present = true;
			break;
		}
	if(!already_present)
		vars.push_back(v1);
	return Expr{expr,vars};
}

Expr operator-(const Var& v1, const Expr& e1){
	std::string expr = v1.get_name() + " - (" + e1.expression + ")";
	std::vector<Var> vars{e1.get_variables()};
	bool already_present = false;
	for(auto& v : e1.get_variables())
		if(!v.get_name().compare(v1.get_name())){
			already_present = true;
			break;
		}
	if(!already_present)
		vars.push_back(v1);
	return Expr{expr,vars};
}

Expr operator* (const Expr& e1, const Var& v1){
	std::string expr = "(" + e1.expression + ") * " + v1.get_name();
	std::vector<Var> vars{e1.get_variables()};
	bool already_present = false;
	for(auto& v : e1.get_variables())
		if(!v.get_name().compare(v1.get_name())){
			already_present = true;
			break;
		}
	if(!already_present)
		vars.push_back(v1);
	return Expr{expr,vars};
}

Expr operator*(const Var& v1, const Expr& e1){
	std::string expr = v1.get_name() + " * (" + e1.expression + ")";
	std::vector<Var> vars{e1.get_variables()};
	bool already_present = false;
	for(auto& v : e1.get_variables())
		if(!v.get_name().compare(v1.get_name())){
			already_present = true;
			break;
		}
	if(!already_present)
		vars.push_back(v1);
	return Expr{expr,vars};
}

Expr operator+(const Expr& e1, const Expr& e2){
	std::string expr = "(" + e1.expression + ") + (" + e2.expression + ")";
	std::vector<Var> vars{e1.get_variables()};
	for(auto& v2 : e2.get_variables()){
		bool already_present = false;
		for(auto& v1 : e1.get_variables())
			if(!v1.get_name().compare(v2.get_name())){
				already_present = true;
					break;
			}
		if(!already_present)
			vars.push_back(v2);
	}
	return Expr{expr,vars};
}

Expr operator-(const Expr& e1, const Expr& e2){
	std::string expr = "(" + e1.expression + ") - (" + e2.expression + ")";
	std::vector<Var> vars{e1.get_variables()};
	for(auto& v2 : e2.get_variables()){
		bool already_present = false;
		for(auto& v1 : e1.get_variables())
			if(!v1.get_name().compare(v2.get_name())){
				already_present = true;
					break;
			}
		if(!already_present)
			vars.push_back(v2);
	}
	return Expr{expr,vars};
}

Expr operator*(const Expr& e1, const Expr& e2){
	std::string expr = "(" + e1.expression + ") * (" + e2.expression + ")";
	std::vector<Var> vars{e1.get_variables()};
	for(auto& v2 : e2.get_variables()){
		bool already_present = false;
		for(auto& v1 : e1.get_variables())
			if(!v1.get_name().compare(v2.get_name())){
				already_present = true;
					break;
			}
		if(!already_present)
			vars.push_back(v2);
	}	
	return Expr{expr,vars};
}*/

