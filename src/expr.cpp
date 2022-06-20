#include "expr.h"

Expr::Expr() = default;

Expr::Expr(const Expr& expr) = default;

Expr::Expr(const ParentExpr * ptr){
	obj.reset(ptr);
}

Expr::Expr(const CompExpr& comp_expr){
	obj.reset(&comp_expr);
}

Expr::Expr(Var& v){
	VarExpr* v_ptr = new VarExpr{v};
	obj.reset(v_ptr);
}

Expr::Expr(int i){
	ConstExpr* c_ptr = new ConstExpr{i};
	obj.reset(c_ptr);
}

Expr::Expr(const ParentExpr& expr){
	obj.reset(&expr);
}

const ParentExpr& Expr::get_obj() const{
	return *obj;
}

const Expr Expr::extend(){
	return Expr{obj->extend()};
}

const Expr Expr::stretch(){
	return Expr{obj->stretch()};
}

std::ostream& operator<<(std::ostream& os, const Expr& ex){
 os << *ex.obj;
  return os;
}
