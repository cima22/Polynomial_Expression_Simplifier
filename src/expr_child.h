#include "expr_parent.h"
#include <string>
#include <map>

class VarExpr : public ParentExpr{ // Expression which is composed only by one variable, e.g.: x
	private:
		bool is_extended() override;

	public:
		VarExpr(const Var& v);
		virtual ~VarExpr();
		void set_value(int v);
		int evaluate() override;
		VarExpr& stretch() override;
		VarExpr& extend() override;
		//std::map<unsigned int,&ParentExpr> get_coeffs(const Var& v) const override;
};

class ConstExpr : public ParentExpr{ // Expression which is composed only by one constant, e.g.: 2
	private:
		int value;
		bool is_extended() override;
	public:
		ConstExpr(const int i);
		virtual ~ConstExpr();
		int evaluate() override;
		ConstExpr& stretch() override;
		ConstExpr& extend() override;
		//std::map<unsigned int,&ParentExpr> get_coeffs(const Var& v) const override;
};

enum class operation {sum, sub, mul};

class CompExpr : public ParentExpr{ // Exression which is composed by the sum, subtracion of multiplication of two expressions
	private:
		ParentExpr& sub_1;
		ParentExpr& sub_2;
		operation op;

		std::string create_string(ParentExpr& e1, ParentExpr& e2, operation op);
		bool is_CompExpr(ParentExpr& ex);
		
		CompExpr& compute_operation();
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

		bool is_extended();
		bool is_only_mult();

	public:
		CompExpr(ParentExpr& e1, ParentExpr& e2, operation op);
		CompExpr(const std::string& expr, ParentExpr& e1, ParentExpr& e2, operation op);
		CompExpr(const std::string& expr, const std::vector<Var>& vars, ParentExpr& e1, ParentExpr& e2, operation op);
		virtual ~CompExpr();	
	
		int evaluate() override;
		CompExpr& stretch() override;
		CompExpr& extend() override;
		operation get_op();
		ParentExpr& get_sub_1();
		ParentExpr& get_sub_2();
		
		//std::map<unsigned,&ParentExpr> get_coeffs(const Var& x) const override;
	/*	
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
		friend CompExpr& operator* (const Var& v1, CompExpr& e1);*/
};
/*
CompExpr& operator+ (const Var& v, int c);
CompExpr& operator+ (int c, const Var& v);
CompExpr& operator- (const Var& v, int c);
CompExpr& operator- (int c, const Var& v);
CompExpr& operator* (const Var& v, int c);
CompExpr& operator* (int c, const Var& v);
CompExpr& operator+ (const Var& v1, const Var& v2);
CompExpr& operator- (const Var& v1, const Var& v2);
CompExpr& operator* (const Var& v1, const Var& v2);
*/
