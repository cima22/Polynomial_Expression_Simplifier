#include "expr.h"
#include <string>

class VarExpr : public Expr{ // Expression which is composed only by one variable, e.g.: x
	public:
		VarExpr(const Var& v);
		void set_value(int v);
		int evaluate() override;
		VarExpr& stretch() override;
};

class ConstExpr : public Expr{ // Expression which is composed only by one constant, e.g.: 2
	private:
		int value;
	public:
		ConstExpr(const int i);
		int evaluate() override;
		ConstExpr& stretch() override;
};

enum class operation {sum, sub, mul};

class CompExpr : public Expr{ // Exression which is composed by the sum, subtracion of multiplication of two expressions
	private:
		Expr& sub_1;
		Expr& sub_2;
		operation op;

		std::string create_string(Expr& e1, Expr& e2, operation op);

	public:
		CompExpr(Expr& e1, Expr& e2, operation op);
		
		int evaluate() override;
		CompExpr& stretch() override;
	
		friend CompExpr& operator+ (const CompExpr& e1, const CompExpr& e2);
		friend CompExpr& operator- (const CompExpr& e1, const CompExpr& e2);
		friend CompExpr& operator* (const CompExpr& e1, const CompExpr& e2);

		friend CompExpr& operator+ (const CompExpr& e1, int i);
		friend CompExpr& operator+ (int i, const CompExpr& e1);

		friend CompExpr& operator- (const CompExpr& e1, int i);
		friend CompExpr& operator- (int i, const CompExpr& e1);
		
		friend CompExpr& operator* (const CompExpr& e1, int i);
		friend CompExpr& operator* (int i, const CompExpr& e1);

		friend CompExpr& operator+ (const CompExpr& e1, const Var& v1);
		friend CompExpr& operator+ (const Var& v1, const CompExpr& e1);

		friend CompExpr& operator- (const CompExpr& e1, const Var& v1);
		friend CompExpr& operator- (const Var& v1, const CompExpr& e1);

		friend CompExpr& operator* (const CompExpr& e1, const Var& v1);
		friend CompExpr& operator* (const Var& v1, const CompExpr& e1);
};

CompExpr& operator+ (const Var& v, int c);
CompExpr& operator+ (int c, const Var& v);
CompExpr& operator- (const Var& v, int c);
CompExpr& operator- (int c, const Var& v);
CompExpr& operator* (const Var& v, int c);
CompExpr& operator* (int c, const Var& v);
CompExpr& operator+ (const Var& v1, const Var& v2);
CompExpr& operator- (const Var& v1, const Var& v2);
CompExpr& operator* (const Var& v1, const Var& v2);
