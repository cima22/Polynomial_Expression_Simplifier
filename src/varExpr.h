#include "expr.h"
class VarExpr : public Expr{
	public:
		VarExpr(const Var& v);
};
