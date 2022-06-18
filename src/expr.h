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

const Expr& operator+ (const Var& v, int c);
const Expr& operator+ (int c, const Var& v);
const Expr& operator- (const Var& v, int c);
const Expr& operator- (int c, const Var& v);
const Expr& operator* (const Var& v, int c);
const Expr& operator* (int c, const Var& v);
const Expr& operator+ (const Var& v1, const Var& v2);
const Expr& operator- (const Var& v1, const Var& v2);
const Expr& operator* (const Var& v1, const Var& v2);
