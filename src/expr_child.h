#include "expr.h"
#include <string>

class VarExpr : public Expr{ // Expression which is composed only by one variable, e.g.: x
	public:
		VarExpr(const Var& v);
		void set_value(int v);
		int evaluate() override;
		VarExpr& stretch() override;
		VarExpr& extend() override;
		bool is_extended() override;
};

class ConstExpr : public Expr{ // Expression which is composed only by one constant, e.g.: 2
	private:
		int value;
	public:
		ConstExpr(const int i);
		int evaluate() override;
		ConstExpr& stretch() override;
		ConstExpr& extend() override;
		bool is_extended() override;
};

enum class operation {sum, sub, mul};

class CompExpr : public Expr{ // Exression which is composed by the sum, subtracion of multiplication of two expressions
	private:
		Expr& sub_1;
		Expr& sub_2;
		operation op;

		std::string create_string(Expr& e1, Expr& e2, operation op);
		bool is_CompExpr(Expr& ex);
		
		CompExpr& sum_simple_comp();
		CompExpr& mult_simple_comp();
		CompExpr& distr_law();
		CompExpr& compound_sum();
		CompExpr& sum_sum();
		CompExpr& sum_mult();
		CompExpr& sum_mixed();
		CompExpr& compound_mult();
		CompExpr& mult_sum();
		CompExpr& mult_mult();
		CompExpr& mult_mixed();

		//bool is_extended();
		bool is_only_mult();

	public:
		CompExpr(Expr& e1, Expr& e2, operation op);
		CompExpr(const std::string& expr, Expr& e1, Expr& e2, operation op);
		CompExpr(const std::string& expr, const std::vector<Var>& vars, Expr& e1, Expr& e2, operation op);
		
		int evaluate() override;
		CompExpr& stretch() override;
		CompExpr& extend() override;
		operation get_op();
		Expr& get_sub_1();
		Expr& get_sub_2();
		
		bool is_extended();

		CompExpr& compute_operation();
		
		friend CompExpr& operator+ (const CompExpr& e1, const CompExpr& e2);
		friend CompExpr& operator- (const CompExpr& e1, const CompExpr& e2);
		friend CompExpr& operator* (const CompExpr& e1, const CompExpr& e2);

		friend CompExpr& operator+ (CompExpr& e1, int i);
		friend CompExpr& operator+ (int i, CompExpr& e1);

		friend CompExpr& operator- (CompExpr& e1, int i);
		friend CompExpr& operator- (int i, CompExpr& e1);
		
		friend CompExpr& operator* (CompExpr& e1, int i);
		friend CompExpr& operator* (int i, CompExpr& e1);

		friend CompExpr& operator+ (CompExpr& e1, const Var& v1);
		friend CompExpr& operator+ (const Var& v1, CompExpr& e1);

		friend CompExpr& operator- (CompExpr& e1, const Var& v1);
		friend CompExpr& operator- (const Var& v1, CompExpr& e1);

		friend CompExpr& operator* (CompExpr& e1, const Var& v1);
		friend CompExpr& operator* (const Var& v1, CompExpr& e1);
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
