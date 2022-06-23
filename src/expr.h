#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include "expr_parent.h"
#include "expr_child.h"
#include "var.h"

class Expr{
	private:
		std::shared_ptr<const ParentExpr> obj;

	public:
		Expr(const Expr& expr);
		Expr(const ParentExpr * ptr);
		Expr(const CompExpr& comp_expr);
		Expr(const ParentExpr& expr);
		Expr(Var& v);
		Expr(int i);
		Expr();
		
		std::vector<Var> get_variables() const;
		std::map<unsigned int,Expr> get_coeffs(const Var& v);
		Expr replace(const std::map<Var,Expr>& repl);
		bool equivalent(const Expr& e1, const Expr& e2);
		const Expr unroll();
		const ParentExpr& get_obj() const;

		friend std::ostream& operator<<(std::ostream& os, const Expr& ex);
		Expr& operator=(CompExpr& e1);

		friend bool equivalent(const Expr& e1, const Expr& e2);
	};

