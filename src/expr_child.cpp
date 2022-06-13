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

std::string VarExpr::stretch(){
	return expression;
}

ConstExpr::ConstExpr(const int i):
	value{i},Expr(std::to_string(i)){}

int ConstExpr::evaluate(){
	return value;
}

std::string ConstExpr::stretch(){
	return expression;
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

std::string CompExpr::stretch(){
	switch(op){
		case operation::sum:
			return sub_1.to_string() + " + " + sub_2.to_string();
		default:
			return "bau";

	}
}

int CompExpr::evaluate(){
	return 0;
}

// operators ---------------------------------------------------------------------------

CompExpr& operator+ (const Var& v, int c){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new CompExpr{*v_e,*c_e,operation::sum};
}

CompExpr& operator+ (int c, const Var& v){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new CompExpr{*c_e,*v_e,operation::sum};
}
CompExpr& operator- (const Var& v, int c){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new CompExpr{*v_e,*c_e,operation::sub};
}
CompExpr& operator- (int c, const Var& v){
	VarExpr* v_e   = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new CompExpr{*c_e,*v_e,operation::sub};
}
CompExpr& operator* (const Var& v, int c){
	VarExpr* v_e   = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new CompExpr{*v_e,*c_e,operation::mul};
}
CompExpr& operator* (int c, const Var& v){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	return * new CompExpr{*c_e,*v_e,operation::mul};
}
CompExpr& operator+ (const Var& v1, const Var& v2){
	VarExpr* v_e_1 = new VarExpr{v1};
	VarExpr* v_e_2 = new VarExpr{v2};
	return * new CompExpr{*v_e_1,*v_e_2,operation::sum};
}
CompExpr& operator- (const Var& v1, const Var& v2){
	VarExpr* v_e_1 = new VarExpr{v1};
	VarExpr* v_e_2 = new VarExpr{v2};
	return * new CompExpr{*v_e_1,*v_e_2,operation::sub};
}
CompExpr& operator* (const Var& v1, const Var& v2){
	VarExpr* v_e_1 = new VarExpr{v1};
	VarExpr* v_e_2 = new VarExpr{v2};
	return * new CompExpr{*v_e_1,*v_e_2,operation::sub};
}

CompExpr& operator+ (const CompExpr& e1, int i){
	ConstExpr* c_e = new ConstExpr{i};
	CompExpr* e = new CompExpr{e1};
	return * new CompExpr{*e,*c_e,operation::sum};
}

CompExpr& operator+(int i, const CompExpr& e1){
	ConstExpr* c_e = new ConstExpr{i};
	CompExpr* e = new CompExpr{e1};
	return * new CompExpr{*c_e,*e,operation::sum};
}

CompExpr& operator- (const CompExpr& e1, int i){
	ConstExpr* c_e = new ConstExpr{i};
	CompExpr* e = new CompExpr{e1};
	return * new CompExpr{*e,*c_e,operation::sub};
}

CompExpr& operator-(int i, const CompExpr& e1){
	ConstExpr* c_e = new ConstExpr{i};
	CompExpr* e = new CompExpr{e1};
	return * new CompExpr{*c_e,*e,operation::sub};
}

CompExpr& operator* (const CompExpr& e1, int i){
	ConstExpr* c_e = new ConstExpr{i};
	CompExpr* e = new CompExpr{e1};
	return * new CompExpr{*e,*c_e,operation::mul};
}

CompExpr& operator*(int i, const CompExpr& e1){
	ConstExpr* c_e = new ConstExpr{i};
	CompExpr* e = new CompExpr{e1};
	return * new CompExpr{*c_e,*e,operation::mul};
}

CompExpr& operator+ (const CompExpr& e1, const Var& v){
	VarExpr* c_e = new VarExpr{i};
	CompExpr* e = new CompExpr{e1};
	return * new CompExpr{*e,*v_e,operation::sum};
}

CompExpr& operator+(const Var& v, const CompExpr& e1){
	VarExpr* c_e = new VarExpr{i};
	CompExpr* e = new CompExpr{e1};
	return * new CompExpr{*v_e,*e,operation::sum};
}

CompExpr& operator- (const CompExpr& e1, const Var& v){
	VarExpr* c_e = new VarExpr{i};
	CompExpr* e = new CompExpr{e1};
	return * new CompExpr{*e,*v_e,operation::sub};
}

CompExpr& operator-(const Var& v, const CompExpr& e1){
	VarExpr* c_e = new VarExpr{i};
	CompExpr* e = new CompExpr{e1};
	return * new CompExpr{*v_e,*e,operation::sub};
}

CompExpr& operator* (const CompExpr& e1, const Var& v){
	VarExpr* c_e = new VarExpr{i};
	CompExpr* e = new CompExpr{e1};
	return * new CompExpr{*e,*v_e,operation::mul};
}

CompExpr& operator*(const Var& v, const CompExpr& e1){
	VarExpr* c_e = new VarExpr{i};
	CompExpr* e = new CompExpr{e1};
	return * new CompExpr{*v_e,*e,operation::mul};
}

CompExpr& operator+(const CompExpr& e1, const CompExpr& e2){
	CompExpr e_1 = e1;
	CompExpr e_2 = e2;
	return * new CompExpr{e_1,e_2,operation::sum};
}

CompExpr& operator-(const CompExpr& e1, const CompExpr& e2){
	CompExpr e_1 = e1;
	CompExpr e_2 = e2;
	return * new CompExpr{e_1,e_2,operation::sub};
}

CompExpr& operator*(const CompExpr& e1, const CompExpr& e2){
	CompExpr e_1 = e1;
	CompExpr e_2 = e2;
	return * new CompExpr{e_1,e_2,operation::mul};
}
