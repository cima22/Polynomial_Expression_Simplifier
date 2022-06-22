#include "expr.h"
#include <vector>

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

std::vector<Var> Expr::get_variables() const{
	return obj->get_variables();
}

const Expr Expr::extend(){
	return Expr{obj->extend()};
}

std::map<unsigned int,Expr> Expr::get_coeffs(const Var &v){
	std::map<unsigned int, const ParentExpr*> coeffs = obj->get_coeffs(v);	
	std::map<unsigned int, Expr> coeff_expr{};
	for(auto& e : coeffs)
		coeff_expr.insert({e.first,Expr{e.second}});
	return coeff_expr;
}

bool equivalent(const Expr& e1, const Expr& e2){
	return false;
}

Expr Expr::replace(const std::map<Var,Expr>& repl){
	std::map<Var,const ParentExpr*> inner_repl{};
	for(auto& e : repl)
		inner_repl.insert({e.first,&e.second.get_obj()});
	return Expr{get_obj().replace(inner_repl)};
}

std::ostream& operator<<(std::ostream& os, const Expr& ex){
 os << *ex.obj;
  return os;
}
