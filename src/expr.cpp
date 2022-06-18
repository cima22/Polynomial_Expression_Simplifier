#include "expr.h"
#include "expr_child.h"

Expr::Expr(const Expr& expr) = default;

Expr::Expr(ParentExpr * ptr):
obj{ptr}{}

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
