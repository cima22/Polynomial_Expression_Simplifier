#ifndef _EXPR_
#define _EXPR_

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "var.h"

class ParentExpr{
	
	protected:
		std::string expression; 	// string format of the expression
		std::vector<Var> vars;  	// vector of variables

		void extract_vars();

	public:
		ParentExpr();
		ParentExpr(const std::string& expr);
		ParentExpr(const std::string& expr, const std::vector<Var>& vars);
		virtual ~ParentExpr() = 0;
		std::vector<Var> get_variables() const;
		const std::string& to_string() const;

		virtual int evaluate() = 0;
		const virtual ParentExpr& stretch() const = 0;
		const virtual ParentExpr& extend() const = 0;
		virtual bool is_extended() const = 0;
		//virtual std::map<unsigned int, ParentExpr&> get_coeffs(const Var& v) const;

		friend std::ostream& operator<<(std::ostream& os, const ParentExpr& expr);
};

#endif
