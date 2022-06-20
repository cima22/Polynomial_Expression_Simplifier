#include "expr_parent.h"
#include <string>
#include <map>
#include <memory>

class VarExpr : public ParentExpr{ // Expression which is composed only by one variable, e.g.: x
	private:
		bool is_extended() const override;

	public:
		VarExpr(const Var& v);
		virtual ~VarExpr();
		void set_value(int v);
		int evaluate() override;
		const VarExpr& stretch() const override;
		const VarExpr& extend() const override;
		const VarExpr& clone() const override;
		bool is_only_mult() const override;
		std::map<unsigned int,const ParentExpr&> get_coeffs(const Var& v) const override;
		void insert_coeff(std::map<unsigned int, const ParentExpr&>& coeffs,const Var& v) const override;
};

class ConstExpr : public ParentExpr{ // Expression which is composed only by one constant, e.g.: 2
	private:
		int value;
		bool is_extended() const override;

	public:
		ConstExpr(const int i);
		virtual ~ConstExpr();
		int evaluate() override;
		const ConstExpr& stretch() const override;
		const ConstExpr& extend() const override;
		const ConstExpr& clone() const override;
		bool is_only_mult() const override;
		std::map<unsigned int,const ParentExpr&> get_coeffs(const Var& v) const override;
		void insert_coeff(std::map<unsigned int, const ParentExpr&>& coeffs,const Var& v) const override;
};

enum class operation {sum, sub, mul};

class CompExpr : public ParentExpr{ // Exression which is composed by the sum, subtracion of multiplication of two expressions
	private:
		const ParentExpr& sub_1;
		const ParentExpr& sub_2;
		operation op;

		std::string create_string(const ParentExpr& e1, const ParentExpr& e2, operation op);
		bool is_CompExpr(const ParentExpr& ex) const;
			
		const CompExpr& compute_operation();
		const CompExpr& sum_simple_comp();
		const CompExpr& mult_simple_comp();
		const CompExpr& distr_law();
		const CompExpr& compound_sum();
		const CompExpr& sum_sum();
		const CompExpr& sum_mult();
		const CompExpr& sum_mixed();
		const CompExpr& compound_mult();
		const CompExpr& mult_sum();
		const CompExpr& mult_mult();
		const CompExpr& mult_mixed();

		bool is_extended() const override;

	public:
		CompExpr(const ParentExpr& e1, const ParentExpr& e2, operation op);
		CompExpr(const std::string& expr, const ParentExpr& e1, const ParentExpr& e2, operation op);
		CompExpr(const std::string& expr, const std::vector<Var>& vars, const ParentExpr& e1, const ParentExpr& e2, operation op);
		CompExpr(const CompExpr& comp);
		virtual ~CompExpr();	
	
		int evaluate() override;
		const CompExpr& stretch() const override;
		const CompExpr& extend() const override;
		const operation get_op() const;
		const ParentExpr& get_sub_1() const;
		const ParentExpr& get_sub_2() const;
		std::map<unsigned int,const ParentExpr&> get_coeffs(const Var& x) const override;
		void insert_coeff(std::map<unsigned int,const ParentExpr&>& coeffs,const Var& v) const override;
		const CompExpr& clone() const override;
		bool is_only_mult() const override;

		friend const CompExpr& operator+ (const CompExpr& e1, const CompExpr& e2);
		friend const CompExpr& operator- (const CompExpr& e1, const CompExpr& e2);
		friend const CompExpr& operator* (const CompExpr& e1, const CompExpr& e2);

		friend const CompExpr& operator+ (const CompExpr& e1, int i);
		friend const CompExpr& operator+ (int i, const CompExpr& e1);

		friend const CompExpr& operator- (const CompExpr& e1, int i);
		friend const CompExpr& operator- (int i, const CompExpr& e1);
		
		friend const CompExpr& operator* (const CompExpr& e1, int i);
		friend const CompExpr& operator* (int i, const CompExpr& e1);

		friend const CompExpr& operator+ (const CompExpr& e1, const Var& v1);
		friend const CompExpr& operator+ (const Var& v1, const CompExpr& e1);

		friend const CompExpr& operator- (const CompExpr& e1, const Var& v1);
		friend const CompExpr& operator- (const Var& v1, const CompExpr& e1);

		friend const CompExpr& operator* (const CompExpr& e1, const Var& v1);
		friend const CompExpr& operator* (const Var& v1, const CompExpr& e1);
};

const CompExpr& operator+ (const Var& v, int c);
const CompExpr& operator+ (int c, const Var& v);
const CompExpr& operator- (const Var& v, int c);
const CompExpr& operator- (int c, const Var& v);
const CompExpr& operator* (const Var& v, int c);
const CompExpr& operator* (int c, const Var& v);
const CompExpr& operator+ (const Var& v1, const Var& v2);
const CompExpr& operator- (const Var& v1, const Var& v2);
const CompExpr& operator* (const Var& v1, const Var& v2);
