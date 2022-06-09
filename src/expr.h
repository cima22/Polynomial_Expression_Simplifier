#ifndef _EXPR_
#define _EXPR_

#include <string>
#include <vector>
#include <algorithm>
#include "var.h"

enum class operation {sum, sub, mul};

class Expr{
	
	private:
		std::string expression; // string format of the expression
		std::vector<Var> vars;  // vector of variables
		const Expr* sub_expression_1;
		const Expr* sub_expression_2;
		operation op;

		void extract_vars();

	public:
		//Expr();
		//Expr(const std::string& expr);
		Expr(const std::string& expr, const std::vector<Var>& vars);
		Expr(const std::string& expr, const std::vector<Var>& vars, const Expr& sub_1, const Expr& sub_2);

		std::vector<Var> get_variables() const;
		
		int evaluate(const std::vector<Var>& v) const;

		friend std::ostream& operator<<(std::ostream& os, const Expr& expr);
		
		friend Expr operator+(const Expr& e1, const Expr& e2);
		friend Expr operator-(const Expr& e1, const Expr& e2);
		friend Expr operator*(const Expr& e1, const Expr& e2);

		friend Expr operator+(const Expr& e1, int i);
		friend Expr operator+(int i, const Expr& e1);

		friend Expr operator-(const Expr& e1, int i);
		friend Expr operator-(int i, const Expr& e1);
		
		friend Expr operator*(const Expr& e1, int i);
		friend Expr operator*(int i, const Expr& e1);

		friend Expr operator+(const Expr& e1, const Var& v1);
		friend Expr operator+(const Var& v1, const Expr& e1);

		friend Expr operator-(const Expr& e1, const Var& v1);
		friend Expr operator-(const Var& v1, const Expr& e1);

		friend Expr operator*(const Expr& e1, const Var& v1);
		friend Expr operator*(const Var& v1, const Expr& e1);

};

Expr operator+ (const Var& v, int c);
Expr operator+ (int c, const Var& v);
Expr operator- (const Var& v, int c);
Expr operator- (int c, const Var& v);
Expr operator* (const Var& v, int c);
Expr operator* (int c, const Var& v);

Expr operator+ (const Var& v1, const Var& v2);
Expr operator- (const Var& v1, const Var& v2);
Expr operator* (const Var& v1, const Var& v2);

#endif
