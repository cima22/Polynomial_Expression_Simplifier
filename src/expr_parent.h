#ifndef _EXPR_
#define _EXPR_

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "var.h"

class Expr{
	
	protected:
		std::string expression; 	// string format of the expression
		std::vector<Var> vars;  	// vector of variables

		void extract_vars();

	public:
		Expr();
		Expr(const std::string& expr);
		Expr(const std::string& expr, const std::vector<Var>& vars);

		std::vector<Var> get_variables() const;
		const std::string& to_string() const;

		virtual int evaluate() = 0;
		virtual Expr& stretch() = 0;
		virtual Expr& extend() = 0;
		virtual bool is_extended() = 0;
		virtual std::map<unsigned int, &Expr> get_coeffs(const Var& v) const;

		friend std::ostream& operator<<(std::ostream& os, const Expr& expr);
};

#endif
