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

CompExpr& operator+ (int c, const Var& v){
	VarExpr v_e{v};
	ConstExpr c_e{c};
	return * new CompExpr{c_e,v_e,operation::sum};
}
CompExpr& operator- (const Var& v, int c){
	VarExpr v_e{v};
	ConstExpr c_e{c};
	return * new CompExpr{v_e,c_e,operation::sub};
}
CompExpr& operator- (int c, const Var& v){
	VarExpr v_e{v};
	ConstExpr c_e{c};
	return * new CompExpr{c_e,v_e,operation::sub};
}
CompExpr& operator* (const Var& v, int c){
	VarExpr v_e{v};
	ConstExpr c_e{c};
	return * new CompExpr{v_e,c_e,operation::mul};
}
CompExpr& operator* (int c, const Var& v){
	VarExpr v_e{v};
	ConstExpr c_e{c};
	return * new CompExpr{c_e,v_e,operation::mul};
}
CompExpr& operator+ (const Var& v1, const Var& v2){
	VarExpr v_e_1{v1};
	VarExpr v_e_2{v2};
	return * new CompExpr{v_e_1,v_e_2,operation::sum};
}
CompExpr& operator- (const Var& v1, const Var& v2){
	VarExpr v_e_1{v1};
	VarExpr v_e_2{v2};
	return * new CompExpr{v_e_1,v_e_2,operation::sub};
}
CompExpr& operator* (const Var& v1, const Var& v2){
	VarExpr v_e_1{v1};
	VarExpr v_e_2{v2};
	return * new CompExpr{v_e_1,v_e_2,operation::sub};
}

CompExpr& operator+ (CompExpr& e1, int i){
	ConstExpr c_e{i};
	return * new CompExpr{e1,c_e,operation::sum};
}

CompExpr& operator+(int i, CompExpr& e1){
	ConstExpr c_e{i};
	return * new CompExpr{c_e,e1,operation::sum};
}

CompExpr& operator- (CompExpr& e1, int i){
	ConstExpr c_e{i};
	return * new CompExpr{e1,c_e,operation::sub};
}

CompExpr& operator-(int i, CompExpr& e1){
	ConstExpr c_e{i};
	return * new CompExpr{c_e,e1,operation::sub};
}

CompExpr& operator* (CompExpr& e1, int i){
	ConstExpr c_e{i};
	return * new CompExpr{e1,c_e,operation::mul};
}

CompExpr& operator*(int i, CompExpr& e1){
	ConstExpr c_e{i};
	return * new CompExpr{c_e,e1,operation::mul};
}

CompExpr& operator+ (CompExpr& e1, const Var& v){
	VarExpr v_e{v};
	return * new CompExpr{e1,v_e,operation::sum};
}

CompExpr& operator+(const Var& v, CompExpr& e1){
	VarExpr v_e{v};
	return * new CompExpr{v_e,e1,operation::sum};
}

CompExpr& operator- (CompExpr& e1, const Var& v){
	VarExpr v_e{v};
	return * new CompExpr{e1,v_e,operation::sub};
}

CompExpr& operator-(const Var& v, CompExpr& e1){
	VarExpr v_e{v};
	return * new CompExpr{v_e,e1,operation::sub};
}

CompExpr& operator* (CompExpr& e1, const Var& v){
	VarExpr v_e{v};
	return * new CompExpr{e1,v_e,operation::mul};
}

CompExpr& operator*(const Var& v, CompExpr& e1){
	VarExpr v_e{v};
	return * new CompExpr{v_e,e1,operation::mul};
}

CompExpr& operator+(CompExpr& e1, CompExpr& e2){
	return * new CompExpr{e1,e2,operation::sum};
}

CompExpr& operator-(CompExpr& e1, CompExpr& e2){
	return * new CompExpr{e1,e2,operation::sub};
}

CompExpr& operator*(CompExpr& e1, CompExpr& e2){
	return * new CompExpr{e1,e2,operation::mul};
}