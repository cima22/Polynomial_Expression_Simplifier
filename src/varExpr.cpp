#include "varExpr.h"
#include <vector>

VarExpr::VarExpr(const Var& v):Expr(v.get_name(),{v}){
	
}
