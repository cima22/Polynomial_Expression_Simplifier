#include "expr.h"
#include "expr_child.h"

Expr::Expr(const Expr& expr) = default;

Expr::Expr(ParentExpr * ptr){
	obj.reset(ptr);
}

std::ostream& operator<<(std::ostream& os, const Expr& ex){
 os << *ex.obj;
  return os;
}

const Expr operator+ (const Var& v, int c){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
  CompExpr* comp = new CompExpr{*v_e,*c_e,operation::sum};
	return Expr{comp};
}

const Expr operator+ (int c, const Var& v){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
  CompExpr* comp = new CompExpr{*c_e,*v_e,operation::sum};
  return Expr{comp};
}

const Expr operator- (const Var& v, int c){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	CompExpr* comp = new CompExpr{*v_e,*c_e,operation::sub};
  return Expr{comp};
}

const Expr operator- (int c, const Var& v){
	VarExpr* v_e   = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	CompExpr* comp = new CompExpr{*c_e,*v_e,operation::sub};
  return Expr{comp};
}

const Expr operator* (const Var& v, int c){
	VarExpr* v_e    = new VarExpr{v};
	ConstExpr* c_e  = new ConstExpr{c};
	CompExpr* comp = new CompExpr{*v_e,*c_e,operation::mul};
  return Expr{comp};
}

const Expr operator* (int c, const Var& v){
	VarExpr*   v_e = new VarExpr{v};
	ConstExpr* c_e = new ConstExpr{c};
	CompExpr* comp = new CompExpr{*c_e,*v_e,operation::mul};
  return Expr{comp};
}

const Expr operator+ (const Var& v1, const Var& v2){
	VarExpr* v_e_1 = new VarExpr{v1};
	VarExpr* v_e_2 = new VarExpr{v2};
	CompExpr* comp = new CompExpr{*v_e_1,*v_e_2,operation::sum};
  return Expr{comp};
}

const Expr operator- (const Var& v1, const Var& v2){
	VarExpr* v_e_1 = new VarExpr{v1};
	VarExpr* v_e_2 = new VarExpr{v2};
	CompExpr* comp = new CompExpr{*v_e_1,*v_e_2,operation::sub};
  return Expr{comp};
}

const Expr operator* (const Var& v1, const Var& v2){
	VarExpr* v_e_1 = new VarExpr{v1};
	VarExpr* v_e_2 = new VarExpr{v2};
	CompExpr* comp = new CompExpr{*v_e_1,*v_e_2,operation::mul};
	return Expr{comp};
}

const Expr operator+ (const Expr& e1, int i){
	ConstExpr* c_e = new ConstExpr{i};
	CompExpr* comp_sub = new ConstExpr{e1};
	CompExpr* comp = new CompExpr{*comp_sub,*c_e,operation::sum};
	//CompExpr* e    = new CompExpr{e1};
	return Expr{comp};
}

const Expr operator+(int i, const Expr& e1){
	ConstExpr* c_e = new ConstExpr{i};
	//CompExpr* e    = new CompExpr{e1};
	return * new CompExpr{*c_e,e1,operation::sum};
}

const Expr operator- (const Expr& e1, int i){
	ConstExpr* c_e = new ConstExpr{i};
	//CompExpr* e    = new CompExpr{e1};
	return * new CompExpr{e1,*c_e,operation::sub};
}

const Expr operator-(int i, const Expr& e1){
	ConstExpr* c_e = new ConstExpr{i};
	//CompExpr* e    = new CompExpr{e1};
	return * new CompExpr{*c_e,e1,operation::sub};
}

const Expr operator* (const Expr& e1, int i){
	ConstExpr* c_e = new ConstExpr{i};
	return * new CompExpr{e1,*c_e,operation::mul};
}

const Expr operator*(int i, const Expr& e1){
	ConstExpr* c_e = new ConstExpr{i};
	return * new CompExpr{*c_e,e1,operation::mul};
}

const Expr operator+ (const Expr& e1, const Var& v){
	VarExpr* v_e = new VarExpr{v};
	return * new CompExpr{e1,*v_e,operation::sum};
}

const Expr operator+(const Var& v, const Expr& e1){
	VarExpr* v_e = new VarExpr{v};
	//CompExpr* e  = new CompExpr{e1};
	return * new CompExpr{*v_e,e1,operation::sum};
}

const Expr operator- (const Expr& e1, const Var& v){
	VarExpr* v_e = new VarExpr{v};
	//CompExpr* e  = new CompExpr{e1};
	return * new CompExpr{e1,*v_e,operation::sub};
}

const Expr operator-(const Var& v, const Expr& e1){
	VarExpr* v_e = new VarExpr{v};
	//CompExpr* e  = new CompExpr{e1};
	return * new CompExpr{*v_e,e1,operation::sub};
}

const Expr operator* (const Expr& e1, const Var& v){
	VarExpr* v_e = new VarExpr{v};
	//CompExpr* e  = new CompExpr{e1};
	return * new CompExpr{e1,*v_e,operation::mul};
}

const Expr operator*(const Var& v, const Expr& e1){
	VarExpr* v_e = new VarExpr{v};
	//CompExpr* e  = new CompExpr{e1};
	return * new CompExpr{*v_e,e1,operation::mul};
}

const Expr operator+(const Expr& e1, const Expr& e2){
	CompExpr& e_1 = * new CompExpr{e1};
	CompExpr& e_2 = * new CompExpr{e2};
	delete &e1;
	delete &e2;
	return * new CompExpr{e_1,e_2,operation::sum};
}

const Expr operator-(const Expr& e1, const Expr& e2){
	CompExpr& e_1 = * new CompExpr{e1};
	CompExpr& e_2 = * new CompExpr{e2};
	delete &e1;
	delete &e2;
	return * new CompExpr{e_1,e_2,operation::sub};
}

const Expr operator*(const Expr& e1, const Expr& e2){
	CompExpr& e_1 = * new CompExpr{e1};
	CompExpr& e_2 = * new CompExpr{e2};
	delete &e1;
	delete &e2;
	return * new CompExpr{e_1,e_2,operation::mul};
}
