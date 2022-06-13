#include "expr_child.h"
#include <string>

VarExpr::VarExpr(const Var& v):
	Expr(v.get_name(),{v}){}

void VarExpr::set_value(int v){
	vars[0].set_value(v);
}

int VarExpr::evaluate(){
	return vars[0].get_value();
}

ConstExpr::ConstExpr(const int i):
	value{i},Expr(std::to_string(i)){}

int ConstExpr::evaluate(){
	return value;
}

std::string CompExpr::create_string(Expr& e1, Expr& e2, const operation op){
	char op_c;
	switch(op){
		case operation::sum:
			op_c = '+';
			break;
		case operation::sub:
			op_c = '-';
			break;
		case operation::mul:
			op_c = '*';
			break;
		default:
			op_c = '?';
			break;
	}
	
	std::string member_1 = e1.to_string();
	std::string member_2 = e2.to_string();
	if(dynamic_cast<CompExpr*>(&e1))
		member_1 = "(" + e1.to_string() + ")";
	if(dynamic_cast<CompExpr*>(&e2))
		member_2 = "(" + e2.to_string() + ")";

	return std::string{member_1 + " " + op_c + " " + member_2};
}

CompExpr::CompExpr(Expr& e1, Expr& e2, const operation op):
	sub_1{e1}, sub_2{e2}, op{op}, Expr(create_string(e1,e2,op))
	{}

int CompExpr::evaluate(){
	return 0;
}

CompExpr& operator+ (const Var& v, int c){
	VarExpr v_e{v};
	ConstExpr c_e{c};
	return * new CompExpr{v_e,c_e,operation::sum};
}
/*
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
}*/
