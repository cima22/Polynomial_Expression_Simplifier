#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include "expr_parent.h"
#include "expr_child.h"
#include "var.h"

/*
 * Class which serves as an interface for the expressions. In order to conciliate RAII and polymorphism, a shared_ptr to the actual expression is present as a private member. All the public members call the relative public member of the abstract class "ParentExpr".
 */

class Expr{
	private:
		std::shared_ptr<const ParentExpr> obj;

	public:
		// Constructors

		Expr(const Expr& expr);
		Expr(const ParentExpr * ptr);
		Expr(const CompExpr& comp_expr);
		Expr(const ParentExpr& expr);
		Expr(Var& v);
		Expr(int i);
		Expr();
		
		// Public Methods

		std::vector<Var> get_variables() const;
		std::map<unsigned int,Expr> get_coeffs(const Var& v);
		Expr replace(const std::map<Var,Expr>& repl);
		bool equivalent(const Expr& e1, const Expr& e2);
		const Expr unroll();
		const ParentExpr& get_obj() const;

		// Friend operators

		friend std::ostream& operator<<(std::ostream& os, const Expr& ex);
		friend bool equivalent(const Expr& e1, const Expr& e2);
	};

