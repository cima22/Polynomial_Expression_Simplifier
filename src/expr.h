#include <iostream>
#include <memory>
#include "expr_parent.h"
#include "expr_child.h"

class Expr{
	private:
		std::shared_ptr<ParentExpr> obj;

	public:
		Expr(const Expr& expr);
		Expr(ParentExpr * ptr);
		Expr();
		std::map<unsigned int,Expr> get_coeffs(const Var& v);
		Expr &replace(const std::map<Var,Expr>& repl);
		bool equivalent(const Expr& e1, const Expr& e2);
		
		ParentExpr& get_obj() const;

		friend std::ostream& operator<<(std::ostream& os, const Expr& ex);
		Expr& operator=(CompExpr& e1);

		/*	
		friend const Expr operator+ (const CompExpr& e1, const CompExpr& e2);
		friend const Expr operator- (const CompExpr& e1, const CompExpr& e2);
		friend const Expr operator* (const CompExpr& e1, const CompExpr& e2);

		friend const Expr operator+ (const Expr& e1, int i);
		friend const Expr operator+ (int i, const Expr& e1);

		friend const Expr operator- (const Expr& e1, int i);
		friend const Expr operator- (int i, const Expr& e1);
		
		friend const Expr operator* (const Expr& e1, int i);
		friend const Expr operator* (int i, const Expr& e1);

		friend const Expr operator+ (const Expr& e1, const Var& v1);
		friend const Expr operator+ (const Var& v1, const Expr& e1);

		friend const Expr operator- (const Expr& e1, const Var& v1);
		friend const Expr operator- (const Var& v1, const Expr& e1);

		friend const Expr operator* (const Expr& e1, const Var& v1);
		friend const Expr operator* (const Var& v1, const Expr& e1);*/
};
/*
const Expr operator+ (const Var& v, int c);
const Expr operator+ (int c, const Var& v);
const Expr operator- (const Var& v, int c);
const Expr operator- (int c, const Var& v);
const Expr operator* (const Var& v, int c);
const Expr operator* (int c, const Var& v);
const Expr operator+ (const Var& v1, const Var& v2);
const Expr operator- (const Var& v1, const Var& v2);
const Expr operator* (const Var& v1, const Var& v2);
*/
