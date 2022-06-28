#include "expr.h"

typedef std::pair<int,std::map<Var,unsigned int>> monomial;

// Constructors

Expr::Expr() = default;

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

// Public methods

const ParentExpr& Expr::get_obj() const{
	return *obj;
}

std::vector<Var> Expr::get_variables() const{
	return obj->get_variables();
}

Expr Expr::unroll(){
	return Expr{obj->unroll()};
}

std::map<unsigned int,Expr> Expr::get_coeffs(const Var &v){
	std::map<unsigned int, const ParentExpr*> coeffs = obj->get_coeffs(v);	
	std::map<unsigned int, Expr> coeff_expr{};
	for(auto& e : coeffs)
		coeff_expr.insert({e.first,Expr{e.second}});
	return coeff_expr;
}

bool equivalent(const Expr& e1, const Expr& e2){ // if two expressions are composed of the same monomials, then they are equal
	std::vector<monomial> v1 = e1.obj->get_vector_of_monomials();
	std::vector<monomial> v2 = e2.obj->get_vector_of_monomials();
	return std::is_permutation(v1.begin(),v1.end(),v2.begin());
}

Expr Expr::replace(const std::map<Var,Expr>& repl){
	std::map<Var,const ParentExpr*> inner_repl{}; // map to be used in the ParentExpr method replace
	for(auto& e : repl)
		inner_repl.insert({e.first,&e.second.get_obj()});
	return Expr{get_obj().replace(inner_repl)};
}

std::ostream& operator<<(std::ostream& os, const Expr& ex){
 os << *ex.obj; // use the operator defined in ParentExpr
  return os;
}

bool operator==(const Expr& e1, const Expr& e2){
	return equivalent(e1,e2);
}
