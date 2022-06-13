#include "expr.h"
#include <string>

class VarExpr : public Expr{
	public:
		VarExpr(const Var& v);
		void set_value(int v);
		int evaluate() override;
};

class ConstExpr : public Expr{
	private:
		int value;
	public:
		ConstExpr(const int i);
		int evaluate() override;
};

enum class operation {sum, sub, mul};

class CompExpr : public Expr{
	private:
		Expr& sub_1;
		Expr& sub_2;
		operation op;

		std::string create_string(Expr& e1, Expr& e2, operation op);

	public:
		CompExpr(Expr& e1, Expr& e2, operation op);
		int evaluate() override;
	
		friend CompExpr& operator+(const CompExpr& e1, const CompExpr& e2);
		friend CompExpr& operator-(const CompExpr& e1, const CompExpr& e2);
		friend CompExpr& operator*(const CompExpr& e1, const CompExpr& e2);

		friend CompExpr& operator+(const CompExpr& e1, int i);
		friend CompExpr& operator+(int i, const CompExpr& e1);

		friend CompExpr& operator-(const CompExpr& e1, int i);
		friend CompExpr& operator-(int i, const CompExpr& e1);
		
		friend CompExpr& operator*(const CompExpr& e1, int i);
		friend CompExpr& operator*(int i, const CompExpr& e1);

		friend CompExpr& operator+(const CompExpr& e1, const Var& v1);
		friend CompExpr& operator+(const Var& v1, const CompExpr& e1);

		friend CompExpr& operator-(const CompExpr& e1, const Var& v1);
		friend CompExpr& operator-(const Var& v1, const CompExpr& e1);

		friend CompExpr& operator*(const CompExpr& e1, const Var& v1);
		friend CompExpr& operator*(const Var& v1, const CompExpr& e1);
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
