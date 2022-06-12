#include "expr.h"
class VarExpr : public Expr{
	public:
		VarExpr(const Var& v);
};

class ConstExpr : public Expr{
	public:
		ConstExpr(const int i);
};

class CompExpr : public Expr{
	public:
		CompExpr(const Expr& e1, const Expr& e2);
}
