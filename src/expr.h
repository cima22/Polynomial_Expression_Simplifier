#include <iostream>
#include <memory>
#include "expr_parent.h"

class Expr{
	private:
		std::unique_ptr<ExprParent> obj;

	public:
		Expr(ParentExpr *);
		std::map<unsigned int,Expr> get_coeffs(const Var& v);
		Expr &replace(const std::map<Var,Expr>& repl);
		bool equivalent(const Expr& e1, const Expr& e2);

		friend ostream& operator<<(ostream& os, const Expr& ex);

};
